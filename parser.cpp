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

void printTable()
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

void printILOC()
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

void parser()
{   
    
    update_tokes();
    t0();
    printTable();
    
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