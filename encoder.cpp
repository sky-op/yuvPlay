#include "encoder.h"
#include <QDebug>
#include <QThread>

#define E_WIDTH 1280
#define E_HEIGHT 720

Encoder::Encoder(QObject *parent) : QObject(parent)
{
    av_register_all();

    pFmtCtx=avformat_alloc_context();
    pOutFmt=av_guess_format(NULL,out_file,NULL);
    pFmtCtx->oformat=pOutFmt;
    if(avio_open(&pFmtCtx->pb,out_file,AVIO_FLAG_READ_WRITE)<0){
        qDebug()<<"encoder failed to open output file\n";
    }
    pStream=avformat_new_stream(pFmtCtx,0);
    if(pStream==NULL){
        qDebug()<<"encoder new stream failed\n";
    }

    pCodecCtx=pStream->codec;
    pCodecCtx->codec_id=pOutFmt->video_codec;
    pCodecCtx->codec_type=AVMEDIA_TYPE_VIDEO;
    pCodecCtx->pix_fmt=AV_PIX_FMT_YUV420P;
    pCodecCtx->width=E_WIDTH;
    pCodecCtx->height=E_HEIGHT;
    pCodecCtx->bit_rate=400000;
    pCodecCtx->gop_size=250;

    pCodecCtx->time_base.num=1;
    pCodecCtx->time_base.den=25;
    pCodecCtx->qmin=10;
    pCodecCtx->qmax=51;
    pCodecCtx->max_b_frames=3;

    AVDictionary* param=nullptr;
    if(pCodecCtx->codec_id==AV_CODEC_ID_H264){
        av_dict_set(&param,"preset","slow",0);
        av_dict_set(&param,"tune","zerolatency",0);
    }
    av_dump_format(pFmtCtx,0,out_file,1);
    pCodec=avcodec_find_encoder(pCodecCtx->codec_id);
    if(!pCodec){
        qDebug()<<"encoder cannot find encoder\n";
    }
    if(avcodec_open2(pCodecCtx,pCodec,&param)<0){
        qDebug()<<"encoder failed to open encoder\n";
    }
    pFrame=av_frame_alloc();
    picture_size=av_image_get_buffer_size(AV_PIX_FMT_YUV420P,E_WIDTH,E_HEIGHT,1);
    picture_buf=(uint8_t*)av_malloc(picture_size);
    av_image_fill_arrays(pFrame->data,pFrame->linesize,picture_buf,AV_PIX_FMT_YUV420P,E_WIDTH,E_HEIGHT,1);
    avformat_write_header(pFmtCtx,NULL);
    av_new_packet(&pkt,picture_size);
}

void Encoder::encode_picture(PICTURE_FRAME *picture_frame, int width, int height)
{
    pFrame->data[0]=picture_frame->picture_buf->data[0];
    pFrame->data[1]=picture_frame->picture_buf->data[1];
    pFrame->data[2]=picture_frame->picture_buf->data[2];
    pFrame->pts=frame_num*(pStream->time_base.den)/(pStream->time_base.num*25);
    int got_picture=0;
    int ret=avcodec_encode_video2(pCodecCtx,&pkt,pFrame,&got_picture);
    if(ret<0){
        qDebug()<<"encoder failed to encode\n";
    }
    if(got_picture==1){
        pkt.stream_index=pStream->index;
        ret=av_write_frame(pFmtCtx,&pkt);
        av_free_packet(&pkt);
    }
    av_free(picture_frame->picture_buf->data[0]);
    av_free(picture_frame->picture_buf);
    av_free(picture_frame);
}
