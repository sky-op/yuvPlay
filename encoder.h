#ifndef ENCODER_H
#define ENCODER_H

#include <QObject>
#include <stdint.h>
extern "C"
{
    #include <stdio.h>
    #include <stdint.h>

    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
    #include <libavdevice/avdevice.h>
    #include <libavformat/version.h>
    #include <libavutil/time.h>
    #include <libavutil/mathematics.h>
    #include <libswscale/swscale.h>
    #include <libavutil/imgutils.h>
    #include <libavutil/pixfmt.h>
}

typedef struct _picture_frame{
    AVPicture* picture_buf;
    uint8_t played;
    uint8_t encodered;
}PICTURE_FRAME;

class Encoder : public QObject
{
    Q_OBJECT
public:
    explicit Encoder(QObject *parent = nullptr);
private:
    AVFormatContext* pFmtCtx;
    AVOutputFormat* pOutFmt;
    AVStream* pStream;
    AVCodecContext* pCodecCtx;
    AVCodec* pCodec;
    AVPacket pkt;
    uint8_t* picture_buf;
    AVFrame* pFrame;
    int picture_size;
    int cnt=0;
    int frame_num=0;
    const char* out_file="out.h264";

signals:

public slots:
    void encode_picture(PICTURE_FRAME* picture_frame,int width,int height);
};

#endif // ENCODER_H
