#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsRectItem>

void MainWindow:: make_6_moving_buttons_disable(const bool& press){
    ui_->a_b->setDisabled(press);
    ui_->a_c->setDisabled(press);
    ui_->b_c->setDisabled(press);
    ui_->b_a->setDisabled(press);
    ui_->c_a->setDisabled(press);
    ui_->c_b->setDisabled(press);

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);

    // We need a graphics scene in which to draw a circle
    scene_ = new QGraphicsScene(this);

    // The graphicsView object is placed on the window
    // at the following coordinates:
    int left_margin = 10; // x coordinate
    int top_margin = 270; // y coordinate
    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui_->graphicsView->setGeometry(left_margin, top_margin,
                                   BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui_->graphicsView->setScene(scene_);

    // The width of the scene_ is BORDER_RIGHT decreased by 1 and
    // the height of it is BORDER_DOWN decreased by 1,
    // because the peg is considered to be inside the sceneRect,
    // if its upper left corner is inside the sceneRect.
    scene_->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);


    //set defaults
    ui_->spinBox->setMinimum(1);
    ui_->reset->setDisabled(true);
    make_6_moving_buttons_disable(true);

    QBrush blackBrush(Qt::black);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    scene_->addRect(LEFT_PEG_CENTER,BORDER_DOWN-PEG_HEIGHT,PEG_WIDTH,PEG_HEIGHT-1,blackPen,blackBrush);
    scene_->addRect(MIDDLE_PEG_CENTER,BORDER_DOWN-PEG_HEIGHT,PEG_WIDTH,PEG_HEIGHT-1,blackPen,blackBrush);
    scene_->addRect(RIGHT_PEG_CENTER,BORDER_DOWN-PEG_HEIGHT,PEG_WIDTH,PEG_HEIGHT-1,blackPen,blackBrush);







    // Defining the color and outline of the disc
/*    QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2)*/



    //circle_ = scene_->addEllipse(0, 0, STEP, STEP, blackPen, redBrush);


    // A non-singleshot timer fires every interval (1000) milliseconds,
    // which makes circle_move function to be called,
    // until the timer is stopped
//    timer_.setSingleShot(false);
//    connect(&timer_, &QTimer::timeout, this, &MainWindow::circle_move);

}



MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    // changing the color of the circle between red and blue
    if(event->key() == Qt::Key_C) {
//        if(circle_->brush().color() == Qt::red) {
//            circle_->setBrush(QBrush(Qt::blue));
//        } else {
//            circle_->setBrush(QBrush(Qt::red));
//        }
//        ui_->statusLabel->setText("Color");
//        return;
    }

    // moving the circle to south (down) by STEP
    if(event->key() == Qt::Key_S) {
//        if(scene_->sceneRect().contains(circle_->x(), circle_->y() + STEP)) {
//            circle_->moveBy(0, STEP);
//            ui_->statusLabel->setText("South");
//        }
//        update_move_button();
//        return;
    }
}


