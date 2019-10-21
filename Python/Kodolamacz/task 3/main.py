def potega_wydajnie(podstawa, wykladnik):
    if wykladnik == 1:
        return podstawa
    if wykladnik == 0:
        return 1
    polowa = potega_wydajnie(podstawa, wykladnik//2)
    if wykladnik % 2 == 0:
        return polowa*polowa
    else:
        return polowa*polowa*podstawa

def czyPalindrom(napis):
    n = len(napis)
    for i in range(n//2):
        if napis[i] != napis[n - 1 - i]:
            return False
    return True

def czyPalindrom2(napis):
    return napis == napis[::-1]

def czyAnagram(napis1, napis2):
    n = len(napis1)
    if n != len(napis2):
        return False
    slownik1 = dict()
    slownik2 = dict()
    for i in range(n):
        if napis1[i] in slownik1:
            slownik1[napis1[i]] += 1
        else:
            slownik1[napis1[i]] = 1
        if napis2[i] in slownik2:
            slownik2[napis2[i]] += 1
        else:
            slownik2[napis2[i]] = 1
    return slownik1 == slownik2

def moda(lista):
    zliczenia = dict()
    for i in range(len(lista)):
        if lista[i] in zliczenia:
            zliczenia[lista[i]] += 1
        else:
            zliczenia[lista[i]] = 1
    maks = -1
    liczba_maks = -1
    for (co, ile) in zliczenia.items():
        if ile > maks:
            liczba_maks = co
            maks = ile
    return liczba_maks

def main():
    print("2^10 = " + str(potega_wydajnie(2, 10)))
    print("czyPalindrom(kajak) = " + str(czyPalindrom("kajak")))
    print("czyPalindrom(kobyla) = " + str(czyPalindrom("kobyla")))
    print("czyPalindrom2(kajak) = " + str(czyPalindrom2("kajak")))
    print("czyPalindrom2(kobyla) = " + str(czyPalindrom2("kobyla")))
    print("czyAnagram(kajak, jaakk) = " + str(czyAnagram("kajak", "jaakk")))
    print("czyAnagram(kobyla, boczek) = " + str(czyAnagram("kobyla", "boczek")))
    print("moda([1,6,4,7,2,8,6,7,6]) = " + str(moda([1,6,4,7,2,8,6,7,6])))


if __name__ == "__main__":
    main()