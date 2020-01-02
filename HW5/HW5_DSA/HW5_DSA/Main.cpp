#include "sha1.hpp"
#include <string>
#include <iostream>
#include <time.h>
using std::string;
using std::cout;
using std::endl;
using namespace std;

#define HashRange 10000000

void GenerateKey();
void Sign(int);
void Sign(string);
void Verify(int, int, int);
void Verify(string, int, int);
int p = 59, q = 29, a = 3, b = 4, d = 7;

int main()
{
	// 產生key: pub(p, q, a, b) prv(d)
	GenerateKey();
	do
	{
		cout << "=========================================" << endl;
		cout << " Enter 'k' for generate the keys." << endl;
		cout << " Enter 's' for sign a message. (number only)" << endl;
		cout << " Enter 'v' for verify a signature. (number only)" << endl;
		cout << " Enter other keys to exit." << endl;
		cout << "=========================================" << endl;
		cout << " Enter: ";
		char mode;
		cin >> mode;
		int input = 0;
		int r = 0, s = 0;
		string message;
		switch (mode)
		{
		case 'k':
			GenerateKey();
			break;
		case 's':
			cout << " Enter a message: ";
			cin >> message;
			Sign(message);
			break;
		case 'v':
			cout << " Enter message to verify: ";
			cin >> message;
			cout << " Enter s: ";
			cin >> s;
			cout << " Enter r: ";
			cin >> r;
			Verify(message, s, r);
			break;
		default:
			return 0;
			break;
		}
	} while (true);
}

void GenerateKey()
{
	cout << "-Generate Keys:" << endl;
	cout << "\tp =\t" << p << endl;
	cout << "\tq =\t" << q << endl;
	cout << "\td =\t" << d << endl;
	cout << "\talpha =\t" << a << endl;
	cout << "\tbeta =\t" << b << endl;
}
void Sign(int message)
{

	// 產生hash (無實作)
	int h = message;

	// 選擇KE
	srand(time(NULL));
	int ke = (rand() + 1) % q;
	int vke;
	for (int i = 2; i < q; i++)
	{
		if ((ke * i) % q == 1)
		{
			vke = i;
			break;
		}
	}

	// 計算r
	int r = 1;
	for (int i = 0; i < ke; i++)
	{
		r = (r * a) % p;
	}
	r = r % q;

	// 計算s
	int s = ((h + d * r) * vke) % q;

	cout << " Result:" << endl;
	cout << " message:\t" << message << endl;
	cout << " s: \t\t" << s << endl;
	cout << " r: \t\t" << r << endl;
}

void Sign(string message)
{
	int m = 0;
	for (char c : message)
	{
		m = (m + ((int)c % HashRange)) % HashRange;
	}
	Sign(m);
}

void Verify(int message, int s, int r)
{
	int w;
	for (int i = 2; i < q; i++)
	{
		if ((s * i) % q == 1)
		{
			w = i;
			break;
		}
	}

	int u1 = (w * message) % q;
	int u2 = (w * r) % q;
	int A = 1;
	for (int i = 0; i < u1; i++)
	{
		A = (A * a) % p;
	}
	int B = 1;
	for (int i = 0; i < u2; i++)
	{
		B = (B * b) % p;
	}

	int v = ((A * B) % p) % q;

	if (r == v)
		cout << " Verify result: Valid." << endl;
	else
		cout << " Verify result: Invalid." << endl;
}

void Verify(string message, int s, int r)
{
	int m = 0;
	for (char c : message)
	{
		m = (m + ((int)c % HashRange)) % HashRange;
	}
	Verify(m, s, r);
}