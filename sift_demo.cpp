#include<iostream>
#include<malloc.h>
#include<stdio.h>
#include<time.h>
#include<math.h>

#include"Read_img.h"
#include"Gss.h"
#include"Dss.h"
#include"Scale_space.h"
#include"Descriptor.h"
#include"Img_descr.h"
#include"SifMatch.h"
#include"Match_exam.h"
#include"sift_demo.h"

#ifdef _DEBUG
#pragma comment(lib, "opencv_world400d.lib")
#else
#pragma comment(lib, "opencv_world400.lib")
#endif

void sift_demo1()
{
	char filename1[]="wadham004.bmp";
	char filename2[]="wadham005.bmp";
	char filecouple[]="matchtxt\\lab4.txt";
	DESCRIPTOR *dscr1,*dscr2;
	dscr1=(DESCRIPTOR *)malloc(NumKey*sizeof(DESCRIPTOR));
	if(!dscr1)exit(0);
    dscr2=(DESCRIPTOR *)malloc(NumKey*sizeof(DESCRIPTOR));
	if(!dscr2)exit(0);
	int time=clock();
	int denum1=0,denum2=0;
    ImgDescri(filename1,dscr1,denum1);
	ImgDescri(filename2,dscr2,denum2);
	COUPLE *head=NULL,*p=NULL;
	head=GetCouples(dscr1,dscr2,denum1,denum2);
	std::cout<<"time costed:"<<clock()-time<<"ms."<<std::endl;
 //	exit(0);
	TickOut(head,GetAngle(head));
//	SaveCouple(filecouple,head);
	IMG img1,img2,*img;
	GetImg(filename1,&img1);
	GetImg(filename2,&img2);
	img = MergeImg(&img1,&img2);
	p=head;
	while(p)
	{
		LineImg(img,p->descriptor1.oframe[0],p->descriptor1.oframe[1],p->descriptor2.oframe[0]+(double)(img1.wid+10),p->descriptor2.oframe[1]);
	    p=p->next;
	}
 	SaveImg(img, "Output.bmp");
	free(img->bmp);
	free(img1.bmp);
	free(img2.bmp);
	free(img);
	p=head;
	int num=0;
	while(head)
	{
		p = head;
		head = head->next;
		num++;
		free(p);
	}
	std::cout<<"matched:"<<num<<std::endl;
	free(dscr1);
	free(dscr2);
	getchar();
	exit(1);
}