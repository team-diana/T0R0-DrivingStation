#include "videocontrolsdisplay.h"
#include "config.h"

#include <QDebug>
#include <QtCore/QDateTime>

VideoControlsDisplay::VideoControlsDisplay(QWidget *parent) : QWidget(parent)
{
    camera_MQTTClient = new QMqttClient(this);
    camera_MQTTClient->setHostname(MQTT_BROKER_IP);
    camera_MQTTClient->setPort(MQTT_BROKER_PORT);
    camera_MQTTClient->connectToHost();

    connect(camera_MQTTClient, SIGNAL (stateChanged()), this, SLOT (checkOrReconnect();));
}

void VideoControlsDisplay::paintEvent(QPaintEvent *)
{

    QPainter painter(this);

    QLinearGradient m_gradient(0,0,0,VIDEO_CONTROLS_DISPLAY_HEIGHT);
    QColor textColor(230,230,230);

    m_gradient.setColorAt(0.0, QColor(10, 10, 10, 255));
    m_gradient.setColorAt(1.0, QColor(10, 10, 10, 255));
    painter.fillRect(QRect(0, 0, VIDEO_CONTROLS_DISPLAY_WIDTH, VIDEO_CONTROLS_DISPLAY_HEIGHT), m_gradient);

    QColor baseColorTheme (251, 172, 50, 255);
    painter.setPen(baseColorTheme);
    painter.drawText(1, 17, "Video Controls");

    painter.setBrush(QColor(0,0,0,0));
    painter.drawRect(0, 0, VIDEO_CONTROLS_DISPLAY_WIDTH, VIDEO_CONTROLS_DISPLAY_HEIGHT);

    // Video Stream Switch Buttons
    zedRSwitchRequestButton = new QPushButton ("ZED Left", this);
    zedRSwitchRequestButton->setGeometry(10, 25, 100, 30);
    zedRSwitchRequestButton->show();
    connect(zedRSwitchRequestButton, SIGNAL (released()), this, SLOT (zedLeftSwitchRequest()));

    zedLSwitchRequestButton = new QPushButton ("ZED Right", this);
    zedLSwitchRequestButton->setGeometry(110, 25, 100, 30);
    zedLSwitchRequestButton->show();
    connect(zedLSwitchRequestButton, SIGNAL (released()), this, SLOT (zedRightSwitchRequest()));

    turretCameraSwitchRequestButton = new QPushButton ("Turret Camera", this);
    turretCameraSwitchRequestButton->setGeometry(10, 65, 100, 30);
    turretCameraSwitchRequestButton->show();
    connect(turretCameraSwitchRequestButton, SIGNAL (released()), this, SLOT (turretCameraSwitchRequest()));

    armCameraSwitchRequestButton = new QPushButton ("Arm Camera", this);
    armCameraSwitchRequestButton->setGeometry(110, 65, 100, 30);
    armCameraSwitchRequestButton->show();
    connect(armCameraSwitchRequestButton, SIGNAL (released()), this, SLOT (armCameraSwitchRequest()));


    painter.setPen(textColor);
    painter.drawText(10, 138, "Computer Vision Recognition");

    cvisionCacheRecognitionButton = new QPushButton ("Cache", this);
    cvisionCacheRecognitionButton->setGeometry(10, 145, 100, 30);
    cvisionCacheRecognitionButton->show();
    connect(cvisionCacheRecognitionButton, SIGNAL (released()), this, SLOT (cvisionCacheActivation()));

    cvisionPanelRecognitionButton = new QPushButton ("Panel", this);
    cvisionPanelRecognitionButton->setGeometry(110, 145, 100, 30);
    cvisionPanelRecognitionButton->show();
    connect(cvisionPanelRecognitionButton, SIGNAL (released()), this, SLOT (cvisionPanelActivation()));
}

void VideoControlsDisplay::zedLeftSwitchRequest()
{
    qDebug() << "zedLeftSwitchRequest";
    checkOrReconnect();

    camera_MQTTClient->publish(QString("cam/zedL"), QString("1").toUtf8());
}

void VideoControlsDisplay::zedRightSwitchRequest()
{
    qDebug() << "zedRightSwitchRequest";
    checkOrReconnect();

    camera_MQTTClient->publish(QString("cam/zedR"), QString("1").toUtf8());
}

void VideoControlsDisplay::turretCameraSwitchRequest()
{
    qDebug() << "turretCameraSwitchRequest";
    checkOrReconnect();

    camera_MQTTClient->publish(QString("cam/turret"), QString("1").toUtf8());
}

void VideoControlsDisplay::armCameraSwitchRequest()
{
    qDebug() << "armCameraSwitchRequest";
    checkOrReconnect();

    camera_MQTTClient->publish(QString("cam/arm"), QString("1").toUtf8());
}


void VideoControlsDisplay::cvisionCacheActivation()
{
    qDebug() << "cvisionCacheActivation";
    checkOrReconnect();

    camera_MQTTClient->publish(QString("cv/cache"), QString("1").toUtf8());
}

void VideoControlsDisplay::cvisionPanelActivation()
{
    qDebug() << "cvisionPanelActivation";
    checkOrReconnect();

    camera_MQTTClient->publish(QString("cv/panel"), QString("1").toUtf8());
}

void VideoControlsDisplay::checkOrReconnect()
{
    if (camera_MQTTClient->state() == 0)
    {
        qDebug() << "MQTT cameras: Reconnecting";
        camera_MQTTClient->connectToHost();
        qDebug() << "MQTT cameras: Reconnected";

        QString diagnosticsTopic ("diagnostics");
        QString connectionMessage = "["
                + QDateTime::currentDateTime().toString()
                + "] Driving Station/Cameras: Connected to MQTT Broker";

        if (camera_MQTTClient->publish(diagnosticsTopic, connectionMessage.toUtf8()) == -1) qDebug() << "MQTT PUBLISH ERROR";
        else qDebug() << "MQTT PUBLISHED";
    }
}
