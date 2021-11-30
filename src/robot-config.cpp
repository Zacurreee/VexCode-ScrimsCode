#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
encoder EncoderA = encoder(Brain.ThreeWirePort.A);
motor MotorFL = motor(PORT20, ratio18_1, false);
motor MotorCL = motor(PORT19, ratio18_1, false);
motor MotorBL = motor(PORT11, ratio18_1, false);
motor MotorFR = motor(PORT10, ratio18_1, true);
motor MotorCR = motor(PORT2, ratio18_1, true);
motor MotorBR = motor(PORT1, ratio18_1, true);
motor MotorFA = motor(PORT12, ratio36_1, false);
motor MotorBA = motor(PORT9, ratio36_1, false);
controller Controller1 = controller(primary);
encoder EncoderE = encoder(Brain.ThreeWirePort.E);
encoder EncoderD = encoder(Brain.ThreeWirePort.D);
inertial InertialL = inertial(PORT8);
timer Timer;

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {
  // nothing to initialize
}