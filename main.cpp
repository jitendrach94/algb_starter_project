#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <chrono>
#include <set>
#include "Gate.h"
#include "Circuit.h"
#include "Poly.h"

using namespace std;
using namespace Gate;
using namespace Circuit;
using namespace Poly;
using namespace std::chrono; 

int main(int argc, char **argv)
{
    vector<gate> pInputs{};
    vector<gate> theCircuit{};
    vector<gate> pOutputs{};
    map<int, string> mapNumWire{};
    map<string, int> mapWireNum{};
    map<int, int> fanouts{};
    map<string, int> outList{};
    set<int> primaryOutputs{};
    map<int, set<int>> gateToRelatedGate{};
    clock_t start, end;
    start = clock(); 
    cout<<"Welcome in Algebraic Backward Rewriting"<<endl;
    string pFile=argv[1];
    circuit *pCircuit{};
  
    pCircuit->circuitModeling(pFile, pInputs, theCircuit, pOutputs, mapNumWire, mapWireNum, fanouts, outList, gateToRelatedGate);
    
//    for(auto item : gateToRelatedGate)
//    {
//        cout<<mapNumWire.at(item.first)<<": ";
//        for(auto it : item.second)
//            cout<<mapNumWire.at(it)<<" ";
//        cout<<endl;
//    } 
    for(auto item : pOutputs)
        primaryOutputs.insert(outList.at(item.outName));
    
    poly *pPoly{};
    pPoly->backwardRewriting(theCircuit, fanouts, mapWireNum, outList, primaryOutputs, gateToRelatedGate);
    end = clock(); 
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);  
    cout << "Overall run Time: " << fixed << setprecision(2) << time_taken << setprecision(5) << " sec " << endl; 
    

    return 0;
}
