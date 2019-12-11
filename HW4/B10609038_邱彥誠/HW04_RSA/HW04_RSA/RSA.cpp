#include"RSA.h"

void PrintKeys()
{
	cout << "\tRSA keys for this program:" << endl;
	cout << "\tp: " << RSA_p << endl;
	cout << "\tq: " << RSA_q << endl;
	cout << "\tn: " << RSA_n << endl;
	cout << "\te: " << RSA_e << endl;
	cout << "\td: " << RSA_d << endl;
}

void Encrypt(string plaintext)
{
	cout << "\tEncrypted result: \n" << "\t ";
	for (char c : plaintext)
	{
		int number = c;
		int total = 1;
		for (int i = 0; i < RSA_e; i++)
		{
			total = (total * number) % RSA_n;
		}
		cout << total << " ";
	}
	cout << endl << endl;
}

void Decrypt(string ciphertext)
{
	stringstream ss;
	ss << ciphertext;
	cout << "\tDecrypted result: " << endl << "\t ";

	int number;
	string temp;
	while (!ss.eof()) 
	{
		ss >> temp;

		/* Checking the given word is integer or not */
		if (stringstream(temp) >> number)
		{
			int total = 1;
			for (int i = 0; i < RSA_d; i++)
			{
				total = (total * number) % RSA_n;
			}
			cout << (char)(total);
		}
		else
		{
			break;
		}
		temp = "";
	}
	cout << endl << endl;
}