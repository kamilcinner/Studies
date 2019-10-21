#include <iostream>
#include <windows.h>

using namespace std;

namespace pies {
    string imie="Hauu";
    int humor=1, glod=2, zmeczenie=5;
    void baw_sie(int czas);
    void jedz(int czas) {
        glod-=czas;
    }
    void odpoczywaj(int czas) {
        zmeczenie-=czas;
    }
}
namespace kot {
    string imie="Miauu";
    int humor=1, glod=2, zmeczenie=5;
    void baw_sie(int czas);
    void jedz(int czas) {
        glod-=czas;
    }
    void odpoczywaj(int czas) {
        zmeczenie-=czas;
    }
}
void pies::baw_sie(int czas) {
    pies::humor+=czas;
    pies::glod+=czas;
    pies::zmeczenie+=czas;
    kot::humor-=czas;
}
void kot::baw_sie(int czas) {
    kot::humor+=czas;
    kot::glod+=czas;
    kot::zmeczenie+=czas;
    pies::humor-=czas;
}

int bal() {
    int x;
    cout<<"Podaj czas/ilosc (liczba calkowita): "; cin>>x;
    return x;
}

int main()
{
    int choice;
    bool proceed=true;

    do {
        cout<<kot::imie<<endl;
        cout<<"Humor: "<<kot::humor<<endl;
        cout<<"Glod: "<<kot::glod<<endl;
        cout<<"Zmeczenie: "<<kot::zmeczenie<<endl<<endl;

        cout<<pies::imie<<endl;
        cout<<"Humor: "<<pies::humor<<endl;
        cout<<"Glod: "<<pies::glod<<endl;
        cout<<"Zmeczenie: "<<pies::zmeczenie<<endl<<endl;

        cout<<"1.Kot - baw sie"<<endl;
        cout<<"2.Kot - jedz"<<endl;
        cout<<"3.Kot - odpoczywaj"<<endl<<endl;

        cout<<"4.Pies - baw sie"<<endl;
        cout<<"5.Pies - jedz"<<endl;
        cout<<"6.Pies - odpoczywaj"<<endl<<endl;

        cout<<"7.Zakoncz program"<<endl<<endl;

        cout<<"Dzialanie: "; cin>>choice;
        system("cls");
        switch(choice) {
        case 1: {
            kot::baw_sie(bal());
            break;
        }
        case 2: {
            kot::jedz(bal());
            break;
        }
        case 3: {
            kot::odpoczywaj(bal());
            break;
        }
        case 4: {
            pies::baw_sie(bal());
            break;
        }
        case 5: {
            pies::jedz(bal());
            break;
        }
        case 6: {
            pies::odpoczywaj(bal());
            break;
        }
        case 7: {
            proceed=false;
            break;
        }
        default: {
            system("cls");
            cout<<"Blad! Sprobuj ponownie...";
            Sleep(500);
        }
        }
        system("cls");
    } while (proceed);

    system("pause");
    return 0;
}
