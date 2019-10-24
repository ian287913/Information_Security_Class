#include <iostream>
#include "Encoder.h"
using namespace std;

///////////
//	Encryption
//	DES
///////////

void Debug(Encoder &encoder)
{
	cout << encoder.DES("0xafafafafafafafaf ", "0xabcdef0123456789") << endl;
	///cout << encoder.Caesar("7", "keepgoingnevergiveup") << "\n";
	//	RLLWNVPUNULCLYNPCLBW
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