#include "reader.h"

int numVal = 0; //Value to store number for const and reg
bool commented = false; //Checks the status of whether the remainder of the line is commented
extern FILE* inFile;
vector< tuple<Token, string> > tokens; //Vector of tuples containing Token types and their lexemes


vector< tuple<Token, string> > scanToken(bool tFlag, bool pFlag)
{
        s0();
        vector<tuple<Token, string>> retTokens = tokens;
        return retTokens;
}


void printToken()
{
        int tokensSize = tokens.size();
        const char* inst_names[] = {"INST","REG","CONST","COMMA","ARROW"};
        for(int i = 0; i < tokensSize; i++)
        {
                cout << "<" << inst_names[get<0>(tokens.at(i))] << ", "; 
                if(get<0>(tokens.at(i)) >= 3)
                {
                        cout << '\'' << get<1>(tokens.at(i)) << "\'>\n";
                }
                else
                {
                        cout << get<1>(tokens.at(i)) << ">\n";
                }
        }

}

void s0()
{
        numVal = 0; //Resets the value for the next const or reg
        char c = getc(inFile);
        
        switch(c)
        {
                case 's':
                        s1();
                case 'l':
                        s4();
                case 'r':
                        s8();
                case 'm':
                        s11();
                case 'a':
                        s12();
                case 'n':
                        s13();
                case 'o':
                        s14();
                case '=':
                        s15();
                case ',':
                        s16();
                case '0' ... '9':
                        s17(c);
                case ' ':
                        s0();
                case '/':
                        s18();
                case '\n':
                        s0();
                case '\t':
                        s0();
                /* case '		':
                        return s0(); */
                case EOF:
                        break;
                default:
                        break;
        }
}

void s1()
{
        char c = getc(inFile);

        switch(c)
        {
                case 't':
                        s2();
                case 'u':
                        s3();
                case EOF:
                        break;
                default:
                        break;
        }
}

void s2()
{
        char c = getc(inFile);

        switch(c)
        {
                case 'o':
                {
                        c = getc(inFile);
                        switch(c)
                        {
                                case 'r':
                                {
                                        c = getc(inFile);
                                        switch(c)
                                        {
                                                case 'e':
                                                {
                                                        c = getc(inFile);
                                                        switch(c)
                                                        {
                                                                /* case ' ':
                                                                        tokens.push_back(make_tuple(INST, "store"));
                                                                        return s0();
                                                                case '\n':
                                                                        tokens.push_back(make_tuple(INST, "store"));
                                                                        return s0();
                                                                case '\t':
                                                                        tokens.push_back(make_tuple(INST, "store"));
                                                                        return s0();
                                                                case EOF:
                                                                        tokens.push_back(make_tuple(INST, "store"));
                                                                        break; */
                                                                default:
                                                                        tokens.push_back(make_tuple(INST, "store"));
                                                                        ungetc(c, inFile);
                                                                        s0();
                                                        }
                                                }
                                                case EOF:
                                                        break;
                                                default:
                                                        break;
                                        }
                                }
                                case EOF:
                                        break;
                                default:
                                        break;
                        }
                }
                case EOF:
                        break;
                default:
                        break;
        }
}

void s3()
{
        char c = getc(inFile);

        switch(c)
        {
                case 'b':
                {
                        c = getc(inFile);
                        switch(c)
                        {
                                /* case ' ':
                                        tokens.push_back(make_tuple(INST, "sub"));
                                        return s0();
                                case '\n':
                                        tokens.push_back(make_tuple(INST, "sub"));
                                        return s0();
                                case '\t':
                                        tokens.push_back(make_tuple(INST, "sub"));
                                        return s0();
                                case EOF:
                                        tokens.push_back(make_tuple(INST, "sub"));
                                        break; */
                                default:
                                        tokens.push_back(make_tuple(INST, "sub"));
                                        ungetc(c, inFile);
                                        s0();
                        }
                }
                case EOF:
                        break;
                default:
                        break;
        }
}

void s4()
{
        char c = getc(inFile);

        switch(c)
        {
                case 'o':
                        s5();
                case 's':
                        s7();
                case EOF:
                        break;
                default:
                        break;
        }
}

void s5()
{
        char c = getc(inFile);

        switch(c)
        {
                case 'a':
                {
                        c = getc(inFile);
                        switch(c)
                        {
                                case 'd':
                                {
                                        c = getc(inFile);
                                        switch(c)
                                        {
                                                case 'I':
                                                        return s6();
                                                /* case ' ':
                                                        tokens.push_back(make_tuple(INST, "load"));
                                                        return s0();
                                                case '\n':
                                                        tokens.push_back(make_tuple(INST, "load"));
                                                        return s0();
                                                case '\t':
                                                        tokens.push_back(make_tuple(INST, "load"));
                                                        return s0();
                                                case EOF:
                                                        tokens.push_back(make_tuple(INST, "load"));
                                                        break; */
                                                default:
                                                        tokens.push_back(make_tuple(INST, "load"));
                                                        ungetc(c, inFile);
                                                        s0();
                                        }
                                }
                                case EOF:
                                        break;
                                default:
                                        break;
                        }
                }
                case EOF:
                        break;
                default:
                        break;
        }
}

void s6()
{
        char c = getc(inFile);

        switch(c)
        {
                /* case ' ':
                        tokens.push_back(make_tuple(INST, "loadI"));
                        return s0();
                case '\n':false
                        tokens.push_back(make_tuple(INST, "loadI"));
                        return s0();
                case EOF:
                        tokens.push_back(make_tuple(INST, "loadI"));
                        break; */
                default:
                        tokens.push_back(make_tuple(INST, "loadI"));
                        ungetc(c, inFile);
                        s0();
        }
}

void s7()
{
        char c = getc(inFile);

        switch(c)
        {
                case 'h':
                {
                        c = getc(inFile);
                        switch(c)
                        {
                                case 'i':
                                {
                                        c = getc(inFile);
                                        switch(c)
                                        {
                                                case 'f':
                                                {
                                                        c = getc(inFile);
                                                        switch(c)
                                                        {
                                                                case 't':
                                                                {
                                                                        c = getc(inFile);
                                                                        switch(c)
                                                                        {
                                                                                /* case ' ':
                                                                                        tokens.push_back(make_tuple(INST, "lshift"));
                                                                                        return s0();
                                                                                case '\n':
                                                                                        tokens.push_back(make_tuple(INST, "lshift"));
                                                                                        return s0();
                                                                                case '\t':
                                                                                        tokens.push_back(make_tuple(INST, "lshift"));
                                                                                        return s0();
                                                                                case EOF:
                                                                                        tokens.push_back(make_tuple(INST, "lshift"));
                                                                                        break; */
                                                                                default:
                                                                                        tokens.push_back(make_tuple(INST, "lshift"));
                                                                                        ungetc(c, inFile);
                                                                                        s0();
                                                                        }
                                                                }
                                                                case EOF:
                                                                        break;
                                                                default:
                                                                        break;
                                                        }
                                                }
                                                case EOF:
                                                        break;
                                                default:
                                                        break;
                                        }
                                }
                                case EOF:
                                        break;
                                default:
                                        break;
                        }
                }
                case EOF:
                        break;
                default:
                        break;
        }
}

void s8()
{
        char c = getc(inFile);

        switch(c)
        {
                case 's':
                        s9();
                case '0' ... '9':
                        s10(c);
                case EOF:
                        break;
                default:
                        break;
        }
}

void s9()
{
        char c = getc(inFile);

        switch(c)
        {
                case 'h':
                {
                        c = getc(inFile);
                        switch(c)
                        {
                                case 'i':
                                {
                                        c = getc(inFile);
                                        switch(c)
                                        {
                                                case 'f':
                                                {
                                                        c = getc(inFile);
                                                        switch(c)
                                                        {
                                                                case 't':
                                                                {
                                                                        c = getc(inFile);
                                                                        switch(c)
                                                                        {
                                                                                /* case ' ':
                                                                                        tokens.push_back(make_tuple(INST, "rshift"));
                                                                                        return s0();
                                                                                case '\n':
                                                                                        tokens.push_back(make_tuple(INST, "rshift"));
                                                                                        return s0();
                                                                                case '\t':
                                                                                        tokens.push_back(make_tuple(INST, "rshift"));
                                                                                        return s0();
                                                                                case EOF:
                                                                                        tokens.push_back(make_tuple(INST, "rshift"));
                                                                                        break; */
                                                                                default:
                                                                                        tokens.push_back(make_tuple(INST, "rshift"));
                                                                                        ungetc(c, inFile);
                                                                                        s0();
                                                                        }
                                                                }
                                                                case EOF:
                                                                        break;
                                                                default:
                                                                        break;
                                                        }
                                                }
                                                case EOF:
                                                        break;
                                                default:
                                                        break;
                                        }
                                }
                                case EOF:
                                        break;
                                default:
                                        break;
                        }
                }
                case EOF:
                        break;
                default:
                        break;
        }
}

void s10(char i)
{
        int x = stoi(&i);
        numVal = numVal*10 + (x);
        string str = "r" + to_string(numVal);
        char c = getc(inFile);

        switch(c)
        {
                case '0' ... '9':
                        return s10(c);
                /* case ' ':
                        tokens.push_back(make_tuple(REG, str));
                        return s0();
                case '\n':
                        tokens.push_back(make_tuple(REG, str));
                        return s0();
                case '\t':
                        tokens.push_back(make_tuple(REG, str));
                        return s0();
                case ',':
                        tokens.push_back(make_tuple(REG, str));
                        tokens.push_back(make_tuple(COMMA, ","));
                        return s0();
                case EOF:
                        tokens.push_back(make_tuple(REG, str));
                        break; */
                default:
                        tokens.push_back(make_tuple(REG, str));
                        ungetc(c, inFile);
                        s0();
        }
}

void s11()
{
        char c = getc(inFile);

        switch(c)
        {
                case 'u':
                {
                        c = getc(inFile);
                        switch(c)
                        {
                                case 'l':
                                {
                                        c = getc(inFile);
                                        switch(c)
                                        {
                                                case 't':
                                                {
                                                        c = getc(inFile);
                                                        switch(c)
                                                        {
                                                                /* case ' ':
                                                                        tokens.push_back(make_tuple(INST, "mult"));
                                                                        return s0();
                                                                case '\n':
                                                                        tokens.push_back(make_tuple(INST, "mult"));
                                                                        return s0();
                                                                case '\t':
                                                                        tokens.push_back(make_tuple(INST, "mult"));
                                                                        return s0();
                                                                case EOF:
                                                                        tokens.push_back(make_tuple(INST, "mult"));
                                                                        break; */
                                                                default:
                                                                        tokens.push_back(make_tuple(INST, "mult"));
                                                                        ungetc(c, inFile);
                                                                        s0();
                                                        }
                                                }
                                                case EOF:
                                                        break;
                                                default:
                                                        break;
                                        }
                                }
                                case EOF:
                                        break;
                                default:
                                        break;
                        }
                }
                case EOF:
                        break;
                default:
                        break;
        }
}

void s12()
{
        char c = getc(inFile);

        switch(c)
        {
                case 'd':
                {
                        c = getc(inFile);
                        switch(c)
                        {
                                case 'd':
                                {
                                        c = getc(inFile);
                                        switch(c)
                                        {
                                                /* case ' ':
                                                        tokens.push_back(make_tuple(INST, "add"));
                                                        return s0();
                                                case '\n':
                                                        tokens.push_back(make_tuple(INST, "add"));
                                                        return s0();
                                                case '\t':
                                                        tokens.push_back(make_tuple(INST, "add"));
                                                        return s0();
                                                case EOF:
                                                        tokens.push_back(make_tuple(INST, "add"));
                                                        break; */
                                                default:
                                                        tokens.push_back(make_tuple(INST, "add"));
                                                        ungetc(c, inFile);
                                                        s0();
                                        }
                                }
                                case EOF:
                                        break;
                                default:
                                        break;
                        }
                }
                case EOF:
                        break;
                default:
                        break;
        }
}

void s13()
{
        char c = getc(inFile);

        switch(c)
        {
                case 'o':
                {
                        c = getc(inFile);
                        switch(c)
                        {
                                case 'p':
                                {
                                        c = getc(inFile);
                                        switch(c)
                                        {
                                                /* case ' ':
                                                        tokens.push_back(make_tuple(INST, "nop"));
                                                        return s0();
                                                case '\n':
                                                        tokens.push_back(make_tuple(INST, "nop"));
                                                        return s0();
                                                case '\t':
                                                        tokens.push_back(make_tuple(INST, "nop"));
                                                        return s0();
                                                case EOF:
                                                        tokens.push_back(make_tuple(INST, "nop"));
                                                        return s0(); */
                                                default:
                                                        tokens.push_back(make_tuple(INST, "nop"));
                                                        ungetc(c, inFile);
                                                        s0();
                                        }
                                }
                                case EOF:
                                        break;
                                default:
                                        break;
                        }
                }
                case EOF:
                        break;
                default:
                        break;
        }
}

void s14()
{
        char c = getc(inFile);

        switch(c)
        {
                case 'u':
                {
                        c = getc(inFile);
                        switch(c)
                        {
                                case 't':
                                {
                                        c = getc(inFile);
                                        switch(c)
                                        {
                                                case 'p':
                                                {
                                                        c = getc(inFile);
                                                        switch(c)
                                                        {
                                                                case 'u':
                                                                {
                                                                        c = getc(inFile);
                                                                        switch(c)
                                                                        {
                                                                                case 't':
                                                                                {
                                                                                        c = getc(inFile);
                                                                                        switch(c)
                                                                                        {
                                                                                                /* case ' ':
                                                                                                        tokens.push_back(make_tuple(INST, "output"));
                                                                                                        return s0();
                                                                                                case '\n':
                                                                                                        tokens.push_back(make_tuple(INST, "output"));
                                                                                                        return s0();
                                                                                                case '\t':
                                                                                                        tokens.push_back(make_tuple(INST, "output"));
                                                                                                        return s0();
                                                                                                case EOF:
                                                                                                        tokens.push_back(make_tuple(INST, "output"));
                                                                                                        break; */
                                                                                                default:
                                                                                                        tokens.push_back(make_tuple(INST, "output"));
                                                                                                        ungetc(c, inFile);
                                                                                                        s0();
                                                                                        }
                                                                                }
                                                                                case EOF:
                                                                                        break;
                                                                                default:
                                                                                        break;
                                                                        }
                                                                }
                                                                case EOF:
                                                                        break;
                                                                default:
                                                                        break;
                                                        }
                                                }
                                                case EOF:
                                                        break;
                                                default:
                                                        break;
                                        }
                                }
                                case EOF:
                                        break;
                                default:
                                        break;
                        }
                }
                case EOF:
                        break;
                default:
                        break;
        }
}

void s15()
{
        char c = getc(inFile);

        switch(c)
        {
                case '>':
                {
                        c = getc(inFile);
                        switch(c)
                        {
                                /* case ' ':
                                        tokens.push_back(make_tuple(ARROW, "=>"));
                                        return s0();
                                case '\n':
                                        tokens.push_back(make_tuple(ARROW, "=>"));
                                        return s0();
                                case '\t':
                                        tokens.push_back(make_tuple(ARROW, "=>"));
                                        return s0();
                                case EOF:
                                        tokens.push_back(make_tuple(ARROW, "=>"));
                                        break; */
                                default:
                                        tokens.push_back(make_tuple(ARROW, "=>"));
                                        ungetc(c, inFile);
                                        s0();
                        }
                }
                case EOF:
                        break;
                default:
                        break;
        }
}

void s16()
{
        char c = getc(inFile);

        switch(c)
        {
                /* case ' ':
                        tokens.push_back(make_tuple(COMMA, ","));
                        return s0();
                case '\n':
                        tokens.push_back(make_tuple(COMMA, ","));
                        return s0();
                case '\t':
                        tokens.push_back(make_tuple(COMMA, ","));
                        return s0();
                case EOF:
                        tokens.push_back(make_tuple(COMMA, ","));
                        break; */
                default:
                        tokens.push_back(make_tuple(COMMA, ","));
                        ungetc(c, inFile);                       
                        s0();
        }
}

void s17(char i)
{
        int x = i - '0';
        numVal = numVal*10 + (x + 0);
        string str = to_string(numVal);
        char c = getc(inFile);

        switch(c)
        {
                case '0' ... '9':
                        s17(c);
                /* case ' ':
                        tokens.push_back(make_tuple(CONST, str));
                        return s0();
                case '\n':
                        tokens.push_back(make_tuple(CONST, str));
                        return s0();
                case '\t':
                        tokens.push_back(make_tuple(CONST, str));
                        return s0();
                case EOF:
                        tokens.push_back(make_tuple(CONST, str));
                        break; */
                default:
                        tokens.push_back(make_tuple(CONST, str));
                        ungetc(c, inFile);
                        s0();
        }
}

void s18()
{
        char c = getc(inFile);

        switch(c)
        {
                case '/':
                        commented = true;
                        s18();
                case '\n':
                        commented = false;
                        s0();
                case EOF:
                        break;
                default:
                        if(commented) s18();
                        else s0();
        }
}