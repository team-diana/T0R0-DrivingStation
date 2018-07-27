#include "crossgraph.h"

CrossGraph::CrossGraph(QWidget *parent) : QWidget(parent)
{
    w = 12;
    h = 120;
    x = 45;
    y=35;
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

    // Background bar
    painter.setBrush(QColor(255, 255, 255, 255));
    painter.drawRect(QRect(0, 0, w, h));

    //painter.setPen(QColor(255, 0, 0, 255));
    //painter.drawText(QPoint(10,16), "DIANA");

    // Percentage bar
    painter.setBrush(QColor(255, 9, 9, 255));
    int percPixels = (int) ((double) h * ((double) ((double)(percentage) / 100.0) ));
    //qDebug() << ">>>>>>>>>>>>>>>>> PERC " << percPixels;
    painter.drawRect(QRect(0, h-percPixels, w, percPixels));
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

    percentage = p;
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

    percentage = p;
    this->update();
}
