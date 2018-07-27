#ifndef CROSSGRAPH_H
#define CROSSGRAPH_H

#include <QWidget>
#include <QPainter>


class CrossGraph : public QWidget
{
    Q_OBJECT

public:
    explicit CrossGraph(QWidget *parent = nullptr);
    ~CrossGraph() override;

    void setX(int _perc);
    void setY(int _perc);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    int size;
    int x, y;
};

#endif // CROSSGRAPH_H
