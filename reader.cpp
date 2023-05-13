#include "reader.h"

FILE* inFile;

int state = 0;

int main(int argc, char** argv)
{
        //OPT HANDLING
        //int opt; unused variable
        bool tFlag = false;
        bool pFlag = false;
        bool kFlag = false;

        int kVal = 3;
        const struct option longopts[] =
        {
                {"help", no_argument, 0, 'h'},
                {"tokens", no_argument, 0, 't'},
                {"print", no_argument, 0, 'p'},
                {"allocator", no_argument, 0, 'k'} //posibly need to add PR limit
        };


        int index;
        int iarg = 0;
        while(iarg != -1)
        {
                iarg = getopt_long(argc, argv, "htpk", longopts, &index);


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
                        case 'k':
                                cout << "printing allocator" << endl;
                                kFlag = true;
                                if(optarg != NULL)
                                {
                                        if(sscanf(optarg, "%d", &kVal) != 1)
                                        {
                                                cerr << "Invalid argument for -k, type -h for help\n";
                                                exit(-1);
                                        }
                                        else if(kVal < 0)
                                        {
                                                cerr << "Invalid argument for -k, type -h for help\n";
                                                exit(-1);
                                        }
                                        else
                                        {
                                                cout << "kVal = " << kVal << endl;
                                        }
                                }
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
        vector<tuple<string, string, string, string>> tempTable = parser(scanToken(tFlag, pFlag));
        if (kFlag)
        {
                cout << "Calling allocator" << endl;
                //vector<Line> tempBlock = returnBlock();
                vector<Line> tempBlock = populateBlock(tempTable);
                naiveAllocator(tempBlock, kVal);
        }
        else{
                //vector<tuple<string, string, string, string>> tempTable = parser();
                printTable(tempTable);
                //printILOC(tempTable);
        }
        //table = parser();
        //naiveAllocator(table, kVal);
        //cout << "Ending scanToken" << endl;


        fclose(inFile);
        return EXIT_SUCCESS;
}


//FLAG FUNCTIONS
void PrintHelp()
{
        cout << "Usage: ./reader <filepath> [options]\n" <<
                "Options:\n";
        cout << "-h:\tPrints a helpful message\n" <<
                "-t:\tPrints a list of tokens - does nothing rn\n" <<
                "-p:\tPrints ILOC code - does nothing rn\n" <<
                "-k <num>:\trequires an int as an argument to define the max amount of physical registers\n"; 
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
