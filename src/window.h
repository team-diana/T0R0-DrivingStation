#ifndef WINDOW_H
#define WINDOW_H

#include <QKeyEvent>
#include <QLabel>

//Gstreamer://
#include <QGst/Pipeline>
#include <QGst/Ui/VideoWidget>
//////////////


#define XPOS_BATTGROUP 0
#define YPOS_BATTGROUP 0

class QBoxLayout;
class QLabel;


class Window : public QWidget
{
	Q_OBJECT

public:
  explicit Window(QWidget *parent = 0);
	~Window();

public Q_SLOTS:
	//Gstreamer://
	void startVideo();
	//////////////

protected:
	void keyPressEvent(QKeyEvent *e);

private:
  bool connected;
	//Gstreamer://
  QGst::PipelinePtr m_pipeline;
	QGst::Ui::VideoWidget *m_videoWidget;

	void onRtpBinPadAdded(const QGst::PadPtr & pad);
  void onBusErrorMessage(const QGst::MessagePtr & msg);
	//////////////
};

#endif // WINDOW_H
