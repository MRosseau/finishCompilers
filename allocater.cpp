#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include "reader.h"

vector<int> SRtoVR;
vector<int> LU;
vector<int> VRtoPR;
vector<int> LRStart;
vector<int> LREnd;
vector<bool> checkVR;
vector<int> regInt;
stack<int> PRList;
int maxVR;
int maxLive;
int reserve;
int maxReg = 0;
int VRName;
int x;

void naiveAllocator(vector<Line> &block, bool kFlag, int kNum) {

    //get maxReg
    for(Line l : block) {
        //cout << "start maxReg" << endl;
        //cout << "line: " << l.opcode << endl;
        if(l.op1.isReg)
        {
            maxReg++;
            regInt.push_back(l.op1.SR);
        }
        if(l.op2.isReg)
        {
            maxReg++;
            regInt.push_back(l.op2.SR);            
        }
        if(l.op3.isReg)
        {
            maxReg++;
            regInt.push_back(l.op3.SR);
        }
    }
    //cout << "maxReg: " << maxReg << endl;
    /*for(unsigned int i = 0; i <= regInt.size(); i++)
    {
        SRtoVR[i] = -1;
    }*/

    lastUse(block); // block, maxReg, SRtoVR, LU, maxVR to block, maxReg, LU

    for(int i = 0; i < maxReg; i++) {
        //cout << "SRtoVR[i]: " << SRtoVR[i] << endl;
        // cout << "SRtoVR[" << i << "]: " << SRtoVR[i] << endl;
        // cout << "LU[" << i << "]: " << LU[i] << endl;
    }
   
    cout << "done" << endl;
   
}
//VR allocation and LU
void lastUse(vector<Line> &block) { //take out SRtoVR and maxReg as a Variable
    VRName = 0;


    for(int i = 0; i < maxReg; i++) {
        //cout << "SRtoVR[i]: " << SRtoVR[i] << endl;
        SRtoVR.push_back(-1);
        LU.push_back(-1);
    }
    for(int i = block.size() - 1; i > 0; i--) {

        //cout << "attempt update on op3 " << block[i].op3.SR << " isReg? " << block[i].op3.isReg << endl;
        update(block[i].op3, i); //block[i].dest to get<3>(block[i]) //get<3>(block[i]) to op
        //cout << "finished op3" << endl;
        if(block[i].op3.isReg) {
            SRtoVR.at(block[i].op3.SR) = -1; //SRtoVR[block[i].op3.SR] = -1; to SRtoVR.at(block[i].op3.SR) = -1;
            LU.at(block[i].op3.SR) = -1; //LU[block[i].op3.SR] = -1; to LU.at(block[i].op3.SR) = -1;
        } 
        
        //cout << "attempt update on op1 " << block[i].op1.SR << " isReg? " << block[i].op1.isReg << endl;
        update(block[i].op1, i); //block[i].source1 to get<1>(block[i])
        //cout << "finished op1" << endl;
        //cout << "attempt update on op2 " << block[i].op2.SR << " isReg? " << block[i].op2.isReg << endl;
        update(block[i].op2, i); //block[i].source2 to get<2>(block[i])
        //cout << "finished op2\n" << endl;
        //cout << SRtoVR[i] << endl;
    }

    maxVR = *std::max_element(SRtoVR.begin(), SRtoVR.end());
}


void update(Operand &op, int index) { //take out SRtoVR and VRName as a Variable
    if(op.isReg) { //op.SR != -1 to op.isReg, if-block extended to cover the whole function
        //cout << "start update op SR " << op.SR << endl;
        if(SRtoVR[op.SR] == -1) {
            SRtoVR[op.SR] = VRName++; //op.SR to get<0>(op)
            cout << "SRtoVR[" << index << "]: " << SRtoVR[op.SR] << endl;
        }
    
        op.VR = SRtoVR[op.SR]; //op.VR to get<1>(op) //op.SR to get<0>(op)
        //cout << "op.VR: " << op.VR << endl;

        op.NU = LU[op.SR]; //op.NU to get<3>(op) //op.SR to get<0>(op)
        //cout << "op.NU: " << op.NU << endl;
        LU[op.SR] = index; //op.SR to get<0>(op)
        cout << "LU[" << index << "]: " << LU[op.SR] << "\n" << endl;
        //cout << "finished update on op SR " << op.SR << endl; 
    }
}

