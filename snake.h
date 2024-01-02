#ifndef SNAKE_H
#define SNAKE_H
#include <QGraphicsItem>
#include <queue>
#include "snakebody.h"

class mainwindow;

using namespace std;

class Snake
{
    public:
        Snake(MainWindow *window);

        bool move();
        void turnRight();
        void turnLeft();
        void turnUp();
        void turnDown();

    private:
        MainWindow *window;
        int x;
        int y;
        int dir; // 0:up  1:right  2:down  3:left
        int length;

        bool canTurn;



        queue<SnakeBody*> bodyQueue;
        SnakeBody *bodyMap[28][20]; // [x][y]

        void makeApple();
        QGraphicsEllipseItem *apple;
        int appleX;
        int appleY;


};

#endif // SNAKE_H
