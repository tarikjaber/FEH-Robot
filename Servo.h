#include <FEHServo.h>

#ifndef SERVO_H
#define SERVO_H

extern FEHServo horizontal_servo; 
extern FEHServo side_servo; 
extern FEHServo back_servo;

// Horizontal Servo
#define HORIZONTAL_SERVO_MIN 500
#define HORIZONTAL_SERVO_MAX 2400
#define HORIZONTAL_REST_DEGREE 40
// Side Servo
#define SIDE_SERVO_MIN 500
#define SIDE_SERVO_MAX 2400
#define SIDE_REST_DEGREE 10
// Back Servo
#define BACK_SERVO_MIN 500
#define BACK_SERVO_MAX 2400
#define BACK_REST_DEGREE 10

// Calibration and Set Up
void calibrate_horizontal();
void calibrate_side();
void calibrate_back();
void set_up_servos();
// All Arms
void reset_arms();
// Back Arm
void drop_back_arm();
void reset_back_arm();
// Side Arm
void drop_side_arm();
void reset_side_arm();
// Horizontal Arm
void slid_ticket();
void reset_horizontal_arm();

#endif
