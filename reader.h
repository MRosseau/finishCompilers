#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <istream>
#include <getopt.h>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <tuple>
#include <iomanip>
#include <algorithm>
#include <iterator>
using namespace std;

typedef tuple<int, int, int, int> operand; //this tracks the sr,vr,pr,and nu of an operand //change sr from string to int
typedef tuple<string,operand,operand,operand> line; //constructs a single line of the block which holds OPCODE, OP1, OP2, and OP3

enum Token {
        INST,
        REG,
        CONST,
        COMMA,
        ARROW
};

enum Optype {
        memop,
        arithop,
        loadi,
        nop,
        output
};

enum Operation {
        store,
        sub,
        loadiOp,
        lshift,
        rshift,
        mult,
        add,
        nopOp,
        outputOp
};

struct Operand {
    int SR;
    int VR;
    int NU;
    int PR;
    bool isReg;
};

struct Line {
    int index;    
    string opcode;
    Operand op1;
    Operand op2;
    Operand op3;
};

//Operand toOperand(int val);

//Line toLine(string opcodeVal, struct Operand op1Val, struct Operand op2Val, struct Operand op3Val);

void PrintHelp();
void PrintTokens();

vector< tuple<Token, string> > scanToken(bool print, bool pFlag);
void printToken();

void ScanErr(char c);

extern FILE* inFile;
extern vector< tuple<Token, string> > tokens;

tuple<string,int> PrintRegister(int index);

void s0 ();
void s1 ();
void s2 ();
void s3 ();
void s4 ();
void s5 ();
void s6 ();
void s7 ();
void s8 ();
void s9 ();
void s10 (char i);
void s11 ();
void s12 ();
void s13 ();
void s14 ();
void s15 ();
void s16 ();
void s17 (char i);
void s18 (); //Scan comments

// parser.cpp
vector<Line> returnBlock();
vector<Line> populateBlock(vector<tuple<string, string, string, string>> &table); //added to convert table to block
void createTableRow();
void update_tokes();
void printTable(vector<tuple<string, string, string, string>> &table);
void printILOC(vector< tuple<string, string, string, string> > table);
vector< tuple<string, string, string, string> > parser(vector< tuple<Token, string> > tok);
void t0();
void t1();
void t2();
void t3();
void t4();
void t5();

//allocater.cpp
//typedef tuple<string, int, int, int> operand; //this tracks the sr,vr,pr,and nu of an operand
//typedef tuple<string,operand,operand,operand> line; //constructs a single line of the block which holds OPCODE, OP1, OP2, and OP3
void naiveAllocator(vector<Line> &block, int kNum);
void lastUse(vector<Line> &block);
void update(Operand &op, int index);
void convertPR(Operand &op, vector<int> &VRtoPR, stack<int> &PRList, vector<Line> &temp, int index);
void updateLiveRange(vector<Line> &block, vector<int> &LRStart, vector<bool> &checkVR, int currentVR, int i);
void printBlock(vector<Line> &block);
string printOperandSR(Operand &op);
void printBlockinfo(vector<Line> &block);


