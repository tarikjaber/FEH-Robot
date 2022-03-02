#include <FEHIO.h>

extern AnalogInputPin cds_cell;

// Function Prototypes
bool is_red();
bool is_blue();
double get_cds_reading();
void wait_for_light();
bool light_on();
