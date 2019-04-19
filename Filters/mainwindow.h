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

    void on_pushButton_Average_clicked();

    void on_pushButton_Copy_clicked();

    void on_pushButton_Blur_clicked();

    void on_pushButton_Roberts_clicked();

    void on_pushButton_Bin_clicked();

    void on_pushButton_Emboss_clicked();

    void on_pushButton_Open_clicked();

    void on_pushButton_Erosion_clicked();

    void on_pushButton_Close_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
