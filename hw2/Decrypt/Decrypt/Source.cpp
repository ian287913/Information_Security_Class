#include <iostream>
#include "Decoder.h"
using namespace std;

///////////
//	Encryption
//	DES
///////////

void Debug(Decoder &decoder)
{
	cout << decoder.DES("0x133457799BBCDFF1", "0x85E813540F0AB405");
	//	0x0123456789abcdef
	cout << decoder.DES("0xafafafafafafafaf", "0x4C30FC30FB2B0BFF");
	//	0xabcdef0123456789
}

void main(int argc, char *argv[])
{
	Decoder decoder;

	if (argc != 3)
	{
		Debug(decoder);


		system("pause");
		return;
	}

	cout << decoder.DES(argv[1], argv[2]);

	return;
}