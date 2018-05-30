#ifndef WINDOW_H
#define WINDOW_H

#include <QKeyEvent>
#include <QLabel>

#define XPOS_BATTGROUP 0
#define YPOS_BATTGROUP 0

class QBoxLayout;
class QLabel;

//LibVLC://
class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;
///////////

class Window : public QWidget
{
	Q_OBJECT

public:
    explicit Window(QRect screen, QWidget *parent = 0);
		~Window();

public Q_SLOTS:
	void openLocal();
	void openUrl();

protected:
	void keyPressEvent(QKeyEvent *k);
	void keyReleaseEvent (QKeyEvent *k);
  int key[3]={0,0,0};
	//ciao

private:
    bool connected;
		//LibVLC://
		VlcInstance *_instance;
		VlcMedia *_media;
		VlcMediaPlayer *_player;
		///////////
};

#endif // WINDOW_H
