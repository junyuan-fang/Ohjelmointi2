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

    void on_a_b_clicked();
    
    void on_b_c_clicked();
    
    void on_c_a_clicked();
    
    void on_a_c_clicked();
    
    void on_b_a_clicked();
    
    void on_c_b_clicked();
    

    void on_ok_clicked();

private:
    Ui::MainWindow *ui_;

    QGraphicsScene* scene_;          // a surface for

    QTimer timer_;          // for continuous moving

    // Scene
    const int BORDER_DOWN = 260;
    const int BORDER_RIGHT = 680;

    enum Peg{A,B,C};


    //pegs x coordination
    const int DISTANCE_PEG=BORDER_RIGHT/4;
    const vector<int>  CENTER_OF_PEGS={
             DISTANCE_PEG,
            DISTANCE_PEG*2,
            DISTANCE_PEG*3};

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
        Peg peg_location;
        QGraphicsRectItem* disk;
    };

    //disks
    vector<Disk> disks_vec_;

    //which is setted by user
    int disk_number_;

    //number of disks which on the peg
    vector<int> disk_number_of_peg_={0,0,0};



    int get_disk_location_x(const int& width,const int& peg_center)const;
    void make_6_moving_buttons_disable(const bool& press);
    void move_disk(const Peg& from , const Peg& to);
    bool is_leagal_from_to(const Peg& from , const Peg& to)const;
    void update_buttons();
    int get_smallest_disk_index_of_peg(const Peg& peg, int top_index)const;
    bool is_disk_on_peg(const Peg& peg, int& first_index)const;
    void remove_all_disks();



};


#endif // MAINWINDOW_HH
