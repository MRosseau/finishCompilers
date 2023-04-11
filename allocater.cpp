#include "reader.h"

vector <tuple<string, string>> SRtoVR;//(tuple<SR name, VR name>)
vector <tuple<string, int>> LastUse;//(tuple<SR name, index of LU>)
//typedef tuple<string, int, int, int> operand; //this tracks the sr,vr,pr,and nu of an operand
//typedef tuple<string,operand,operand,operand> line; //constructs a single line of the block which holds OPCODE, OP1, OP2, and OP3
vector<line> block;
extern vector< tuple<string, string, string, string> > table; //Vector of quadruple containing strings for opcode, op1, op2, and dest

int VRName = 0;

void populateBlock()
{
    for (unsigned int i = 0; i < table.size(); i++)
    {
        line newLine = make_tuple(get<0>(table.at(i)), 
                                  make_tuple(get<1>(table.at(i)), NULL, NULL , NULL), 
                                  make_tuple(get<2>(table.at(i)), NULL, NULL , NULL), 
                                  make_tuple(get<3>(table.at(i)), NULL, NULL , NULL));
        block.resize(table.size());
        block[i] = newLine;
    }
}
string returnOpAsString(operand op)
{
    string opString = "sr: " + get<0>(op) + 
                      " vr: " + to_string(get<1>(op)) +
                      " pr: " + to_string(get<2>(op)) +
                      " nu: " + to_string(get<3>(op));
    return opString;
}
void printBlock(vector<line> block)
{
    int blockSize = block.size();
    // cout << "|" << left << setw(5) << "index" << "|" <<
    //     left << setw(6) << "opcode" << " |" <<
    //     "| " << left << setw(3) << "op1" << " | " <<
    //     left << setw(3) << "op2" << " |" <<
    //     left << setw(3) << "dest" << " |" << endl;
    // cout << "|" << left << setw(5) << "" << "|" <<
    //     left << setw(6) << "" << " |" <<
    //     "| " << left << setw(3) << "sr" << " | " <<
    //     left << setw(3) << "sr" << " | " <<
    //     left << setw(3) << "sr" << " |" << endl;

    for(int i = 0; i < blockSize; i++)
        {
                cout << "|" << left << setw(5) << i << "|" << //Index
                left << setw(6) << get<0>(block.at(i)) << " |" << //Opcode
                "| " << left << setw(3) << returnOpAsString(get<1>(block.at(i))) << " | " << //op1
                left << setw(3) << returnOpAsString(get<2>(block.at(i))) << " | " << //op2
                left << setw(3) << returnOpAsString(get<3>(block.at(i))) << " |" << endl; //dest
        }
}

void fillSRVRandLU(vector<line> block)
{
    int maxRegNum = 0;
    string newSR;
    //vector<tuple<string,string>>::iterator unique_checker;
    //string unique_checker;
    //if (std::find(v.begin(), v.end(), "abc") != v.end())

    //find is having trouble with finding newSR bc it is a string and SRtoVR is a vec<tup<str,str>>. we will eith have to make a vector of just SR's to use find(),
    // figure out how to get find() to either use pattern matching possilbly using wildcards, or only look at the first string in the tuple, or find an alternative to find().


    for(unsigned int i = 0; i < block.size(); i++)
        {
            newSR = get<0>(get<1>(block[i]));
            //unique_checker = find(SRtoVR.begin(), SRtoVR.end(), newSR);
            if(newSR != "-" && std::find(SRtoVR.begin(), SRtoVR.end(), newSR) != SRtoVR.end())
            {
                SRtoVR.resize(maxRegNum);
                LastUse.resize(maxRegNum);
                get<0>(SRtoVR[maxRegNum]) = newSR;
                get<0>(LastUse[maxRegNum]) = newSR;
                maxRegNum++;
            }// checks if sr is unique of op1 and if so creates an SRtoVR tuple for it.
            
            newSR = get<0>(get<2>(block[i]));
            //unique_checker = find(SRtoVR.begin(), SRtoVR.end(), newSR);
            if(newSR != "-" && std::find(SRtoVR.begin(), SRtoVR.end(), newSR) != SRtoVR.end())
            {
                SRtoVR.resize(maxRegNum);
                LastUse.resize(maxRegNum);
                get<0>(SRtoVR[maxRegNum]) = newSR;
                get<0>(LastUse[maxRegNum]) = newSR;
                maxRegNum++;
            }// checks if sr is unique of op2 and if so creates an SRtoVR tuple for it.
            
            newSR = get<0>(get<3>(block[i]));
            //unique_checker = find(SRtoVR.begin(), SRtoVR.end(), newSR);
            if(newSR != "-" && std::find(SRtoVR.begin(), SRtoVR.end(), newSR) != SRtoVR.end())
            {
                SRtoVR.resize(maxRegNum);
                LastUse.resize(maxRegNum);
                get<0>(SRtoVR[maxRegNum]) = newSR;
                get<0>(LastUse[maxRegNum]) = newSR;
                maxRegNum++;
            }// checks if sr is unique of op3 and if so creates an SRtoVR tuple for it.
            
            
            /*!SRtoVR.contains(get<0>(get<1>(block.at(i))))*/ 
                // cout << "|" << left << setw(5) << i << "|" << //Index
                // left << setw(6) << get<0>(block.at(i)) << " |" << //Opcode
                // "| " << left << setw(3) << returnOpAsString(get<1>(block.at(i))) << " | " << //op1
                // left << setw(3) << returnOpAsString(get<2>(block.at(i))) << " | " << //op2
                // left << setw(3) << returnOpAsString(get<3>(block.at(i))) << " |" << endl; //dest


        }
}

void ComputeNextUse(vector<line> block)
{
    
    fillSRVRandLU(block);
    int maxRegNum = LastUse.size();
    for(int i = 0;i < maxRegNum; i++)
    {
        get<1>(SRtoVR[i]) = "invalid";
        get<1>(LastUse[i]) = -1;
    }
    //printBlock(block);

    for(int i = block.size() - 1; i > 0; i--)
    {
        int posOfSR;
        vector<tuple<string,string>>::iterator findSR;
        findSR = find(SRtoVR.begin(), SRtoVR.end(), get<0>(get<1>(block[i])));
        posOfSR = findSR - SRtoVR.begin();
        UpdateCNU(get<3>(block[i]), i);
        get<1>(SRtoVR[posOfSR]) = "invalid";
        get<1>(LastUse[posOfSR]) = -1;
        UpdateCNU(get<1>(block[i]), i);
        UpdateCNU(get<2>(block[i]), i);
    }
}

void UpdateCNU(operand op, int index)
{
    if (get<1>(SRtoVR[find(SRtoVR.begin(), SRtoVR.end(), get<0>(op)) - SRtoVR.begin() ]) == "invalid") //SRtoVR has an error bc it is trying to get an index from a string
    {
        get<1>(SRtoVR[find(SRtoVR.begin(), SRtoVR.end(), get<0>(op)) - SRtoVR.begin() ]) = VRName++;
    }
    get<1>(op) = stoi(get<1>(SRtoVR[find(SRtoVR.begin(), SRtoVR.end(), get<0>(op)) - SRtoVR.begin() ])); //sets VR
    get<3>(op) = get<1>(LastUse[find(SRtoVR.begin(), SRtoVR.end(), get<0>(op)) - SRtoVR.begin() ]); //sets NU
    get<1>(LastUse[find(SRtoVR.begin(), SRtoVR.end(), get<0>(op)) - SRtoVR.begin()]) = index;

}

