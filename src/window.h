#ifndef WINDOW_H
#define WINDOW_H

#include <QLabel>

#include <QString>

#define XPOS_BATTGROUP 0
#define YPOS_BATTGROUP 0

class Window : public QWidget
{
	Q_OBJECT

public:
    explicit Window(QRect screen, QWidget *parent = 0);

public slots:

protected:
	//void keyPressEvent(QKeyEvent *k) Q_DECL_OVERRIDE;

private:
    bool connected;

    // Custom elements
	//KeyPress *key_press_event;
};

#endif // WINDOW_H
