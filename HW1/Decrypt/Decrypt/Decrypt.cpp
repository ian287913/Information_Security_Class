#include"Decrypt.h"

void Caesar(string text, int key)
{
	cout << "Caesar:" << endl;
	cout << "input: " << text << endl;
	string output = "";
	vector<int> AlphaText = StringToAlphabet(text);
	for (int i = 0; i < AlphaText.size(); i++)
	{
		AlphaText[i] -= key;
		AlphaText[i] %= 26;
	}
	output = AlphabetToString(AlphaText);
	cout << output;
}


void Playfair(string text, string key)
{
}

void Vernam(string text, string key)
{
}

void Row(string text, string key)
{
}

void RailFence(string text, int key)
{
}

vector<int> StringToAlphabet(string input)
{
	vector<int> output = vector<int>();

	for(char c : input)
	{
		if (c >= 65 && c <= 90)
		{
			output.push_back(c - 65);
		}
		else
		{
			output.push_back(-c);
		}
	}

	return output;
}

string AlphabetToString(vector<int> input)
{
	string output = "";

	for (int i : input)
	{
		char push;
		if (i > 0)
		{
			push = (char)(i + 65);
		}
		else
		{
			push = (char)(-i);
		}
		output += push;
	}

	return output;
}