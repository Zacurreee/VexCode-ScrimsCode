#ifndef _ODOM_H_
#define _ODOM_H_
extern double X, Y;
extern const double inPerDeg;
void setCoords(double x, double y);
void Odometry(void * ignore);
void resetPrevEncd();
extern double encdL, encdR, bearing, angle;
void Sensors(void * ignore);
#endif
