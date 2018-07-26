/****************************************************************************
**
** T0-R0 Driving Station Configuration
**
** This file contains the main configuration of T0-R0 Rover Driving Station.
** Modify here to set up all main variables of this code.
**
****************************************************************************/

#ifndef CONFIG_H
#define CONFIG_H

//* WINDOW SIZE *//
#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1080
///////////

//* IPs *//
#define IP_ROVER "127.0.0.1"
//#define IP_MISSIONCONTROL "127.0.0.1"
///////////

//* MOTORS *//
#define PORT_MOTORS_START 50100
#define N_MOTORS 4

#define MOTOR_FRONT_LEFT  1
#define MOTOR_FRONT_RIGHT 0
#define MOTOR_REAR_RIGHT  3
#define MOTOR_REAR_LEFT   2


#define PORT_MOBILITY_FRONTLEFT  50101
#define PORT_MOBILITY_REARLEFT   50102
#define PORT_MOBILITY_REARRIGHT  50103
///////////

//* ARM *//
#define PORT_ARM_START   50150
#define ARM_N_ACTUATORS  7

#define ARM_SLEAWINGGEAR 0
#define ARM_SHOULDER     1
#define ARM_ELBOW        2
#define ARM_WRIST_ROT1   3
#define ARM_WRIST_BEND   4
#define ARM_WRIST_ROT2   5
#define ARM_PINCH        6
///////////

//* PORTS FROM MISSION CONTROL *//
#define PORT_MOBILITYCONTROLS_ACK 50050
///////////

//* CAMERA *//
#define CAMERA_WIDTH  960
#define CAMERA_HEIGHT 600
///////////

//** HID **//
#define THISIS_GAMEPAD  0
#define THISIS_JOYSTICK 1
///////////

//* GAMEPAD *//
#define GAMEPAD_PATH "/dev/input/js0"

#define DEATHZONE_VAL 0.07      // -val < x < val interval will give 0 as output
#define FULLZONE_VAL  1.1        // x < -val gives -1, x > val gives 1 as output
#define LINEARITY_EXP 2         // 1 for linear input, 2 for quadratic non-linear input, 3 ...
///////////

//* JOYSTICK *//
#define JOYSTICK_PATH "/dev/input/js1"
///////////

#endif // CONFIG_H
