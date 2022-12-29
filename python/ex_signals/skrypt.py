# 4.1
def podaj_zakodowane_przeslanie(sygnaly):
    przeslanie = ''
    for i in range(40-1, len(sygnaly), 40):
        przeslanie += sygnaly[i][10-1]
    
    return przeslanie

# 4.2
def podaj_slowo_z_najwieksza_liczba_roznych_liter(sygnaly):
    slowo = ''
    liczba_roznych_liter = 0
    najwieksza_liczba_roznych_liter = 0
    for sygnal in sygnaly:
        liczba_roznych_liter = len(set(sygnal))
        if liczba_roznych_liter > najwieksza_liczba_roznych_liter:
            najwieksza_liczba_roznych_liter = liczba_roznych_liter
            slowo = sygnal
    
    return [slowo, najwieksza_liczba_roznych_liter]

# 4.3
def podaj_slowa_ktorych_litery_oddalone_sa_co_najwyzej_o_10(sygnaly):
    slowa = []
    czy_slowo_jest_prawidlowe = True
    for sygnal in sygnaly:
        litery = list(set(sygnal))

        for i in range(len(litery)):
            for j in range(i+1, len(litery)):
                if abs(ord(litery[i])-ord(litery[j])) > 10:
                    czy_slowo_jest_prawidlowe = False

                if not czy_slowo_jest_prawidlowe:
                    break

            if not czy_slowo_jest_prawidlowe:
                break

        if czy_slowo_jest_prawidlowe:
            slowa.append(sygnal)

        czy_slowo_jest_prawidlowe = True
    
    return slowa

        

with open('sygnaly.txt', 'r') as f1, open('wyniki.txt', 'w') as f2:
    sygnaly = []
    for linia in f1:
        sygnaly.append(linia.strip())

    f2.write(f'4.1 {podaj_zakodowane_przeslanie(sygnaly)} \n')
    f2.write(f'4.2 {podaj_slowo_z_najwieksza_liczba_roznych_liter(sygnaly)} \n')
    f2.write(f'4.3 {podaj_slowa_ktorych_litery_oddalone_sa_co_najwyzej_o_10(sygnaly)} \n')