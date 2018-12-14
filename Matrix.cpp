#include<iostream>
#include<time.h>
#include<math.h>
#include<malloc.h>
using namespace std;
#include"Matrix.h"

void Display(IMDATA * Matrix,int hei,int wid)
{
	if(!Matrix)return;
	cout<<endl;
	for(int i=0;i<hei;i++)
	{
		for(int j=0;j<wid;j++)
		{
			cout<<Matrix[i*wid+j]<<"\t";
		}
		cout<<endl;
	}
}

IMDATA GetMatrixValue(IMDATA * Matrix,int wid)
{
	if(wid==1)return Matrix[0];
	IMDATA value=0;
	int n,j,i;
	IMDATA *child,para;
    child=(IMDATA *)malloc((wid-1)*(wid-1)*sizeof(IMDATA));
	for(n=0;n<wid;n++)
	{
		for(i=1;i<wid;i++)
		{
			for(j=1;j<wid;j++)
			{
				child[(i-1)*(wid-1)+(j-1)]=Matrix[i*wid+(j+n)%wid];				
			}
		}
		if((n*(wid-n))%2)para=-1.0;
		else para=1.0;
		value+=para*Matrix[n]*GetMatrixValue(child,wid-1);
	}
	free(child);
	return value;
}

IMDATA * Multiple(IMDATA *Mat1,IMDATA * Mat2,int h1,int w1,int h2,int w2)
{
	if(w1!=h2)return NULL;
	IMDATA *Mat=(IMDATA *)malloc(h1*w2*sizeof(IMDATA));
	int i,j,k;
	for(i=0;i<h1;i++)
	{
		for(j=0;j<w2;j++)
		{
			Mat[i*w2+j]=0;
			for(k=0;k<w1;k++)Mat[i*w2+j]+=Mat1[i*w1+k]*Mat2[k*w2+j];
		}
	}
	return Mat;
}

bool GetNi(IMDATA * Matrix1,IMDATA * Matrix2,int wid)
{
	if(!Matrix1)return false;
	IMDATA value=GetMatrixValue(Matrix1,wid);
	if(value==0)return false;
	int m,n,j,i;
	IMDATA *child,para;
    child=(IMDATA *)malloc((wid-1)*(wid-1)*sizeof(IMDATA));
	for(m=0;m<wid;m++)
	{
		for(n=0;n<wid;n++)
		{
			for(i=1;i<wid;i++)
			{
				for(j=1;j<wid;j++)
				{
					child[(i-1)*(wid-1)+(j-1)]=Matrix1[((i+m)%wid)*wid+(j+n)%wid];				
				}
			}
			if((n*(wid-n)+m*(wid-m))%2)para=-1.0;
			else para=1.0;
			Matrix2[n*wid+m]=para*GetMatrixValue(child,wid-1)/value;
		}
	}
	free(child);
	return true;
}