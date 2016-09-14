#include <Fcount.h>

void Fcount::MyISRp1(){
  NewIRQcount1++;
}
unsigned int Fcount::UpdateIRQcount1(){
  unsigned int c,d;
  c=NewIRQcount1;
  d=c-LastIRQcount1;
  LastIRQcount1=c;
  return(d);
}
void Fcount::MyISRp2(){
  unsigned int c;
  c=NewIRQcount1;
  NewCount=c-LastIRQcount2;
  LastIRQcount2=c;
#ifdef IRQ2_SIZE_COUNT
  NewTotal-=LastIRQcount[LastIRQptr=(LastIRQptr+1)%IRQ2_SIZE_COUNT];
  NewTotal+=(LastIRQcount[LastIRQptr]=NewCount);
#else
  NewTotal-=(NewTotal/TCONST);
  NewTotal+=NewCount;
#endif
  Changed=true;
}
void Fcount::Init1(){
  pinMode(IRQpin1,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IRQpin1),MyISRp1, RISING);
}
void Fcount::Init2(){
  Init1();
  pinMode(IRQpin2,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IRQpin2),MyISRp2, RISING);
}
void Fcount::Init(int p1){
  IRQpin1=p1;
  Init1();
}
void Fcount::Init(int p1,int p2){
  IRQpin1=p1;
  IRQpin2=p2;
  Init2();
}
unsigned int Fcount::GetCount1(){
  return(UpdateIRQcount1());
}
bool Fcount::CheckNewCount2(){
  return(Changed);
}
unsigned int Fcount::GetCount2(){
  Changed=false; // race hazard!?
  return(NewCount);
}
long Fcount::GetTotal2(){
  Changed=false; // race hazard!?
  return(NewTotal);
}
double Fcount::GetFreq2(){
  double f;
#ifdef IRQ2_SIZE_COUNT
  f=GetTotal2();
  return(f/IRQ2_SIZE_COUNT);
#else
  f=GetTotal2();
  return(f/TCONST);
#endif
}
Fcount::Fcount(){
#ifdef IRQ2_SIZE_COUNT
  int i;
  for(i=0;i<IRQ2_SIZE_COUNT;i++)LastIRQcount[i]=0;
#endif
}
Fcount::~Fcount(){}
volatile unsigned int Fcount::NewIRQcount1=0;
volatile unsigned int Fcount::LastIRQcount2=0;
#ifdef IRQ2_SIZE_COUNT
volatile unsigned int Fcount::LastIRQcount[IRQ2_SIZE_COUNT];
#endif
volatile byte Fcount::LastIRQptr=0;
volatile unsigned int Fcount::NewCount=0;
volatile long Fcount::NewFreq=0;
volatile long Fcount::NewTotal=0;
volatile bool Fcount::Changed=false;

