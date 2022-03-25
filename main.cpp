#include <FEHLCD.h>
#include "Navigation.h"
#include "Sensor.h"
#include "Battery.h"
#include "Servo.h"
#include "LineFollowing.h"
#include "RPS.h"

// Start
void initialize();
// All Tasks
void perform_tasks();
// Individual Tasks
void hit_jukebox();
void deposit_tray();
void slide_ticket();
void flip_ice_cream();
void flip_burger();
// End
void hit_final_button();

int main() {
    // Set Up
    initialize();

    // Body
    perform_tasks();

    // Resetting servos and exiting main
    shutdown();
    return 0;
}

// Start
void initialize() {
    RPS.InitializeTouchMenu();
    set_up_servos();
    wait_for_light();
}

// All Tasks
void perform_tasks() {
    flip_ice_cream();
    deposit_tray();
    flip_burger();
    slide_ticket();
    hit_jukebox();
    hit_final_button();
}

// Individual Tasks
void flip_ice_cream() {
    // Angle towards ramp
    move_forward(14);
    turn_right(45);

    // Go up the ramp
    move_forward(31.5, 50);
    LCD.WriteLine(RPS.Heading());
    Sleep(2.5);
    correct_heading(88.0);

    // Turning to get right of the ice cream levers
    Sleep(0.5);
    turn_left(55);
    move_forward(10.5);

    // Getting angled with levers
    turn_right(100);
    move_back(3);

    // Getting ice cream flavor
    int flavor = get_ice_cream();
    LCD.WriteLine(flavor);

    // Raising side arm to maximum
    set_side(0);

    // Calculating necessary distance to reach lever depending on the flavor
    int distance = flavor * 4.3 + 2.4;
    move_forward(distance);

    // Lowering the arm, moving back to wait, and lifting the lever
    Sleep(0.8);
    set_side(60);
    Sleep(0.8);
    set_side(0);
    move_back(2);
    Sleep(7.0);
    set_side(70);
    Sleep(0.8);
    move_forward(2);
    Sleep(0.8);
    set_side(0);
    Sleep(0.8);

    // Moving back to initial location should
    set_side(80);
    Sleep(0.8);
    move_back(distance);
    set_side(0);
}

void deposit_tray() {
    // Going to sink
    turn_left(45);
    move_back(5);
    // Opening horizontal arm so that back servo can go down
    set_horizontal(100);
    Sleep(1.0);

    // Move to sink
    move_time(5, BACKWARD);

    // Lowering the back arm
    set_back(95);
    
    // Moving forward to drop the tray off and lifting the back arm back up
    move_forward(5);
    set_back(0);
    Sleep(0.8);
    set_horizontal(0);
}

void flip_burger() {
    // Going to the burger plate
    turn_right(45);
    move_forward(13);
    turn_right(45);

    // Correcting the x-coordinate
    correct_x(26);
    correct_heading(0);

    // Lowering side arm all the way down
    set_side(100);

    // Flipping the burger
    move_forward(3);
    set_side(50);
    move_forward(4, 60);
    set_side(80);
    
    // Returning the hot plate
    move_back(3);
    turn_right(15);
    move_time(4, FORWARD);
    set_side(20);
    move_back(9);
    
    // Lefting side arm back up
    Sleep(0.8);
    set_side(0);
}

void slide_ticket() {
    // Aligning with ticket
    move_forward(4);
    correct_x(29);

    // Turning to angle to ticket
    turn_left(90);
    correct_heading(90);

    // Moving back to the ticket
    move_back(20);
    correct_heading(90);
    set_horizontal(80);

    // Slide ticket
    move_back(3);
    set_horizontal(0);
    Sleep(1.0);

    // Leaving ticket area
    set_horizontal(90);
    move_forward(10);
}

void hit_jukebox() {
    // Going to jukebox
    turn_right(90);
    move_back(15);
    correct_x(18);
    turn_left(90);
    correct_heading(90);
    move_back(15);

    // Aligning with light
    turn_left(90);
    move_forward(8);
    correct_x(10);
    turn_left(90);
    correct_heading(270);

    // Drive until light
    set_both(30);
    wait_for_light();
    stop();

    // Pressing the correct button
    Sleep(1.0);

    // Testing if the light is red or blue or wasn't read correctly
    if (is_red()) {
        LCD.Clear(SCARLET);
        turn_right(20.0);
        move_forward(4);
        turn_left(20.0);

        move_time(3, FORWARD);
    }
    else if (is_blue()) {
        LCD.Clear(BLUE);
        turn_left(20.0);
        move_forward(3);
        turn_right(20.0);

        move_time(3, FORWARD);
    }
    else
    {
        LCD.Clear(GREEN);
        LCD.WriteLine("ERROR: Did not read light value.");
    }
}

// End
void hit_final_button() {
    move_back(5);
    turn_left(75);
    move_forward(50, 50);
}

void shutdown() {
    reset_servos();
}
