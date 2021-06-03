#ifndef _GATE_H
#define _GATE_H

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include "math.h"
using namespace std;

enum Type {PI, PO, AIG}; // 0->PI; 1->PO; 2->AND; 3->NOR.

namespace Gate {
  class gate{
    public:
        Type gateType;
        string in1Name{}, in2Name{}, outName{};
        bool inv1Val, inv2Val, invOut;
        int gateID{};
        int level{};
        int reverseLevel{};
        
        
        gate(Type gateType, string &portName) {
        this->gateType = gateType;
        this->in1Name = portName;
        this->outName = portName;
        this->inv1Val = 1;
        this->invOut = 1;
        this->level = -1;
        this->reverseLevel = -1;
        }
        
        gate(Type gateType, string &in1Name, string &in2Name, string &outName, string &inv1Val, string &inv2Val, string &invOut) {
          this->gateType = gateType;
          this->in1Name = in1Name;
          this->in2Name = in2Name;
          this->outName = outName;
          this->inv1Val = (inv1Val == "1");
          this->inv2Val = (inv2Val == "1");
          this->invOut = (invOut == "1");
          this->level = -1;
          this->reverseLevel = -1;
      }
        
        gate(){}
        ~gate(){}
        
        
        
  };
}



#endif
