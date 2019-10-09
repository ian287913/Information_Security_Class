#include <iostream>
#include "Encoder.h"
using namespace std;

///////////
//	Encryption
//	Caesar cipher
//	Playfair cipher
//	Vernam proposed the autokey system
//	Row transposition
//	Rail fence cipher
///////////

void Debug(Encoder &encoder)
{
	cout << encoder.Caesar("7", "keepgoingnevergiveup") << "\n";
	//	RLLWNVPUNULCLYNPCLBW
	
	cout << encoder.Playfair("playfairexample", "hidethegoldinthetreestump") << "\n";
	//	BMODZBXDNABEKUDMUIXMMOUVIF
	
	cout << encoder.Vernam("queenly", "attackatdawn") << "\n";
	//	QHXEPBYTQTWP
	
	cout << encoder.RowTransposition("4312567", "attackpostponeduntiltwoamxyz") << "\n";
	//	TTNAAPTMTSUOAODWCOIXKNLYPETZ
	
	cout << encoder.RailFence("3", "thisisasecretmessage") << "\n";
	//	TIETSHSSSCEMSAEIAREG

}

void main(int argc, char *argv[])
{
	Encoder encoder;

	if (argc != 4)
	{
		Debug(encoder);
		system("pause");
		return;
	}

	string encodeType(argv[1]);

	if (encodeType == "caesar")
	{
		cout << encoder.Caesar(argv[2], argv[3]);
	}
	else if (encodeType == "playfair")
	{
		cout << encoder.Playfair(argv[2], argv[3]);
	}
	else if (encodeType == "vernam")
	{
		cout << encoder.Vernam(argv[2], argv[3]);
	}
	else if (encodeType == "row")
	{
		cout << encoder.RowTransposition(argv[2], argv[3]);
	}
	else if (encodeType == "rail_fence")
	{
		cout << encoder.RailFence(argv[2], argv[3]);
	}
	else
	{
		cout << "Unknown cipher type...";
	}

	return;
}