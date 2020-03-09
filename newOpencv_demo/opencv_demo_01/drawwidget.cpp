#include "drawwidget.h"
#include <QDebug>

Drawwidget::Drawwidget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);//对窗体背景色设置
    setPalette(QPalette(Qt::white));
    pix = new QPixmap(size());
    pix->fill(Qt::white);
    setMinimumSize(600, 400);//设置最小尺寸

    mresule = new ResuleEdit(this);
    mresule->hide();
}


void Drawwidget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "press mouse";
    QString str;
    if(src.empty())
    {
         str = QString("pos = (%1, %2), rgb = (%3, %4, %5);").arg(event->x()).arg(event->y())\
                .arg(1).arg(2).arg(3);
    }
    else {
        rvalue = src.at<cv::Vec3b>(cv::Point(event->x(), event->y()))[0];
        gvalue = src.at<cv::Vec3b>(cv::Point(event->x(), event->y()))[1];
        bvalue = src.at<cv::Vec3b>(cv::Point(event->x(), event->y()))[2];

        str = QString("pos = (%1, %2), rgb = (%3, %4, %5);").arg(event->x()).arg(event->y())\
                .arg(rvalue).arg(gvalue).arg(bvalue);
        emit rgbUpdate();
    }
//    mresule->mainEdit->append(str);
//    if(mresule->isHidden())
//    {
//        qDebug() << "show mresule";
//        mresule->show();
//    }
}


void Drawwidget::showPic(cv::Mat &pixSrc)
{

//    pix = new QPixmap("src.png");
//    src = cv::imread("src.png");
//    src = pixSrc;
//    cv::Mat temp;]
    if(!src.empty())
        src.release();
    cv::cvtColor(pixSrc, src, cv::COLOR_BGR2RGB);//BGR convert to RGB

    update();
}

void Drawwidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);


    QImage tmp = QImage((const unsigned char*)(src.data), src.cols, src.rows, src.step, QImage::Format_RGB888);
    p.drawImage(QPoint(0,0), tmp);
//    p.drawPixmap(QPoint(0,0), *pix);
}

int Drawwidget::getRvalue()
{
    return rvalue;
}

int Drawwidget::getGvalue()
{
    return gvalue;
}

int Drawwidget::getBvalue()
{
    return bvalue;
}

