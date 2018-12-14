#ifndef Hesse_h
#define Hesse_h
#include"Resource.h"
#include"Dss.h"

IMDATA * GetHesse(DSS &dss,int posx,int posy,int scale,int octave,int dim);
bool GetContract(DSS &dss,int posx,int posy,int scale,int octave,IMDATA &nx,IMDATA &ny,IMDATA &nscale);
bool EdgeElim(DSS &dss,int posx,int posy,int scale,int octave);
bool localization(IMDATA * Matrix,IMDATA * Serial,IMDATA &nx,IMDATA &ny,IMDATA &nscale);
bool Localize(DSS &dss,int posx,int posy,int scale,int octave,IMDATA *newpos);
#endif