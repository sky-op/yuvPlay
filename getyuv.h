#ifndef GETYUV_H
#define GETYUV_H
#include <QThread>
#include <QFile>

#define WIDTH 352
#define HEIGHT 288
class GetYuv : public QThread
{
    Q_OBJECT
public:
    GetYuv(const QString& fileName,QObject *parent=nullptr);
protected:
    void run() override;
private:
    QFile* yuvFile;
    uchar yuvPtr[WIDTH*HEIGHT*3/2];
signals:
    void sndYuv(uchar* yuvPtr,uint width,uint height);
};

#endif // GETYUV_H
