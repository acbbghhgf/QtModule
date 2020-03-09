#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QGridLayout>
#include <QTextEdit>
#include <QLabel>
#include <QGraphicsView>
#include <QMouseEvent>
#include <resuleedit.h>
#include <QPaintEvent>
#include <opencv2/opencv.hpp>

class Drawwidget : public QWidget
{
    Q_OBJECT
public:
    explicit Drawwidget(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

    int getRvalue();
    int getGvalue();
    int getBvalue();

signals:
    void rgbUpdate();

public slots:
    void showPic(cv::Mat &pixSrc);

private:
    QPixmap *pix;
    cv::Mat src;
    ResuleEdit *mresule;
    int rvalue;
    int gvalue;
    int bvalue;
};

#endif // DRAWWIDGET_H
