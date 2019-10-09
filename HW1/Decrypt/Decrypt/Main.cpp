#include"Decrypt.h"
using namespace std;
// Test:
// caesar 7 RLLWNVPUNULCLYNPCLBW						-----keepgoingnevergiveup
// playfair PLAYFAIREXAMPLE BMODZBXDNABEKUDMUIXMMOUVIF	-----hidethegoldinthetreestump
// vernam QUEENLYATTAC QHXEPBYTQTWP						-----attackatdawn
// row 4312567 TTNAAPTMTSUOAODWCOIXKNLYPETZ				-----attackpostponeduntiltwoamxyz
// rail_fence 2 MEMATRHTGPRYETEFETEOAAT					-----thisisasecretmessage 
int main(int argc, char *argv[])
{
	const string type[5] = { 
		"caesar",
		"playfair",
		"vernam",
		"row",
		"rail_fence" 
	};
	string cipherType = argv[1];
	string key = argv[2];
	string cipherText = argv[3];

	int typeNum = -1;
	for (int typeIndex = 0; typeIndex < 5; typeIndex++)
	{
		if (type[typeIndex] == cipherType)
		{
			typeNum = typeIndex;
			break;
		}
	}

	int numberKey;
	
	switch (typeNum)
	{
	case 0:
		// caesar
		numberKey = stoi(key);
		Caesar(cipherText, numberKey);
		break;
	case 1:
		// playfair
		Playfair(cipherText, key);
		break;
	case 2:
		// vernam
		Vernam(cipherText, key);
		break;
	case 3:
		// row
		Row(cipherText, key);
		break;
	case 4:
		// rail_fence
		numberKey = stoi(key);
		RailFence(cipherText, numberKey);
		break;
	default:
		cout << "Invalid Cipher Input!" << endl;
		break;
	}
	return 0;
}