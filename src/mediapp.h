
#ifndef MEDIAAPP_H
#define MEDIAAPP_H

#include <QTimer>
#include <QWidget>
#include <QStyle>

class Player;
class QBoxLayout;
class QLabel;
class QSlider;
class QToolButton;
class QTimer;

class MediaApp : public QWidget
{
    Q_OBJECT
public:
    MediaApp(QWidget *parent = 0);
    ~MediaApp();

    void openFile(const QString & fileName);
private Q_SLOTS:
    void open();
    void toggleFullScreen();

    void onStateChanged();
    void onPositionChanged();

    void setPosition(int position);

    void showControls(bool show = true);
    void hideControls() { showControls(false); }
protected:
    void mouseMoveEvent(QMouseEvent *event);

private:
    QToolButton *initButton(QStyle::StandardPixmap icon, const QString & tip,
                            QObject *dstobj, const char *slot_method, QLayout *layout);
    void createUI(QBoxLayout *appLayout);

    QString m_baseDir;
    Player *m_player;
    QToolButton *m_openButton;
    QToolButton *m_fullScreenButton;
    QToolButton *m_playButton;
    QToolButton *m_pauseButton;
    QToolButton *m_stopButton;
    QSlider *m_positionSlider;
    QSlider *m_volumeSlider;
    QLabel *m_positionLabel;
    QLabel *m_volumeLabel;
    QTimer m_fullScreenTimer;
};
#endif
