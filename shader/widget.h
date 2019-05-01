#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QMouseEvent>
struct VertexData{
    VertexData(){

    }
    VertexData(QVector3D p, QVector2D t, QVector3D n) :
        position(p), texCoord(t), normal(n){

    }

    QVector3D position;
    QVector2D texCoord;
    QVector3D normal;
};

#pragma comment(lib, "opengl32.lib")

class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();


    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


    void initShaders();
    void initCube(float width);

private:
    QMatrix4x4 projectionMatrix;
    QOpenGLShaderProgram program;
    QOpenGLTexture* texture;
    QOpenGLBuffer arrayBuffer;
    QOpenGLBuffer indexBuffer;
    QVector2D mousePosition;
    QQuaternion rotation;
};

#endif // WIDGET_H
