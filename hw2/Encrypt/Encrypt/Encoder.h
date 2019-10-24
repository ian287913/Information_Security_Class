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
		63, 55, 47, 39, 31, 23, 15, 7	};
	int IP_inverse[64] = {
		40, 8, 48, 16, 56, 24, 64, 32, 
		39, 7, 47, 15, 55, 23, 63, 31, 
		38, 6, 46, 14, 54, 22, 62, 30, 
		37, 5, 45, 13, 53, 21, 61, 29, 
		36, 4, 44, 12, 52, 20, 60, 28, 
		35, 3, 43, 11, 51, 19, 59, 27, 
		34, 2, 42, 10, 50, 18, 58, 26, 
		33, 1, 41, 9, 49, 17, 57, 25	};
	int E[48] = {
		32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1
	};

	bitset<64> Permutation(bitset<64> arr, int table[]);
	bitset<48> Expansion(bitset<32> arr, int table[]);
	bitset<32> FunctionF(bitset<32> R32, bitset<48> K48);

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
	

	
	bitset<64> bits64 = String2Bits(_key);
	bits64 = Permutation(bits64, IP);
	bitset<32> bits32L;
	bitset<32> bits32R;

	Bits64to32(bits64, bits32L, bits32R);
	/*cout << bits32L.to_string() << endl;
	cout << bits32R.to_string() << endl;
	Swap32(bits32L, bits32R);
	cout << bits32L.to_string() << endl;
	cout << bits32R.to_string() << endl;*/


	///	Transform1( PC-1(Key) )


	///	L0, R0, K1 -> L1, R1		K1 -> K2
	///	L1, R1, K2 -> L2, R2		K2 -> K3
	///	...
	///	L15, R15, K16 -> L16, R16

	///	FinalPermutation(L16, R16)


	return Bits2String(bits64);
}


//	(64 bits)
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

	return result32;
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