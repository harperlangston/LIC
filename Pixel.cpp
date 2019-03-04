#include "Pixel.h"
#include <iostream>
#include <math.h>

Pixel::Pixel(){
  x = 0.0; y = 0.0; ux = 0.0; uy = 0.0; val = 0;
}

void Pixel::setPix(double a, double b){
  x = a; y = b;
}

void Pixel::set(double a, double b, double vx, double vy){
  x =a; y = b; 
  ux = vx; uy = vy;
}

void Pixel::set(double a, double b, double vx, double vy, int v){
  x =a; y = b; 
  ux = vx; uy = vy;
  val = v;
}

Pixel::~Pixel(){
}

void Pixel::set(Pixel p){
  x = p.x; y = p.y;
  ux = p.ux; uy = p.uy;
  val = p.val;
}

void Pixel::setVel(double vx, double vy){
  ux = vx; uy = vy;
}

void Pixel::setVel(Velocity v){
  ux = v.getUx();
  uy = v.getUy();
}

void Pixel::setVal(int v){
  val = v;
}

void Pixel::print(){
  std::cout <<x<<" "<<y<<" "<<ux<<" "<<uy<<" "<<val<<std::endl;
}

double Pixel::normUxUy(){
  double temp = ux*ux + uy*uy;
  temp = sqrt(temp);
  return temp;
}

void Pixel::reset(){
  x = 0.0; y = 0.0; ux = 0.0; uy = 0.0; val = 0;
}
