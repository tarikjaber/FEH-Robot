#include "Battery.h"

void display_battery_voltage() {
    LCD.Clear();
    LCD.Write("Battery Voltage (V): ");
    LCD.WriteLine(Battery.Voltage());
}