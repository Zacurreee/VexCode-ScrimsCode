#ifndef _PID_H_
#define _PID_H_

#define DISTANCE_LEEWAY 5
#define MAX_POWER 100
#define RAMPING_POWER 10

#define DEFAULT_KP 0.83
#define DEFAULT_KD 0.2
#define TURN_KP 0.65
#define TURN_KD 0.3

#define INCH_PER_DEG 0.0353563596126047
#define BASE_WIDTH 7.4683412361978
#define TO_RAD  0.0174532925199432957692369076849

void baseMove (double errorL, double errorR, double kP, double kD, double cutoff);
void pointTurn (double angle, double kP, double kD, double cutoff);

#endif