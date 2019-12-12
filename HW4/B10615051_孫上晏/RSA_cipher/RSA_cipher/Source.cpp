#include <iomanip>
#include <iostream>
#include<string>
#include<math.h>
using namespace std;

//	predefined numbers
#define p 13
#define q 11
#define n 143	//	n = p * q
#define e 17	//	1 < e < (phi(n) = (p - 1) * (q - 1))
#define d 113	//	d = e^(−1) (mod phi(n))

void EncryptRSA()
{
	cout << "Plaintext here: \n";
	string text = "";
	getline(cin, text);	//	to dispose \n
	getline(cin, text);

	cout << "The cipher text: \n";

	for (int t = 0; t < text.size(); t++)
	{
		int cipherText = 1;
		for (int i = 0; i < e; i++)
		{
			cipherText = (cipherText * (int)(text[t])) % n;
		}

		cout << setfill('0') << setw(3) << cipherText;
	}
	cout << "\n\n";
}

//	for numbers "###"
void DecryptRSA()
{
	cout << "Cipher number here: \n";
	string text = "";
	getline(cin, text);	//	to dispose \n
	getline(cin, text);


	cout << "The plain text: \n";
	for (int t = 0; t < text.size(); t+=3)
	{
		int cipherNumber = stoi(text.substr(t, 3));

		int plainText = 1;
		for (int i = 0; i < d; i++)
		{
			plainText = (plainText * cipherNumber) % n;
		}

		cout << (char)plainText;
	}
	cout << "\n\n";
}

int main()
{
	char cipherMode;
	cout << "Please select the cipher mode ('e' for encode / 'd' for decode): ";
	while (cin >> cipherMode)
	{
		switch (cipherMode)
		{
			//	encode
		case 'e':
		case 'E':
			EncryptRSA();
			break;
			//	decode
		case 'd':
		case 'D':
			DecryptRSA();
			break;
		default:
			cout << "Undefined mode. Please try 'e' or 'd'\n";
			break;
		}
		cout << "Please select the cipher mode ('e' for encode / 'd' for decode): ";
	}

	system("pause");
	return 0;
}
