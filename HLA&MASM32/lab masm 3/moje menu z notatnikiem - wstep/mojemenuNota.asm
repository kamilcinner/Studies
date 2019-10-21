.386
.model flat,stdcall
option casemap:none

include		\masm32\include\windows.inc
include		\masm32\include\user32.inc
include		\masm32\include\kernel32.inc
include		\masm32\include\gdi32.inc

includelib	\masm32\lib\user32.lib
includelib	\masm32\lib\kernel32.lib
includelib	\masm32\lib\gdi32.lib

.const
IDM_TEST				EQU 1
IDM_ELEMENT1 	EQU 2
IDM_ELEMENT2		EQU 3
IDM_ELEMENT3		EQU 4
IDM_KONIEC			EQU 5

.data
NazwaKlasy		db "WinClass", 0
TytulOkna 			db "Moje pierwsze okienko", 0
NazwaMenu		db "MojePierwszeMenu", 0
napisTestowy	db "Wybrales element Test z menu", 0

char WPARAM 20h ;20h to spacja

.data?
hInstance HINSTANCE ?
hMenu HMENU ?

.code
start:
		invoke GetModuleHandle, 0
		mov    hInstance,eax

		call WinMain
		invoke ExitProcess,  0
	
		WinMain proc
				LOCAL wc:WNDCLASSEX
				LOCAL msg:MSG
				;LOCAL hWnd:HWND
			
				mov   wc.cbSize, SIZEOF WNDCLASSEX
				mov   wc.style, CS_HREDRAW or CS_VREDRAW
				mov   wc.lpfnWndProc, OFFSET WndProc

				push  hInstance
				pop   wc.hInstance

				mov   wc.hbrBackground, COLOR_WINDOW+1
				
				invoke LoadMenu, hInstance, offset NazwaMenu
				mov hMenu, eax
				
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
						hMenu,
						hInstance,
						0
			
				;mov hWnd, eax
				
				;invoke ShowWindow, hWnd, SW_SHOWNORMAL
				;invoke UpdateWindow, hWnd
				
				.WHILE TRUE
						invoke GetMessage, addr msg, 0, 0, 0
						.BREAK .IF (!eax)
						invoke TranslateMessage, addr msg
						invoke DispatchMessage, addr msg
				.ENDW
				mov eax, msg.wParam
				ret
		WinMain endp

		WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
				LOCAL hdc:HDC
				LOCAL ps:PAINTSTRUCT

				.IF uMsg==WM_DESTROY
						invoke PostQuitMessage, 0
				.ELSEIF uMsg==WM_COMMAND
						mov eax, wParam
						.IF eax==IDM_TEST
								invoke MessageBox, hWnd ,addr napisTestowy, offset TytulOkna, MB_OK
						.ELSEIF eax==IDM_KONIEC
								invoke DestroyWindow, hWnd
						.ENDIF
						invoke DefWindowProc, hWnd, uMsg, wParam, lParam		
						ret
				.ELSEIF uMsg==WM_CHAR
						push wParam
						pop char
						invoke InvalidateRect, hWnd, 0, TRUE
				.ELSEIF uMsg==WM_PAINT
						invoke BeginPaint,  hWnd ,addr ps
						mov hdc, eax
						invoke TextOut, hdc, 0, 0, addr char, 1
						invoke EndPaint, hWnd, addr ps
				.ELSE
						invoke DefWindowProc, hWnd, uMsg, wParam, lParam		
						ret
				.ENDIF
				xor eax, eax
				ret
		WndProc endp
end start