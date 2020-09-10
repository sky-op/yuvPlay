#ifndef CAMERACAPTURE_H
#define CAMERACAPTURE_H
#include <QAbstractVideoSurface>
#include <QVideoWidget>
#include "encoder.h"

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

class CameraCapture : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    explicit CameraCapture(QObject *parent=nullptr);
    virtual QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType=QAbstractVideoBuffer::NoHandle) const override;
    virtual bool present(const QVideoFrame& frame) override;
    uchar* getYUV420P(const uchar* src,enum AVPixelFormat pix_fmt,int width,int height);
    enum AVPixelFormat pix_fmt[35];
    enum AVPixelFormat ffmpeg_type;
signals:
    void frameAvailable(PICTURE_FRAME* picture_frame,int width,int height);
};

#endif // CAMERACAPTURE_H
