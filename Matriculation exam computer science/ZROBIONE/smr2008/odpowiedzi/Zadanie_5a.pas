program Zadanie_5a;

var
 dane      : text;    {Plik z danymi}
 wynik1    : text;    {Plik z zaszyfrowanymi s³owami}
 wynik2    : text;    {Plik z policzonymi odpowiedziami}
 slowo     : string;  {Kolejne s³owo}
 slowo_min : string;  {Dot¹d najkrótsze s³owo}
 slowo_max : string;  {Dot¹d najd³u¿sze s³owo}
 dl        : integer; {D³ugoœc slowo}
 min       : integer; {D³ugoœæ slowo_min}
 max       : integer; {D³ugoœæ slowo_max}


procedure odwroc(var slowo: string);
 {Odwaca kolejnoœæ znaków w slowo}
 var
  l, p   : integer; {Indeksy}
  pom    : char;    {Pomocnicza}
begin
  l     := 1;
  p     := length(slowo);
  while l < p do
   begin
    pom      := slowo[l];
    slowo[l] := slowo[p];
    slowo[p] := pom;
    l := l + 1;
    p := p - 1;
   end; {while}
end; {Odwróæ}

begin
  assign(dane, 'slowa.txt');
  reset(dane);
  assign(wynik1, 'hasla_a.txt');
  rewrite(wynik1);
  assign(wynik2, 'slowa_a.txt');
  rewrite(wynik2);

  min := MaxInt; 
  max := 0;
  while not eof(dane) do
   begin
    readln(dane, slowo);
    odwroc(slowo);
    dl := length(slowo);
    if dl < min then
     begin 
      slowo_min := slowo; 
      min       := dl; 
     end;
    if dl > max then 
     begin 
      slowo_max := slowo; 
      max       := dl; 
     end;
    writeln(wynik1, slowo);
   end; {while}

  close(dane);
  writeln(wynik2, slowo_min, ' ',min);
  writeln(wynik2, slowo_max, ' ',max);
  close(wynik1);
  close(wynik2)
end.
