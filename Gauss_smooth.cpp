#include<math.h>
#include<malloc.h>
#include<iostream>
using namespace std;
#include<windows.h>
#include"Gauss_smooth.h"
#include"Resource.h"

void GetGaussTemp(IMDATA *Temp,int n,IMDATA sigma)
{
	IMDATA sum=0.0;
	int i;
	for(i=0;i<2*n+1;i++)
	{
		Temp[i]=exp(-(i-n)*(i-n)/(2.0*sigma*sigma));
		sum+=Temp[i];
	}
	
	for(i=0;i<2*n+1;i++)
	{
		Temp[i]/=sum;
	}
}

IMG * GaussSmooth(IMG * img,IMDATA sigma)
{
	int i,j,k;
	IMG *img2;	
	img2=(IMG *)malloc(sizeof(IMG));	
	img2->hei=img->hei;	
	img2->wid=img->wid;	
	img2->bmp=(IMDATA *)malloc((img2->wid)*(img2->hei)*sizeof(IMDATA));
	if(sigma>0.01)
	{
		IMG * img1;
        img1=(IMG *)malloc(sizeof(IMG));
		img1->hei=img->hei;
		img1->wid=img->wid;
		img1->bmp=(IMDATA *)malloc((img1->wid)*(img1->hei)*sizeof(IMDATA));
		IMDATA *temp;
		int tempn=ceil(4.0*sigma);
		tempn=2*tempn+1;
		temp=(IMDATA *)malloc(tempn*sizeof(IMDATA));
		GetGaussTemp(temp,(tempn-1)/2,sigma);
		IMDATA acc,incr;
		for(i=0;i<img->hei;i++)
		{
			for(j=0;j<img->wid;j++)
			{
				acc=0.0;				
				for(k=i-tempn/2;k<=i+tempn/2;k++)
				{
					if(k<=0)incr=img->bmp[j];
					else if(k>=(img->hei-1))incr=img->bmp[(img->hei-1)*(img->wid)+j];
					else incr=img->bmp[k*(img->wid)+j];
					acc+=(temp[k-i+tempn/2]*incr);
				}
				img1->bmp[i*(img2->wid)+j]=acc;
			}
		}
		for(i=0;i<img->hei;i++)
		{
			for(j=0;j<img->wid;j++)
			{				
				acc=0.0;
				for(k=j-tempn/2;k<=j+tempn/2;k++)
				{
					if(k<=0)incr=img1->bmp[i*(img1->wid)];
					else if(k>=(img1->wid-1))incr=img1->bmp[(1+i)*(img1->wid)-1];
					else incr=img1->bmp[i*(img1->wid)+k];
					acc+=(temp[k-j+tempn/2]*incr);
				}
				img2->bmp[i*(img2->wid)+j]=acc;
			}
		}
		free(img1->bmp);
		free(img1);
		free(temp);
	}
	else
	{
		memcpy(img2->bmp,img->bmp,(img->wid)*(img->hei)*sizeof(IMDATA));
	}	
	return img2;
}

void evolve(IMDATA * dest,IMDATA * src,int wid,int hei)
{
	IMDATA *pt1,*pt2,*pt_end;
	pt1=dest;
	pt2=src;
	pt_end=src+wid*hei;
	while(pt1!=pt_end)
	{
		IMDATA *first,*last;
		first=pt1;
	}
}
