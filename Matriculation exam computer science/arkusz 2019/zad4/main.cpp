#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void wczytaj(vector<unsigned int>& liczby)
{
    liczby.resize(500);
    ifstream file("liczby.txt");
    if(file.is_open())
    {
        for(unsigned int i=0;i<500;i++)
        {
            file >> liczby[i];
        }
        file.close();
    }
}

void zad1(const vector<unsigned int>& liczby)
{
    int ile=0;
    bool jestPotega;
    int liczba;
    for(unsigned int i=0;i<500;i++)
    {
        liczba=liczby[i];
        jestPotega=true;
        while(liczba > 1)
        {
            if(liczba % 3 != 0)
            {
                jestPotega=false;
                break;
            }
            liczba /= 3;
        }
        if(jestPotega) ile++;
    }
    cout<<"zad1: "<<ile<<endl;
}

int main()
{
    vector<unsigned int> liczby;
    wczytaj(liczby);
    zad1(liczby);

    return 0;
}
