#ifndef gss_h
#define gss_h
#include"Resource.h"

struct IMG{
	int wid,hei;
	IMDATA *bmp;
};

struct OCTAVE{
	int num;
	IMG ** imgs;
};

struct GSS{
	int O,S,omin,smin,smax;
	IMDATA sigma0;
    OCTAVE * octaves;
};
void InitialGss(GSS &gss,IMG * &img);
#endif