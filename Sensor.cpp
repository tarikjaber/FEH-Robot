#include "Sensor.h"

AnalogInputPin cds_cell(FEHIO::P2_0);

bool is_red() {
    bool is_red = false;
    
    if (get_cds_reading() < 1.3) {
        is_red = true;
    }

    return is_red;
}

bool is_blue() {
    bool is_blue = false;

    double reading = get_cds_reading();

    if ((reading < 2.5) && (reading > 1.5)) {
        is_blue = true;
    }

    return is_blue;
}

double get_cds_reading() {
    return cds_cell.Value();
}

void wait_for_light() {
    while (!light_on()) {};
}

bool light_on() {
    return (get_cds_reading() < 2.5);
}