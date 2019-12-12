#pragma once
#include<iostream>
#include<string>
#include<sstream>

#define RSA_p 13
#define RSA_q 11
#define RSA_n 143
#define RSA_e 17
#define RSA_d 113

using namespace std;

void PrintKeys();
void Encrypt(string);
void Decrypt(string);

