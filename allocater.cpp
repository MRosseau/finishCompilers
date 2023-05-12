#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include "reader.h"

vector<int> SRtoVR;
vector<int> LU;
// vector<int> VRtoPR;
// vector<int> LRStart;
// vector<int> LREnd;
// vector<bool> checkVR;
vector<int> regInt;
stack<int> PRList;
int maxVR;
int maxReg = 0;
int VRName;

void naiveAllocator(vector<Line> &block, int kNum) {

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
    //cout << "regInt.size(): " << regInt.size() << endl;
    /*for(unsigned int i = 0; i <= regInt.size(); i++)
    {
        SRtoVR[i] = -1;
    }*/
    cout << "input block" << endl;
    printBlock(block);

    lastUse(block); // block, maxReg, SRtoVR, LU, maxVR to block, maxReg, LU

    // for(int i = 0; i < maxReg; i++) {
    //     //cout << "SRtoVR[i]: " << SRtoVR[i] << endl;
    //      cout << "SRtoVR[" << i << "]: " << SRtoVR[i] << endl;
    //      cout << "LU[" << i << "]: " << LU[i] << endl;
    // }
   
    cout << "output block" << endl;
    printBlock(block);
    cout << "output block info" << endl;
    printBlockinfo(block);
   
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

    //maxVR = *std::max_element(SRtoVR.begin(), SRtoVR.end());
    //cout << "maxVR: " << maxVR << endl;
    //cout << "maxReg: " << maxReg << endl;
}


void update(Operand &op, int index) { //take out SRtoVR and VRName as a Variable
    if(op.isReg) { //op.SR != -1 to op.isReg, if-block extended to cover the whole function
        //cout << "start update op SR " << op.SR << endl;
        if(SRtoVR[op.SR] == -1) {
            SRtoVR[op.SR] = VRName++; //op.SR to get<0>(op)
            //cout << VRName << endl;
            //cout << "SRtoVR[" << index << "]: " << SRtoVR[op.SR] << endl;
        }
    
        op.VR = SRtoVR[op.SR]; //op.VR to get<1>(op) //op.SR to get<0>(op)
        //cout << "op.VR: " << op.VR << endl;

        op.NU = LU[op.SR]; //op.NU to get<3>(op) //op.SR to get<0>(op)
        //cout << "op.NU: " << op.NU << endl;
        LU[op.SR] = index; //op.SR to get<0>(op)
        //cout << "LU[" << index << "]: " << LU[op.SR] << "\n" << endl;
        //cout << "finished update on op SR " << op.SR << endl; 
    }
}

void printBlock(vector<Line> &block) {
    //cout << "It reaches here" << endl;
    int bSize = 0;
    for(Line l : block) {
        cout << "index: " << to_string(bSize) <<
                ", opcode: " << l.opcode << 
                ", op1.SR:" << printOperandSR(l.op1) << 
                ", op2.SR:" << printOperandSR(l.op2) << 
                ", op3.SR:" << printOperandSR(l.op3) << endl;
        bSize++;
    }
}

string printOperandSR(Operand &op) {
    string opstr;
    if(op.isReg) {
        opstr = " r" + to_string(op.SR);
    }
    else if(op.SR == -1) {
        opstr = " -";
    }
    else {
        opstr = " " + to_string(op.SR);
    }
    return opstr;
}

tuple<string, string, string, string> printableOp(Operand &op){
    string opSR;
    string opVR;
    string opNU;
    string opPR;
    if(op.isReg) {
        opSR = "r" + to_string(op.SR);
        opVR = to_string(op.VR);
        opNU = to_string(op.NU);
        opPR = to_string(0); //prints out 0 as a standin for mem location
    }
    else if(op.SR == -1) {
        opSR = "-";
        opVR = "-";
        opNU = "-";
        opPR = "-";
    }
    else {
        opSR = to_string(op.SR);
        opVR = "-";
        opNU = "-";
        opPR = "-";
    
    }
    return make_tuple(opSR, opVR, opNU, opPR);
}

// void printBlockinfo(vector<Line> &block) {
//     //cout << "It reaches here" << endl;
//     int bSize = 0;
//     for(Line l : block) {
//         cout << "index: " << to_string(bSize) <<
//                 ", opcode: " << l.opcode << 

//                 ", op1.SR:" << printOperandSR(l.op1) << 
//                 ", op1.VR:" << l.op1.VR <<
//                 ", op1.NU:" << l.op1.NU <<
//                 ", op1.PR:" << l.op1.PR << 

//                 ", op2.SR:" << printOperandSR(l.op2) << 
//                 ", op2.VR:" << l.op2.VR <<
//                 ", op2.NU:" << l.op2.NU <<
//                 ", op2.PR:" << l.op2.PR << 

//                 ", op3.SR:" << printOperandSR(l.op3) << 
//                 ", op3.VR:" << l.op3.VR <<
//                 ", op3.NU:" << l.op3.NU <<
//                 ", op3.PR:" << l.op3.PR <<  endl;
//         bSize++;
//     }
// }

void printBlockinfo(vector<Line> &block) {
    //cout << "It reaches here" << endl;
    int bSize = 0;
    for(Line l : block) {
        tuple<string, string, string, string> printOp1 = printableOp(l.op1);
        tuple<string, string, string, string> printOp2 = printableOp(l.op2);
        tuple<string, string, string, string> printOp3 = printableOp(l.op3);
        cout << "index: " << to_string(bSize);
        cout << ", opcode: " << l.opcode; 

        cout << ", op1.SR:" << get<0>(printOp1);
        cout << ", op1.VR:" << get<1>(printOp1);
        cout << ", op1.NU:" << get<2>(printOp1);
        cout << ", op1.PR:" << get<3>(printOp1); 

        cout << "        op2.SR:" << get<0>(printOp2);
        cout << ", op2.VR:" << get<1>(printOp2);
        cout << ", op2.NU:" << get<2>(printOp2);
        cout << ", op2.PR:" << get<3>(printOp2); 

        cout << "        op3.SR:" << get<0>(printOp3);
        cout << ", op3.VR:" << get<1>(printOp3);
        cout << ", op3.NU:" << get<2>(printOp3);
        cout << ", op3.PR:" << get<3>(printOp3) <<  endl;
        bSize++;
    }
}



// void printOperandSR(Operand &op) {
//     if(op.isReg) {
//         cout << " r" << op.SR << endl;
//     }
//     else if(op.SR == -1) {
//         cout << " -" << endl;
//     }
//     else {
//         cout << " " << op.SR << endl;
//     }
// }
