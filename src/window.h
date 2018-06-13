#ifndef WINDOW_H
#define WINDOW_H

#include <QKeyEvent>
#include <QWidget>
#include <QTcpSocket>
#include <QByteArray>

#include "TcpClient.h"

#define XPOS_BATTGROUP 0
#define YPOS_BATTGROUP 0

class WindowUi;

//INPUT://
class Joystick;
//////////

class Window : public QWidget
{
	Q_OBJECT

public:
  explicit Window(QWidget *parent = 0);
	~Window();

	//INPUT://
	Joystick *jstick;
	//////////

public Q_SLOTS:
	//

protected:

	void keyPressEvent(QKeyEvent *keyevent);
	void keyReleaseEvent (QKeyEvent *keyevent);
  int key[3]={0,0,0};

private:

	TcpClient *left_client, *right_client;
	//UI://
	WindowUi *ui;
	///////

	void ChangeText_Button(int n, int pressed);
	void ChangeText_Axis(int n, int position);
};

#endif // WINDOW_H
