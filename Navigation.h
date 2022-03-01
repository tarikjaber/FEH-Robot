// Header Files
#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHLCD.h>
#include <cmath>

// Constants
#define WHEEL_DIAMETER 3
#define TRANSITIONS_PER_REVOLUTION 318
#define COUNTS_PER_DEGREE 2.20
#define STRAIGHT_SPEED_PERCENT 30.0
#define RIGHT_CORRECTION_FACTOR 1.05

// Motors
FEHMotor left_motor(FEHMotor::Motor0, 9.0);
FEHMotor right_motor(FEHMotor::Motor1, 9.0);

// Encoders
DigitalEncoder left_encoder(FEHIO::P1_0);
DigitalEncoder right_encoder(FEHIO::P2_7);

// Prototypes
void stop();
void reset_encoder_counts();
void turn_left(double);
void turn_right(double);
void set_both(double);
void set_left_percent(double);
void set_right_percent(double);
void turn(double);
double inches_to_counts(double);
void turn_with_angle(double, double);
void move_forward(double);
void move_forward(double, double);
void move_forward(double, double, double);
void move_back(double);
void move_back(double, double);
void move_back(double, double, double);
void test_navigation();