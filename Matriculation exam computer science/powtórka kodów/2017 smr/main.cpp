#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h> // atoi, itoa, strtoul
#include <bits/stdc++.h> // strcpy

using namespace std;

void wczytaj(vector<string>& binarne)
{
    ifstream file("binarne.txt");
    binarne.resize(500);
    for(unsigned int i=0; i<500; i++)
        file>>binarne[i];
    file.close();
}

void p1(const vector<string>& binarne)
{
    unsigned int ile=0;
    string najdluzszy_dwucykliczny;
    bool dwucykliczny;
    for(unsigned int i=0; i<500; i++)
    {
        dwucykliczny=true;
        for(unsigned int j=0; j<binarne[i].size()/2; j++)
        {
            if(binarne[i][j]!=binarne[i][binarne[i].size()/2+j])
            {
                dwucykliczny=false;
                break;
            }
        }
        if(dwucykliczny)
        {
            ile++;
            if(najdluzszy_dwucykliczny.size()<binarne[i].size())
                najdluzszy_dwucykliczny=binarne[i];
        }
    }
    cout<<"1:\nile = "<<ile<<"\nnajdluzszy dwucykliczny: "<<najdluzszy_dwucykliczny<<"\ndlugosc: "<<najdluzszy_dwucykliczny.size()<<endl;
}

void p2(const vector<string>& binarne)
{
    unsigned int ile=0,suma4,t,dlugosc_min;
    bool poprawny;
    for(unsigned int i=0; i<500; i++)
    {
        poprawny=true;
        for(unsigned int j=0; j<binarne[i].size(); j+=4)
        {
            suma4=0;
            t=8;
            for(unsigned int k=0; k<4; k++)
            {
                if(binarne[i][j+k]=='1')
                {
                    suma4+=t;
                }
                t/=2;
            }
            if(suma4>9)
            {
                poprawny=false;
                break;
            }
        }
        if(!poprawny)
        {
            if(ile==0)
            {
                dlugosc_min=binarne[i].size();
            }
            else if(dlugosc_min>binarne[i].size())
            {
                dlugosc_min=binarne[i].size();
            }
            ile++;
        }
    }
    cout<<"2:\nile = "<<ile<<"\ndlugosc_min: "<<dlugosc_min<<endl;
}

void p3(const vector<string>& binarne)
{
    char* bin;
    unsigned long int max_dziesietnie=0,dziesietnie;
    for(unsigned int i=0; i<500; i++)
    {
        if(binarne[i].size()>16)
            continue;

        bin=new char[binarne[i].size()+1];
        strcpy(bin,binarne[i].c_str());
        dziesietnie=strtoul(bin,NULL,2);

        if(dziesietnie>max_dziesietnie)
            max_dziesietnie=dziesietnie;
    }
    delete bin;

    char max_binarnie[16];
    itoa(max_dziesietnie,max_binarnie,2);

    cout<<"3:\nmax dziesietnie: "<<max_dziesietnie<<endl;
    cout<<"max binarnie: "<<max_binarnie<<endl;
}

int main()
{
    vector<string> bin;
    wczytaj(bin);
    p1(bin);
    p2(bin);
    p3(bin);

    return 0;
}
