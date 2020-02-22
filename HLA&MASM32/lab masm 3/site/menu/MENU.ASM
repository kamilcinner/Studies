.386

.MODEL FLAT,STDCALL

OPTION CASEMAP:NONE

WinMain PROTO :DWORD, :DWORD, :DWORD, :DWORD

INCLUDE    \masm32\include\windows.inc
INCLUDE    \masm32\include\user32.inc
INCLUDE    \masm32\include\kernel32.inc
INCLUDELIB \masm32\lib\user32.lib
INCLUDELIB \masm32\lib\kernel32.lib

.DATA

ClassName      DB "SimpleWinClass",0
AppName        DB "Nasze Pierwsze Okno",0
MenuName       DB "FirstMenu",0
Test_string    DB "Wybra³eœ element Test z menu",0
Hello_string   DB "Witaj, mój przyjacielu",0
Goodbye_string DB "Do zobaczenia, czeœæ",0

.DATA?

hInstance   HINSTANCE ?
CommandLine LPSTR     ?

.CONST

IDM_TEST    EQU 1
IDM_HELLO   EQU 2
IDM_GOODBYE EQU 3
IDM_EXIT    EQU 4

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

LOCAL wc:WNDCLASSEX
LOCAL msg:MSG
LOCAL hwnd:HWND

    mov    wc.cbSize, SIZEOF WNDCLASSEX
    mov    wc.style, CS_HREDRAW OR CS_VREDRAW
    mov    wc.lpfnWndProc, OFFSET WndProc
    mov    wc.cbClsExtra, NULL
    mov    wc.cbWndExtra, NULL
    push   hInst
    pop    wc.hInstance
    mov    wc.hbrBackground, COLOR_WINDOW+1
    mov    wc.lpszMenuName, OFFSET MenuName
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
    INVOKE ShowWindow, hwnd,SW_SHOWNORMAL
    INVOKE UpdateWindow, hwnd

    .WHILE TRUE
        INVOKE GetMessage, ADDR msg, NULL, 0, 0
        .BREAK .IF (!eax)
        INVOKE DispatchMessage, ADDR msg
    .ENDW

    mov    eax,msg.wParam
    ret
    
WinMain ENDP

WndProc PROC hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM

    .IF uMsg==WM_DESTROY
        INVOKE PostQuitMessage, NULL
    .ELSEIF uMsg==WM_COMMAND
        mov eax,wParam
        .IF ax==IDM_TEST
            INVOKE MessageBox, NULL, ADDR Test_string, OFFSET AppName, MB_OK
        .ELSEIF ax==IDM_HELLO
            INVOKE MessageBox, NULL, ADDR Hello_string, OFFSET AppName, MB_OK
        .ELSEIF ax==IDM_GOODBYE
            INVOKE MessageBox, NULL, ADDR Goodbye_string, OFFSET AppName, MB_OK
        .ELSE
            INVOKE DestroyWindow, hWnd
        .ENDIF
    .ELSE
        INVOKE DefWindowProc, hWnd, uMsg, wParam, lParam
        ret
    .ENDIF

    xor eax, eax
    ret
    
WndProc ENDP

END start
