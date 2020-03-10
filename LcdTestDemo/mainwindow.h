#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QList>
#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <QPushButton>
#include <QTextLine>
#include <QLineEdit>
#include <QTextEdit>
#include <QFile>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QKeyEvent>
#include <QSpinBox>

typedef struct{
    cv::Mat frame;
    int inRvalue;
    int inGvalue;
    int inBvalue;
}mFrame_t, *pFrame_t;

typedef struct{
    QPoint pos;
    int inRvalue;
    int inGvalue;
    int inBvalue;
    int outRvalue;
    int outGvalue;
    int outBvalue;
}mPos_t, *pPos_t;

typedef struct{
    mPos_t resPos[3];
}mResult_t, *pResult_t;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createView();
    void createTimer();


protected:
    virtual void keyPressEvent(QKeyEvent *ev);

public slots:
    void showPic();
    void capPic();
    void processDone();
    void startProcess();

private:
    void usbGetPic(cv::Mat &src);

private:
    QTimer *showTimer;
    QTimer *capTimer;
    QTimer *processTimer;

    QLabel *showLabel;
    QPixmap *tmpPix;
    int rInvalue;
    int gInvalue;
    int bInvalue;

    //界面
    QLabel *testLabel;
    QLineEdit *testText;
    QLabel *pos1xLabel;
    QLabel *pos1yLabel;
    QSpinBox *x1Value;
    QSpinBox *y1Vaule;
    QLabel *pos2xLabel;
    QLabel *pos2yLabel;
    QSpinBox *x2Value;
    QSpinBox *y2Vaule;
    QLabel *pos3xLabel;
    QLabel *pos3yLabel;
    QSpinBox *x3Value;
    QSpinBox *y3Vaule;
    QPushButton *startBtn;
    QTextBrowser *displayEdit;

    QGridLayout *rightLayout;
    QVBoxLayout *leftLayout;
    QGridLayout *mainLayout;


    //数据保存
    QFile *file;
    cv::VideoCapture *cap;
    //input data
    QList<pFrame_t> inputList;
    //output data
    QList<pResult_t> outputList;


};

#endif // MAINWINDOW_H
