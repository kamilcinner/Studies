Program Slowa_zadanie6;
Const
 max_r = 1000;
Type
 String20 = String[20];
Var 
 wyniki: text; 
 s: Array[1..max_r] Of String20;
 liczbaSlow: integer;

Procedure wczytajDane;
var
  dane: text;
Begin
  Assign(dane, 'dane.txt');
  Reset(dane);
  liczbaSlow:=0;
  While Not eof(dane) Do
   Begin
    Inc(liczbaSlow);
    Readln(dane, s[liczbaSlow]);
   End;
  Close(dane);
End;

Procedure podpunktA;

 Procedure SortujSlowa;
 Var
  i,j,k: integer;
  x: String20;
 Begin
  For i:=1 To liczbaSlow-1 Do
   Begin
    k:=i; x:=s[i];
    For j:=i+1 To liczbaSlow Do
     If x > s[j] Then
      Begin
       k:=j;
       x:=s[j]
      End;
    s[k]:=s[i];
    s[i]:=x
   End;
 End;

var
 liczbaPowtorzenSlow: integer;
 najczestszeSlowo: String20;
 maxLiczbaWystapien: integer;

 Procedure ObsluzSlowo(slowo: String20; liczbaWystapien: integer);
 Begin
  If liczbaWystapien > 1 Then Inc(liczbaPowtorzenSlow);
  If liczbaWystapien > maxLiczbaWystapien Then
   Begin
    maxLiczbaWystapien := liczbaWystapien;
    najczestszeSlowo := slowo;
   End;
 End;

Var 
 i,licznik: integer;

Begin
 Writeln(wyniki,'Odpowiedzi do podpunktu a)');
 SortujSlowa;

 liczbaPowtorzenSlow := 0;
 najczestszeSlowo := s[1];
 maxLiczbaWystapien := 1;
 licznik:=1;    { liczba wystapien aktualnego slowa }
 For i:=2 To liczbaSlow Do
  If s[i] <> s[i-1] Then
   Begin { nowe slowo }
    ObsluzSlowo(s[i-1], licznik);
    licznik:=1;
   End
  Else Inc(licznik);
 { Szczegolny przypadek - ostatnie slowo }
 ObsluzSlowo(s[liczbaSlow], licznik);

 Writeln(wyniki,'Liczba slow wystepujacych wiecej niz jeden raz: ', 
   liczbaPowtorzenSlow);
 Writeln(wyniki,'Slowo o najwiekszej liczbie wystapien to: ', 
   najczestszeSlowo);
 Writeln(wyniki,'Liczba jego wystapien jest rowna: ', 
   maxLiczbaWystapien);
End;

Procedure podpunktB;
Var 
 i, licznik : integer;
 ostatniZnak : char;
 liczba : String20;
Begin
 licznik:=0; { liczba liczb parzystych }
 For i:=1 To liczbaSlow Do
  Begin
   liczba:=s[i];
   ostatniZnak:=liczba[length(liczba)];
   If ostatniZnak In ['A','C','E'] Then inc(licznik);
    { sprawdzamy parzystosc ost. pozycji }
  End;
 Writeln(wyniki);
 Writeln(wyniki,'Odpowiedz do podpunktu b)');
 Writeln(wyniki,'Liczb parzystych jest: ', licznik);
End;

Procedure podpunktC;
Var 
 i, licznik: integer;

 Function Palindrom (x:String):boolean;
 Var 
  lewy, prawy: integer;
 Begin
  lewy := 1;
  prawy := Length(x);
  While (lewy < prawy) And (x[lewy]=x[prawy]) Do
   Begin
    Inc(lewy);
    Dec(prawy)
   End;
  Palindrom := lewy >= prawy;
 End;

Begin
  Writeln(wyniki);
  Writeln(wyniki,'Odpowiedz do podpunktu c)');
  licznik:=0;
  For i:=1 To liczbaSlow Do
   If Palindrom(s[i]) Then
    Inc(licznik);
  Writeln(wyniki, 'Liczba palindromow w pliku: ',licznik);
End;


Begin
  wczytajDane;
  Assign(wyniki, 'wyniki.txt'); { utworzenie}
  Rewrite(wyniki);              { pliku wynikowego }
  { wyznaczanie i zapisywanie odpowiedzi do poszczegolnych podpunktow }
  podpunktA;
  podpunktB;
  podpunktC;
  Close(wyniki);
End.
