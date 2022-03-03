#include <FEHLCD.h>
#include "Navigation.h"
#include "Sensor.h"
#include "Battery.h"
#include "Servo.h"
#include "LineFollowing.h"

void hit_jukebox_button();

void slide_ticket() {
    back_servo.SetDegree(0);
    Sleep(1.0);
    horizontal_servo.SetDegree(150);
    Sleep(1.0);
    horizontal_servo.SetDegree(10);
}

void deposit_tray() {
    horizontal_servo.SetDegree(160);
    Sleep(1.0);
    back_servo.SetDegree(180);
    //move_forward(2);
}

int main() {
    set_up_servos();

    back_servo.SetDegree(0);
    Sleep(1.0);
    horizontal_servo.SetDegree(0);

    move_forward(13);
    turn_right(45);
    move_forward(40, 40);
    turn_right(55);
    move_back(12);
    turn_left(55);
    move_back(2);
    move_back(8);
    horizontal_servo.SetDegree(160);
    back_servo.SetDegree(160);
    move_forward(5);
    // deposit_tray();

    // horizontal_servo.SetDegree(150);
    // Sleep(1.5);
    // horizontal_servo.SetDegree(0);
    // horizontal_servo.TouchCalibrate();
    //  LCD.WriteLine("test");
    //  back_servo.SetMax(BACK_SERVO_MAX);
    //  back_servo.SetMin(BACK_SERVO_MIN);

    // while(true) {
    // back_servo.SetDegree(0);
    // Sleep(0.5);
    // back_servo.SetDegree(180);
    // Sleep(0.5);
    // }
    // horizontal_servo.TouchCalibrate();
    //  move_forward(10);
    //  turn_right(45);
    //  move_forward(20, 60);
    //  turn_left(90);
    //  move_forward(6);
    //  turn_right(90);
    //  drop_back_arm();
    //  move_forward(2);
    //  reset_back_arm();
    //  turn_right(90);
    //  move_forward(25);
    //  turn_right(90);

    // move_back(14);

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