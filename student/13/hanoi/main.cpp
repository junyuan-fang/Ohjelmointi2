/* *
 * Program author ( Fill with your own info )
 * Name: Junyuan Fang
 * Student number: 292042
 * UserID: fqjufa ( Necessary due to gitlab folder naming. )
 * E-Mail: junyuan.fang@tuni.fi
 *
 * Notes:
 *
 * */
#include "mainwindow.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
