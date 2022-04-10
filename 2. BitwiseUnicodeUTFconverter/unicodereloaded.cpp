#include <iostream>
#include <fstream>

using namespace std;

class characterDecoding
{

public:

int x, y, ref[257] = {0};
long int n, byte; 
unsigned char s;
char c[4] = {0}, symb;
string size;

void enterSymbol(){

    cout << "Insert a number: ";
    cin >> n;
}

void readCharacter(){

    ifstream read;
    ofstream write;

    read.open("cp437.txt");
        
        for(int i = 176; i <= 225; i++){
            read >> hex >> y;
            if(i == 225) i = 254;
            ref[i] = y;
        }

    read.close();
  
    read.open("386intel.txt");
    write.open("output.txt");
  
    while(read.get(symb)){
  	    s = (unsigned char)symb;
  	    n = (int)s;
        if(n >= 176 && n <= 224 || n == 254) {
            n = ref[n];
            checkingByteSize();
            convertToUTF();
            write << c;
        }
        else if(n < 128){
            size = "1byte";
            convertToUTF();
            write << c;
        }
        else{
            checkingByteSize();
            convertToUTF();
            write << c;
        }       
    }     
}

void checkingByteSize(){

    if(n >= 0 && n < 128){
        size = "1byte";
        //cout << "Unicode: U+00" << hex << uppercase << n << "\n";
    }
    else if(n >= 128 && n < 2048){
        size = "2byte";
       // if(n > 255) cout << "Unicode: U+0" << hex << uppercase << n << "\n";
       //     else cout  << "Unicode: U+00" << hex << uppercase << n << "\n";
    } 
    else if(n >= 2048 && n < 65535){
        size = "3byte";
      //  if(n > 4095) cout << "Unicode: U+" << hex << uppercase << n << "\n";
      //      else cout << "Unicode: U+0" << hex << uppercase << n << "\n";
    } 
    else if(n >= 65535 && n <= 1114111){
        size = "4byte";
      //  cout << "Unicode: U+" << hex << uppercase << n << "\n";
    } 
    else cout << "Error!", exit(0);
}

void convertToUTF(){

    if(size == "1byte"){
        byte = n;
       // cout << "UTF - 8: " << hex << uppercase << ((byte >> 4) & 0b1111) << (byte & 0b1111);
        c[0] = byte;
    }

    if(size == "2byte"){

        byte = 0b1100000010000000;
        byte |= ((n << 2) & 0b11111000000);
        byte |= (n & 0b111111);
 /*       
        cout << "UTF - 8: ";
        cout << hex << uppercase << (n >> 12) << ((n >> 8) & 0b1111) << " ";
        cout << hex << uppercase << ((n >> 4) & 0b1111) << (n & 0b1111);
*/
        c[0] = ((n >> 12) & (n >> 8));
        c[1] = ((n >> 4) & (n & 0b1111));
        
    }

    if(size == "3byte"){

        byte = 0b111000001000000010000000;
        byte |= ((n << 4) & 0b11110000000000000000);
        byte |= ((n << 2) & 0b111111000000000);
        byte |= (n & 0b111111);

      /*  cout << "UTF - 8: ";
        cout << hex << uppercase << (n >> 20) << ((n >> 16) & 0b1111) << " ";
        cout << hex << uppercase << ((n >> 12) & 0b1111) << ((n >> 8) & 0b1111) << " ";
        cout << hex << uppercase << ((n >> 4) & 0b1111) << (n & 0b1111);
*/
        c[0] = ((n >> 20) & (n >> 16));
        c[1] = ((n >> 12) & (n & 8));
        c[2] = ((n >> 4) & (n & 0b1111));
        
    }

    if(size == "4byte"){

        byte = 0b11110000100000001000000010000000;
        byte |= ((n << 6) & 0b111000000000000000000000000);
        byte |= ((n << 4) & 0b1111110000000000000000);
        byte |= ((n << 2) & 0b11111100000000);
        byte |= (n & 0b111111);

 /*       cout << "UTF - 8: ";
        cout << hex << uppercase << (n >> 28) << ((n >> 24) & 0b1111) << " ";
        cout << hex << uppercase << (n >> 20) << ((n >> 16) & 0b1111) << " ";
        cout << hex << uppercase << ((n >> 12) & 0b1111) << ((n >> 8) & 0b1111) << " ";
        cout << hex << uppercase << ((n >> 4) & 0b1111) << (n & 0b1111);
        */

        c[0] = ((n >> 28) & (n >> 24));
        c[1] = ((n >> 20) & (n >> 16));
        c[2] = ((n >> 12) & (n & 8));
        c[3] = ((n >> 4) & (n & 0b1111));
        
    }

    //cout << "\nChar   : " << c;
}
};

int main(int argc, char *argv[2]){

    characterDecoding C;

    //C.enterSymbol();
    //C.checkingByteSize();
    //C.convertToUTF();

    C.readCharacter();

    return 0;
}