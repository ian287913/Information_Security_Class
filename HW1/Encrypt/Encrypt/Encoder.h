#pragma once
#include <iostream>
#include <string>
using namespace std;


static string toUpper(string text)
{
	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] >= 'a' && text[i] <= 'z')
			text[i] = text[i] + 'A' - 'a';
	}
	return text;
}

static string toLower(string text)
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
	string Caesar(string _key, string _plaintext);
	string Playfair(string _key, string _plaintext);
	string Vernam(string _key, string _plaintext);
	string RowTransposition(string _key, string _plaintext);
	string RailFence(string _key, string _plaintext);
};

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
	string key = toLower(_key);
	//	create a matrix
	string matrix = "abcdefghiklmnopqrstuvwxyz";
	//	refine key
	for (int i = 0; i < key.size(); i++)
	{
		if (key[i] == 'j')
			key[i] = 'i';
		for (int j = 0; j < i; j++)
		{
			if (key[i] == key[j])
			{
				key.erase(key.begin() + i);
				i--;
				break;
			}
		}
	}
	//	init matrix
	for (int i = key.size() - 1; i >= 0; i--)
	{
		matrix.erase(matrix.begin() + matrix.find(key[i]));
		matrix.insert(matrix.begin(), key[i]);
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
	string ciphertext = "";
	for (int i = 1; i <= _key.size(); i++)
	{
		//	find the column number of current turn
		for (int c = 0; c < _key.size(); c++)
		{
			
			if (_key[c] == (i + '0'))
			{
				//	write the whole column into ciphertext
				for (int r = 0;; r++)
				{
					int index = _key.size() * r + c;
					if (index >= _plaintext.size())
						break;
					ciphertext += _plaintext[index];
				}
			}
		}
	}

	return toUpper(ciphertext);
}

string Encoder::RailFence(string _key, string _plaintext)
{
	int key = stoi(_key);
	string ciphertext = "";
	string *texts = new string[key];
	for (int i = 0; i < key; i++)
	{
		texts[i] = "";
	}
	//	devide text into N parts
	int level = 0;
	for (int i = 0; i < _plaintext.size(); i++)
	{
		int index = (level >= 0 ? level : (-level));
		texts[index] += _plaintext[i];

		if (level == (key - 1))
			level = -level;
		
		level++;
	}
	//	append texts
	for (int i = 0; i < key; i++)
	{
		ciphertext += texts[i];
	}

	delete [] texts;

	return toUpper(ciphertext);
}
