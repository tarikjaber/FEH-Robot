#include "Servo.h"

FEHServo horizontal_servo(FEHServo::Servo1); 
FEHServo side_servo(FEHServo::Servo5); 
FEHServo back_servo(FEHServo::Servo7);

void calibrate_horizontal() {
    horizontal_servo.TouchCalibrate();
}

void calibrate_side() {
    side_servo.TouchCalibrate();
}

void calibrate_back() {
    back_servo.TouchCalibrate();
}

void set_up_servos() {
    horizontal_servo.SetMin(HORIZONTAL_SERVO_MIN);
    horizontal_servo.SetMax(HORIZONTAL_SERVO_MAX);
    side_servo.SetMin(SIDE_SERVO_MIN);
    side_servo.SetMax(SIDE_SERVO_MAX);
    back_servo.SetMin(BACK_SERVO_MIN);
    back_servo.SetMax(BACK_SERVO_MAX);

    reset_servos();
}

// All Arms
void reset_servos() {
    open_horizontal_arm();
    reset_back_arm();
    reset_horizontal_arm();
    reset_side_arm();
}

// Back Arm
void reset_back_arm() {
    back_servo.SetDegree(BACK_REST_DEGREE);
}

void set_back(double percent) {
    back_servo.SetDegree(percent * 180 / 100);
}

// Side Arm
void reset_side_arm() {
    side_servo.SetDegree(SIDE_REST_DEGREE);
}

void set_side(double percent) {
    side_servo.SetDegree(180 - percent * 180 / 100);
}

// Horizontal Arm
void open_horizontal_arm() {
    set_side(100);
}

void reset_horizontal_arm() {
    horizontal_servo.SetDegree(HORIZONTAL_REST_DEGREE);
}

void set_horizontal(double percent) {
    horizontal_servo.SetDegree(percent * 180 / 100);
}

