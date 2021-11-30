#include "vex.h"

// void resetCoords(double X, double Y) {
//   X = 0;
//   Y = 0;
// }
// void Odometry(void *ignore) {

//   while (true) {
//     double posL = MotorCL.position(deg), posR = MotorCL.position(deg);
//     double prevposL = posL, prevposR = posR;
//     double posChangeL = posL - prevposL, posChangeR = posR - prevposR;

//     if (InertialL.isCalibrating()) {
//       resetCoords(0, 0);
//       double dist = posChangeL - posChangeR/2* INCH_PER_DEG;
//     }
//   }
// }