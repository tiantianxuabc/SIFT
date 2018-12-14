#include<windows.h>
#include<malloc.h>
#include<math.h>
#include"Orientation.h"

void GetOrientation(GSS &gss,IMDATA * oframe,int octave,IMDATA * bins,int &binnum)
{
	binnum=0;
	int x=(int)(oframe[0]+0.5);
	int y=(int)(oframe[1]+0.5);
	int s=(int)(oframe[2]+0.5);
	int octk=octave-gss.omin;
	int wid,hei;
	wid=gss.octaves[octk].imgs[0]->wid;
	hei=gss.octaves[octk].imgs[0]->hei;
	IMDATA BIN[NumBin];
	IMDATA sigmaw=Win_factor*(gss.sigma0)*pow(2.0,(oframe[2])/((IMDATA)(gss.S)));
	int WIDTH=(int)(floor(3*sigmaw));
	int i,j;
	for(i=0;i<NumBin;i++)BIN[i]=0.0;
	if(x<1 || x>wid-1 || y<1 || y>hei-1 || s<0 || s>gss.smax-gss.smin)
	{
		binnum=0;
		return;
	}
	IMDATA DX,DY,xoff,yoff;
	IMDATA contri,mod;
	int theta;

#define At(dx,dy) gss.octaves[octk].imgs[s]->bmp[(y+dy)*wid+(x+dx)]

    for(i=max(-WIDTH,1-y);i<=min(WIDTH,hei-y-2);i++)
		for(j=max(-WIDTH,1-x);j<=min(WIDTH,wid-x-2);j++)
		{
			DX=0.5*(At(j+1,i)-At(j-1,i));
			DY=0.5*(At(j,i+1)-At(j,i-1));
			xoff=((IMDATA)(j+x))-oframe[0];
			yoff=((IMDATA)(i+y))-oframe[1];
			if(xoff*xoff+yoff*yoff>=(IMDATA(WIDTH*WIDTH))+0.5)continue;
			contri=exp(-(xoff*xoff+yoff*yoff)/2/sigmaw/sigmaw);
			mod=sqrt(DX*DX+DY*DY);
			theta=((int)((atan2(DY,DX))/2/pi*NumBin+2*NumBin))%NumBin;
			BIN[theta]+=contri*mod;
		}
	for(i=0;i<6;i++)//6 is remarkable
	{
		IMDATA prev=BIN[NumBin-1];
		for(j=0;j<NumBin;j++)
		{
			IMDATA newh=(prev+BIN[j]+BIN[(j+1)%NumBin])/3.0;
			prev=BIN[j];
			BIN[j]=newh;
		}
	}
	IMDATA maxh=BIN[0];
	IMDATA hs[3];
	for(i=1;i<NumBin;i++)maxh=max(maxh,BIN[i]);
	for(i=0;i<NumBin;i++)
	{
		hs[0]=BIN[(i-1+NumBin)%NumBin];
		hs[1]=BIN[i];
		hs[2]=BIN[(i+1)%NumBin];
		if(hs[1]>0.8*maxh && hs[1]>hs[0] && hs[1]>hs[2])
		{
			IMDATA di=-0.5*(hs[2]-hs[0])/(hs[2]+hs[0]-2*hs[1]);
			IMDATA th=2*pi*(((IMDATA)(i+di))+0.5)/NumBin;
            bins[binnum]=th;
			binnum++;
		}
	}
}
