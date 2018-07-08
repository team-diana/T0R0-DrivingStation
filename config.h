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
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
///////////

//* IPs *//
#define IP_ROVER "127.0.0.1"
///////////

//* PORTS TO ROVER *//
#define PORT_MOBILITY_LEFT 50100
#define PORT_MOBILITY_RIGHT 50101
///////////


//* CAMERA *//
#define CAMERA_WIDTH 960
#define CAMERA_HEIGHT 600
///////////

//* JOYSTICK *//
#define JOYSTICK_PATH "/dev/input/js1"
///////////

//* GAMEPAD *//
#define GAMEPAD_PATH "/dev/input/js0"

#define DEATHZONE_VAL 0.05      // -val < x < val interval will give 0 as output
#define FULLZONE_VAL 0.05       // x < -val gives -1, x > val gives 1 as output
#define LINEARITY_EXP 0.05      // 1 for linear input, 2 for quadratic non-linear input, 3 ...
///////////

#endif // CONFIG_H
