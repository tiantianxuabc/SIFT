#ifndef SifMatch_h
#define SifMatch_h
#include"Resource.h"
#include"Descriptor.h"

struct COUPLE{
	DESCRIPTOR descriptor1,descriptor2;
	COUPLE *next;
};
//struct NewCouple{
//	int x1,y1,x2,y2;
//};

COUPLE * GetCouples(DESCRIPTOR * DeImg1,DESCRIPTOR * DeImg2,int DeNum1,int DeNum2);
//NewCouple * GetNewCouples(DESCRIPTOR * DeImg1,DESCRIPTOR * DeImg2,int DeNum1,int DeNum2);
int SaveCouple(char * filename,COUPLE * head);
void ReadCouple(char * filename,COUPLE * &head);
#endif