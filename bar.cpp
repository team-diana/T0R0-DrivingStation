#include "bar.h"

#include <QDebug>

/*
Bar::Bar(QWidget *parent, int _width, int _height)
{
    w = _width;
    h = _height;
    percentage = 0;
}*/

Bar::Bar(QWidget *parent) : QWidget(parent)
{
    w = 12;
    h = 220;
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
    painter.setBrush(QColor(255, 255, 255, 255));
    painter.drawRect(QRect(0, 0, w, h));

    //painter.setPen(QColor(255, 0, 0, 255));
    //painter.drawText(QPoint(10,16), "DIANA");

    // Percentage bar
    painter.setBrush(QColor(255, 9, 9, 255));
    //double percPixels = ((double) (h) * ((double) ( (double)(percentage) / 100.0) ));
    int percPixels = (int) ((double) h * ((double) ((double)(percentage) / 100.0) ));


    //qDebug() << ">>>>>>>>>>>>>>>>> PERC " << percPixels;
    painter.drawRect(QRect(0, h-percPixels, w, percPixels));
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
