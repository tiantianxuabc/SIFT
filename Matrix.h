#ifndef Matrix_h
#define Matrix_h
#include"Resource.h"

void Display(IMDATA * Matrix,int hei,int wid);
IMDATA GetMatrixValue(IMDATA * Matrix,int wid);
IMDATA * Multiple(IMDATA *Mat1,IMDATA * Mat2,int h1,int w1,int h2,int w2);
bool GetNi(IMDATA * Matrix1,IMDATA * Matrix2,int wid);
#endif