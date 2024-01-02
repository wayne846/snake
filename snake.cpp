#include "snake.h"
#include "mainwindow.h"
#include <cmath>
#include <QDebug>

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
    this->length = 3;

    //init other value
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

    //need edit when eat apple
    bodyQueue.pop();
    bodyMap[lastBody->x][lastBody->y] = NULL;
    delete(lastBody);

    //now you can move
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
