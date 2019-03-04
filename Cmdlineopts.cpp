/*                                                         */
#include <iostream>
#include <string>
#include <stdlib.h>

#include "Cmdlineopts.h"

CmdLineOpts::CmdLineOpts(int ArgC, char* ArgV[]){

  argc = ArgC;
  argv = ArgV;
   
  strcpy(VelocityIn, "velocity.dat");
  strcpy(ImageIn, "rand.dat");
  strcpy(ImageOut, "out.dat");

  fLength = 0;
  
  parseCommandLine();
  
}

void CmdLineOpts::parseCommandLine(){
  int test = 0;
  for (int i = 1; i < argc; i++) {
    /* Careful! i may change it's value inside the loop */
    
    if ( strcmp(argv[i],"-in") ==  0 ) {
      i++;
      strcpy(ImageIn, argv[i]);
      test++;
    } 

    else if ( strcmp (argv[i], "-out") == 0 ) {
      i++;
      strcpy(ImageOut, argv[i]);
      test++;
    }

    else if ( strcmp (argv[i], "-vel") == 0 ) {
      i++;
      strcpy(VelocityIn, argv[i]);
      test++;
    }

    else if ( strcmp (argv[i], "-L") == 0 ) {
      i++;
      fLength = atoi(argv[i]);
      test++;
    }
    
    else if ( strcmp (argv[i], "-H") == 0 ) {
      i++;
      height = atoi(argv[i]);
      test++;
    }

    else if ( strcmp (argv[i], "-W") == 0 ) {
      i++;
      width = atoi(argv[i]);
      test++;
    }

    else {
      std::cerr << "Incorrecet Usage" << std::endl;
      usage(1);
      exit(-1);
    }
    
  }

  if (test == 0) { usage(test); }
  else if (test > 6) { usage(test); }
}

bool CmdLineOpts::fLengthDef(){
  if (fLength == 0) { return FALSE; }
  else { return TRUE; }
}

bool CmdLineOpts::heightDef(){
  if (height == 0) { return FALSE; }
  else { return TRUE; }
}

bool CmdLineOpts::widthDef(){
  if (width == 0) { return FALSE; }
  else { return TRUE; }
}

void CmdLineOpts::usage(int i){
  
  if ( i == 0 ){
    std::cerr << "No files/options designated; using default files (see below)\n\n" 
	 << "Usage: main <options>\n"
	 << "            options: -in fileIn.dat   : Designates image in file.  Defaults to rand.dat\n"
	 << "                     -out fileOut.dat    : Designates output image.  Defaults to out.dat (Currently pgm format)\n"
	 << "                     -vel VelocityIn.dat  : Designates input velocity.  Defaults to velocity.dat.  Format is ux uy uz velocities per line (uz not used now)\n"
	 << "                     -L FILTERLENGTH : Designates filter length.  Defaults to 15 (forward and backward, so total = 15)\n"
	 << "                     -W WIDTH :  Designates WIDTH (width of the input and output images - defaults to SIZE1 in LIC.h)\n"
      	 << "                     -H HEIGHT : Designates HEIGHT filter length.  (width of the input and output images - defaults to SIZE2 in LIC.h)\n"
	      << std::endl;
  }

  else {
    std::cerr << "Incorrect Usage" 
	 << "Usage: main <options>\n"
	 << "            options: -in fileIn.dat   : Designates image in file.  Defaults to rand.dat\n"
	 << "                     -out fileOut.dat    : Designates output image.  Defaults to out.dat (Currently pgm format)\n"
	 << "                     -vel VelocityIn.dat  : Designates input velocity.  Defaults to velocity.dat.  Format is ux uy uz velocities per line (uz not used now)\n"
	 << "                     -L FILTERLENGTH : Designates filter length.  Defaults to 20 (forward and back, so total = 40)\n"
	 << "                     -W WIDTH :  Designates WIDTH (width of the input and output images - defaults to SIZE1 in LIC.h)\n"
      	 << "                     -H HEIGHT : Designates HEIGHT filter length.  (width of the input and output images - defaults to SIZE2 in LIC.h)\n"
	 << "\nEither type 'main' or main <options>"
	      << std::endl;
  }

}
