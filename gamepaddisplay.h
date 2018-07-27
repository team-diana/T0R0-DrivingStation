#ifndef GAMEPADDISPLAY_H
#define GAMEPADDISPLAY_H

#include <QWidget>
#include <QPainter>

#include "bar.h"
#include "crossgraph.h"
#include "joystickhandler.h"

class GamepadDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit GamepadDisplay(QWidget *parent = nullptr);
    ~GamepadDisplay() override;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;


private:
    Bar *leftThrottle, *rightThrottle;
    //CrossGraph *cGraph;
    JoystickHandler *gamepadhandler;
};

#endif // GAMEPADDISPLAY_H
