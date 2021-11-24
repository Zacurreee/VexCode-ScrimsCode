#include "Pid.h"
#include "vex.h"

double abscap(double value, double cap) {
  if (value > cap)
    return cap;
  else if (value < -cap)
    return -cap;
  else
    return value;
}

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

    powerL = abscap(powerL, MAX_POWER);
    powerR = abscap(powerR, MAX_POWER);

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

void autoBalance(double pitch, double kP, double kD, bool reversed, bool cutoff) {

  double error = pitch - InertialL.pitch(deg);
  // double errorR = pitch - InertialL.pitch(deg);

  double prevErrorL = error, prevErrorR = error;
  double powerL = 0, powerR = 0;
  // fabs(error) > 1.5
 
  while (cutoff ? fabs(error) > 0.5 : fabs(-7 - InertialL.pitch(deg)) > 0.5) {
    error = pitch - InertialL.pitch(deg);

    double derivativeL = error - prevErrorL;
    double derivativeR = error - prevErrorR;

    double targpowerL = error * kP + derivativeL * kD;
    double targpowerR = error * kP + derivativeR * kD;

    // double speedupL = targpowerL - powerL;
    // double speedupR = targpowerR - powerR;

    // powerL += abscap(speedupL, RAMPING_POWER);
    // powerR += abscap(speedupR, RAMPING_POWER);

    powerL = abscap(targpowerL, MAX_POWER);
    powerR = abscap(targpowerR, MAX_POWER);

    int dir = reversed ? -1: 1;

    MotorFL.spin(fwd, dir*powerL, pct);
    MotorCL.spin(fwd, dir*powerL, pct);
    MotorBL.spin(fwd, dir*powerL, pct);
    MotorFR.spin(fwd, dir*powerR, pct);
    MotorCR.spin(fwd, dir*powerR, pct);
    MotorBR.spin(fwd, dir*powerR, pct);

    printf("error: %.2f\n", pitch - InertialL.pitch(deg));
    wait(5, msec);
  }
}

void autoBalance(double pitch) { autoBalance(pitch, DEFAULT_KP, DEFAULT_KD, false, true); }
