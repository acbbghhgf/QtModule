#include "mainwidget.h"
#include "ui_mainwidget.h"

mainWidget::mainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainWidget)
{
    ui->setupUi(this);
    this->move(0,0);
    this->resize(QSize(1024, 600));
    this->showFullScreen();
    this->setCursor(Qt::BlankCursor);
    setAutoFillBackground(true);
    setPalette(QPalette(Qt::white));
    this->grabKeyboard();
}

mainWidget::~mainWidget()
{
    delete ui;
}


void mainWidget::new_model_pic()
{
    standby_pic = QPixmap(QSize(1024, 600));
    standby_pic.fill(Qt::white);
    draw_locate_rect(standby_pic, 20, 20, 60, 900, 480);
    black_whit_demo(standby_pic, 0xE4, 0xE4, 0xE4);
}


void mainWidget::black_whit_demo(QPixmap &pix_one, unsigned char r_char, unsigned char g_char, unsigned char b_char)
{

    std::vector<unsigned char> file_char;
    file_char.push_back(r_char);
    file_char.push_back(g_char);
    file_char.push_back(b_char);

    std::vector<QColor> fcolor;

    draw_locate_rect(pix_one, 20, 20, 60, 900, 480);
    QPainter p;
    try {
        p.begin(&pix_one);
        p.setBrush(QBrush(QColor(0,0,0), Qt::SolidPattern));
        p.setPen(Qt::NoPen);
        p.drawRect(90, 80, 820, 400);
        for (int sy = 80; sy < 480; sy += 40)
        {
            for(int sx = 90; sx < 900 - (4 * 30 + 4 * 10) ; sx += (4 * 30 + 4*10))
            {
                std::vector<std::pair<int, int>> tmp;
                tmp.push_back(std::make_pair(sx, sy));
                tmp.push_back(std::make_pair(sx + 30 + 10, sy));
                tmp.push_back(std::make_pair(sx + 2 * 30 + 2 * 10, sy));
                tmp.push_back(std::make_pair(sx + 3 * 30 + 3 * 10, sy));

                int ret = encode_chars(file_char, fcolor);
                if(ret == -1)
                {
                    qDebug() << "encode char fail.";
                }
                for(auto it = fcolor.begin(); it != fcolor.end(); ++it)
                {
                    p.setBrush(QBrush(*it, Qt::SolidPattern));
                    p.setPen(Qt::NoPen);
                    p.drawRect(tmp[it - fcolor.begin()].first, tmp[it - fcolor.begin()].second, 30, 30);
                }
            }
        }
        p.end();

    } catch (...) {
        qDebug() << __func__;

    }
}

int mainWidget::make_pic(std::string &split_str, QPixmap &dst)
{
    dst = QPixmap(QSize(1024, 600));
    dst.fill(Qt::white);
    draw_locate_rect(dst, 20, 20, 60, 900, 480);
    black_whit_demo(dst, split_str[0], split_str[1], split_str[2]);
    if(dst.isNull())
        return -1;
    return 0;
}

void mainWidget::draw_locate_rect(QPixmap &pic,int start_x,int start_y,
                                  int out_len,int width,int height)
{
    std::vector<std::pair<int,int>> temp;
    temp.push_back(std::make_pair(start_x,start_y));
    temp.push_back(std::make_pair(start_x,start_y+height));
    temp.push_back(std::make_pair(start_x+width,start_y+height));
    temp.push_back(std::make_pair(start_x+width,start_y));
    try
    {

        QPainter p;
        p.begin(&pic);
        QBrush b(Qt::black,Qt::SolidPattern);
        QBrush c(Qt::white,Qt::SolidPattern);


        for(auto it = temp.begin();it!= temp.end();++it)
        {
            p.setBrush(b);
            p.drawRect(it->first,it->second,out_len,out_len);
            p.setBrush(c);
            p.drawRect(it->first+out_len/6,it->second+out_len/6,out_len*2/3,out_len*2/3);
            p.setBrush(b);
            p.drawRect(it->first+out_len/3,it->second+out_len/3,out_len/3,out_len/3);

        }
        p.end();
    }
    catch(...)
    {
        qDebug() << __func__ ;
    }
}


int mainWidget::encode_chars(std::vector<unsigned char> &file_content,std::vector<QColor> & color)
{
    if(file_content.size()!=3)
    {
        return -1;
    }


    unsigned char t1 = 0x0f;
    short low_four,high_four;
    std::vector<std::vector<int>> color_levels;
    color.clear();
    color.resize(4);

    for(auto it = file_content.cbegin();it!=file_content.cend();++it)
    {
        std::vector<int> temp;
        low_four = (*it) & t1;
        high_four = ((*it)>>4) & t1;

        temp.push_back( high_four/4);
        temp.push_back( high_four%4);
        temp.push_back( low_four/4);
        temp.push_back( low_four%4);
        color_levels.push_back(temp);
    }



    for(std::vector<int>::size_type i = 0;i<4;++i)
    {
        color[i].setRgb((color_levels[0])[i]==0?32:(color_levels[0])[i]==1?96:(color_levels[0])[i]==2?160:(color_levels[0])[i]==3?224:0,
                    (color_levels[1])[i]==0?32:(color_levels[1])[i]==1?96:(color_levels[1])[i]==2?160:(color_levels[1])[i]==3?224:0,
                    (color_levels[2])[i]==0?32:(color_levels[2])[i]==1?96:(color_levels[2])[i]==2?160:(color_levels[2])[i]==3?224:0);
    }
    return 0;
}



void mainWidget::init_draw_parameter(m_widget &one)
{
    start_x = one.start_x;
    start_y = one.start_y;
    four_blocks_col_num = one.four_blocks_col_num;
    four_blocks_row_num = one.four_blocks_row_num;
    draw_width = one.draw_width;
    draw_height = one.draw_height;
}


int mainWidget::modify_display_pic(display_mode mode, QPixmap input)
{
    switch (mode) {
    case SEND_READY_PIC:
        send_ready_pix = QPixmap(QSize(1024,600));
        send_ready_pix.fill(Qt::white);
        draw_locate_rect(send_ready_pix, 20, 20, 60, 900, 480);
        black_whit_demo(send_ready_pix, 0xE4, 0xE4, 0xE4);
        qDebug() << "display send ready pic";
        break;
    case SENDING_PIC:
        qDebug() << "modify display pic";
        sending_pic = input;
        if(sending_pic.isNull())
        {
            qDebug() << "sending pic error";
            return -1;
        }
        break;
    case STANDY_PIC:
        standby_pic = QPixmap(QSize(1024,600));
        standby_pic.fill(Qt::white);
        draw_locate_rect(standby_pic, 20, 20, 60, 900, 480);
        black_whit_demo(standby_pic, 0x00, 0x00, 0x00);
        qDebug() << "display standy pic";
        break;
    default:
        qDebug() << "modify display pic mode error";
        return -1;
    }
    current_mode = mode;
    update();
    return 0;
}


void mainWidget::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Q)
    {
       this->close();
       exit(0);
    }

    return QWidget::keyPressEvent(ev);
}

void mainWidget::paintEvent(QPaintEvent *)
{
    // add SoSum
    QPainter painter(this);
    switch (current_mode) {
    case SEND_READY_PIC:
        painter.drawPixmap(QPoint(0,0), send_ready_pix);
        qDebug() << "display standby_pic ";
        break;
    case SENDING_PIC:
        painter.drawPixmap(QPoint(0,0), sending_pic);
        qDebug() << "display standby_pic ";
        break;
    case STANDY_PIC:
        painter.drawPixmap(QPoint(0,0), standby_pic);
        qDebug() << "display standby_pic ";
        break;
    default:
        qDebug() << "mainwidget display mode error";
    }

}

