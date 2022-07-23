#include "vts.h"

void setDefaultColor()
{
    wprintf(L"\x1b[0m");
}

void setTextColor(int c)
{
    wprintf(L"\x1b[%dm", c);
}

void setBackgroundForgroundColor(int b, int f)
{
    wprintf(L"\x1b[%dm\x1b[%dm", b, f);
}

void setVerticalCursorPosition(int v)
{
    wprintf(L"\x1b[%dd", v);
}

void setHorizontalCursorPosition(int h)
{
    wprintf(L"\x1b[%dG", h);
}

void setCursorPosition(int h, int v)
{
    wprintf(L"\x1b[%d;%dH", v, h);
}

void clearScreen()
{
    wprintf(L"\x1b[2J");
    setCursorPosition(1, 1);
#ifdef _WIN64
    ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);  // disable scrollbar
#endif // _WIN64
}

void showCursor()
{
    wprintf(L"\x1b[?25h");
}

void hideCursor()
{
    wprintf(L"\x1b[?25l");
}

void setTitle(wchar_t* str)
{
    wprintf(L"\x1b]0;%S\x07", str);
}

void drawRectangle(int h, int v, int sizeH, int sizeV)
{
    if(h < 1) {h = 1;}
    if(v < 1) {v = 1;}
    if(sizeH < 1) {sizeH = 1;}
    if(sizeV < 0) {sizeV = 0;}
    setCursorPosition(h, v);
    wprintf(L"\x1b(0l");  /* Left + Set to Line mode */
    int t = 0;
    for(t = h - 1; t < (sizeH + h - 3); t++)
    {
        wprintf(L"\x1b(0q"); /* horizontal lines */
    }
    wprintf(L"\x1b(0k"); /* Right */
    for(t = 0; t < sizeV; t++)
    {
        wprintf(L"\x1b[%dG\x1b[1B\x1b(0x\x1b[%dG\x1b(0x", h, (sizeH + h - 1));  /* Next Line Down + indent */
    }
    wprintf(L"\x1b[%dG\x1b[1B\x1b(0m", h);  /* Left */
    for(t = h - 1; t < (sizeH + h - 3); t++)
    {
        wprintf(L"\x1b(0q"); /* horizontal lines */
    }
    wprintf(L"\x1b(0j\x1b(B"); /* Right + Reset back to ASCII mode */
}

int initConsoleColors()
{
#ifdef _WIN64
    _setmode(_fileno(stdout), _O_U8TEXT);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if(hOut != INVALID_HANDLE_VALUE)
    {
        DWORD dwMode = 0;
        if(GetConsoleMode(hOut, &dwMode))
        {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
            setTitle(L"QUEST RUNNER v0.1");
            ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);  // disable scrollbar
        } else {
            wprintf(L"ERROR : Unable to get console Mode.\n");
            return -1;
        }
    } else {
        wprintf(L"ERROR : Unable to get console Handle.\n");
        return -1;
    }
#else
    setlocale(LC_ALL, "en_US.utf8");   // This sets up unicode for linux in XTERM
#endif
    return 1;
}

