#ifndef _CIRCUIT_H
#define _CIRCUIT_H

#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include "time.h"
#include "Gate.h"
#include <stdlib.h>
using namespace std;
using namespace Gate;

namespace Circuit {
  class circuit {
    public:
        int PISize=0;
        int POSize=0;
        int gateSize=0;
        
        circuit(string blifFile, vector<gate> &pInputs, vector<gate> &theCircuit, vector<gate> &pOutputs, map<int, string> &mapNumWire, map<string, int> &mapWireNum, map<int, int> &fanouts, map<string, int> &outList, map<int, set<int>> &gateToRelatedGate){
        PISize=0;
        POSize=0;
        gateSize=0;
        circuitModeling(blifFile, pInputs, theCircuit, pOutputs, mapNumWire, mapWireNum, fanouts, outList, gateToRelatedGate);
        }
    
        ~circuit(){}
    
    /*--------------Function-----------------*/
    void circuitModeling(string blifFile, vector<gate> &pInputs, vector<gate> &theCircuit, vector<gate> &pOutputs, map<int, string> &mapNumWire, map<string, int> &mapWireNum, map<int, int> &fanouts, map<string, int> &outList, map<int, set<int>> &gateToRelatedGate)
    {
        cout<<"--------------Circuit Initialization-----------------"<<endl;
        //cout<<"gateType in1Name\tin2Name \toutName \tinv1Val \tinv2Val \tinvOut \tgateID \tLevel\trLevel"<<endl;
        blifParser(blifFile, pInputs, theCircuit, pOutputs, mapNumWire, mapWireNum, fanouts, outList, gateToRelatedGate);
        //cout<<endl<<"-------------Successfull Initialization ------------"<<endl;
    }
    
   /*--------------Function--------------*/
    void splitName(string &line, vector<string> &elems)
    {
        int spaceLength{};
        for(auto ch : line)
        {
            if(ch==' ')
            {
                spaceLength+=1;
            }else{
                break;
            }
        }
        line.erase(0, spaceLength);
        stringstream lineStream(line);
        string item;
        while( getline(lineStream, item, ' ') )
        {
            if (item == "\\")
            {
                continue;
            }else{
                elems.push_back(item);
            }
        }
    }
    
 
    /*-------------Function-----Almost Done------------*/
    void blifParser(string blifFile, vector<gate> &pInputs, vector<gate> &theCircuit, vector<gate> &pOutputs, map<int, string> &mapNumWire, map<string, int> &mapWireNum, map<int, int> &fanouts, map<string, int> &outList, map<int, set<int>> &gateToRelatedGate)
    {
        ifstream file;
        file.open(blifFile);
        if(!file)
        {
            cout<< "Error: file not opened!"<<endl;
        }
        int lineNum = 0;
        int gateIndex = 0;
        string line;
        bool stillIn = false, stillOut = false;
        vector<string> POTemp{};
        while(!file.eof())
        {
            getline(file, line);
            lineNum++;
            //cout<<line<<endl;
            vector<string> elems;
            if(line.find(".inputs") != string::npos || stillIn)
            {
                if(line.find("\\") != string::npos)
                {
                    stillIn=true;
                }else{
                    stillIn=false;
                }
                //cout<<line<<endl;
                splitName(line, elems);
               // cout<<"Input element size: "<<elems.size()<<endl;
                for(size_t i=0; i<elems.size(); i++)
                {
                    if(elems[i]==".inputs" || elems[i]=="\\")
                    {
                        continue;
                    }else{
                        gate newInput= gate(PI, elems[i]);
                        //cout<<elems[i];
                        //cout<<elems[i]<<endl;
                        newInput.gateID=gateIndex;
                        pInputs.push_back(newInput);
                        mapWireNum.insert(pair<string, int>(newInput.outName, gateIndex));
                        mapNumWire.insert(pair<int, string>(gateIndex, newInput.outName));
                        fanouts.insert(pair<int, int>(gateIndex, 0));
                        set<int> temp{};
                        gateToRelatedGate.insert(pair<int, set<int>>(gateIndex, temp));
                        gateIndex++;
                    }
                }
            }else if(line.find(".outputs") != string::npos || stillOut){
                if(line.find("\\") != string::npos)
                {
                    stillOut=true;
                }else{
                    stillOut=false;
                }
                POTemp.push_back(line);
            }else if(line.find(".names")!=string::npos){
                splitName(line, elems);
                getline(file, line);
                // add space between inputs
                string newLine{};
                for(auto ch : line)
                {
                    //cout<<ch<<endl;
                    if(ch!=' '){
                       newLine=newLine + ch + ' '; 
                    }
                }
                //cout<<newLine<<endl;
                splitName(newLine, elems);
                lineNum++;
                //cout<<"Gate element size: "<<elems.size()<<endl;
                if(elems.size()==7)
                {
                    //cout<<"AND or NOR gate "<<elems[0]<<endl;
                    // Add this gate to theCircuit
                    // Add this gate output to the output list 
                    gate newAig = gate(AIG, elems[1], elems[2], elems[3], elems[4], elems[5], elems[6]);
                    newAig.gateID=gateIndex;
                    theCircuit.push_back(newAig);
                    mapWireNum.insert(pair<string, int>(newAig.outName, gateIndex));
                    mapNumWire.insert(pair<int, string>(gateIndex, newAig.outName));
                    fanouts.insert(pair<int, int>(gateIndex, 0));
                    fanouts.at(mapWireNum.at(elems[1]))+=1;
                    fanouts.at(mapWireNum.at(elems[2]))+=1;
                    set<int> temp{};
                    gateToRelatedGate.insert(pair<int, set<int>>(gateIndex, temp));
                    gateToRelatedGate.at(mapWireNum.at(elems[1])).insert(gateIndex);
                    gateToRelatedGate.at(mapWireNum.at(elems[2])).insert(gateIndex);
                    gateIndex++;
                }
            }else{
                //cout<<"In blif file, line num: "<<lineNum<<" is the end of file or not part of the circuit!"<<endl;
            }
            
        }
        for(size_t i=0; i<POTemp.size(); i++)
            {
                vector<string> elems{};
                splitName(POTemp[i], elems);
                for(size_t j=0; j<elems.size(); j++)
                {
                    if(elems[j]==".outputs" || elems[j]=="\\")
                    {
                        continue;
                    }else{
                        gate newOutput=gate(PO, elems[j]);
                        pOutputs.push_back(newOutput);
                        fanouts.at(mapWireNum.at(elems[j]))+=1;
                        outList.insert(pair<string, int>(elems[j], mapWireNum.at(elems[j])));
                    }
                }
            }
        file.close();

//        printCircuit(theCircuit);
//        for(auto item : mapNumWire)
//        {
//            cout<<item.first<<"\t"<<item.second<<endl;
//        }
//        for(auto item : fanouts)
//        {
//            cout<<item.first<<"\t"<<item.second<<endl;
//        }
//        for(auto item : outList)
//        {
//            cout<<item.first<<"\t"<<item.second<<endl;
//        }
//        for(auto item : gateToRelatedGate)
//        {
//            cout<<mapNumWire.at(item.first)<<"-->";
//            for(auto it : item.second)
//                cout<<mapNumWire.at(it)<<" ";
//            cout<<endl;
//        }
//        cout<<endl;
    }


    /*-----------------Function--Done---------------*/
    void printCircuit(vector<gate> &pCircuit) //pCircuit to change????????????
    {
        for(auto item : pCircuit)
        {
            if(item.gateType==PI || item.gateType==PO)
            {
                cout<<' '<<item.gateType<<"\t  "<<item.in1Name<<"\t\t"<<"\t\t"<<item.outName<<"\t\t";
                cout<<item.inv1Val<<"\t\t"<<"\t\t"<<item.invOut<<"\t"<<item.gateID<<endl;
            }else{
                cout<<' '<<item.gateType<<"\t  "<<item.in1Name<<"\t\t"<<item.in2Name<<"\t\t"<<item.outName<<"\t\t";
                cout<<item.inv1Val<<"\t\t"<<item.inv2Val<<"\t\t"<<item.invOut<<"\t"<<item.gateID<<"\t"<<endl;
            }
        }
    }
    
   

    
  };
}

#endif
