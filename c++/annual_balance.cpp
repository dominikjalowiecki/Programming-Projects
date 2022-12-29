/*
    Program takes income and expense for each calendar month and
    displays statistics.
*/

#include <iostream>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <iomanip>

using namespace std;

void menu();
void wprowadzDaneDoTablicy(float tablica[], int n, string wiadomosc);
void obliczWartosciDochodu(float przychody[], float koszty[], float dochody[], int n);
float obliczSumeWartosciTablicy(float tablica[], int n);
float obliczSredniaKwote(float suma, int liczbaSkladnikow);
void podajSkrajneWartosciIIchIndeksy(float tablica[], int n, float &min_wart, float &max_wart, char &indeks_min_wart, char &indeks_max_wart);

int main()
{
    menu();
    return EXIT_SUCCESS;
}

void menu()
{
    const char LICZBA_MIESIECY = 12;
    const string MIESIACE[LICZBA_MIESIECY] = {"Styczen", "Luty", "Marzec", "Kwiecien", "Maj", "Czerwiec", "Lipiec", "Sierpien", "Wrzesien", "Pazdziernik", "Listopad", "Grudzien"};
    float przychody[LICZBA_MIESIECY];
    float koszty[LICZBA_MIESIECY];
    float dochody[LICZBA_MIESIECY] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    float sumaryczny_przychod = 0, sumaryczne_koszty = 0, sumaryczny_dochod = 0;

    cout << setprecision(2) << fixed;
    cout << "===== Program roczny bilans =====" << endl;

    while(true)
    {
        wprowadzDaneDoTablicy(przychody, LICZBA_MIESIECY, "Wprowadz przychody z kolejnych 12 miesiecy: ");
        wprowadzDaneDoTablicy(koszty, LICZBA_MIESIECY, "Wprowadz koszty z kolejnych 12 miesiecy: ");

        obliczWartosciDochodu(przychody, koszty, dochody, LICZBA_MIESIECY);

        sumaryczny_przychod = obliczSumeWartosciTablicy(przychody, LICZBA_MIESIECY);
        sumaryczne_koszty = obliczSumeWartosciTablicy(koszty, LICZBA_MIESIECY);
        sumaryczny_dochod = obliczSumeWartosciTablicy(dochody, LICZBA_MIESIECY);

        float sr_p = obliczSredniaKwote(sumaryczny_przychod, LICZBA_MIESIECY);
        float sr_k = obliczSredniaKwote(sumaryczne_koszty, LICZBA_MIESIECY);
        float sr_d = obliczSredniaKwote(sumaryczny_dochod, LICZBA_MIESIECY);

        char indeks_p_min, indeks_p_max;
        char indeks_k_min, indeks_k_max;
        char indeks_d_min, indeks_d_max;
        float min_p, max_p;
        float min_k, max_k;
        float min_d, max_d;

        podajSkrajneWartosciIIchIndeksy(przychody, LICZBA_MIESIECY, min_p, max_p, indeks_p_min, indeks_p_max);
        podajSkrajneWartosciIIchIndeksy(koszty, LICZBA_MIESIECY, min_k, max_k, indeks_k_min, indeks_k_max);
        podajSkrajneWartosciIIchIndeksy(dochody, LICZBA_MIESIECY, min_d, max_d, indeks_d_min, indeks_d_max);

        cout << "Sumaryczny przychod wynosi: "<< sumaryczny_przychod << endl;
        cout << "Sumaryczne koszty wynosza: "<< sumaryczne_koszty << endl;
        cout << "Sumaryczny dochod wynosi: "<< sumaryczny_dochod << endl;
        cout << endl;
        cout << "Minimalny przychod wynosi: " << min_p << " i wystapil w: " << MIESIACE[indeks_p_min] << endl;
        cout << "Maksymalny przychod wynosi: " << max_p << " i wystapil w: " << MIESIACE[indeks_p_max] << endl;
        cout << "Sredni przychod wynosi: " << sumaryczny_przychod / LICZBA_MIESIECY << endl;
        cout << endl;
        cout << "Minimalny koszt wynosi: " << min_k << " i wystapil w: " << MIESIACE[indeks_k_min] << endl;
        cout << "Maksymalny koszt wynosi: " << max_k << " i wystapil w: " << MIESIACE[indeks_k_max] << endl;
        cout << "Sredni koszt wynosi: " << sumaryczne_koszty / LICZBA_MIESIECY << endl;
        cout << endl;
        cout << "Minimalny dochod wynosi: " << min_d << " i wystapil w: " << MIESIACE[indeks_d_min] << endl;
        cout << "Maksymalny dochod wynosi: " << max_d << " i wystapil w: " << MIESIACE[indeks_d_max] << endl;
        cout << "Sredni dochod wynosi: " << sumaryczny_dochod / LICZBA_MIESIECY << endl;
        cout << endl;
        cout << "Miesiac | Wartosc przychodu | Wartosc kosztu | Wartosc dochodu | Stan" << endl;
        for(int i = 0; i < LICZBA_MIESIECY; i++)
        {
            printf("%6d. | %-17.2f | %-14.2f | %-15.2f | %s\n", (i + 1), przychody[i], koszty[i], dochody[i], (dochody[i] >= 0) ? ((dochody[i] == 0) ? "zero" : "zysk") : "strata" );
        }


        char opcja;
        cout << endl << "Czy chcesz powtorzyc obliczenia (T/N)?: " << endl;
        do
        {
            cout << "> ";
            cin >> opcja;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } while(opcja != 'T' && opcja != 'N');

        if(opcja == 'N')
            break;
    }

    cout << "Zamykanie programu...";
}

void wprowadzDaneDoTablicy(float tablica[], int n, string wiadomosc)
{
    float wprowadzenie;

    cout << endl << wiadomosc << endl;
    for(int i = 0; i < n; i++)
    {
        while(true)
        {
            cout << (i+1) << ". ";
            cin >> wprowadzenie;
            if(wprowadzenie >= 0 && cin.good())
            {
                tablica[i] = wprowadzenie;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            } else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "BLAD! Wprowadzono niepoprawne dane. Wprowadzana liczba musi byc rzeczywista i nieujemna..." << endl;
            }
        }
    }
}

void obliczWartosciDochodu(float przychody[], float koszty[], float dochody[], int n)
{
     for(int i = 0; i < n; i++)
        dochody[i] = przychody[i] - koszty[i];
}

float obliczSumeWartosciTablicy(float tablica[], int n)
{
    float suma = 0;
    for(int i = 0; i < n; suma += tablica[i++]);
    return suma;
}

float obliczSredniaKwote(float suma, int liczbaSkladnikow)
{
    return (round((suma / liczbaSkladnikow) * 100) / 100);
}

void podajSkrajneWartosciIIchIndeksy(float tablica[], int n, float &min_wart, float &max_wart, char &indeks_min_wart, char &indeks_max_wart)
{
    indeks_min_wart = 0;
    indeks_max_wart = 0;
    min_wart = tablica[0];
    max_wart = tablica[0];

    for(int i = 0; i < n; i++)
    {
        if(tablica[i] < min_wart)
        {
            indeks_min_wart = i;
            min_wart = tablica[i];
        } else if(tablica[i] > max_wart)
        {
            indeks_max_wart = i;
            max_wart = tablica[i];
        }
    }
}
