#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QTimer>
#include <vector>
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


private:
    Ui::MainWindow *ui_;

    QGraphicsScene* scene_;          // a surface for
    vector<QGraphicsRectItem*> disks_;   // drawing disks

    QTimer timer_;          // for continuous moving

    // Scene
    const int BORDER_DOWN = 260;
    const int BORDER_RIGHT = 680;

    //pegs x coordination
    const int LEFT_PEG_CENTER=BORDER_RIGHT/4;
    const int MIDDLE_PEG_CENTER=BORDER_RIGHT/2;
    const int RIGHT_PEG_CENTER=BORDER_RIGHT*3/4;

    //pegs hight
    const int PEG_HEIGHT=240;
    const int PEG_WIDTH=2;






    void make_6_moving_buttons_disable(const bool& press);


};


#endif // MAINWINDOW_HH
