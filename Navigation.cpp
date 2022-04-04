#include "Navigation.h"

using namespace std;

FEHMotor left_motor(FEHMotor::Motor0, 9.0);
FEHMotor right_motor(FEHMotor::Motor1, 9.0);

DigitalEncoder left_encoder(FEHIO::P2_7);
DigitalEncoder right_encoder(FEHIO::P1_0);

// Double Equality
bool are_same(double d1, double d2) {
    return fabs(d1 - d2) < EPSILON;
}

// Test Code
void write_counts() {
    LCD.Write("Right: ");
    LCD.WriteLine(right_encoder.Counts());
    LCD.Write("Left:  ");
    LCD.WriteLine(left_encoder.Counts());
}

void test_navigation() {
    // Forward 12 inches
    move_forward(25);
    LCD.WriteLine("Forward______________");
    write_counts();
    Sleep(1.0);
    // 90 degree right turn
    turn_right(90);
    LCD.WriteLine("Right________________");
    write_counts();
    Sleep(1.0);
    // 90 degree left turn
    turn_left(90);
    LCD.WriteLine("Left_________________");
    write_counts();
    Sleep(1.0);
    // 90 degree left turn
    turn_left(90);
    LCD.WriteLine("Left_________________");
    write_counts();
    Sleep(1.0);
    // 90 degree right turn
    turn_right(90);
    LCD.WriteLine("Right________________");
    write_counts();
    Sleep(1.0);
    // Back 12 inches
    move_back(25);
    LCD.WriteLine("Back_________________");
    write_counts();
    Sleep(1.0);
}
// Encoder Functions
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
    set_right(right_speed);
    set_left(left_speed);

    while ((right_encoder.Counts() + left_encoder.Counts()) / 2 < counts) {
        double correction_factor = (right_encoder.Counts() + 0.01) / (left_encoder.Counts() + 0.01);
        set_left(left_speed * correction_factor * correction_factor);
    }
}

// Motor Percentage Manipulation
void set_both(double percent) {
    set_right(percent);
    set_left(percent);
}

void set_right(double percent) {
    right_motor.SetPercent(percent * RIGHT_CORRECTION_FACTOR);
}

void set_left(double percent) {
    left_motor.SetPercent(-percent);
}

void turn_left(double degrees) {
    turn(-degrees, TURN_MOTOR_PERCENT);
}

void turn_left(double degrees, double percent) {
    turn(-degrees, percent);
}

void turn_right(double degrees) {
    turn(degrees, TURN_MOTOR_PERCENT);
}

void turn_right(double degrees, double percent) {
    turn(degrees, percent);
}

void turn(double degrees, double percent) {
    reset_encoder_counts();
    
    double motor_percent = percent;
    
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

// Motor Functions
void turn_with_angle(double inches, double degrees) {
    double left_wheel_percent = STRAIGHT_SPEED_PERCENT;
    double right_wheel_percent = STRAIGHT_SPEED_PERCENT;
    
    double total_counts = inches_to_counts(inches);

    if (degrees > 0) {
        right_wheel_percent -= degrees;
    } else {
        left_wheel_percent -= degrees;
    }

    set_left(left_wheel_percent);
    set_right(right_wheel_percent);

    while ((left_encoder.Counts() + right_encoder.Counts()) / 2 < total_counts) {}

    stop();
}

// Forward Functions
void move_time(double time, Direction direction) {
    if (direction == FORWARD) {
        set_both(STRAIGHT_SPEED_PERCENT);
    } else if (direction == BACKWARD) {
        set_left(-STRAIGHT_SPEED_PERCENT);
        set_right(-STRAIGHT_SPEED_PERCENT * 1.10);
    } else if (direction == LEFT) {
        set_right(STRAIGHT_SPEED_PERCENT);
        set_left(-STRAIGHT_SPEED_PERCENT);
    } else if (direction == RIGHT) {
        set_right(-STRAIGHT_SPEED_PERCENT);
        set_left(STRAIGHT_SPEED_PERCENT);
    }

    Sleep(time);

    stop();
}

void move_forward(double inches) {
    if (inches >= 0) {
        move_forward(inches, STRAIGHT_SPEED_PERCENT, STRAIGHT_SPEED_PERCENT);
    } else {
        move_back(inches, STRAIGHT_SPEED_PERCENT, STRAIGHT_SPEED_PERCENT);
    }
}

void move_forward(double inches, double speed) {
    move_forward(inches, speed, speed);
}

void move_forward(double inches, double left_speed, double right_speed) {
    reset_encoder_counts();
    
    double total_counts = inches_to_counts(inches);

    set_left(left_speed);
    set_right(right_speed);

    while ((left_encoder.Counts() + right_encoder.Counts()) / 2 < total_counts) {}
    stop();
}

// Backward Functions
void move_back(double inches) {
    if (inches >= 0) {
        move_back(inches, STRAIGHT_SPEED_PERCENT, STRAIGHT_SPEED_PERCENT);
    } else {
        move_forward(inches, STRAIGHT_SPEED_PERCENT, STRAIGHT_SPEED_PERCENT);
    }
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