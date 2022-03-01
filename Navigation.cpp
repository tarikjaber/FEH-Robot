#include "Navigation.h"

void reset_encoder_counts() {
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
}

void turn_left(double degrees) {
    turn(-degrees);
}

void turn_right(double degrees) {
    turn(degrees);
}

void set_both(double percent) {
    set_right_percent(percent);
    set_left_percent(percent);
}

void set_right_percent(double percent) {
    right_motor.SetPercent(percent * RIGHT_CORRECTION_FACTOR);
}

void set_left_percent(double percent) {
    left_motor.SetPercent(-percent);
}

void turn(double degrees) {
    reset_encoder_counts();
    
    double motor_percent = 20;
    
    // If degrees is negative then turn left
    // NOTE: Turning left is negative degrees. 
    // Turning right is positive degrees.
    if (degrees < 0) {
        motor_percent *= -1;
        degrees *= -1;
    }

    set_left_percent(motor_percent);
    set_right_percent(-motor_percent);

    while ((right_encoder.Counts() + left_encoder.Counts()) / 2 < degrees * COUNTS_PER_DEGREE) {}

    stop();
}   

double inches_to_counts(double inches) {
    double circumference = M_PI * WHEEL_DIAMETER;
    double rotations = inches / circumference;
    double total_counts = rotations * TRANSITIONS_PER_REVOLUTION;

    return total_counts;
}

void turn_with_angle(double inches, double degrees) {
    double left_wheel_percent = STRAIGHT_SPEED_PERCENT;
    double right_wheel_percent = STRAIGHT_SPEED_PERCENT;
    
    double total_counts = inches_to_counts(inches);

    if (degrees > 0) {
        right_wheel_percent -= degrees;
    } else {
        left_wheel_percent -= degrees;
    }
    
    set_left_percent(left_wheel_percent);
    set_right_percent(right_wheel_percent);

    while ((right_encoder.Counts() + left_encoder.Counts()) / 2 < total_counts) {}

    stop();
}

void move_forward(double inches) {
    move_forward(inches, STRAIGHT_SPEED_PERCENT);
}

void move_forward(double inches, double speed) {
    reset_encoder_counts();
    
    double total_counts = inches_to_counts(inches);
    
    set_right_percent(speed);
    set_left_percent(speed);
    
    while ((right_encoder.Counts() + left_encoder.Counts()) / 2 < total_counts) {}

    stop();
}

void move_forward(double inches, double left_speed, double right_speed) {
    reset_encoder_counts();
    
    double total_counts = inches_to_counts(inches);
    
    set_left_percent(left_speed);
    set_right_percent(right_speed);
    
    while ((right_encoder.Counts() + left_encoder.Counts()) / 2 < total_counts) {}

    stop();
}

void move_back(double inches) {
    move_back(inches, STRAIGHT_SPEED_PERCENT);
}

void move_back(double inches, double speed) {
    reset_encoder_counts();
    
    double total_counts = inches_to_counts(inches);
    
    set_left_percent(-speed);
    set_right_percent(-speed);
    
    while ((right_encoder.Counts() + left_encoder.Counts()) / 2 < total_counts) {}
    
    stop();
}

void move_back(double inches, double left_speed, double right_speed) {
    reset_encoder_counts();
    
    double total_counts = inches_to_counts(inches);
    
    set_left_percent(-left_speed);
    set_right_percent(-right_speed);
    
    while ((right_encoder.Counts() + left_encoder.Counts()) / 2 < total_counts) {}
    
    stop();
}

void stop() {
    left_motor.Stop();
    right_motor.Stop();
}