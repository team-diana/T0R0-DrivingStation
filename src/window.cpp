#include "window.h"

#include <QDebug>
#include <QString>
#include <QCoreApplication>
#include <QLabel>
#include <QKeyEvent>
#include <QBoxLayout>

//Gstreamer://
#include <QGlib/Connect>
#include <QGlib/Error>
#include <QGst/Pipeline>
#include <QGst/Bus>
#include <QGst/Message>
#include <QGst/ElementFactory>
#include <QGst/Pad>

#include <QGst/Ui/VideoWidget>

#include <QDialog>
//////////////

// Constructor
Window::Window(QWidget *parent) : QWidget(parent)
{
  this->setGeometry(0, 0, 1920, 1080);

  // set black background
  QPalette pal = palette();

	// Set backgroud color
	pal.setColor(QPalette::Background, QColor(14,14,14,255));
  this->setAutoFillBackground(true);
  this->setPalette(pal);


	// Show Team D.I.A.N.A. logo at bottom-right
  //add images to resources.qrc to use them//
  // http://doc.qt.io/qt-5/resources.html //
	QLabel *pixlogo = new QLabel(this);
  QPixmap pixmaplogo(":/Images/diana-logo-193x90.png");
	pixlogo->setPixmap(pixmaplogo.scaled(193, 90, Qt::KeepAspectRatio));
	pixlogo->setGeometry( this->width() - 238, this->height() - 120, 193, 90 );

  connected = false;

  m_videoWidget = new QGst::Ui::VideoWidget(this);
  m_videoWidget->setGeometry( 100, 100, 640, 480 );
}

Window::~Window(){
  //Gstremer://
  m_pipeline->setState(QGst::StateNull);
  m_videoWidget->stopPipelineWatch();
  m_pipeline.clear();
  /////////////
}

//GStreamer://
void Window::startVideo(){
	m_pipeline = QGst::Pipeline::create();
	QGst::ElementPtr rtpbin = QGst::ElementFactory::make("rtpbin");
	if (!rtpbin) {
			qFatal("Failed to create rtpbin");
	}
	m_pipeline->add(rtpbin);

  QGst::ElementPtr videosrc;
  try {
      videosrc = QGst::Bin::fromDescription(
          "udpsrc port=1234 ! application/x-rtp, encoding-name=JPEG, payload=26 ! rtpjpegdepay ! jpegdec ! xvimagesink"
      );
  } catch (const QGlib::Error & error) {
      qCritical() << error;
      qFatal("One ore more required elements are missing. Aborting...");
  }
  m_pipeline->add(videosrc);
  videosrc->link(rtpbin, "send_rtp_sink_2");

  //watch for the receiving side src pads
  QGlib::connect(rtpbin, "pad-added", this, &Window::onRtpBinPadAdded);
  //watch the bus
  m_pipeline->bus()->addSignalWatch();
  QGlib::connect(m_pipeline->bus(), "message::error", this, &Window::onBusErrorMessage);
  //switch to the video view and connect the video widget
  m_videoWidget->watchPipeline(m_pipeline);
  //go!
  m_pipeline->setState(QGst::StatePlaying);
}

void Window::onRtpBinPadAdded(const QGst::PadPtr & pad)
{
    QGst::ElementPtr bin;
    try {
        //recv_rtp_src_1_* -> session 1 - audio
        if (pad->name().startsWith(QLatin1String("recv_rtp_src_1"))) {
            bin = QGst::Bin::fromDescription(
                "rtpspeexdepay ! speexdec ! audioconvert ! autoaudiosink"
            );
        } else { //recv_rtp_src_2_* -> session 2 - video
            bin = QGst::Bin::fromDescription(
                "rtph264depay ! avdec_h264 ! videoconvert ! autovideosink"
            );
        }
    } catch (const QGlib::Error & error) {
        qCritical() << error;
        qFatal("One ore more required elements are missing. Aborting...");
    }
    m_pipeline->add(bin);
    bin->syncStateWithParent();
    pad->link(bin->getStaticPad("sink"));
}

void Window::onBusErrorMessage(const QGst::MessagePtr & msg)
{
    qCritical() << "Error from bus:" << msg.staticCast<QGst::ErrorMessage>()->error();
    //stop the call
    m_pipeline->setState(QGst::StateNull);
    m_videoWidget->stopPipelineWatch();
    m_pipeline.clear();
}
//////////////

void Window::keyPressEvent (QKeyEvent *keyevent) {
	switch ( keyevent->key() ) {
	        case Qt::Key_R:                               // reload
	            qDebug("Pressed R");
	            update();
	            break;
	        case Qt::key_Q:
              qDebug("Pressed Q")
	            key[0] = 1;
	            break;
         case Qt::key_Alt:
              qDebug("Pressed Alt")
              key[1] = 1;
              break;
         case Qt::key_Control:
              qDebug("Pressed Ctrl")
              key[2] = 1;
              break;

	    }

      if (key[0] && key[1] && key[2])
      {
        qDebug("Ctrl-Alt-Q all Pressed")
        QCoreApplication::quit();
      }
}

void Window::keyReleaseEvent (QKeyEvent *keyevent) {
  switch ( keyevent->key() ) {
        case Qt::key_Q:
            qDebug("Released Q")
            key[0] = 0;
            break;
        case Qt::key_Alt:
            qDebug("Released Alt")
            key[1] = 0;
            break;
        case Qt::key_Control:
            qDebug("Released Ctrl");
            key[2] = 0;
            break;

      }
}
