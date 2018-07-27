#ifndef BAR_H
#define BAR_H

#include <QWidget>
#include <QPainter>

class Bar : public QWidget
{

    Q_OBJECT

public:
    //explicit Bar(QWidget *parent = nullptr, int _width = 10, int _height = 100);
    explicit Bar(QWidget *parent = nullptr, int _direction=0);
    ~Bar() override;

    void setPerc(int _perc);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    int w, h;
    int percentage;
    int direction;
};

#endif // BAR_H
