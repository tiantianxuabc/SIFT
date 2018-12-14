#include<windows.h>
#include<stdio.h>
#include<time.h>
#include<iostream>
using namespace std;
#include"Img_descr.h"

void ImgDescri(char *filename,DESCRIPTOR * dscr,int &denum)
{
    IMG *img;
	img=(IMG *)malloc(sizeof(IMG));
	GSS gss;
	DSS dss;
	denum=0;
	int o,s;
	GetImg(filename,img);
	InitialGss(gss,img);
	InitialDss(dss,gss);
	GetKeyPoints(dss,gss,dscr,denum);
	cout<<"denum:"<<denum<<endl;
	for(o=0;o<gss.O;o++)
		for(s=0;s<gss.smax-gss.smin+1;s++)free(gss.octaves[o].imgs[s]->bmp);
//	FILE *fp;
//	fp=fopen("C:\\±‡≥Ã”√\\for_pic\\edit_pics2\\keynodes.txt","wb");
//	for(int i=0;i<denum;i++)fprintf(fp,"%f\t%f\t%d\n",dscr[i].oframe[0],dscr[i].oframe[1],(int)(dscr[i].oframe[3]/2/pi*36));
}