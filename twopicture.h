#ifndef TWOPICTURE_H
#define TWOPICTURE_H

#include <QMainWindow>
#include <QCamera>
#include <QCameraInfo>
#include "cameracapture.h"
#include "glwidget.h"
#include "encoder.h"
#include "decoder.h"
#include <QHBoxLayout>
#include "playwidget.h"

class TwoPicture : public QMainWindow
{
    Q_OBJECT
public:
    explicit TwoPicture(QWidget *parent = nullptr);
    void init();
    void decoder_start();
private:
    QWidget* centralWidget;
    QHBoxLayout* layout;
    GLWidget* leftWidget;
    PlayWidget* rightWidget;
    QCamera* camera;
    CameraCapture* cameraCapture;
    Encoder* encoder;
    Decoder* decoder;

signals:

public slots:
};

#endif // TWOPICTURE_H
