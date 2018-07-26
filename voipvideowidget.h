#ifndef VOIPVIDEOWIDGET_H
#define VOIPVIDEOWIDGET_H

//Gstreamer://
#include <QGst/Pipeline>
#include <QGst/Ui/VideoWidget>
//////////////

class QString;

class VoipVideoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VoipVideoWidget(QWidget *parent = 0);
    ~VoipVideoWidget();

    //Gstreamer://
    void startPipeline();

    void setPort(int p);

    void stopPipeline();
    //////////////


public Q_SLOTS:
    //

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    int port;
    QString s_port;

    //Gstreamer://
    QGst::PipelinePtr pipeline;
    QGst::Ui::VideoWidget *videoWidget;

    void onRtpBinPadAdded(const QGst::PadPtr & pad);
    void onBusErrorMessage(const QGst::MessagePtr & msg);
    //////////////

};

#endif // VOIPVIDEOWIDGET_H
