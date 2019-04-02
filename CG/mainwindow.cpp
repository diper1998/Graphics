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


    img.load(fileName);

    ui->label_Picture->setPixmap(QPixmap::fromImage(img));

}

void MainWindow::on_pushButton_Average_clicked()
{

   QRgb** matrix = new QRgb*[img.width()];

   for(int i = 0; i < img.width(); i++){
   matrix[i] = new QRgb[img.height()];
   }

    for(int x = 0; x < img.width(); x++){
        for(int y = 0; y < img.height(); y++){
            matrix[x][y] = img.pixel(x,y);
        }
    }


    double red = 0;
    double green = 0;
    double blue = 0;
    QRgb res = 0;

    for(int x = 0; x < img.width(); x++){
        for(int y = 0; y < img.height(); y++){
            red = (qRed(matrix[x][y])+qBlue(matrix[x][y])+qGreen(matrix[x][y]))/3;
            blue = (qRed(matrix[x][y])+qBlue(matrix[x][y])+qGreen(matrix[x][y]))/3;
            green = (qRed(matrix[x][y])+qBlue(matrix[x][y])+qGreen(matrix[x][y]))/3;

            res = qRgb(red, green, blue);

            copy.setPixel(x,y,res);
        }
    }

   copy.save(copyName);

   ui->label_Copy->setPixmap(QPixmap::fromImage(copy));

}


void MainWindow::on_pushButton_Copy_clicked()
{

    copyName = QFileDialog::getOpenFileName(this, QString("Открыть файл"), QString("./folder"), QString("JPG (*.jpg)"));

    copy.load(copyName);

    ui->label_Copy->setPixmap(QPixmap::fromImage(copy));


}

void MainWindow::on_pushButton_Blur_clicked()
{
    QRgb** matrix = new QRgb*[img.width()];

    for(int i = 0; i < img.width(); i++){
    matrix[i] = new QRgb[img.height()];
    }

     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){
             matrix[x][y] = img.pixel(x,y);
         }
     }


     double red = 0;
     double green = 0;
     double blue = 0;
     QRgb res = 0;
     int h = ui->lineEdit_h->text().toInt();
     int r = 0;
     int g = 0;
     int b = 0;


     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){
             r = 1;
             g = 1;
             b = 1;


             red = qRed(matrix[x][y]);
             green = qGreen(matrix[x][y]);
             blue = qBlue(matrix[x][y]);

             for(int i = 0; i < h; i++){
                 for(int j = 0; j < h; j++){

                     if((y+j)<img.height()&&(x-i)>=0){
                     red += qRed(matrix[x-i][y+j]);
                     r++;
                     }
                     if((y-j)>=0 &&(x+i)<img.width()){
                     red += qRed(matrix[x+i][y-j]);
                     r++;
                     }
                     if((y-j)>=0 &&(x-i)>=0){
                     red += qRed(matrix[x-i][y-j]);
                     r++;
                     }
                     if((y-j)>=0 &&(x+i)<img.width()){
                     red += qRed(matrix[x+i][y-j]);
                     r++;
                     }

                     //G
                     if((y+j)<img.height()&&(x-i)>=0){
                     green += qGreen(matrix[x-i][y+j]);
                     g++;
                     }
                     if((y+j)<img.height()&&(x-i)>=0){
                     green += qGreen(matrix[x-i][y+j]);
                     g++;
                     }
                     if((y+j)<img.height()&&(x+i)<img.width()){
                     green+= qGreen(matrix[x+i][y+j]);
                     g++;
                     }
                     if((y-j)>=0 &&(x-i)>=0){
                     green += qGreen(matrix[x-i][y-j]);
                     g++;
                     }
                     if((y-j)>=0 &&(x+i)<img.width()){
                     green += qGreen(matrix[x+i][y-j]);
                     g++;
                     }
                    //B
                     if((y+j)<img.height()&&(x-i)>=0){
                     blue += qBlue(matrix[x-i][y+j]);
                     b++;
                     }
                     if((y+j)<img.height()&&(x-i)>=0){
                     blue += qBlue(matrix[x-i][y+j]);
                     b++;
                     }
                     if((y+j)<img.height()&&(x+i)<img.width()){
                     blue+= qBlue(matrix[x+i][y+j]);
                     b++;
                     }
                     if((y-j)>=0 &&(x-i)>=0){
                     blue += qBlue(matrix[x-i][y-j]);
                     b++;
                     }
                     if((y-j)>=0 &&(x+i)<img.width()){
                     blue += qBlue(matrix[x+i][y-j]);
                     b++;
                     }

                 }


             }

             red/=r;
             blue/=b;
             green/=g;

             res = qRgb(red, green, blue);

             copy.setPixel(x,y,res);
         }
     }

    copy.save(copyName);

    ui->label_Copy->setPixmap(QPixmap::fromImage(copy));

}

void MainWindow::on_pushButton_Roberts_clicked()
{



    QRgb** matrix = new QRgb*[img.width()];

    for(int i = 0; i < img.width(); i++){
    matrix[i] = new QRgb[img.height()];
    }

     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){
             matrix[x][y] = img.pixel(x,y);
         }
     }





     double** red = new double*[img.width()];
     double** green = new double*[img.width()];
     double** blue = new double*[img.width()];

     double** redX = new double*[img.width()];
     double** greenX = new double*[img.width()];
     double** blueX = new double*[img.width()];

     double** redY = new double*[img.width()];
     double** greenY = new double*[img.width()];
     double** blueY = new double*[img.width()];


     double** redRes = new double*[img.width()];
     double** greenRes = new double*[img.width()];
     double** blueRes = new double*[img.width()];

     for(int i = 0; i < img.width(); i++){
     red[i] = new double[img.height()];
     green[i] = new double[img.height()];
     blue[i] = new double[img.height()];

     redX[i] = new double[img.height()];
     greenX[i] = new double[img.height()];
     blueX[i] = new double[img.height()];

     redY[i] = new double[img.height()];
     greenY[i] = new double[img.height()];
     blueY[i] = new double[img.height()];

     redRes[i] = new double[img.height()];
     greenRes[i] = new double[img.height()];
     blueRes[i] = new double[img.height()];

     }


     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){
             red[x][y] = qRed(matrix[x][y]);
             blue[x][y] = qBlue(matrix[x][y]);
             green[x][y] = qGreen(matrix[x][y]);

             redX[x][y]   = 0;
             blueX[x][y]  = 0;
             greenX[x][y] = 0;

             redY[x][y]   = 0;
             blueY[x][y]  = 0;
             greenY[x][y] = 0;

             redRes[x][y]   = 0;
             blueRes[x][y]  = 0;
             greenRes[x][y] = 0;
     }

     }



     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){
             if((x+1) < img.width() && (y+1) < img.width()){
             redX[x][y] = red[x][y]-red[x+1][y+1];
             blueX[x][y] = blue[x][y]-blue[x+1][y+1];
             greenX[x][y] = green[x][y]-green[x+1][y+1];
             } else {
                 redX[x][y] =   0;
                 blueX[x][y] =  0;
                 greenX[x][y] = 0;
             }

             if((x+1) < img.width() && (y+1) < img.width()){
             redY[x][y] = red[x+1][y]-red[x][y+1];
             blueY[x][y] = blue[x+1][y]-blue[x][y+1];
             greenY[x][y] = green[x+1][y]-green[x][y+1];
             } else {
                 redY[x][y] =   0;
                 blueY[x][y] =  0;
                 greenY[x][y] = 0;
             }



             redRes[x][y] = pow(redX[x][y]*redX[x][y] + redY[x][y]*redY[x][y], 0.5);
             blueRes[x][y] = pow(blueX[x][y]*blueX[x][y] + blueY[x][y]*blueY[x][y], 0.5);
             greenRes[x][y] = pow(greenX[x][y]*greenX[x][y] + greenY[x][y]*greenY[x][y], 0.5);

}
}





     double redPix = 0;
     double bluePix = 0;
     double greenPix = 0;
     QRgb res;

     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){
             redPix = redRes[x][y];
             bluePix = blueRes[x][y];
             greenPix = greenRes[x][y];

             res = qRgb(redPix, greenPix, bluePix);

             copy.setPixel(x,y,res);

}
}
     copy.save(copyName);

     ui->label_Copy->setPixmap(QPixmap::fromImage(copy));


}

void mult(double** A, double** B, double** C, int size){

    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
        {
            C[i][j] = 0;
            for(int k = 0; k < size; k++)
                C[i][j] += A[i][k] * B[k][j];
        }

}


void multMatrix(double** A, int (& B)[3][3], double** C, int width, int hight){


    for(int x = 0; x < width; x++){
        for(int y = 0; y < hight; y++){
            for(int i = 0; i < 3; i++)
                for(int j = 0; j < 3; j++){
                    if((x+j<width) && (y+i<hight))
                    C[x][y] += A[x+j][y+i]*B[j][i];
                }
        }
    }



}


void SetMatrix(double**A, double**C, int row, int col){

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++)
        {
         C[i][j] = A[i+col][j+row];
        }
    }

}


void MainWindow::on_pushButton_Bin_clicked()
{
    int bin = 0;
    bin = ui->lineEdit_Bin->text().toInt();

    QRgb** matrix = new QRgb*[img.width()];

    for(int i = 0; i < img.width(); i++){
    matrix[i] = new QRgb[img.height()];
    }

     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){
             matrix[x][y] = img.pixel(x,y);
         }
     }


     double red = 0;
     double green = 0;
     double blue = 0;
     QRgb res = 0;

     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){
             red = (qRed(matrix[x][y])+qBlue(matrix[x][y])+qGreen(matrix[x][y]))/3;

             if(red < bin){
                 red = 0;
                 blue = 0;
                 green = 0;
             } else {
                 red = 255;
                 blue = 255;
                 green = 255;
             }

             res = qRgb(red, green, blue);

             copy.setPixel(x,y,res);
         }
}
     copy.save(copyName);

     ui->label_Copy->setPixmap(QPixmap::fromImage(copy));
}

void MainWindow::on_pushButton_Emboss_clicked()
{
    QRgb** matrix = new QRgb*[img.width()];

    for(int i = 0; i < img.width(); i++){
    matrix[i] = new QRgb[img.height()];
    }

     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){
             matrix[x][y] = img.pixel(x,y);
         }
     }


     double** red = new double*[img.width()];
     double** green = new double*[img.width()];
     double** blue = new double*[img.width()];



     double** redRes = new double*[img.width()];
     double** greenRes = new double*[img.width()];
     double** blueRes = new double*[img.width()];

     for(int i = 0; i < img.width(); i++){
     red[i] = new double[img.height()];
     green[i] = new double[img.height()];
     blue[i] = new double[img.height()];


     redRes[i] = new double[img.height()];
     greenRes[i] = new double[img.height()];
     blueRes[i] = new double[img.height()];

     }


     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){
             red[x][y] = qRed(matrix[x][y]);
             blue[x][y] = qBlue(matrix[x][y]);
             green[x][y] = qGreen(matrix[x][y]);

             redRes[x][y]   = 0;
             blueRes[x][y]  = 0;
             greenRes[x][y] = 0;
     }

     }




 int redX[3][3] = {{-1, -1, 0},
                     {-1, 0, 1},
                     {0, 1, 1}};

 int blueX[3][3] = {{-1, -1, 0},
                     {-1, 0, 1},
                     {0, 1, 1}};

 int greenX[3][3] = {{-1, -1, 0},
                     {-1, 0, 1},
                     {0, 1, 1}};



     multMatrix(red, redX, redRes, img.width(), img.height());
     multMatrix(blue, blueX, blueRes, img.width(), img.height());
     multMatrix(green, greenX, greenRes, img.width(), img.height());




     double redPix = 0;
     double bluePix = 0;
     double greenPix = 0;
     QRgb res;

     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){
             redPix = redRes[x][y];
             bluePix = blueRes[x][y];
             greenPix = greenRes[x][y];

             res = qRgb(redPix, greenPix, bluePix);

             copy.setPixel(x,y,res);

}
}
     copy.save(copyName);

     ui->label_Copy->setPixmap(QPixmap::fromImage(copy));

}

void Erosion(double** A, double** C, int width, int height){


    //int k =255;
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            if(A[x][y] == 0){

                C[x][y] = A[x][y];

                if(y+1 < height){
                C[x][y+1] = 0;

                }
                if(y-1 > 0){
                C[x][y-1] = 0;

                }
                if(x+1 < width){
                C[x+1][y] = 0;

                }
                if(x-1 > 0) {
                C[x-1][y] = 0;

                }

                if(x-1 > 0 && y-1> 0) {
                C[x-1][y-1] = 0;
}

                if(x-1 > 0 && y+1 < height)
                C[x-1][y+1] = 0;

                if(x+1 < width && y+1 < height)
                C[x+1][y+1] = 0;

                if(x+1 < width && y-1 > 0)
                C[x+1][y-1] = 0;



                }


            else{
                C[x][y] = A[x][y];
            }
        }
    }


}



void Rilation(double** A, double** C, int width, int height){


    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            if(A[x][y] == 255){

                C[x][y] = A[x][y];

                if(y+1 < height){
                C[x][y+1] = 255;

                }
                if(y-1 > 0){
                C[x][y-1] = 255;

                }
                if(x+1 < width){
                C[x+1][y] = 255;

                }
                if(x-1 > 0) {
                C[x-1][y] = 255;

                }


                if(x-1 > 0 && y-1> 0) {
                C[x-1][y-1] = 255;
}

                if(x-1 > 0 && y+1 < height)
                C[x-1][y+1] = 255;

                if(x+1 < width && y+1 < height)
                C[x+1][y+1] = 255;

                if(x+1 < width && y-1 > 0)
                C[x+1][y-1] = 255;



            }else{
                C[x][y] = A[x][y];
            }

            }
        }
    }






void MainWindow::on_pushButton_Open_clicked()
{
    QRgb** matrix = new QRgb*[img.width()];

    for(int i = 0; i < img.width(); i++){
    matrix[i] = new QRgb[img.height()];
    }

     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){
             matrix[x][y] = img.pixel(x,y);
         }
     }


     double** red = new double*[img.width()];
     double** green = new double*[img.width()];
     double** blue = new double*[img.width()];



     double** redRes = new double*[img.width()];
     double** greenRes = new double*[img.width()];
     double** blueRes = new double*[img.width()];

     double** redY = new double*[img.width()];
     double** greenY = new double*[img.width()];
     double** blueY = new double*[img.width()];


     for(int i = 0; i < img.width(); i++){
     red[i] = new double[img.height()];
     green[i] = new double[img.height()];
     blue[i] = new double[img.height()];


     redRes[i] = new double[img.height()];
     greenRes[i] = new double[img.height()];
     blueRes[i] = new double[img.height()];

     redY[i] = new double[img.height()];
     greenY[i] = new double[img.height()];
     blueY[i] = new double[img.height()];

     }


     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){
             red[x][y] = qRed(matrix[x][y]);
             blue[x][y] = qBlue(matrix[x][y]);
             green[x][y] = qGreen(matrix[x][y]);

             redRes[x][y]   = 0;
             blueRes[x][y]  = 0;
             greenRes[x][y] = 0;

             redY[x][y]   = 0;
             blueY[x][y]  = 0;
             greenY[x][y] = 0;
     }

     }




     Erosion(red, redY, img.width(), img.height());
     Erosion(blue, blueY, img.width(), img.height());
     Erosion(green, greenY, img.width(), img.height());

     Rilation(redY, redRes, img.width(), img.height());
     Rilation(blueY, blueRes, img.width(), img.height());
     Rilation(greenY, greenRes, img.width(), img.height());



     double redPix = 0;
     double bluePix = 0;
     double greenPix = 0;
     QRgb res;

     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){
             redPix = redRes[x][y];
             bluePix = blueRes[x][y];
             greenPix = greenRes[x][y];

             res = qRgb(redPix, greenPix, bluePix);

             copy.setPixel(x,y,res);

}
}
     copy.save(copyName);

     ui->label_Copy->setPixmap(QPixmap::fromImage(copy));


}


void MainWindow::on_pushButton_Erosion_clicked()
{
    QRgb** matrix = new QRgb*[img.width()];

    for(int i = 0; i < img.width(); i++){
    matrix[i] = new QRgb[img.height()];
    }

     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){
             matrix[x][y] = img.pixel(x,y);
         }
     }


     double** red = new double*[img.width()];
     double** green = new double*[img.width()];
     double** blue = new double*[img.width()];


     double** redY = new double*[img.width()];
     double** greenY = new double*[img.width()];
     double** blueY = new double*[img.width()];


     for(int i = 0; i < img.width(); i++){
     red[i] = new double[img.height()];
     green[i] = new double[img.height()];
     blue[i] = new double[img.height()];




     redY[i] = new double[img.height()];
     greenY[i] = new double[img.height()];
     blueY[i] = new double[img.height()];

     }


     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){
             red[x][y] = qRed(matrix[x][y]);
             blue[x][y] = qBlue(matrix[x][y]);
             green[x][y] = qGreen(matrix[x][y]);



             redY[x][y]   = 0;
             blueY[x][y]  = 0;
             greenY[x][y] = 0;
     }

     }




     Erosion(red, redY, img.width(), img.height());
     Erosion(blue, blueY, img.width(), img.height());
     Erosion(green, greenY, img.width(), img.height());


     double redPix = 0;
     double bluePix = 0;
     double greenPix = 0;
     QRgb res;

     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){
             redPix = redY[x][y];
             bluePix = blueY[x][y];
             greenPix = greenY[x][y];

             res = qRgb(redPix, greenPix, bluePix);

             copy.setPixel(x,y,res);

}
}
     copy.save(copyName);

     ui->label_Copy->setPixmap(QPixmap::fromImage(copy));

}

void MainWindow::on_pushButton_Close_clicked()
{
    QRgb** matrix = new QRgb*[img.width()];

    for(int i = 0; i < img.width(); i++){
    matrix[i] = new QRgb[img.height()];
    }

     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){
             matrix[x][y] = img.pixel(x,y);
         }
     }


     double** red = new double*[img.width()];
     double** green = new double*[img.width()];
     double** blue = new double*[img.width()];



     double** redRes = new double*[img.width()];
     double** greenRes = new double*[img.width()];
     double** blueRes = new double*[img.width()];

     double** redY = new double*[img.width()];
     double** greenY = new double*[img.width()];
     double** blueY = new double*[img.width()];


     for(int i = 0; i < img.width(); i++){
     red[i] = new double[img.height()];
     green[i] = new double[img.height()];
     blue[i] = new double[img.height()];


     redRes[i] = new double[img.height()];
     greenRes[i] = new double[img.height()];
     blueRes[i] = new double[img.height()];

     redY[i] = new double[img.height()];
     greenY[i] = new double[img.height()];
     blueY[i] = new double[img.height()];

     }


     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){
             red[x][y] = qRed(matrix[x][y]);
             blue[x][y] = qBlue(matrix[x][y]);
             green[x][y] = qGreen(matrix[x][y]);

             redRes[x][y]   = 0;
             blueRes[x][y]  = 0;
             greenRes[x][y] = 0;

             redY[x][y]   = 0;
             blueY[x][y]  = 0;
             greenY[x][y] = 0;
     }

     }



     Rilation(red, redY, img.width(), img.height());
     Rilation(blue, blueY, img.width(), img.height());
     Rilation(green, greenY, img.width(), img.height());

     Erosion(redY, redRes, img.width(), img.height());
     Erosion(blueY, blueRes, img.width(), img.height());
     Erosion(greenY, greenRes, img.width(), img.height());





     double redPix = 0;
     double bluePix = 0;
     double greenPix = 0;
     QRgb res;

     for(int x = 0; x < img.width(); x++){
         for(int y = 0; y < img.height(); y++){
             redPix = redRes[x][y];
             bluePix = blueRes[x][y];
             greenPix = greenRes[x][y];

             res = qRgb(redPix, greenPix, bluePix);

             copy.setPixel(x,y,res);

}
}
     copy.save(copyName);

     ui->label_Copy->setPixmap(QPixmap::fromImage(copy));

}
