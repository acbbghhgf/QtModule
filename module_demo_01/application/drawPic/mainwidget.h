#ifndef __MAINWIDGET_H
#define __MAINWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <QWidget>
#include <deque>
#include <sstream>
#include <string>
#include <QKeyEvent>
#include <vector>
#include "platform/encode/encode.h"
#include <QDebug>
//#include "main.h"

typedef struct m_widget{
    int start_x;
    int start_y;
    int draw_width;
    int draw_height;
    int four_blocks_row_num;
    int four_blocks_col_num;
}m_widget_t;

enum display_mode{
    SEND_READY_PIC,
    SENDING_PIC,
    STANDY_PIC
};

namespace Ui {
class mainWidget;
}

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit mainWidget(QWidget *parent = nullptr);
    ~mainWidget();

    void paintEvent(QPaintEvent*);
    void init_draw_parameter(m_widget& one);
    void                 new_model_pic();
    int make_pic(std::string &split_str, QPixmap &dst);
    int modify_display_pic(display_mode mode, QPixmap input = QPixmap(QSize(1024, 600)));


protected:
    virtual void keyPressEvent(QKeyEvent *ev);

private:
    void black_whit_demo(QPixmap &pix_one, unsigned char r_char, unsigned char g_char, unsigned char b_char);
    void            draw_locate_rect(QPixmap & pic,int start_x,int start_y, int out_len,int width,int height);
    int encode_chars(std::vector<unsigned char> &file_content,std::vector<QColor> & color);

private:
    Ui::mainWidget *ui;
    QPixmap standby_pic;
    QPixmap sending_pic;
    QPixmap send_ready_pix;
    display_mode current_mode;
    int              start_x; // 90
    int              start_y; // 80
    int              four_blocks_row_num;
    int              four_blocks_col_num;
    int              draw_width;
    int              draw_height;
};

#endif // MAINWIDGET_H
