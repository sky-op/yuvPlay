#ifndef PICTUREQUEUE_H
#define PICTUREQUEUE_H

#include <QObject>
#include <QQueue>
#include <encoder.h>
#include <QThread>

class PictureQueue : public QThread
{
    Q_OBJECT
public:
    explicit PictureQueue(QObject *parent = nullptr);
private:
    QQueue<PICTURE_FRAME*> pictureQueue;
protected:
    void run() override;

signals:

public slots:
    void put(PICTURE_FRAME* picture_frame);
};

#endif // PICTUREQUEUE_H
