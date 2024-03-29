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

    //init text
    text_died = scene->addText("YOU DIED", QFont("Arial", 50));  //died text
    text_died->setZValue(1);
    text_died->setPos(SCENE_WIDTH/2.0 - text_died->boundingRect().width()/2.0, SCENE_HEIGHT/2.0 - text_died->boundingRect().height()/2.0);
    text_died->hide();
    scene->addEllipse(0, -TILE_WIDTH * 1.35, TILE_WIDTH, TILE_WIDTH, QPen(LINE_COLOR, 2.5), QBrush(APPLE_COLOR));
    text_score = scene->addText("0", QFont("Arial", 20));
    text_score->setPos(TILE_WIDTH * 1.35, -TILE_WIDTH * 1.55);

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


void MainWindow::on_actionrestart_triggered()
{
    delete(snake);
    snake = new Snake(this);
    text_died->hide();
    text_score->setPlainText("0");
    isDead = false;
}

