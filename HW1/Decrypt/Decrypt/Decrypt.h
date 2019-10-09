#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;

void Caesar(string text, int key);

void Playfair(string text, string key);

void Vernam(string text, string key);

void Row(string text, string key);

void RailFence(string text, int key);

vector<int> StringToAlphabet(string);

string AlphabetToString(vector<int>);

static string toUpper(string text);

static string toLower(string text);