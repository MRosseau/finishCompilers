#include "reader.h"

extern vector< tuple<Token, string> > tokens;
vector< tuple<string, string, string, string> > table; //Vector of quadruple containing strings for opcade, op1, op2, and dest


Token toke;
string tName;
string opcodeStr = "-";
string op1 = "-";
string op2 = "-";
string dest = "-";
int pos = 0;
int tableSize; 
int tokensSize;

void update_tokes()
{   
    tokensSize = tokens.size();
    
    if (pos < tokensSize)
    {
        toke = get<0>(tokens.at(pos));
        tName = get<1>(tokens.at(pos));
        pos++;
    }
    
}

void printTable(vector< tuple<string, string, string, string> > &table)
{   
    tableSize = table.size();
    cout << "|" << left << setw(5) << "index" << "|" <<
        left << setw(6) << "opcode" << " |" <<
        "| " << left << setw(3) << "op1" << " | " <<
        left << setw(3) << "op2" << " |" <<
        left << setw(3) << "dest" << " |" << endl;
    cout << "|" << left << setw(5) << "" << "|" <<
        left << setw(6) << "" << " |" <<
        "| " << left << setw(3) << "sr" << " | " <<
        left << setw(3) << "sr" << " | " <<
        left << setw(3) << "sr" << " |" << endl;

    for(int i = 0; i < tableSize; i++)
        {
                cout << "|" << left << setw(5) << i << "|" << //Index
                left << setw(6) << get<0>(table.at(i)) << " |" << //Opcode
                "| " << left << setw(3) << get<1>(table.at(i)) << " | " << //op1
                left << setw(3) << get<2>(table.at(i)) << " | " << //op2
                left << setw(3) << get<3>(table.at(i)) << " |" << endl; //dest
        }
}

void printILOC(vector< tuple<string, string, string, string> > table)
{
    update_tokes();
    t0();
    tableSize = table.size();
    cout << "Table size is " << tableSize << endl;
    for(int i = 0; i < tableSize; i++)
    {
        //cout << "Iteration " << i << endl;
        string opcode = get<0>(table.at(i));

        if(opcode == "load" || opcode == "loadI") //Print load, loadI
        {
            cout << left << setw(8) << opcode <<
                left << setw(14) << get<1>(table.at(i)) <<
                "=> " << get<3>(table.at(i)) << endl;
        }
        else if(opcode == "store") //Print store
        {
            cout << left << setw(8) << opcode <<
                left << setw(14) << get<1>(table.at(i)) <<
                "=> " << get<2>(table.at(i)) << endl;
        }
        else if(opcode == "add" || opcode == "sub" || opcode == "mult" || opcode == "lshift" || opcode == "rshift") //Print add, sub, mult, lshift, rshift
        {
            cout << left << setw(8) << opcode <<
                left << setw(6) << get<1>(table.at(i)) <<
                left << setw(2) << ", " <<
                left << setw(6) << get<2>(table.at(i)) <<
                "=> " << get<3>(table.at(i)) << endl;
        }
        else if(opcode == "nop") //Print nop
        {
            cout << "nop" << endl;
        }
        else if(opcode == "output") //Print output
        {
            cout << left << setw(8) << opcode << get<1>(table.at(i)) << endl;
        }
        else
        {
            cout << "Invalid token" << endl;
        }
    }
}

Operand toOperand(int val) {
    Operand newOp;
    newOp.SR = val;
    return newOp;
}

Line toLine(string opcodeVal, Operand op1Val, Operand op2Val, Operand op3Val) {
    Line newOp;
    newOp.opcode = opcodeVal;
    newOp.op1 = op1Val;
    newOp.op2 = op2Val;
    newOp.op3 = op3Val;
    return newOp;
}

vector<Line> returnBlock(){
    vector<Line> retBlock;

    retBlock = populateBlock(table);

    return retBlock;
}

vector<Line> populateBlock(vector<tuple<string, string, string, string>> &table)
{
    vector<Line> block;
    block.resize(table.size());
   /*for (unsigned int i = 0; i < table.size(); i++)
   {
        operand op1 = make_tuple(stoi(get<1>(table.at(i))), NULL, NULL , NULL);
        operand op2 = make_tuple(stoi(get<2>(table.at(i))), NULL, NULL , NULL);
        operand op3 = make_tuple(stoi(get<3>(table.at(i))), NULL, NULL , NULL);
       line newLine = make_tuple(get<0>(table.at(i)), op1, op2, op3);
       block.resize(table.size());
       block[i] = newLine;
       return block;
   }*/
    
   for (unsigned int i = 0; i < table.size(); i++)
   {
        string op1SR = get<1>(table.at(i));
        string op2SR = get<2>(table.at(i));
        string op3SR = get<3>(table.at(i));

        Operand op1;
        Operand op2;
        Operand op3;

        if(op1SR == "-")
        {
            op1 = toOperand(-1);
            op1.isReg = false;
        }
        else if(op1SR[0] == 'r')
        {
            op1 = toOperand(stoi(op1SR.substr(1)));
            op1.isReg = true;
        }
        else
        {
            op1 = toOperand(stoi(op1SR));
            op1.isReg = false;
        }

        if(op2SR == "-")
        {
            op2 = toOperand(-1);
            op2.isReg = false;
        }
        else if(op2SR[0] == 'r')
        {
            op2 = toOperand(stoi(op2SR.substr(1)));
            op2.isReg = true;
        }
        else
        {
            op2 = toOperand(stoi(op2SR));
            op2.isReg = false;
        }

        if(op3SR == "-")
        {
            op3 = toOperand(-1);
            op3.isReg = false;
        }
        else if(op3SR[0] == 'r')
        {
            op3 = toOperand(stoi(op3SR.substr(1)));
            op3.isReg = true;
        }
        else
        {
            op3 = toOperand(stoi(op3SR));
            op3.isReg = false;
        }

        //cout << "op1SR is " << op1SR << " op1 isReg? " << op1.isReg << " op2SR is " << op2SR << " op2 isReg? " << op2.isReg << " op3SR is " << op3SR << " op3 isReg? " << op3.isReg <<endl;
        //cout << "op1 SR: " << op1.SR << " op1 VR: " << op1.VR << " op1 PR: " << op1.VR << " op1 NU: " << op1.NU << " op1 isReg? " << op1.isReg << "        op2 SR:" << op2.SR << " op2 VR: " << op2.VR << " op2 PR: " << op2.VR << " op2 NU: " << op2.NU << " op2 isReg? " << op2.isReg << "        op3 is " << op3.SR << " op3 VR: " << op3.VR << " op3 PR: " << op3.VR << " op3 NU: " << op3.NU << " op3 isReg? " << op3.isReg << "\n" <<endl;
        Line newLine = toLine(get<0>(table.at(i)), op1, op2, op3);
        block[i] = newLine;
   }
   return block;
}


vector< tuple<string, string, string, string> > parser(vector< tuple<Token, string> > tok)
{  
        tokens = tok;
        update_tokes();
        t0();
        //printTable();

        return table;

        // vector<Line> updatedTable = populateBlock(table); //Moved to reader.cpp
        // naiveAllocator(updatedTable, true, 3);
}


void createTableRow()
{
    table.push_back(make_tuple(opcodeStr,op1,op2,dest));
    update_tokes();
    opcodeStr = "-";
    op1 = "-";
    op2 = "-";
    dest = "-";
    t0();
}

void t0()
{

    switch(toke)
    {
        case INST:
            if (tName == "store" || tName == "load")
            {
                opcodeStr = tName;
                t1();
            }
            else if (tName == "sub" || tName == "add" || tName == "mult" || tName == "rshift" || tName == "lshift")
            {
                opcodeStr = tName;
                t2();
            }
            else if (tName == "loadI")
            {
                opcodeStr = tName;
                t3();
            }
            else if (tName == "nop")
            {
                opcodeStr = tName;
                t4();
            }
            else if (tName == "output")
            {
                opcodeStr = tName;
                t5();
            }
            else 
                break; 
        default:
            break;
    }
}

void t1()// memop
{
    update_tokes();
    
    switch(toke)
    {
        case REG:
        {
            op1 = tName;
            update_tokes();
            switch (toke)
            {
                case ARROW:
                {
                    update_tokes();
                    switch (toke)
                    {
                        case REG:
                        {
                            if(opcodeStr == "load")
                            {
                                dest = tName;
                                createTableRow();
                            }
                            else if(opcodeStr == "store")
                            {
                                op2 = tName;
                                createTableRow();
                            }
                            else
                                break;
                        }
                        default:
                            break;
                    }
                }
            default:
                break;
            }
        }
        default:
            break;
    }

}

void t2()// arithop
{
    update_tokes();
    
    switch(toke)
    {
        case REG:
        {
            op1 = tName;
            update_tokes();
            switch (toke)
            {
                case COMMA:
                {
                    update_tokes();
                    switch (toke)
                    {
                        case REG:
                        {
                            op2 = tName;
                            update_tokes();
                            switch (toke)
                            {
                                case ARROW:
                                {
                                    update_tokes();
                                    switch (toke)
                                    {
                                    case 1:
                                    {
                                        dest = tName;
                                        createTableRow();
                                    }
                                    default:
                                        break;
                                    }
                                }
                                default:
                                    break;
                            }
                        }
                        default:
                            break;
                    }
                }
                default:
                    break;
            }
        }
        default:
            break;
    }

}

void t3()// loadI
{
    update_tokes();
    
    switch(toke)
    {
        case CONST:
        {
            op1 = tName;
            update_tokes();
            switch (toke)
            {
            case ARROW:
            {
                update_tokes();
                switch (toke)
                {
                    case REG:
                    {
                        dest = tName;
                        createTableRow();
                    }
                    default:
                        break;
                }
            }
            default:
                break;
            }
        }
        default:
            break;
    }

}

void t4()// nop
{
    createTableRow();
}

void t5()// output
{

    update_tokes();
    //cout << "checking for const inside of output - start" << endl;
    switch(toke)
    {
        case CONST:
        {
            //out << "changing op1 to current const" << endl;
            op1 = tName;
            createTableRow();
        }
        default:
        {   
            //cout << "Breaking from output" << endl;
            break;
        }
            
    }


}