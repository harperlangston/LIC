#ifndef __VELOCITY_H__
#define __VELOCITY_H__

class Velocity{

 private:
  double ux,uy;

 public:

  Velocity();
  Velocity(double ux, double uy);
  ~Velocity();

  void set(double ux, double uy);

  double getUx() { return ux; }
  double getUy() { return uy; }

  double norm();

  Velocity vOverNorm();
};

#endif
