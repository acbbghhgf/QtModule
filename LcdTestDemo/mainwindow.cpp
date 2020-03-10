#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(tr("LCDtest"));
    createView();
    createTimer();
    tmpPix = new QPixmap(1024, 600);
    showLabel = new QLabel;

    cap = new cv::VideoCapture(0);
    if(!cap->isOpened())
    {
        qDebug() << "capture open error!";
    }
    else {
        qDebug() << "capture opened!";
    }

    connect(startBtn, SIGNAL(clicked()), this, SLOT(startProcess()));
}

MainWindow::~MainWindow()
{

}


void MainWindow::createView()
{
    testLabel = new QLabel(tr("testLCDmodel："));
    testText = new QLineEdit;
    startBtn = new QPushButton(tr("start"));
    pos1xLabel = new QLabel(tr("Pos1-x:"));
    pos1yLabel = new QLabel(tr("Pos1-y:"));
    x1Value = new QSpinBox;
    x1Value->setRange(0,100);
    x1Value->setSingleStep(10);
    y1Vaule = new QSpinBox;
    y1Vaule->setRange(0,100);
    y1Vaule->setSingleStep(10);

    pos2xLabel = new QLabel(tr("Pos2-x:"));
    pos2yLabel = new QLabel(tr("Pos2-y:"));
    x2Value = new QSpinBox;
    x2Value->setRange(0,100);
    x2Value->setSingleStep(10);
    y2Vaule = new QSpinBox;
    y2Vaule->setRange(0,100);
    y2Vaule->setSingleStep(10);

    pos3xLabel = new QLabel(tr("Pos3-x:"));
    pos3yLabel = new QLabel(tr("Pos3-y:"));
    x3Value = new QSpinBox;
    x3Value->setRange(0,100);
    x3Value->setSingleStep(10);
    y3Vaule = new QSpinBox;
    y3Vaule->setRange(0,100);
    y3Vaule->setSingleStep(10);


    rightLayout = new QGridLayout;
    rightLayout->setMargin(10);
    rightLayout->setSpacing(5);
    rightLayout->addWidget(testLabel, 0, 0);
    rightLayout->addWidget(testText, 0, 1, 1, 3);
    rightLayout->addWidget(pos1xLabel, 1, 0);
    rightLayout->addWidget(x1Value, 1, 1);
    rightLayout->addWidget(pos1yLabel,1, 2);
    rightLayout->addWidget(y1Vaule, 1, 3);

    rightLayout->addWidget(pos2xLabel, 2, 0);
    rightLayout->addWidget(x2Value, 2, 1);
    rightLayout->addWidget(pos2yLabel, 2, 2);
    rightLayout->addWidget(y2Vaule, 2, 3);

    rightLayout->addWidget(pos3xLabel, 3, 0);
    rightLayout->addWidget(x3Value, 3, 1);
    rightLayout->addWidget(pos3yLabel, 3, 2);
    rightLayout->addWidget(y3Vaule, 3, 3);

    rightLayout->addWidget(startBtn, 4, 0, 2, 4);

    displayEdit = new QTextBrowser;
    leftLayout = new QVBoxLayout;
    leftLayout->addWidget(displayEdit);

    mainLayout = new QGridLayout(this);
    mainLayout->addLayout(leftLayout, 0, 0);
    mainLayout->addLayout(rightLayout, 0, 1);
}

void MainWindow::createTimer()
{
    showTimer = new QTimer(this);
    connect(showTimer, SIGNAL(timeout()), this, SLOT(showPic()));

    capTimer = new QTimer(this);
    capTimer->setSingleShot(true);
    connect(capTimer, SIGNAL(timeout()), this, SLOT(capPic()));

    processTimer = new QTimer(this);
    connect(processTimer, SIGNAL(timeout()), this, SLOT(processDone()));
}

void MainWindow::startProcess()
{
    startBtn->setEnabled(false);
    //修改颜色像素值步进改变
    //启动颜色显示
    rInvalue = 0;
    gInvalue = 0;
    bInvalue = 0;
    showTimer->start(3000);
    processTimer->start(3000);
}

void MainWindow::showPic()
{
    //像素值变化
//    showLabel->hide();
    tmpPix->fill(QColor(rInvalue, gInvalue, bInvalue));
    showLabel->setPixmap(*tmpPix);
    showLabel->setScaledContents(true);
    //颜色显示，并且启动拍照
    showLabel->setCursor(Qt::BlankCursor);
    showLabel->showFullScreen();

    rInvalue += 100;
    if(rInvalue > 255)
    {
        rInvalue = 0;
        gInvalue += 100;
        if(gInvalue > 255)
        {
            gInvalue = 0;
            bInvalue += 255;
            if(bInvalue > 255)
            {
                showTimer->stop();
                showLabel->close();
                startBtn->setEnabled(true);
                this->setCursor(Qt::ArrowCursor);
            }
        }
    }
    qDebug() << "showpic start cap timer";
    capTimer->start(1500);
}

void MainWindow::capPic()
{
    //拍照
    qDebug() <<"cap pic timer running!";
    pFrame_t frameData = new mFrame_t;
    frameData->inRvalue = rInvalue;
    frameData->inGvalue = gInvalue;
    frameData->inBvalue = bInvalue;

    //使用usb摄像头拍照并保存图片。
    usbGetPic(frameData->frame);
    if(!frameData->frame.empty())
    {
        inputList.push_back(frameData);
    }
    else {
        qDebug() <<"cat get pic error!";
        delete frameData;
    }
}

void MainWindow::processDone()
{
    //处理获得的图片并解析数据并释放图片
    if(inputList.empty())
    {
        if(showTimer->isActive())
        {//还在获取数据，等待处理
            return;
        }
        else {//处理结束
            processTimer->stop();
        }
    }
    else {
        pFrame_t dataTmp = inputList.first();
        pResult_t resultPosTmp = new mResult_t;
        //暂时用数字替代，后期替换成使用该百分比数字。
        resultPosTmp->resPos[0].pos.setX(x1Value->text().toInt());
        resultPosTmp->resPos[0].pos.setY(y1Vaule->text().toInt());
        resultPosTmp->resPos[1].pos.setX(x2Value->text().toInt());
        resultPosTmp->resPos[1].pos.setY(y2Vaule->text().toInt());
        resultPosTmp->resPos[2].pos.setX(x3Value->text().toInt());
        resultPosTmp->resPos[2].pos.setY(y3Vaule->text().toInt());

        //获取坐标值
        cv::Mat dst;
        cv::cvtColor(dataTmp->frame, dst, cv::COLOR_BGR2RGB);
        ----------------0310

        //获取图像rgb像素值
        inputList.pop_front();
        delete dataTmp;
    }

}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Q)
    {
        showLabel->close();
        this->close();
    }
}

void MainWindow::usbGetPic(cv::Mat &src)
{
    if(!cap->isOpened())
    {
        qDebug() << "capture open error!";
        return ;
    }
    for(int i = 0; i < 6; i++)
    {
        cap->read(src);
    }
    if(src.empty())
    {
        qDebug() << "usb get frame is empty!!!";
        return ;
    }

}
