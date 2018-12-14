#include<windows.h>
#include<iostream>
#include<math.h>
#include<time.h>
#include<string>
using namespace std;
#include"Gss.h"
#include"Resize_img.h"
#include"Gauss_smooth.h"
#include"Read_img.h"

void InitialGss(GSS &gss,IMG * &img)
{
	int time=clock();
	//初始基本参数
	gss.S=3;
	IMDATA k;
	k=pow(2.0,1.0/(gss.S));
	gss.sigma0=1.6*k;
	gss.omin=0;
	gss.smin=-1;
	gss.smax=gss.S+1;
	IMDATA sigman=0.5;
	gss.O=int(log(min(img->hei,img->wid))/log(2.0))-gss.omin-3;
	gss.octaves=(OCTAVE *)malloc(gss.O * sizeof(OCTAVE));
    //缩放图像
	int i,j;
	IMG *Oldimg;
	if(gss.omin<0)
	{
		for(i=0;i<-gss.omin;i++)
		{
			Oldimg=img;
			img=doublesize(img);
			free(Oldimg);
		}
	}
	if(gss.omin>0)
	{
		for(i=0;i<gss.omin;i++)
		{
			Oldimg=img;
			img=halfsize(img);
			free(Oldimg);
		}
	}
    //构建高斯金字塔
	int so=1-gss.smin;
	IMDATA dsigma0,dx;
	gss.octaves[0].num=gss.smax+so;
	gss.octaves[0].imgs=(IMG **)malloc((gss.octaves[0].num)*sizeof(IMG *));
	dsigma0=gss.sigma0*sqrt(1.0-1.0/k/k);
	dx=dsigma0*pow(k,gss.smin);
	gss.octaves[0].imgs[0]=GaussSmooth(img,1.249);
	for(i=1;i<gss.smax+so;i++)
	{
		dx*=k;
		gss.octaves[0].imgs[i]=GaussSmooth(gss.octaves[0].imgs[i-1],dx);
	}
	int sbest=min(gss.smin+gss.S,gss.smax);
	for(i=1;i<gss.O;i++)
	{
		//Oldimg=img;
		img=halfsize(gss.octaves[i-1].imgs[sbest+so]);
		//free(Oldimg);
		IMDATA target=gss.sigma0*pow(k,gss.smin);

	    gss.octaves[i].num=gss.smax+so;
	    gss.octaves[i].imgs=(IMG **)malloc((gss.octaves[i].num)*sizeof(IMG *));

		IMDATA prev=gss.sigma0*pow(k,sbest-gss.S);
		if(target>prev)gss.octaves[i].imgs[0]=GaussSmooth(img,target*target-prev*prev);
		else gss.octaves[i].imgs[0]=img;
		dx=dsigma0*pow(k,gss.smin);
		for(j=1;j<gss.smax+so;j++)
		{
			dx*=k;
			gss.octaves[i].imgs[j]=GaussSmooth(gss.octaves[i].imgs[j-1],dx);
		}
	}
	cout<<"gss initial time:"<<clock()-time<<endl;
}