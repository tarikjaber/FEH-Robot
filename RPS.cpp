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
 * Pulse clockwise a short distance using time
 */
void pulse_clockwise(int percent, float seconds) 
{
    pulse_counterclockwise(-percent, seconds);
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
    while((RPS.X() >= 0) && (RPS.X() < x_coordinate - POSITION_ERROR || RPS.X() > x_coordinate + POSITION_ERROR))
    {
        if(RPS.X() > x_coordinate + POSITION_ERROR)
        {
            // Pulse the motors for a short duration in the correct direction
            pulse_forward(-power, PULSE_TIME);
        }
        else if(RPS.X() < x_coordinate - POSITION_ERROR)
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
    while((RPS.Y() >= 0) && (RPS.Y() < y_coordinate - POSITION_ERROR || RPS.Y() > y_coordinate + POSITION_ERROR))
    {
        if(RPS.Y() > y_coordinate + POSITION_ERROR)
        {
            // Pulse the motors for a short duration in the correct direction
            pulse_forward(-power, PULSE_TIME);
        }
        else if(RPS.Y() < y_coordinate - POSITION_ERROR)
        {
            // Pulse the motors for a short duration in the correct direction
           pulse_forward(power, PULSE_TIME);
        }
        LCD.WriteLine(RPS.Y());
        Sleep(RPS_WAIT_TIME_IN_SEC);
    }
}

/* 
 * Use RPS to move to the desired heading
 */
void correct_heading(float heading)
{
   while((RPS.Heading() >= 0) && (RPS.Heading() < heading - HEADING_ERROR || RPS.Heading() > heading + HEADING_ERROR))
    {
        if(RPS.Heading() > heading + HEADING_ERROR)
        {
            if (RPS.Heading() - heading > 180) {
                pulse_counterclockwise(PULSE_POWER, PULSE_TIME);
                // Testing if the heading is close to 0 (with a large value like 359.8 degrees)
                if (heading == 0 && (RPS.Heading() > 360 - HEADING_ERROR)) {
                    return;
                }
            } else {
                pulse_clockwise(PULSE_POWER, PULSE_TIME);
            }
        }
        else if(RPS.Heading() < heading - HEADING_ERROR)
        {
            // Pulse the motors for a short duration in the correct direction
            pulse_counterclockwise(PULSE_POWER, PULSE_TIME);
        }
        Sleep(RPS_WAIT_TIME_IN_SEC);
    }
}
