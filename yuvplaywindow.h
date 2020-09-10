#ifndef YUVPLAYWINDOW_H
#define YUVPLAYWINDOW_H

#include <QMainWindow>
#include "glwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include "getyuv.h"

class YuvPlayWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit YuvPlayWindow(QWidget *parent = nullptr);
    void decoder_start();

signals:

public slots:
    void open_file();
    void play_file();
private:
    QWidget* centralWidget;
    QVBoxLayout* layout;

    GLWidget* topWidget;

    QWidget* midWidget;
    QHBoxLayout* midLayout;
    QLabel* filePathPre;
    QLabel* filePath;

    QWidget* bottomWidget;
    QHBoxLayout* bottomLayout;
    QPushButton* fileButton;
    QPushButton* playButton;
    QWidget* bottomLeftWidget;

    QString fileName;
    QFile* yuvFile;
    GetYuv* getYuv;
};

#endif // YUVPLAYWINDOW_H
