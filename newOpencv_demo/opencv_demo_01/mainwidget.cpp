#include "mainwidget.h"
#include <QThread>
#include <QDebug>


mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
{
    createWidget();

    picLabel = new QLabel;
    timer = new QTimer;
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(timedone()));

    cap = new cv::VideoCapture(0);
    if(cap->isOpened())
    {
        qDebug() << "capture is opened!";
    }
    else{
        qDebug() << "capture open error!!!";
    }
}

mainWidget::~mainWidget()
{

}

void mainWidget::createWidget()
{
    rLabel = new QLabel(tr("R通道值："));
    rTextLine = new QSpinBox;
    rTextLine->setRange(0,255);
    rTextLine->setSingleStep(10);
    gLabel = new QLabel(tr("G通道值："));
    gTextLine = new QSpinBox;
    gTextLine->setRange(0, 255);
    gTextLine->setSingleStep(10);
    bLabel = new QLabel(tr("B通道值："));
    bTextLine = new QSpinBox;
    bTextLine->setRange(0,255);
    bTextLine->setSingleStep(10);
    resuleBtn = new QPushButton(tr("开始"));
    resuleBtn->setEnabled(true);
    displayResult = new QTextBrowser;

    //右侧布局
    rightLayout = new QGridLayout;
    rightLayout->addWidget(rLabel, 0 , 0);
    rightLayout->addWidget(rTextLine, 0 , 1);
    rightLayout->addWidget(gLabel, 0 , 2);
    rightLayout->addWidget(gTextLine, 0 ,3);
    rightLayout->addWidget(bLabel, 0, 4);
    rightLayout->addWidget(bTextLine, 0 ,5);
    rightLayout->addWidget(resuleBtn, 1, 0, 1, 2);
    rightLayout->addWidget(displayResult, 2, 0, 1, 6);

    //左侧显示窗口
    mDrawwidget = new Drawwidget(this);

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(mDrawwidget, 0, 0);
    mainLayout->addLayout(rightLayout, 0 ,1);

    //信号连接
    connect(resuleBtn, SIGNAL(clicked()), this, SLOT(mainProcess()));
    connect(mDrawwidget, SIGNAL(rgbUpdate()), this, SLOT(showRsult()));
}

void mainWidget::mainProcess()
{
    //放置重复触发
    resuleBtn->setEnabled(false);

    //绘制图片并显示全屏。

//    picLabel->setPixmap(pix.fromImage(tmp));
    inputRvalue = rTextLine->text().toInt();
    inputGvalue = gTextLine->text().toInt();
    inputBvalue = bTextLine->text().toInt();

    QPixmap *tmpPix = new QPixmap(1024, 600);
    tmpPix->fill(QColor(inputRvalue, inputGvalue, inputBvalue));
    picLabel->setPixmap(*tmpPix);
    picLabel->setScaledContents(true);
    picLabel->setCursor(Qt::BlankCursor);//隐藏鼠标
    picLabel->showFullScreen();//全屏显示

    timer->start(5000);//延时5S关闭画面。
}

void mainWidget::timedone()
{
    //使用usb摄像头拍照并保存图片。
    usbGetPic();

    //将图片显示drawwidget窗口下。
    if(!src.empty())
    {
        mDrawwidget->showPic(src);
        src.release();
    }
    picLabel->hide();
    resuleBtn->setEnabled(true);
}


void mainWidget::usbGetPic()
{
    if(!cap->isOpened())
    {
        qDebug() << "capture open error!";
        return ;
    }
    for(int i = 0; i < 6; i++)
    {
        cap->read(src);
//        cap >>  src;
    }
    if(src.empty())
    {
        qDebug() << "usb get frame is empty!!!";
        return ;
    }

//    cv::imwrite("src.png", src);
//    cap.release();

}


void mainWidget::showRsult()
{
    QString str, str1, str2, str3;

    int displayRvalue = mDrawwidget->getRvalue();
    int displayGvalue = mDrawwidget->getGvalue();
    int displayBvalue = mDrawwidget->getBvalue();

    str1 = QString("input(%1, %2, %3), ").arg(inputRvalue).arg(inputGvalue).arg(inputBvalue);
    str2 = QString("display(%1,%2,%3), ").arg(displayRvalue).arg(displayGvalue).arg(displayBvalue);
    int tmpResult = MAX(abs(displayRvalue - inputRvalue) , abs(displayGvalue - inputGvalue));
    tmpResult = MAX(tmpResult , abs(displayBvalue - inputBvalue));
    str3 = QString("result = %1").arg(tmpResult);
    str = str1 + str2 + str3;
    displayResult->append(str);
}

void mainWidget::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key::Key_Q)
    {
        this->close();
    }
}
