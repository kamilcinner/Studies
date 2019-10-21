.386
.model flat,stdcall
option casemap:none

include \masm32\include\windows.inc
include \masm32\include\user32.inc
include \masm32\include\kernel32.inc
includelib \masm32\lib\user32.lib
includelib \masm32\lib\kernel32.lib

.const
IDM_TEST				EQU 1
IDM_ELEMENT1 	EQU 2
IDM_ELEMENT2		EQU 3
IDM_ELEMENT3		EQU 4
IDM_KONIEC			EQU 5

.data
NazwaKlasy db "WinClass",0
TytulOkna  db "Moje pierwsze okienko",0
NazwaMenu db "MojePierwszeMenu",0
napisTestowy db "Wybrales element Test z menu",0

.data?
hInstance HINSTANCE ?
hMenu HMENU ?
;hWnd HWND ?

.code
start:
    invoke GetModuleHandle, NULL
    mov    hInstance,eax

    call WinMain
    invoke ExitProcess,0
	
WinMain proc
	LOCAL wc:WNDCLASSEX
	LOCAL msg:MSG
	
	mov   wc.cbSize, SIZEOF WNDCLASSEX
	mov   wc.style, CS_HREDRAW or CS_VREDRAW
	mov   wc.lpfnWndProc, OFFSET WndProc

	push  hInstance
	pop   wc.hInstance

	mov   wc.hbrBackground, COLOR_WINDOW+1
	
	invoke LoadMenu, hInstance, offset NazwaMenu
	mov hMenu, eax
	;mov wc.lpszMenuName, OFFSET NazwaMenu
	
	mov   wc.lpszClassName, OFFSET NazwaKlasy

	invoke LoadIcon, NULL, IDI_APPLICATION
	mov   wc.hIcon, eax
	mov   wc.hIconSm, eax

	invoke LoadCursor, NULL, IDC_ARROW
	mov   wc.hCursor, eax

	invoke RegisterClassEx, addr wc

	invoke CreateWindowEx,
        0,
        ADDR NazwaKlasy,
        ADDR TytulOkna,
        WS_OVERLAPPEDWINDOW or WS_VISIBLE,
        100,
        100,
        350,
        200,
        0,
        hMenu, ;0,
        hInstance,
        0
	
	;mov hWnd, eax
	
	.WHILE TRUE
		invoke GetMessage, ADDR msg, 0, 0, 0
		.BREAK .IF (!eax)
		invoke TranslateMessage, ADDR msg
		invoke DispatchMessage, ADDR msg
	.ENDW
	ret
WinMain endp

WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
	.if uMsg==WM_DESTROY
		invoke PostQuitMessage, 0
	.elseif uMsg==WM_COMMAND
		mov eax, wParam
		.if eax==IDM_TEST
			invoke MessageBox,hWnd,addr napisTestowy,offset TytulOkna, MB_OK
		.elseif eax==IDM_KONIEC
			invoke DestroyWindow, hWnd
		.endif
		invoke DefWindowProc, hWnd, uMsg, wParam, lParam		
		ret
	.else
		invoke DefWindowProc, hWnd, uMsg, wParam, lParam		
		ret
	.endif
WndProc endp

end start