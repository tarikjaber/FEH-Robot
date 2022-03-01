#include <FEHServo.h>

FEHServo front_servo(FEHServo::Servo6); 
FEHServo side_servo(FEHServo::Servo7); 
FEHServo back_servo(FEHServo::Servo0);

#define FRONT_SERVO_MIN 10
#define FRONT_SERVO_MAX 10
#define SIDE_SERVO_MIN 10
#define SIDE_SERVO_MAX 10
#define BACK_SERVO_MIN 10
#define BACK_SERVO_MAX 10

void calibrate_front();
void calibrate_side();
void calibrate_back();
void set_up_servos();