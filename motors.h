#ifndef MOTORS_H
#define MOTORS_H

#include <QWidget>

//* SINGLE MOTOR *//
class Motor : public QWidget
{
    Q_OBJECT

public:
    explicit Motor (QWidget *parent = nullptr, int16_t _throttle = 0);
    ~Motor ();

    int16_t readThrottle ();
    void writeThrottle (int16_t _thrtl);

//public Q_SIGNALS:

//public Q_SLOTS:

private:
    int16_t throttle;
};

#endif // MOTORS_H
