#ifndef read_img_h
#define read_img_h
#include"Gss.h"
#include"Resource.h"
#include <iostream>

void GetImg(char *filename,IMG * img);
void SaveImg(IMG * img,std::string newfilenme);
void LineImg(IMG * img,double x1,double y1,double x2,double y2);
IMG * MergeImg(IMG * img1,IMG *img2);
#endif