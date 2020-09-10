#include "playwidget.h"
#include <QFileDialog>

PlayWidget::PlayWidget(QWidget *parent) : QWidget(parent)
{
    layout=new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);

    topWidget=new GLWidget(this);

    midWidget=new QWidget(this);
    midWidget->setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed));
    midWidget->setMinimumSize(QSize(0,5));
    midLayout=new QHBoxLayout(midWidget);
    midLayout->setSpacing(5);
    midLayout->setContentsMargins(10,5,10,5);
    filePathPre=new QLabel("filepath :",midWidget);
    filePath=new QLabel(midWidget);
    midLayout->addWidget(filePathPre);
    midLayout->addWidget(filePath);

    bottomWidget=new QWidget(this);
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

    connect(fileButton,SIGNAL(clicked()),this,SLOT(open_file()));
    connect(playButton,SIGNAL(clicked()),this,SLOT(play_file()));
}

void PlayWidget::open_file()
{
    fileName=QFileDialog::getOpenFileName(this,tr("open file"),"","");
    filePath->setText(fileName);
}

void PlayWidget::play_file()
{
    decoder=new Decoder(fileName.toLatin1().data());
    connect(decoder,SIGNAL(getPicture2(AVFrame*,int,int)),topWidget,SLOT(showYuv3(AVFrame*, int, int)));
    decoder->start();
}
