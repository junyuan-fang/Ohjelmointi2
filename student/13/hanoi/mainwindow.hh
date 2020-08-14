#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QTimer>
#include <vector>
#include <map>
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
    void keyPressEvent(QKeyEvent* event) override;

private slots:



    void on_start_clicked();

    void on_reset_clicked();

private:
    Ui::MainWindow *ui_;

    QGraphicsScene* scene_;          // a surface for

    QTimer timer_;          // for continuous moving

    // Scene
    const int BORDER_DOWN = 260;
    const int BORDER_RIGHT = 680;

    enum Peg{A,B,C};


    //pegs x coordination
    const vector<int>  CENTER_OF_PEGS={
             BORDER_RIGHT/4,
            BORDER_RIGHT/2,
            BORDER_RIGHT*3/4};

    //colors
    const vector<QBrush> COLOR{
                Qt::red,
                Qt::yellow,
                Qt::green
    };

    //pegs hight
    const int PEG_HEIGHT=240;
    const int PEG_WIDTH=2;
    const int DISK_HEIGHT=15;

    //which is calculated for fitting the scene.
    const int DISK_MAX=15;
    const int DISK_MIN=1;
    const int DISK_WIDTH_MIN=20;
    const int DISK_WIDTH_ADD=10;

    //disk
    struct Disk{
        int y;
        int x;
        int width;
        QGraphicsRectItem* disk;
    };

    //disks
    vector<Disk> disks_vec;

    //which is setted by user
    int disk_number_;



    int get_disk_location_x(const int& width,const int& peg_center);
    void make_6_moving_buttons_disable(const bool& press);


};


#endif // MAINWINDOW_HH
