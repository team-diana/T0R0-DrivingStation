#include "crossgraph.h"

CrossGraph::CrossGraph(QWidget *parent) : QWidget(parent)
{
    size = 220;
    x = 45;
    y= 35;
}

CrossGraph::~CrossGraph()
{

}

void CrossGraph::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(QColor(255, 255, 255, 255));

    painter.setBrush(QColor(45, 45, 45, 255));
    painter.drawRect(QRect(0, 0, this->width(), this->height()));

    // Background
    painter.setBrush(QColor(255, 255, 255, 255));
    painter.drawRect(QRect(0, 0, size, size));

    //painter.setPen(QColor(255, 0, 0, 255));
    //painter.drawText(QPoint(10,16), "DIANA");

    // Percentage bar
    painter.setBrush(QColor(255, 9, 9, 255));
    int xPixels = (int) ((double) size * ((double) ((double)(x) / 100.0) ));
    int yPixels = (int) ((double) size * ((double) ((double)(y) / 100.0) ));

    //qDebug() << ">>>>>>>>>>>>>>>>> PERC " << percPixels;
    painter.drawRect(QRect(0, size-xPixels, size, yPixels));
}

void CrossGraph::setX(int _perc)
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

    x = p;
    this->update();
}

void CrossGraph::setY(int _perc)
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

    y = p;
    this->update();
}
