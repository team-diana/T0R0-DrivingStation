#ifndef JOYSTICKDISPLAY_H
#define JOYSTICKDISPLAY_H

#include <QWidget>
#include <QPainter>

#include "bar.h"
#include "joystickhandler.h"

class JoystickDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit JoystickDisplay(QWidget *parent = nullptr);
    ~JoystickDisplay();
    Bar *bar1;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;


private:
    JoystickHandler *joystickhandler;
};

#endif // JOYSTICKDISPLAY_H
