#include "decoder.h"
#include <QDebug>
#include <QDateTime>

long long test2=0;
Decoder::Decoder(const char* in_file,QObject *parent):
    QThread (parent)
{
    av_register_all();
    pFmtCtx=avformat_alloc_context();
    if(avformat_open_input(&pFmtCtx,in_file,NULL,NULL)!=0){
        qDebug()<<"avformat_open_input failed\n";
    }
    if(avformat_find_stream_info(pFmtCtx,NULL)<0){
        qDebug()<<"avformat_find_stream_info failed\n";
    }
    for(int i=0;i<pFmtCtx->nb_streams;i++){
        if(pFmtCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO){
            videoidx=i;
            break;
        }
    }
    if(videoidx<0){
        qDebug()<<"no find video stream\n";
    }
    pCodecCtx=pFmtCtx->streams[videoidx]->codec;
    pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
    if(pCodec==NULL){
        qDebug()<<"no find decoder\n";
    }
    if(avcodec_open2(pCodecCtx,pCodec,NULL)<0){
        qDebug()<<"decoder open failed\n";
    }
    pFrame=av_frame_alloc();
}

void Decoder::test()
{

}

void Decoder::run()
{
    int finished=0;
    while(1){
        while(av_read_frame(pFmtCtx,&packet)>=0){
            if(packet.stream_index==videoidx){
                if(avcodec_decode_video2(pCodecCtx,pFrame,&finished,&packet)<0){
                    qDebug()<<"decode failed\n";
                    continue;
                }
            }
            if(finished){
                emit getPicture2(pFrame,pFrame->width,pFrame->height);
                qDebug()<<"decoder:run:"<<QThread::currentThreadId()<<"time:"<<QDateTime::currentDateTime().toMSecsSinceEpoch()-test2<<endl;
                test2=QDateTime::currentDateTime().toMSecsSinceEpoch();
                pFrame=av_frame_alloc();
            }
            QThread::msleep(35);
        }
        QThread::msleep(200);
    }

}
