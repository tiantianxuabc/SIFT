#ifndef descriptor_h
#define descriptor_h
#include"Resource.h"
#include"Gss.h"
#include"Scale_space.h"

struct DESCRIPTOR{
	IMDATA serial[NBO*NBP*NBP];
	IMDATA oframe[4];
	int octave;
};
IMDATA fast_mod(IMDATA th);
int fast_floor(IMDATA x);
void normalize(IMDATA *serial,int num);
void GetDescriptor(GSS &gss,DESCRIPTOR * dscr,struct KEYPOINT * key,int keynum,int octave,int &denum);
#endif