#ifndef Scale_space_h
#define Scale_space_h
#include"Resource.h"
#include"Dss.h"
#include"Gss.h"
#include"Descriptor.h"

struct KEYPOINT{
	IMDATA oframe[4];//0x1y2s3dir
	int octave;
};
void GetKeyPoints(DSS &dss,GSS &gss,struct DESCRIPTOR * dscr,int &denum);

#endif