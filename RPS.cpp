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
    double error = x_coordinate - RPS.X();

    while (error > POSITION_ERROR) {
        double distance = error / sin(RPS.Heading());
        move_forward(distance);
        Sleep(RPS_WAIT_TIME_IN_SEC);
        error = x_coordinate - RPS.X();
    }
}

/* 
 * Use RPS to move to the desired y_coordinate based on the orientation of the QR code
 */
void correct_y(float y_coordinate)
{
    double error = y_coordinate - RPS.Y();

    while (error > POSITION_ERROR) {
        double distance = error / cos(RPS.Heading());
        move_forward(distance);
        Sleep(RPS_WAIT_TIME_IN_SEC);
        error = y_coordinate - RPS.Y();
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
            double error = RPS.Heading() - heading;
            if (error > 180) {
                // Testing if the heading is close to 0 (with a large value like 359.8 degrees)
                if (heading == 0 && (RPS.Heading() > 360 - HEADING_ERROR)) {
                    return;
                } else {
                    turn_left(360 - error);
                }
            } else {
                if (error > 1.0) {
                    turn_right(error);
                } else {
                    pulse_clockwise(PULSE_POWER, PULSE_TIME);
                }
            }
        }
        else if(RPS.Heading() < heading - HEADING_ERROR)
        {
            float error = heading - RPS.Heading();
            if (error > 180) {
                turn_right(360 - error);
            } else {
                if (error > 1.0) {
                    turn_left(error);
                } else {
                    // Pulse the motors for a short duration in the correct direction
                    pulse_counterclockwise(PULSE_POWER, PULSE_TIME);
                }
            }
        }
        Sleep(RPS_WAIT_TIME_IN_SEC);
    }
}
