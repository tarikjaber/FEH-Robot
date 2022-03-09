#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHLCD.h>
#include <cmath>

#ifndef NAVIGATION_H
#define NAVIGATION_H

#define WHEEL_DIAMETER 3
#define TRANSITIONS_PER_REVOLUTION 318
#define COUNTS_PER_DEGREE 2.40
#define STRAIGHT_SPEED_PERCENT 30.0
#define RIGHT_CORRECTION_FACTOR 1.018

extern FEHMotor left_motor;
extern FEHMotor right_motor;

extern DigitalEncoder left_encoder;
extern DigitalEncoder right_encoder;

enum Direction
{
    FORWARD,
    BACKWARD,
    RIGHT,
    LEFT
};

// Testing
void test_navigation();
// Encoders
double inches_to_counts(double);
void reset_encoder_counts();
void travel_counts(double);
// Turning
void turn_left(double);
void turn_right(double);
void turn(double);
// Motor
void set_both(double);
void set_left_percent(double);
void set_right_percent(double);
void turn_with_angle(double, double);
void stop();
void move_time(double, Direction);
void move_forward(double);
void move_forward(double, double);
void move_forward(double, double, double);
void move_back(double);
void move_back(double, double);
void move_back(double, double, double);

#endif
