#include "mainwindow.h"
#include <QApplication>
#include "glwidget.h"
#include "getyuv.h"
#include "yuvplaywindow.h"
#include "cameracapture.h"
#include <QCamera>
#include <QCameraInfo>
#include <stdint.h>
#include <QObject>
#include "picturequeue.h"
#include "encoder.h"
#include "twopicture.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TwoPicture  w;
//    w.show();
//    MainWindow w;
    w.show();
    return a.exec();


}




















