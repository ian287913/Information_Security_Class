#include"Decrypt.h"

void Caesar(string text, int key)
{
	string output = "";
	vector<int> AlphaText = StringToAlphabet(text);
	for (int i = 0; i < AlphaText.size(); i++)
	{
		AlphaText[i] -= key;
		AlphaText[i] %= 26;
		if (AlphaText[i] < 0)
			AlphaText[i] += 26;
	}
	output = AlphabetToString(AlphaText);
	output = toLower(output);
	cout << output;
}


void Playfair(string text, string key)
{
	int table[5][5];
	bool added[26];
	for (int i = 0; i < 26; i++)
	{
		added[i] = false;
	}
	added[9] = true;

	int keyIndex = 0;
	int alphaIndex = 0;
	bool keyUsedUp = false;
	vector<int> alphaKey = StringToAlphabet(key);
	vector<int> alphaText = StringToAlphabet(text);
	for (int i = 0; i < alphaKey.size(); i++)
	{
		if (alphaKey[i] == 9)
			alphaKey[i] = 8;
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (!keyUsedUp)
			{
				while (added[alphaKey[keyIndex]])
				{
					keyIndex++;
					if (keyIndex >= alphaKey.size())
					{
						keyUsedUp = true;
						break;
					}
				}

				if (keyIndex < alphaKey.size())
				{
					table[i][j] = alphaKey[keyIndex];
					added[alphaKey[keyIndex]] = true;
				}
				else
				{
					keyUsedUp = true;
					for (int k = 0; k < 26; k++)
					{
						if (!added[k])
						{
							table[i][j] = k;
							alphaIndex = k;
							added[k] = true;
							break;
						}
					}
				}
			}
			else
			{
				while (added[alphaIndex])
				{
					alphaIndex++;
					if (alphaIndex > 25)
					{
						alphaIndex = 0;
						break;
					}
				}
				table[i][j] = alphaIndex;
				added[alphaIndex] = true;
				alphaIndex++;
			}
		}
		/*for (int j = 0; j < 5; j++)
		{
			cout << table[i][j] << " ";
		}
		cout << endl;*/
	}
	
	vector<int> plainText = vector<int>();
	for (int pair = 0; pair < alphaText.size() - 1; pair += 2)
	{
		int firstRow, secondRow, firstCol, secondCol;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (table[i][j] == alphaText[pair])
				{
					firstRow = i;
					firstCol = j;
				}
				else if (table[i][j] == alphaText[pair + 1])
				{
					secondRow = i;
					secondCol = j;
				}
			}
		}
		if (firstRow == secondRow)
		{
			int fcol = firstCol - 1, scol = secondCol - 1;
			if (fcol < 0)
				fcol = 4;
			if (scol < 0)
				scol = 4;
			plainText.push_back(table[firstRow][fcol]);
			plainText.push_back(table[secondRow][scol]);
		}
		else if (firstCol == secondCol)
		{
			int frow = firstRow - 1, srow = secondRow - 1;
			if (frow < 0)
				frow = 4;
			if (srow < 0)
				srow = 4;
			plainText.push_back(table[frow][firstCol]);
			plainText.push_back(table[srow][secondCol]);
		}
		else
		{
			plainText.push_back(table[firstRow][secondCol]);
			plainText.push_back(table[secondRow][firstCol]);
		}
	}

	string output = toLower(AlphabetToString(plainText));
	cout << output;
}

void Vernam(string text, string key)
{
	if (text.length() != key.length())
	{
		cout << "Wrong Key!";
		return;
	}
	string output = "";
	for (int i = 0; i < text.length(); i++)
	{
		output += ((text[i] - 65) ^ (key[i] - 65)) + 65;
	}
	output = toLower(output);
	cout << output;
}

void Row(string text, string key)
{
	vector<vector<char>> plainTable = vector<vector<char>>();
	int rowLen = key.length();
	int addRow = text.length() % rowLen;
	int colLen = text.length() / rowLen;
	vector<int> inverse = vector<int>();
	for (int i = 0; i < rowLen; i++)
	{
		for (int j = 0; j < rowLen; j++)
		{
			if (i == (key[j] - 49))
			{
				inverse.push_back(j);
				break;
			}
		}
	}

	for (int i = 0; i < colLen; i++)
	{
		vector<char> temp = vector<char>();
		for (int j = 0; j < rowLen; j++)
			temp.push_back('*');
		plainTable.push_back(temp);
	}
	if (addRow != 0)
	{
		vector<char> temp = vector<char>();
		for (int j = 0; j < addRow; j++)
			temp.push_back('*');
	}
	for (int c = 0; c < rowLen; c++)
	{
		int maxLen = colLen;
		if (c < addRow)
			maxLen++;

		// find the column
		int order = key[c] - 49;
		int startIndex = 0;
		for (int i = 0; i < order; i++)
		{
			startIndex += colLen;
			if (inverse[i] < addRow)
				startIndex++;
		}

		for (int r = 0; r < maxLen; r++)
		{
			// build that column
			plainTable[r][c] = text[startIndex];
			startIndex++;
		}
	}

	string output = "";
	for (int i = 0; i < plainTable.size(); i++)
	{
		for (int j = 0; j < plainTable[i].size(); j++)
		{
			output += plainTable[i][j];
		}
	}
	cout << toLower(output);

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
		if (i >= 0)
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