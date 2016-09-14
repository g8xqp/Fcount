#ifndef Fcount_h
#define Fcount_h
#include "Arduino.h"
#define IRQ2_SIZE_COUNT 20
#define TCONST 10

class Fcount{// max irq frequency 140kHz
 private:
  static volatile  unsigned int NewIRQcount1;
  unsigned int LastIRQcount1;
  static volatile  unsigned int LastIRQcount2;
#ifdef IRQ2_SIZE_COUNT
  static volatile  unsigned int LastIRQcount[IRQ2_SIZE_COUNT];
#endif
  static volatile  byte LastIRQptr;
  static volatile  unsigned int NewCount;
  static volatile  long NewFreq;
  static volatile  long NewTotal;
  static volatile  bool Changed;
  int IRQpin1,IRQpin2;
  static void MyISRp1();
  unsigned int UpdateIRQcount1();
  static void MyISRp2();
  void Init1();
  void Init2();
 public:
  void Init(int p1);
  void Init(int p1,int p2);
  unsigned int GetCount1();
  bool CheckNewCount2();
  unsigned int GetCount2();
  long GetTotal2();
  double GetFreq2();
  Fcount();
  ~Fcount();
};
#endif
