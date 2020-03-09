#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <QLabel>
#include <QTextEdit>
#include <QTextLine>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTimer>
#include <QTextBrowser>
#include <QSpinBox>
#include <QKeyEvent>
#include "drawwidget.h"


class mainWidget : public QWidget
{
    Q_OBJECT

public:
    mainWidget(QWidget *parent = 0);
    ~mainWidget();

    void createWidget();

protected:
    virtual void keyPressEvent(QKeyEvent *ev);

public slots:
    void mainProcess();
    void timedone();
    void showRsult();

private:
    void usbGetPic();

private:
    //定时
    QTimer *timer;
    //界面
    QLabel *rLabel;
    QLabel *gLabel;
    QLabel *bLabel;
    QSpinBox *rTextLine;
    QSpinBox *gTextLine;
    QSpinBox *bTextLine;
    QPushButton *resuleBtn;
    QTextBrowser *displayResult;

    Drawwidget *mDrawwidget;

    QGridLayout *rightLayout;
    QGridLayout *mainLayout;

    //处理
    QLabel *picLabel;
    QPixmap pix;
    cv::Mat src;

    //result
    int inputRvalue;
    int inputGvalue;
    int inputBvalue;
};

#endif // MAINWIDGET_H
