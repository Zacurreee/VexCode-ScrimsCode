
#include "vex.h"

double abscap(double value, double cap) {
  if (value > cap)
    return cap;
  else if (value < -cap)
    return -cap;
  else
    return value;
}

// Function for PID
void baseMove(double targL, double targR, double kP, double kD, double cutoff) {

  MotorFL.resetRotation();
  MotorCL.resetRotation();
  MotorBL.resetRotation();
  MotorFR.resetRotation();
  MotorCR.resetRotation();
  MotorBR.resetRotation();

  targL /= INCH_PER_DEG;
  targR /= INCH_PER_DEG;

  double errorL = targL - MotorCL.position(deg);
  double errorR = targR - MotorCR.position(deg);

  double prevErrorL = errorL, prevErrorR = errorR;
  double powerL = 0, powerR = 0;
  double start = Timer.time();
  // cutoff can be split into waitBase, according to preference
  while ((fabs(errorL - MotorCL.position(deg)) > DISTANCE_LEEWAY ||
          fabs(errorR - MotorCR.position(deg)) > DISTANCE_LEEWAY) &&
         (Timer.time() - start) < cutoff) {

    double derivativeL = errorL - prevErrorL;
    double derivativeR = errorR - prevErrorR;

    double targpowerL = errorL * kP + derivativeL * kD;
    double targpowerR = errorR * kP + derivativeR * kD;

    double speedupL = targpowerL - powerL;
    double speedupR = targpowerR - powerR;

    powerL += abscap(speedupL, RAMPING_POWER);
    powerR += abscap(speedupR, RAMPING_POWER);

    powerL = abscap(powerL, BASE_MAX_POWER);
    powerR = abscap(powerR, BASE_MAX_POWER);

    MotorFL.spin(fwd, powerL, pct);
    MotorCL.spin(fwd, powerL, pct);
    MotorBL.spin(fwd, powerL, pct);
    MotorFR.spin(fwd, powerR, pct);
    MotorCR.spin(fwd, powerR, pct);
    MotorBR.spin(fwd, powerR, pct);
  }
  wait(5, msec);
}

void baseMove(double dis, double kP, double kD, double cutoff) {
  baseMove(dis, dis, kP, kD, cutoff);
}

// Main Pid function to be called
void baseMove(double dis, double cutoff) {
  baseMove(dis, DEFAULT_KP, DEFAULT_KD, cutoff);
}

void pointTurn(double a, double kP, double kD, double cutoff) {
  double arc = a * TO_RAD * BASE_WIDTH;
  baseMove(arc, -arc, kP, kD, cutoff);
}

void pointTurn(double a, double cutoff) {
  pointTurn(a, TURN_KP, TURN_KD, cutoff);
}

// Function for autobalancing: Values to be tuned: Cutoff values
void autoBalance(double pitch, double kP, double kD, double cut, bool reversed,
                 bool cutoff) {

  double error = pitch - InertialL.pitch(deg);

  double prevErrorL = error, prevErrorR = error;
  double powerL = 0, powerR = 0;

  while (cutoff ? fabs(error) > 0.5
                : fabs(cut - InertialL.pitch(deg)) >
                      0.5) { // values here require tuning to robot
    error = pitch - InertialL.pitch(deg);

    double derivativeL = error - prevErrorL;
    double derivativeR = error - prevErrorR;

    double targpowerL = error * kP + derivativeL * kD;
    double targpowerR = error * kP + derivativeR * kD;

    powerL = abscap(targpowerL, BALANCED_MAX_POWER);
    powerR = abscap(targpowerR, BALANCED_MAX_POWER);

    int dir = reversed ? -1 : 1;

    MotorFL.spin(fwd, dir * powerL, pct);
    MotorCL.spin(fwd, dir * powerL, pct);
    MotorBL.spin(fwd, dir * powerL, pct);
    MotorFR.spin(fwd, dir * powerR, pct);
    MotorCR.spin(fwd, dir * powerR, pct);
    MotorBR.spin(fwd, dir * powerR, pct);

    // printf("error: %.2f\n", pitch - InertialL.pitch(deg));
    wait(5, msec);
  }
}

// Main autoBalacne function to be called
void autoBalance(double pitch, double cut, bool reversed, bool cutoff) {
  autoBalance(pitch, DEFAULT_KP, DEFAULT_KD, cut, false, true);
}
