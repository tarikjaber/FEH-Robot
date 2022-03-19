#include <FEHLCD.h>
#include "Navigation.h"
#include "Sensor.h"
#include "Battery.h"
#include "Servo.h"
#include "LineFollowing.h"
#include "RPS.h"

void initialize();
void hit_jukebox_button();
void deposit_tray();
void slide_ticket();
void flip_burger();
void flip_ice_cream();
void flip_right_ice_cream();
void hit_final_button();

int main() {
    // Set Up
    initialize();

    // Body
    flip_right_ice_cream();
    hit_final_button();

    // Resetting servos and exiting main
    reset_servos();
    return 0;
}

void flip_right_ice_cream() {
    // Angle towards ramp
    move_forward(10);
    turn_right(45);
    // Go up the ramp
    move_forward(30, 30);
    // Turning to get right of the ice cream levers
    turn_left(45);
    move_forward(6);
    // Getting angled with levers
    turn_right(45);
    move_forward(5);
    turn_right(45);
    // Getting ice cream flavor
    int flavor = get_ice_cream();
    // Raising side arm to maximum
    set_side_percent(0);
    // Calculating necessary distance to reach lever depending on the flavor
    int distance = flavor * 3 + 1.5;
    move_forward(distance);
    // Lowering the arm, moving back to wait, and lifting the lever
    set_side_percent(40);
    Sleep(0.8);
    set_side_percent(0);
    move_back(1.5);
    Sleep(7.0);
    set_side_percent(60);
    move_forward(1.5);
    set_side_percent(80);
    // Moving back to initial location should
    move_back(distance);
}

void hit_final_button() {
    // Angling with the ramp
    turn_left(135);
    move_back(15);
    turn_left(90);
    // Going down the ramp
    move_forward(30);
    // Hitting final button
    turn_left(45);
    move_forward(15);
}

void flip_burger() {
    // Wait for light and drive up ramp
    wait_for_light();
    move_forward(13);
    turn_right(48);
    Sleep(0.5);
    side_servo.SetDegree(180);
    move_forward(45.2, 50);
    Sleep(1.0);
    // Correcting the y-coordinate of the robot using RPS
    //correct_y(68);
    Sleep(1.0);
    // Turning into burger tray, Correctiong x-coordinate and heading
    turn_right(88);
    Sleep(1.0);
    //correct_heading(0);
    move_back(3.7);
    Sleep(1.0);
    //correct_x(26);
    side_servo.SetDegree(0);
    move_forward(2.4, 20);
    side_servo.SetDegree(80);
    turn_right(10);
    move_forward(5,50);
    side_servo.SetDegree(180);
    turn_right(10);
    move_time(1.4, FORWARD);
    move_back(2.7);
    side_servo.SetDegree(180);
    turn_right(18);
    move_time(2, FORWARD);
    side_servo.SetDegree(120);
    move_back(7);
}

void flip_ice_cream() {
    // Moving back, Lifting side arm, and Correcting x-coordinate
    move_back(9.5);
    side_servo.SetDegree(180);
    // Getting into position and Flipping the ice cream lever down
    turn_left(50);
    move_back(6.5);
    LCD.WriteLine("About to lower side arm");
    Sleep(1.0);
    side_servo.SetDegree(70);
    LCD.WriteLine("FINISHED");
    Sleep(5.0);
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

void initialize() {
    RPS.InitializeTouchMenu();
    set_up_servos();
}