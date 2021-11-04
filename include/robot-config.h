using namespace vex;

extern brain Brain;

// VEXcode devices
extern encoder EncoderA;
extern motor MotorFL;
extern motor MotorBL;
extern motor MotorFR;
extern motor MotorBR;
extern controller Controller1;
extern encoder EncoderE;
extern inertial InertialL;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );