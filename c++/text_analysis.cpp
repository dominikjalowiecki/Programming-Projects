/*
    Program analyses entered text and gives stats e.g.
    number of capital and lowercase letters, number of words etc.
*/

#include <cstdlib>
#include <iostream>
using namespace std;
const int MAX_LEN = 128;

/*
  int str_len(char * s)

  Wlasna implementacja funkcji wyznaczajacej dlugosc
  napisu liczona w znakach

  Parametry:
    char * s -- tablica zawierajaca napis, ktorego
    dlugosc jest wyznaczana

  Rezultat:
    Dlugosc napisu liczona w znakach
*/
int str_len(char * s)
{
    int liczba_znakow = 0;

    while(*(s++) != '\0')
      ++liczba_znakow;

    return liczba_znakow;
}

/*
  int lwr_str_cnt(char * s)

  Wyznacza liczbe malych liter w napisie s

  Parametry:
    char s[] -- tablica zawierajaca napis

  Rezultat:
    Liczba malych liter w napisie s
*/
int lwr_str_cnt(char * s)
{
    int liczba_malych_znakow = 0;

    for(;*s != '\0';s++)
    {
      if(*s >= 97 && *s <= 122)
        ++liczba_malych_znakow;
    }

    return liczba_malych_znakow;
}

/*
  int upr_str_cnt(char * s)

  Wyznacza liczbe duzych liter w napisie s

  Parametry:
    char * s -- tablica zawierajaca napis

  Rezultat:
    Liczba duzych liter w napisie s
*/
int upr_str_cnt(char * s)
{
    int liczba_duzych_znakow = 0;

    for(;*s != '\0';s++)
    {
      if(*s >= 65 && *s <= 90)
        ++liczba_duzych_znakow;
    }

    return liczba_duzych_znakow;
}

/*
  int dgt_str_cnt(char * s)

  Wyznacza liczbe cyfr w napisie s

  Parametry:
    char * s -- tablica zawierajaca napis

  Rezultat:
    Liczba cyfr w napisie s
*/
int dgt_str_cnt(char * s)
{
    int liczba_cyfr = 0;

    for(;*s != '\0';s++)
    {
        if(*s >= 48 && *s <= 57)
        ++liczba_cyfr;
    }

    return liczba_cyfr;
}

/*
  int nalpha_str_cnt(const char * s)

  Wyznacza liczbe liter i cyfr w napisie s

  Parametry:
    char * s -- tablica zawierajaca napis

  Rezultat:
    Liczba liter i cyfr w napisie s
*/
int nalpha_str_cnt(char * s)
{
    int liczba_liter_i_cyfr = 0;

    for(;*s != '\0';s++)
    {
      if(
         (*s >= 97 && *s <= 122) ||
         (*s >= 65 && *s <= 90) ||
         (*s >= 48 && *s <= 57)
        )
        ++liczba_liter_i_cyfr;
    }

    return liczba_liter_i_cyfr;
}

/*
  int chr_str_cnt(char c, char * s)

  Wyznacza liczbe wystapien znaku c w s

  Parametry:
    char c   -- znak poszukiwany w napisie
    char * s -- tablica zawierajaca napis

  Rezultat:
    Liczba wystapien znaku c w napisie s
*/
int chr_str_cnt(char c, char * s)
{
    int liczba_wystapien_znaku = 0;

    for(;*s != '\0'; s++)
        if(*s == c)
            ++liczba_wystapien_znaku;

    return liczba_wystapien_znaku;
}

/*
  char * chr_str_pos(char c, char * s)

  Wyznacza wskazanie na pierwsze wystapienie znaku c w s

  Parametry:
    char c   -- znak poszukiwany w napisie
    char * s -- tablica zawierajaca napis

  Rezultat:
    Wskazanie na pierwsze wystapienie znaku c w s lub 0 gdy znak
    nie zostal znaleziony
*/
char * chr_str_pos(char c, char * s)
{
    char * wskazanie_na_znak = 0;

    for(;*s != '\0'; s++)
    {
        if(*s == c)
        {
            wskazanie_na_znak = s;
            break;
        }
    }

    return wskazanie_na_znak;
}

/*
  char * chr_str_rpos(char c, char * s)

  Wyznacza wskazanie na ostatnie wystapienie znaku c w s

  Parametry:
    char c   -- znak poszukiwany w napisie
    char * s -- tablica zawierajaca napis

  Rezultat:
    Wskazanie na ostatnie wystapienie znaku c w s lub NULL gdy znak
    nie zostal znaleziony
*/
char * chr_str_rpos(char c, char * s)
{
    char * wskazanie_na_znak_rpos = NULL;

    for(;*s != '\0'; s++)
    {
      if(*s == c)
      {
          wskazanie_na_znak_rpos = s;
      }
    }

    return wskazanie_na_znak_rpos;
}

/*
  char * str_rev( char * s )

  Odwraca kolejnosc znakow w tablicy s

  Parametry:
    char * s -- tablica zawierajaca napis

  Rezultat:
    Wskazanie na tablice s
*/
char * str_rev(char * s)
{
    char * l = s;
    char * p = s;

    for(;*p != '\0'; p++);
    --p;

    while(p-l > 0)
    {
        *l ^= *p;
        *p ^= *l;
        *l ^= *p;
        ++l;
        --p;
    }

    return s;
}

/*
  int str_word_count(char * s)

  Funkcja wyznacza liczbe slow w tablicy s. Jako slowo
  rozumiemy ciag liter cyfr i znakow podkreslenia. Slowa
  moga być rozdzielane jednym lub wieloma znakami spacji, tabulacji,
  podzialu wiersza.

  Przyklad:
  Napis: "Ala _ma_    kot_ta i    dwa psy"
  Liczba slow: 6

  Parametry:
    char * s -- tablica zawierajaca napis

  Rezultat:
    Liczba slow w napisie s
*/
int str_word_count(char * s)
{
    int liczba_slow = 0;

    if(*s != ' ')
        ++liczba_slow;

    for(;*s != '\0'; ++s)
        if(*(s-1) == ' ' && *s != ' ')
            ++liczba_slow;

    return liczba_slow;
}

int main()
{
  char line[MAX_LEN];
  char c;
  char * pos;

  cout << "\n\nWpisz linie tekstu: ";
  cin.getline(line, MAX_LEN-1);

  cout << "\nLiczba znakow         : " << str_len(line);
  cout << "\nLiczba malych liter   : " << lwr_str_cnt(line);
  cout << "\nLiczba duzych liter   : " << upr_str_cnt(line);
  cout << "\nLiczba cyfr           : " << dgt_str_cnt(line);
  cout << "\nLiczba znakow alfanum : " << nalpha_str_cnt(line);

  cout << "\n\nPodaj pojedynczy znak: ";
  cin >> c;

  cout << "\nLiczba wystapien znaku " << c << ": " << chr_str_cnt(c, line);

  if((pos = chr_str_pos(c, line)) != 0)
    cout << "\nPierwsze wystapienie znaku " << *pos << " na pozycji: " << pos - line;
  else
    cout << "\nZnak " << c << " nie zostal znaleziony";

  if((pos = chr_str_rpos(c, line)) != 0)
    cout << "\nOstatnie wystapienie znaku " << *pos  << " na pozycji: " << pos - line;
  else
    cout << "\nZnak " << c << " nie zostal znaleziony";

  cout << "\n\nNapis oryginalny : " << line;
  cout << "\nNapis odwrocony  : " << str_rev(line);
  cout << "\nLiczba slow w napisie: " << str_word_count(line);
  cin.ignore();
  cin.get();
  return EXIT_SUCCESS;
}
