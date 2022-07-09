#include <iostream>
#include <string>
#include <fstream>
using namespace std;

typedef unsigned char uchar;

long wczytajLiczbe(ifstream &plik, int n)

{

    long wynik;
    uchar bajt;
    int i;

    if (n>4)
        return -1;

    wynik = 0;
    for (i=1; i<=n; i++) {
        plik.read( reinterpret_cast<char *>(&bajt), 1 );
        switch (i) {
            case 1:   wynik += bajt;   break;
            case 2:   wynik += (bajt << 8);   break;
            case 3:   wynik += (bajt << 16);   break;
            case 4:   wynik += (bajt << 24);   break;
        }
    }
}

int main()
{
    string nazwaPliku;
    ifstream Plik;
    uchar bufor[4];   
    long a;  
    string poczNag;  
    char wybor;



    cout << "Wszystkie metadane liczbowe podawane sa " <<
            "w systemie dziesietnym." << endl;
    cout << endl << endl;



    /* pobranie nazwy pliku */

    cout << "Podaj nazwe pliku BMP:  ";
    cin >> nazwaPliku;
    while (cin.get() != '\n')  ;
    cout << endl << endl;