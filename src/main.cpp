
#include "ui_voip.h"
#include <QApplication>
#include <QDialog>
#include <QGlib/Connect>
#include <QGlib/Error>
#include <QGst/Init>
#include <QGst/Pipeline>
#include <QGst/ElementFactory>
#include <QGst/Pad>
#include <QGst/Structure>
#include <QGst/Bus>
#include <QGst/Message>
class VoipExample : public QDialog
{
    Q_OBJECT
public:
    explicit VoipExample(QWidget *parent = 0);
    virtual ~VoipExample();
private Q_SLOTS:
    void on_startCallButton_clicked();
    void on_endCallButton_clicked();
    //keep the rtcp ports in sync with the rtp ports on the UI
    void on_audioRtpSrcSpinBox_valueChanged(int value) { m_ui.audioRtcpSrcSpinBox->setValue(value + 1); }
    void on_audioRtpDestSpinBox_valueChanged(int value) { m_ui.audioRtcpDestSpinBox->setValue(value + 1); }
    void on_videoRtpSrcSpinBox_valueChanged(int value) { m_ui.videoRtcpSrcSpinBox->setValue(value + 1); }
    void on_videoRtpDestSpinBox_valueChanged(int value) { m_ui.videoRtcpDestSpinBox->setValue(value + 1); }
private:
    void onRtpBinPadAdded(const QGst::PadPtr & pad);
    void onBusErrorMessage(const QGst::MessagePtr & msg);
private:
    Ui::VoipExample m_ui;
    QGst::PipelinePtr m_pipeline;
};
VoipExample::VoipExample(QWidget *parent)
    : QDialog(parent)
{
    m_ui.setupUi(this);
}
VoipExample::~VoipExample()
{
    //cleanup if the pipeline is still active
    if (m_pipeline) {
        on_endCallButton_clicked();
    }
}



void VoipExample::on_startCallButton_clicked()
{
	m_pipeline = QGst::Pipeline::create();
	QGst::ElementPtr rtpbin = QGst::ElementFactory::make("rtpbin");
	if (!rtpbin) {
			qFatal("Failed to create rtpbin");
	}
	m_pipeline->add(rtpbin);
	//video content
	if (m_ui.videoGroupBox->isChecked()) {
			//sending side
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
//			QGst::ElementPtr rtpudpsink = QGst::ElementFactory::make("udpsink");
//			if (!rtpudpsink) {
//					qFatal("Failed to create udpsink. Aborting...");
//			}
//			rtpudpsink->setProperty("port", m_ui.videoRtpDestSpinBox->value());
//			m_pipeline->add(rtpudpsink);
//			rtpbin->link("send_rtp_src_2", rtpudpsink);
			//receiving side
//			QGst::ElementPtr rtpudpsrc = QGst::ElementFactory::make("udpsrc");
//			if (!rtpudpsrc) {
//					qFatal("Failed to create udpsrc. Aborting...");
//			}
//			rtpudpsrc->setProperty("port", m_ui.videoRtpSrcSpinBox->value());
/*			rtpudpsrc->setProperty("caps", QGst::Caps::fromString("application/x-rtp,"
																														"media=(string)video,"
																														"clock-rate=(int)90000,"
																														"encoding-name=(string)H264"));
			m_pipeline->add(rtpudpsrc);
			rtpudpsrc->link(rtpbin, "recv_rtp_sink_2");
			//recv sink will be added when the pad becomes available
			//rtcp connection
			QGst::ElementPtr rtcpudpsrc = QGst::ElementFactory::make("udpsrc");
			rtcpudpsrc->setProperty("port", m_ui.videoRtcpSrcSpinBox->value());
			m_pipeline->add(rtcpudpsrc);
			rtcpudpsrc->link(rtpbin, "recv_rtcp_sink_2");
			QGst::ElementPtr rtcpudpsink = QGst::ElementFactory::make("udpsink");
			rtcpudpsink->setProperty("host", m_ui.remoteHostLineEdit->text());
			rtcpudpsink->setProperty("port", m_ui.videoRtcpDestSpinBox->value());
			rtcpudpsink->setProperty("sync", false);
			rtcpudpsink->setProperty("async", false);
			m_pipeline->add(rtcpudpsink);
			rtpbin->link("send_rtcp_src_2", rtcpudpsink);
	}
	//watch for the receiving side src pads*/
	QGlib::connect(rtpbin, "pad-added", this, &VoipExample::onRtpBinPadAdded);
	//watch the bus
	m_pipeline->bus()->addSignalWatch();
	QGlib::connect(m_pipeline->bus(), "message::error", this, &VoipExample::onBusErrorMessage);
	//switch to the video view and connect the video widget
	m_ui.stackedWidget->setCurrentIndex(1);
	m_ui.videoWidget->watchPipeline(m_pipeline);
	//go!
	m_pipeline->setState(QGst::StatePlaying);

}
void VoipExample::onRtpBinPadAdded(const QGst::PadPtr & pad)
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
void VoipExample::onBusErrorMessage(const QGst::MessagePtr & msg)
{
    qCritical() << "Error from bus:" << msg.staticCast<QGst::ErrorMessage>()->error();
    on_endCallButton_clicked(); //stop the call
}
void VoipExample::on_endCallButton_clicked()
{
    m_pipeline->setState(QGst::StateNull);
    m_ui.videoWidget->stopPipelineWatch();
    m_ui.stackedWidget->setCurrentIndex(0);
    m_pipeline.clear();
}
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QGst::init(&argc, &argv);
    VoipExample gui;
    gui.show();
		startVideo();
    return app.exec();
}
#include "main.moc"
