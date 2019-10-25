#include <iostream>
#include "Encoder.h"
using namespace std;

///////////
//	Encryption
//	DES
//	http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm
///////////

void Debug(Encoder &encoder)
{
	cout << encoder.DES("0x133457799BBCDFF1", "0x0123456789abcdef") << endl;
	//	85E813540F0AB405
}

void main(int argc, char *argv[])
{
	Encoder encoder;

	/*string s = "0xabcd";
	stringstream ss;
	ss << hex << s;
	unsigned n;
	ss >> n;
	bitset<32> bs(n);
	cout << "0x" << hex << uppercase << bs.to_ulong() << endl;*/

	if (argc != 3)
	{
		Debug(encoder);


		system("pause");
		return;
	}

	string encodeType(argv[1]);

	///cout << encoder.Caesar(argv[2], argv[3]);

	return;
}