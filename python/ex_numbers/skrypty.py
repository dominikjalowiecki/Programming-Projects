# 4.1
def czy_potega_liczby_trzy(n):
    potega = 1
    while potega <= n:
        if potega == n:
            return True

        potega *= 3
    
    return False

def policz_potegi_liczby_trzy(liczby):
    licznik = 0
    for liczba in liczby:
        if czy_potega_liczby_trzy(liczba):
            licznik += 1
    
    return licznik

# 4.2
def oblicz_silnie_liczby(n):
    silnia = 1
    for i in range(1, n+1):
        silnia *= i
    
    return silnia

def oblicz_sume_silni_cyfr_liczby(liczba):
    suma_silni = 0
    liczba = str(liczba)
    for cyfra in liczba:
        suma_silni += oblicz_silnie_liczby(int(cyfra))
    
    return suma_silni

def podaj_liczby_rowne_sumie_silni_cyfr(liczby):
    tablica = []
    for liczba in liczby:
        if liczba == oblicz_sume_silni_cyfr_liczby(liczba):
            tablica.append(liczba)
        
    return tablica

# 4.3
def oblicz_najwiekszy_wspolny_dzielnik(a, b):
    while a != b:
        if a > b:
            a -= b
        else:
            b -= a
    
    return a

def podaj_ciag_w_ktorym_nwd_jest_wieksze_od_jeden(liczby):
    pierwsza_liczba_ciagu = -1
    dlugosc_ciagu = 1
    najwiekszy_wspolny_dzielnik_ciagu = 0
    wynik = [pierwsza_liczba_ciagu, dlugosc_ciagu, najwiekszy_wspolny_dzielnik_ciagu]

    idx = 0
    while idx < len(liczby):
        if dlugosc_ciagu == 1:
            nwdc = oblicz_najwiekszy_wspolny_dzielnik(liczby[idx-1], liczby[idx])
        else:
            nwdc = oblicz_najwiekszy_wspolny_dzielnik(najwiekszy_wspolny_dzielnik_ciagu, liczby[idx])
            
        if nwdc > 1:
            if pierwsza_liczba_ciagu == -1:
                pierwsza_liczba_ciagu = liczby[idx-1]
            najwiekszy_wspolny_dzielnik_ciagu = nwdc
            
            dlugosc_ciagu += 1
            idx += 1
        else:
            if dlugosc_ciagu > wynik[1]:
                wynik = [pierwsza_liczba_ciagu, dlugosc_ciagu, najwiekszy_wspolny_dzielnik_ciagu]
            if not oblicz_najwiekszy_wspolny_dzielnik(liczby[idx-1], liczby[idx]) > 1:
                idx += 1
            pierwsza_liczba_ciagu = -1
            dlugosc_ciagu = 1
            najwiekszy_wspolny_dzielnik_ciagu = 0

    if dlugosc_ciagu > wynik[1]:
        wynik = [pierwsza_liczba_ciagu, dlugosc_ciagu, najwiekszy_wspolny_dzielnik_ciagu]

    return wynik



with open('liczby.txt', 'r') as f1, open('wyniki4.txt', 'w') as f2:
    liczby = []
    for line in f1:
        liczba = int(line.strip())
        liczby.append(liczba)
    
    f2.write(f'4.1 {policz_potegi_liczby_trzy(liczby)}\n')
    f2.write(f'4.2 {podaj_liczby_rowne_sumie_silni_cyfr(liczby)}\n')
    f2.write(f'4.3 {podaj_ciag_w_ktorym_nwd_jest_wieksze_od_jeden(liczby)}\n')
    