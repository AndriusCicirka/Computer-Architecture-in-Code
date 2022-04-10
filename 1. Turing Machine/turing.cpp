#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <windows.h>

using namespace std;

struct programTape{
    string currentState, newState;
    char currentSymbol, direction, newSymbol;
};

int main(int argc, char* argv[4] = {0})
{
    int headPosition, a = 0, b = 0, cycles = 0, limit, slowMode;
    string fileName;
    char x;

    vector <char> tape;
    vector <programTape> program;

    fileName = argv[1];
    ifstream read(fileName);
    if(atoi(argv[2]) == 0) limit = 2500;
        else limit = atoi(argv[2]);

    if(atoi(argv[3]) == 0) slowMode = 0;
        else slowMode = 250;

    system("cls");
    cout << "Starting the machine with tape from a file: " << argv[1];
    cout << "\nLimit of machine cycles before prompt: " << limit;
    cout << "\nSlow mode: ";
    if(slowMode != 0) cout << "turned ON\n\n\n";
        else cout << "turned OFF\n\n\n";

    system("pause");
    cout << "\n\n";

    while(x != '\n')
        x = read.get(), tape.push_back(x);

    read >> headPosition;

    while(!read.eof()){
        program.push_back(programTape());
            read >> program.at(a).currentState;
            read >> program.at(a).currentSymbol;
            read >> program.at(a).newSymbol;
            read >> program.at(a).direction;
            read >> program.at(a).newState;
            a++; 
    }
    
    string currentState = "0";

    while(true){
        for(int i = 0; i < tape.size(); i++) //Printing the machine 'tape'
            cout << tape.at(i);

        cout << setw(headPosition) << "^"; //Printing the 'tape head'
        
        if(headPosition == tape.size()|| headPosition < 0){
            cout << "\nThe edge of the tape has been reached!";
            break;
        }

        int loop = 1;
        for(int i = 0; i < a; i++){//Scanning through the whole tape
            if(currentState == program.at(i).currentState && tape.at(headPosition - 1) == program.at(i).currentSymbol)
            {   //Element 1
                tape.at(headPosition - 1) = program.at(i).newSymbol; //Element 2
                if(program.at(i).direction == 'L') headPosition--; //Moving the 'tape head'
                    else if(program.at(i).direction == 'R') headPosition++;
                        else{
                            cout << "\n\nError in adressing a new direction!";
                            break;
                        } 

                currentState = program.at(i).newState; //Setting a new machine state
                i = a; //Finishing the scan;
                loop = 0;
            }              
        }

        if(loop == 1){
            cout << "\nThe machine has stopped!\n";
            break;
        }
        
        Sleep(slowMode);
        
        cycles++;
        reprompt:
        if(cycles == limit){
            cout << "\n\nThe limit has been reached! Continue without a limit? (Y/N): ";
            cin >> x;
            if(x == 'Y' || x == 'y'){
                limit--;
                cout << "\n\nContinuing:\n\n";
                Sleep(1000);
            } 
                else if(x == 'N' || x == 'n'){
                    cout << "\n\nThe machine has stopped!\n";
                    break;
                }
                else goto reprompt;
        } 
        cout << "\n";
   }

    read.close();

    return 0;
}   
