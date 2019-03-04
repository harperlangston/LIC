#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Cmdlineopts.h"

#ifndef WIDTH
#define WIDTH 100
#endif

#ifndef HEIGHT
#define HEIGHT 100
#endif

#ifndef MAX
#define MAX 256
#endif

class Random {
 private:
  int width, height;
  ofstream to1;
  ofstream to2;
  CmdLineOpts * cmdLine;

 public:
  Random();
  ~Random();

  void generate(int argc, char ** argv);

};
  
#endif
