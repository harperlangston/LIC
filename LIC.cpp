#include "LIC.h"

LIC::LIC(){
}

LIC::~LIC(){
}

void LIC::set(int argc, char ** argv)
{
  CmdLineOpts* cmdLine = new CmdLineOpts(argc, argv);
  to.open(cmdLine->ImageOut);
  velocity.open(cmdLine->VelocityIn);
  random.open(cmdLine->ImageIn);
  if (cmdLine->fLengthDef()) { L = cmdLine->fLength; }
  else { L = FILTERLENGTH; }
  if (cmdLine->widthDef()) { width = cmdLine->width; }
  else { width = SIZE1; }
  if (cmdLine->heightDef()) { height = cmdLine->height; }
  else { height = SIZE2; }
  fIn_it = Field_In.begin();
  vel_it = UxUy.begin();
  f_it = F.begin();

  std::cout << "\nL = " << L << "  " << "height = " << height << "  " << "width = " << width << std::endl;
  std::cout << "\nVelocity file = " << cmdLine->VelocityIn << std::endl;
  std::cout << "Image In file = " << cmdLine->ImageIn << std::endl;
  std::cout <<"Image out file = " << cmdLine->ImageOut << std::endl;

  double temp, temp_ux, temp_uy, temp_uz;
  int temp_int, temp_val, i, j;
  Pixel Pix_Temp;
  Velocity Vel_Temp;
  Pixel F_Temp;

  // Extract velocities from velocity file and values from input image
  // See Random.cpp for noise image that can be used
  for (j = 0; j < height; j++){
    for (i = 0; i < width; i++){
      velocity >> temp_ux;
      velocity >> temp_uy;
      velocity >> temp_uz;

      Vel_Temp.set(temp_ux,temp_uy);
      UxUy.push_back(Vel_Temp);

      random >> temp_val;
      Pix_Temp.setPix((double)i,(double)j);

      Pix_Temp.setVal(temp_val);
      Field_In.push_back(Pix_Temp);

      F_Temp.set(0.0, 0.0, 0.0, 0.0, 0);
      F.push_back(F_Temp);
    }
  }

  // Make sure that the input field is the same size as h*w.  If not, make sure
  // h and w is right or file is right size.
  if (Field_In.size() != height * width){
    std::cerr << "height/width not set properly to size of row/column" << std::endl;
    exit(-1);
  }

  // Do with iterators?
  // Reason trying to load velocities here instead of above is to sort them properly so image
  // . . . isn't off by 90 degrees.  Still working on this.  In general, alter this depending on input orientation
  for (j = 0; j < height; j++){
    for (i = 0; i < width; i++){
      //      temp_int = ((height - j)*height) - (width - i); 
      temp_int = j*width + i;
      Field_In[temp_int].setVel(UxUy[temp_int].getUx(),UxUy[temp_int].getUy());
    }
  }
  
  //free(Pix_Temp);
  //free (Vel_Temp);
  //free (F_Temp);
  //free(i); free(j); free(temp_int); free(temp_ux); free(temp_uy); free(temp_uz);
}


void LIC::doLIC(){
  int temp_int, i, j, k;
  double ValSum, ValtSum, hSum, htSum, temp;
  double s[L],st[L],h[L],ht[L];
  Pixel P[L], Pt[L];
  
  //Generate the forward and backward streamlines based on FILTERLENGTH
  //P[k] used for forward direction and Pt[k] for backwards
  for (j = 0; j < height; j++){
    for (i = 0; i < width; i++){
      temp_int = j*width + i;
      //cout << temp_int << endl;
      // Initialize P[0] and Pt[0] as per algorithm.  Make sure to get proper velocity values from the Field.
      // This'll make things easier
      P[0].reset();
      P[0].set((double)i + 0.5, (double)j + 0.5, Field_In[temp_int].getUx(), Field_In[temp_int].getUy(), Field_In[temp_int].getVal());
      Pt[0].set((double)i + 0.5, (double)j + 0.5, Field_In[temp_int].getUx(), Field_In[temp_int].getUy(), Field_In[temp_int].getVal());
      
      // Reset steps and sums for LIC output
      s[0] = 0.0; st[0] = 0.0;
      ValSum = 0.0; ValtSum = 0.0; hSum = 0.0; htSum = 0.0;

      for (k=1; k < L; k++){
	// Reset P[k]
	P[k].reset();
      	if ((P[k-1].getX() <= width - 1 && P[k-1].getY() <=  height - 1) && (P[k-1].getX() >= 0 && P[k-1].getY() >= 0)){
	  temp = P[k-1].normUxUy();
	  if (temp > 0){
	    P[k].setPix(P[k-1].getX()+(P[k-1].getUx()/temp), P[k-1].getY()+(P[k-1].getUy()/temp));
	    s[k] = s[k-1] + 1.0;
	    temp_int =  (int) (floorAbs(P[k].getX()) + width*(floorAbs(P[k].getY())));
	    P[k].setVel(Field_In[temp_int].getUx(),Field_In[temp_int].getUy());
	    P[k].setVal(Field_In[temp_int].getVal());
	  }
	}

	// Reset Pt[k] in case any junk leftover
	Pt[k].reset();
	if ((Pt[k-1].getX() <= width - 1 && Pt[k-1].getY() <=  height - 1) && (Pt[k-1].getX() >= 0 && Pt[k-1].getY() >= 0)){
	  temp = Pt[k-1].normUxUy();
	  if (temp > 0){	  

	    Pt[k].setPix(Pt[k-1].getX()-(Pt[k-1].getUx()/temp), Pt[k-1].getY()-(Pt[k-1].getUy()/temp));
	    st[k] = st[k-1] + 1.0;

	    temp_int = (int) (floorAbs(Pt[k].getX()) + width*(floorAbs(Pt[k].getY())));
	    Pt[k].setVel(Field_In[temp_int].getUx(),Field_In[temp_int].getUy());
	    P[k].setVal(Field_In[temp_int].getVal());
	  }
	}
      }

      
      // Now we get the bottom and top sums for LIC output
      for (k = 0; k < L-1; k++){
	if (!(P[k].getX() == 0.0 && P[k].getY() == 0.0 && P[k].getUx() == 0.0 && P[k].getUy() == 0.0)){
	  h[k] = kIntegral(s[k],s[k+1],0.1,10.3,PI/6.0);
	  ht[k] = kIntegral(st[k],st[k+1],0.1,0.3,PI/12.0);
	  
	  ValSum += (double)(P[k].getVal())*h[k];
	  ValtSum += (double)(Pt[k].getVal())*ht[k];
	  
	  hSum += h[k];
	  htSum += ht[k];
	}
      }

      // This is kind of a pain which I need to work on - need to avaoid dividing by zero on boundaries
      if (hSum > 0.0000000001 && htSum > 0.00000000001){
	temp = (ValSum + ValtSum)/(hSum + htSum); 
	//Scaling the output makes it easier to see but can actually mess up output.  Need to do coloring for magnitude
	
	if (temp != Field_In[i+j*width].getVal()){
	  F [j*width + i].setVal((int)(temp*SCALE));
	}
	else {
	  F [j*width + i].setVal(0);
	}
      }
      else{
	F[i+j*width].setVal(0);
      }
    }
  }
}


// This flips the F (file to go out) about thex axis, so it's generated properly
// This is needed since the input file for the velocity comes in such that the bottom left
// is the beginning, going to the right and then up.  I'm working in re-orienting this above in set()
// so flipping is unecessary.  In which case this can be ignored later.
//
// Actually, for now I'm doing the flipping in writeFile since I'm most interested in the file for now.
// This will need to be fixed though either here or above
//void LIC::flipF(){
//  int i,j;
//  Pixel Temp;
//}  
  

void LIC::writeFile(){
  int i, j;
  // All we need to do now is generate the output image in grayscale
  to << "P2";
  to << std::endl;
  to << "# rand.pgm";
  to << std::endl;
  to << width;
  to << " ";
  to << height;
  to << std::endl;
  to << MAX;
  to << std::endl;

  // Go from bottom up so image is flipped properly.
  for(j=height; j >= 0; j--){
    for (i = 0; i < width; i++){
      //Fix?
      //      if (F[i+j*width].getVal() == Field_In[i+j*width].getVal())
      // Reference points so image gets flipped around x axis so no upside down.
      to << F[i+j*width].getVal();
      to << " ";
    }
    to << std::endl;
  }
}

double LIC::kIntegral(double a, double b, double c, double d, double Beta){
  float temp = b - a + (sin(b*c) - sin(a*c))/c + (sin(b*d + Beta) - sin(a*d + Beta))/d;
  temp += (sin(b*(c-d) - Beta) - sin(a*(c-d) - Beta))/(2*(c-d));
  temp += (sin(b*(c+d) + Beta) - sin(a*(c+d) + Beta))/(2*(c+d));
  temp *= 0.25;
  return temp;
}


double LIC::floorAbs(double a){
  if (a >= 0) { return floor(a); }
  else { return 0.0; }
}
