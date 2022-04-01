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
void shutdown();

int main() {
    // Set Up
    initialize();

    // move_forward(10);
    // write_counts();
    // move_back(10);
    // write_counts();
    // Body
    perform_tasks();

    // Resetting servos and exiting main
    shutdown();
    return 0;
}

// Start
void initialize() {
    set_up_servos();
}

// All Tasks
void perform_tasks() {
    RPS.InitializeTouchMenu();
    wait_for_light();
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
    move_forward(13);
    turn_right(37);
    correct_x(20);
    correct_heading(90);

    // Go up the ramp
    move_forward(31.5, 50);
    write_counts();
    LCD.WriteLine(RPS.Heading());
    LCD.WriteLine(RPS.Y());
    Sleep(2.5);
    correct_heading(88.0);
    correct_y(50.5);

    // Turning to get right of the ice cream levers
    Sleep(0.5);
    turn_left(53);
    Sleep(0.5);
    move_forward(10.5);
    Sleep(0.5);

    // Getting angled with levers
    //Right
    //turn_right(97);
    //Left
    turn_right(100);

    // Getting ice cream flavor
    int flavor = get_ice_cream();
    LCD.WriteLine(flavor);

    // Raising side arm to maximum
    set_side(0);

    // Calculating necessary distance to reach lever depending on the flavor
    int distance = flavor * 4.15;
    move_forward(distance);
    //Right
    move_back(0.75);

    // Lowering the arm, moving back to wait, and lifting the lever
    Sleep(0.8);
    set_side(60);
    Sleep(0.8);
    set_side(0);

    // Flip back up
    move_back(1.25);
    Sleep(7.0);
    set_side(70);
    Sleep(0.8);
    turn_right(13);
    Sleep(0.8);
    set_side(0);
    Sleep(0.8);

    // Moving back to initial location should
    set_side(70);
    Sleep(0.8);
    turn_left(13);

    // Flipping side lever all the way up
    set_side(0);
    Sleep(0.8);
    move_back(distance - 1.25);
}

void deposit_tray() {
    // Going to sink
    turn_left(45);
    move_back(5);
    // Opening horizontal arm so that back servo can go down
    set_horizontal(100);
    Sleep(1.0);

    // Move to sink
    move_time(1.2, BACKWARD);

    // Lowering the back arm
    set_back(96);
    
    // Moving forward to drop the tray off and lifting the back arm back up
    move_forward(5);
    set_back(0);
    Sleep(0.8);
    set_horizontal(0);
}

void flip_burger() {
    // Going to the burger plate
    turn_right(33);
    move_forward(13.0);
    correct_y(62.0);
    turn_right(62);

    // Correcting the x-coordinate
    Sleep(1.0);
    LCD.WriteLine("X-Coordinate:");
    LCD.WriteLine(RPS.X());
    correct_x(20.0);
    correct_heading(0);
    move_back(2.5);

    // Lowering side arm all the way down
    set_side(100);

    // Flipping the burger
    move_forward(2.0);
    set_side(60);
    move_forward(2.0, 60);
    turn_right(20, 50);
    move_forward(2, 60);
    set_side(0);
    turn_right(15, 50);
    Sleep(1.0);

    // Returning the hot plate
    move_back(5);
    turn_right(10);
    move_time(2.5, FORWARD);
    set_side(50);
    move_back(9);
    
    // Lefting side arm back up
    Sleep(0.8);
    set_side(0);
}

void slide_ticket() {
    // Aligning with ticket
    move_forward(2.5);
    correct_x(29.5);

    // Turning to angle to ticket
    turn_left(95);
    LCD.WriteLine(RPS.Heading());
    correct_heading(95);
    LCD.WriteLine(RPS.Heading());

    // Moving back to the ticket
    move_back(15.5);
    correct_heading(90);
    Sleep(1.0);
    set_horizontal(90);

    // Slide ticket
    Sleep(0.6);
    move_back(5);
    Sleep(0.6);
    set_horizontal(0);
    Sleep(1.0);

    // Leaving ticket area
    set_horizontal(90);
    move_forward(10);
    set_horizontal(0);
}

void hit_jukebox() {
    // Going to jukebox
    turn_right(110);
    move_back(10.0);
    correct_x(20);
    turn_left(90);
    correct_heading(90);
    move_back(14);
    correct_y(23.5);
    
    // Aligning with light
    turn_left(90);
    move_forward(10.5);
    correct_x(4);
    turn_left(90);

    // Drive until light
    set_both(30);
    wait_for_light();
    stop();

    // Testing if the light is red or blue or wasn't read correctly
    if (is_red()) {
        Sleep(1.0);
        turn_left(90);
        correct_heading(270);

        LCD.Clear(SCARLET);
        turn_right(20.0);
        move_forward(4);
        turn_left(20.0);

        move_time(3, FORWARD);
    }
    else if (is_blue()) {
        Sleep(1.0);
        turn_left(90);
        correct_heading(270);

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
