#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

int main()
{
    int C, byteConst;                                            // Instruction variables one and two
    unsigned char regs[16];                                      // Registries
    char prog_mem[256], symb;                                    // Program memory and symbol variable
    bool flag_EOF = false, flag_zero = false, running = true;    // Two flag registries, boolean value for while loop

    ifstream readBinary("decryptor.bin", ios::in | ios::binary); // Preloading program memory with instructions
    readBinary.read(&prog_mem[0], 256);                          //
    readBinary.close();                                          //

    ifstream readEncrypted("q1_encr.txt");
    ofstream write("result.txt");

    while (running)
    {
        for (int i = 0; i < 255; i += 2)                         // Program memory iterator
        {                                                        //
            C = prog_mem[i];                                     // Reading first hex value of relative instruction
            byteConst = prog_mem[i + 1];                         // Reading second hex value of relative instruction
                                                                 //
            switch (C)                                           // Command registry, supporting 17 different instructions
            {
            case 1:// INC
                regs[byteConst] = (regs[byteConst & 0x0F]) + 1;
                if (regs[byteConst & 0x0F] == 0) flag_zero = true;
                    else flag_zero = false;
                break;

            case 2:// DEC
                regs[byteConst] = (regs[byteConst & 0x0F]) - 1;
                if (regs[byteConst & 0x0F] == 0) flag_zero = true;
                    else flag_zero = false;
                break;

            case 3:// MOV
                regs[byteConst & 0x0F] = (regs[byteConst & 0xF0]) >> 4;
                break;

            case 4:// MOVC
                regs[0] = byteConst;
                break;

            case 5:// LSL
                regs[byteConst & 0x0F] = (regs[byteConst & 0x0F]) << 1;
                break;

            case 6:// LSR
                regs[byteConst & 0x0F] = (regs[byteConst & 0x0F]) >> 1;
                break;

            case 7:// JMP
                i += byteConst, i -= 2;
                break;

            case 8:// JZ
                if (flag_zero == true){
                    i += byteConst; 
                    i -= 2;
                    flag_zero = false;
                }         
                break;

            case 9:// JNZ
                if (flag_zero == false)
                    i += byteConst, i -= 2;
                break;

            case 10:// JFE
                if (flag_EOF == true)
                    i += byteConst, i -= 2;
                break;
                
            case 11:// RET
                cout << "\nStopping the VM...";
                running = false;
                return 0;
                break;

            case 12:// ADD
                regs[byteConst & 0x0F] = regs[byteConst & 0x0F] + (regs[(byteConst & 0xF0) >> 4]);
                if (regs[byteConst & 0x0F] == 0) flag_zero = true;
                    else flag_zero = false;
                break;

            case 13:// SUB
                regs[byteConst & 0x0F] = regs[byteConst & 0x0F] - (regs[(byteConst & 0xF0) >> 4]);
                if (regs[byteConst & 0x0F] == 0) flag_zero = true;
                    else flag_zero = false;
                break;

            case 14:// XOR
                regs[byteConst & 0x0F] = regs[byteConst & 0x0F] ^ (regs[(byteConst & 0xF0) >> 4]);
                if (regs[byteConst & 0x0F] == 0) flag_zero = true;
                    else flag_zero = false;
                break;

            case 15:// OR
                regs[byteConst & 0x0F] = regs[byteConst & 0x0F] | (regs[(byteConst & 0xF0) >> 4]);
                if (regs[byteConst & 0x0F] == 0) flag_zero = true;
                    else flag_zero = false;
                break;

            case 16:// IN
             readEncrypted >> regs[byteConst & 0x0F];
                if (readEncrypted.eof())
                    flag_EOF = true;
                break;

            case 17:// OUT
                write << regs[byteConst & 0x0F];
                break;
            }
        }
    }

    readEncrypted.close();
    write.close();
}
