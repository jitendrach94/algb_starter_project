#ifndef POLY_H
#define POLY_H
#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <set>
#include <map>
#include "Gate.h"
#include "Circuit.h"
#include <chrono>

using namespace Circuit;
using namespace Gate;
using namespace std;
using namespace std::chrono; 


//Representing coeff 2^a[0] * a[1].
namespace Poly{
class poly{
  
public:
struct constMono
{
  int sign=1;
  long int coeff[2]{0,1};
  int val{};
};
struct mono
{
  int sign=1;
  long int coeff[2]{0,1};
  int nVar=0;
  set<int> Var;
};
struct polyExpr
{
   vector<mono> monomial{};
   constMono constant{};
};

 poly(){}
 ~poly(){}

void printMono(mono &temp)
{
    if(temp.sign == 1){
        cout<< " + ";
    }else{
        cout<< " - ";
    }
    cout<<"2^"<<temp.coeff[0]<<"*"<<temp.coeff[1]<<"( ";
    for(auto item : temp.Var)
    {
        cout<<item<<" ";
    }
    cout<<")"<<endl;
}

void outputSignature(vector<mono> &outSig, map<string, int> &outList)
{
    map<string, int>::iterator iter=outList.begin();
    int i=0;
    while(iter!=outList.end())
    {
        mono temp{};
        temp.nVar=1;
        temp.Var.insert(iter->second);
        temp.coeff[0]=i;
        outSig.push_back(temp);
        i++;
        iter++;
    }
    reverse(outSig.begin(), outSig.end());
}

void printOutSignature(vector<mono> &outSign)
{
    vector<mono>::iterator iter=outSign.begin();
    while(iter!=outSign.end())
    {
        cout<< " + " << "2^" <<iter->coeff[0]<<"*"<<iter->coeff[1]<< "( ";
        for(auto item : iter->Var)
            cout<<item<<" ";
        cout<<")";
        iter++;
    }
    cout<<endl;
}
 
void genPoly(polyExpr &temp, int in1, int in2, int out, bool in1Val, bool in2Val, bool outVal)
{
    //cout<<in1<<"\t"<<in2<<"\t"<<out<<endl;
    if(outVal == 1)
    {
        if(in1Val == 1)
        {
            if(in2Val == 1)
            {
                //------xy
                mono temp1{};
                temp1.nVar=2;
                temp1.sign=1;
                temp1.Var.insert(in1);
                temp1.Var.insert(in2);
                temp.monomial.push_back(temp1);
            }else{
                //------x(1-y)
                mono temp1{};
                mono temp2{};
                temp1.nVar=1;
                temp1.sign=1;
                temp1.Var.insert(in1);
                temp2.nVar=2;
                temp2.Var.insert(in1);
                temp2.Var.insert(in2);
                temp2.sign=-1;
                temp.monomial.push_back(temp1);
                temp.monomial.push_back(temp2);
            }
        }else{
            if(in2Val == 1)
            {
                //------(1-x)y
                mono temp1{};
                mono temp2{};
                temp1.nVar=1;
                temp1.sign=1;
                temp1.Var.insert(in2);
                temp2.nVar=2;
                temp2.Var.insert(in1);
                temp2.Var.insert(in2);
                temp2.sign=-1;
                temp.monomial.push_back(temp1);
                temp.monomial.push_back(temp2);
            }else{
                //------(1-x)(1-y)
                temp.constant.val=1;
                mono temp1{};
                mono temp2{};
                mono temp3{};
                temp1.nVar=1;
                temp2.nVar=1;
                temp3.nVar=2;
                temp1.sign=-1;
                temp2.sign=-1;
                temp3.sign=1;
                temp1.Var.insert(in1);
                temp2.Var.insert(in2);
                temp3.Var.insert(in1);
                temp3.Var.insert(in2);
                temp.monomial.push_back(temp1);
                temp.monomial.push_back(temp2);
                temp.monomial.push_back(temp3);
            }
        }
    }else{
        if(in1Val == 1)
        {
            if(in2Val == 1)
            {
                //------1-xy
                temp.constant.val=1;
                mono temp1{};
                temp1.sign=-1;
                temp1.nVar=2;
                temp1.Var.insert(in1);
                temp1.Var.insert(in2);
                temp.monomial.push_back(temp1);
            }else{
                //------1-x(1-y)
                temp.constant.val=1;
                mono temp1{};
                mono temp2{};
                temp1.nVar=1;
                temp2.nVar=2;
                temp1.sign=-1;
                temp2.sign=1;
                temp1.Var.insert(in1);
                temp2.Var.insert(in1);
                temp2.Var.insert(in2);
                temp.monomial.push_back(temp1);
                temp.monomial.push_back(temp2);
            }
        }else{
            if(in2Val == 1)
            {
                //------1-(1-x)y
                temp.constant.val=1;
                mono temp1{};
                mono temp2{};
                temp1.nVar=1;
                temp2.nVar=2;
                temp1.sign=-1;
                temp2.sign=1;
                temp1.Var.insert(in2);
                temp2.Var.insert(in1);
                temp2.Var.insert(in2);
                temp.monomial.push_back(temp1);
                temp.monomial.push_back(temp2);
            }else{
                //------1-(1-x)(1-y)
                mono temp1{};
                mono temp2{};
                mono temp3{};
                temp1.sign=1;
                temp2.sign=1;
                temp3.sign=-1;
                temp1.nVar=1;
                temp2.nVar=1;
                temp3.nVar=2;
                temp1.Var.insert(in1);
                temp2.Var.insert(in2);
                temp3.Var.insert(in1);
                temp3.Var.insert(in2);
                temp.monomial.push_back(temp1);
                temp.monomial.push_back(temp2);
                temp.monomial.push_back(temp3);
            }
        }
    }
}

void printPoly(polyExpr &temp)
{
    if(temp.constant.val!=0)
    {
        if(temp.constant.sign==-1)
        {
            cout<<" - ";
        }else{
            cout<<" + ";
        }
        cout<<" 2^"<<temp.constant.coeff[0]<<"*"<<temp.constant.coeff[1];
    }
    for(auto item : temp.monomial)
    {
        if(item.sign==-1)
        {
            cout<<" - ";
        }else{
            cout<<" + ";
        }
        cout<<"2^"<<item.coeff[0]<<"*"<<item.coeff[1]<<"( ";
        for(auto it : item.Var)
        {
            cout<<it<<" ";
        }
        cout<<")";
    }
    cout<<endl;
}
 
void printCircuitPoly(map<int, polyExpr> &circuitPoly)
{
    map<int, polyExpr>::iterator iter=circuitPoly.begin();
    while(iter!=circuitPoly.end())
    {
        cout<<iter->first<<"\t";
        printPoly(iter->second);
        iter++;
    }
}

void printConstHsh(vector<constMono> &temp)
{
    vector<constMono>::iterator iter=temp.begin();
    while(iter!=temp.end())
    {
        if(iter->sign<0)
        {
            cout<<" - ";
        }else{
            cout<<" + ";
        }
        cout<<"2^"<<(iter->coeff[0])<<"*"<<iter->coeff[1];
        iter++;
    }
    cout<<endl;
}

void printVarHsh(map<int, vector<mono>> &temp)
{
    map<int, vector<mono>>::iterator iter=temp.begin();
    while(iter!=temp.end())
    {
        for(auto item : iter->second)
        {
            if(item.sign == 1)
            {
                cout<<" + ";
            }else{
                cout<<" - ";
            }
            cout<<"2^"<<item.coeff[0]<<"*"<<item.coeff[1]<<"( ";
            for(auto it : item.Var)
            {
                cout<<it<<" ";
            }
            cout<<")";
        }
        iter++;
    }
    cout<<endl;
}
 
void genCircuitPoly(map<int, polyExpr> &circuitPoly, vector<gate> &theCircuit, map<int, int> &fanouts, map<string, int> &mapWireNum)
{
    vector<gate>::iterator iter=theCircuit.end();
    do{
        iter--;
        polyExpr temp{};
        int in1=mapWireNum.at(iter->in1Name);
        int in2=mapWireNum.at(iter->in2Name);
        genPoly(temp, in1, in2, iter->gateID, iter->inv1Val, iter->inv2Val, iter->invOut);
        circuitPoly.insert(pair<int, polyExpr>(iter->gateID, temp));
    }while(iter!=theCircuit.begin());
    //printCircuitPoly(circuitPoly);
}

void multiplyBy(polyExpr &curPoly, mono curMono)
{
    //printMono(curMono);
    vector<mono>::iterator iter=curPoly.monomial.begin();
    while(iter!=curPoly.monomial.end())
    {
        if(!((curMono.Var).empty()))
        {
            iter->sign=(iter->sign) * (curMono.sign);
            iter->coeff[0]=(iter->coeff[0])+(curMono.coeff[0]);
            iter->coeff[1]=(iter->coeff[1])*(curMono.coeff[1]);
            (iter->Var).insert(curMono.Var.begin(), curMono.Var.end());
            iter->nVar=(iter->Var).size();
        }else{
            iter->sign=(iter->sign) * (curMono.sign);
            iter->coeff[0]=(iter->coeff[0])+(curMono.coeff[0]);
            iter->coeff[1]=(iter->coeff[1])*(curMono.coeff[1]);
        }
        iter++;
    }
    if(curPoly.constant.val!=0)
    {
        if(curMono.Var.empty())
        {
            curPoly.constant.sign=(curPoly.constant.sign)*(curMono.sign);
            curPoly.constant.coeff[0]=(curPoly.constant.coeff[0])+(curMono.coeff[0]);
            curPoly.constant.coeff[1]=(curPoly.constant.coeff[1])*(curMono.coeff[1]);
        }else{
            mono temp;
            temp.sign=(curPoly.constant.sign)*(curMono.sign);
            temp.coeff[0]=(curPoly.constant.coeff[0])+(curMono.coeff[0]);
            temp.coeff[1]=(curPoly.constant.coeff[1])*(curMono.coeff[1]);
            temp.Var = curMono.Var;
            curPoly.constant.sign=1;
            curPoly.constant.coeff[0]=0;
            curPoly.constant.coeff[1]=1;
            curPoly.constant.val=0;
            curPoly.monomial.push_back(temp);
        }
    }
}

bool addConstCoeff(constMono temp, constMono &iter, bool &del)
{
    if((temp.coeff[0] - iter.coeff[0]) > 25 || (temp.coeff[0] - iter.coeff[0]) < -25)
    {
        return false;
    }
    if(temp.sign==iter.sign)
    {
        if(temp.coeff[0] == iter.coeff[0])
        {
            iter.coeff[1]=temp.coeff[1]+iter.coeff[1];
        }else if(temp.coeff[0]>iter.coeff[0]){
            int temp1=temp.coeff[0]-iter.coeff[0];
            iter.coeff[1]=iter.coeff[1]+(temp.coeff[1])*(pow(2, temp1));
        }else if(temp.coeff[0]<iter.coeff[0]){
            int temp1=iter.coeff[0]-temp.coeff[0];
            iter.coeff[0]=temp.coeff[0];
            iter.coeff[1]=(iter.coeff[1])*(pow(2, temp1))+temp.coeff[1];
        }
    }else if(temp.sign==1 && iter.sign==-1){
        if(temp.coeff[0]==iter.coeff[0])
        {
            if(temp.coeff[1] == iter.coeff[1])
            {
                del = true;
            }else if(temp.coeff[1] > iter.coeff[1]){
                iter.sign=1;
                iter.coeff[1]=temp.coeff[1]-iter.coeff[1];
            }else{
                iter.coeff[1]=iter.coeff[1]-temp.coeff[1];
            }
        }else if(temp.coeff[0]>iter.coeff[0]){
            int temp1=temp.coeff[0]-iter.coeff[0];
            iter.coeff[1]=(temp.coeff[1])*(pow(2, temp1))-iter.coeff[1];
            if(iter.coeff[1]>0)
            {
                iter.sign=1;
            }else{
                iter.coeff[1]=-iter.coeff[1];
            }
        }else if(temp.coeff[0]<iter.coeff[0]){
            int temp1=iter.coeff[0]-temp.coeff[0];
            iter.coeff[0] = temp.coeff[0];
            iter.coeff[1]=temp.coeff[1]-(iter.coeff[1])*(pow(2, temp1));
            if(iter.coeff[1]>0)
            {
                iter.sign=1;
            }else{
                iter.coeff[1]=-iter.coeff[1];
            }
        }
    }else if(temp.sign==-1 && iter.sign==1){
        if(temp.coeff[0]==iter.coeff[0])
        {
            if(temp.coeff[1] == iter.coeff[1])
            {
                del = true;
            }else if(temp.coeff[1] > iter.coeff[1]){
                iter.sign=-1;
                iter.coeff[1]=temp.coeff[1]-iter.coeff[1];
            }else{
                iter.coeff[1]=iter.coeff[1]-temp.coeff[1];
            }
        }else if(temp.coeff[0] > iter.coeff[0]){
            int temp1=temp.coeff[0]-iter.coeff[0];
            iter.coeff[1]=iter.coeff[1]-(temp.coeff[1])*(pow(2, temp1));
            if(iter.coeff[1]<0)
            {
                iter.coeff[1]=-iter.coeff[1];
                iter.sign=-1;
            }
        }else if(temp.coeff[0] < iter.coeff[0]){
            int temp1=iter.coeff[0]-temp.coeff[0];
            iter.coeff[1]=(iter.coeff[1])*(pow(2, temp1))-temp.coeff[1];
            iter.coeff[0] = temp.coeff[0];
            if(iter.coeff[1]<0)
            {
                iter.coeff[1]=-iter.coeff[1];
                iter.sign=-1;
            }
        }
    }
    if(iter.coeff[1] == 0)
    {
        del = true;
    }
    while(iter.coeff[1]%2==0)
    {
        iter.coeff[0]+=1;
        iter.coeff[1]=(iter.coeff[1])/2;
    }
    return true;
}

bool addVarCoeff(mono &iter, mono &temp, bool &del)
{
    if((iter.coeff[0] - temp.coeff[0]) > 25 || (iter.coeff[0] - temp.coeff[0]) < -25)
    {
        return false;
    }
    if(iter.sign == temp.sign)
    {
        if(iter.coeff[0] == temp.coeff[0])
        {
            iter.coeff[1] = iter.coeff[1] + temp.coeff[1];
        }else if(iter.coeff[0] > temp.coeff[0]){
            int temp1 = iter.coeff[0] - temp.coeff[0];
            iter.coeff[0]= temp.coeff[0];
            iter.coeff[1] = iter.coeff[1] * pow(2, temp1) + temp.coeff[1];
        }else if(iter.coeff[0] < temp.coeff[0]){
            int temp1 = temp.coeff[0] - iter.coeff[0];
            iter.coeff[1] = iter.coeff[1] + temp.coeff[1] * pow(2, temp1);
        }
    }else if(iter.sign == -1 && temp.sign == 1){
        if(iter.coeff[0] == temp.coeff[0]){
            if(iter.coeff[1] == temp.coeff[1]){
                del = true;
            }else{
                iter.coeff[1] = temp.coeff[1] - iter.coeff[1];
                if(iter.coeff[1] > 0)
                {
                    iter.sign = 1;
                }else{
                    iter.coeff[1] = - iter.coeff[1];
                }
            }
        }else if(iter.coeff[0] > temp.coeff[0]){
            int temp1 = iter.coeff[0] - temp.coeff[0];
            iter.coeff[1] = temp.coeff[1] - iter.coeff[1] * pow(2, temp1);
            iter.coeff[0] = temp.coeff[0];
            if(iter.coeff[1] < 0 )
            {
                iter.coeff[1] = - iter.coeff[1];
            }else if(iter.coeff[1] > 0){
                iter.sign = 1;
            }else{
                del = true;
            }
        }else if(iter.coeff[0] < temp.coeff[0]){
            int temp1 = temp.coeff[0] - iter.coeff[0];
            iter.coeff[1] = temp.coeff[1] * pow(2, temp1) - iter.coeff[1];
            if(iter.coeff[1] < 0)
            {
                iter.coeff[1] = - iter.coeff[1];
            }else if( iter.coeff[1] > 0){
                iter.sign = 1;
            }else{
                del = true;
            }
        }
    }else if(iter.sign == 1 && temp.sign == -1){
        if(iter.coeff[0] == temp.coeff[0]){
            if(iter.coeff[1] == temp.coeff[1]){
                del = true;
            }else if(iter.coeff[1] > temp.coeff[1]){
                iter.coeff[1] = iter.coeff[1] - temp.coeff[1];
            }else if(iter.coeff[1] < temp.coeff[1]){
                iter.coeff[1] = temp.coeff[1] - iter.coeff[1];
                iter.sign =-1;
            }
        }else if(iter.coeff[0] > temp.coeff[0]){
            int temp1 = iter.coeff[0] - temp.coeff[0];
            iter.coeff[0] = temp.coeff[0];
            iter.coeff[1] = iter.coeff[1] * pow(2, temp1) - temp.coeff[1];
            if(iter.coeff[1] < 0)
            {
                iter.coeff[1] = - iter.coeff[1];
                iter.sign = -1;
            }else if(iter.coeff[1] == 0){
                del = true;
            }
        }else if(iter.coeff[0] < temp.coeff[0]){
            int temp1 = temp.coeff[0] - iter.coeff[0];
            iter.coeff[1] = iter.coeff[1] - temp.coeff[1] * pow(2, temp1);
            if(iter.coeff[1] < 0)
            {
                iter.coeff[1] = - iter.coeff[1];
                iter.sign = -1;
            }else if(iter.coeff[1] == 0){
                del = true;
            }
        }
    }
    if(iter.coeff[1] == 0)
    {
        del = true;
        return true;
    }
    while(iter.coeff[1]%2 == 0)
    {
        iter.coeff[0]+=1;
        iter.coeff[1]=(iter.coeff[1])/2;
    }
    return true;
}

void constantWrite(constMono &temp, vector<constMono> &constHsh)
{
    vector<constMono>::iterator iter=constHsh.begin();
    bool add=false;
    bool del=false;
    while(iter!=constHsh.end())
    {
        if(addConstCoeff(temp, *iter, del))
        {
            if(del)
            {
                constHsh.erase(iter);
            }
            iter=constHsh.end();
            add=true;
        }else{
            iter++;
            add=false;
        }
    }
    if(!add)
    {
        constHsh.push_back(temp);
    }
}

void variableWrite(mono &temp, map<int, vector<mono>> &varHsh)
{
    bool inserted=false;
    vector<mono> temp1{};
    if(varHsh.find(temp.Var.size()) == varHsh.end())
    {
        temp1.push_back(temp);
        varHsh.insert(pair<int, vector<mono>>(temp.Var.size(), temp1));
        inserted = true;
    }else{
        vector<mono>::iterator iter=varHsh.at(temp.Var.size()).begin();
        while(iter!=varHsh.at(temp.Var.size()).end())
        {
            if(iter->Var == temp.Var)
            {
                bool del = false;
                if(addVarCoeff(*iter, temp, del))
                {
                    if(del)
                    {
                        varHsh.at(temp.Var.size()).erase(iter);
                    }
                    inserted = true; 
                }else{
                    inserted = false;
                }
                iter=varHsh.at(temp.Var.size()).end();
            }else{
                inserted = false;
                iter++;
            }
        }
        if(!inserted)
        {
            varHsh.at(temp.Var.size()).push_back(temp);
        }
    }
}

void writeInHsh(polyExpr &curPoly, vector<constMono> &constHsh, map<int, vector<mono>> &varHsh)
{
    if(curPoly.constant.val!=0)
    {
        constMono curConstant=curPoly.constant;
//        cout<<"constant: ";
//        if(curConstant.sign==1)
//        {
//            cout<<" + ";
//        }else{
//            cout<<" - ";
//        }
//        cout<<"2^"<<curConstant.coeff[0]<<"*"<<curConstant.coeff[1]<<endl;
        constantWrite(curConstant, constHsh);
        //cout<<"constHah: ";
        //printConstHsh(constHsh);
    }
    for(auto curMono : curPoly.monomial)
    {
        //cout<<"mono: ";
        //printMono(curMono);
        variableWrite(curMono, varHsh);
        //cout<<"varHsh: ";
        //printVarHsh(varHsh);
    }
}

void mergeVarHsh(map<int, vector<mono>> &varHsh, map<int, vector<mono>> &tempHsh)
{
    map<int, vector<mono>>::iterator iter = tempHsh.begin();
    while(iter!= tempHsh.end())
    {
        for(auto item : iter->second)
        {
            variableWrite(item, varHsh);
        }
        iter++;
    }
}

void writePoly(vector<constMono> &constHsh, map<int, vector<mono>> &varHsh, map<int, polyExpr> &circuitPoly)
{
    map<int, polyExpr>::iterator iter1=circuitPoly.end();
    do{
        iter1--;
       // cout<<iter1->first<<"-->";
        //printPoly(iter1->second);
        map<int, vector<mono>>::iterator iter2=varHsh.begin();
        map<int, vector<mono>> tempVarHsh{};
        while(iter2!=varHsh.end())
        {
            vector<mono>::iterator iter3=(iter2->second).begin();
            while(iter3!=(iter2->second).end())
            {
                set<int>::iterator iter4;
                iter4=(iter3->Var).find(iter1->first);
                if(iter4!=(iter3->Var).end())
                {
                    (iter3->Var).erase(iter4);
                    polyExpr temp=iter1->second;
                    multiplyBy(temp, *iter3);
                   // cout<<"Poly-->";
                   // printPoly(temp);
                    (iter2->second).erase(iter3);
                    writeInHsh(temp, constHsh, tempVarHsh);
                    //cout<<"tempVarHsh: "<<tempVarHsh.size()<<endl;
                    //printVarHsh(tempVarHsh);
                    
                    iter3--;
                }
                iter3++;
            }
            iter2++;
        }
//        cout<<"*************************"<<endl;
//        printVarHsh(tempVarHsh);
        mergeVarHsh(varHsh, tempVarHsh);
//        cout<<endl;
//        cout<<"Variables---->"<<endl;
//        printVarHsh(varHsh);
//        cout<<"Constants---->"<<endl;
//        printConstHsh(constHsh);
//        cout<<"---------------------------------------"<<endl;
    }while(iter1!=circuitPoly.begin());
}

void addTwoPoly(polyExpr &poly1, polyExpr &poly2)
{
    if(poly2.constant.val!=0)
    {
        if(poly1.constant.val!=0)
        {
            if(poly1.constant.sign == poly2.constant.sign)
            {
                if(poly1.constant.coeff[0] == poly2.constant.coeff[0])
                {
                    poly1.constant.coeff[1] = poly1.constant.coeff[1] + poly2.constant.coeff[1];
                }else if(poly1.constant.coeff[0] > poly2.constant.coeff[0]){
                    int temp =poly1.constant.coeff[0] - poly2.constant.coeff[0];
                    poly1.constant.coeff[0] = poly2.constant.coeff[0];
                    poly1.constant.coeff[1] = poly1.constant.coeff[1] * pow(2, temp) + poly2.constant.coeff[1];
                }else if(poly1.constant.coeff[0] < poly2.constant.coeff[0]){
                    int temp =poly2.constant.coeff[0] - poly1.constant.coeff[0];
                    poly1.constant.coeff[1] = poly2.constant.coeff[1] * pow(2, temp) + poly1.constant.coeff[1];
                }
            }else if(poly1.constant.sign == 1 && poly2.constant.sign == -1){
                if(poly1.constant.coeff[0] == poly2.constant.coeff[0])
                {
                    if(poly1.constant.coeff[1] == poly2.constant.coeff[1])
                    {
                        poly1.constant.val = 0;
                    }else{
                        poly1.constant.coeff[1] = poly1.constant.coeff[1] - poly2.constant.coeff[1];
                        if(poly1.constant.coeff[1] < 0)
                        {
                            poly1.constant.coeff[1] = - poly1.constant.coeff[1];
                            poly1.constant.sign = -1;
                        }
                    }
                }else if(poly1.constant.coeff[0] > poly2.constant.coeff[0]){
                    int temp = poly1.constant.coeff[0] - poly2.constant.coeff[0];
                    poly1.constant.coeff[0] = poly2.constant.coeff[0];
                    poly1.constant.coeff[1] = poly1.constant.coeff[1] * pow(2, temp) - poly2.constant.coeff[1];
                    if(poly1.constant.coeff[1] < 0)
                    {
                        poly1.constant.coeff[1] = - poly1.constant.coeff[1];
                        poly1.constant.sign = -poly1.constant.sign;
                    }else if(poly1.constant.coeff[1] == 0){
                        poly1.constant.val = 0;
                    }
                }else if(poly1.constant.coeff[0] < poly2.constant.coeff[0]){
                    int temp = poly2.constant.coeff[0] - poly1.constant.coeff[0];
                    poly1.constant.coeff[1] = poly1.constant.coeff[1] - poly2.constant.coeff[1] * pow(2, temp);
                    if(poly1.constant.coeff[1] < 0)
                    {
                        poly1.constant.coeff[1] = - poly1.constant.coeff[1];
                        poly1.constant.sign = -poly1.constant.sign;
                    }else if(poly1.constant.coeff[1] == 0){
                        poly1.constant.val = 0;
                    }
                }
            }else if(poly1.constant.sign == -1 && poly2.constant.sign == 1){
                if(poly1.constant.coeff[0] == poly2.constant.coeff[0])
                {
                    if(poly1.constant.coeff[1] == poly2.constant.coeff[1])
                    {
                        poly1.constant.val = 0;
                    }else{
                        poly1.constant.coeff[1] = poly2.constant.coeff[1] - poly1.constant.coeff[1];
                        if(poly1.constant.coeff[1] > 0)
                        {
                            poly1.constant.sign = 1;
                        }else{
                            poly1.constant.coeff[1] = - poly1.constant.coeff[1];
                        }
                    }
                }else if(poly1.constant.coeff[0] > poly2.constant.coeff[0]){
                    int temp = poly1.constant.coeff[0] - poly2.constant.coeff[0];
                    poly1.constant.coeff[0] = poly2.constant.coeff[0];
                    poly1.constant.coeff[1] = poly2.constant.coeff[1] - poly1.constant.coeff[1] * pow(2, temp);
                    if(poly1.constant.coeff[1] < 0)
                    {
                        poly1.constant.coeff[1] = - poly1.constant.coeff[1];
                    }else if(poly1.constant.coeff[1] == 0){
                        poly1.constant.val = 0;
                    }else{
                        poly1.constant.sign = 1;
                    }
                }else if(poly1.constant.coeff[0] < poly2.constant.coeff[0]){
                    int temp = poly2.constant.coeff[0] - poly1.constant.coeff[0];
                    poly1.constant.coeff[1] = poly1.constant.coeff[1] - poly2.constant.coeff[1] * pow(2, temp);
                    if(poly1.constant.coeff[1] < 0)
                    {
                        poly1.constant.coeff[1] = - poly1.constant.coeff[1];
                    }else if(poly1.constant.coeff[1] == 0){
                        poly1.constant.val = 0;
                    }else{
                        poly1.constant.sign = 1;
                    }
                }
            }
        }else{
            poly1.constant=poly2.constant;
        }
    }
    
    vector<mono> tempPoly;
    vector<mono>::iterator iter2 = poly2.monomial.begin();
    while(iter2!= poly2.monomial.end())
    {
        vector<mono>::iterator iter1 = poly1.monomial.begin();
        bool added=false;
        while(iter1!=poly1.monomial.end())
        {
            if(iter2->Var == iter1->Var)
            {
                bool del=false;
                if(addVarCoeff(*iter1, *iter2, del))
                {
                    if(del)
                    {
                        poly1.monomial.erase(iter1);
                    }
                    added = true;
                    iter1=poly1.monomial.end();
                }else{
                    iter1++;
                    added = false;
                }
            }else{
                iter1++;
            }
        }
        if(!added)
        {
            tempPoly.push_back(*iter2);
        }
        iter2++;
    }
    for(auto item : tempPoly)
    {
        poly1.monomial.push_back(item);
    }
}

void mergeTwoPoly(polyExpr &poly1, polyExpr &poly2, int temp)
{
    polyExpr tempPoly{};
    tempPoly.constant=poly1.constant;
    for(auto tempMono : poly1.monomial)
    {
        if(tempMono.Var.count(temp)!=0)
        {
            tempMono.Var.erase(temp);
            //printPoly(poly2);
            polyExpr poly3 = poly2;
            multiplyBy(poly3, tempMono);
            //printPoly(poly3);
            addTwoPoly(tempPoly, poly3);
        }else{
            tempPoly.monomial.push_back(tempMono);
        }
    }
    poly1 = tempPoly;
}

void polynomialReduction(map<int, polyExpr> &circuitPoly, map<int, int> &fanouts, set<int> &primaryOutputs, map<int, set<int>> &gateToRelatedGate)
{
    map<int, polyExpr>::iterator iter1=circuitPoly.begin();
    map<int, polyExpr> tempCircuitPoly{};
    while(iter1!=circuitPoly.end())
    {
        if(fanouts.at(iter1->first)==1)
        {
            if(primaryOutputs.count(iter1->first)==0)
            {
                tempCircuitPoly.insert(pair<int, polyExpr>(iter1->first, iter1->second));
            }
        }
        iter1++;
    }
    map<int, polyExpr>::iterator iter = tempCircuitPoly.begin();
    while(iter!=tempCircuitPoly.end())
    {
        for(auto gateId : gateToRelatedGate.at(iter->first))
        {
            polyExpr poly1=circuitPoly.at(gateId);
            polyExpr poly2=circuitPoly.at(iter->first);
            set<int> temp{};
            for(auto it : poly1.monomial)
            {
                temp.insert(it.Var.begin(), it.Var.end());
            }
//            cout<<gateId<<"->";
//            printPoly(poly1);
//            cout<<iter->first<<"->";
//            printPoly(poly2);
            mergeTwoPoly(poly1, poly2, iter->first);
/*            temp.erase(iter->first);
//            cout<<gateId<<"->";
//            printPoly(poly1);
//            cout<<"--------------------------"<<endl;
            for(auto item : temp)
            {
                polyExpr poly3=circuitPoly.at(item);
                mergeTwoPoly(poly1, poly3, item);
            }
             */
            circuitPoly.erase(gateId);
            circuitPoly.insert(pair<int, polyExpr>(gateId, poly1));
        }
        circuitPoly.erase(iter->first);
        //cout<<iter->first<<endl;
        iter++;
    }
}

void sizeCalculate(map<int, polyExpr> &temp)
{
    cout<<"#Polynomials: "<<temp.size()<<endl;
    map<int, polyExpr>::iterator iter=temp.begin();
    size_t i=0;
    size_t j=0;
    while(iter!=temp.end())
    {
        if((iter->second).constant.val != 0)
        {
            j=j+1;
        }
        i=i+(iter->second).monomial.size();
        iter++;
    }
    cout<<"#VarMono: "<<i<<endl;
    cout<<"#ConstMono: "<<j<<endl;
}

void backwardRewriting(vector<gate> &theCircuit, map<int, int> &fanouts, map<string, int> &mapWireNum, map<string, int> &outList, set<int> &primaryOutputs, map<int, set<int>> &gateToRelatedGate)
{
    cout<<"-------------------Backward rewriting-------------------"<<endl;
    vector<constMono> constHsh{};
    map<int, vector<mono>> varHsh{};
    vector<mono> outSig{};
    map<int, polyExpr> circuitPoly{};
    map<int, polyExpr> newCircuitPoly{};
    outputSignature(outSig, outList);
    varHsh.insert(pair<int, vector<mono>>(1, outSig));
    clock_t start, end;
    genCircuitPoly(circuitPoly, theCircuit, fanouts, mapWireNum);
//    printCircuitPoly(circuitPoly);
//    Reduce polynomials
    cout<<"old circuit size:"<<endl;
    sizeCalculate(circuitPoly);
    start = clock(); 
    polynomialReduction(circuitPoly, fanouts, primaryOutputs, gateToRelatedGate);
    cout<<"New circuit size:"<<endl;
    sizeCalculate(circuitPoly);
    printCircuitPoly(circuitPoly);
    
 //   cout<<"Hsh table-->";
//    printVarHsh(varHsh);
    
    
//    writePoly(constHsh, varHsh, circuitPoly);
//    cout<<"----------Remainder-----------"<<endl;
//    cout<<"variables---->"<<endl;
//    printVarHsh(varHsh);
//    cout<<"constants:---->"<<endl;
//    printConstHsh(constHsh); 
    size_t i =0;
    for(auto item : varHsh)
    {
        i = i + (item.second).size();
    }
    cout<<"#Mono left: "<<i + constHsh.size()<<endl; 
    end = clock(); 
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);  
    cout << "Time for backward rewriting: " << fixed << setprecision(2) << time_taken << setprecision(5) << " sec " << endl; 
}


};

}
#endif // POLY_H
