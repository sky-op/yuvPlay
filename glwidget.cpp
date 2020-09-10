#include "glwidget.h"
#include <QTime>
#include <QThread>

GLWidget::GLWidget(QWidget *parent):
    QOpenGLWidget (parent)
{
}

void GLWidget::showYuv(uchar *ptr, uint width, uint height)
{
    data0=ptr;
    data1=ptr+width*height;
    data2=ptr+width*height*5/4;
    videoW=width;
    videoH=height;
    update();
}

void GLWidget::showYuv2(PICTURE_FRAME *picture_frame, int width, int height)
{
    data0=picture_frame->picture_buf->data[0];
    data1=picture_frame->picture_buf->data[1];
    data2=picture_frame->picture_buf->data[2];
    videoW=width;
    videoH=height;
    update();
    emit picturePlayed(picture_frame,width,height);
}

void GLWidget::showYuv3(AVFrame *frame, int width, int height)
{
    data0=frame->data[0];
    data1=frame->data[1];
    data2=frame->data[2];
    videoW=width;
    videoH=height;
    update();
    av_frame_free(&frame);
}

void GLWidget::initializeGL()
{
    qDebug() << "initializeGL";
    initializeOpenGLFunctions();
    glClearColor(1,1,1,1);
    glEnable(GL_DEPTH_TEST);
    static const GLfloat vertices[]={
        -1.0f,-1.0f,
        1.0f,-1.0f,
        -1.0f,1.0f,
        1.0f,1.0f,
        0.0f,1.0f,
        1.0f,1.0f,
        0.0f,0.0f,
        1.0f,0.0f
    };

    shader=new GLShader(":/glsl/vtx.vsh",":/glsl/fnt.fsh");
    program=shader->getProgram();
    int positionHandle=program->attributeLocation("qt_Vertex");
    int textureHandle=program->attributeLocation("qt_MultiTexCoord0");
    program->enableAttributeArray(positionHandle);
    program->setAttributeArray(positionHandle,vertices,2);
    program->enableAttributeArray(textureHandle);
    program->setAttributeArray(textureHandle,vertices+8,2);

    textureUniformY=program->uniformLocation("tex_y");
    textureUniformU=program->uniformLocation("tex_u");
    textureUniformV=program->uniformLocation("tex_v");
    textureY=new QOpenGLTexture(QOpenGLTexture::Target2D);
    textureU=new QOpenGLTexture(QOpenGLTexture::Target2D);
    textureV=new QOpenGLTexture(QOpenGLTexture::Target2D);
    textureY->create();
    textureU->create();
    textureV->create();
    idY=textureY->textureId();
    idU=textureU->textureId();
    idV=textureV->textureId();
}

void GLWidget::paintGL()
{
    shader->use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,idY);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RED,(GLsizei)videoW,(GLsizei)videoH,0,GL_RED,GL_UNSIGNED_BYTE,data0);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,idU);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RED,videoW>>1,videoH>>1,0,GL_RED,GL_UNSIGNED_BYTE,data1);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D,idV);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RED,videoW>>1,videoH>>1,0,GL_RED,GL_UNSIGNED_BYTE,data2);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

    glUniform1i(textureUniformY,0);
    glUniform1i(textureUniformU,1);
    glUniform1i(textureUniformV,2);
    glDrawArrays(GL_TRIANGLE_STRIP,0,4);

}
