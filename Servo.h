#include <FEHServo.h>

#ifndef SERVO_H
#define SERVO_H

extern FEHServo horizontal_servo; 
extern FEHServo side_servo; 
extern FEHServo back_servo;

// Horizontal Servo
#define HORIZONTAL_SERVO_MIN 960
#define HORIZONTAL_SERVO_MAX 2289
#define HORIZONTAL_REST_DEGREE 0
#define HORIZONTAL_ACTIVE_DEGREE 180
// Side Servo
#define SIDE_SERVO_MIN 1600
#define SIDE_SERVO_MAX 2380
#define SIDE_REST_DEGREE 180
#define SIDE_ACTIVE_DEGREE 0
// Back Servo
#define BACK_SERVO_MIN 656
#define BACK_SERVO_MAX 1700
#define BACK_REST_DEGREE 0
#define BACK_ACTIVE_DEGREE 180

// Calibration and Set Up
void calibrate_horizontal();
void calibrate_side();
void calibrate_back();
void set_up_servos();
// All Arms
void reset_servos();
// Back Arm
void drop_back_arm();
void reset_back_arm();
void set_back_percent(double);
// Side Arm
void drop_side_arm();
void reset_side_arm();
void set_side_percent(double);
// Horizontal Arm
void swipe_horizontal();
void open_horizontal_arm();
void reset_horizontal_arm();
void set_horizontal_percent(double);

#endif
