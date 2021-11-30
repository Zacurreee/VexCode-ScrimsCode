#ifndef _PID_H_
#define _PID_H_
// defined for normal base movements
#define DISTANCE_LEEWAY 5
#define BASE_MAX_POWER 100
#define RAMPING_POWER 10
#define DEFAULT_KP 1
#define DEFAULT_KD 0
// defined for balancing movements
#define BALANCED_MAX_POWER 15 
#define BALANCED_KP 1
#define BALANCED_KD 10
// defined for turning movements
#define TURN_KP 0.65
#define TURN_KD 0.3

// constants defined for math application 
#define INCH_PER_DEG 0.0353563596126047
#define BASE_WIDTH 7.4683412361978
#define TO_RAD  0.0174532925199432957692369076849


void baseMove (double targL, double targR, double kP, double kD, double cutoff);
void baseMove (double dis, double kP, double kD, double cutoff);
void baseMove (double dis, double cutoff);

void pointTurn (double a, double kP, double kD, double cutoff);
void pointTurn (double a, double cutoff);

void autoBalance(double pitch, double kP, double kD, double cut, bool reversed, bool cutoff);
void autoBalance(double pitch, double cut, bool reversed, bool cutoff);
#endif