#ifndef __CMDLINEOPTS_H__
#define __CMDLINEOPTS_H__

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif 

class CmdLineOpts {

public:
   int       argc;
   char    **argv;

   int     fLength;
   int     height, width;

   char    VelocityIn[256];
   char    ImageIn[256];
   char    ImageOut[256];
   
   CmdLineOpts(int ArgC, char* ArgV[]);

   void      parseCommandLine( );
   void      usage(int i);
   
   bool      fLengthDef();
   bool      heightDef();
   bool      widthDef();

};

#endif
