#include <FEHServo.h>

extern FEHServo front_servo; 
extern FEHServo side_servo; 
extern FEHServo back_servo;

#define FRONT_SERVO_MIN 10
#define FRONT_SERVO_MAX 10
#define SIDE_SERVO_MIN 10
#define SIDE_SERVO_MAX 10
#define BACK_SERVO_MIN 500
#define BACK_SERVO_MAX 2400

void calibrate_front();
void calibrate_side();
void calibrate_back();
void set_up_servos();