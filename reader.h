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
#include <tuple>
#include <iomanip>
#include <algorithm>
#include <iterator>
using namespace std;

typedef tuple<string, int, int, int> operand; //this tracks the sr,vr,pr,and nu of an operand
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

void PrintHelp();
void PrintTokens();

void scanToken(bool print, bool pFlag);
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
void createTableRow();
void update_tokes();
void printTable();
void printILOC();
void parser();
void t0();
void t1();
void t2();
void t3();
void t4();
void t5();

//allocater.cpptypedef tuple<string, int, int, int> operand; //this tracks the sr,vr,pr,and nu of an operand
typedef tuple<string,operand,operand,operand> line; //constructs a single line of the block which holds OPCODE, OP1, OP2, and OP3
void populateBlock();
string returnOpAsString(operand op);
void printBlock(vector<line> block);
void fillSRVRandLU(vector<line> block);
void ComputeNextUse(vector<line> block);
void UpdateCNU(operand op, int index);

