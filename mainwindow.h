#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>

class Snake;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);

        const QColor WALL_COLOR = QColor(90,136,62);
        const QColor OUT_BACKGROUND_COLOR = WALL_COLOR;//QColor(75,117,50);
        const QColor IN_BACKGROUND_COLOR = QColor(171,214,93);
        const QColor SNAKE_COLOR = QColor(70,114,224);
        const QColor LINE_COLOR = QColor(50, 50, 50);
        const QColor APPLE_COLOR = QColor(232,73,44);
        const int TILE_WIDTH = 25;
        const int SCENE_WIDTH_TILE_NUM = 28;
        const int SCENE_HEIGHT_TILE_NUM = 20;
        const int SCENE_WIDTH = TILE_WIDTH * SCENE_WIDTH_TILE_NUM;
        const int SCENE_HEIGHT = TILE_WIDTH * SCENE_HEIGHT_TILE_NUM;

        QGraphicsScene *scene;
        QGraphicsTextItem *text_score;

        ~MainWindow();

    protected:
        void keyPressEvent(QKeyEvent *);

    private slots:
        void update();

        void on_actionrestart_triggered();

    private:
        Ui::MainWindow *ui;
        Snake *snake;
        QTimer *timer;

        bool isDead;
        QGraphicsTextItem *text_died;
};
#endif // MAINWINDOW_H
