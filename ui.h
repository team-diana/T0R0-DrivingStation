#ifndef UI_H
#define UI_H

#include <QKeyEvent>
#include <QLabel>

//GAMEPAD//
#include "gamepad.h"

class VoipVideoWidget;

class WindowUi : public QWidget
{
    Q_OBJECT

public:
  explicit WindowUi(QWidget *parent = 0);
    ~WindowUi();

    QLabel *jstick_lbl;

public Q_SLOTS:
  //

protected:
  //

private:
    void CreateUI();

  //Gstreamer://
  VoipVideoWidget *camera1_videoWidget;
  //////////////

  //GAMEPAD://
  Gamepad *gamepad;
  //////////////
};

#endif // UI_H
