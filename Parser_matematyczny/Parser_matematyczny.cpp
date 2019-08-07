#include "Parser_matematyczny.h"
using namespace std;


Parser_matematyczny::Parser_matematyczny(string dzialanie)
{
	Parser_matematyczny::dzialanie = dzialanie;//konstruktor
}


Parser_matematyczny::~Parser_matematyczny()
{
}
void Parser_matematyczny::Wpisz_dzialanie(string dzialanie)
{
	Parser_matematyczny::dzialanie = dzialanie;//wpisanie stringa z dzialaniem do pola klasy
}
float Parser_matematyczny::Oblicz_na_podstawie_operatora(string Operator,float a, float b)// na podstawie otrztmanego operatora, funkcja zwroci wynik dzialania
{
	if (Operator == "^")
	{
		return pow(a, b);
	}
	else if (Operator == "*")
	{
		return a*b;
	}
	else if (Operator == "/")
	{
		if (b == 0)cout << "BLAD, dzielenie przez 0"<<endl;
		else
		return a / b;
	}
	else if (Operator == "+")
	{
		return a + b;
	}
	else if (Operator == "-")
	{
		return a - b;
	}
}
float Parser_matematyczny::Oblicz_na_podstawie_funkcji(string funkcja, float argument)//na podstawie nazwy funkcji do obliczenia, funkcja zwroci wynik
{
	if (funkcja=="sin")
	{
		return sin(argument);
	}
	else if (funkcja == "cos")
	{
		return cos(argument);
	}
	else if (funkcja == "log")
	{
		return log10(argument);
	}
	else if (funkcja == "ln")
	{
		return log(argument);
	}
	else cout << "Brak funkcji o nazwie" << funkcja << endl;

}

int Parser_matematyczny::Czy_jest_operatorem(string znak)//sprawdzenie, czy dany znak jest operatorem i od razu zwrocenie jego priorytetu jesli jest
{
	if (znak == "sin"||znak=="cos"||znak=="log"||znak=="ln")
	{
		return 4;
	}
	else if (znak == "^")
	{
		return 3;
	}
	else if (znak == "*" || znak == "/")
	{
		return 2;
	}
	else if (znak == "+" || znak == "-")
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
vector<string>Parser_matematyczny::ONP() // funkcja konwetujaca zapis infiksowy do odwrotnej notacji polskiej
{
	int dlugosc = dzialanie.length();
	vector<string> stos;//stos do przechowywania operatorow, nawiasow, funkcji
	vector<string> kolejka;//wyjscie do obliczen
	string pomoc; // zmienna pomocnicza do operowania wyrazeniem

	for (int i = 0; i < dlugosc; i++)
	{
		
		if ((dzialanie[i] >= '0'&&dzialanie[i] <= '9')|| dzialanie[i] == '.')
		{
			pomoc = dzialanie[i];
			while ((dzialanie[i + 1] >= '0'&&dzialanie[i + 1] <= '9') || dzialanie[i+1] == '.') //dopoki znak jest liczba, to bedzie dopisywany do zmiennej, . dotyczy liczb zmiennoprzecinkowych
			{
				i++;
				pomoc += dzialanie[i];

			}
			kolejka.push_back(pomoc);//wpisanie danej liczby do kolejki
			kolejka.push_back(" ");//dodanie odstepu, w celu odroznienia liczb wielocyfrowych
			pomoc.clear();
		}
		else if (dzialanie[i] >= 'a'&&dzialanie[i] <= 'z') //znajdowanie funkcji matematycznych, np sin, log
		{
			pomoc = dzialanie[i];
			while (dzialanie[i + 1] >= 'a'&&dzialanie[i] <= 'z')
			{
				i++;
				pomoc += dzialanie[i];
			}
			stos.push_back(pomoc);
			pomoc.clear();

		}
		else if (dzialanie[i] == '(')//nawias otwierajacy
		{
			pomoc = dzialanie[i];
			stos.push_back(pomoc);
			pomoc.clear();

		}
		else if (dzialanie[i] == ')')//nawias zmykajacy
		{

			while (stos[stos.size() - 1] != "(")
			{
				kolejka.push_back(stos[stos.size() - 1]);
				stos.pop_back();
			}

			stos.pop_back();
		}
		else if (dzialanie[i] == 32)//wyszukiwanie w spacji w poleceniu i pomijanie 
		{			
			continue;
		}
		else //jesli znak jest operatorem
		{	
			pomoc = dzialanie[i];

			if (stos.size() == 0) // jesli stos jest pusty, to dodaje sie operator 
			{
				stos.push_back(pomoc);
				pomoc.clear();
			}
			else
			{
				while (Czy_jest_operatorem(stos[stos.size() - 1])) // sprawdzanie, czy element na gorze stosu jest operatorem
				{

					if (Czy_jest_operatorem(pomoc) <= Czy_jest_operatorem(stos[stos.size() - 1]) && (Czy_jest_operatorem(pomoc) == 1 || Czy_jest_operatorem(pomoc) == 2))// sprawdzenie priorytetu operatora oraz lacznosci(lewostronna lacznosc);
					{
						kolejka.push_back(stos[stos.size() - 1]);//dodanie do kolejki operatora spelniajacego warunki
						stos.pop_back();
					}
					else if (Czy_jest_operatorem(pomoc) == 3 && Czy_jest_operatorem(pomoc) < Czy_jest_operatorem(stos[stos.size() - 1]))// tak samo jak w poprzednim przypadku, tylko ze sprawdzana jest lacznosc prawostronna
					{
						kolejka.push_back(stos[stos.size() - 1]);
						stos.pop_back();
					}
					break;
				}
				stos.push_back(pomoc);
			}
		}
	}

	while (stos.size() > 0)//dodanie do kolejki wyjscia pozostalych operatorow i funkcji znajdujacych sie na stosie
	{
		kolejka.push_back(stos[stos.size() - 1]);
		stos.pop_back();
	}

	for (int i = 0; i < kolejka.size();i++)//wpisanie wyrazenia w ONP
	{
		cout << kolejka[i];
	}
	cout << endl;
	return kolejka;
}
float Parser_matematyczny::Oblicz(vector<string> Dzialanie)// obliczenie wyrazenie na podstawie ONP
{
	vector<string> stos;
	
	string pomoc;//zmienna pomocnicza do operowania tekstem
	float wynik;
	float liczba1;
	float liczba2;

	for (int i = 0; i < Dzialanie.size(); i++)
	{

		if ((Dzialanie[i] >= "0"&&Dzialanie[i] <= "999999999999") || Dzialanie[i] == ".")// jesli element tego wyrazenia jest liczba to idzie na stos
		{			
			pomoc = Dzialanie[i];
			stos.push_back(pomoc);
			pomoc.clear();			
		}
		else if (Czy_jest_operatorem(Dzialanie[i])!=0 && Czy_jest_operatorem(Dzialanie[i])!=4)// jesli w wyrazeniu pojawil sie operator 
		{

			pomoc = stos[stos.size() - 1];//pobranie liczby ze stosu
			liczba1 = stof(pomoc);//konwersja z typu string na typ float
			stos.pop_back();// usuniecie wierzcholka stosu
			pomoc = stos[stos.size() - 1];
			liczba2 = stof(pomoc);
			stos.pop_back();
			wynik = Oblicz_na_podstawie_operatora(Dzialanie[i], liczba2, liczba1); //wykonanie obliczen na podstawie otrzymanego operatora		
			pomoc = to_string(wynik);			
			stos.push_back(pomoc);//odlozenie na stos wyniku
			pomoc.clear();
			
		}
		else if(Dzialanie[i] >= "a"&&Dzialanie[i] <= "z")// jesli dzialanie jest funkcja
		{
			pomoc = stos[stos.size() - 1];
			liczba1 = stof(pomoc);
			stos.pop_back();
			wynik = Oblicz_na_podstawie_funkcji(Dzialanie[i], liczba1);//wykonanie odpowiedniej funkcji
			pomoc = to_string(wynik);
			stos.push_back(pomoc);
			pomoc.clear();
		}
	}
	pomoc = stos[stos.size() - 1];
	stos.pop_back();
	cout << pomoc << endl;// wypisanie wyniku
	return wynik;
}