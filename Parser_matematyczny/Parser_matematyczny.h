#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<math.h>
using namespace std;

class Parser_matematyczny
{
	string dzialanie;	
public:
	int ilosc_operatorow;
	int ilosc_funkcji;
	void Wpisz_dzialanie(string dzialanie);
	vector<string> ONP();
	int Czy_jest_operatorem(string znak);
	float Oblicz(vector<string> Dzialanie);
	float Oblicz_na_podstawie_operatora(string Operator,float a, float b);
	float Oblicz_na_podstawie_funkcji(string funkcja, float argument);
	Parser_matematyczny(string dzialanie = "");
	~Parser_matematyczny();
};

