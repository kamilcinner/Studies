Program Figura_zadanie5;

Function g(arg : real) : real;
 Begin
   g := 1 + arg * arg/100 - arg/200;
 End;

Function f(arg : real) : real;
 { Funkcje f liczymy z dodatnim znakiem}
 Begin
  f := arg * arg/50;
 End;



Procedure punkt_a;
{ Ekperymentalne szukanie pola figury F(10) }

Const
 C = 10;
Var
 krok, pole: real;

 Function pole_metoda_trapezow(C, krok : real): real;
 {Obliczanie pola figury F(C) z krokiem "krok"}
 Var
  poz, polef, poleg  : real;
  {poz - pozycja "lewej podstawy trapezu"
   polef - pole pod osia OX
   poleg - pole nad osia OX }
 Begin
  polef := 0;
  poleg := 0;
  poz := 0;
  While poz < C Do
   Begin
    If (poz+krok) > C then krok:= C - poz;
    polef := polef + (f(poz)+f(poz+krok))/2 * krok;
    poleg := poleg + (g(poz)+g(poz+krok))/2 * krok;
    poz := poz + krok;
   End;
  pole_metoda_trapezow := polef + poleg;
 End;

Begin
 Writeln('Podpunkt a)');
 Writeln('Podawaj kolejne kroki dla metody trapezow. Zero konczy eksperyment');
 Write('krok = ');
 Readln(krok);
 While krok <> 0 Do
  Begin
   pole := pole_metoda_trapezow(C, krok);
   Writeln('pole = ', pole:0:10);
   Write('krok = ');
   Readln(krok);
  End;
End;


Procedure punkt_b;
Var x : real;
Begin
 x:=0;
 While (trunc(f(x))+trunc(g(x))) < 26 Do
  x:=x+1;
 Writeln('Podpunkt b)');
 Writeln('Wspolrzedne prostokata to:');
 Writeln('(',x:0:0,',',trunc(g(x)),')');
 Writeln('(',x:0:0,',',trunc(g(x))-26,')');
 Writeln('(',x+100:0:0,',',trunc(g(x)),')');
 Writeln('(',x+100:0:0,',',trunc(g(x))-26,')');
End;


Begin
 punkt_a;
 punkt_b;
End.
