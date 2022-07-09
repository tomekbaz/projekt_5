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

     /* otwarcie pliku */

    Plik.open(nazwaPliku.c_str(), ios::in|ios::binary);


    /* weryfikacja poprawnego otwarcia pliku */

    if (! Plik.is_open())
    {
        cout << "--- Nie dalo sie otworzyc pliku!" << endl;
        cout << endl;
        cout << "Nacisnij <ENTER>, aby zakonczyc program... ";
        cin.get();
        return 0;
    }
 /* dane z naglowka pliku */

    cout << "< NAGLOWEK PLIKU >" << endl;

    // poczatek naglowka pliku
    Plik.read( reinterpret_cast<char *>(bufor) , 2 );
    poczNag = string("") +
              static_cast<char>(bufor[0]) + static_cast<char>(bufor[1]);
    cout << "Poczatek naglowka pliku:  " << poczNag << endl;

    // weryfikacja podejrzenia, ze plik moze nie byc plikiem BMP
    if (poczNag != "BM")
    {
        cout << endl;
        cout << "--- Poczatek naglowka pliku inny niz \"BM\"." << endl;
        cout << "    To moze nie byc plik BMP !" << endl;
        do {
            cout << "Czy kontynuowac?  (T/N)  ";
            wybor = cin.get();
            while (cin.get() != '\n')  ;
            switch (wybor) {
                case 't':  wybor = 'T';  break;
                case 'n':  wybor = 'N';  break;
            }
        }while (! (wybor=='T' || wybor=='N'));
        cout << endl;
        if (wybor == 'N')
        {
            Plik.close();   /* zamknij plik */
            cout << "Nacisnij <ENTER>, aby zakonczyc program... ";
            cin.get();
            return 0;
        } // if (wybor == 'N')
    } // if (poczNagl != "BM")

    // rozmiar calego pliku w bajtach
    a = wczytajLiczbe(Plik,4);
    cout << "Rozmiar calego pliku w bajtach:  " << a << endl;

    
    // pole zarezerwowane, na offsecie 0006(h)
    Plik.read( reinterpret_cast<char *>(bufor) , 2 );
    cout << "Pole zarezerwowane, na offsecie 0006(h):  " <<
            static_cast<int>(bufor[0]) << ", " <<
            static_cast<int>(bufor[1]) << endl;

    // pole zarezerwowane, na offsecie 0008(h)
    Plik.read( reinterpret_cast<char *>(bufor) , 2 );
    cout << "Pole zarezerwowane, na offsecie 0008(h):  " <<
            static_cast<int>(bufor[0]) << ", " <<
            static_cast<int>(bufor[1]) << endl;

    // poczatkowy adres bitów w tablicy pikseli
    a = wczytajLiczbe(Plik,4);
    cout << "Poczatkowy adres bitow w tablicy pikseli:  " << a << endl;

    /* koniec danych z nag³ówka pliku */

        /* przerywnik */

    cout << endl;
    cout << "Nacisnij <ENTER>, aby kontynuowac... ";
    while (cin.get() != '\n')  ;
    cout << endl;



    /* dane z naglówka DIB */

    cout << "< NAGLOWEK DIB >" << endl;

    // biSize - wielkoœæ nag³ówka DIB
    a = wczytajLiczbe(Plik,4);
    cout << "biSize (wielkosc naglowka DIB):  " << a << endl;
    cout << "    (typ:  ";
    switch(a)
    {
        case  12:  cout << "BITMAPCOREHEADER OS21XBITMAPHEADER";  break;
        case  64:  cout << "BITMAPCOREHEADER2 OS22XBITMAPHEADER";  break;
        case  40:  cout << "BITMAPINFOHEADER";  break;
        case  52:  cout << "BITMAPV2INFOHEADER";  break;
        case  56:  cout << "BITMAPV3INFOHEADER";  break;
        case 108:  cout << "BITMAPV4HEADER";  break;
        case 124:  cout << "BITMAPV5HEADER";  break;
        default :  cout << "-typ nieznany-";  break;
    }
    cout << ")" << endl;

    if (a == 40)   /* typ naglowka: "BITMAPINFOHEADER" */
    {
        // biWidth - szerokosc obrazu w pikselach
        a = wczytajLiczbe(Plik,4);
        cout << "biWidth  (szerokosc obrazu w pikselach):  " << a << endl;

        // biHeight - wysokoscobrazu w pikselach
        a = wczytajLiczbe(Plik,4);
        cout << "biHeight  (wysokosc obrazu w pikselach):  " << a << endl;

        // biPlanes - liczba warstw kolorów
        a = wczytajLiczbe(Plik,2);
        cout << "biPlanes  (liczba warstw kolorow):  " << a << endl;

        // biBitCount - liczba bitów na piksel
        a = wczytajLiczbe(Plik,2);
        cout << "biBitCount  (liczba bitow na piksel):  " << a << endl;

        // biCompression - algorytm kompresji
        a = wczytajLiczbe(Plik,4);
        cout << "biCompression  (algorytm kompresji):  " << a << endl;

        // biSizeImage - rozmiar samego rysunku
        a = wczytajLiczbe(Plik,4);
        cout << "biSizeImage  (rozmiar samego rysunku):  " << a << endl;

        // biXPelsPerMeter - rozdzielczosc pozioma
        a = wczytajLiczbe(Plik,4);
        cout << "biXPelsPerMeter  (rozdzielczosc pozioma):  " << a << endl;

        // biYPelsPerMeter - rozdzielczosc pionowa
        a = wczytajLiczbe(Plik,4);
        cout << "biYPelsPerMeter  (rozdzielczosc pionowa):  " << a << endl;

        // biClrUsed - liczba kolorów w palecie
        a = wczytajLiczbe(Plik,4);
        cout << "biClrUsed  (liczba kolorow w palecie):  " << a << endl;

        // biClrImportant - liczba waznych kolorów w palecie
        a = wczytajLiczbe(Plik,1);
        cout << "biClrImportant  (liczba waznych kolorow " <<
                "w palecie):  " << a << endl;

        // biClrRotation - flaga rotacji
        a = wczytajLiczbe(Plik,1);
        cout << "biClrRotation  (flaga rotacji):  " << a << endl;

        // biReserved
        Plik.read( reinterpret_cast<char *>(bufor) , 2 );
        cout << "biReserved  (2-bajtowe pole zarezerwowane):  " <<
                static_cast<int>(bufor[0]) << ", " <<
                static_cast<int>(bufor[1]) << endl;
    }

    /* koniec danych z naglówka DIB */



    /* zamkniecie pliku */

    Plik.close();



    cout << endl;
    cout << "Aby zakonczyc program, nacisnij <ENTER>... ";
    cin.get();
    return 0;


