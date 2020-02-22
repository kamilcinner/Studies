.386

.MODEL FLAT, STDCALL

OPTION CASEMAP:NONE

WinMain PROTO :DWORD, :DWORD, :DWORD, :DWORD

INCLUDE    \masm32\include\windows.inc
INCLUDE    \masm32\include\user32.inc
INCLUDE    \masm32\include\kernel32.inc
INCLUDE    \masm32\include\gdi32.inc
INCLUDELIB \masm32\lib\user32.lib
INCLUDELIB \masm32\lib\kernel32.lib
INCLUDELIB \masm32\lib\gdi32.lib

.DATA

ClassName DB "SimpleWinClass",0
AppName   DB "Tekst z klawiatury",0
char WPARAM 20h

.DATA?

hInstance   HINSTANCE ?
CommandLine LPSTR     ?

.CODE

start:
	INVOKE GetModuleHandle, NULL
	mov    hInstance, eax
	INVOKE GetCommandLine
	mov    CommandLine, eax
	INVOKE WinMain, hInstance, NULL, CommandLine, SW_SHOWDEFAULT
	INVOKE ExitProcess, eax

WinMain PROC hInst:     HINSTANCE,\
             hPrevInst: HINSTANCE,\
             CmdLine:   LPSTR,\
             CmdShow:   DWORD

LOCAL wc:   WNDCLASSEX
LOCAL msg:  MSG
LOCAL hwnd: HWND

	mov    wc.cbSize, SIZEOF WNDCLASSEX
	mov    wc.style, CS_HREDRAW OR CS_VREDRAW
	mov    wc.lpfnWndProc, OFFSET WndProc
	mov    wc.cbClsExtra, NULL
	mov    wc.cbWndExtra, NULL
	push   hInst
	pop    wc.hInstance
	mov    wc.hbrBackground, COLOR_WINDOW+1
	mov    wc.lpszMenuName, NULL
	mov    wc.lpszClassName, OFFSET ClassName
	INVOKE LoadIcon, NULL, IDI_APPLICATION
	mov    wc.hIcon, eax
	mov    wc.hIconSm, eax
	INVOKE LoadCursor, NULL, IDC_ARROW
	mov    wc.hCursor, eax
	INVOKE RegisterClassEx, ADDR wc
	INVOKE CreateWindowEx, NULL, ADDR ClassName, ADDR AppName,\
           WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,\
           CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,\
           hInst, NULL
	mov    hwnd, eax
	INVOKE ShowWindow, hwnd, SW_SHOWNORMAL
	INVOKE UpdateWindow, hwnd
	.WHILE TRUE
        INVOKE GetMessage, ADDR msg, NULL, 0, 0
        .BREAK .IF (!eax)
        INVOKE TranslateMessage, ADDR msg
        INVOKE DispatchMessage,  ADDR msg
	.ENDW
	mov eax, msg.wParam
	ret
WinMain ENDP

WndProc PROC hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

LOCAL hdc: HDC
LOCAL ps:  PAINTSTRUCT

	.IF uMsg==WM_DESTROY
		INVOKE PostQuitMessage, NULL
	.ELSEIF uMsg==WM_CHAR
		push   wParam
		pop    char
		INVOKE InvalidateRect, hWnd, NULL, TRUE
	.ELSEIF uMsg==WM_PAINT
		INVOKE BeginPaint, hWnd, ADDR ps
		mov    hdc, eax
		INVOKE TextOut, hdc, 0, 0, ADDR char, 1
		INVOKE EndPaint, hWnd, ADDR ps
	.ELSE
		INVOKE DefWindowProc, hWnd, uMsg, wParam, lParam
		ret
	.ENDIF
	xor    eax, eax
	ret

WndProc ENDP

END start
