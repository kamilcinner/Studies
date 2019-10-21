import math
class FunkcjaKwadratowa:
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c
    def Rozwiaz(self):
        if self.a == 0:
            if self.b == 0:
                if self.c == 0:
                    print("Nieskonczenie wiele rozwiazan")
                    return "inf"
                print("Sprzecznosc")
                return "contr"
            else:
                print("Jedno miejsce zerowe")
                return (1, - self.c / self.b)
        else:
            delta = self.b * self.b - 4 * self.a * self.c
            if delta > 0:
                print("Dwa miejsca zerowe")
                x1 = (- self.b - math.sqrt(delta)) / (2 * self.a)
                x2 = (- self.b + math.sqrt(delta)) / (2 * self.a)
                return (2, x1, x2)
            elif delta == 0:
                print("Jedno miejsce zerowe")
                x = - self.b / (2 * self.a)
                return (1, x)
            else:
                print("Brak miejsc zerowych")
                return 0

class Zespolona:
    def __init__(self, re, im):
        self.re = re
        self.im = im
    def modul(self):
        return math.sqrt(self.re * self.re + self.im * self.im)
    @staticmethod
    def dodaj(Z1, Z2):
        return Zespolona(Z1.re + Z2.re, Z1.im + Z2.im)
    @staticmethod
    def mnoz(Z1, Z2):
        Re = Z1.re * Z2.re - Z1.im * Z2.im
        Im = Z1.re * Z2.im + Z1.im * Z2.re
        return Zespolona(Re, Im)

class Ulamek:
    def __init__(self, licznik, mianownik):
        if licznik == 0 or mianownik == 0:
            exit (0)
        self.licznik = licznik
        self.mianownik = mianownik
    def skroc(self):
        if self.licznik > self.mianownik:
            n = self.licznik
            m = self.mianownik
        else:
            n = self.mianownik
            m = self.licznik
        while m != 0:
            r = n - (n // m) * m
            n = m
            m = r
        nwd = n
        self.licznik /= nwd
        self.mianownik /= nwd
    @staticmethod
    def wspMianownik(U1, U2):
        U1.licznik *= U2.mianownik
        U2.licznik *= U1.mianownik
        U1.mianownik = U2.mianownik = U1.mianownik * U2.mianownik
    @staticmethod
    def dodaj(U1, U2):
        Ulamek.wspMianownik(U1, U2)
        U = Ulamek(U1.licznik + U2.licznik, U1.mianownik)
        U.skroc()
        return U
    @staticmethod
    def odejmij(U1, U2):
        Ulamek.wspMianownik(U1, U2)
        U = Ulamek(U1.licznik - U2.licznik, U1.mianownik)
        U.skroc()
        return U
    @staticmethod
    def mnoz(U1, U2):
        U = Ulamek(U1.licznik * U2.licznik, U1.mianownik * U2.mianownik)
        U.skroc()
        return U
    @staticmethod
    def dziel(U1, U2):
        U = Ulamek(U1.licznik * U2.mianownik, U1.mianownik * U2.licznik)
        U.skroc()
        return U

def main():
    # test zespolone
    Z1 = Zespolona(4, 5)
    Z2 = Zespolona(10, -23)
    Z3 = Zespolona.dodaj(Z1, Z2)
    print(Z3.re, Z3.im)
    Z4 = Zespolona.mnoz(Z1, Z3)
    print(Z4.re, Z4.im)
    print(Z4.modul())

    # test ulamki
    U1 = Ulamek(12, 3)
    print (U1.licznik, U1.mianownik)
    U1.skroc()
    print(U1.licznik, U1.mianownik)
    U2 = Ulamek(4, 6)
    U3 = Ulamek.dodaj(U1, U2)
    print(U3.licznik, U3.mianownik)
    U4 = Ulamek.odejmij(U1, U2)
    print(U4.licznik, U4.mianownik)
    U5 = Ulamek.mnoz(U3, U4)
    print(U5.licznik, U5.mianownik)
    U6 = Ulamek(1, 3)
    U7 = Ulamek(3, 1)
    U8 = Ulamek.mnoz(U6, U7)
    print(U8.licznik, U8.mianownik)
    U9 = Ulamek(1, 3)
    U10 = Ulamek.dziel(U6, U9)
    print(U10.licznik, U10.mianownik)

    # test funkcja
    F1 = FunkcjaKwadratowa(1,2,-13)
    FL = []
    FL = F1.Rozwiaz()
    print(FL)

if __name__ == "__main__":
    main()
