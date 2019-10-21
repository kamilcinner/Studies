.386
.model flat,stdcall
option casemap:none

include \masm32\include\windows.inc
include \masm32\include\user32.inc
include \masm32\include\kernel32.inc
includelib \masm32\lib\user32.lib
includelib \masm32\lib\kernel32.lib

.const

.data
tytul db "Nadchodza swieta",0
pytanie db "Czy zakupiles juz prezenty dla najblizszych?",0
tak db "Super, zapewne i Ty dostaniesz!",0
nie db "Nie zapomnij o najblizszych!",0
anuluj db "I tak nie uciekniesz od zakupow",0

.data?
.code
start:
invoke MessageBox,0,addr pytanie, addr tytul, MB_YESNOCANCEL or MB_ICONQUESTION
.IF (eax==IDYES)
    invoke MessageBox,0,addr tak, addr tytul, MB_OK or MB_ICONEXCLAMATION
.ELSEIF (eax==IDNO)
    invoke MessageBox,0,addr nie, addr tytul, MB_OK or MB_ICONEXCLAMATION
.ELSEIF (eax==IDCANCEL)
    invoke MessageBox,0,addr anuluj, addr tytul, MB_OK or MB_ICONERROR
.ENDIF

invoke ExitProcess,0
end start