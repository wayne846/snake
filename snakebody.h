#ifndef SNAKEBODY_H
#define SNAKEBODY_H
#include <QGraphicsItem>

class MainWindow;

class SnakeBody
{
    public:
        SnakeBody(MainWindow *window, int x, int y);

        MainWindow *window;
        int x;
        int y;
        QGraphicsRectItem *myTile;

        ~SnakeBody();
};

#endif // SNAKEBODY_H
