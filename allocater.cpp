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

//void naiveAllocator(vector<Line> &block, bool kFlag, int kNum)
//void naiveAllocator(vector<Line> &block, bool kFlag, int kNum)

void naiveAllocator(vector<Line> &block, bool kFlag, int kNum) {



    /*get # of registers
    for(int i = 0; i < reg.size(); i++) {
        if(reg[i] > maxReg) {
            maxReg = reg[i];
        }
    }*/

    //get maxReg
    for(Line l : block) {
        cout << "start maxReg" << endl;
        cout << "line: " << l.opcode << endl;
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

    lastUse(block, maxReg, LU); // block, maxReg, SRtoVR, LU, maxVR to block, maxReg, LU

    cout << "done" << endl;
   
}
//VR allocation and LU
void lastUse(vector<Line> &block, int maxReg, vector<int> &LU) { //take out SRtoVR and maxReg as a Variable
    VRName = 0;


    for(int i = 0; i < maxReg; i++) {
        //cout << "SRtoVR[i]: " << SRtoVR[i] << endl;
        SRtoVR.push_back(-1);
        LU.push_back(-1);
    }
    for(int i = block.size() - 1; i > 0; i--) {
        //operand op3 = make_tuple(get<0>(get<3>(block[i])), get<1>(get<3>(block[i])), get<2>(get<3>(block[i])), get<3>(get<3>(block[i])));
        //operand op1 = make_tuple(get<0>(get<1>(block[i])), get<1>(get<1>(block[i])), get<2>(get<1>(block[i])), get<3>(get<1>(block[i])));
        //operand op2 = make_tuple(get<0>(get<2>(block[i])), get<1>(get<2>(block[i])), get<2>(get<2>(block[i])), get<3>(get<2>(block[i])));

        cout << "attempt update on " << block[i].op3.SR << endl;
        update(block[i].op3, i, LU); //block[i].dest to get<3>(block[i]) //get<3>(block[i]) to op
        cout << "updated op3" << endl; 
        SRtoVR[block[i].op3.SR] = -1; //block[i].dest.SR to get<0>(get<3>(block[i]))
        cout << "set SR3 to invalid" << endl; 
        LU[block[i].op3.SR] = -1; //block[i].dest.SR to get<0>(get<3>(block[i]))
        cout << "set LU to invalid" << endl; 
        update(block[i].op1, i, LU); //block[i].source1 to get<1>(block[i])
        cout << "updated op1" << endl;
        update(block[i].op2, i, LU); //block[i].source2 to get<2>(block[i])
        cout << "updated op2" << endl;
        //cout << SRtoVR[i] << endl;
    }

    maxVR = *std::max_element(SRtoVR.begin(), SRtoVR.end());
}


void update(Operand &op, int index, vector<int> &LU) { //take out SRtoVR and VRName as a Variable
    cout << "start update op SR " << op.SR << endl;
    if(op.isReg) { //op.SR != -1 to op.isReg, if-block extended to cover the whole function
        if(SRtoVR[op.SR] == -1) {
            SRtoVR[op.SR] = VRName++; //op.SR to get<0>(op)
        }
    
    op.VR = SRtoVR[op.SR]; //op.VR to get<1>(op) //op.SR to get<0>(op)

    op.NU = LU[op.SR]; //op.NU to get<3>(op) //op.SR to get<0>(op)
    LU[op.SR] = index; //op.SR to get<0>(op)
    cout << "finished update on op SR " << op.SR << endl; 
    }
}

