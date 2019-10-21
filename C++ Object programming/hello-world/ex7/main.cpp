#include <iostream>
#include <windows.h>

using namespace std;

class State {
public:
    string imie;
    int humor, glod, zmeczenie;

    State(string imie="No name", int humor=1, int glod=2, int zmeczenie=3) {
        this->imie=imie;
        this->humor=humor;
        this->glod=glod;
        this->zmeczenie=zmeczenie;
    }
};

State Kot;
State Pies;

namespace pies {
    State& do_kotka=Kot;

    void baw_sie(const int& czas);

    void jedz(const int& czas) {
        Pies.glod-=czas;
    }
    void odpoczywaj(const int& czas) {
        Pies.zmeczenie-=czas;
    }
}
namespace kot {
    State& do_pieska=Pies;

    void baw_sie(const int& czas);

    void jedz(const int& czas) {
        Kot.glod-=czas;
    }
    void odpoczywaj(const int& czas) {
        Kot.zmeczenie-=czas;
    }
}
void pies::baw_sie(const int& czas) {
    kot::do_pieska.humor+=czas;
    kot::do_pieska.glod+=czas;
    kot::do_pieska.zmeczenie+=czas;
    pies::do_kotka.humor-=czas;
}
void kot::baw_sie(const int& czas) {
    pies::do_kotka.humor+=czas;
    pies::do_kotka.glod+=czas;
    pies::do_kotka.zmeczenie+=czas;
    kot::do_pieska.humor-=czas;
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
        cout<<pies::do_kotka.imie<<endl;
        cout<<"Humor: "<<pies::do_kotka.humor<<endl;
        cout<<"Glod: "<<pies::do_kotka.glod<<endl;
        cout<<"Zmeczenie: "<<pies::do_kotka.zmeczenie<<endl<<endl;

        cout<<kot::do_pieska.imie<<endl;
        cout<<"Humor: "<<kot::do_pieska.humor<<endl;
        cout<<"Glod: "<<kot::do_pieska.glod<<endl;
        cout<<"Zmeczenie: "<<kot::do_pieska.zmeczenie<<endl<<endl;

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
