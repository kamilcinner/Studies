#include <iostream>
#include <fstream>
using namespace std;

// W programie zastosowano dwie metody sprawdzania czy liczba jest pierwsza.
// Czêsto wystêpuj¹ce sprawdzanie pierwszoœci liczb z przedzia³u [2,n] jest
// szybko wykonywane za pomoc¹ raz wyliczanej tablicy czyPierwsza. 
// Sprawdzanie liczb, które mog¹ byæ wiêksze od n realizuje 
// funkcja jestPierwsza.

const int n = 100000;
  // Informacje o pierwszoœci liczb z zakresu [2,n] pamiêtamy w tablicy.

bool czyPierwsza[n+1]; 
  // Globalna tablica informuj¹ca, czy liczba bêd¹ca indeksem 
  // jest liczb¹ pierwsz¹

void sito()
//Wyznacza liczby pierwsze w przedziale [2,n]
//Po wykonaniu tej funkcji czyPierwsza[j] wtedy i tylko gdy j jest 
//liczb¹ pierwsz¹ (dla j z przedzia³u [2,n])
	{
      czyPierwsza[0]=false;   
      czyPierwsza[1]=false;   
	  for (int k=2; k<=n; k++)
        czyPierwsza[k]=true;	
	  for (int k=2; k*k<=n; k++)
		{
		  if (czyPierwsza[k])
       	  	for (int i=k*k; i<=n; i+=k)
		      czyPierwsza[i]=false;			
		}	
	}

bool d_pierwsza(int x, int d)
//Sprawdza, czy suma cyfr liczby x z przedzia³u [2,n] w zapisie 
//przy podstawie d jest liczb¹ pierwsz¹. Korzysta z tablicy czyPierwsza.
	{
	  int s = 0;
	  while (x!=0)	
  		{
   		  s+=x%d;
  		  x/=d;	
  		}
  	  return czyPierwsza[s]; 
	}

bool jestPierwsza(long x)
//sprawdza czy liczba x jest pierwsza
	{
	  if (x<2)
        return false;
	  else
  		{
    	  for (int i=2; i*i<=x; i++)
       	    if (x%i==0) 
              return false;
   		  return true;
  		}
	} 
   
void pierwsze_w_przedziale(int pocz, int kon, char* nazwa_pliku)
	{
	 ofstream wyniki(nazwa_pliku); // Strumieñ z wynikami
	 long suma_B = 0; //suma liczb super B pierwszych w przedziale [pocz,kon]
	 int ile_B = 0;   //liczba wyst¹pieñ liczb super B pierwszych  
	 int ile_p = 0;   //liczba liczb w przedziale, których suma cyfr jest pierwsza

	 for (int i=pocz; i<=kon; i++)
		{
 		  if (czyPierwsza[i] && d_pierwsza(i,10) && d_pierwsza(i,2))
		  //Czy i jest super B pierwsza? 
  			{
   			  wyniki << i << endl;
  			  suma_B+=i;
  			  ile_B++;
  			}   
 		 if (d_pierwsza(i,10))
		 //Czy suma cyfr liczby i jest pierwsza? 
           ile_p++;
		}
	 
	 cout << "ile_B = " << ile_B << "; ile_p = " << ile_p << 
   	         (jestPierwsza(suma_B)? "; suma jest pierwsza" :  
                                    "; suma NIE jest pierwsza") << endl;
	}

int main()
	{
	  //wyznaczenie liczb pierwszych w przedziale [2,100000]
	  sito();
	  
	  //zadanie a-1
 	  pierwsze_w_przedziale(2,1000,"1.txt");
	  
	  //zadanie a-2, b
 	  pierwsze_w_przedziale(100,10000,"2.txt");
	  
	  //zadanie a-3
 	  pierwsze_w_przedziale(1000,100000,"3.txt");
	 
	  // system("pause");
	}
