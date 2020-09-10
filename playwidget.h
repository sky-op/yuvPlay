#ifndef PLAYWIDGET_H
#define PLAYWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFile>
#include "glwidget.h"
#include "decoder.h"

class PlayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayWidget(QWidget *parent = nullptr);
private:
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

    Decoder* decoder;
signals:

public slots:
    void open_file();
    void play_file();
};

#endif // PLAYWIDGET_H
