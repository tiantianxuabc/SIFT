#ifndef Match_exam
#define Match_exam
#include"Resource.h"
#include"SifMatch.h"
#include"Descriptor.h"

double GetAngle(COUPLE * head);
void TickOut(COUPLE * &head,double theta);
bool GetTransMatrix(COUPLE *head,double * &Matrix,int order);
void TickFromTrans(COUPLE * &head,double * Matrix);
#endif
