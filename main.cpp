#include <FEHLCD.h>
#include "Navigation.h"
#include "Sensor.h"
#include "Battery.h"
#include "Servo.h"
#include "LineFollowing.h"

void hit_jukebox_button();

int main() {
    move_forward(10);
    turn_right(45);
    move_forward(20, 60);

    return 0;
}

void hit_jukebox_button() {
    wait_for_light();

    move_back(20.0);
    turn_right(45.0);

    set_left_percent(20.0);
    set_right_percent(20.0);

    wait_for_light();

    stop();

    Sleep(1.0);

    LCD.WriteLine(get_cds_reading());

    move_forward(0.1);

    Sleep(1.0);

    LCD.WriteLine(get_cds_reading());

    if (is_red()) {
        LCD.Clear(SCARLET);
        turn_right(20.0);
        move_forward(4);
        turn_left(25.0);

        //move_forward(3);
        set_left_percent(20.0);
        set_right_percent(20.0);
        Sleep(2.0);
        stop();

        // Starting reverse sequence
        move_back(3);
        turn_right(38);
        move_back(3);
        turn_right(38);
        move_back(9.5);
        turn_right(70);
    }
    else if (is_blue()) {
        LCD.Clear(BLUE);
        turn_left(20.0);
        move_forward(3);
        turn_right(26.0);

        set_left_percent(20.0);
        set_right_percent(20.0);
        Sleep(2.0);
        stop();

        move_back(3);
        turn_right(75);
        move_back(7);
        turn_right(70);
    }
    else
    {
        LCD.Clear(GREEN);
        LCD.WriteLine("ERROR: Did not read light value.");
    }

    Sleep(2.0);

    move_forward(30, 50, 53);
    Sleep(1.5);
    move_back(30, 50, 53);
}