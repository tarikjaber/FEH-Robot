#include <FEHLCD.h>
#include "Navigation.h"
#include "Sensor.h"
#include "Battery.h"
#include "Servo.h"
#include "LineFollowing.h"
#include "RPS.h"

void hit_jukebox_button();
void deposit_tray();
void slide_ticket();
void flip_burger();
void flip_ice_cream();

int main() {
    // Set Up
    RPS.InitializeTouchMenu();
    set_up_servos();

    // Body
    flip_burger();
    flip_ice_cream();

    // Resetting servos and exiting main
    reset_servos();
    return 0;
}

void flip_burger() {
    // Wait for light and drive up ramp
    wait_for_light();
    move_forward(13);
    turn_right(45);
    side_servo.SetDegree(180);
    move_forward(40, 40);
    // Correcting the y-coordinate of the robot using RPS
    correct_y(68);
    // Turning into burger tray and Correction x-coordinate
    turn_right(90);
    correct_x(26);
    side_servo.SetDegree(0);
    move_forward(4);
    // Lifting burger tray and flipping
    side_servo.SetDegree(90);
    move_forward(4);
}

void flip_ice_cream() {
    // Moving back and lifting side arm, and Correcting x-coordinate
    move_back(10);
    side_servo.SetDegree(180);
    correct_x(20);
    // Getting into position and flipping the ice cream lever
    turn_left(45);
    move_back(6);
    side_servo.SetDegree(110);
}

void deposit_tray() {
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