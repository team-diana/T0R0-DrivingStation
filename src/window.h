#ifndef WINDOW_H
#define WINDOW_H

#include <QKeyEvent>
#include <QLabel>

#define XPOS_BATTGROUP 0
#define YPOS_BATTGROUP 0

class Player;
class QBoxLayout;
class QLabel;

class Window : public QWidget
{
	Q_OBJECT

public:
    explicit Window(QRect screen, QWidget *parent = 0);
		~Window();

		void openFile(const QString & filename);
public Q_SLOTS:
	//void onPositionChanged();

protected:
	void keyPressEvent(QKeyEvent *e);

private:
    bool connected;
		//Video player test:
		Player *player;
		QLabel *label;
};

#endif // WINDOW_H
