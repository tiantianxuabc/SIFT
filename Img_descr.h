#ifndef img_descri_h
#define img_descri_h
#include"Descriptor.h"
#include"Dss.h"
#include"Gauss_smooth.h"
#include"Gss.h"
#include"Hesse.h"
#include"Orientation.h"
#include"Read_img.h"
#include"Resize_img.h"
#include"Resource.h"
#include"Scale_space.h"

void ImgDescri(char *filename,DESCRIPTOR * dscr,int &denum);
#endif