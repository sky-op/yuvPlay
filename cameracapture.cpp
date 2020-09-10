#include "cameracapture.h"
#include <QDebug>
#include <string.h>
#include <QThread>
#include <QDateTime>

long long test1=0;
CameraCapture::CameraCapture(QObject *parent) : QAbstractVideoSurface (parent)
{
    pix_fmt[QVideoFrame::Format_ARGB32]=AV_PIX_FMT_ARGB;
    pix_fmt[QVideoFrame::Format_RGB24]=AV_PIX_FMT_RGB24;
    pix_fmt[QVideoFrame::Format_BGRA32]=AV_PIX_FMT_BGRA;
    pix_fmt[QVideoFrame::Format_ABGR32]=AV_PIX_FMT_ABGR;
    pix_fmt[QVideoFrame::Format_BGR24]=AV_PIX_FMT_BGR24;
    pix_fmt[QVideoFrame::Format_YUV420P]=AV_PIX_FMT_YUV420P;
    pix_fmt[QVideoFrame::Format_UYVY]=AV_PIX_FMT_UYVY422;
    pix_fmt[QVideoFrame::Format_YUYV]=AV_PIX_FMT_YUYV422;
    pix_fmt[QVideoFrame::Format_RGB32]=AV_PIX_FMT_RGB32;
}

QList<QVideoFrame::PixelFormat> CameraCapture::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    Q_UNUSED(handleType);
    return QList<QVideoFrame::PixelFormat>()
            <<QVideoFrame::Format_RGB32
            <<QVideoFrame::Format_YUV420P;
}

bool CameraCapture::present(const QVideoFrame &frame)
{
    qDebug()<<"cameracapture:present:"<<QThread::currentThreadId()<<"time:"<<QDateTime::currentDateTime().toMSecsSinceEpoch()-test1<<endl;
    test1=QDateTime::currentDateTime().toMSecsSinceEpoch();
    if(frame.isValid()){
        QVideoFrame cloneFrame(frame);
        cloneFrame.map(QAbstractVideoBuffer::ReadOnly);
        ffmpeg_type=pix_fmt[cloneFrame.pixelFormat()];
        AVPicture* in_picture=(AVPicture*)av_malloc(sizeof(AVPicture));
        AVPicture* out_picture=(AVPicture*)av_malloc(sizeof(AVPicture));
        int size=av_image_get_buffer_size(AV_PIX_FMT_YUV420P,cloneFrame.width(),cloneFrame.height(),1);
        uint8_t* picture_buf=(uint8_t*)av_malloc(size);
        av_image_fill_arrays(out_picture->data,out_picture->linesize,picture_buf,AV_PIX_FMT_YUV420P,cloneFrame.width(),cloneFrame.height(),1);
        av_image_fill_arrays(in_picture->data,in_picture->linesize,cloneFrame.bits(),ffmpeg_type,cloneFrame.width(),cloneFrame.height(),1);
        struct SwsContext* pSwsCtx;
        pSwsCtx=sws_getContext(cloneFrame.width(),cloneFrame.height(),ffmpeg_type,cloneFrame.width(),cloneFrame.height(),AV_PIX_FMT_YUV420P,SWS_BICUBIC,NULL,NULL,NULL);
        sws_scale(pSwsCtx,in_picture->data,in_picture->linesize,0,cloneFrame.height(),out_picture->data,out_picture->linesize);
        PICTURE_FRAME* picture_frame=(PICTURE_FRAME*)av_malloc(sizeof(PICTURE_FRAME));
        picture_frame->picture_buf=out_picture;
        picture_frame->played=0;
        picture_frame->encodered=0;
        emit frameAvailable(picture_frame,cloneFrame.width(),cloneFrame.height());
        sws_freeContext(pSwsCtx);
        cloneFrame.unmap();
        av_free(in_picture);
        return  true;
    }
    return  false;
}
