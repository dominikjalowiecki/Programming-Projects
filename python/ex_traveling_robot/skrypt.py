# "Podróżujący robot"

# 4.1
def wykonaj_ruch(ruch, pozycja):
    if ruch == 'N':
        pozycja[0] -= 1
    if ruch == 'E':
        pozycja[1] += 1
    if ruch == 'S':
        pozycja[0] += 1
    if ruch == 'W':
        pozycja[1] -= 1

def policz_graczy_zdyskfalifikowanych(ruchy, plansza):
    pozycja = [0, 0]
    licznik = 0

    for ruchy_gracza in ruchy:
        pozycja = [0, 0]
        for ruch in ruchy_gracza:
            wykonaj_ruch(ruch, pozycja)
            if (pozycja[0] < 0 or pozycja[0] > 19) or (pozycja[1] < 0 or pozycja[1] > 19):
                licznik += 1
                break
    
    return licznik

# 4.2
def podaj_gracza_z_najwieksza_liczba_punktow(ruchy, plansza):
    pozycja = [0, 0]
    numer_gracza = 0
    najwieksza_liczba_punktow = 0
    liczba_punktow = 0

    for indeks_gracza in range(len(ruchy)):
        pozycja = [0, 0]
        liczba_punktow = plansza[0][0]

        for ruch in ruchy[indeks_gracza]:
            wykonaj_ruch(ruch, pozycja)
            if (pozycja[0] < 0 or pozycja[0] > 19) or (pozycja[1] < 0 or pozycja[1] > 19):
                liczba_punktow = -1
                break
            liczba_punktow += plansza[pozycja[0]][pozycja[1]]
        
        if liczba_punktow > najwieksza_liczba_punktow:
            numer_gracza = indeks_gracza+1
            najwieksza_liczba_punktow = liczba_punktow
    
    return [numer_gracza, najwieksza_liczba_punktow]

# 4.3
def podaj_graczy_ktorzy_wykonali_najwieksza_liczbe_nastepujacych_po_sobie_ruchow(ruchy, plansza):
    liczba_ruchow = 0
    najwieksza_liczba_ruchow = 0
    gracze = []
    gracze_z_najwieksza_liczba_punktow = []

    for indeks_gracza in range(len(ruchy)):
        liczba_ruchow = 0
        najwieksza_liczba_ruchow = 0
        for ruch in ruchy[indeks_gracza]:
            if ruch == 'W' or ruch == 'E':
                liczba_ruchow += 1
            else:
                if liczba_ruchow > najwieksza_liczba_ruchow:
                    najwieksza_liczba_ruchow = liczba_ruchow
                liczba_ruchow = 0

        gracze.append([indeks_gracza+1, najwieksza_liczba_ruchow])
    
    gracze = sorted(gracze, key=lambda gracz: gracz[1], reverse=True)
    for indeks_gracza in range(len(gracze)-1):
        gracze_z_najwieksza_liczba_punktow.append(gracze[indeks_gracza])
        if gracze[indeks_gracza+1][1] != gracze[indeks_gracza][1]:
            break
    
    return gracze_z_najwieksza_liczba_punktow

with open('robot.txt', 'r') as f1, open('plansza.txt', 'r') as f2, open('zadanie4.txt', 'w') as f3:
    ruchy = []
    plansza = []

    for linia in f1:
        ruchy.append(linia.strip())

    for linia in f2:
        tablica = linia.split()
        for indeks in range(len(tablica)):
            tablica[indeks] = int(tablica[indeks])
        plansza.append(tablica)
    
    f3.write(f'4.1 {policz_graczy_zdyskfalifikowanych(ruchy, plansza)}\n')
    f3.write(f'4.2 {podaj_gracza_z_najwieksza_liczba_punktow(ruchy, plansza)}\n')
    f3.write(f'4.3 {podaj_graczy_ktorzy_wykonali_najwieksza_liczbe_nastepujacych_po_sobie_ruchow(ruchy, plansza)}\n')