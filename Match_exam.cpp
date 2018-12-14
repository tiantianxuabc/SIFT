#include<windows.h>
#include<math.h>
#include<iostream>
using namespace std;
#include"Match_exam.h"
#include"Matrix.h"
#include"Resource.h"

double GetAngle(COUPLE * head)
{
	COUPLE *p;
	p=head;
	int num=0;
	double theta=0;
	while(p)
	{
		theta+=atan2(p->descriptor1.oframe[1]-p->descriptor2.oframe[1],p->descriptor1.oframe[0]-p->descriptor2.oframe[0]);
		num++;
		p=p->next;
	}
	if(num==0)return -1000;
	theta/=num;
	return fast_mod(theta);
}

void TickOut(COUPLE * &head,double theta)
{
	if(theta<0 || theta>2*pi)return;
	COUPLE *p,*q;
	q=p=head;
	double th=0;
	while(p)
	{
		th=atan2(p->descriptor1.oframe[1]-p->descriptor2.oframe[1],p->descriptor1.oframe[0]-p->descriptor2.oframe[0]);
		th=fast_mod(th);
		if(fabs(th-theta)>0.5)
		{
			if(p==q)
			{
			    p=p->next;
				head=p;
				free(q);
				q=p;
			}
			else
			{
				q->next=p->next;
				free(p);
				p=q->next;
			}
		}
		else
		{
 			q=p;
			p=p->next;
		}
	}
}

bool GetTransMatrix(COUPLE *head,double * &Matrix,int order)
{
	if(!head)return false;
	if(!(head->next))return false;
	double aid1[4],aid2[4],aid3[4];
	aid1[0]=head->descriptor1.oframe[0];
	aid1[1]=head->descriptor1.oframe[1];
	aid1[2]=head->next->descriptor1.oframe[0];
	aid1[3]=head->next->descriptor1.oframe[1];
	aid2[0]=head->descriptor2.oframe[0];
	aid2[1]=head->descriptor2.oframe[1];
	aid2[2]=head->next->descriptor2.oframe[0];
	aid2[3]=head->next->descriptor2.oframe[1];
	if(GetNi(aid1,aid3,2)==false)return false;
	Matrix=Multiple(aid2,aid3,2,2,2,2);
	return true;
}

void TickFromTrans(COUPLE * &head,double * Matrix)
{
	if(!Matrix)return;
	COUPLE *p,*q;
	q=p=head;
	double aid1[2],aid2[2],*aid3;
	int num=0;
	while(p)
	{
		aid1[0]=p->descriptor1.oframe[0];
		aid1[1]=p->descriptor1.oframe[1];
		aid2[0]=p->descriptor2.oframe[0];
		aid2[1]=p->descriptor2.oframe[1];
		aid3=Multiple(Matrix,aid1,2,2,2,1);
		if((aid2[0]-aid3[0])*(aid2[0]-aid3[0])+(aid2[1]-aid3[1])*(aid2[1]-aid3[1])>10000)
		{
			if(p==q)
			{
			    p=p->next;
				head=p;
				free(q);
				q=p;
			}
			else
			{
				q->next=p->next;
				free(p);
				p=q->next;
			}
		}
		else
		{
			num++;
 			q=p;
			p=p->next;
		}
		free(aid3);
	}
	cout<<num<<endl;
}