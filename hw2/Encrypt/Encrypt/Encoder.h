#pragma once
#include <iostream>
#include <string>
#include <bitset>
#include <sstream>
using namespace std;

//	Alphabet-Case Transformation
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
	string DES(string _key, string _plaintext);
	int IP[64] = {
		58, 50, 42, 34, 26, 18, 10, 2,
		60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14,	6,
		64, 56, 48, 40, 32, 24, 16,	8,
		57, 49, 41, 33, 25, 17, 9,	1,
		59, 51, 43, 35, 27, 19, 11,	3,
		61, 53, 45, 37, 29, 21, 13,	5,
		63, 55, 47, 39, 31, 23, 15, 7 };
	int IP_inverse[64] = {
		40, 8, 48, 16, 56, 24, 64, 32,
		39, 7, 47, 15, 55, 23, 63, 31,
		38, 6, 46, 14, 54, 22, 62, 30,
		37, 5, 45, 13, 53, 21, 61, 29,
		36, 4, 44, 12, 52, 20, 60, 28,
		35, 3, 43, 11, 51, 19, 59, 27,
		34, 2, 42, 10, 50, 18, 58, 26,
		33, 1, 41, 9, 49, 17, 57, 25 };
	int FP[32] = { 16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25 };
	int PC_1[56] = { 57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4 };
	int PC_2[48] = { 14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32 };
	int E[48] = {
		32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1
	};
	unsigned long S[8][64] = {
		{
			14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
			0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
			4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
			15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13
		},

		{
			15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
			3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
			0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
			13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9
		},

		{
			10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
			13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
			13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
			1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12
		},

		{
			7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
			13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
			10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
			3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14
		},

		{
			2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
			14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
			4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
			11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3
		},

		{
			12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
			10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
			9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
			4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
		},

		{
			4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
			13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
			1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
			6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12
		},

		{
			13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
			1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
			7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
			2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
		}
	};


	bitset<64> Permutation(bitset<64> arr, int table[]);
	bitset<32> Permutation32(bitset<32> arr, int table[]);
	bitset<56> Permutation56(bitset<64> arr);	//	PC_1
	bitset<48> Permutation48(bitset<56> arr);	//	PC_2
	bitset<48> Expansion(bitset<32> arr, int table[]);
	bitset<32> FunctionF(bitset<32> R32, bitset<48> K48);
	bitset<32> SBox(bitset<48> bs);
	bitset<56> KeyRound(bitset<56> bs, int round);


	static bitset<64> String2Bits(string s);
	string Bits2String(bitset<64> bs);
	void Bits64to32(bitset<64> bs64, bitset<32>& bsL, bitset<32>& bsR);
	void Swap32(bitset<32>& bsL, bitset<32>& bsR);

};


///
//	Key generation
//	XOR
//	Permutation (bits, matrix)
///
string Encoder::DES(string _key, string _plaintext)
{

	///	<L0, R0> Split( InitialPermutation(Plaintext) )
	bitset<64> bits64 = String2Bits(_plaintext);
	cout << "_P: " << bits64.to_string() << endl;
	bits64 = Permutation(bits64, IP);
	bitset<32> bits32L;
	bitset<32> bits32R;

	Bits64to32(bits64, bits32L, bits32R);

	///	Transform1( PC-1(Key) )
	cout << "_K: " << String2Bits(_key).to_string() << endl;

	bitset<56> key56 = Permutation56(String2Bits(_key));
	cout << "KEY: " << key56.to_string() << endl;


	for (int i = 1; i <= 16; i++)
	{
		key56 = KeyRound(key56, i);

		bits32L = (bits32L ^ FunctionF(bits32R, Permutation48(key56)));

		Swap32(bits32L, bits32R);
	}
	Swap32(bits32L, bits32R);

	///cout << "KEY: " << key56.to_string() << endl;

	string s64 = bits32L.to_string() + bits32R.to_string();
	cout << s64 << endl;
	bits64 = bitset<64>(s64);

	bits64 = Permutation(bits64, IP_inverse);

	///	L0, R0, K1 -> L1, R1		K1 -> K2
	///	L1, R1, K2 -> L2, R2		K2 -> K3
	///	...
	///	L15, R15, K16 -> L16, R16

	///	FinalPermutation(L16, R16)


	return Bits2String(bits64);
}


bitset<64> Encoder::Permutation(bitset<64> arr, int table[])
{
	bitset<64> arr_new;

	//	fill the content by match table
	for (int i = 0; i < 64; i++)
	{
		arr_new[i] = arr[(table[i] - 1)];
	}

	return arr_new;
}
bitset<32> Encoder::Permutation32(bitset<32> arr, int table[])
{
	bitset<32> arr_new;

	//	fill the content by match table
	for (int i = 0; i < 32; i++)
	{
		arr_new[i] = arr[(table[i] - 1)];
	}

	return arr_new;
}
bitset<56> Encoder::Permutation56(bitset<64> arr)
{
	bitset<56> arr_new;

	//	fill the content by match table
	for (int i = 0; i < 56; i++)
	{
		arr_new[i] = arr[(PC_1[i] - 1)];
	}

	return arr_new;
}
bitset<48> Encoder::Permutation48(bitset<56> arr)
{
	bitset<48> arr_new;

	//	fill the content by match table
	for (int i = 0; i < 48; i++)
	{
		arr_new[i] = arr[(PC_2[i] - 1)];
	}

	return arr_new;
}
bitset<48> Encoder::Expansion(bitset<32> arr, int table[])
{
	bitset<48> arr_new;

	//	fill the content by match table
	for (int i = 0; i < 48; i++)
	{
		arr_new[i] = arr[(table[i] - 1)];
	}

	return arr_new;
}

bitset<32> Encoder::FunctionF(bitset<32> R32, bitset<48> K48)
{
	bitset<32> result32;

	bitset<48> xor48 = Expansion(R32, E) ^ K48;

	result32 = SBox(xor48);

	result32 = Permutation32(result32, FP);

	return result32;
}

bitset<32> Encoder::SBox(bitset<48> bs48)
{
	string result32 = "";

	for (int i = 0; i < 8; i++)
	{
		int index = 0;
		index += bs48[(i * 6) + 0] * 16;
		index += bs48[(i * 6) + 1] * 1;
		index += bs48[(i * 6) + 2] * 2;
		index += bs48[(i * 6) + 3] * 4;
		index += bs48[(i * 6) + 4] * 8;
		index += bs48[(i * 6) + 5] * 32;

		bitset<4> map4(S[i][index]);

		//	add 4bits to result
		result32 += map4.to_string();
	}

	return bitset<32>(result32);
}

bitset<56> Encoder::KeyRound(bitset<56> bs, int round)
{
	//	split 56 into 28,28 (C is MSB)
	string s56 = bs.to_string();
	string sC28 = "";
	sC28.insert(sC28.begin(), s56.begin() + 0, s56.begin() + 28);
	string sD28 = "";
	sD28.insert(sD28.begin(), s56.begin() + 28, s56.begin() + 56);
	bitset<28> C28(sC28);
	bitset<28> D28(sD28);
	//	rotate
	if (round == 1 || round == 2 || round == 9 || round == 16)
	{
		//	shift left 1
		bitset<28> bs28(C28);
		C28 = C28 << 1;
		bs28 = bs28 >> (28 - 1);
		C28 = C28 | bs28;

		bs28 = D28;
		D28 = D28 << 1;
		bs28 = bs28 >> (28 - 1);
		D28 = D28 | bs28;
	}
	else
	{
		//	shift left 2
		bitset<28> bs28(C28);
		C28 = C28 << 2;
		bs28 = bs28 >> (28 - 2);
		C28 = C28 | bs28;

		bs28 = D28;
		D28 = D28 << 2;
		bs28 = bs28 >> (28 - 2);
		D28 = D28 | bs28;
	}

	return bitset<56>(C28.to_string() + D28.to_string());
}



void Encoder::Bits64to32(bitset<64> bs64, bitset<32> &bsL, bitset<32> &bsR)
{
	//	注意: R在低位元、L在高位元
	for (int i = 0; i < 64; i++)
	{
		if (i < 32)
			bsR[i] = bs64[i];
		else
			bsL[i - 32] = bs64[i];
	}
}

void Encoder::Swap32(bitset<32>& bsL, bitset<32>& bsR)
{
	bitset<32> bsTemp = bsL;
	bsL = bsR;
	bsR = bsTemp;
}


//	(64 bits)
bitset<64> Encoder::String2Bits(string s)
{
	string sL = "";
	sL.insert(sL.begin(), s.begin() + 2, s.begin() + 10);
	///cout << sL << endl;
	string sR = "";
	sR.insert(sR.begin(), s.begin() + 10, s.begin() + 18);
	///cout << sR << endl;

	stringstream ssL;
	ssL << hex << sL;
	unsigned nL;
	ssL >> nL;
	bitset<64> bsL(nL);
	///cout << bsL.to_string() << endl;

	stringstream ssR;
	ssR << hex << sR;
	unsigned nR;
	ssR >> nR;
	bitset<64> bsR(nR);
	///cout << bsR.to_string() << endl;
	bitset<64> bs;

	bsL = bsL << 32;
	bsL = bsL | bsR;

	///cout << bsL << endl;
	return bsL;
}
string Encoder::Bits2String(bitset<64> bs)
{
	stringstream ss;
	ss << "0x" << hex << uppercase << bs.to_ullong() << endl;
	return ss.str();
}