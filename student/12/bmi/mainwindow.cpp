#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->resultLabel->setText(QString(""));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_weightLineEdit_editingFinished()
{
    weight_ = ui->weightLineEdit->text().toDouble();
    //qDebug() << weight_;
}

void MainWindow::on_heightLineEdit_editingFinished()
{
    height_ = ui->heightLineEdit->text().toDouble();
    //qDebug() << height_;
}

void MainWindow::on_countButton_clicked()
{
    bmi_ = weight_ / ((height_ /100)* (height_/100));

    ui->resultLabel->setText(QString::number(bmi_));

    if(bmi_ < 18.5){
        info_ = QString("You are underweight.");
    }else if(bmi_ > 25){
        info_ = QString("You are overweight.");
    }else{
        info_ = QString("Your weight is normal.");
    }
    ui->infoTextBrowser->setText(info_);
    //qDebug() << bmi_;

}


