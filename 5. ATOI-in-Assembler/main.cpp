#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main(int argc, char** argv)
{
	int pcOut = 0, n;
	char* pcInp;
	string input;

	pcInp = argv[1];
	input = pcInp;
	cout << "Original string input: " << input << "\n";

	__asm
	{

		push eax
		push ebx
		push ecx

		xor ebx, ebx              // zero ebx                       
		mov ecx, pcInp            // Address of argv[1]             
		dec ecx                   // loop increases ecx at start  
								  // so we decrease to compensate    
		aloop :
		inc ecx                   // ecx points to next char in string 
		mov al, byte ptr[ecx]    // byte of string to al           
		cmp al, 0                 // compare to zero (string end )  
		je exit_aloop              // if zero byte (string end)         
									  //  then exit                     
		cmp al, 'A'               // compare to A                    
		jl aloop		          // if less, then loop to lext char 
		cmp al, 'z'               // compare to last char 'z'       
		jg aloop		          // if greater, loop next char     

		cmp al, 'Z'               // compare to Z                                
		jle inc_a_count        // if less or equal to Z, inc counter 
		cmp al, 'a'               //                                 
		jge inc_a_count        // if greater or equal than 'a', inc counter 

		jmp aloop                 // otherwise loop to next char     

		inc_a_count :           // counter increase starts here  
		inc ebx                   // increasing counter              
		jmp aloop                 // and loop to next char           

		exit_aloop :                // end point    

		cmp ebx, 0
		jg NI

		pop ecx
		pop ebx
		pop eax

		push eax	//Loading registries
		push ebx	//
		push ecx	//
		push edx	//

		//
		xor ebx, ebx              // zero ebx                       
		mov ecx, pcInp            // Address of argv[1]
		dec ecx                   // loop increases ecx at start  
								  // so we decrease to compensate
		sloop :

		inc ecx                   // ecx points to next char in string 
		mov al, byte ptr[ecx]    // byte of string to al           
		cmp al, 0                 // compare to zero (string end )  
		je exit_loop              // if zero byte (string end)         
									  //  then exit                     
		cmp al, '0'               // compare to A                    
		jl sloop		          // if less, then loop to lext char 
		cmp al, '9'               // compare to last char 'z'       
		jg sloop		          // if greater, loop next char     

		cmp al, '9'               // compare to Z                                
		jle inc_char_count        // if less or equal to Z, inc counter 
		cmp al, '0'               //                                 
		jge inc_char_count        // if greater or equal than 'a', inc counter 

		jmp sloop                 // otherwise loop to next char     

		inc_char_count :           // counter increase starts here  
		inc ebx                    // increasing counter              
		jmp sloop                  // and loop to next char           

		exit_loop :                // end point                       
		
		mov edx,ebx				   // answer to variable 
		
		//

		xor eax, eax
		xor ebx, ebx
		xor ecx, ecx
		
		mov ebx, 1
		mov ecx, pcInp

		add ecx, edx
		dec ecx

		STOI :
		cmp edx, 0
		jle EXIT

		xor eax, eax
		mov al, byte ptr[ecx]
		sub eax, '0'
		imul eax, ebx

		dec ecx
		imul ebx, 10
		add pcOut, eax
		jo OF

		dec edx
		jmp STOI

		OF:
		mov pcOut, -1
		jmp EXIT

		NI:
		push edx
		mov pcOut, -2

		EXIT :

		pop edx		//
		pop ecx		//
		pop ebx		//
		pop eax		//Unloading registries in reverse order
	}

	if (pcOut == -1) cout << "Overflow";
	else if (pcOut == -2) cout << "Wrong input";
	else cout << "String converted to Integer: " << pcOut;

	return 0;
}
