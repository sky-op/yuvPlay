#include "getyuv.h"
#include <QDebug>

GetYuv::GetYuv(const QString& fileName,QObject *parent):
    QThread (parent)
{
    yuvFile=new QFile(fileName);
}

void GetYuv::run()
{
    int ret=yuvFile->open(QIODevice::ReadOnly);
    if(!ret){
        qDebug()<<"YUV file failed\n";
    }
    int length=0;
    while(1){
        if((length=yuvFile->read((char*)yuvPtr,WIDTH*HEIGHT*3/2))!=WIDTH*HEIGHT*3/2){
            yuvFile->seek(0);
            yuvFile->read((char*)yuvPtr,WIDTH*HEIGHT*3/2);
        }
        emit sndYuv(yuvPtr,WIDTH,HEIGHT);
        QThread::msleep(100);
    }
}
