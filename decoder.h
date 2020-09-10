#ifndef DECODER_H
#define DECODER_H

#include <stdint.h>
#include <QThread>
#include "encoder.h"

class Decoder : public QThread
{
    Q_OBJECT
public:
    explicit Decoder(const char* in_file="out_file",QObject *parent=nullptr);
    void test();
protected:
    void run() override;
private:
    AVFormatContext* pFmtCtx;
    AVCodecContext* pCodecCtx;
    AVCodec* pCodec;
    int videoidx=-1;
    AVFrame* pFrame;
    AVPacket packet;
signals:
    void getPicture2(AVFrame* frame,int width,int height);
};

#endif // DECODER_H
