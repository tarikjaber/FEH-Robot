#include <FEHRPS.h>

#ifndef RPS_H
#define RPS_H

// RPS Delay time
#define RPS_WAIT_TIME_IN_SEC 0.35

// Shaft encoding counts for CrayolaBots
#define COUNTS_PER_INCH 40.5
#define COUNTS_PER_DEGREE 2.48

// Defines for pulsing the robot
#define PULSE_TIME 0.07
#define PULSE_POWER 20

// Define for the motor power
#define POWER 30

// Orientation of QR Code
#define PLUS 0
#define MINUS 1

// Delay of Position and Heading
#define HEADING_ERROR 0.5
#define POSITION_ERROR 0.25

// Function Prototypes
int get_ice_cream();
void correct_x(float);
void correct_y(float);
void correct_heading(float);
void pulse_counterclockwise(int, float);
void pulse_clockwise(int, float);

#endif