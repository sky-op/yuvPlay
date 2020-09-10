#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include "glshader.h"
#include "cameracapture.h"
#include "encoder.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent=nullptr);

public slots:
    void showYuv(uchar *ptr,uint width,uint height);
    void showYuv2(PICTURE_FRAME* picture_frame,int width,int height);
    void showYuv3(AVFrame* frame,int width,int height);

protected:
    void initializeGL();
    void paintGL();

private:
    GLShader* shader;
    QOpenGLShaderProgram* program;
    int textureUniformY,textureUniformU,textureUniformV;
    QOpenGLTexture *textureY=nullptr,*textureU=nullptr,*textureV=nullptr;
    GLuint idY,idU,idV;
    uint videoW,videoH;
    uchar *yuvPtr=nullptr;
    uchar *data0=nullptr;
    uchar *data1=nullptr;
    uchar *data2=nullptr;
    PICTURE_FRAME* picture_frame=nullptr;
signals:
    void picturePlayed(PICTURE_FRAME* picture_frame,int width,int height);
};

#endif // GLWIDGET_H
