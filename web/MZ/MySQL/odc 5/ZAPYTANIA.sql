DELETE FROM zamowienia WHERE idzamowienia = 2
DELETE FROM zamowienia

DELETE FROM slowa_kluczowe
TRUNCATE TABLE slowa_kluczowe

DELETE FROM klienci ORDER BY idklienta DESC LIMIT 5
DROP DATABASE ksiegarnia
DROP TABLE klienci
DROP TABLE IF EXIST klienci
