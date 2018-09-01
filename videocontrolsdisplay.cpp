#include "videocontrolsdisplay.h"

#include <QDebug>

VideoControlsDisplay::VideoControlsDisplay(QWidget *parent) : QWidget(parent)
{

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
}

void VideoControlsDisplay::zedRightSwitchRequest()
{
    qDebug() << "zedRightSwitchRequest";
}

void VideoControlsDisplay::turretCameraSwitchRequest()
{
    qDebug() << "turretCameraSwitchRequest";
}

void VideoControlsDisplay::armCameraSwitchRequest()
{
    qDebug() << "armCameraSwitchRequest";
}


void VideoControlsDisplay::cvisionCacheActivation()
{
    qDebug() << "cvisionCacheActivation";
}

void VideoControlsDisplay::cvisionPanelActivation()
{
    qDebug() << "cvisionPanelActivation";
}
