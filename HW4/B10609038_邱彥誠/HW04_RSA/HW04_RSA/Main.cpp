#include"RSA.h"

/*
1. Euler Phi����@��wiki�� euler product formula�����ڡA�ѮvPDF�������ӯ��@�X��(Chap0809-part1, pg22)
2. Miller-rabin test, �Ѯv����pdf�]�O�S��k�Ψӹ�@�A��wiki���N�n(Chap0809-part2, pg26)
3. �b��mod inverse mutiple, �� extended euler gcd�M����²��, ��ĳ���n�� (a^(phi(n)-1))�A�n���M50bits�}�l�N�ܤ[�F
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