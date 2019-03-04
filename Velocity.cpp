#include <math.h>
#include "Velocity.h"                          

Velocity::Velocity(){
  ux = 0.0;
  uy = 0.0;
}

Velocity::Velocity(double vx, double vy){
  ux = vx;
  uy = vy;
}

Velocity::~Velocity(){
}

void Velocity::set(double vx, double vy){
  ux = vx;
  uy = vy;
}

double Velocity::norm(){
  return sqrt(ux*ux + uy*uy);
}

Velocity Velocity::vOverNorm(){
  Velocity temp;
  double n = norm();
  temp.set(ux/n, uy/n);
  return temp;
}
