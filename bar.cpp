#include "bar.h"

/*
Bar::Bar(QWidget *parent, int _width, int _height)
{
    w = _width;
    h = _height;
    percentage = 0;
}*/

Bar::Bar(QWidget *parent, int _width, int _height, int _startPerc) : QWidget(parent)
{
    w = _width;
    h = _height;
    percentage = _startPerc;
}

Bar::~Bar()
{

}

void Bar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(QColor(255, 255, 255, 255));
    painter.setBrush(QColor(255, 255, 255, 255));
    //painter.drawLine(0, 0, w, h);
    painter.drawRect(QRect(0, 0, this->width(), this->height()));
    painter.drawText(QPoint(10,16), "DIANA");

}

void Bar::setPerc(int _perc)
{
    int p = _perc;

    if (p < 100)
    {

    }
    else if (p > 0)
    {

    }

    percentage = p;
    this->update();
}
