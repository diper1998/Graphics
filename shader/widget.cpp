#include "widget.h"



Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent), texture(0), indexBuffer(QOpenGLBuffer::IndexBuffer)
{
}

Widget::~Widget()
{

}

void Widget::initializeGL()
{
    glClearColor(0, 0, 0, 1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initShaders();
    initCube(1.0);
}

void Widget::resizeGL(int w, int h)
{
    float aspect = w/(float)h;
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(45, aspect, 0.1, 10);
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 viewMatrix;
    viewMatrix.setToIdentity();
    viewMatrix.translate(0,0,-5);
    viewMatrix.rotate(rotation);

    texture->bind(0);

    program.bind();

    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();


    program.setUniformValue("u_projectionMatrix", projectionMatrix);
    program.setUniformValue("u_viewMatrix", viewMatrix);
    program.setUniformValue("u_modelMatrix", modelMatrix);
    program.setUniformValue("u_texture", 0);
    program.setUniformValue("u_lightPosition", QVector4D(0.0, 0.0, 0.0, 1.0));
    program.setUniformValue("u_lightPower", 5.0f);

   arrayBuffer.bind();

    int offset = 0;

    int vertLoc = program.attributeLocation("a_position");
    program.enableAttributeArray(vertLoc);
    program.setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3, sizeof (VertexData));

    offset+= sizeof(QVector3D);

    int texLoc = program.attributeLocation("a_texcoord");
    program.enableAttributeArray(texLoc);
    program.setAttributeBuffer(texLoc, GL_FLOAT, offset, 2, sizeof(VertexData));


    offset+= sizeof(QVector2D);

    int normLoc = program.attributeLocation("a_normal");
    program.enableAttributeArray(normLoc);
    program.setAttributeBuffer(normLoc, GL_FLOAT, offset, 3, sizeof(VertexData));

    indexBuffer.bind();

    glDrawElements(GL_TRIANGLES, indexBuffer.size(), GL_UNSIGNED_INT, 0);

}

void Widget::mousePressEvent(QMouseEvent *event)
{
    mousePosition = QVector2D(event->localPos());
    event->accept();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    QVector2D diff = QVector2D(event->localPos()) - mousePosition;
    mousePosition = QVector2D(event->localPos());

    float angle = diff.length()/2;

    QVector3D axis = QVector3D(diff.y(), diff.x(), 0);

    rotation = QQuaternion::fromAxisAndAngle(axis, angle)*rotation;

    update();

}

void Widget::initShaders()
{

    if(!program.addShaderFromSourceFile(QOpenGLShader::Vertex, "D:\\ITMM\\Graphics\\Shader\\shader\\vshader.vsh"))
            close();

    if(!program.addShaderFromSourceFile(QOpenGLShader::Fragment,"D:\\ITMM\\Graphics\\Shader\\shader\\fshader.fsh"))
        close();

    if(!program.link())
            close();
/*
    QString shsr("attribute highp vec4 a_position;"
                 "attribute highp vec2 a_texcoord;"
                 "attribute highp vec3 a_normal;"
                 "uniform highp mat4 u_projectionMatrix;"
                 "uniform highp mat4 u_viewMatrix;"
                 "uniform highp mat4 u_modelMatrix;"
                 "varying highp vec2 v_texcoord;"
                 "varying highp vec3 v_normal;"
                 "varying highp vec4 v_position;"
                 "void main(void)"
                 "{"
                 "mat4 mv_matrix = u_viewMatrix*u_modelMatrix;"

                    " gl_Position = u_projectionMatrix * mv_matrix*a_position;"
                     "v_texcoord = a_texcoord;"
                 "v_normal = normalize(vec3(mv_matrix*vec4(a_normal,0)));"
                 "v_position = mv_matrix*a_position;"

                 "}");

    QString shfr("uniform sampler2D u_texture;"
                 "uniform highp vec4 u_lightPosition;"
                 "uniform highp float u_lightPower;"
                 "varying highp vec2 v_texcoord;"
                 "varying highp vec3 v_normal;"
                 "varying highp vec4 v_position;"
               "                                                          "
               "  void main(void)                                         "
               "  {                                                       "
                 "vec4 resultColor = vec4(0, 0, 0, 0);"
                 "vec4 eyePosition = vec4(0, 0, 0, 1);"
                 "vec4 diffMatColor = texture2D(u_texture, v_texcoord);"
                 "vec3 eyeVect = normalize(v_position.xyz - eyePosition.xyz);"
                 "vec3 lightVect = normalize(v_position.xyz - u_lightPosition); "
                 "vec3 reflectLight = normalize(reflect(lightVect, v_normal)); "
                 "float len = length(v_position.xyz - eyePosition.xyz);"
                 "float specularFactor = 10;"
                 "float ambienFactor = 0.1;"
                 "vec4 diffColor = diffMatColor * u_lightPower * dot(v_normal, -lightVect) / (1 + 0.25 * pow(len, 2));"
                 "resultColor += diffColor;"
               "      gl_FragColor = resultColor;"
               "  }");


    program.addShaderFromSourceCode(QOpenGLShader::Vertex, shsr);
    program.addShaderFromSourceCode(QOpenGLShader::Fragment, shfr);
    program.link();
*/
}

void Widget::initCube(float width)
{
    float width_div_2 = width/2.0;
    QVector<VertexData> vertexes;
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(0, 1), QVector3D(0,0,1)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(0, 0), QVector3D(0,0,1)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(1, 1), QVector3D(0,0,1)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(1, 0), QVector3D(0,0,1)));

    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(0, 1), QVector3D(1,0,0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(0, 0), QVector3D(1,0,0)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(1, 1), QVector3D(1,0,0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(1, 0), QVector3D(1,0,0)));

    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(0, 1), QVector3D(0,1,0)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(0, 0), QVector3D(0,1,0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(1, 1), QVector3D(0,1,0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(1, 0), QVector3D(0,1,0)));

    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(0, 1), QVector3D(0,0,-1)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(0, 0), QVector3D(0,0,-1)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(1, 1), QVector3D(0,0,-1)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(1, 0), QVector3D(0,0,-1)));

    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(0, 1), QVector3D(-1,0,0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(0, 0), QVector3D(-1,0,0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(1, 1), QVector3D(-1,0,0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(1, 0), QVector3D(-1,0,0)));

    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(0, 1), QVector3D(0,-1,0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(0, 0), QVector3D(0,-1,0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(1, 1), QVector3D(0,-1,0)));
    vertexes.append(VertexData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(1, 0), QVector3D(0,-1,0)));


    QVector<GLuint> indexes;
    indexes.append(0);
    indexes.append(1);
    indexes.append(2);

    indexes.append(2);
    indexes.append(1);
    indexes.append(3);

    for(int i = 0; i < 24; i+=4){

        indexes.append(i+0);
        indexes.append(i+1);
        indexes.append(i+2);

        indexes.append(i+2);
        indexes.append(i+1);
        indexes.append(i+3);


    }



    arrayBuffer.create();
    arrayBuffer.bind();
    arrayBuffer.allocate(vertexes.constData(), vertexes.size()*sizeof(VertexData));
    arrayBuffer.release();

    indexBuffer.create();
    indexBuffer.bind();
    indexBuffer.allocate(indexes.constData(), indexes.size()*sizeof(GLuint));
    indexBuffer.release();


    texture = new QOpenGLTexture(QImage("D:\\ITMM\\Graphics\\Shader\\shader\\cube.png").mirrored());

    texture->setMagnificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
    texture->setWrapMode(QOpenGLTexture::Repeat);


}
