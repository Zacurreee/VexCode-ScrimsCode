#include "vex.h"
const double inPerDeg = 0.0461916735714906;

#define halfPI  1.57079632679489661923132169164
#define toRad   0.0174532925199432957692369076849


double encdL = 0, encdR = 0, bearing = 0, ang = halfPI;
double X = 0, Y = 0, prevEncdL = 0, prevEncdR = 0;
void setCoords(double x, double y) {
  X = x;
  Y = y;
  printf("X %.2f , Y %.2f\n", X , Y);

}
void Odometry(void *ignore) {
  while (true) {
    if (InertialL.isCalibrating()) {
      setCoords(0, 0);
    } else {
      double encdChangeL = encdL - prevEncdL;
      double encdChangeR = encdR - prevEncdR;

      double dist = (encdChangeL + encdChangeR) / 2 * inPerDeg;
      X += dist * cos(ang);
      Y += dist * sin(ang);
      /** update prev variables */
      prevEncdL = encdL;
      prevEncdR = encdR;
      
    }
    wait(5, msec);
  }
}
void resetPrevEncd() {
  prevEncdL = 0;
  prevEncdR = 0;
}

void Sensors(void *ignore) {
  while (true) {
    if (InertialL.isCalibrating()) {
      encdL = MotorCL.position(deg);
      encdR = MotorCR.position(deg);
      bearing = InertialL.angle(deg);
      ang = halfPI - bearing * toRad;
    }
    wait(5, msec);
  }
}