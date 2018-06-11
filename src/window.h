#ifndef WINDOW_H
#define WINDOW_H

#include <QKeyEvent>
#include <QWidget>
#include <QTcpSocket>
#include <QByteArray>

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
	void connectTcp();
	void readTcpData();
	void keyPressEvent(QKeyEvent *keyevent);
	void keyReleaseEvent (QKeyEvent *keyevent);
  int key[3]={0,0,0};

private:
  bool connected;
	QTcpSocket *_pSocket;
	QTcpSocket *pSocket;

	//UI://
	WindowUi *ui;
	///////

	void ChangeText_Button(int n, int pressed);
	void ChangeText_Axis(int n, int position);
};

#endif // WINDOW_H
