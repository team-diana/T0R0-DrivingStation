#ifndef VIDEOCONTROLSDISPLAY_H
#define VIDEOCONTROLSDISPLAY_H

#include <QWidget>
#include <QPainter>
#include <QComboBox>
#include <QPushButton>
#include <QMqttClient>

#define VIDEO_CONTROLS_DISPLAY_POSX  1500
#define VIDEO_CONTROLS_DISPLAY_POSY   240
#define VIDEO_CONTROLS_DISPLAY_WIDTH  220
#define VIDEO_CONTROLS_DISPLAY_HEIGHT 285

class VideoControlsDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit VideoControlsDisplay(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;


public Q_SLOTS:
    void zedLeftSwitchRequest();
    void zedRightSwitchRequest();
    void turretCameraSwitchRequest();
    void armCameraSwitchRequest();

    void cvisionCacheActivation();
    void cvisionPanelActivation();

private:
    QMqttClient *camera_MQTTClient;

    QComboBox *menuVideo;
    QPushButton *zedRSwitchRequestButton, *zedLSwitchRequestButton, *turretCameraSwitchRequestButton, *armCameraSwitchRequestButton;
    QPushButton *cvisionCacheRecognitionButton, *cvisionPanelRecognitionButton;

    void  checkOrReconnect();
};

#endif // VIDEOCONTROLSDISPLAY_H
