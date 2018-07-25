// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Copyright Drew Noakes 2013-2016

#ifndef __JOYSTICK_HH__
#define __JOYSTICK_HH__

#include <QString>
#include <QThread>
#include <QObject>
#include <iostream>

#define JS_EVENT_BUTTON 0x01 // button pressed/released
#define JS_EVENT_AXIS   0x02 // joystick moved
#define JS_EVENT_INIT   0x80 // initial state of device

/**
 * Encapsulates all data relevant to a sampled joystick event.
 */
class JoystickEvent
{
public:
    /** Minimum value of axes range */
    static const short MIN_AXES_VALUE = -32768;

    /** Maximum value of axes range */
    static const short MAX_AXES_VALUE = 32767;

    /**
    * The timestamp of the event, in milliseconds.
    */
    unsigned int time;

    /**
    * The value associated with this joystick event.
    * For buttons this will be either 1 (down) or 0 (up).
    * For axes, this will range between MIN_AXES_VALUE and MAX_AXES_VALUE.
    */
    short value;

    /**
    * The event type.
    */
    unsigned char type;

    /**
    * The axis/button number.
    */
    unsigned char number;

    /**
    * Returns true if this event is the result of a button press.
    */
    bool isButton()
    {
        return (type & JS_EVENT_BUTTON) != 0;
    }

    /**
    * Returns true if this event is the result of an axis movement.
    */
    bool isAxis()
    {
        return (type & JS_EVENT_AXIS) != 0;
    }

    /**
    * Returns true if this event is part of the initial state obtained when
    * the joystick is first connected to.
    */
    bool isInitialState()
    {
        return (type & JS_EVENT_INIT) != 0;
    }
};

/**
 * Stream insertion function so you can do this:
 *    cout << event << endl;
 */
std::ostream& operator<<(std::ostream& os, const JoystickEvent& e);

/**
 * Represents a joystick device. Allows data to be sampled from it.
 */
class Joystick : public QThread
{
    Q_OBJECT

private:
    void openPath(std::string devicePath, bool blocking=false);

    int _fd;

    //QT://
    bool m_stop;
    ///////

protected:
    //QT://
    void run() override;
    ///////

public:
    ~Joystick();

    /**
    * Initialises an instance for the joystick with the specified,
    * zero-indexed number.
    Joystick(QObject *parent = 0, int joystickNumber=0);
    */

    /**
    * Joystick objects cannot be copied
    * Joystick(QObject *parent = 0, Joystick const&) = delete;
    */

    /**
    * Joystick objects can be moved
    * Joystick(QObject *parent = 0, Joystick &&) = default;
    */

    /**
    * Initialises an instance for the joystick device specified and provide
    * the option of blocking I/O.
    */
    Joystick(QObject *parent = 0, std::string devicePath="null", bool blocking=false);

    /**
    * Returns true if the joystick was found and may be used, otherwise false.
    */
    bool isFound();

    /**
    * Attempts to populate the provided JoystickEvent instance with data
    * from the joystick. Returns true if data is available, otherwise false.
    */
    bool sample(JoystickEvent* event);

    //QT://

public Q_SLOTS:
    void stop();

    Q_SIGNALS:
    void pitchAxisUpdate(int position);
    void yawAxisUpdate(int position);
    void rollAxisUpdate(int position);
    void throttleAxisUpdate(int position);

    void dpadLRAxisUpdate(int position);
    void dpadUDAxisUpdate(int position);

    void fireButtonUpdate(int pressed);
    void thumbButtonUpdate(int pressed);
    void ButtonUpdate3(int pressed);
    void ButtonUpdate4(int pressed);
    void ButtonUpdate5(int pressed);
    void ButtonUpdate6(int pressed);
    void ButtonUpdate7(int pressed);
    void ButtonUpdate8(int pressed);
    void ButtonUpdate9(int pressed);
    void ButtonUpdate10(int pressed);
    void ButtonUpdate11(int pressed);
    void ButtonUpdate12(int pressed);

    //void ButtonUpdate(int n, int pressed);   // DEPRECATED
    //void AxisUpdate(int n, int position);    // DEPRECATED
    ///////
};

#endif
