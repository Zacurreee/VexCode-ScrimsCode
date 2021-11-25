// #include "vex.h"

// const double inPerDeg = 0.0461916735714906;
// double X = 0, Y = 0, prevEncdL = 0, prevEncdR = 0;
// double encdL = 0, encdR = 0, bearing = 0, angle = halfPI;

// void setCoords(double x, double y){
//   X = x;
//   Y = y;
// }
  
// void Odometry(void *ignore){
//   while (true){
//   if(InertialL.isCalibrating()){
//       (EncoderE.resetRotation()); 
//    }else  {
      
//       double encdChangeL = encdL-prevEncdL;
//       double encdChangeR = encdR-prevEncdR;
      
//       double distance = (encdChangeL = encdChangeR)/2*inPerDeg;
//       X+= distance*cos(angle); 
//       prevEncdL = encdL;
//       prevEncdR = encdR;
//    }
//    wait(5, msec);
//   }    
// }

// void resetPrevEncd()  {
//     prevEncdL = 0;
//     prevEncdR = 0;
// }

// void Sensors(void*ignore){
//     while(true){
//       if(!InertialL.isCalibrating()){
//         encdL = MotorBL.position(deg);
//         encdR = MotorBR.position(deg);
//       bearing = InertialL.rotation();
//       angle = halfPI - bearing * toRad;
// }
//   }
// }