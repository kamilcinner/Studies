#include <iostream>

using namespace std;

class Samochod
{
    public:
    string marka;
    string model;
    int rocznik;
    int przebieg;
    void wczytaj()
    {
        cout<<"Wczytam dane"<<endl;
        cout<<"Podaj marke: ";
        cin>>marka;
        cout<<"Podaj model: ";
        cin>>model;
        cout<<"Podaj rocznik: ";
        cin>>rocznik;
        cout<<"Podaj przebieg: ";
        cin>>przebieg;
    }
    void wypisz()
    {
        cout<<"Podaje dane"<<endl;
        cout<<"Marka: "<<marka<<"\nModel: "<<model<<"\nRocznik: "<<rocznik<<"\nPrzebieg: "<<przebieg;
    }
};

int main()
{
    Samochod s1;
    s1.wczytaj();
    s1.wypisz();
    return 0;
}
