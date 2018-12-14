#include<windows.h>
#include<malloc.h>
#include<iostream>
#include<math.h>
using namespace std;
#include"Read_img.h"

void GetImg(char *filename,IMG * img)
{
	BITMAPFILEHEADER Bmpfh;
	BITMAPINFO Bmpinfo;
	FILE *fp;
	fp=fopen(filename,"rb");
	if(!fp)
	{
		cout<<filename<<"打开失败!"<<endl;
		exit(0);
	}
	fread(&Bmpfh,sizeof(Bmpfh),1,fp);
	fread(&Bmpinfo,sizeof(BITMAPINFO),1,fp);//暂时处理24位真彩
	img->wid=Bmpinfo.bmiHeader.biWidth;
	int readwid=(img->wid+3)/4*4;
	img->hei=Bmpinfo.bmiHeader.biHeight;
	long maplength;
	maplength=img->wid*img->hei;
	unsigned char color[3];
	img->bmp=(IMDATA *)malloc(maplength*sizeof(IMDATA));
	img->bmp=(IMDATA *)GlobalLock((HGLOBAL)img->bmp);
	fseek(fp,Bmpfh.bfOffBits,0);
	int i,j;
	IMDATA minp=1.0,maxp=0.0,mp;
	for(j=0;j<img->hei;j++)
		for(i=0;i<readwid;i++)
		{
			fread(color,1,3,fp);
			mp=img->bmp[(img->hei-j-1)*(img->wid)+i]=((IMDATA)(0.114*((IMDATA)color[0])+0.587*((IMDATA)color[1])+0.299*((IMDATA)color[2])))/255.0;
			if(mp>maxp)maxp=mp;
			if(mp<minp)minp=mp;
		}
	for(i=0;i<(img->hei)*(img->wid);i++)img->bmp[i]=(img->bmp[i]-minp)/(maxp-minp);
	fclose(fp);
	GlobalUnlock((HGLOBAL)img->bmp);
}

void LineImg(IMG * img,double x1,double y1,double x2,double y2)
{
	double i,j;
	if(x1!=x2)
	{
		for(i=x1;i<=x2;i+=1)
		{
			j=(i-x1)/(x2-x1)*(y2-y1)+y1;
			if(j<0||j>img->hei)continue;
			img->bmp[(int)((int)j*(img->wid)+i)]=1;
		}
	}
	else if(y1!=y2)
	{
		for(j=y1;j<=y2;j+=1)
		{
			i=(j-y1)/(y2-y1)*(x2-x1)+x1;
			if(i<0||i>img->wid)continue;
			img->bmp[(int)((int)j*(img->wid)+i)]=1;
		}
	}
}

IMG * MergeImg(IMG * img1,IMG *img2)
{
	if(!img1 || !img2)return NULL;
	IMG * img;
	img=(IMG *)malloc(sizeof(IMG));
	img->hei=max(img1->hei,img2->hei);
	img->wid=img1->wid+10+img2->wid;
	int i,j;
	img->bmp=(double *)malloc(img->hei*img->wid*sizeof(double));
	for(i=0;i<img->hei;i++)
		for(j=0;j<img->wid;j++)img->bmp[i*img->wid+j]=0.6;
	for(i=0;i<img1->hei;i++)
		for(j=0;j<img1->wid;j++)img->bmp[i*img->wid+j]=img1->bmp[i*img1->wid+j];
    for(i=0;i<img2->hei;i++)
		for(j=0;j<img2->wid;j++)img->bmp[i*img->wid+j+10+img1->wid]=img2->bmp[i*img2->wid+j];
	return img;
}

void SaveImg(IMG * img,std::string newfilename)
{
	int savedwid=(img->wid+3)/4*4;
	
	BITMAPFILEHEADER Bmpfh;
	BITMAPINFO Bmpinfo;
	Bmpfh.bfOffBits=54;
	Bmpfh.bfReserved1=0;
	Bmpfh.bfReserved2=0;
	Bmpfh.bfSize=58+3*savedwid*(img->hei);
	Bmpfh.bfType=19778;
	FILE *fout;
	fout=fopen(newfilename.c_str(),"wb");
	Bmpinfo.bmiHeader.biBitCount=24;
    Bmpinfo.bmiHeader.biClrImportant=0;
	Bmpinfo.bmiHeader.biClrUsed=0;
	Bmpinfo.bmiHeader.biCompression=0;
	Bmpinfo.bmiHeader.biHeight=img->hei;
	Bmpinfo.bmiHeader.biPlanes=1;
	Bmpinfo.bmiHeader.biSize=40;
	Bmpinfo.bmiHeader.biSizeImage=3*savedwid*(img->hei);
	Bmpinfo.bmiHeader.biWidth=savedwid;
	Bmpinfo.bmiHeader.biXPelsPerMeter=2834;
	Bmpinfo.bmiHeader.biYPelsPerMeter=2834;
	rewind(fout);
	fwrite(&Bmpfh,sizeof(Bmpfh),1,fout);
	fwrite(&Bmpinfo,sizeof(Bmpinfo),1,fout);
	int i,j;
	unsigned char pixel;
	for(i=0;i<img->hei;i++)
	{
		for(j=0;j<savedwid;j++)
		{
			if(j>=img->wid)pixel=255;
			else pixel=(unsigned char)fabs(((img->bmp[(img->hei-i-1)*img->wid+j])*255.0));
			fwrite(&pixel,1,1,fout);
			fwrite(&pixel,1,1,fout);
			fwrite(&pixel,1,1,fout);
		}
	}
	fclose(fout);
}