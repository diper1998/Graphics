#include "mainscene.h"


void MainScene::initializeGL()
{
 qglClearColor(Qt::black);
 glEnableClientState(GL_VERTEX_ARRAY);
 glEnableClientState(GL_COLOR_ARRAY);
 //glShadeModel(GL_FLAT);
 glEnable(GL_CULL_FACE);

}

void MainScene::resizeGL(int nWidth, int nHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 10, 0, 10, -10, 10);
    glViewport(0, 0, nWidth, nHeight);
}

void MainScene::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(yAxisRotation, 0, 1 , 0);
    glRotatef(xAxisRotation, 1, 0 , 0);



    GLfloat triangleVertexArray[4][3];
    GLfloat triangleColorArray[4][3];
    GLubyte triangleIndexArray[4][3];

    triangleVertexArray[0][0] = 4;
    triangleVertexArray[0][1] = 4;
    triangleVertexArray[0][2] = 0;


    triangleVertexArray[1][0] = 8;
    triangleVertexArray[1][1] = 4;
    triangleVertexArray[1][2] = 0;


    triangleVertexArray[2][0] = 8;
    triangleVertexArray[2][1] = 6;
    triangleVertexArray[2][2] = 0;

    triangleVertexArray[3][0] = 4;
    triangleVertexArray[3][1] = 4;
    triangleVertexArray[3][2] = 4;


    triangleColorArray[0][1] = 1;
    triangleColorArray[0][2] = 1;
    triangleColorArray[0][3] = 0;


    triangleColorArray[1][1] = 1;
    triangleColorArray[1][2] = 0;
    triangleColorArray[1][3] = 0;


    triangleColorArray[2][1] = 0;
    triangleColorArray[2][2] = 0;
    triangleColorArray[2][3] = 1;

    triangleColorArray[3][1] = 0;
    triangleColorArray[3][2] = 1;
    triangleColorArray[3][3] = 1;

    triangleIndexArray[0][0] = 0;
    triangleIndexArray[0][1] = 1;
    triangleIndexArray[0][2] = 2;

    triangleIndexArray[1][0] = 0;
    triangleIndexArray[1][1] = 2;
    triangleIndexArray[1][2] = 3;

    triangleIndexArray[2][0] = 3;
    triangleIndexArray[2][1] = 2;
    triangleIndexArray[2][2] = 1;


    triangleIndexArray[3][0] = 0;
    triangleIndexArray[3][1] = 3;
    triangleIndexArray[3][2] = 1;



    glVertexPointer(3, GL_FLOAT, 0, triangleVertexArray);
    glColorPointer(3, GL_FLOAT, 0, triangleColorArray);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, triangleIndexArray);






    /*
    glColor3f(255, 255, 255);

    glBegin(GL_TRIANGLES);

    glVertex2f(2, 2);
    glVertex2f(8,2);
    glVertex2f(8,8);

    glEnd();
    */
}

void MainScene::mousePressEvent(QMouseEvent *event){
    pressPosition =  event->pos();
}

void MainScene::mouseMoveEvent(QMouseEvent *event){

    yAxisRotation += (180 * ((GLfloat)event->y() - (GLfloat)pressPosition.y())) / (height());
    xAxisRotation += (180 * ((GLfloat)event->x() - (GLfloat)pressPosition.x())) / (width());

       pressPosition = event->pos();

       updateGL();
}

