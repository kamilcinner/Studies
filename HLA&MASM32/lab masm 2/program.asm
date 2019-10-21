.386
.model flat,stdcall
option casemap:none

include \masm32\include\windows.inc
include \masm32\include\user32.inc
include \masm32\include\kernel32.inc
includelib \masm32\lib\user32.lib
includelib \masm32\lib\kernel32.lib

.data
ClassName db "SimpleWinClass",0
AppName  db "Our First Window",0

.data?
hInstance dd ?

.code
start:
	invoke GetModuleHandle, NULL
	mov    hInstance,eax

    call WinMain
    invoke ExitProcess,0

WinMain proc
	LOCAL wc:WNDCLASSEX
	LOCAL msg:MSG
	LOCAL hwnd:HWND
	
	mov   wc.cbSize, SIZEOF WNDCLASSEX
	mov   wc.style, CS_HREDRAW or CS_VREDRAW
	mov   wc.lpfnWndProc, OFFSET WndProc
	push  hInstance
	pop   wc.hInstance
	mov   wc.hbrBackground, COLOR_WINDOW+1
	mov   wc.lpszClassName, OFFSET ClassName

	invoke LoadIcon, NULL, IDI_APPLICATION
	mov   wc.hIcon, eax
	mov   wc.hIconSm, eax
	invoke LoadCursor, NULL, IDC_ARROW
	mov   wc.hCursor, eax

	invoke RegisterClassEx, addr wc

	invoke CreateWindowEx,
        0,
        ADDR ClassName,
        ADDR AppName,
        WS_OVERLAPPEDWINDOW,
        100,
        100,
        320,
        200,
        0,
        0,
        hInstance,
        0

	mov   hwnd, eax
	invoke ShowWindow, hwnd, SW_SHOWNORMAL
	
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
	.else
		invoke DefWindowProc, hWnd, uMsg, wParam, lParam		
		ret
	.endif
WndProc endp

end start