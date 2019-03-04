#include <iostream>
#include "Random.h"

using namespace std;

void main(int argc, char ** argv)
{
  Random R;
  R.generate(argc,argv);
}
