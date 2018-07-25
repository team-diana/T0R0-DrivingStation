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

#include "joystick.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <QString>
#include <sstream>
#include "unistd.h"

#include "inputmapping.h"

//QT://
#include <QDebug>
#include <QThread>
///////

/*
Joystick::Joystick(QObject *parent, int joystickNumber)
  : QThread(parent)
{
  std::stringstream sstm;
  sstm << "/dev/input/js" << joystickNumber;
  openPath(sstm.str());
}
*/

Joystick::Joystick(QObject *parent, std::string devicePath, bool blocking)
    : QThread(parent)
    , m_stop(false)
{
    openPath(devicePath, blocking);
}

void Joystick::openPath(std::string devicePath, bool blocking)
{
    // Open the device using either blocking or non-blocking
    _fd = open(devicePath.c_str(), blocking ? O_RDONLY : O_RDONLY | O_NONBLOCK);
}

bool Joystick::sample(JoystickEvent* event)
{
    int bytes = read(_fd, event, sizeof(*event));

    if (bytes == -1)
    return false;

    // NOTE if this condition is not met, we're probably out of sync and this
    // Joystick instance is likely unusable
    return bytes == sizeof(*event);
}

bool Joystick::isFound()
{
    return _fd >= 0;
}

//QT://
void Joystick::stop()
{
    m_stop = true;
}

void Joystick::run()
{
    //uint16_t data = 42;

    qDebug() << "\nJoystick: Started\n";

    // Ensure that it was found and that we can use it
    if (!this->isFound())
    {
        qDebug() << "Joystick: open failed.\n";
        exit(1);
    }

    while (true)
    {
        // Attempt to sample an event from the joystick
        JoystickEvent event;
        if (this->sample(&event) < 1)
        {
            if (event.isButton())
            {
                printf("Button %u is %s\n",
                event.number,
                event.value == 0 ? "up" : "down");

                switch (event.number) {
                case JOYSTICK_FIRE:
                    Q_EMIT fireButtonUpdate(event.value);
                    break;

                case JOYSTICK_THUMB:
                    Q_EMIT thumbButtonUpdate(event.value);
                    break;

                case JOYSTICK_3:
                    Q_EMIT ButtonUpdate3(event.value);
                    break;

                case JOYSTICK_4:
                    Q_EMIT ButtonUpdate4(event.value);
                    break;

                case JOYSTICK_5:
                    Q_EMIT ButtonUpdate5(event.value);
                    break;

                case JOYSTICK_6:
                    Q_EMIT ButtonUpdate6(event.value);
                    break;

                case JOYSTICK_7:
                    Q_EMIT ButtonUpdate7(event.value);
                    break;

                case JOYSTICK_8:
                    Q_EMIT ButtonUpdate8(event.value);
                    break;

                case JOYSTICK_9:
                    Q_EMIT ButtonUpdate9(event.value);
                    break;

                case JOYSTICK_10:
                    Q_EMIT ButtonUpdate10(event.value);
                    break;

                case JOYSTICK_11:
                    Q_EMIT ButtonUpdate11(event.value);
                    break;

                case JOYSTICK_12:
                    Q_EMIT ButtonUpdate12(event.value);
                    break;

                default:
                    break;
                }

                //Q_EMIT ButtonUpdate(event.number, event.value);   // DEPRECATED
            }

            if (event.isAxis())
            {
                //if(event.number == 0) {
                //  printf("Axis %u is at position %d\n", event.number, event.value);
                //data = (uint16_t) ~((unsigned int) event.value);
                //  printf("Data = %hu\n", data);


                //printf("Sending %hu\n", data);
                //socket->send16(data);
                //}

                switch (event.number) {
                case JOYSTICK_PITCH:
                    Q_EMIT pitchAxisUpdate(event.value);
                    break;

                case JOYSTICK_YAW:
                    Q_EMIT yawAxisUpdate(event.value);
                    break;

                case JOYSTICK_ROLL:
                    Q_EMIT rollAxisUpdate(event.value);
                    break;

                case JOYSTICK_THROTTLE:
                    Q_EMIT throttleAxisUpdate(event.value);
                    break;

                case JOYSTICK_ARROWLR:
                    Q_EMIT dpadLRAxisUpdate(event.value);
                    break;

                case JOYSTICK_ARROWUD:
                    Q_EMIT dpadUDAxisUpdate(event.value);
                    break;

                default:
                    break;
                }

                Q_EMIT AxisUpdate(event.number, event.value);   // DEPRECATED
            }

            //Stop thread:
            if (m_stop) break;

            // Restrict rate
            usleep(100000);
        }
    }
}
///////

Joystick::~Joystick()
{
    close(_fd);
}

std::ostream& operator<<(std::ostream& os, const JoystickEvent& e)
{
    os << "type=" << static_cast<int>(e.type)
       << " number=" << static_cast<int>(e.number)
       << " value=" << static_cast<int>(e.value);
    return os;
}
