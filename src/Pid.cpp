#include "vex.h"  
#include "Pid.h"


double abscap(double value, double cap) {
  if(value > cap) return cap;
  else if(value < -cap) return -cap;
  else return value;
}

void baseMove(double targL, double targR, double kP, double kD, double cutoff){


MotorFL.resetRotation(); 
MotorBL.resetRotation(); 
MotorFR.resetRotation(); 
MotorBR.resetRotation(); 

targL /= INCH_PER_DEG;
targR /= INCH_PER_DEG;

double errorL = targL -MotorBL.position(deg);
double errorR = targR -MotorBR.position(deg);
double startTime = timer::system();

double prevErrorL = errorL, prevErrorR = errorR;
double powerL =0, powerR = 0;

double derivativeL = errorL - prevErrorL;
double derivativeR = errorR - prevErrorR;

double targpowerL = errorL*kP + derivativeL *kD;
double targpowerR = errorR*kP + derivativeR *kD;

double speedupL = targpowerL - powerL;
double speedupR = targpowerR - powerR;

powerL += abscap(speedupL, RAMPING_POWER);
powerR += abscap(speedupR, RAMPING_POWER);

powerL = abscap(powerL, MAX_POWER);
powerR = abscap(powerR, MAX_POWER);

MotorFL.setVelocity(powerL, pct);
MotorBL.setVelocity(powerL, pct);
MotorFR.setVelocity(powerR, pct);
MotorBR.setVelocity(powerR, pct);


while((fabs(errorL) > DISTANCE_LEEWAY || fabs(errorR) > DISTANCE_LEEWAY) && timer::system() - startTime < cutoff) {
		errorL = targL - MotorBL.position(deg);
		errorR = targR - MotorBR.position(deg);
}
}

void pointTurn(double angle, double kP, double kD, double cutoff) {
  double arc = angle * TO_RAD * BASE_WIDTH;
  baseMove(arc, -arc, kP, kD, cutoff);
}