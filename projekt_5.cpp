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