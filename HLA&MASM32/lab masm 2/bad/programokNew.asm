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
    Klasa db "WinClass", 0
    TytulOkna db "Moje pierwsze wymeczone okno c:", 0
.data?
    hInstance HINSTANCE ?
.code
start:
    invoke GetModuleHandle, 0
    mov hInstance, eax
    
    WinMain proc
        LOCAL msg : MSG
        LOCAL KlasaOkna : WNDCLASSEX
            mov KlasaOkna.cbSize, sizeof(WNDCLASSEX)
            mov KlasaOkna.style, CS_HREDRAW or CS_VREDRAW
            mov KlasaOkna.lpfnWndProc, offset WndProc
            push hInstance
            pop KlasaOkna.hInstance
            mov KlasaOkna.hbrBackground, COLOR_WINDOW + 1
            mov KlasaOkna.lpszClassName, offset Klasa
            
            invoke LoadIcon, 0, IDI_APPLICATION
            mov KlasaOkna.hIcon, eax
            mov KlasaOkna.hIconSm, eax
            invoke LoadCursor, 0, IDC_ARROW
            mov KlasaOkna.hCursor, eax

            invoke RegisterClassEx, addr KlasaOkna

            invoke CreateWindowEx,
                0,
                addr Klasa,
                addr TytulOkna,
                WS_OVERLAPPEDWINDOW or WS_VISIBLE,
                100,
                100,
                320,
                200,
                0,
                0,
                hInstance,
                0,

            .WHILE TRUE
                invoke GetMessage, addr msg, 0, 0, 0
                .BREAK .IF(!eax)
                invoke TranslateMessage, addr msg
                invoke DispatchMessage, addr msg
            .ENDW
            ret
    WinMain endp
     
    WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
        .IF (uMsg == WM_DESTROY)
            invoke PostQuitMessage, 0
        .ELSE
            invoke DefWindowProc, hWnd, uMsg, wParam, lParam
            ret
        .ENDIF
    WndProc endp
end start
    
program:
    call WinMain
    invoke ExitProcess, 0
end program