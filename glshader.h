#ifndef GLSHADER_H
#define GLSHADER_H
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QString>

class GLShader : public QObject,protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GLuint ID;
    GLShader(const QString& vtxPath,const QString& fntPath);
    void use();
    void setFloat(const QString& name,float value);
    void setInt(const QString& name,int value);
    QOpenGLShaderProgram* getProgram();
private:
    QOpenGLShaderProgram* program=nullptr;
};

#endif // GLSHADER_H
