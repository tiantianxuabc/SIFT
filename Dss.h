#ifndef dss_h
#define dss_h
#include"Gss.h"
#include"Resource.h"

struct DSS{
	int O,S,omin,smin,smax;
	IMDATA sigma0;
    OCTAVE * octaves;
};
void InitialDss(DSS &dss,GSS &gss);
#endif