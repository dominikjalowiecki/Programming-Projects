# 6.1
def znajdzNajciemniejszyINajjasniejszyPiksel(piksele):
    najciemniejszyPiksel = piksele[0][0]
    najjasniejszyPiksel = piksele[0][0]
    for i in piksele:
        for j in i:
            if j > najjasniejszyPiksel:
                najjasniejszyPiksel = j
            elif j < najciemniejszyPiksel:
                najciemniejszyPiksel = j
    
    return {
        'najciemniejszyPiksel': najciemniejszyPiksel,
        'najjasniejszyPiksel': najjasniejszyPiksel
    }

# 6.2
def czyWierszMaZachowanaOsSymetrii(wiersz):
    for idx in range(0,len(wiersz)//2):
        if(wiersz[idx] != wiersz[(len(wiersz)-1)-idx]):
            return False

    return True

def ileWierzowUsunacZebyZachowacPionowaOsSymetrii(piksele):
    licznik = 0
    for wiersz in piksele:
        if not czyWierszMaZachowanaOsSymetrii(wiersz):
            licznik += 1
    
    return licznik

# 6.3
def czyPikselJestKontrastujacy(piksele, idxK, idxW, kMax, wMax):
    if idxK > 0:
        if abs(piksele[idxK][idxW] - piksele[idxK-1][idxW]) > 128:
            return True
    if idxW > 0:
        if abs(piksele[idxK][idxW] - piksele[idxK][idxW-1]) > 128:
            return True
    if idxK < kMax:
        if abs(piksele[idxK][idxW] - piksele[idxK+1][idxW]) > 128:
            return True
    if idxW < wMax:
        if abs(piksele[idxK][idxW] - piksele[idxK][idxW+1]) > 128:
            return True

def ileJestKontrastujacychPikselow(piksele):
    licznik = 0
    for idxK in range(0, len(piksele)):
        for idxW in range(0, len(piksele[idxK])):
            if czyPikselJestKontrastujacy(piksele, idxK, idxW, len(piksele)-1, len(piksele[idxK])-1):
                licznik += 1
    
    return licznik

# 6.4
def ileWynosiNajdluzszaLiniaPionowa(piksele):
    dlugoscKolumny = len(piksele)
    dlugoscWiersza = len(piksele[0])
    licznikMax = 0
    licznik = 0
    for i in range(0, dlugoscWiersza):
        for j in range(0, dlugoscKolumny-1):
            if piksele[j][i] == piksele[j+1][i]:
                licznik += 1
            else:
                if licznik > licznikMax:
                    licznikMax = licznik + 1
                licznik = 0
        if licznik > licznikMax:
            licznikMax = licznik + 1
        licznik = 0
    
    return licznikMax


with open('dane.txt', 'r') as f:
    piksele = []
    for linia in f:
        linia = linia.rstrip()
        piksele.append([int(i) for i in linia.split(' ')])
    
    print(znajdzNajciemniejszyINajjasniejszyPiksel(piksele))
    print(ileWierzowUsunacZebyZachowacPionowaOsSymetrii(piksele))
    print(ileJestKontrastujacychPikselow(piksele))
    print(ileWynosiNajdluzszaLiniaPionowa(piksele))