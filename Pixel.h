#ifndef __PIXEL_H__
#define __PIXEL_H__

#include "Velocity.h"

class Pixel {

 private:
  int val;
  double x,y,ux,uy;

 public:

  Pixel();

  void setPix(double a, double b);
  void set(double a, double b, double vx, double vy);
  void set(double a, double b, double vx, double vy, int val);

  ~Pixel();

  void set(Pixel p);
  void setVel(double ux,double uy);
  void setVel(Velocity v);
  void setVal(int v);
  void print();

  double getX() { return x; }
  double getY() { return y; }

  double getUx() { return ux; }
  double getUy() { return uy; }

  int getVal() { return val; }

  double normUxUy();

  void reset();
};

#endif
