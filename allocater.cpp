#include <iostream>
#include <fstream>
#include "reader.h"


void naiveAllocator(vector<Line> block, bool kFlag, int kNum) {
    vector<int> SRtoVR;
    vector<int> LU;
    vector<int> VRtoPR;
    vector<int> LRStart;
    vector<int> LREnd;
    vector<bool> checkVR;
    vector<int> regInt;
    stack<int> PRList;
    int maxVR;
    int maxReg = 0;

    //get maxReg
    for(Line l : block) {
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
    cout << "maxReg: " << maxReg << endl;

    lastUse(block, maxReg, SRtoVR, LU, maxVR);
   
}
//VR allocation and LU
void lastUse(vector<Line> block, int maxReg, vector<int> SRtoVR, vector<int> LU, int maxVR) {
    int VRName = 0;


    for(int i = 0; i < maxReg; i++) {
        SRtoVR[i] = -1;
        LU[i] = -1;
    }
    for(int i = block.size() - 1; i > 0; i--) {
        update(block[i].op3, i, SRtoVR, LU, VRName); //block[i].dest to get<3>(block[i]) //get<3>(block[i]) to op 
        SRtoVR[block[i].op3.SR] = -1; //block[i].dest.SR to get<0>(get<3>(block[i]))
        LU[block[i].op3.SR] = -1; //block[i].dest.SR to get<0>(get<3>(block[i]))
        update(block[i].op1, i, SRtoVR, LU, VRName); //block[i].source1 to get<1>(block[i])
        update(block[i].op2, i, SRtoVR, LU, VRName); //block[i].source2 to get<2>(block[i])
        cout << SRtoVR[i] << endl;
    }
    maxVR = VRName;
}


void update(Operand op, int index, vector<int> SRtoVR, vector<int> LU, int VRName) {
    if(SRtoVR[op.SR] == -1) { //op.SR to get<0>(op)
        SRtoVR[op.SR] = VRName++; //op.SR to get<0>(op)
    }
    op.VR = SRtoVR[op.SR]; //op.VR to get<1>(op) //op.SR to get<0>(op)
    op.NU = LU[op.SR]; //op.NU to get<3>(op) //op.SR to get<0>(op)
    LU[op.SR] = index; //op.SR to get<0>(op)
}


