#include "vex.h"
#define twoPI 6.28318530717958647692528676656
double boundRad(double rad) {
  double res = fmod(rad, twoPI);
  if (res < 0)
    res += twoPI;
  return res;
}
double boundDeg(double deg) {
  double res = fmod(deg, 360);
  if (res < 0)
    res += 360;
  return res;
}

double abscap2(double x, double cap) {
  if (x > cap)
    return cap;
  else if (x < -cap)
    return -cap;
  else
    return x;
}