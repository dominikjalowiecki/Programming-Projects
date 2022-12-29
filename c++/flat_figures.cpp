/*
    Program calculates field of chosen flat figure.
*/

#include <iostream>
#include <limits>
#include <cctype>

using namespace std;

void menu();

void wprowadzWartosc(float & wartosc, char tekst[]);

void czyscBuforWej();

class Kwadrat
{
    public:
        Kwadrat(float a)
        {
            this->a = (a > 0) ? a : 1;
            pole = obliczPole();
        }

        void wyswietlPole();
    private:
        float a, pole;
        float obliczPole();
};

class Prostokat
{
    public:
        Prostokat(float a, float b)
        {
            this->a = (a > 0) ? a : 1;
            this->b = (b > 0) ? b : 1;
            pole = obliczPole();
        }

        void wyswietlPole();
    private:
        float a, b, pole;
        float obliczPole();
};

class Kolo
{
    public:
        Kolo(float r)
        {
            this-> r = (r > 0) ? r : 1;
            pole = obliczPole();
        }

        void wyswietlPole();
    private:
        float r, pole;
        const float PI = 3.1415;
        float obliczPole();
};

class Trojkat
{
    public:
        Trojkat(float a, float h)
        {
            this->a = (a > 0) ? a : 1;
            this->h = (h > 0) ? h : 1;
            pole = obliczPole();
        }

        void wyswietlPole();
    private:
        float a, h, pole;
        float obliczPole();

};

class Trapez
{
    public:
        Trapez(float a, float b, float h)
        {
            this->a = (a > 0) ? a : 1;
            this->b = (b > 0) ? b : 1;
            this->h = (h > 0) ? h : 1;
            pole = obliczPole();
        }

        void wyswietlPole();
    private:
        float a, b, h, pole;
        float obliczPole();
};

enum Figury
{
    kwadrat = '1', prostokat, kolo, trojkat, trapez
};

int main()
{
    menu();

    return 0;
}

float Kwadrat::obliczPole()
{
    return a * a;
}

void Kwadrat::wyswietlPole()
{
    cout << "Wartosc pola kwadratu o podanym boku wynosi: " << pole << endl;
}

float Prostokat::obliczPole()
{
    return a * b;
}

void Prostokat::wyswietlPole()
{
    cout << "Wartosc pola prostokata o podanych bokach wynosi: " << pole << endl;
}

float Kolo::obliczPole()
{
    return PI * r * r;
}

void Kolo::wyswietlPole()
{
    cout << "Wartosc pola kola o podanym promieniu wynosi: " << pole << endl;
}

float Trojkat::obliczPole()
{
    return a * h / 2;
}

void Trojkat::wyswietlPole()
{
    cout << "Wartosc pola trojkata o podanej podstawie i wysokosci wynosi: " << pole << endl;
}

float Trapez::obliczPole()
{
    return (a + b) * h / 2;
}

void Trapez::wyswietlPole()
{
    cout << "Wartosc pola trapezu o podanych podstawach i wysokosci wynosi: " << pole << endl;
}

void menu()
{
    char wybor = 0;

    cout << "=== PROGRAM WYLICZANIE POL FIGUR PLASKICH ===" << endl << endl;

    while(true)
    {
        cout << "Wybierz figure, ktorej pole chcesz wyliczyc:" << endl;
        cout << "1 - Kwadrat" << endl;
        cout << "2 - Prostakat" << endl;
        cout << "3 - Kolo" << endl;
        cout << "4 - Trojkat" << endl;
        cout << "5 - Trapez" << endl;
        cout << "> ";
        wybor = getchar();

        if(cin.fail())
        {
            cout << "BLAD! Wystapil blad podczas podawania opcji..." << endl;
            czyscBuforWej();
            continue;
        }

        czyscBuforWej();

        switch(wybor)
        {
            case kwadrat: {
                float bok = 0, pole = 0;
                wprowadzWartosc(bok, "boku kwadratu");

                Kwadrat * kw = new Kwadrat(bok);
                kw->wyswietlPole();

                delete kw;
                kw = NULL;
            } break;
            case prostokat: {
                float bok1 = 0, bok2 = 0, pole = 0;
                wprowadzWartosc(bok1, "pierwszego boku prostokata");
                wprowadzWartosc(bok2, "drugiego boku prostokata");

                Prostokat * pr = new Prostokat(bok1, bok2);
                pr->wyswietlPole();

                delete pr;
                pr = NULL;
            } break;
            case kolo: {
                float promien = 0, pole = 0;
                wprowadzWartosc(promien, "promienia kola");

                Kolo * ko = new Kolo(promien);
                ko->wyswietlPole();

                delete ko;
                ko = NULL;
            } break;
            case trojkat: {
                float podstawa = 0, wysokosc = 0, pole = 0;
                wprowadzWartosc(podstawa, "podstawy trojkata");
                wprowadzWartosc(wysokosc, "wysokosci trojkata");

                Trojkat * tr = new Trojkat(podstawa, wysokosc);
                tr->wyswietlPole();

                delete tr;
                tr = NULL;
            } break;
            case trapez: {
                float podstawa1 = 0, podstawa2 = 0, wysokosc = 0, pole = 0;
                wprowadzWartosc(podstawa1, "pierwszej podstawy trapezu");
                wprowadzWartosc(podstawa2, "drugiej podstawy trapezu");
                wprowadzWartosc(wysokosc, "wysokosci trapezu");

                Trapez * trap = new Trapez(podstawa1, podstawa2, wysokosc);
                trap->wyswietlPole();

                delete trap;
                trap = NULL;
            } break;
            default:
                cout << "Podano niepoprawna opcje..." << endl;
                continue;
        }

        cout << "Wpisz 'T' jesli chcesz kontynuowac: ";
        wybor = getchar();

        if(!(toupper(wybor) == 'T'))
            break;

        czyscBuforWej();
    }

    cout << endl << "Zamykanie programu..." << endl;
}

void wprowadzWartosc(float & wartosc, char tekst[])
{
    while(true)
    {
        cout << "Podaj wartosc " << tekst << ": ";
        cin >> wartosc;

        if(cin.fail())
        {
            czyscBuforWej();
            cout << "BLAD! Wystapil blad podczas wprowadzania wartosci..." << endl;
            continue;
        } else if(wartosc <= 0)
        {
            czyscBuforWej();
            cout << "BLAD! Wprowadzana wartosc musi byc dodatnia..." << endl;
            continue;
        } else
        {
            czyscBuforWej();
            break;
        }
    }
}

void czyscBuforWej()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
