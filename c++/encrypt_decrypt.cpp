/*
    Program for encrypting and decrypting file with key of one character.
*/

#include <iostream>
#include <cstdlib>
#include <cstring>

// Maksymalna dlugosc tekstu w buforze przy metodzie zapisu i odczytu blokowego
#define MAKS_DL 1024

using namespace std;

bool glowna_funkcja_programu(int argc, const char * const argv[]);
bool czy_plik_istnieje(const char * const nazwa_pliku);
short odczyt_blokowy_pliku(const char * const nazwa_pliku, char * const bufor);
short zapis_blokowy_pliku(const char * const nazwa_pliku, char * const bufor, short odczytany_rozmiar, char klucz_szyfr);
bool znakowy_zapis_i_odczyt_plikow(const char * const nazwa_pliku_wej, const char * const nazwa_pliku_wyj, char klucz_szyfr);
char szyfrowanie_i_deszyfrowanie_znaku(char znak, char klucz_szyfr);
void szyfrowanie_i_deszyfrowanie_bufora(char * const bufor, short odczytany_rozmiar, char klucz_szyfr);
bool walidacja_argumentow_wejsciowych(int argc, const char * const argv[]);
void zamkniecie_pliku(FILE *& fp);


int main(int argc, char *argv[])
{
    cout << endl << "========== PROGRAM SZYFROWANIE I DESZYFROWANIE PLIKU KLUCZEM JEDNOZNAKOWYM =========" << endl << endl;
    bool status = glowna_funkcja_programu(argc, argv);

    cout << endl << "Nacisnij ENTER, aby kontynuowac...";
    getchar();
    cout << "Zamykanie programu..." << endl;
    if(status)
        return EXIT_SUCCESS;
    else
        return EXIT_FAILURE;
}

bool glowna_funkcja_programu(int argc, const char * const argv[])
{
    if(!walidacja_argumentow_wejsciowych(argc, argv))
        return false;

    const char * const operacja = argv[1];
    const char * const plik_wej = argv[2];
    const char * const plik_wyj = argv[3];
    const char * const klucz_szyfr = argv[4];
    char * bufor = new char[MAKS_DL];

    cout << ((!strcmp(operacja, "s")) ? "Szyfrowanie " : "Deszyfrowanie ") << "zawartosci pliku \"" << plik_wej << "\" do pliku \"" << plik_wyj << "\"" << " kluczem jednoznakowym: \"" <<  klucz_szyfr << "\"..." << endl;
    short rozmiar = odczyt_blokowy_pliku(plik_wej, bufor);

    if(rozmiar < 0)
    {
        return false;
    } else if(rozmiar == MAKS_DL + 1)
    {
        if(znakowy_zapis_i_odczyt_plikow(plik_wej, plik_wyj, klucz_szyfr[0]) < 0)
            return false;
    } else
    {
        if(zapis_blokowy_pliku(plik_wyj, bufor, rozmiar, klucz_szyfr[0]) < 0)
            return false;
    }

    cout << ((!strcmp(operacja, "s")) ? "Szyfrowanie" : "Deszyfrowanie") << " do pliku \"" << plik_wyj << "\" zakonczone sukcesem!" << endl;

    delete [] bufor;
    bufor = NULL;

    return true;
}

bool czy_plik_istnieje(const char * const nazwa_pliku)
{
    return (fopen(nazwa_pliku, "r") != 0);
}

short odczyt_blokowy_pliku(const char * const nazwa_pliku, char * const bufor)
{
    // -1 to blad odczytu, -2 blad otwarcia pliku, a MAKS_DL + 1 to przepelnienie bufora
    short odczytany_rozmiar = -2;
    FILE * fp = NULL;

    if((fp = fopen(nazwa_pliku, "rb")) != NULL)
    {
        odczytany_rozmiar = (short)fread(bufor, sizeof(bufor[0]), MAKS_DL, fp);

        if(feof(fp) == 0)
            odczytany_rozmiar = MAKS_DL + 1;

        if(ferror(fp) != 0)
        {
            cout << "BLAD! Wystapil blad podczas odczytywania pliku wejsciowego..." << endl;
            odczytany_rozmiar = -1;
        }
    } else
    {
        cout << "BLAD! Nie udalo sie otoworzyc podanego pliku wejsciowego..." << endl;
    }

    if(fp != NULL) zamkniecie_pliku(fp);
    return odczytany_rozmiar;
}

short zapis_blokowy_pliku(const char * const nazwa_pliku, char * const bufor, short odczytany_rozmiar, char klucz_szyfr)
{
    // -1 to blad zapisu, -2 blad otwarcia pliku, a 0 to sukces
    char status = -2;
    FILE * fp = NULL;

    szyfrowanie_i_deszyfrowanie_bufora(bufor, odczytany_rozmiar, klucz_szyfr);

    if((fp = fopen(nazwa_pliku, "wb")) != NULL)
    {
        if(fwrite(bufor, sizeof(bufor[0]), odczytany_rozmiar, fp) != odczytany_rozmiar)
        {
            status = -1;
        } else
        {
            if(ferror(fp) != 0)
            {
                cout << "BLAD! Wystapil blad poczas zapisu do pliku wyjsciowego..." << endl;
                status = -1;
            } else
            {
                status = 0;
            }
        }
    } else
    {
        cout << "BLAD! Nie udalo sie otoworzyc podanego pliku wyjsciowego..." << endl;
    }

    if(fp != NULL) zamkniecie_pliku(fp);
    return status;
}

bool znakowy_zapis_i_odczyt_plikow(const char * const nazwa_pliku_wej, const char * const nazwa_pliku_wyj, char klucz_szyfr)
{
    // -1 to blad zapisu, -2 to blad odczytu, -3 to blad otwarcia pliku wyjsciowego, -4 to blad otwarcia pliku wejsciowego, a 0 to sukces
    char status = -4;
    FILE * fp1 = NULL;
    FILE * fp2 = NULL;

    if((fp1 = fopen(nazwa_pliku_wej, "rt")) != NULL)
    {
        if((fp2 = fopen(nazwa_pliku_wyj, "wt")) != NULL)
        {
            char znak = 0;

            while((znak = fgetc(fp1)) != EOF)
            {
                fputc(szyfrowanie_i_deszyfrowanie_znaku(znak, klucz_szyfr), fp2);

                if(ferror(fp2) != 0)
                {
                    cout << "BLAD! Wystapil blad podczas zapisu do pliku wyjsciowego..." << endl;
                    status = -1;
                    break;
                }
            }

            if(ferror(fp1) != 0)
            {
                cout << "BLAD! Wystapil blad podczas odczytu z pliku wejsciowego..." << endl;
                status = -2;
            } else
            {
                status = 0;
            }
        } else
        {
            cout << "BLAD! Nie udalo sie otworzyc podanego pliku wyjsciowego..." << endl;
            status = -3;
        }
    } else
    {
        cout << "BLAD! Nie udalo sie otworzyc podanego pliku wejsciowego..." << endl;
    }

    if(fp1 != NULL) zamkniecie_pliku(fp1);
    if(fp2 != NULL) zamkniecie_pliku(fp2);
    return status;
}

char szyfrowanie_i_deszyfrowanie_znaku(char znak, char klucz_szyfr)
{
    return (znak != klucz_szyfr) ? (char)(znak ^ klucz_szyfr) : 0;
}

void szyfrowanie_i_deszyfrowanie_bufora(char * const bufor, short odczytany_rozmiar, char klucz_szyfr)
{
    char * el = bufor;
    for(short i = 0; i < odczytany_rozmiar; i++)
    {
        *el = szyfrowanie_i_deszyfrowanie_znaku(*el, klucz_szyfr);
        ++el;
    }
}

bool walidacja_argumentow_wejsciowych(int argc, const char * const argv[])
{
    if(argc == 5)
    {
        if(!czy_plik_istnieje(argv[2]))
        {
            cout << "BLAD! Podany plik wejsciowy nie istnieje..." << endl;
            return false;
        }

        if(czy_plik_istnieje(argv[3]))
        {
            cout << "BLAD! Zabezpieczenie przeciw nadpisaniu pliku. Podany plik wyjsciowy istnieje. Podaj nazwe pliku, ktory nie istnieje..." << endl;
            return false;
        }

        if(strlen(argv[4]) == 1)
        {
            if(strcmp(argv[1], "s") == 0 || strcmp(argv[1], "d") == 0)
            {
                return true;
            } else
            {
                cout << "BLAD! Wymagane parametry s - szyfrowanie lub d - deszyfrowanie..." << endl;
                return false;
            }
        } else
        {
            cout << "BLAD! Wymagany jednoznakowy klucz do operacji szyfrowania i deszyfrowania..." << endl;
            return false;
        }
    } else
    {
        cout << "BLAD! Program wymaga podania 4 parametrow (szydeszca.exe <1> <2> <3> <4>):" << endl;
        cout << " 1. s - szyfrowanie lub d - deszyfrowanie" << endl;
        cout << " 2. Nazwa pliku do szyfrowania/deszyfrowania" << endl;
        cout << " 3. Nazwa pliku zaszyfrowanego/odszyfrowanego" << endl;
        cout << " 4. Jednoznakowy klucz do operacji szyfrowania i deszyfrowania" << endl;
        return false;
    }
}

void zamkniecie_pliku(FILE *& fp)
{
    fclose(fp);
    fp = NULL;
}
