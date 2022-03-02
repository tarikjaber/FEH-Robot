#include <FEHIO.h>

#ifndef SENSOR_H
#define SENSOR_H

extern AnalogInputPin cds_cell;

// Function Prototypes
bool is_red();
bool is_blue();
double get_cds_reading();
void wait_for_light();
bool light_on();

#endif
