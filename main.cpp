#include <FEHLCD.h>
#include "Navigation.h"
#include "Sensor.h"
#include "Battery.h"
#include "Servo.h"
#include "LineFollowing.h"

int main() {
    test_navigation();

    // wait_for_light();

    // move_backward(20.0);
    // turn_right(45.0);

    // set_left_percent(20.0);
    // set_right_percent(20.0);

    // wait_for_light();

    // stop();

    // Sleep(1.0);

    // LCD.WriteLine(get_cds_reading());

    // move_forward(0.1);

    // Sleep(1.0);

    // LCD.WriteLine(get_cds_reading());

    // if (is_red()) {
    //     LCD.Clear(SCARLET);
    //     turn_right(20.0);
    //     move_forward(4);
    //     turn_left(25.0);

    //     //move_forward(3);
    //     set_left_percent(20.0);
    //     set_right_percent(20.0);
    //     Sleep(2.0);
    //     stop();

    //     // Starting reverse sequence
    //     move_backward(3);
    //     turn_right(38);
    //     move_backward(3);
    //     turn_right(38);
    //     move_backward(9.5);
    //     turn_right(70);
    // }
    // else if (is_blue()) {
    //     LCD.Clear(BLUE);
    //     turn_left(20.0);
    //     move_forward(3);
    //     turn_right(26.0);

    //     set_left_percent(20.0);
    //     set_right_percent(20.0);
    //     Sleep(2.0);
    //     stop();

    //     move_backward(3);
    //     turn_right(75);
    //     move_backward(7);
    //     turn_right(70);
    // }
    // else
    // {
    //     LCD.Clear(GREEN);
    //     LCD.WriteLine("ERROR: Did not read light value.");
    // }

    // Sleep(2.0);

    // move_forward(30, 50, 53);
    // Sleep(1.5);
    // move_backward(30, 50, 53);

    return 0;
}