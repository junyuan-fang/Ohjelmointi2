#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <vector>
#include <map>
#include <memory>

using namespace std;

void MainWindow:: make_6_moving_buttons_disable(const bool& press){
    ui_->a_b->setDisabled(press);
    ui_->a_c->setDisabled(press);
    ui_->b_c->setDisabled(press);
    ui_->b_a->setDisabled(press);
    ui_->c_a->setDisabled(press);
    ui_->c_b->setDisabled(press);
}

int MainWindow:: get_disk_location_x(const int& width,const int& peg_center){
    return peg_center-width/2;
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
    ui_->spinBox->setMinimum(DISK_MIN);
    ui_->spinBox->setMaximum(DISK_MAX);

    ui_->reset->setDisabled(true);
    make_6_moving_buttons_disable(true);

    //pegs
    QBrush blackBrush(Qt::black);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    scene_->addRect(CENTER_OF_PEGS[A],BORDER_DOWN-PEG_HEIGHT,PEG_WIDTH,PEG_HEIGHT-1,blackPen,blackBrush);
    scene_->addRect(CENTER_OF_PEGS[B],BORDER_DOWN-PEG_HEIGHT,PEG_WIDTH,PEG_HEIGHT-1,blackPen,blackBrush);
    scene_->addRect(CENTER_OF_PEGS[C],BORDER_DOWN-PEG_HEIGHT,PEG_WIDTH,PEG_HEIGHT-1,blackPen,blackBrush);

    // Defining the color and outline of the disc
/*    QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2)*/

    // A non-singleshot timer fires every interval (1000) milliseconds,
    // which makes circle_move function to be called,
    // until the timer is stopped
//    timer_.setSingleShot(false);
//    connect(&timer_, &QTimer::timeout, this, &MainWindow::circle_move);

}



MainWindow::~MainWindow()
{
    for(Disk item: disks_vec_){
        delete item.disk;
    }
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


void MainWindow::on_start_clicked()
{
    disk_number_=ui_->spinBox->value();
    Disk new_disk;
    QBrush brush= COLOR[A];
    QPen pen(Qt::white);
    for(int i=0;i<disk_number_;++i){
        new_disk.peg_location=A;
        new_disk.width=DISK_WIDTH_MIN+i*DISK_WIDTH_ADD;
        new_disk.y=BORDER_DOWN-(disk_number_-i)*DISK_HEIGHT;
        new_disk.x=get_disk_location_x(new_disk.width,CENTER_OF_PEGS[A]);
        new_disk.disk=scene_->addRect(new_disk.x, new_disk.y, new_disk.width, DISK_HEIGHT, pen, brush);
        disks_vec_.push_back(new_disk);
    }
    disk_number_of_peg_[A]=disk_number_;
    make_6_moving_buttons_disable(false);

    
}

//make a helping function that can move the disks,
//but still need another function for checking the lefality of moving
//this function always move the smallest one of the peg
void MainWindow::move_disk(const Peg &from, const Peg &to){
    int top_index=0;
    bool find=false;
    //get the top_index, and check if any disks on the peg
    for(unsigned int x=0; x<disks_vec_.size();++x){
        if(disks_vec_.at(x).peg_location==from){
            top_index=x;
            find=true;
            break;
        }
    }
    //if there is a disk on the target get, then we can start moving
    if(find){
        unsigned int i = 0;
        do{
            // if the disk if on the peg, and it is the smallest one
            if(disks_vec_.at(i).peg_location==from &&
                disks_vec_.at(i).x>disks_vec_.at(top_index).x){
                top_index=i;
            }
            ++i;
        }while(i<disks_vec_.size());
        //disk's x value changes by peg's location,
        //y value changes by disk's number
        //delta_y= the placewill be(y)-right now(y)
        int delta_x=(to-from)*DISTANCE_PEG;
        int delta_y= (BORDER_DOWN-(disk_number_of_peg_[to]+1)*DISK_HEIGHT)-disks_vec_.at(top_index).y;
        disks_vec_.at(top_index).x+=delta_x;
        disks_vec_.at(top_index).y+=delta_y;
        //moving
        disks_vec_.at(top_index).disk->moveBy(delta_x, delta_y);
        disk_number_of_peg_[from]--;
        disk_number_of_peg_[to]++;
        disks_vec_.at(top_index).peg_location=to;
    }

}

void MainWindow::on_reset_clicked()
{

}

void MainWindow::on_a_b_clicked()
{
    move_disk(A,B);
}

void MainWindow::on_b_c_clicked()
{
    move_disk(B,C);
}

void MainWindow::on_c_a_clicked()
{
    move_disk(C,A);
}

void MainWindow::on_a_c_clicked()
{
    move_disk(A,C);
}

void MainWindow::on_b_a_clicked()
{
    move_disk(B,A);
}

void MainWindow::on_c_b_clicked()
{
    move_disk(C,B);
}
