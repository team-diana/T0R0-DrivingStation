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

#include <QDebug>
#include <QPainter>

#include "joystickhandler.h"
#include "config.h"
#include "inputmapping.h"

JoystickHandler::JoystickHandler(QWidget *parent) : QThread()
{
    // Create an instance of Joystick
    joystick = new Joystick("/dev/input/js0");

    // Ensure that it was found and that we can use it
    if (!joystick->isFound())
    {
        qDebug() << "Joystick: open failed";
    }

    arm_tcp = new TcpHarbinger(nullptr, IP_ROVER, PORT_ARM_START, ARM_N_ACTUATORS);
    arm_tcp->start();
}

JoystickHandler::~JoystickHandler()
{

}

void JoystickHandler::run()
{
    while (true)
    {
        // Restrict rate
        usleep(1000);

        // Attempt to sample an event from the joystick
        JoystickEvent event;
        if (joystick->sample(&event))
        {
            if (event.isButton())
            {
                qDebug() << "Button " << event.number << " is " << (event.value == 0 ? "up" : "down");

                switch (event.number) {
                    // First wrist rotary gear
                    case JOYSTICK_3:
                        if (event.value) arm_tcp->writeData16(ARM_WRIST_ROT1, -32768);
                        else         arm_tcp->writeData16(ARM_WRIST_ROT1, 0);
                        break;

                    case JOYSTICK_4:
                        if (event.value) arm_tcp->writeData16(ARM_WRIST_ROT1, 32767);
                        else         arm_tcp->writeData16(ARM_WRIST_ROT1, 0);
                        break;

                    // Second wrist rotary gear
                    case JOYSTICK_5:
                        if (event.value) arm_tcp->writeData16(ARM_WRIST_ROT2, -32768);
                        else         arm_tcp->writeData16(ARM_WRIST_ROT2, 0);
                        break;

                    case JOYSTICK_6:
                        if (event.value) arm_tcp->writeData16(ARM_WRIST_ROT2, 32767);
                        else         arm_tcp->writeData16(ARM_WRIST_ROT2, 0);
                        break;
                }
            }
            else if (event.isAxis())
            {
                qDebug() << "Axis " << event.number << " is at position " << event.value;

                switch (event.number) {
                    case JOYSTICK_PITCH:
                        arm_tcp->writeData16(ARM_SHOULDER, event.value);
                        bar1->setPerc(event.value);
                        break;

                    case JOYSTICK_ROLL:
                        arm_tcp->writeData16(ARM_ELBOW, event.value);
                        break;

                    case JOYSTICK_YAW:
                        arm_tcp->writeData16(ARM_SLEAWINGGEAR, event.value);
                        break;

                    case JOYSTICK_THROTTLE:
                        if      (event.value < -30000) arm_tcp->writeData16(ARM_PINCH, -32768);
                        else if (event.value >  30000) arm_tcp->writeData16(ARM_PINCH,  32767);
                        else                        arm_tcp->writeData16(ARM_PINCH,      0);
                        break;

                    case JOYSTICK_ARROWLR:
                        arm_tcp->writeData16(ARM_WRIST_BEND, event.value);
                        break;

                    case JOYSTICK_ARROWUD:
                        arm_tcp->writeData16(ARM_WRIST_BEND, event.value);
                        break;
                    }
            }
        }
    }
}
