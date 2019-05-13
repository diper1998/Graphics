#include "widget.h"
#include <QApplication>
#include <QGLWidget>
#include <QtOpenGL>
#pragma comment(lib, "opengl32.lib")


float r_x = 0, r_y = 290.0, r_w = 40, r_h = 8.0;



class MainScene : public QGLWidget
{
   protected:
    QPoint pressPosition;
    int xAxisRotation, yAxisRotation;

      void initializeGL();
      void resizeGL(int w, int h){
          glMatrixMode(GL_PROJECTION);
          glViewport(0, 0, w, h);
      }
      void paintGL();
      void mousePressEvent(QMouseEvent *event);
      void mouseMoveEvent(QMouseEvent *event);

   public:

};

class Brick {
    public:
    bool active;
    short row, col, hit;
    float w, h;
    Brick(short r_, short c_, float w_, float h_, short hit_):
        row(r_), col(c_), hit(hit_), w(w_), h(h_), active(false){}
    Brick():row(), col(), w(20), h(20), hit(1), active(false){}
};


Brick brick[10][15];



class Ball {
    public:
        float x, y, dx, dy, r;
        bool active;
        Ball(float y_, float r_):x(), y(y_), r(r_), dx(), dy(), active(false){}

        void move(){
            x+=dx;
            y+=dy;
            if(x-r<=0){
                x = r;
                dx*=-1;
            } else if (y - r <= 0) {
                y = r;
                dy*=-1;
            } else if(x+r>=300){
                x= 300-r;
                dx*=-1;
            } else if(y+r>=r_y && y+r<=r_y+r_h && x>r_x && x<r_x+r_w){
                dy*=-1;
            } else if(y>300)
                active = false;
        }
};

Ball ball(r_y, 5);


bool isCollision(Ball &b, Brick &br){

    float x=b.x, y=b.y, r=b.r, c=br.col, w=br.w, row=br.row, h=br.h;
    if(br.active)
    {
    if(abs(x-c*w-w/2-2)<=r+w/2 && abs(y-row*h-h/2-2)<=r+h/2)
    {
    if(sqrt((c*w+w/2-x)*(c*w+w/2-x) + (row*h+h/2-y)*(row*h+h/2-y))
    - (w/2-1)*sqrt(2.0) - r > r*(sqrt(2.0)-1))
    return 0;
    else
    return 1;
    }
    }
    return 0;
}

void MainScene::initializeGL()
{
 glClearColor(1.0, 1.0, 1.0, 0.0);
 glMatrixMode(GL_PROJECTION); //создали матрицу
 glOrtho(0, 300, 300, 0, 1, 0); // задали сетку x[0..300] и тд

}




void MainScene::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  //  glRotatef(yAxisRotation, 0, 1 , 0);
  //  glRotatef(xAxisRotation, 1, 0 , 0);
    glColor3f(0.517647059, 0.796078431, 0.85882352941);
    glRectf(r_x, r_y, r_x+r_w, r_y+r_h);

    glColor3f(0.5725490196, 0.454901960, 0.28627450980 );
    glBegin(GL_POLYGON);
    for(float i = 0; i < 2*M_PI; i+=M_PI/4){
        glVertex2d(ball.x+ball.r*sin(i), ball.y + ball.r*cos(i));
    }
    glEnd();

    glColor3f(0.8588235294, 0.5019607843137, 0.0);
    glBegin(GL_QUADS);
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 15; j++){
            Brick &b = brick[i][j];
            if(b.active){
            glVertex2f(b.col*b.w, b.row*b.h+1);
            glVertex2f(b.col*b.w+b.w-1, b.row*b.h+1);
            glVertex2f(b.col*b.w+b.w-1, b.row*b.h+b.h-1);
            glVertex2f(b.col*b.w+1, b.row*b.h + b.h-1);
            }

        }
    }
    glEnd();

}

void MainScene::mousePressEvent(QMouseEvent *event){
    pressPosition =  event->pos();
    if(event->buttons() & Qt::LeftButton && !ball.active){
        ball.active = true;
        ball.dx = 2;
        ball.dy = -2;
    }
}


void MainScene::mouseMoveEvent(QMouseEvent *event){

    //r_y = (GLfloat)event->y();
    r_x = (GLfloat)event->x() - r_w/2;

    if(!ball.active){
    ball.x = r_x+r_w/2;
    ball.y = r_y - ball.r;
    } else {
    ball.move();

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 15; j++){
            Brick &b = brick[i][j];
            if(isCollision(ball, b)){
                if(abs(ball.x-b.col*b.w-b.w/2) < abs(ball.y-b.row*b.h-b.h/2))
                {ball.dy*=-1;}
                else if(abs(ball.x-b.col*b.w-b.w/2) > abs(ball.y-b.row*b.h-b.h/2))
                {ball.dx*=-1;}
                else
                {
                if(ball.dx>0)
                {if(ball.x < b.col*b.w+1) ball.dx*=-1;}
                else if(ball.x > (b.col+1)*b.w-1) ball.dx*=-1;
                if(ball.dy>0)
                {if(ball.y < b.row*b.h+1) ball.dy*=-1;}
                else if(ball.y > (b.row+1)*b.h-1) ball.dy*=-1;
                }
                if(--b.hit==0)
                {
                b.active=false;
                }
                goto o;
            }
        }
    }

    }
o:        pressPosition = event->pos();

     updateGL();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
   // w.show();


    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 15; j++){
            brick[i][j].active = true;
            brick[i][j].col = j;
            brick[i][j].row = i;
        }
    }
    MainScene scene;
    scene.resize(300, 300);
    scene.show();


    return a.exec();
}
