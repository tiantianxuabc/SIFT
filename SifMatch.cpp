#include<windows.h>
#include<math.h>
#include<stdio.h>
#include<iostream>
using namespace std;
#include"SifMatch.h"

COUPLE * GetCouples(DESCRIPTOR * DeImg1,DESCRIPTOR * DeImg2,int DeNum1,int DeNum2)
{
	if(DeNum1==0 || DeNum2==0)return NULL;
	COUPLE *head=NULL,*p=NULL;
	int i,j,k;
	IMDATA sum=0;
	int closest[2];
	IMDATA clstdistance[2];
	for(i=0;i<DeNum1;i++)
	{
		clstdistance[0]=clstdistance[1]=10000;//2.0*Descriptordim;	
		closest[0]=closest[1]=-1;
		for(j=0;j<DeNum2;j++)
		{
			sum=0;
			for(k=0;k<NBP*NBP*NBO;k++)
				sum+=((DeImg1[i].serial[k])-(DeImg2[j].serial[k]))*((DeImg1[i].serial[k])-(DeImg2[j].serial[k]));
			if(sum<clstdistance[0])
			{
				clstdistance[1]=clstdistance[0];
				closest[1]=closest[0];
                clstdistance[0]=sum;
				closest[0]=j;
			}
			else
			{
				if(sum<clstdistance[1])
				{
					clstdistance[1]=sum;
					closest[1]=j;
				}
			}
		}
		if((closest[0]==-1 )||(closest[1]==-1))continue;
		if(clstdistance[1]==0)continue;
		if(clstdistance[0]*MatchGate2<clstdistance[1])
		{
			p=(COUPLE *)malloc(sizeof(COUPLE));
			p->descriptor1.oframe[0]=(DeImg1[i].oframe[0]);
			p->descriptor1.oframe[1]=(DeImg1[i].oframe[1]);
			p->descriptor2.oframe[0]=(DeImg2[closest[0]].oframe[0]);
			p->descriptor2.oframe[1]=(DeImg2[closest[0]].oframe[1]);
//			cout<<closest[0]<<"  "<<clstdistance[0]<<"  "<<i<<endl;
			p->next=head;
			head=p;
		}
	}
	return head;
}

int SaveCouple(char * filename,COUPLE * head)
{
	FILE *fp;
	int num=0;
	fp=fopen(filename,"wb");
	while(head!=NULL)
	{
		num++;
		fprintf(fp,"%f\t%f\t%f\t%f\n",head->descriptor1.oframe[0],head->descriptor1.oframe[1],head->descriptor2.oframe[0],head->descriptor2.oframe[1]);
		head=head->next;
	}
	cout<<"num couples:"<<num<<endl;
	fclose(fp);
	return num;
}

void ReadCouple(char * filename,COUPLE * &head)
{
	head=NULL;
	COUPLE *p=NULL;
	FILE *fp;
	int num=0;
	fp=fopen(filename,"rb");
	float pos[4];
	while(!feof(fp))
	{
		num++;
		fscanf(fp,"%f\t%f\t%f\t%f\n",&pos[0],&pos[1],&pos[2],&pos[3]);
		if(head==NULL)
		{
			head=(COUPLE *)malloc(sizeof(COUPLE));
			p=head;
		}
		else
		{
			head->next=(COUPLE *)malloc(sizeof(COUPLE));
			head=head->next;
		}
		head->descriptor1.oframe[0]=pos[0];
		head->descriptor1.oframe[1]=pos[1];
		head->descriptor2.oframe[0]=pos[2];
		head->descriptor2.oframe[1]=pos[3];
	}
	head->next=NULL;
	head=p;
	cout<<"num couples:"<<num<<endl;
	fclose(fp);
}

//NewCouple * GetNewCouples(DESCRIPTOR * DeImg1,DESCRIPTOR * DeImg2,int DeNum1,int DeNum2)
//{
//	if(DeNum1==0 || DeNum2==0)return NULL;
//	NewCouple *head=NULL,*p=NULL;
//	unsigned char *serial1,*serial2;
//	serial1=(unsigned char *)malloc(DeNum1*sizeof(unsigned char));
//	serial2=(unsigned char *)malloc(DeNum2*sizeof(unsigned char));
//	int i,j,k;
//	for(i=0;i<DeNum1;i++)serial1[i]=(unsigned char)(512*DeImg1.serial[i]);
//	for(i=0;i<DeNum2;i++)serial2[i]=(unsigned char)(512*DeImg2.serial[i]);
//	double sum=0;
//	int closest[2];
//	unsigned char clstdistance[2];
//	for(i=0;i<DeNum1;i++)
//	{
//		clstdistance[0]=clstdistance[1]=255;//2.0*Descriptordim;	
//		closest[0]=closest[1]=-1;
//		for(j=0;j<DeNum2;j++)
//		{
//			sum=0;
//			for(k=0;k<NBP*NBP*NBO;k++)sum+=abs((serial1[k])-(serial2[k]));
//			if(sum<clstdistance[0])
//			{
//				clstdistance[1]=clstdistance[0];
//				closest[1]=closest[0];
//                clstdistance[0]=sum;
//				closest[0]=j;
//			}
//			else
//			{
//				if(sum<clstdistance[1])
//				{
//					clstdistance[1]=sum;
//					closest[1]=j;
//				}
//			}
//		}
//		if((closest[0]==-1 )||(closest[1]==-1))continue;
//		if(clstdistance[1]==0)continue;
//		if((clstdistance[0]/clstdistance[1])<MatchGate)
//		{
//			p=(COUPLE *)malloc(sizeof(COUPLE));
//			p->descriptor1.oframe[0]=(DeImg1[i].oframe[0]);
//			p->descriptor1.oframe[1]=(DeImg1[i].oframe[1]);
//			p->descriptor2.oframe[0]=(DeImg2[closest[0]].oframe[0]);
//			p->descriptor2.oframe[1]=(DeImg2[closest[0]].oframe[1]);
////			cout<<closest[0]<<"  "<<clstdistance[0]<<"  "<<i<<endl;
//			p->next=head;
//			head=p;
//		}
//	}
//	return head;
//}