#include "yuvplaywindow.h"
#include "getyuv.h"
#include <QFileDialog>

YuvPlayWindow::YuvPlayWindow(QWidget *parent) : QMainWindow(parent)
{
    resize(480,300);
    centralWidget=new QWidget(this);
    layout=new QVBoxLayout(centralWidget);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);

    topWidget=new GLWidget(centralWidget);

    midWidget=new QWidget(centralWidget);
    midWidget->setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed));
    midWidget->setMinimumSize(QSize(0,5));
    midLayout=new QHBoxLayout(midWidget);
    midLayout->setSpacing(5);
    midLayout->setContentsMargins(10,5,10,5);
    filePathPre=new QLabel("filepath :",midWidget);
    filePath=new QLabel(midWidget);
    midLayout->addWidget(filePathPre);
    midLayout->addWidget(filePath);

    bottomWidget=new QWidget(centralWidget);
    bottomWidget->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
    bottomWidget->setMinimumSize(QSize(10,5));
    bottomLayout=new QHBoxLayout(bottomWidget);
    bottomLayout->setSpacing(10);
    bottomLayout->setContentsMargins(10,5,10,5);
    fileButton=new QPushButton("open",bottomWidget);
    playButton=new QPushButton("play",bottomWidget);
    bottomLeftWidget=new QWidget(bottomWidget);
    bottomLayout->addWidget(fileButton);
    bottomLayout->addWidget(playButton);
    bottomLayout->addWidget(bottomLeftWidget);

    layout->addWidget(topWidget);
    layout->addWidget(midWidget);
    layout->addWidget(bottomWidget);

    setCentralWidget(centralWidget);

    connect(fileButton,SIGNAL(clicked()),this,SLOT(open_file()));
    connect(playButton,SIGNAL(clicked()),this,SLOT(play_file()));
}

void YuvPlayWindow::decoder_start()
{

}

void YuvPlayWindow::open_file()
{
    fileName=QFileDialog::getOpenFileName(this,tr("open file"),"","");
    filePath->setText(fileName);
}

void YuvPlayWindow::play_file()
{
    getYuv=new GetYuv(fileName,this);
    connect(getYuv,SIGNAL(sndYuv(uchar*,uint,uint)),topWidget,SLOT(showYuv(uchar*,uint,uint)));
    getYuv->start();
}
