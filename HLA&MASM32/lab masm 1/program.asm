.386
.model flat, stdcall
option casemap: none

include \masm32\include\windows.inc
include \masm32\include\user32.inc
include \masm32\include\kernel32.inc
includelib \masm32\lib\user32.lib
includelib \masm32\lib\kernel32.lib

.const

.data
sonda db "Sonda studencka", 0
pytanie db "Czy zrozumiales zasady tworzenia komunikatow?", 0
tak db "Mozemy zatem przejsc do nastepnej czesci", 0
nie db "Szkoda, cwicz wiecej", 0
anuluj db "Nie odpowiedziales na pytanie", 0
	
.data?

.code
program:

invoke MessageBox, 0, addr pytanie, addr sonda, MB_YESNOCANCEL or MB_ICONSTOP
.IF (ax == IDYES)
    invoke MessageBox, 0, addr tak, addr sonda, MB_ICONEXCLAMATION
.ELSEIF (eax == IDNO)
    invoke MessageBox, 0, addr nie, addr sonda, MB_OK or MB_ICONEXCLAMATION
.ELSEIF (eax == IDCANCEL)
    invoke MessageBox, 0, addr anuluj, addr sonda, MB_ICONHAND
.ENDIF

invoke ExitProcess, 0
end program