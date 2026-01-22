#define UNICODE
#include <windows.h>
#include <stdio.h>

#define ID_BUTTON_HELLO   1
#define ID_BUTTON_EXIT    2
#define ID_BUTTON_PRINT  3
#define ID_EDIT_TEXT     4

HWND hEdit;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
        // Edit (text field)
        hEdit = CreateWindowW(
            L"EDIT",
            L"",
            WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            50, 30, 180, 25,
            hwnd,
            (HMENU)ID_EDIT_TEXT,
            NULL,
            NULL
        );

        // Print button
        CreateWindowW(
            L"BUTTON",
            L"Print Text",
            WS_VISIBLE | WS_CHILD,
            50, 70, 120, 30,
            hwnd,
            (HMENU)ID_BUTTON_PRINT,
            NULL,
            NULL
        );

        // Hello button
        CreateWindowW(
            L"BUTTON",
            L"Say Hello",
            WS_VISIBLE | WS_CHILD,
            50, 110, 120, 30,
            hwnd,
            (HMENU)ID_BUTTON_HELLO,
            NULL,
            NULL
        );

        // Exit button
        CreateWindowW(
            L"BUTTON",
            L"Exit",
            WS_VISIBLE | WS_CHILD,
            50, 150, 120, 30,
            hwnd,
            (HMENU)ID_BUTTON_EXIT,
            NULL,
            NULL
        );
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_BUTTON_PRINT:
        {
            wchar_t buffer[256];
            GetWindowTextW(hEdit, buffer, 256);
            wprintf(L"Text field says: %ls\n", buffer);
            break;
        }

        case ID_BUTTON_HELLO:
            MessageBoxW(hwnd, L"Hello from Win32!", L"Message", MB_OK);
            break;

        case ID_BUTTON_EXIT:
            PostQuitMessage(0);
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProcW(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI wWinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    PWSTR lpCmdLine,
    int nCmdShow
)
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    WNDCLASSW wc = {0};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = L"MyWindowClass";

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0,
        L"MyWindowClass",
        L"Simple Win32 Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        300, 260,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while (GetMessageW(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return 0;
}
