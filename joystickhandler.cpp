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

#define DEBUG_GAMEPAD 1
#define DEBUG_JOYSTICK 0
#define DEBUG_REMAP 0

JoystickHandler::JoystickHandler(QWidget *parent, int _hidType) : QThread()
{
    par = parent;
    hidType = _hidType;
    inverseKinematicMode = 0;
    verticalPlaneMode = 1;
    dJPitch = 0; dJRoll = 0; dJYaw = 0;

    if (hidType == THISIS_GAMEPAD)
    {
        // Create an instance of Joystick
        joystick = new Joystick(GAMEPAD_PATH);

        // Ensure that it was found and that we can use it
        if (!joystick->isFound())
        {
            qDebug() << "Gamepad: open failed";
        }
        else qDebug() << "Gamepad: opened successfully";

        mobility_tcp = new TcpClientHarbinger(nullptr, IP_ROVER, PORT_MOTORS_START, N_MOTORS);
        mobility_tcp->start();

        turretCam_tcp = new TcpClientHarbinger(nullptr, IP_ROVER, PORT_TURRET_CAM_START, TURRET_CAM_N_AXIS);
        turretCam_tcp->start();
    }

    else if (hidType == THISIS_JOYSTICK)
    {
        // Create an instance of Joystick
        joystick = new Joystick(JOYSTICK_PATH);

        // Ensure that it was found and that we can use it
        if (!joystick->isFound())
        {
            qDebug() << "Joystick: open failed";
        }
        else qDebug() << "Joystick: opened successfully";

        arm_tcp = new TcpClientHarbinger(nullptr, IP_ROVER, PORT_ARM_START, ARM_N_ACTUATORS);
        arm_tcp->start();

        /* ARM CAMERA init
        armCam_tcp = new TcpClientHarbinger(nullptr, IP_ROVER, PORT_ARM_START, ARM_N_ACTUATORS);
        armCam_tcp->start();
        /**/
    }
}

JoystickHandler::~JoystickHandler()
{

}

void JoystickHandler::run()
{
    while (true)
    {
        //qDebug() << " VALORE: >>>>>> " << this->getAxisValue(JOYSTICK_PITCH);

        // Restrict rate
        usleep(1000);

        // Attempt to sample an event from the joystick
        JoystickEvent event;

        if(hidType == THISIS_GAMEPAD)       ///// >>> GAMEPAD
        {
            if (joystick->sample(&event))
            {
                if (event.isButton())
                {
                    if (DEBUG_GAMEPAD) qDebug() << "Gamepad > Button " << event.number << " is " << (event.value == 0 ? "up" : "down");

                    switch (event.number)
                    {
                        case GAMEPAD_L2:
                        if (event.value == 0) turretCam_tcp->writeData16(TURRET_CAM_PAN, -1);
                        break;

                        case GAMEPAD_R2:
                        if (event.value == 0) turretCam_tcp->writeData16(TURRET_CAM_PAN, -1);
                        break;

                        default:
                        break;
                    }
                }
                else if (event.isAxis())
                {
                    axisesValues[event.number] = event.value;
                    if (DEBUG_GAMEPAD) qDebug() << "Gamepad > Axis " << event.number << " is at position " << event.value;



                    switch (event.number) {
                        case GAMEPAD_L3Y:
                        mobility_tcp->writeData16(MOTOR_FRONT_LEFT, 0.62*JoystickHandler::inputRemap(event.value, DEATHZONE_VAL, FULLZONE_VAL, LINEARITY_EXP));
                        mobility_tcp->writeData16(MOTOR_REAR_LEFT, 0.62*JoystickHandler::inputRemap(event.value, DEATHZONE_VAL, FULLZONE_VAL, LINEARITY_EXP));
                        break;

                        case GAMEPAD_R3Y:
                        mobility_tcp->writeData16(MOTOR_FRONT_RIGHT, 0.62*JoystickHandler::inputRemap(event.value, DEATHZONE_VAL, FULLZONE_VAL, LINEARITY_EXP));
                        mobility_tcp->writeData16(MOTOR_REAR_RIGHT, 0.62*JoystickHandler::inputRemap(event.value, DEATHZONE_VAL, FULLZONE_VAL, LINEARITY_EXP));
                        break;

                        // PAN L1-R!
                        // TILT L2-R2
                        //*TURRET CAMERA
                        case GAMEPAD_L1:
                        turretCam_tcp->writeData16(TURRET_CAM_PAN, 1);
                        break;

                        case GAMEPAD_R1:
                        turretCam_tcp->writeData16(TURRET_CAM_PAN, 1);
                        break;
                        /**/

                        default:
                        break;
                    }


                }
            }
        }

        else if (hidType == THISIS_JOYSTICK)       ///// >>> JOYSTICK
        {
            if (joystick->sample(&event))
            {
                if (event.isButton())
                {
                    if (DEBUG_JOYSTICK) qDebug() << "Joystick > Button " << event.number << " is " << (event.value == 0 ? "up" : "down");


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

                        case JOYSTICK_FIRE:
                        if (event.value == 0) verticalPlaneMode = 0;
                        else verticalPlaneMode = 1;
                        break;

                        case JOYSTICK_11:
                        inverseKinematicMode = 0;
                        break;

                        case JOYSTICK_12:
                        //inverseKinematicMode = 1;
                        break;
                    }

                }
                else if (event.isAxis())
                {
                    axisesValues[event.number] = event.value;
                    if (DEBUG_JOYSTICK) qDebug() << "Joystick > Axis " << event.number << " is at position " << event.value;
                    inverseKinematicMode=0; // TEST
                    if (inverseKinematicMode == 0)         // DIRECT KINEMATICS MODE ON
                    {
                        switch (event.number) {
                            case JOYSTICK_PITCH:
                            arm_tcp->writeData16(ARM_SHOULDER, event.value);
                            //bar1->setPerc(event.value);
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
                            else                           arm_tcp->writeData16(ARM_PINCH,      0);
                            break;

                            case JOYSTICK_ARROWLR:
                            arm_tcp->writeData16(ARM_WRIST_BEND, event.value);
                            break;

                            case JOYSTICK_ARROWUD:
                            arm_tcp->writeData16(ARM_WRIST_BEND, event.value);
                            break;
                        }
                    }

                    else                                   // INVERSE KINEMATICS MODE ON
                    {
                        // Get value from axis and update instance
                        switch (event.number) {
                            case JOYSTICK_PITCH:
                            if (verticalPlaneMode == 1) dJZ=event.value;
                            else dJPitch = event.value;
                            break;

                            case JOYSTICK_ROLL:
                            dJRoll = event.value;
                            break;

                            case JOYSTICK_YAW:
                            dJYaw = event.value;
                            break;
                        }

                        // Compute and send

                    }
                }
            }
        }
    }
}

int16_t JoystickHandler::getAxisValue(int axis)
{
    return axisesValues[axis];
}

bool JoystickHandler::getButtonState(int button)
{
    return buttonsState[button];
}

void JoystickHandler::putAxisValue(int axis, int16_t value)
{
    axisesValues[axis] = value;
    //par->update();
}

void JoystickHandler::putButtonState(int button, bool state)
{
    buttonsState[button] = state;
    //par->update();
}

int16_t JoystickHandler::inputRemap (int16_t x, float a, float b, int c)
{

    /*
    * To see the function
    * Copy this on Geogebra after creating three sliders (a, b, c)
    * Se(x < (-(1 + a)) / b, -1, (-(1 + a)) / b < x < (-a) / b, -abs((b x + a)^c), (-a) / b < x < a / b, 0, a / b < x < (1 + a) / b, (b x - a)^c, x > (1 + a) / b, 1)
    */

    float minFactor = a / b;
    float maxFactor = (1+a) / b;

    double ans = 0;
    double rel = (double) ((double) x / 32768);

    if (rel < -maxFactor)
    {
        ans = -1;
    }
    else if ( rel > -maxFactor && rel < -minFactor)
    {
        // -abs((b x + a)^c)
        ans = -(double) pow ( (double)(-std::abs(b*rel+ a)), (double)c);
    }
    else if ( rel > -minFactor && rel< minFactor)
    {
        ans = 0;
    }
    else if ( rel > minFactor && rel< maxFactor)
    {
        ans = (double) pow ( (double)(b*rel- a), (double)c);
    }
    else
    {
        ans = 1;
    }

    // ans range = [-1,1]

    if (DEBUG_REMAP) qDebug() << "REMAP\t\t\t\t\t\t" << ans  << "\t\t" << rel;

    return ans*32767;
}
