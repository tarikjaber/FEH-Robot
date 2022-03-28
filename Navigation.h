#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHLCD.h>
#include <FEHSD.h>
#include <cmath>
#include <string>

#ifndef NAVIGATION_H
#define NAVIGATION_H

#define WHEEL_DIAMETER 3
#define TRANSITIONS_PER_REVOLUTION 318
#define COUNTS_PER_DEGREE 2.40
#define STRAIGHT_SPEED_PERCENT 30.0
#define RIGHT_CORRECTION_FACTOR 1.0
#define EPSILON 0.01

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
void write_counts();
// Encoders
double inches_to_counts(double inches);
void reset_encoder_counts();
void travel_counts(double counts);
// Turning
void turn_left(double degrees);
void turn_right(double degrees);
void turn(double degrees);
// Motor
void set_both(double percent);
void set_left(double percent);
void set_right(double percent);
void turn_with_angle(double counts, double angle);
void stop();
void move_time(double time, Direction direction);
void move_forward(double inches);
void move_forward(double inches, double motor_percent);
void move_forward(double inches, double left_percent, double right_percent);
void move_back(double);
void move_back(double, double);
void move_back(double, double, double);
// Double Equality
bool are_same(double d1, double d2);

#endif
