#include"RSA.h"

/*
1. Euler Phi的實作用wiki的 euler product formula比較實際，老師PDF給的不太能實作出來(Chap0809-part1, pg22)
2. Miller-rabin test, 老師給的pdf也是沒辦法用來實作，用wiki的就好(Chap0809-part2, pg26)
3. 在找mod inverse mutiple, 用 extended euler gcd尋找比較簡單, 建議不要用 (a^(phi(n)-1))，要不然50bits開始就很久了
73 15 118 132 127 118 132 127 129 91 95 127 15 124 124 105 123
*/

int main()
{
	do 
	{
		cout << "=========================================" << endl;
		cout << " Enter 'k' for print all the keys." << endl;
		cout << " Enter 'e' for encrypt a plain text." << endl;
		cout << " Enter 'd' for decrypt a cipher text." << endl;
		cout << " Enter other keys to exit." << endl;
		cout << "=========================================" << endl;
		cout << " Enter: ";
		char mode;
		cin >> mode;
		string input = "";
		switch (mode)
		{
		case 'k':
			PrintKeys();
			break;
		case 'e':
			cout << " Enter a plain text: ";
			cin >> input;
			Encrypt(input);
			break;
		case 'd':
			cout << " Enter a cipher text: ";
			getline(cin, input, '\n');
			getline(cin, input, '\n');
			Decrypt(input);
			break;
		default:
			return 0;
			break;
		}
	} while (true);
}