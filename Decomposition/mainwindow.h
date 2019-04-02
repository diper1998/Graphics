#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QImage img;
    QImage copy;
    QString fileName;
    QString copyName;

private slots:


    void on_pushButton_File_clicked();

    void on_pushButton_Start_clicked();
    void MainWindow::RGB(int r,  int g, int b);

    void on_pushButton_Copy_clicked();

    void MainWindow::YUV(int y,  int u, int v);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
