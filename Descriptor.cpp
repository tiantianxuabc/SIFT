#include<windows.h>
#include<malloc.h>
#include<math.h>
#include<iostream>
#include<time.h>
using namespace std;
#include"Descriptor.h"

IMDATA fast_mod(IMDATA th)
{
  while(th<0)th+=2*pi;
  while(th>2*pi)th-=2*pi;
  return th ;
}

int fast_floor(IMDATA x)
{
  return (int)(x-((x>=0)?0:1)); 
}

void normalize(IMDATA *serial,int num)
{
	int i;
	IMDATA sum=0.0;
	for(i=0;i<num;i++)sum+=serial[i]*serial[i];
	sum=sqrt(sum);
	for(i=0;i<num;i++)serial[i]/=sum;
}

void GetDescriptor(GSS &gss,DESCRIPTOR * dscr,KEYPOINT * key,int keynum,int octave,int &denum)
{
	denum=-1;
	IMDATA *Gradi;
	IMDATA DX,DY;
	
	int s,j,i,m;
	int o=octave-gss.omin;
	int wid,hei;
	wid=gss.octaves[o].imgs[0]->wid;
	hei=gss.octaves[o].imgs[0]->hei;
	int bufsize;
	bufsize=(wid*hei*(gss.smax-gss.smin+1)+0x7f)&(~0x7f);
	Gradi=(IMDATA *)malloc(2*bufsize*sizeof(IMDATA));
	if(!Gradi){cout<<"¿Õ¼ä²»×ã!"<<endl;exit(0);}
//	double *Mpt=Gradi+wid,*Tpt=Gradi+bufsize+wid;
//	double *Gpt;
#define At(dx,dy) (gss.octaves[o].imgs[s]->bmp[(i+dy)*wid+j+dx])
	int time=clock();
	for(s=0;s<gss.smax-gss.smin+1;s++)
	{
//		Gpt=gss.octaves[o].imgs[s]->bmp+wid;
		for(i=1;i<hei-1;i++)
		{			
			//Mpt++;
			//Tpt++;
			//Gpt++;
			for(j=1;j<wid-1;j++)
			{
				DX=0.5*(At(1,0)-At(-1,0));
				DY=0.5*(At(0,1)-At(0,-1));
				//DX=0.5*(*(Gpt+1)-*(Gpt-1));
				//DY=0.5*(*(Gpt+wid)-*(Gpt-wid));
				Gradi[s*wid*hei+i*wid+j]=sqrt(DX*DX+DY*DY);
				//*Mpt=sqrt(DX*DX+DY*DY);
				Gradi[s*wid*hei+i*wid+j+bufsize]=atan2(DY,DX);
				//*Tpt=atan2(DY,DX);
//				Mpt++;
//				Tpt++;
//				Gpt++;
			}

		}
	}
	cout<<"gradient costed:"<<clock()-time<<"  ";
	IMDATA posx,posy,scale,theta0,cth0,sth0;
	int xi,yi,si;
	IMDATA SBP;
	int W,bin,dxi,dyi;
	IMDATA mod,angle,theta,dox,doy,nx,ny,nt,wsigma,contri;
	int binx,biny,bint,dbinx,dbiny,dbint;
	IMDATA rbinx,rbiny,rbint,weight;
	for(m=0;m<keynum;m++)
	{
		posx=key[m].oframe[0];
		posy=key[m].oframe[1];
		scale=key[m].oframe[2];
		theta0=(key[m].oframe[3]);//*2*pi/NumBin;
		sth0=sin(theta0);
		cth0=cos(theta0);
		xi=(int)floor(posx+0.5);
		yi=(int)floor(posy+0.5);
		si=(int)floor(scale+(IMDATA)gss.smin+0.5)-gss.smin;
		if(xi<0 || yi<0 || xi>wid-1 || yi>hei-1 || si<0 || si>gss.smax-gss.smin)continue;
		else denum++;
		SBP=3.0*(gss.sigma0)*pow(2.0,((IMDATA)(scale+(IMDATA)gss.smin))/((IMDATA)(gss.S)));
		W=(int)floor(sqrt(2.0)*SBP*(NBP+1)/2.0+0.5);
        for(i=0;i<NBP*NBP*NBO;i++)dscr[denum].serial[i]=0.0;
		for(dyi=max(-W,1-yi);dyi<=min(W,hei-2-yi);dyi++)
		{
			for(dxi=max(-W,1-xi);dxi<=min(W,wid-2-xi);dxi++)
			{
				mod=Gradi[si*wid*hei+(yi+dyi)*wid+dxi+xi];
				angle=Gradi[bufsize+si*wid*hei+(yi+dyi)*wid+dxi+xi];
				theta=fast_mod(angle-theta0);
				dox=(IMDATA)(xi+dxi)-posx;
				doy=(IMDATA)(yi+dyi)-posy;
				nx=(cth0*dox+sth0*doy)/SBP;
				ny=(-sth0*dox+cth0*doy)/SBP;
                nt=NBO*theta/2.0/pi;
				wsigma=NBP/2.0;
				contri=exp(-(nx*nx+ny*ny)/2.0/wsigma/wsigma);
				binx=fast_floor(nx-0.5);
				biny=fast_floor(ny-0.5);
				bint=fast_floor(nt);
                rbinx=nx-((IMDATA)binx+0.5) ;
                rbiny=ny-((IMDATA)biny+0.5) ;
                rbint=nt-(IMDATA)bint ;
				for(dbiny=0;dbiny<2;dbiny++)
					for(dbinx=0;dbinx<2;dbinx++)
						for(dbint=0;dbint<2;dbint++)
						{
							if( binx+dbinx >= -(NBP/2) &&
                                binx+dbinx <   (NBP/2) &&
                                biny+dbiny >= -(NBP/2) &&
                                biny+dbiny <   (NBP/2) )
							{
								weight=contri*mod*fabs(1-(IMDATA)dbinx-rbinx)
                                        *fabs(1-(IMDATA)dbiny-rbiny)*fabs(1-(IMDATA)dbint-rbint);
								dscr[denum].serial[(NBP/2+biny+dbiny)*NBO*NBP+(NBP/2+binx+dbinx)*NBO+(bint+dbint+NBO)%NBO]+=weight;									
							}
                
						}
			}
		}
		normalize(dscr[denum].serial,NBO*NBP*NBP);
		for(bin=0;bin<NBO*NBP*NBP;bin++)
			if(dscr[denum].serial[bin]>0.2)dscr[denum].serial[bin]=0.2;
		normalize(dscr[denum].serial,NBO*NBP*NBP);
		dscr[denum].octave=octave;
		dscr[denum].oframe[0]=(key[m].oframe[0])*pow(2.0,(IMDATA)octave);
		dscr[denum].oframe[1]=(key[m].oframe[1])*pow(2.0,(IMDATA)octave);
		dscr[denum].oframe[2]=gss.sigma0*pow(2.0,((IMDATA)octave)+(scale+((IMDATA)gss.smin))/((double)gss.S));
		dscr[denum].oframe[3]=key[m].oframe[3];
	}
	free(Gradi);
}