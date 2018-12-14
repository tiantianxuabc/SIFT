#ifndef Gauss_smooth_h
#define Gauss_smooth_h
#include"Resource.h"
#include"Gss.h"

void GetGaussTemp(IMDATA *Temp,int n,IMDATA sigma);
IMG * GaussSmooth(IMG * img,IMDATA sigma);
void evolve(IMDATA * dest,IMDATA * src,int wid,int hei);
#endif