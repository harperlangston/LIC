#include "Random.h"

using namespace std;

Random::Random(){
}

Random::~Random(){
}

void Random::generate(int argc, char ** argv){
  int i,j, temp;

  CmdLineOpts* cmdLine = new CmdLineOpts(argc, argv);
  to1.open("rand.pgm");
  to2.open("rand.dat");

  if (cmdLine->widthDef()) { width = cmdLine->width; }
  else { width = WIDTH; }
  if (cmdLine->heightDef()) { height = cmdLine->height; }
  else { height = HEIGHT; }

  to1 << "P2";
  to1 << endl;
  to1 << "# rand.pgm";
  to1 << endl;
  to1 << width;
  to1 << " ";
  to1 << height;
  to1 << endl;
  to1 << MAX;
  to1 << endl;

  for(i=0; i<width; i++){
    for (j = 0; j < height; j++){
      temp = int((double(rand())/RAND_MAX)*MAX);
      to1 << temp;
      to2 << temp;
      to1 << " ";
      to2 << " ";
    }
    to1 << endl;
    to2 << endl;
  }
}
