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

int MainWindow:: get_disk_location_x(const int& width,const int& peg_center)const{
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

    ui_->start->setDisabled(true);
    make_6_moving_buttons_disable(true);

    //pegs
    QBrush blackBrush(Qt::black);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    scene_->addRect(CENTER_OF_PEGS[A],BORDER_DOWN-PEG_HEIGHT,PEG_WIDTH,PEG_HEIGHT-1,blackPen,blackBrush);
    scene_->addRect(CENTER_OF_PEGS[B],BORDER_DOWN-PEG_HEIGHT,PEG_WIDTH,PEG_HEIGHT-1,blackPen,blackBrush);
    scene_->addRect(CENTER_OF_PEGS[C],BORDER_DOWN-PEG_HEIGHT,PEG_WIDTH,PEG_HEIGHT-1,blackPen,blackBrush);



    // A non-singleshot timer fires every interval (1000) milliseconds,
    timer_=new QTimer(this);
    timer_->setSingleShot(false);
    connect(timer_, &QTimer::timeout, this, &MainWindow::update_time);

}

void MainWindow::update_time(){
    second_++;
    if(second_==60){
        second_=0;
        minute_++;
    }
    if(minute_==60){
        minute_=0;
        hour_++;
    }
    ui_->hour->display(hour_);
    ui_->minute->display(minute_);
    ui_->second->display(second_);

}

void MainWindow::remove_all_disks(){
    for(Disk i : disks_vec_){
        delete i.disk;
    }
    disks_vec_.clear();
    disk_number_of_peg_={0,0,0};
}

//check and tell the user that, he wins the game
void MainWindow::check_winning(){
    if(disk_number_of_peg_[B]==disk_number_ || disk_number_of_peg_[C]==disk_number_){
        ui_->congraduation->setText(QString("YOU WIN!"));
        make_6_moving_buttons_disable(true);
        timer_->stop();
        is_win=true;
        ui_->start->setDisabled(true);
    }

}

MainWindow::~MainWindow()
{
    for(Disk item: disks_vec_){
        delete item.disk;
    }
    delete timer_;
    delete ui_;

}

void MainWindow::keyPressEvent(QKeyEvent* event) {

    if(event->key() == Qt::Key_A||event->key() == Qt::Key_B||event->key() == Qt::Key_C) {
        keys_.push_back(Peg(event->key()-'A'));
        if(keys_.size()==2&&!is_win){//check if moving successes
            if(key_ever_moved==true){
                timer_->start(1000);
            }
            if(is_leagal_from_to(keys_.at(0),keys_.at(1))){
                move_disk(keys_.at(0),keys_.at(1));
                update_buttons();
                check_winning();

                key_ever_moved=true;

            }
            keys_.clear();
        }
    }
}



void MainWindow::on_start_clicked()
{
        update_buttons();
        timer_->start(1000);
    
}

//return bool value ture if there is a disk on the peg,
//and change first_index. Otherwise return false
bool MainWindow::is_disk_on_peg(const Peg &peg, int& first_index) const{
    bool find=false;
    //get the top_index, and check if any disks on the peg
    for(unsigned int x=0; x<disks_vec_.size();++x){
        if(disks_vec_.at(x).peg_location==peg){
            find=true;
            first_index=x;
            break;
        }
    }
    return find;
}

// go through the vec, and return the top_index of the peg
int MainWindow::get_smallest_disk_index_of_peg(const Peg &peg, int top_index) const{
    unsigned int i = 0;
    do{
        // if the disk if on the peg, and it is the smallest one
        if(disks_vec_.at(i).peg_location==peg &&
            disks_vec_.at(i).width<disks_vec_.at(top_index).width){
            top_index=i;
        }
        ++i;
    }while(i<disks_vec_.size());
    return top_index;
}


//make a helping function that can move the disks,
//but still need another function for checking the lefality of moving
//this function always move the smallest one of the peg
//append moving to history
void MainWindow::move_disk(const Peg &from, const Peg &to){
    int first_index=0;
    //Must have a disk on the target get, then we can start moving
    is_disk_on_peg(from,first_index);//just indicate the first_index to the right location
    int top_index=get_smallest_disk_index_of_peg(from, first_index);
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
    //set color
    disks_vec_.at(top_index).disk->setBrush(COLOR[to]);
    //updating the history;
    history_.append(PEG_CHAR[from]);
    history_.append("->");
    history_.append(PEG_CHAR[to]);
    history_.append("\n");

    ui_->history->setText(history_);

}

//return true: when smallest(from)< smalleset(to)
bool MainWindow::is_leagal_from_to(const Peg& from , const Peg& to)const{
    int first_index=0;// first index of the
    if(is_disk_on_peg(from,first_index)){
        if(disk_number_of_peg_.at(to)==0){
            return true;
        }
        int from_index=get_smallest_disk_index_of_peg(from, first_index);
        is_disk_on_peg(to,first_index);// now first_index is changed for destination peg
        int to_index=get_smallest_disk_index_of_peg(to, first_index);

        return disks_vec_.at(from_index).width<disks_vec_.at(to_index).width;
    }
    return false;
}


void MainWindow::update_buttons(){
    make_6_moving_buttons_disable(true);
    if(is_leagal_from_to(A,B)){
        ui_->a_b->setEnabled(true);
    }
    if(is_leagal_from_to(A,C)){
        ui_->a_c->setEnabled(true);
    }
    if(is_leagal_from_to(B,C)){
        ui_->b_c->setEnabled(true);
    }
    if(is_leagal_from_to(B,A)){
        ui_->b_a->setEnabled(true);
    }
    if(is_leagal_from_to(C,B)){
        ui_->c_b->setEnabled(true);
    }
    if(is_leagal_from_to(C,A)){
        ui_->c_a->setEnabled(true);
    }

}



void MainWindow::on_a_b_clicked()
{
    move_disk(A,B);
    update_buttons();
    check_winning();
}

void MainWindow::on_b_c_clicked()
{
    move_disk(B,C);
    update_buttons();
    check_winning();
}

void MainWindow::on_c_a_clicked()
{
    move_disk(C,A);
    update_buttons();
    check_winning();
}

void MainWindow::on_a_c_clicked()
{
    move_disk(A,C);
    update_buttons();
    check_winning();
}

void MainWindow::on_b_a_clicked()
{
    move_disk(B,A);
    update_buttons();
    check_winning();
}

void MainWindow::on_c_b_clicked()
{
    move_disk(C,B);
    update_buttons();
    check_winning();
}

void MainWindow::on_ok_clicked()
{
    is_win=false;
    ui_->congraduation->setText(QString(""));
    //start button is unlocked
    ui_->start->setDisabled(false);

    //reset disks
    remove_all_disks();
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
    //reset buttons
    make_6_moving_buttons_disable(true);
    //reset times
    second_=0;
    minute_=0;
    hour_=0;
    timer_->stop();
    ui_->hour->display(hour_);
    ui_->minute->display(minute_);
    ui_->second->display(second_);
    //reset history
    history_.clear();
    ui_->history->setText(history_);


}
