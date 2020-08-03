#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPalette pal = palette();

    // set black background
    pal.setColor(QPalette::Background, Qt::green);

    ui->lcdNumberSec->setAutoFillBackground(true);
    ui->lcdNumberMin->setAutoFillBackground(true);
    ui->lcdNumberSec->setPalette(pal);
    ui->lcdNumberMin->setPalette(pal);
    ui->lcdNumberMin->show();
    ui->lcdNumberSec->show();
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    

}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::on_startButton_clicked()
{
    // every 1000 interval, emit one signal
    timer->start(1000);

}

void MainWindow::showTime()
{
    second_ = second_ + 1;
    if (second_ == 60){
        minute_ = minute_ + 1;
        second_ = 0;
    }
    ui->lcdNumberSec->display(second_);
    ui->lcdNumberMin->display(minute_);

}

void MainWindow::on_stopButton_clicked()
{
    timer->stop();
}

void MainWindow::on_resetButton_clicked()
{
    timer->stop();
    second_ = 0;
    minute_ = 0;

    ui->lcdNumberSec->display(second_);
    ui->lcdNumberMin->display(minute_);

}
