#include "Navigation.h"

FEHMotor left_motor(FEHMotor::Motor0, 9.0);
FEHMotor right_motor(FEHMotor::Motor1, 9.0);

DigitalEncoder left_encoder(FEHIO::P1_0);
DigitalEncoder right_encoder(FEHIO::P2_7);

//* Test Code
void test_navigation() {
    move_forward(12);
    LCD.WriteLine(left_encoder.Counts());
    LCD.WriteLine(right_encoder.Counts());
    Sleep(1.0);
    turn_right(90);
    LCD.WriteLine(left_encoder.Counts());
    LCD.WriteLine(right_encoder.Counts());
    Sleep(1.0);
    turn_left(90);
    LCD.WriteLine(left_encoder.Counts());
    LCD.WriteLine(right_encoder.Counts());
    Sleep(1.0);
    turn_left(90);
    LCD.WriteLine(left_encoder.Counts());
    LCD.WriteLine(right_encoder.Counts());
    Sleep(1.0);
    turn_right(90);
    LCD.WriteLine(left_encoder.Counts());
    LCD.WriteLine(right_encoder.Counts());
    Sleep(1.0);
    move_back(12);
    LCD.WriteLine(left_encoder.Counts());
    LCD.WriteLine(right_encoder.Counts());
}
//* Encoder Functions
void reset_encoder_counts() {
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
}

double inches_to_counts(double inches) {
    double circumference = M_PI * WHEEL_DIAMETER;
    double rotations = inches / circumference;
    double total_counts = rotations * TRANSITIONS_PER_REVOLUTION;

    return total_counts;
}

void move_counts(double counts, double left_speed, double right_speed) {
    double current_left_speed = left_speed;
    double current_right_speed = right_speed;

    set_left_percent(current_left_speed);
    set_right_percent(current_right_speed);

    int index = 0;

    while ((right_encoder.Counts() + left_encoder.Counts()) / 2 < counts) {
        if ((index % 100) == 50) {
            if (left_encoder.Counts() < right_encoder.Counts()) {
                //current_left_speed *= 1.001;
            } else if (left_encoder.Counts() > right_encoder.Counts()) {
                //current_left_speed *= 0.999;
            }
        }
        index++;
        set_left_percent(current_left_speed);
    }
}

//* Motor Percentage Manipulation
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

//* Turning
void turn_left(double degrees) {
    turn(-degrees);
}

void turn_right(double degrees) {
    turn(degrees);
}

void turn(double degrees) {
    reset_encoder_counts();
    
    double motor_percent = 20;
    
    // If degrees is negative then turn left
    // NOTE: Turning left is "negative" degrees. 
    // Turning right is "positive" degrees.
    if (degrees < 0) {
        motor_percent *= -1;
        degrees *= -1;
    }

    move_counts(degrees * COUNTS_PER_DEGREE, motor_percent, -motor_percent);
    stop();
}   

//* Motor Functions
// TODO Think about how to better implement this function
void turn_with_angle(double inches, double degrees) {
    double left_wheel_percent = STRAIGHT_SPEED_PERCENT;
    double right_wheel_percent = STRAIGHT_SPEED_PERCENT;
    
    double total_counts = inches_to_counts(inches);

    if (degrees > 0) {
        right_wheel_percent -= degrees;
    } else {
        left_wheel_percent -= degrees;
    }

    move_counts(total_counts, left_wheel_percent, right_wheel_percent);
    stop();
}

void move_forward(double inches) {
    move_forward(inches, STRAIGHT_SPEED_PERCENT, STRAIGHT_SPEED_PERCENT);
}

void move_forward(double inches, double speed) {
    move_forward(inches, speed, speed);
}

void move_forward(double inches, double left_speed, double right_speed) {
    reset_encoder_counts();
    
    double total_counts = inches_to_counts(inches);

    move_counts(total_counts, left_speed, right_speed);
    stop();
}

void move_back(double inches) {
    move_back(inches, STRAIGHT_SPEED_PERCENT, STRAIGHT_SPEED_PERCENT);
}

void move_back(double inches, double speed) {
    move_back(inches, speed, speed);
}

void move_back(double inches, double left_speed, double right_speed) {
    reset_encoder_counts();
    
    double total_counts = inches_to_counts(inches);

    move_counts(total_counts, -left_speed, -right_speed);
    stop();
}

void stop() {
    left_motor.Stop();
    right_motor.Stop();
}