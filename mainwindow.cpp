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

    text_died = scene->addText("YOU DIED", QFont("Arial", 50));
    text_died->setPos(SCENE_WIDTH/2.0 - text_died->boundingRect().width()/2.0, SCENE_HEIGHT/2.0 - text_died->boundingRect().height()/2.0);
    text_died->hide();

    //init snake
    snake = new Snake(this);

    //init timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(130);

    //init other value
    isDead = false;
}

void MainWindow::update(){
    if(isDead){
        text_died->show();
        return;
    }
    if(!snake->move()){
        isDead = true;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(isDead) return;
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

