#include "RPS.h"
#include "Navigation.h"

/**
 * Returns an integer representing the ice cream flavor to flip
 */
int get_ice_cream() {
    return RPS.GetIceCream();
}

/**
 * Pulses the robot forward.
 */ 
void pulse_forward(int percent, float seconds) 
{
    // Set both motors to desired percent
    set_both(percent);

    // Wait for the correct number of seconds
    Sleep(seconds);

    // Turn off motors
    stop();
}

/*
 * Pulse counterclockwise a short distance using time
 */
void pulse_counterclockwise(int percent, float seconds) 
{
    // Set both motors to desired percent
    set_right(percent);
    set_left(-percent);

    // Wait for the correct number of seconds
    Sleep(seconds);

    // Turn off motors
    stop();
}

/* 
 * Use RPS to move to the desired x_coordinate based on the orientation of the QR code
 */
void correct_x(float x_coordinate)
{
    // Determine the direction of the motors based on the orientation of the QR code 
    int power = PULSE_POWER;

    // "Minus Orientation"
    if (RPS.Heading() >= 90 && RPS.Heading() <= 270) {
        power = -PULSE_POWER;
    }

    // Check if receiving proper RPS coordinates and whether the robot is within an acceptable range
    while((RPS.X() >= 0) && (RPS.X() < x_coordinate - 1 || RPS.X() > x_coordinate + 1))
    {
        if(RPS.X() > x_coordinate + 1)
        {
            // Pulse the motors for a short duration in the correct direction
            pulse_forward(-power, PULSE_TIME);
        }
        else if(RPS.X() < x_coordinate - 1)
        {
            // Pulse the motors for a short duration in the correct direction
            pulse_forward(power, PULSE_TIME);
        }
        Sleep(RPS_WAIT_TIME_IN_SEC);
    }
}

/* 
 * Use RPS to move to the desired y_coordinate based on the orientation of the QR code
 */
void correct_y(float y_coordinate)
{
    // Determine the direction of the motors based on the orientation of the QR code
    int power = PULSE_POWER;

    // "Minus Orientation"
    if (RPS.Heading() >= 180) {
        power = -PULSE_POWER;
    }

    // Check if receiving proper RPS coordinates and whether the robot is within an acceptable range
    while((RPS.Y() >= 0) && (RPS.Y() < y_coordinate - 0.6 || RPS.Y() > y_coordinate + 0.6))
    {
        if(RPS.Y() > y_coordinate + 0.6)
        {
            // Pulse the motors for a short duration in the correct direction
            pulse_forward(-power, PULSE_TIME);
        }
        else if(RPS.Y() < y_coordinate - 0.6)
        {
            // Pulse the motors for a short duration in the correct direction
           pulse_forward(power, PULSE_TIME);
        }
        Sleep(RPS_WAIT_TIME_IN_SEC);
    }
}

/* 
 * Use RPS to move to the desired heading
 */
void correct_heading(float heading)
{
   while((RPS.Heading() >= 0) && (RPS.Heading() < heading - 0.6 || RPS.Heading() > heading + 0.6))
    {
        if(RPS.Heading() > heading + 0.6)
        {
            // Pulse the motors for a short duration in the correct direction
            pulse_counterclockwise(-PULSE_POWER, PULSE_TIME);
            if (RPS.Heading() > 355 && heading == 0) {
                pulse_counterclockwise(PULSE_POWER, PULSE_TIME);
            }
        }
        else if(RPS.Heading() < heading - 0.6)
        {
            // Pulse the motors for a short duration in the correct direction
            pulse_counterclockwise(PULSE_POWER, PULSE_TIME);
        }
        Sleep(RPS_WAIT_TIME_IN_SEC);
    }
}
