#include "snake.h"
#include "mainwindow.h"
#include <cmath>
#include <QDebug>
#include <stdlib.h>

using namespace std;

Snake::Snake(MainWindow *window)
{
    this->window = window;
    this->x = floor(window->SCENE_WIDTH_TILE_NUM * 0.25);
    this->y = floor(window->SCENE_HEIGHT_TILE_NUM * 0.5);
    this->dir = 1;

    //init bodyMap
    for(int i = 0; i < window->SCENE_WIDTH_TILE_NUM; i++){
        for(int j = 0; j < window->SCENE_HEIGHT_TILE_NUM; j++){
            this->bodyMap[i][j] = NULL;
        }
    }

    for(int i = 0; i < 3; i++){
        SnakeBody *newBody = new SnakeBody(window, this->x, this->y);
        this->bodyQueue.push(newBody);
        this->bodyMap[this->x][this->y] = newBody;
        if(i != 2) this->x += 1;
    }

    makeApple();

    //init other value
    this->length = 0;
    canTurn = true;
}

bool Snake::move(){
    int nextX = x;
    int nextY = y;
    canTurn = true;

    //qDebug() << "x:" << x << "y:" << y;

    switch(dir){
        case 0:
            nextY--;
            break;
        case 1:
            nextX++;
            break;
        case 2:
            nextY++;
            break;
        case 3:
            nextX--;
            break;
    }

    //check bound
    if(nextX < 0 || nextX >= window->SCENE_WIDTH_TILE_NUM) return false;
    if(nextY < 0 || nextY >= window->SCENE_HEIGHT_TILE_NUM) return false;

    //check body
    SnakeBody *lastBody = bodyQueue.front();
    if(bodyMap[nextX][nextY] != NULL && bodyMap[nextX][nextY] != lastBody) return false;

    //now you can move
    //eat apple
    if(nextX == appleX && nextY == appleY){
        delete(apple);
        makeApple();
        length++;
        window->text_score->setPlainText(QString::number(length));
    }else{
        bodyQueue.pop();
        bodyMap[lastBody->x][lastBody->y] = NULL;
        delete(lastBody);
    }


    //make new body
    x = nextX;
    y = nextY;
    SnakeBody *newBody = new SnakeBody(window, x, y);
    bodyQueue.push(newBody);
    bodyMap[x][y] = newBody;

    return true;
}

void Snake::turnRight(){
    if(dir == 3 || dir == 1 || !canTurn) return;
    dir = 1;
    canTurn = false;
}

void Snake::turnLeft(){
    if(dir == 1 || dir == 3 || !canTurn) return;
    dir = 3;
    canTurn = false;
}

void Snake::turnUp(){
    if(dir == 2 || dir == 0 || !canTurn) return;
    dir = 0;
    canTurn = false;
}

void Snake::turnDown(){
    if(dir == 0 || dir == 2 || !canTurn) return;
    dir = 2;
    canTurn = false;
}

void Snake::makeApple(){
    srand(time(NULL));
    appleX = rand() % window->SCENE_WIDTH_TILE_NUM;
    appleY = rand() % window->SCENE_HEIGHT_TILE_NUM;
    while(bodyMap[appleX][appleY] != NULL){
        appleX = rand() % window->SCENE_WIDTH_TILE_NUM;
        appleY = rand() % window->SCENE_HEIGHT_TILE_NUM;
    }
    apple = window->scene->addEllipse(QRect(0, 0, window->TILE_WIDTH, window->TILE_WIDTH), QPen(window->LINE_COLOR, 2.5), QBrush(window->APPLE_COLOR));
    apple->setPos(window->TILE_WIDTH * appleX, window->TILE_WIDTH * appleY);
}

