#include <iostream>
#include "LIC.h"

int main(int argc, char ** argv)
{
  LIC N;
  N.set(argc, argv);
  std::cout <<"\nFinished parsing command line" << std::endl;

  std::cout << "\nComputing LIC . . . " << std::endl;
  N.doLIC();
  std::cout << "\nFinished Computing LIC" << std::endl;
  
  std::cout << "\nWriting out file" << std::endl;
  N.writeFile();

  return(0);
}
