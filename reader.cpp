#include "reader.h"

FILE* inFile;

int state = 0;

int main(int argc, char** argv)
{
        //OPT HANDLING
        //int opt; unused variable
        bool tFlag = false;
        bool pFlag = false;
        const struct option longopts[] = 
        {
                {"help", no_argument, 0, 'h'},
                {"tokens", no_argument, 0, 't'},
                {"print", no_argument, 0, 'p'}
        };

        int index;
        int iarg = 0;
        while(iarg != -1)
        {
                iarg = getopt_long(argc, argv, "htp", longopts, &index);

                switch(iarg)
                {
                        case 'h':
                                cout << "Printing help" << endl;
                                PrintHelp();
                                exit(1);
                                break;
                        case 't':
                                cout << "Printing tokens" << endl;
                                void PrintTokens();
                                tFlag = true;
                                break;
                        case 'p':
                                cout << "pretty printing" << endl;
                                pFlag = true;
                                break;
                        case '?':
                                cerr << "Invalid flag, type -h for help\n";
                                exit(-1);
                                break;
                        default:
                                break;
                }
        }
        
        //INPUT HANDLING
        inFile = fopen(argv[optind], "r");
        if(inFile == nullptr) return EXIT_FAILURE;
        //char c; unused variable
        //cout << "Calling scanToken" << endl;
        scanToken(tFlag, pFlag);
        //cout << "Ending scanToken" << endl;

        fclose(inFile);
        return EXIT_SUCCESS;
}

//FLAG FUNCTIONS
void PrintHelp()
{
        cout << "-h:\tPrints a helpful message\n" << 
                "-t:\tPrints a list of tokens\n" <<
                "-p:\tPrints ILOC code\n";
}

void PrintTokens() //Deprecated
{
        cout << "-t option\n";
}

void ScanErr(char c)
{
        cerr << "Invalid char " << c << "\n";
        exit(-1);
}
