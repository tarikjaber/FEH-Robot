#include "Servo.h"

void calibrate_front() {
    front_servo.TouchCalibrate();
}

void calibrate_side() {
    side_servo.TouchCalibrate();
}

void calibrate_back() {
    back_servo.TouchCalibrate();
}

void set_up_servos() {
    front_servo.SetMin(FRONT_SERVO_MIN);
    front_servo.SetMax(FRONT_SERVO_MAX);
    side_servo.SetMin(SIDE_SERVO_MIN);
    side_servo.SetMax(SIDE_SERVO_MAX);
    back_servo.SetMin(BACK_SERVO_MIN);
    back_servo.SetMax(BACK_SERVO_MAX);
}