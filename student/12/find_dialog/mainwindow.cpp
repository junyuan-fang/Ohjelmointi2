#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fileLineEdit_editingFinished()
{
    file_name_ = ui->fileLineEdit->text();
}

void MainWindow::on_keyLineEdit_editingFinished()
{
    word_name_ = ui->keyLineEdit->text();
}

void MainWindow::on_findPushButton_clicked()
{
    QString str = find_file_and_word();

    ui->textBrowser->setText(str);
    //qDebug() << ui->textBrowser->toPlainText();

}

QString MainWindow::find_file_and_word()
{
    QString str = "";
    ifstream file_input(file_name_.toStdString());
    if (not file_input){
        str.append("File not found");
        return str;

    }else{
        str.append("File found");
        if(not word_name_.isEmpty()){
            string word;
            while (file_input >> word){
                if (compare_two_words(word, word_name_.toStdString())){
                    str.clear();
                    str.append("Word found");
                    return str;
                }
            }
            str.clear();
            str.append("Word not found");

            file_input.close();
        }

    }
    return str;
}


string MainWindow::str_tolower(string s) {
    for_each(s.begin(), s.end(), [](char & c) {
        c = tolower(c);
    });
    return s;
}

bool MainWindow::compare_two_words(string word1, string word2)
{
    if(ui->matchCheckBox->isChecked()){
        return word1 == word2;
    }else{
        string new_word1 = str_tolower(word1);
        string new_word2 = str_tolower(word2);
        return new_word1 == new_word2;
    }

}
