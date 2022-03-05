#include <FEHLCD.h>
#include "Navigation.h"
#include "Sensor.h"
#include "Battery.h"
#include "Servo.h"
#include "LineFollowing.h"

void hit_jukebox_button();
void deposit_tray();
void slide_ticket();

int main() {
    deposite_tray();
    slide_ticket();

    return 0;
}

void deposite_tray() {
    set_up_servos();
    back_servo.SetDegree(0);
    Sleep(1.0);
    horizontal_servo.SetDegree(0);
    wait_for_light();

    move_forward(13);
    turn_right(45);
    move_forward(40, 40);
    turn_right(65);
    move_back(13.5);
    horizontal_servo.SetDegree(160);
    turn_left(55);
    move_back(10);
    
    back_servo.SetDegree(160);
    move_forward(5);
}

void slide_ticket() {
    turn_right(90);
    back_servo.SetDegree(0);
    horizontal_servo.SetDegree(134);
    move_forward(20);
    turn_left(90);
    move_back(11);
    Sleep(2.0);
    horizontal_servo.SetDegree(10);
    Sleep(1.0);
    horizontal_servo.SetDegree(100);
    turn_right(20);

    move_forward(30);
    Sleep(.5);
    horizontal_servo.SetDegree(10);
    horizontal_servo.SetDegree(100);
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