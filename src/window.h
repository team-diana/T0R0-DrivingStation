#ifndef WINDOW_H
#define WINDOW_H

#include <QKeyEvent>
#include <QWidget>

#define XPOS_BATTGROUP 0
#define YPOS_BATTGROUP 0

class WindowUi;

class Window : public QWidget
{
	Q_OBJECT

public:
  explicit Window(QWidget *parent = 0);
	~Window();

public Q_SLOTS:
	//

protected:
	void keyPressEvent(QKeyEvent *keyevent);
	void keyReleaseEvent (QKeyEvent *keyevent);
  int key[3]={0,0,0};

private:
  bool connected;

	//UI://
	WindowUi *ui;
	///////
};

#endif // WINDOW_H
