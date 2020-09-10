#include "twopicture.h"

TwoPicture::TwoPicture(QWidget *parent) : QMainWindow(parent)
{
    resize(1280,720);
    centralWidget=new QWidget(this);
    layout=new QHBoxLayout(centralWidget);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    leftWidget=new GLWidget(centralWidget);
    rightWidget=new PlayWidget(centralWidget);
    layout->addWidget(leftWidget);
    layout->addWidget(rightWidget);
    setCentralWidget(centralWidget);
    init();
}

void TwoPicture::init()
{
    QList<QCameraInfo> cameras=QCameraInfo::availableCameras();
    foreach(const QCameraInfo& cameraInfo,cameras){
        camera=new QCamera(cameraInfo);
        break;
    }
    cameraCapture=new CameraCapture;
    camera->setViewfinder(cameraCapture);
    encoder=new Encoder;
    connect(cameraCapture,SIGNAL(frameAvailable(PICTURE_FRAME*,int,int)),leftWidget,SLOT(showYuv2(PICTURE_FRAME*,int,int)));
    connect(leftWidget,SIGNAL(picturePlayed(PICTURE_FRAME*,int,int)),encoder,SLOT(encode_picture(PICTURE_FRAME*,int,int)));
    camera->start();
}

void TwoPicture::decoder_start()
{
    decoder->start();
}
