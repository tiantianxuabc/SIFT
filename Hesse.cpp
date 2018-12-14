#include<windows.h>
#include<math.h>
#include<iostream>
using namespace std;
#include"Hesse.h"
#include"Matrix.h"


IMDATA * GetHesse(DSS &dss,int posx,int posy,int scale,int octave,int dim)
{
	if(dim<=0)return NULL;
	IMDATA * Serial=(IMDATA *)malloc(dim*sizeof(IMDATA));
	IMDATA k=pow(2.0,1.0/((IMDATA)(dss.S)));
	///////////////////////////////////////////////////
//	double sigma=OSigma(dss->octave)*inisigma*pow(step,(double)kpara);
//	double dsigma[2];
//	dsigma[0]=(step-1.0)*sigma;
//	dsigma[1]=(1.0-1.0/step)*sigma;

	int sk=scale-dss.smin;
	int octk=octave-dss.omin;
	int wid=dss.octaves[octk].imgs[sk]->wid;
	if(dim==2)
	{
		Serial[0]=((dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx+1])-(dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx-1]))/2;
		Serial[1]=((dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx+wid])-(dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx-wid]))/2;
		return Serial;
	}
	if(dim==3)
	{
		Serial[0]=((dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx+1])-(dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx-1]))/2;
		Serial[1]=((dss.octaves[octk].imgs[sk]->bmp[posy*wid+wid+posx])-(dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx-wid]))/2;
		Serial[2]=((dss.octaves[octk].imgs[sk+1]->bmp[posy*wid+posx])-(dss.octaves[octk].imgs[sk-1]->bmp[posy*wid+posx]))/2;
		return Serial;
	}
	if(dim==4)
	{
		IMDATA assist[6];
		assist[0]=(dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx])-(dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx-1]);
		assist[1]=(dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx+1])-(dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx]);
		assist[2]=(dss.octaves[octk].imgs[sk]->bmp[posy*wid+wid+posx+1])-(dss.octaves[octk].imgs[sk]->bmp[posy*wid+wid+posx]);
		assist[3]=(dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx])-(dss.octaves[octk].imgs[sk]->bmp[posy*wid-wid+posx]);
		assist[4]=(dss.octaves[octk].imgs[sk]->bmp[posy*wid+wid+posx])-(dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx]);
		assist[5]=(dss.octaves[octk].imgs[sk]->bmp[posy*wid+wid+posx+1])-(dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx+1]);
		Serial[0]=assist[1]-assist[0];
		Serial[1]=assist[2]-assist[1];
		Serial[2]=assist[5]-assist[4];
		Serial[3]=assist[4]-assist[3];
		return Serial;
	}
	if(dim==9)
	{
		IMDATA assist[12];
		assist[0]=(dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx])-(dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx-1]);
		assist[1]=(dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx+1])-(dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx]);
		assist[2]=(dss.octaves[octk].imgs[sk]->bmp[posy*wid+wid+posx+1])-(dss.octaves[octk].imgs[sk]->bmp[posy*wid+wid+posx]);
		assist[3]=(dss.octaves[octk].imgs[sk+1]->bmp[posy*wid+posx+1])-(dss.octaves[octk].imgs[sk+1]->bmp[posy*wid+posx]);
		assist[4]=(dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx])-(dss.octaves[octk].imgs[sk]->bmp[posy*wid-wid+posx]);
		assist[5]=(dss.octaves[octk].imgs[sk]->bmp[posy*wid+wid+posx])-(dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx]);
		assist[6]=(dss.octaves[octk].imgs[sk]->bmp[posy*wid+wid+posx+1])-(dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx+1]);
		assist[7]=(dss.octaves[octk].imgs[sk+1]->bmp[posy*wid+wid+posx])-(dss.octaves[octk].imgs[sk+1]->bmp[posy*wid+posx]);
        assist[8]=(dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx])-(dss.octaves[octk].imgs[sk-1]->bmp[posy*wid+posx]);
		//assist[8]/=dsigma[1];
		assist[9]=(dss.octaves[octk].imgs[sk+1]->bmp[posy*wid+posx])-(dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx]);
		//assist[9]/=dsigma[0];
		assist[10]=(dss.octaves[octk].imgs[sk+1]->bmp[posy*wid+posx+1])-(dss.octaves[octk].imgs[sk]->bmp[posy*wid+posx+1]);
		//assist[10]/=dsigma[0];
		assist[11]=(dss.octaves[octk].imgs[sk+1]->bmp[posy*wid+wid+posx])-(dss.octaves[octk].imgs[sk]->bmp[posy*wid+wid+posx]);
		//assist[11]/=dsigma[0];
		Serial[0]=assist[1]-assist[0];
		Serial[1]=assist[2]-assist[1];
		Serial[2]=(assist[3]-assist[1]);///dsigma[0];
		Serial[3]=assist[6]-assist[5];
		Serial[4]=assist[5]-assist[4];
		Serial[5]=(assist[7]-assist[5]);///dsigma[0];
		Serial[6]=assist[10]-assist[9];
		Serial[7]=assist[11]-assist[9];
		Serial[8]=(assist[9]-assist[8]);///dsigma[1];
		return Serial;
	}
	free(Serial);
	return NULL;
}

bool GetContract(DSS &dss,int posx,int posy,int scale,int octave,IMDATA &nx,IMDATA &ny,IMDATA &nscale)
{
	IMDATA *Serial,*Matrix,MNi[9];
    Serial=GetHesse(dss,posx,posy,scale,octave,3);
	Matrix=GetHesse(dss,posx,posy,scale,octave,9);
	if(Serial==NULL || Matrix==NULL)return false;
	int octk=octave-dss.omin;
	int sk=scale-dss.smin;
	IMDATA multi=0;
	if(!GetNi(Matrix,MNi,3))
	{
		free(Serial);
		free(Matrix);
		return false;
	}
    multi=(Multiple(Multiple(Serial,MNi,1,3,3,3),Serial,1,3,3,1))[0];
	multi=dss.octaves[octk].imgs[sk]->bmp[posy*(dss.octaves[octk].imgs[sk]->wid)+posx]-multi/2;
	if(fabs(multi)<ContractGate)return false;
	if(localization(MNi,Serial,nx,ny,nscale))
	{
		free(Serial);
		free(Matrix);
		return true;
	}
	free(Serial);
	free(Matrix);
	return false;
}

bool EdgeElim(DSS &dss,int posx,int posy,int scale,int octave)
{
	IMDATA *Matrix;
	Matrix=GetHesse(dss,posx,posy,scale,octave,4);
	if(Matrix==NULL)return false;
	IMDATA det,trace;
	det=GetMatrixValue(Matrix,2);
	trace=Matrix[0]+Matrix[3];
	free(Matrix);
	if(det<=0)return false;	
	if(trace*trace/det>EdgeGate)return false;
	return true;
}

bool localization(IMDATA * Matrix,IMDATA * Serial,IMDATA &nx,IMDATA &ny,IMDATA &nscale)
{
	IMDATA *Serial2;
	Serial2=Multiple(Matrix,Serial,3,3,3,1);
	nx=-Serial2[0];
	ny=-Serial2[1];
	nscale=-Serial2[2];
	free(Serial2);
	return true;
}

bool Localize(DSS &dss,int posx,int posy,int scale,int octave,IMDATA *newpos)
{
	int dpx=0,dpy=0,dps=0;
	//double * newpos=NULL;
	//newpos=(double *)malloc(3*sizeof(double));
	int wid,hei,octk,sk;
	octk=octave-dss.omin;
	sk=scale-dss.smin;
	wid=dss.octaves[octk].imgs[0]->wid;
	hei=dss.octaves[octk].imgs[0]->hei;

#define At(dx,dy,ds) dss.octaves[octk].imgs[(sk+ds)]->bmp[(posy+dy)*wid+(posx+dx)]

	int i;
	IMDATA Hesse[9];
	for(i=0;i<5;i++)
	{
		posx+=dpx;
		posy+=dpy;
		sk+=dps;
		if((posx<1)||(posx>wid-2)||(posy<1)||(posy>hei-2)||(sk<1)||(sk>dss.smax-dss.smin-1))
			return false;//return NULL;
        newpos[0]=-0.5*(At(1,0,0)-At(-1,0,0));
		newpos[1]=-0.5*(At(0,1,0)-At(0,-1,0));
		newpos[2]=-0.5*(At(0,0,1)-At(0,0,-1));
		Hesse[0]=At(1,0,0)+At(-1,0,0)-2.0*At(0,0,0);
		Hesse[4]=At(0,1,0)+At(0,-1,0)-2.0*At(0,0,0);
		Hesse[8]=At(0,0,1)+At(0,0,-1)-2.0*At(0,0,0);
		Hesse[1]=Hesse[3]=0.25*(At(1,1,0)+At(-1,-1,0)-At(-1,1,0)-At(1,-1,0));
		Hesse[2]=Hesse[6]=0.25*(At(1,0,1)+At(-1,0,-1)-At(-1,0,1)-At(1,0,-1));
		Hesse[5]=Hesse[7]=0.25*(At(0,1,1)+At(0,-1,-1)-At(0,-1,1)-At(0,1,-1));

		dpx=((newpos[0]>0.6 && posx<wid-2)?1:0)+((newpos[0]<-0.6 && posx>1)?-1:0);
		dpy=((newpos[1]>0.6 && posy<hei-2)?1:0)+((newpos[1]<-0.6 && posy>1)?-1:0);
		if(dpx==0 && dpy==0)break;
	}
	if(Hesse[0]*Hesse[4]-Hesse[1]*Hesse[1]==0)return false;//return NULL;
	IMDATA score=(Hesse[0]+Hesse[4])*(Hesse[0]+Hesse[4])/(Hesse[0]*Hesse[4]-Hesse[1]*Hesse[1]);
	IMDATA val=At(0,0,0)-0.5*(newpos[0]*newpos[0]+newpos[1]*newpos[1]+newpos[2]*newpos[2]);
	if(fabs(val)>ContractGate &&
		score<EdgeGate &&
		score>=0 &&
		fabs(newpos[0]) <1.5 &&
		fabs(newpos[1]) <1.5 &&
		fabs(newpos[2]) <1.5)
	{
		newpos[0]+=(IMDATA)posx;
		newpos[1]+=(IMDATA)posy;
		newpos[2]+=(IMDATA)sk;
		if(newpos[0]>=0 && newpos[0]<=wid-1 && newpos[1]>=0 && newpos[1]<=hei-1 &&
			newpos[2]>=0 &&newpos[2]<=dss.smax-dss.smin)
		{
			//top++;
			return true;
		}
			//return newpos;
	}
	return false;//return NULL;
}  
