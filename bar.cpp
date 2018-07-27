#include "bar.h"

#include <QDebug>

/*
Bar::Bar(QWidget *parent, int _width, int _height)
{
    w = _width;
    h = _height;
    percentage = 0;
}*/

Bar::Bar(QWidget *parent, int _direction) : QWidget(parent)
{
    direction = _direction;

    switch (direction)
    {
        case 0:
            w = 12;
            h = 220;
        break;

        case 1:
            h = 12;
            w = 220;
        break;
    }

    percentage = 50;
}

Bar::~Bar()
{

}

void Bar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(QColor(255, 255, 255, 255));

    painter.setBrush(QColor(45, 45, 45, 255));
    painter.drawRect(QRect(0, 0, this->width(), this->height()));

    // Background bar
    painter.setBrush(QColor(210, 210, 210, 255));
    painter.drawRect(QRect(0, 0, w, h));

    //painter.setPen(QColor(255, 0, 0, 255));
    //painter.drawText(QPoint(10,16), "DIANA");

    // Percentage bar
    painter.setBrush(QColor(255, 9, 9, 255));

    int percPixels;
    switch (direction)
    {
        case 0:
            percPixels = (int) ((double) h * ((double) ((double)(percentage) / 100.0) ));
            painter.drawRect(QRect(0, h-percPixels, w, percPixels));
        break;

        case 1:
            percPixels = (int) ((double) w * ((double) ((double)(percentage) / 100.0) ));
            painter.drawRect(QRect(0, 0, percPixels, h));
        break;
    }

}

void Bar::setPerc(int _perc)
{
    int p = _perc;

    if (p >= 100)
    {
        p=100;
    }
    else if (p <= 0)
    {
        p=0;
    }

    percentage = p;
    this->update();
}
