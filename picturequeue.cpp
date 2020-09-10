#include "picturequeue.h"
#include <QDebug>

PictureQueue::PictureQueue(QObject *parent) : QThread(parent)
{

}

void PictureQueue::run()
{
    while(1){
        while(!pictureQueue.isEmpty()){
            PICTURE_FRAME* picture_frame=pictureQueue.dequeue();
            if(picture_frame->played&&picture_frame->encodered){
                av_free(picture_frame->picture_buf->data[0]);
                av_free(picture_frame->picture_buf);
                av_free(picture_frame);
            }
            QThread::usleep(100000);
            qDebug()<<"picturequeue:run:"<<QThread::currentThreadId()<<"length:"<<pictureQueue.count()<<endl;
        }
        QThread::usleep(100000);
    }
}

void PictureQueue::put(PICTURE_FRAME *picture_frame)
{
    pictureQueue.enqueue(picture_frame);
}
