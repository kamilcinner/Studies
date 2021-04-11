#ifndef LAB03_H
#define LAB03_H

/*
Zadanie 1 : Dwu-wątkowe sumowanie wektora

W programie należy stworzyć tablicę jednowymiarową, czyli wektor, o rozmiarze n. W tablicy należy zapisać liczby losowe. Tablicę sumujemy stosując 2 wątki. Pierwszy wątek sumuje pierwszą połowę tablicy, drugi drugą połowę. Po zakończeniu pracy obie sumy są dodawane do siebie i wyświetlane. Dodatkowo suma jest obliczana w głównym wątku programu dla całej tablicy i również wyświetlana.

Charakterystyka zadania: 1) Brak współdzielonych zasobów, 2 Brak sekcji krytycznych
*/

void lab03(unsigned int arraySize);

#endif
