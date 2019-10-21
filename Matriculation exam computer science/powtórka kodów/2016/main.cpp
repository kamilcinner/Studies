#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void p1()
{
    unsigned int k=107%26;
    ifstream file("dane_6_1.txt");
    vector<string> slowa;
    slowa.resize(100);
    if(file.is_open())
    {
        for(unsigned int i=0; i<100; i++)
        {
            file>>slowa[i];
        }
        file.close();
    }
    ofstream file2("wyniki_6_1.txt");
    for(unsigned int i=0; i<100; i++)
    {
        for(unsigned int j=0; j<slowa[i].size(); j++)
        {
            slowa[i][j]+=k;
            if(slowa[i][j]>90)
                slowa[i][j]-=26;
        }
        file2<<slowa[i]<<endl;
    }
    file2.close();
}

void p2()
{
    vector<string> slowo;
    vector<unsigned int> klucz;
    slowo.resize(3000);
    klucz.resize(3000);
    ifstream file("dane_6_2.txt");
    if(file.is_open())
    {
        for(unsigned int i=0; i<3000; i++)
        {
            file>>slowo[i];
            file>>klucz[i];
            klucz[i]%=26;
        }
        file.close();
    }
    ofstream file2("wyniki_6_2.txt");
    for(unsigned int i=0; i<3000; i++)
    {
        for(unsigned int j=0; j<slowo[i].size(); j++)
        {
            slowo[i][j]-=klucz[i];
            if(slowo[i][j]<65)
                slowo[i][j]+=26;
        }
        file2<<slowo[i]<<endl;
    }
    file2.close();
}

void p3()
{
    vector<string> slowo;
    vector<string> szyfr;
    unsigned int klucz_glowny, klucz_znaku;
    slowo.resize(3000);
    szyfr.resize(3000);
    ifstream file("dane_6_3.txt");
    if(file.is_open())
    {
        for(unsigned int i=0; i<3000; i++)
        {
            file>>slowo[i];
            file>>szyfr[i];
        }
        file.close();
    }
    ofstream file2 ("wyniki_6_3.txt");
    for(unsigned int i=0; i<3000; i++)
    {
        if(szyfr[i][0]<slowo[i][0])
        {
            klucz_glowny=90-slowo[i][0];
            klucz_glowny++;
            klucz_glowny+=szyfr[i][0]-65;
        }
        else
            klucz_glowny=szyfr[i][0]-slowo[i][0];
        for(unsigned int j=1; j<slowo[i].size(); j++)
        {
            if(szyfr[i][j]<slowo[i][j])
            {
                klucz_znaku=90-slowo[i][j];
                klucz_znaku++;
                klucz_znaku+=szyfr[i][j]-65;
            }
            else
                klucz_znaku=szyfr[i][j]-slowo[i][j];
            if(klucz_glowny!=klucz_znaku)
            {
                file2<<slowo[i]<<endl;
                break;
            }
        }
    }
    file2.close();
}

int main()
{
    p1();
    p2();
    p3();
    return 0;
}
