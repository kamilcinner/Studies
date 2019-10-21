#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Liczba
{
public:
    string liczba;
    unsigned int nr_wiersza;
};

void wczytaj(vector<string>& liczby)
{
    ifstream file("liczby.txt");
    liczby.resize(1000);
    if(file.is_open())
    {
        for(unsigned int i=0; i<1000; i++)
        {
            file>>liczby[i];
        }
        file.close();
    }
}

void p1(const vector<string>& liczby)
{
    unsigned int zera,jedynki,ile=0;
    for(unsigned int i=0; i<1000; i++)
    {
        zera=jedynki=0;
        for(unsigned int j=0; j<liczby[i].size(); j++)
        {
            if(liczby[i][j]=='0')
                zera++;
            else
                jedynki++;
        }
        if(zera>jedynki)
            ile++;
    }
    cout<<"1: "<<ile<<endl;
}

void p2(const vector<string>& liczby)
{
    unsigned int p2=0,p8=0;
    for(unsigned int i=0; i<1000; i++)
    {
        if(liczby[i][liczby[i].size()-1]=='0')
        {
            p2++;
            if(liczby[i].size()>3 && liczby[i][liczby[i].size()-2]=='0' && liczby[i][liczby[i].size()-3]=='0')
                p8++;
        }
    }
    cout<<"2:\nprzez 2: "<<p2<<"\nprzez 8: "<<p8<<endl;
}

void p3(const vector<string>& liczby)
{
    unsigned int max_dlugosc, min_dlugosc;
    max_dlugosc=min_dlugosc=liczby[0].size();
    for(unsigned int i=1; i<1000; i++)
    {
        if(liczby[i].size()>max_dlugosc)
            max_dlugosc=liczby[i].size();
        else if(liczby[i].size()<min_dlugosc)
            min_dlugosc=liczby[i].size();
    }

    vector<Liczba> liczbyEX;
    Liczba liczbaEX;
    for(unsigned int i=0; i<1000; i++)
    {
        liczbaEX.liczba=liczby[i];
        liczbaEX.nr_wiersza=i+1;
        liczbyEX.push_back(liczbaEX);
    }

    vector<Liczba> liczby_dlugie, liczby_krotkie;
    for(unsigned int i=0; i<1000; i++)
    {
        if(liczbyEX[i].liczba.size()==max_dlugosc)
            liczby_dlugie.push_back(liczbyEX[i]);
        else if(liczbyEX[i].liczba.size()==min_dlugosc)
            liczby_krotkie.push_back(liczbyEX[i]);
    }
    Liczba liczba_min, liczba_max;
    liczba_min=liczby_krotkie[0];
    liczba_max=liczby_dlugie[0];
    for(unsigned int i=1; i<liczby_dlugie.size(); i++)
    {
        for(unsigned int j=0; j<liczby_dlugie[i].liczba.size(); j++)
        {
            if(liczba_max.liczba[j]<liczby_dlugie[i].liczba[j])
            {
                //cout<<liczba_max.liczba<<endl;
                //cout<<liczby_dlugie[i].liczba<<endl<<endl;
                liczba_max=liczby_dlugie[i];
                break;
            }
            else if (liczba_max.liczba[j]>liczby_dlugie[i].liczba[j]) break; // to jest bardzo wazne
        }
    }
    for(unsigned int i=1; i<liczby_krotkie.size(); i++)
    {
        for(unsigned int j=0; j<liczby_krotkie[i].liczba.size(); j++)
        {
            if(liczba_min.liczba[j]>liczby_krotkie[i].liczba[j])
            {
                //cout<<liczba_min.liczba<<endl;
                //cout<<liczby_krotkie[i].liczba<<endl<<endl;
                liczba_min=liczby_krotkie[i];
                break;
            }
            else if(liczba_min.liczba[j]<liczby_krotkie[i].liczba[j]) break; // to jest bardzo wazne
        }
    }
    cout<<"3:\nmin: "<<liczba_min.nr_wiersza<<"\nmax: "<<liczba_max.nr_wiersza<<endl;
}

int main()
{
    vector<string> L;
    wczytaj(L);
    p1(L);
    p2(L);
    p3(L);

    return 0;
}
