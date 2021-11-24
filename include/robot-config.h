using namespace vex;

extern brain Brain;

// VEXcode devices
extern encoder EncoderA;
extern motor MotorFL;
extern motor MotorBL;
extern motor MotorCL;
extern motor MotorFR;
extern motor MotorCR;
extern motor MotorBR;
extern motor MotorFA;
extern motor MotorBA;
extern controller Controller1;
extern encoder EncoderE;
extern inertial InertialL;
extern timer Timer;

extern competition Competition;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );