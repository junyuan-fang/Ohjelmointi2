#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <string>
#include <iostream>
#include <fstream>
//#include <QDebug>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_fileLineEdit_editingFinished();

    void on_keyLineEdit_editingFinished();

    void on_findPushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString file_name_ = "";
    QString word_name_ = "";

    QString find_file_and_word();

    string str_tolower(string s);

    bool compare_two_words(string word1, string word2);


};

#endif // MAINWINDOW_HH
