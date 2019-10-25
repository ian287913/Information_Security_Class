#include <iostream>
#include "Encoder.h"
using namespace std;

///////////
//	Encryption
//	DES
///////////

void Debug(Encoder &encoder)
{
	cout << encoder.DES("0x133457799BBCDFF1", "0x0123456789abcdef");
	//	0x85E813540F0AB405
	cout << encoder.DES("0xafafafafafafafaf", "0xabcdef0123456789");
	//	0x4C30FC30FB2B0BFF
}

void main(int argc, char *argv[])
{
	Encoder encoder;

	if (argc != 3)
	{
		Debug(encoder);


		system("pause");
		return;
	}

	cout << encoder.DES(argv[1], argv[2]);

	return;
}