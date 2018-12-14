#include<malloc.h>
#include<windows.h>
#include<math.h>
#include"Resize_img.h"
#include"Resource.h"

IMG * halfsize(IMG *img)
{
	IMG *newimg=(IMG *)malloc(sizeof(IMG));
	newimg->wid=(img->wid+1)/2;
	newimg->hei=(img->hei+1)/2;
	int i,j;
	newimg->bmp=(IMDATA *)malloc((newimg->wid)*(newimg->hei)*sizeof(IMDATA));
	for(i=0;i<img->hei;i+=2)
		for(j=0;j<img->wid;j+=2)newimg->bmp[(i/2)*(newimg->wid)+j/2]=img->bmp[i*(img->wid)+j];
	return newimg;
}

IMG * doublesize(IMG *img)
{
    IMG *newimg=(IMG *)malloc(sizeof(IMG));
	newimg->wid=img->wid*2;
	newimg->hei=img->hei*2;
	int i,j;
	newimg->bmp=(IMDATA *)malloc((newimg->wid)*(newimg->hei)*sizeof(IMDATA));
	for(i=0;i<newimg->hei;i+=2)
		for(j=0;j<newimg->wid;j+=2)newimg->bmp[i*newimg->wid+j]=img->bmp[i/2*img->wid+j/2];
	for(i=1;i<newimg->hei-1;i+=2)
		for(j=1;j<newimg->wid-1;j+=2)newimg->bmp[i*newimg->wid+j]=0.25*(img->bmp[i/2*img->wid+j/2]+img->bmp[i/2*img->wid+j/2+1]+img->bmp[(i/2+1)*img->wid+j/2]+img->bmp[(i/2+1)*img->wid+j/2+1]);
	for(i=0;i<newimg->hei;i+=2)
		for(j=1;j<newimg->wid-1;j+=2)newimg->bmp[i*newimg->wid+j]=0.5*(img->bmp[i/2*img->wid+j/2]+img->bmp[i/2*img->wid+j/2+1]);
	for(i=1;i<newimg->hei-1;i+=2)
		for(j=0;j<newimg->wid;j+=2)newimg->bmp[i*newimg->wid+j]=0.5*(img->bmp[i/2*img->wid+j/2]+img->bmp[(i/2+1)*img->wid+j/2]);
	for(i=1;i<=newimg->hei;i++)newimg->bmp[i*(newimg->wid)-1]=0;
	return newimg;
}
