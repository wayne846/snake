#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "snake.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    //init screen
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 700, 500);
    scene->addRect(QRect(-TILE_WIDTH, -TILE_WIDTH, TILE_WIDTH*2+SCENE_WIDTH, TILE_WIDTH*2+SCENE_HEIGHT), QPen(WALL_COLOR), QBrush(WALL_COLOR));
    scene->addRect(QRect(0, 0, SCENE_WIDTH, +SCENE_HEIGHT), QPen(IN_BACKGROUND_COLOR), QBrush(IN_BACKGROUND_COLOR));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setBackgroundBrush(QBrush(OUT_BACKGROUND_COLOR));

    //init snake
    snake = new Snake(this);

    //init timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(100);

}

void MainWindow::update(){
    snake->move();
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_Up:
        case Qt::Key_W:
            snake->turnUp();
            break;
        case Qt::Key_Right:
        case Qt::Key_D:
            snake->turnRight();
            break;
        case Qt::Key_Down:
        case Qt::Key_S:
            snake->turnDown();
            break;
        case Qt::Key_Left:
        case Qt::Key_A:
            snake->turnLeft();
    }
}

MainWindow::~MainWindow(){
    delete ui;
}

