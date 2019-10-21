#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

void wczytaj(vector<string>& sygnaly)
{
    ifstream file("sygnaly.txt");
    sygnaly.resize(1000);
    if(file.is_open())
    {
        for(unsigned int i=0; i<1000; i++)
        {
            file>>sygnaly[i];
        }
        file.close();
    }
}

void p1(const vector<string>& sygnaly)
{
    string wynik;
    for(unsigned int i=39; i<1000; i+=40)
    {
        wynik.push_back(sygnaly[i][9]);
    }
    cout<<"1: "<<wynik<<endl;
}

void p2(const vector<string>& sygnaly)
{
    vector<char> rozne_litery;
    string piekne_slowo;
    unsigned int liczba_roznych=0;
    bool inna_litera;
    for(unsigned int i=0; i<1000; i++)
    {
        rozne_litery.clear();
        rozne_litery.push_back(sygnaly[i][0]);
        for(unsigned int j=1; j<sygnaly[i].size(); j++)
        {
            inna_litera=true;
            for(unsigned int k=0; k<rozne_litery.size(); k++)
            {
                if(rozne_litery[k]==sygnaly[i][j])
                {
                    inna_litera=false;
                    break;
                }
            }
            if(inna_litera)
            {
                rozne_litery.push_back(sygnaly[i][j]);
            }
        }
        if(rozne_litery.size()>liczba_roznych)
        {
            liczba_roznych=rozne_litery.size();
            piekne_slowo=sygnaly[i];
        }
    }
    cout<<"2:\nliczba roznych liter: "<<liczba_roznych<<"\nslowo: "<<piekne_slowo<<endl;
}

void p3(const vector<string>& sygnaly)
{
    ofstream file("3.txt");
    bool dobre_slowo;
    for(unsigned int i=0; i<1000; i++)
    {
        dobre_slowo=true;
        for(unsigned int j=0; j<sygnaly[i].size(); j++)
        {
            for(unsigned int k=j+1; k<sygnaly[i].size(); k++)
            {
                if(abs(sygnaly[i][j]-sygnaly[i][k])>10)
                {
                    dobre_slowo=false;
                    break;
                }
            }
            if(!dobre_slowo)
                break;
        }
        if(dobre_slowo)
        {
            file<<sygnaly[i]<<endl;
        }
    }
    file.close();
}

int main()
{
    vector<string> S;
    wczytaj(S);
    p1(S);
    p2(S);
    p3(S);
    return 0;
}
