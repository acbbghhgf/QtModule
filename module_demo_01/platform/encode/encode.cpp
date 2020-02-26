#include "encode.h"

unsigned char getXsChar(int a, int b, int c)
{
    unsigned char ch = 0;
    if (a > 15)
    {
        ch = c * 16 + c;
    }
    else
    {
        c = (a + b) % 16;
        ch = c * 16 + c;
    }
    return ch;
}

void charShow(int yuandian_row, int yuandian_column, int current_row, int current_column, int screen_width,
              int screen_height, int num_row, int num_column, unsigned char ch, QPixmap &p)
{
    int      x, y;
    QPainter painter;
    painter.begin(&p);
    // QPixmap test;
    painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));

    int four_blocks_width, one_block_width, four_blocks_height, one_block_height;
    four_blocks_width = screen_width / num_row;
    one_block_width = four_blocks_width / 2;
    four_blocks_height = screen_height / num_column;
    one_block_height = four_blocks_height / 2;

    x = yuandian_row + current_row * four_blocks_width;
    y = yuandian_column + current_column * four_blocks_height;

    int int_a = static_cast<int>(ch);

    for (int i = 0; i < 8; i++)
    {
        if (i < 4)
        {
            if ((int_a >> (i + 4)) & 0x00000001)
            {
                painter.drawRect(x + (i % 2) * one_block_width, y + (i / 2) * one_block_height, one_block_width,
                                 one_block_height);
            }
        }
        else
        {
            if ((int_a >> (i - 4)) & 0x00000001)
            {
                painter.drawRect(x + four_blocks_width + ((i - 4) % 2) * one_block_width,
                                 y + ((i - 4) / 2) * one_block_height, one_block_width, one_block_height);
            }
        }
    }

#if 0
    unsigned char cTemp;

    cTemp = ch / 16;

    int a[5], b, i;
    for (i = 0; i < 5; i++)
        a[i] = 0;

    i = 0;
    do
    {
        a[i] = cTemp % 2;
        i++;
        b = cTemp / 2;
        cTemp = b;
    } while (b != 0);

    for (i = 0; i < 4; i++)
    {
        if (a[i] == 1)
        {
            painter->drawRect(x + (i % 2) * one_block_width, y + (i / 2) * one_block_height, one_block_width, one_block_height);
        }
    }

    x = x1 + four_blocks_width + xx * four_blocks_width;
    y = y1 + yy * four_blocks_height;

    cTemp = ch % 16; //zijiediwei

    for (i = 0; i < 5; i++)
        a[i] = 0;
    i = 0;
    do
    {
        a[i] = cTemp % 2;
        i++;
        b = cTemp / 2;
        cTemp = b;
    } while (b != 0);

    for (i = 0; i < 4; i++)
    {
        if (a[i] == 1)
        {
            painter->drawRect(x + (i % 2) * one_block_width, y + (i / 2) * one_block_height, one_block_width, one_block_height);
        }
    }
#endif
    painter.end();
}

int jiajia(int y, int bl, int fw)
{
    int x;
    x = (y + bl) % fw;
    return x;
}
int jiejie(int y, int bl, int fw)
{
    int x;
    if (y < bl)
    {
        x = y + fw - bl;
    }
    else
    {
        x = y - bl;
    }
    return x;
}
