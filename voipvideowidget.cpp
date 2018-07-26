#include "voipvideowidget.h"

#include <QDebug>
#include <QString>
#include <QPainter>

#include <QVBoxLayout>

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
VoipVideoWidget::VoipVideoWidget(QWidget *parent) : QWidget(parent)
{
    port = 5000;
    s_port = "5000";

    //A layout helps the videoWidget resize with the VoipVideoWidget
    QVBoxLayout *layout = new QVBoxLayout();

    //Gstremer://
    videoWidget = new QGst::Ui::VideoWidget;
    layout->addWidget(videoWidget);
    /////////////

    this->setLayout(layout);
}

void VoipVideoWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(QColor(255, 10, 10, 255));
    painter.setBrush(QColor(10, 10, 10, 255));
    painter.drawRect(0, 0, this->width(), this->height());
    painter.fillRect(QRect(0, 0, this->width(), this->height()), QColor(11, 250, 150, 255));
}

VoipVideoWidget::~VoipVideoWidget(){
    //Gstremer://
    stopPipeline();
    /////////////
}

void VoipVideoWidget::setPort(int p){
    port = p;
    s_port = QString::number(port);
}

//GStreamer://
void VoipVideoWidget::startPipeline(){
    pipeline = QGst::Pipeline::create();
    QGst::ElementPtr rtpbin = QGst::ElementFactory::make("rtpbin");
    if (!rtpbin) {
            qFatal("Failed to create rtpbin");
    }
    pipeline->add(rtpbin);

    QGst::ElementPtr videosrc;
  try {
      //Connect to video from udp using port
        videosrc = QGst::Bin::fromDescription(
                    "udpsrc port=" + s_port +
                    " ! application/x-rtp, encoding-name=JPEG, payload=26 ! rtpjpegdepay ! jpegdec ! xvimagesink"
                    );
    }
    catch (const QGlib::Error & error) {
        qCritical() << error;
        qFatal("One ore more required elements are missing. Aborting...");
    }
    pipeline->add(videosrc);
    videosrc->link(rtpbin, "send_rtp_sink_2");

    //watch for the receiving side src pads
    QGlib::connect(rtpbin, "pad-added", this, &VoipVideoWidget::onRtpBinPadAdded);
    //watch the bus
    pipeline->bus()->addSignalWatch();
    QGlib::connect(pipeline->bus(), "message::error", this, &VoipVideoWidget::onBusErrorMessage);
    //switch to the video view and connect the video widget
    videoWidget->watchPipeline(pipeline);
    //go!
    pipeline->setState(QGst::StatePlaying);
}

void VoipVideoWidget::onRtpBinPadAdded(const QGst::PadPtr & pad)
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
    pipeline->add(bin);
    bin->syncStateWithParent();
    pad->link(bin->getStaticPad("sink"));
}

void VoipVideoWidget::onBusErrorMessage(const QGst::MessagePtr & msg)
{
    qCritical() << "Error from bus:" << msg.staticCast<QGst::ErrorMessage>()->error();
    //stop the call
    stopPipeline();
}

void VoipVideoWidget::stopPipeline(){
    pipeline->setState(QGst::StateNull);
    videoWidget->stopPipelineWatch();
    pipeline.clear();
}
//////////////
