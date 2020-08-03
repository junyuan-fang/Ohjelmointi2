#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <string>
#include <QDebug>

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
    void on_weightLineEdit_editingFinished();

    void on_heightLineEdit_editingFinished();

    void on_countButton_clicked();


private:
    Ui::MainWindow *ui;
    double weight_;
    double height_;
    double bmi_;
    QString info_;
};

#endif // MAINWINDOW_HH
