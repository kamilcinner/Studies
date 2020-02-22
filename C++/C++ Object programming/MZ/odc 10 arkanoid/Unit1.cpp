//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int x=-8,y=-8;
int do_wygranej=12;

bool kolizja(TImage*pilka,TImage*cegla)
{
        if(pilka->Left >= cegla->Left-pilka->Width &&
        pilka->Left <= cegla->Left+cegla->Width &&
        pilka->Top >= cegla->Top-pilka->Height &&
        pilka->Top <= cegla->Top+cegla->Height)
        {
                return true;
        }
        else return false;
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer_pilkaTimer(TObject *Sender)
{
        b->Left+=x;
        b->Top+=y;

        //odbij od lewej sciany
        if(b->Left-5 <= tlo->Left) x=-x;

        //odbij od gornej sciany
        if(b->Top-5 <= tlo->Top) y=-y;

        //odbij od prawej sciany
        if(b->Left+b->Width+5 >= tlo->Width) x=-x;

        //skucha!
        if(b->Top >= p->Top+p->Height+15)
        {
                Timer_pilka->Enabled=false;
                b->Visible=false;
                Button1->Caption="Porazka! Jeszcze raz?";
                Button1->Visible=true;
        }
        else if(b->Left > p->Left-b->Width/2 && b->Left < p->Left+p->Width &&
                b->Top+b->Height > p->Top)
        {
                if(y>0) y=-y;
        }

        if(do_wygranej<=0)
        {
                Timer_pilka->Enabled=false;
                b->Visible=false;
                Button1->Caption="Wygrana! Jeszcze raz?";
                Button1->Visible=true;
        }

        //blok1
        if(kolizja(b,Image1) && Image1->Visible==true)
        {x=-x; y=-y; Image1->Visible=false; do_wygranej--;}

        //blok2
        if(kolizja(b,Image2) && Image2->Visible==true)
        {x=-x; y=-y; Image2->Visible=false; do_wygranej--;}

        //blok3
        if(kolizja(b,Image3) && Image3->Visible==true)
        {x=-x; y=-y; Image3->Visible=false; do_wygranej--;}

        //blok4
        if(kolizja(b,Image4) && Image4->Visible==true)
        {x=-x; y=-y; Image4->Visible=false; do_wygranej--;}

        //blok5
        if(kolizja(b,Image5) && Image5->Visible==true)
        {x=-x; y=-y; Image5->Visible=false; do_wygranej--;}

        //blok6
        if(kolizja(b,Image6) && Image6->Visible==true)
        {x=-x; y=-y; Image6->Visible=false; do_wygranej--;}

        //blok7
        if(kolizja(b,Image7) && Image7->Visible==true)
        {x=-x; y=-y; Image7->Visible=false; do_wygranej--;}

        //blok8
        if(kolizja(b,Image8) && Image8->Visible==true)
        {x=-x; y=-y; Image8->Visible=false; do_wygranej--;}

        //blok9
        if(kolizja(b,Image9) && Image9->Visible==true)
        {x=-x; y=-y; Image9->Visible=false; do_wygranej--;}

        //blok10
        if(kolizja(b,Image10) && Image10->Visible==true)
        {x=-x; y=-y; Image10->Visible=false; do_wygranej--;}

        //blok11
        if(kolizja(b,Image11) && Image11->Visible==true)
        {x=-x; y=-y; Image11->Visible=false; do_wygranej--;}

        //blok12
        if(kolizja(b,Image12) && Image12->Visible==true)
        {x=-x; y=-y; Image12->Visible=false; do_wygranej--;}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::lewoTimer(TObject *Sender)
{
        if(p->Left>10) p->Left-=10;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::prawoTimer(TObject *Sender)
{
        if(p->Left+p->Width < tlo->Width) p->Left+=10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key==VK_LEFT) lewo->Enabled=true;
        if(Key==VK_RIGHT) prawo->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key==VK_LEFT) lewo->Enabled=false;
        if(Key==VK_RIGHT) prawo->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
        b->Left=50;
        b->Top=50;

        b->Visible=true;
        x=-8;
        y=-8;
        Timer_pilka->Enabled=true;
        Button1->Visible=false;
        do_wygranej=12;
        Image1->Visible=true; Image2->Visible=true; Image3->Visible=true;
        Image4->Visible=true; Image5->Visible=true; Image6->Visible=true;
        Image7->Visible=true; Image8->Visible=true; Image9->Visible=true;
        Image10->Visible=true; Image11->Visible=true; Image12->Visible=true;
}
//---------------------------------------------------------------------------
