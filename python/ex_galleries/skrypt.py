# 4.1
def podaj_liczbe_miast_w_ktorych_powstana_galerie_dla_danego_kraju(galerie):
    wyniki = {}
    for galeria in galerie:
        wyniki[galeria[0]] = 0
    for galeria in galerie:
        wyniki[galeria[0]] += 1

    return wyniki

# 4.2
def podaj_powierzchnie_handlowa_oraz_liczbe_lokali_w_galerii(galerie):
    wyniki = []
    liczby = []
    liczba_lokali = 0
    powierzchnia_lokalu = 0
    powierzchnia_handlowa = 0
    for galeria in galerie:
        liczby = galeria[2:]
        for i in range(0, len(liczby), 2):
            if(liczby[i] == '0'):
                break
            powierzchnia_lokalu = int(liczby[i]) * int(liczby[i+1])
            liczba_lokali += 1
            powierzchnia_handlowa += powierzchnia_lokalu

        wyniki.append([galeria[1], powierzchnia_handlowa, liczba_lokali])
        
        liczba_lokali = 0
        powierzchnia_handlowa = 0
        liczby = []    

    wyniki = sorted(wyniki, key=lambda k: k[1])

    return wyniki

# 4.3
def podaj_galerie_z_najmniejsza_i_najwieksza_iloscia_roznych_lokali(galerie):
    wyniki = []
    powierzchnie_lokali = []
    powierzchnia_lokalu = 0
    for galeria in galerie:
        liczby = galeria[2:]
        for i in range(0, len(liczby), 2):
            if(liczby[i] == '0'):
                break
            powierzchnia_lokalu = int(liczby[i]) * int(liczby[i+1])
            powierzchnie_lokali.append(powierzchnia_lokalu)
        
        wyniki.append([galeria[1], len(set(powierzchnie_lokali))])
        powierzchnie_lokali = []
    
    wyniki = sorted(wyniki, key=lambda k: k[1])

    return wyniki


with open('galerie.txt', 'r') as plik1:
    galerie = []
    for linia in plik1:
        linia = linia.strip()
        galerie.append(linia.split(' '))

    print(podaj_liczbe_miast_w_ktorych_powstana_galerie_dla_danego_kraju(galerie))

    wyniki = podaj_powierzchnie_handlowa_oraz_liczbe_lokali_w_galerii(galerie)
    print(wyniki[len(wyniki)-1], wyniki[0])

    wyniki = podaj_galerie_z_najmniejsza_i_najwieksza_iloscia_roznych_lokali(galerie)
    print(wyniki[len(wyniki)-1], wyniki[0])