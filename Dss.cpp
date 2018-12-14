#include<windows.h>
#include<stdio.h>
#include<string>
#include<time.h>
#include<iostream>
using namespace std;
#include"Dss.h"
#include"Gss.h"
#include"Read_img.h"

void InitialDss(DSS &dss,GSS &gss)
{
	int time=clock();
	dss.O=gss.O;
	dss.S=gss.S;
	dss.omin=gss.omin;
	dss.smin=gss.smin;
	dss.smax=gss.smax-1;
	dss.sigma0=gss.sigma0;
	dss.octaves=(OCTAVE *)malloc(dss.O * sizeof(OCTAVE));
	int i,j,m;
	int so=1-dss.smin;
	int wid,hei;

	for(i=0;i<dss.O;i++)
	{
		wid=gss.octaves[i].imgs[0]->wid;
		hei=gss.octaves[i].imgs[0]->hei;
		dss.octaves[i].num=dss.smax+so;
		dss.octaves[i].imgs=(IMG **)malloc((dss.octaves[i].num)*sizeof(IMG *));
		for(j=0;j<dss.smax+so;j++)
		{
			dss.octaves[i].imgs[j]=(IMG *)malloc(sizeof(IMG));
			dss.octaves[i].imgs[j]->hei=hei;
			dss.octaves[i].imgs[j]->wid=wid;
			dss.octaves[i].imgs[j]->bmp=(IMDATA *)malloc(hei*wid*sizeof(IMDATA));
			for(m=0;m<wid*hei;m++)
				dss.octaves[i].imgs[j]->bmp[m]=gss.octaves[i].imgs[j+1]->bmp[m]-gss.octaves[i].imgs[j]->bmp[m];
		}
	}
	cout<<"dss costed:"<<clock()-time<<endl;
//	char filename[100];
//	for(i=0;i<dss.O;i++)
//		for(j=0;j<dss.smax+so;j++)
//		{
//			sprintf(filename,"C:\\±à³ÌÓÃ\\for_pic\\sift_ex3\\data\\%dxu.bmp",i*(dss.smax+so)+j+1);
//			SaveImg(dss.octaves[i].imgs[j],filename);
//		}
//	exit(0);
}