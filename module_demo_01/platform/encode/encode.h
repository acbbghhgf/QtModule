#ifndef ENCODE_H
#define ENCODE_H
#include <QPainter>
#include <QPixmap>

void          charShow(int x1, int y1, int xx, int yy, int w, int h, int ww, int hh, unsigned char ch, QPixmap &p);
unsigned char getXsChar(int a, int b, int c);
int           jiajia(int y, int bl, int fw);
int           jiejie(int y, int bl, int fw);
#endif // ENCODE_H
