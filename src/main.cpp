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

void autonomous(){
int autonNum = 1;
	switch (autonNum){
		case 0: skills(); break;
		case 1: blueLeft(); break;
		case 2: blueRight(); break;
		case 3: redLeft(); break;
		case 4: redRight(); break;
}
}

int main() {
  // entire sequence to toggle tank/arcade on and off
  bool isTank = true, enableToggle = true;
    while(true) {
      double left, right; 

      if(Controller1.ButtonY.pressing()) {
        if(enableToggle) {
          isTank = !isTank;
          enableToggle = false;
        }
      } else {
        enableToggle = true;
      }
                  
      if(isTank) {
        //assigns motor group to joysticks
        left = Controller1.Axis3.position();
        right = Controller1.Axis2.position();
      }else {
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
      MotorFR.spin(fwd, right, pct);
      MotorBR.spin(fwd, right, pct);

  }
  vexcodeInit();


}
