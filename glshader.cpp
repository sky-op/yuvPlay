#include "glshader.h"
#include <QFile>
#include <QTextStream>

GLShader::GLShader(const QString& vtxPath, const QString& fntPath)
{
    bool ret;
    QOpenGLShader *vtxShader=new QOpenGLShader(QOpenGLShader::Vertex,this);
    QOpenGLShader *fntShader=new QOpenGLShader(QOpenGLShader::Fragment,this);
    ret=vtxShader->compileSourceFile(vtxPath);
    if(ret!=true){
        qDebug()<<"compile vertex code failed\n"<<endl;
        return;
    }
    ret=fntShader->compileSourceFile(fntPath);
    if(ret!=true){
        qDebug()<<"compile fragment code failed\n"<<endl;
        return;
    }
    program=new QOpenGLShaderProgram(this);
    program->addShader(vtxShader);
    program->addShader(fntShader);
    ret=program->link();
    if(ret!=true){
        qDebug()<<"program linked failed\n"<<endl;
    }
}

void GLShader::use()
{
    program->bind();
}

void GLShader::setFloat(const QString &name, float value)
{
    glUniform1f(program->uniformLocation(name),value);
}

void GLShader::setInt(const QString &name, int value)
{
    glUniform1i(program->uniformLocation(name),value);
}

QOpenGLShaderProgram *GLShader::getProgram()
{
    return program;
}
