#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QFileDialog"

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

void MainWindow::on_pushButton_File_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, QString("Открыть файл"), QString("./folder"), QString("JPG (*.jpg)"));

    copyName = fileName;

    img.load(fileName);

    ui->label_Picture->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::RGB(int r,  int g, int b){

    QRgb** matrix = new QRgb*[img.width()];

    for(int i = 0; i < img.width(); i++){
    matrix[i] = new QRgb[img.height()];
    }

     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){
             matrix[x][y] = img.pixel(x,y);
         }
     }


double red, blue, green, res;

     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){

             red = r*qRed(matrix[x][y]);
             blue = b*qBlue(matrix[x][y]);
             green = g*qGreen(matrix[x][y]);


             res = qRgb(red, green, blue);

             copy.setPixel(x,y,res);
         }
     }

    copy.save(copyName);

     if(r){
         ui->label_R->setPixmap(QPixmap::fromImage(copy));
     }

     if(g){
         ui->label_G->setPixmap(QPixmap::fromImage(copy));
     }

     if(b){
         ui->label_B->setPixmap(QPixmap::fromImage(copy));
     }
}


void MainWindow::YUV(int y,  int u, int v){

    QRgb** matrix = new QRgb*[img.width()];

    for(int i = 0; i < img.width(); i++){
    matrix[i] = new QRgb[img.height()];
    }

     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){
             matrix[x][y] = img.pixel(x,y);
         }
     }


double Y, U, V, res;

     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){

             Y = (0.299*qRed(matrix[x][y])+0.587*qGreen(matrix[x][y])+0.114*qBlue(matrix[x][y]));
             U = (0.492*(qBlue(matrix[x][y]) - Y));
             V = (0.877*(qRed(matrix[x][y])-Y));


             res = qRgb(y*Y, u*U, v*V);
              res = (y*Y, u*U, v*V);



             copy.setPixel(x,y,res);
         }
     }

    copy.save(copyName);

    if(y && u && v){
         ui->label_Picture->setPixmap(QPixmap::fromImage(copy));
    } else {

     if(y){
         ui->label_R->setPixmap(QPixmap::fromImage(copy));
     }

     if(u){
         ui->label_G->setPixmap(QPixmap::fromImage(copy));
     }

     if(v){
         ui->label_B->setPixmap(QPixmap::fromImage(copy));
     }


}


}

void MainWindow::on_pushButton_Start_clicked()
{

    if(ui->radioButton_RGB->isChecked()){
RGB(1, 0, 0);
RGB(0, 1, 0);
RGB(0, 0, 1);
    }

    if(ui->radioButton_YUV->isChecked()){
        YUV(1, 0, 0);
        YUV(0, 1, 0);
        YUV(0, 0, 1);
        YUV(1, 1, 1);

    }

}

void MainWindow::on_pushButton_Copy_clicked()
{
    copyName = QFileDialog::getOpenFileName(this, QString("Открыть файл"), QString("./folder"), QString("JPG (*.jpg)"));

    copy.load(copyName);

    ui->label_R->setPixmap(QPixmap::fromImage(copy));
    ui->label_G->setPixmap(QPixmap::fromImage(copy));
    ui->label_B->setPixmap(QPixmap::fromImage(copy));
}
