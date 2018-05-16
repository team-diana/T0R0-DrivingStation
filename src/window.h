#ifndef WINDOW_H
#define WINDOW_H

#include <QKeyEvent>
#include <QLabel>

#define XPOS_BATTGROUP 0
#define YPOS_BATTGROUP 0

class Window : public QWidget
{
	Q_OBJECT

public:
    explicit Window(QRect screen, QWidget *parent = 0);

public slots:

protected:
	void keyPressEvent(QKeyEvent *e);

private:
    bool connected;
};

#endif // WINDOW_H
