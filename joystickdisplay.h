#ifndef JOYSTICKDISPLAY_H
#define JOYSTICKDISPLAY_H

#include <QWidget>
#include <QPainter>

#include "bar.h"
#include "crossgraph.h"
#include "joystickhandler.h"

class JoystickDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit JoystickDisplay(QWidget *parent = nullptr);
    ~JoystickDisplay() override;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;


private:
    Bar *bar1;
    CrossGraph *cGraph;
    JoystickHandler *joystickhandler;
};

#endif // JOYSTICKDISPLAY_H
