#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

void wczytaj(vector<vector<int> >& dane)
{
    ifstream file("dane.txt");
    dane.resize(200);
    if(file.is_open())
    {
        for(unsigned int i=0; i<200; i++)
        {
            dane[i].resize(320);
            for(unsigned int j=0; j<320; j++)
            {
                file>>dane[i][j];
            }
        }
        file.close();
    }
}

void p1(const vector<vector<int> >& dane)
{
    unsigned int mini, maxi;
    mini=maxi=dane[0][0];
    for(unsigned int i=0; i<200; i++)
    {
        for(unsigned int j=0; j<320; j++)
        {
            if(dane[i][j]>maxi)
                maxi=dane[i][j];
            else if(dane[i][j]<mini)
                mini=dane[i][j];
        }
    }
    cout<<"2:\nnajjasniejszy: "<<maxi<<"\nnajciemniejszy: "<<mini<<endl;
}

void p2(const vector<vector<int> >& dane)
{
    unsigned int ile=0;
    for(unsigned int i=0; i<200; i++)
    {
        for(unsigned int j=0; j<320/2; j++)
        {
            if(dane[i][j]!=dane[i][320-1-j])
            {
                ile++;
                break;
            }
        }
    }
    cout<<"2: "<<ile<<endl;
}

void p3(const vector<vector<int> >& dane)
{
    unsigned int ile=0;
    for(unsigned int i=1; i<200-1; i++)
    {
        for(unsigned int j=1; j<320-1; j++)
        {
            if(abs(dane[i][j]-dane[i][j-1])>128)
                ile++;
            else if(abs(dane[i][j]-dane[i][j+1])>128)
                ile++;
            else if(abs(dane[i][j]-dane[i-1][j])>128)
                ile++;
            else if(abs(dane[i][j]-dane[i+1][j])>128)
                ile++;
        }
    }
    for(unsigned int i=1; i<200-1; i++)
    {
        if(abs(dane[i][0]-dane[i-1][0])>128)
            ile++;
        else if(abs(dane[i][0]-dane[i+1][0])>128)
            ile++;
        else if(abs(dane[i][0]-dane[i][1])>128)
            ile++;

        if(abs(dane[i][319]-dane[i-1][319])>128)
            ile++;
        else if(abs(dane[i][319]-dane[i+1][319])>128)
            ile++;
        else if(abs(dane[i][319]-dane[i][318])>128)
            ile++;
    }
    for(unsigned int j=1; j<320-1; j++)
    {
        if(abs(dane[0][j]-dane[0][j-1])>128)
            ile++;
        else if(abs(dane[0][j]-dane[0][j+1])>128)
            ile++;
        else if(abs(dane[0][j]-dane[1][j])>128)
            ile++;

        if(abs(dane[199][j]-dane[199][j-1])>128)
            ile++;
        else if(abs(dane[199][j]-dane[199][j+1])>128)
            ile++;
        else if(abs(dane[199][j]-dane[198][j])>128)
            ile++;
    }
    if(abs(dane[0][0]-dane[0][1])>128||abs(dane[0][0]-dane[1][0])>128)
        ile++;
    if(abs(dane[0][319]-dane[0][318])>128||abs(dane[0][319]-dane[1][319])>128)
        ile++;
    if(abs(dane[199][0]-dane[199][1])>128||abs(dane[199][0]-dane[198][0])>128)
        ile++;
    if(abs(dane[199][319]-dane[199][318])>128||abs(dane[199][319]-dane[198][319])>128)
        ile++;
    cout<<"3: "<<ile<<endl;
}

void p4(const vector<vector<int> >& dane)
{
    unsigned int ile,maxi=0;
    for(unsigned int j=0; j<320; j++)
    {
        ile=1;
        for(unsigned int i=1; i<200; i++)
        {
            if(dane[i][j]==dane[i-1][j]) {
                ile++;
            }
            else {
                if(ile>maxi) maxi=ile;
                ile=1;
            }
        }
        if(ile>maxi) maxi=ile;
    }
    cout<<"4: dlugosc linii: "<<maxi<<endl;
}

int main()
{
    vector<vector<int> > dane;
    wczytaj(dane);
    p1(dane);
    p2(dane);
    p3(dane);
    p4(dane);
    return 0;
}
