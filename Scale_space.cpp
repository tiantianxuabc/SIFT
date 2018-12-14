#include<windows.h>
#include<math.h>
#include<string.h>
#include<stdio.h>
#include<time.h>
#include<iostream>
using namespace std;
#include"Scale_space.h"
#include"Gauss_smooth.h"
#include"Read_img.h"
//#include"Hesse.h"
//#include"Assign_orientation.h"
#include"Resource.h"
#include"Hesse.h"
#include"Orientation.h"
#include"Descriptor.h"

void GetKeyPoints(DSS &dss,GSS &gss,DESCRIPTOR * dscr,int &denum)//,
				  //DESCRIPTOR ** DeImg,int &DeNum)
{
	denum=0;
	int i,j,k,maxscale,minscale;
	int o;
	int wid,hei;
	int so=-dss.smin;
	IMDATA bins[2*NumBin];
	IMDATA rad;
	KEYPOINT key[NumKey];
	int top=0,currnum=0;
	int binnum=0;
	int time;
	for(o=0;o<dss.O;o++)
	{
		top=0;
		currnum=-1;
		hei=dss.octaves[o].imgs[0]->hei;
		wid=dss.octaves[o].imgs[0]->wid;
		time=clock();
		for(i=1;i<=hei-2;i++)
		{
			for(j=1;j<=wid-2;j++)
			{
				int pos=i*wid+j;
				maxscale=minscale=dss.smin;
				for(k=1;k<dss.smax+so+1;k++)
				{
					maxscale=minscale=k-so;
//					if((dss.octaves[o].imgs[k]->bmp[pos])>(dss.octaves[o].imgs[maxscale+so]->bmp[pos]))maxscale=k-so;
//					if((dss.octaves[o].imgs[k]->bmp[pos])<(dss.octaves[o].imgs[minscale+so]->bmp[pos]))minscale=k-so;
//				}
				if((maxscale!=dss.smin)&&(maxscale!=dss.smax))
				{
					for(;;)
					{
						rad=magnif*gss.sigma0*pow(2.0,maxscale/(IMDATA(gss.S)))*NBP/2 ;
						if(j<=rad || i<=rad || j>=wid-1-rad || i>=hei-1-rad)break;
						if(fabs(dss.octaves[o].imgs[maxscale+so]->bmp[pos])<0.00533)break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so]->bmp[pos-1])))break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so]->bmp[pos+1])))break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so]->bmp[pos-wid])))break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so]->bmp[pos+wid])))break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so]->bmp[pos-1-wid])))break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so]->bmp[pos+1-wid])))break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so]->bmp[pos-1+wid])))break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so]->bmp[pos+1+wid])))break;

						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so-1]->bmp[pos-1])))break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so-1]->bmp[pos+1])))break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so-1]->bmp[pos-wid])))break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so-1]->bmp[pos+wid])))break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so-1]->bmp[pos-1-wid])))break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so-1]->bmp[pos+1-wid])))break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so-1]->bmp[pos-1+wid])))break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so-1]->bmp[pos+1+wid])))break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so-1]->bmp[pos])))break;

						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so+1]->bmp[pos-1])))break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so+1]->bmp[pos+1])))break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so+1]->bmp[pos-wid])))break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so+1]->bmp[pos+wid])))break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so+1]->bmp[pos-1-wid])))break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so+1]->bmp[pos+1-wid])))break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so+1]->bmp[pos-1+wid])))break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so+1]->bmp[pos+1+wid])))break;
						if(NLG((dss.octaves[o].imgs[maxscale+so]->bmp[pos]),(dss.octaves[o].imgs[maxscale+so+1]->bmp[pos])))break;
//if(o==0)cout<<"rad:"<<rad<<"x:"<<j<<"y:"<<i<<endl;					

						if(!Localize(dss,j,i,maxscale,o+dss.omin,key[top].oframe))break;
						binnum=0;
                        GetOrientation(gss,key[top].oframe,o+dss.omin,bins,binnum);
						for(int inter=0;inter<binnum;inter++)
						{
							key[top+inter].octave=o+dss.omin;
							key[top+inter].oframe[0]=key[top].oframe[0];
							key[top+inter].oframe[1]=key[top].oframe[1];
							key[top+inter].oframe[2]=key[top].oframe[2];
							key[top+inter].oframe[3]=bins[inter];
						}
						top+=binnum;
//xxx+=binnum;
						break;
					}
				}
				if((minscale!=dss.smin)&&(minscale!=dss.smax))
				{
					for(;;)
					{
						rad=magnif*gss.sigma0*pow(2.0,minscale/(IMDATA(gss.S)))*NBP/2 ;		
						if(j<=rad || i<=rad || j>=wid-1-rad || i>=hei-1-rad)break;
						if(fabs(dss.octaves[o].imgs[minscale+so]->bmp[pos])<0.00533)break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so]->bmp[pos-1])))break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so]->bmp[pos+1])))break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so]->bmp[pos-wid])))break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so]->bmp[pos+wid])))break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so]->bmp[pos-1-wid])))break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so]->bmp[pos+1-wid])))break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so]->bmp[pos-1+wid])))break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so]->bmp[pos+1+wid])))break;

						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so-1]->bmp[pos-1])))break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so-1]->bmp[pos+1])))break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so-1]->bmp[pos-wid])))break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so-1]->bmp[pos+wid])))break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so-1]->bmp[pos-1-wid])))break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so-1]->bmp[pos+1-wid])))break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so-1]->bmp[pos-1+wid])))break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so-1]->bmp[pos+1+wid])))break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so-1]->bmp[pos])))break;


						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so+1]->bmp[pos-1])))break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so+1]->bmp[pos+1])))break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so+1]->bmp[pos-wid])))break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so+1]->bmp[pos+wid])))break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so+1]->bmp[pos-1-wid])))break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so+1]->bmp[pos+1-wid])))break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so+1]->bmp[pos-1+wid])))break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so+1]->bmp[pos+1+wid])))break;
						if(NLS((dss.octaves[o].imgs[minscale+so]->bmp[pos]),(dss.octaves[o].imgs[minscale+so+1]->bmp[pos])))break;
	//if(o==0)cout<<"rad:"<<rad<<"x:"<<j<<"y:"<<i<<endl;						
	
						if(!Localize(dss,j,i,minscale,o+dss.omin,key[top].oframe))break;
						binnum=0;
                        GetOrientation(gss,key[top].oframe,o+dss.omin,bins,binnum);
						for(int inter=0;inter<binnum;inter++)
						{
							key[top+inter].octave=o+dss.omin;
							key[top+inter].oframe[0]=key[top].oframe[0];
							key[top+inter].oframe[1]=key[top].oframe[1];
							key[top+inter].oframe[2]=key[top].oframe[2];
							key[top+inter].oframe[3]=bins[inter];
						}
						top+=binnum;
//xxx+=binnum;
						break;
					}
				}
			}}
		}
		cout<<o+gss.omin<<":"<<top<<",detect costed:"<<clock()-time<<endl;
		time=clock();
		for(int inter=0;inter<dss.smax-dss.smin+1;inter++)free(dss.octaves[o].imgs[inter]->bmp);
		if(denum+top<NumKey)
		{
			GetDescriptor(gss,&dscr[denum],key,top,o+dss.omin,currnum);
		    denum+=(currnum+1);
		}
		cout<<"descrip costed:"<<clock()-time<<endl;
	}
}