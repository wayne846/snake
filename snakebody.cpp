#include "snakebody.h"
#include "mainwindow.h"

SnakeBody::SnakeBody(MainWindow *window, int x, int y)
{
    this->window = window;
    this->x = x;
    this->y = y;
    this->myTile = window->scene->addRect(QRect(0, 0, window->TILE_WIDTH, window->TILE_WIDTH), QPen(window->LINE_COLOR, 2.4), QBrush(window->SNAKE_COLOR));
    this->myTile->setPos(window->TILE_WIDTH * x, window->TILE_WIDTH * y);
}

SnakeBody::~SnakeBody(){
    delete(myTile);
}
