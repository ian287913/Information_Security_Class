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

void main()
{
	Encoder encoder;

	cout << encoder.Caesar("7", "keepgoingnevergiveup") << "\n";

	cout << encoder.Playfair("playfairexample", "hidethegoldinthetreestump") << "\n";

	cout << encoder.Vernam("queenly", "attackatdawn") << "\n";

	
	system("pause");
}