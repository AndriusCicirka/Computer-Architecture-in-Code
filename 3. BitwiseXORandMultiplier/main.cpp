#include <iostream>
#include <fstream>

using namespace std;

int fullAdder(int a, int& carry, int sum, int result);

int main(int argc, char *argv[2]){

    //list separator - ;
    ofstream write("result.csv");

    write << "3 laboratorinis darbas\n\n";

    int a, b, tempA, tempB, result = 0, carry = 0, sum = 0;

    a = stoi(argv[1]);
    b = stoi(argv[2]);

    write << "A   :;" << a << "\n";
    write << "B   :;" << b << "\n\n";

    //1 XOR

    write << "1 XOR:;(~A & B) |;(A & ~B)  =;";
    write << ((~a & b) | (a & ~b)) << "\n";

    //2 XOR

    write << "2 XOR:;(A | B)   &;~(A & B)  =;";
    write << ((a | b) & ~(a & b)) << "\n";

    //3 XOR

    write << "3 XOR:;(A | B)   &;(~A | ~B) =;";
    write << ((a | b) & (~a | ~b)) << "\n";

    //4 XOR

    write << "4 XOR:;~( ~(A & ~;(A  &  B)) ;& ~(B &  ~;(A & B))) =;";
    write << ~(~(a & ~(a & b)) & ~(b & ~(a & b))) << "\n\n";

    //Multiplication

while(b != 0){

    if((b & 1) != 0)
        result = fullAdder(a, carry, sum, result);

    a <<= 1;
    b >>= 1;
}   

    write << "Daugyba:;" << result;
    write.close();

    return 0;
}

int fullAdder(int a, int& carry, int sum, int result){

    int tempA, tempB, temp = 0;

    for(int i = 0; i < 32; i++){
        tempA = 1 & (a >> i);
        tempB = 1 & (result >> i);

        sum = ((tempA ^ tempB) ^ carry);
        carry = (((tempA ^ tempB) & carry) | (tempA & tempB));
        temp |= sum << i;
    }

    return temp;
}