#ifndef __LIC_H__
#define __LIC_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "Pixel.h"
#include "Velocity.h"
#include "Cmdlineopts.h"

#ifndef MAX
#define MAX 256
#endif

#ifndef SIZE1
#define SIZE1 100
#endif

#ifndef SIZE2
#define SIZE2 100
#endif

#ifndef SCALE
#define SCALE 2.0
#endif

// FILTERLENGTH can be defined on command line, in Makefile or here
#ifndef FILTERLENGTH
#define FILTERLENGTH 10
#endif 

#define PI 3.141592653589793238462643

class LIC {
  
 private:

  int L, height, width;
  std::vector<Pixel> Field_In;
  std::vector<Velocity> UxUy;
  std::vector<Pixel> F;

  std::vector<Pixel>::iterator fIn_it;
  std::vector<Velocity>::iterator vel_it;
  std::vector<Pixel>::iterator f_it;

  std::ofstream to;
  std::ifstream velocity;
  std::ifstream random;

 public:

  CmdLineOpts * cmdLine;
  
  LIC();
  ~LIC();

  void set(int argc, char ** argv);
  void doLIC();
  void writeFile();

  double kIntegral(double a, double b, double c, double d, double Beta);
  double floorAbs(double a);

};

#endif
