#include "mainwindow.h"
#include <QApplication>
#include "mainscene.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    MainScene scene;
    scene.resize(600, 600);
    scene.show();

    return a.exec();
}
