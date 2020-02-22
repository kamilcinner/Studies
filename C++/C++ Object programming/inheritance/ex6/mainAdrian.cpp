#include <iostream>
#include <sstream>
#include <typeinfo>

using namespace std;

class FunkcjeZyciowe
{
public:
    virtual void jedz(int iloscPozywienia)= 0;
    virtual void pij(int iloscWody)=0;
    virtual void spij(int czas)=0;
    virtual void baw(int czas)=0;

};

class Zwierze
{
protected:
    int glod = 0;
    int pragnienie = 0;
    int zmeczenie = 0;
    int humor = 0;
private:
    string mImie;
public:
     Zwierze(string name, int glod, int pragnienie, int zmeczenie, int humor)
     {
         mImie=name;
         this->glod = glod;
         this->pragnienie = pragnienie;
         this->zmeczenie = zmeczenie;
         this->humor = humor;
     }
     void UstawImie(string imie);
     const string NaLancuch() const;
     virtual string DajRodzaj() const
     {
        return "Zwierzatko: ";
     }
     virtual void WypiszFunkcje() const
     {
         cout <<"glod: " << glod << '\n' << "pragnienie: " << pragnienie << '\n' << "zmeczenie: " << zmeczenie
             << '\n'<<"humor: "<<humor<<'\n'<<endl;
     }
};

void Zwierze::UstawImie(string imie)
{
    mImie=imie;
}

const string Zwierze::NaLancuch() const
{
    WypiszFunkcje();
    return DajRodzaj() + mImie;
}

class Pies: public Zwierze, public FunkcjeZyciowe
{
private:

public:
    Pies(string imie) : Zwierze(imie,1,1,1,1){}
    void Szczekaj()
    {
        cout << "Hau Hau"<<endl;
    }
    void DajLape()
    {

        cout << "Pies daje lape"<<endl;
    }
    string DajRodzaj() const
    {
        return "Pies: ";
    }

    void jedz(int iloscPozywienia)
    {
        this->glod-=iloscPozywienia;
    }

    void pij(int iloscWody)
    {
        this->pragnienie-=iloscWody;
    }

    void spij(int czas)
    {
        this->zmeczenie-=czas;
    }

    void baw(int czas)
    {
        this->glod += czas;
    }

};

class Schronisko
{

    Zwierze *tab[100];
public:
    Zwierze* dajZwierze(int a);

    Schronisko(Zwierze* t[], int rozmiar)
    {
        for(int i = 0; i < rozmiar; i++)
        {
            tab[i] = t[i];
        }
    }


};

Zwierze* Schronisko::dajZwierze(int a)
{
    return tab[a];
}

class Kot : public Zwierze, public FunkcjeZyciowe
{
    string name;
public:
    Kot(string imie) : Zwierze(imie,1,1,1,1){}
    void miaucz()
    {
        cout << "Miau" << endl;
    }
    void myjSie()
    {
        cout <<"myj myj"<<endl;
    }
    string dajRodzajZwierzecia()
    {
        return "Kot:" + name;
    }

    void jedz(int iloscPozywienia)
    {
        this->glod-=iloscPozywienia;
    }

    void pij(int iloscWody)
    {
        this->pragnienie-=iloscWody;
    }

    void spij(int czas)
    {
        this->zmeczenie-=czas;
    }

    void baw(int czas)
    {
        this->glod += czas;
    }
};


int main()
{
    Zwierze zwierzatko("Zwierzatko",1,1,1,1);
    Pies pies("Pies1");
    Pies pies2("Pies2");

    Zwierze& refZwierzatko = zwierzatko;
    Pies& refPies = pies;

    Zwierze* wskZwierzatko1 = &zwierzatko;
    Zwierze* wskPies = &pies;
    Zwierze* wskPies2 = &pies2;

    FunkcjeZyciowe& funkcje = pies;

    pies.NaLancuch();
    funkcje.baw(1);
    pies.NaLancuch();
    funkcje.jedz(1);
    pies.NaLancuch();
    funkcje.pij(1);
    pies.NaLancuch();
    funkcje.spij(1);
    pies.NaLancuch();
    cout << endl;

    Kot kot("kot");
    FunkcjeZyciowe& funkcjek = kot;


    cout << "kot"<<string(100,'*')<<endl;
    kot.NaLancuch();
    funkcjek.baw(1);
    kot.NaLancuch();
    funkcjek.jedz(1);
    kot.NaLancuch();
    funkcjek.pij(1);
    kot.NaLancuch();
    funkcjek.spij(1);
    kot.NaLancuch();

    cout << dynamic_cast<Kot&>(funkcjek).NaLancuch() << endl;
    cout << dynamic_cast<Pies&>(funkcje).NaLancuch() << endl;


//    cout << refZwierzatko.NaLancuch()<<'\n'<< refPies.NaLancuch()<<endl;
//    const int N = 3;
//    Zwierze* tab[N] = {wskPies, wskPies2};
//    Schronisko schronisko(tab, N);
//    for(int i = 0; i < N ; i++)
//    {
//        Pies* tempPies = dynamic_cast<Pies*>(schronisko.dajZwierze(i));
//        cout << tempPies->NaLancuch() << endl;
//        tempPies->Szczekaj();
//    }



    try
    {
        Pies* wskPies2 = dynamic_cast<Pies*>(wskPies);
        //wskPies2->DajLape();
    }
    catch (bad_alloc &bada)
    {
        cout << bada.what() <<endl;

    }



    return 0;
}
