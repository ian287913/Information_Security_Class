#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;


string toUpper(string text)
{
	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] >= 'a' && text[i] <= 'z')
			text[i] = text[i] + 'A' - 'a';
	}
	return text;
}

string toLower(string text)
{
	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] >= 'A' && text[i] <= 'Z')
			text[i] = text[i] + 'a' - 'A';
	}
	return text;
}

class Encoder
{
public:
	Encoder();
	~Encoder();

	string Caesar(string _key, string _plaintext);
	string Playfair(string _key, string _plaintext);
	string Vernam(string _key, string _plaintext);
	string RowTransposition(string _key, string _plaintext);
	
};

Encoder::Encoder()
{
}

Encoder::~Encoder()
{
}

//	(Alphabets only)
string Encoder::Caesar(string _key, string _plaintext)
{
	int key = stoi(_key);
	string ciphertext = _plaintext;
	for (int i = 0; i < ciphertext.size(); i++)
	{
		ciphertext[i] = (ciphertext[i] - 'a' + key) % 26 + 'A';
	}
	return ciphertext;
}

//	(Alphabets only)
string Encoder::Playfair(string _key, string _plaintext)
{
	//	create a matrix
	string matrix = "abcdefghiklmnopqrstuvwxyz";
	//	refine key
	for (int i = 0; i < _key.size(); i++)
	{
		if (_key[i] == 'j')
			_key[i] = 'i';
		for (int j = 0; j < i; j++)
		{
			if (_key[i] == _key[j])
			{
				_key.erase(_key.begin() + i);
				i--;
				break;
			}
		}
	}
	//	init matrix
	for (int i = _key.size() - 1; i >= 0; i--)
	{
		matrix.erase(matrix.begin() + matrix.find(_key[i]));
		matrix.insert(matrix.begin(), _key[i]);
	}

	//	deal with plaintext
	for (int i = 1; i < _plaintext.size(); i++)
	{
		if (_plaintext[i] == _plaintext[i - 1])
		{
			_plaintext.insert(_plaintext.begin() + i, 'x');
			i++;
		}
	}
	//	odd handling
	if ((_plaintext.size() % 2) == 1)
	{
		_plaintext.insert(_plaintext.begin() + _plaintext.size(), 'x');
	}

	//	encrypting
	string ciphertext = "";
	for (int i = 0; i < _plaintext.size(); i += 2)
	{
		int firstCharIndex = matrix.find(_plaintext[i]);
		int firstCharCoor[2] = { (firstCharIndex / 5), (firstCharIndex % 5) };
		int secondCharIndex = matrix.find(_plaintext[i + 1]);
		int secondCharCoor[2] = { (secondCharIndex / 5), (secondCharIndex % 5) };

		//	same row
		if (firstCharCoor[0] == secondCharCoor[0])
		{
			ciphertext.insert(ciphertext.begin() + ciphertext.size(), matrix[(firstCharCoor[0] * 5) + ((firstCharCoor[1] + 1) % 5)]);
			ciphertext.insert(ciphertext.begin() + ciphertext.size(), matrix[(secondCharCoor[0] * 5) + ((secondCharCoor[1] + 1) % 5)]);
		}
		//	same column
		else if (firstCharCoor[1] == secondCharCoor[1])
		{
			ciphertext.insert(ciphertext.begin() + ciphertext.size(), matrix[(((firstCharCoor[0] + 1) % 5) * 5) + (firstCharCoor[1])]);
			ciphertext.insert(ciphertext.begin() + ciphertext.size(), matrix[(((secondCharCoor[0] + 1) % 5) * 5) + (secondCharCoor[1])]);
		}
		//	rectangle
		else
		{
			ciphertext.insert(ciphertext.begin() + ciphertext.size(), matrix[(firstCharCoor[0] * 5) + secondCharCoor[1]]);
			ciphertext.insert(ciphertext.begin() + ciphertext.size(), matrix[(secondCharCoor[0] * 5) + firstCharCoor[1]]);
		}
	}

	return toUpper(ciphertext);
}

//	(Alphabets only)
string Encoder::Vernam(string _key, string _plaintext)
{
	string key = toLower(_key + _plaintext);
	string ciphertext = _plaintext;

	for (int i = 0; i < _plaintext.size(); i++)
	{
		ciphertext[i] = ((key[i] - 'a') ^ (_plaintext[i] - 'a')) + 'a';
	}

	return toUpper(ciphertext);
}

string Encoder::RowTransposition(string _key, string _plaintext)
{

}

