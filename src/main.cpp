/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\19zachary.ng.yi.kiat                             */
/*    Created:      Tue Nov 02 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// EncoderA             encoder       A, B
// MotorFL              motor         11
// MotorBL              motor         20
// MotorFR              motor         1
// MotorBR              motor         10
// Controller1          controller
// EncoderE             encoder       E, F
// InertialL            inertial      2
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;
competition Competition;

void pre_auton() { vexcodeInit(); }

int main() {
  // entire sequence to toggle tank/arcade on and off
  InertialL.calibrate();
  while (InertialL.isCalibrating()) {
    wait(5, msec);
  }
  bool isTank = true, enableToggle = true;
  bool isCoast = true, enableBrake = true;
  while (true) {
    double left, right;

    if (Controller1.ButtonY.pressing()) {
      if (enableToggle) {
        isTank = !isTank;
        enableToggle = false;
      }
    } else {
      enableToggle = true;
    }

    if (isTank) {
      // assigns motor group to joysticks
      left = Controller1.Axis3.position();
      right = Controller1.Axis2.position();

    } else {
      // assigns power and turn to the joysticks
      int power = Controller1.Axis3.position();
      int turn = Controller1.Axis1.position();
      // define left side and right side
      left = power + turn;
      right = power - turn;
    }
    // group motor to either left or right
    MotorFL.spin(fwd, left, pct);
    MotorBL.spin(fwd, left, pct);
    MotorCL.spin(fwd, left, pct);
    MotorFR.spin(fwd, right, pct);
    MotorCR.spin(fwd, right, pct);
    MotorBR.spin(fwd, right, pct);

    if (Controller1.ButtonA.pressing()) {
      if (enableBrake) {
        isCoast = !isCoast;
        enableBrake = false;
      }
    } else {
      enableBrake = true;
    }

    if (isCoast) {
      MotorFL.setBrake(coast);
      MotorBL.setBrake(coast);
      MotorCL.setBrake(coast);
      MotorFR.setBrake(coast);
      MotorCR.setBrake(coast);
      MotorBR.setBrake(coast);
    } else {
      MotorFL.setBrake(hold);
      MotorBL.setBrake(hold);
      MotorCL.setBrake(hold);
      MotorFR.setBrake(hold);
      MotorCR.setBrake(hold);
      MotorBR.setBrake(hold);
    }

    // arm control
    if (Controller1.ButtonL1.pressing()) {
      MotorBA.spin(fwd, 100, pct);
    } else if (Controller1.ButtonL2.pressing()) {
      MotorBA.spin(fwd, -100, pct);
    } else if (Controller1.ButtonR1.pressing()) {
      MotorFA.spin(fwd, 100, pct);
    } else if (Controller1.ButtonR2.pressing()) {
      MotorFA.spin(fwd, -100, pct);
    } else {
      MotorFA.stop(hold);
      MotorBA.stop(hold);
    }

    // autobalance for driver control
    if (Controller1.ButtonX.pressing()) {
      autoBalance(15, 10, 0, -6.5, false, true);
      wait(200, msec);
      autoBalance(13, 10, 1, -6, true, false);
      MotorFL.setBrake(hold);
      MotorBL.setBrake(hold);
      MotorCL.setBrake(hold);
      MotorFR.setBrake(hold);
      MotorCR.setBrake(hold);
      MotorBR.setBrake(hold);
    }
  }
  wait(5, msec);
}
