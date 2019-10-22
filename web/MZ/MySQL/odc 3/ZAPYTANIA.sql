przed WHERE ,
po WHERE AND lub OR

UPDATE klienci SET nazwisko="Psikuta" WHERE idklienta=4
UPDATE ksiazki SET cena=ROUND(cena*1.1, 2)
UPDATE ksiazki SET cena=cena-10 ORDER BY cena DESC LIMIT 1
UPDATE klienci SET imie="Joanna", nazwisko="Dostojewska" WHERE idklienta=10
UPDATE zamowienia SET status="wyslano" WHERE idzamowienia BETWEEN 4 AND 5

INSERT INTO klienci VALUES (NULL, "Franciszek", "Janowski", "Chorzów")
INSERT INTO zamowienia (idzamowienia, data, status, idklienta, idksiazki) VALUES (NULL, "2016-01-01", "oczekiwanie", 7, 3)
INSERT INTO ksiazki (idksiazki, nazwiskoautora, tytul) VALUES (NULL, "Grębosz", "Symfonia C++")
INSERT INTO klienci VALUES (NULL, "Marilyn", "Monroe", "Los Angeles"), (NULL, "John", "Wayne", "Los Angeles")

INSERT INTO klienci SET idklienta=NULL, imie="Steve", nazwisko="McQueen", miejscowosc="Los Angeles"