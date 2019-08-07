#include"Parser_matematyczny.h"
using namespace std;
int main()
{
	string polecenie;
	Parser_matematyczny dzialanie;
	while (getline(cin,polecenie))//zapisanie tekstu z konsoli do zminnej
	{
		dzialanie.Wpisz_dzialanie(polecenie);
		dzialanie.Oblicz(dzialanie.ONP());
	}
}