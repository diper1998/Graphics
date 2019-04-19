#include <QGLWidget>
#include <QtOpenGL>
#pragma comment(lib, "opengl32.lib")

class MainScene : public QGLWidget
{
   protected:
    QPoint pressPosition;
    int xAxisRotation, yAxisRotation;

      void initializeGL();
      void resizeGL(int w, int h);
      void paintGL();
      void mousePressEvent(QMouseEvent *event);
      void mouseMoveEvent(QMouseEvent *event);

   public:

};
