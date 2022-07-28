#include "vts.h"

struct _MENU_WINDOW {
    int h, v, sizeH, sizeV;
} MENU_WINDOW;

void restoreDefaultWindow()
{
    setDefaultColor();
#ifdef _WIN64
    ShowScrollBar(GetConsoleWindow(), SB_VERT, 1);  // enable scrollbar  (Windows Only)
#endif // _WIN64
}

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
    ShowScrollBar(GetConsoleWindow(), SB_VERT, 0);  // disable scrollbar (Windows Only)
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

void drawRectangle(int h, int v, int sizeH, int sizeV, wchar_t* color)
{
    MENU_WINDOW.h = h;
    MENU_WINDOW.v = v;
    MENU_WINDOW.sizeH = sizeH;
    MENU_WINDOW.sizeV = sizeV;

    wprintf(color);
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

void clearRectangle()
{
    wprintf(L"\x1b[30m");
    for(int t = 0 ; t <= (MENU_WINDOW.sizeV + 1); t++)
    {
        setCursorPosition(MENU_WINDOW.h, MENU_WINDOW.v + t);
        wprintf(L"\x1b[%dX", MENU_WINDOW.sizeH);
    }
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

void delay(int number_of_milliseconds)
{
#ifdef _WIN64
    Sleep(number_of_milliseconds * 60);
    clock_t clock_time = clock();
    while(clock() < clock_time + (number_of_milliseconds * 60));
#else
    usleep(number_of_milliseconds * 5000); // For linux ( might need adjusting )
#endif // _WIN64
}

#ifndef _WIN64   // If not Windows

/* Reads  from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}

int kbhit(void)
{
    static const int STDIN = 0;
    static int initialized = 0;
    if(!initialized)
    {
        // Use termios to turn off line buffering
        struct termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = 1;
    }
    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

#endif // End Not Windows

/*
https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences

ESC = \x1b
EXAMPLE : \x1b[3G --- 3 space to the right

ESC [ <n> A 	  Cursor Up 	Cursor up by <n>
ESC [ <n> B 	  Cursor Down 	Cursor down by <n>
ESC [ <n> C 	  Cursor Forward 	Cursor forward (Right) by <n>
ESC [ <n> D 	  Cursor Backward 	Cursor backward (Left) by <n>
ESC [ <n> E 	  Cursor Next Line 	Cursor down <n> lines from current position
ESC [ <n> F 	  Cursor Previous Line 	Cursor up <n> lines from current position
ESC [ <n> G 	  Cursor Horizontal Absolute 	Cursor moves to <n>th position horizontally in the current line
ESC [ <n> d 	  Vertical Line Position Absolute 	Cursor moves to the <n>th position vertically in the current column

ESC [ <y>;<x> H or f   Cursor Position 	*Cursor moves to <x>;<y> coordinate within the viewport, where <x> is the column of the <y> line

ESC ( 0  Designate Character Set – DEC Line Drawing   Enables DEC Line Drawing Mode
ESC ( B  Designate Character Set – US ASCII           Enables ASCII Mode (Default)

0x6a 	j 	┘
0x6b 	k 	┐
0x6c 	l 	┌
0x6d 	m 	└
0x6e 	n 	┼
0x71 	q 	─
0x74 	t 	├
0x75 	u 	┤
0x76 	v 	┴
0x77 	w 	┬
0x78 	x 	│

0 	Default 	            Returns all attributes to the default state prior to modification
1 	Bold/Bright 	        Applies brightness/intensity flag to foreground color
22 	No bold/bright 	        Removes brightness/intensity flag from foreground color
4 	Underline 	            Adds underline
24 	No underline 	        Removes underline
7 	Negative 	            Swaps foreground and background colors
27 	Positive (No negative) 	Returns foreground/background to normal

30 	Foreground Black 	    Applies non-bold/bright black to foreground
31 	Foreground Red 	        Applies non-bold/bright red to foreground
32 	Foreground Green 	    Applies non-bold/bright green to foreground
33 	Foreground Yellow 	    Applies non-bold/bright yellow to foreground
34 	Foreground Blue 	    Applies non-bold/bright blue to foreground
35 	Foreground Magenta 	    Applies non-bold/bright magenta to foreground
36 	Foreground Cyan 	    Applies non-bold/bright cyan to foreground
37 	Foreground White 	    Applies non-bold/bright white to foreground
38 	Foreground Extended 	Applies extended color value to the foreground (see details below)
39 	Foreground Default 	    Applies only the foreground portion of the defaults (see 0)

40 	Background Black 	    Applies non-bold/bright black to background
41 	Background Red 	        Applies non-bold/bright red to background
42 	Background Green 	    Applies non-bold/bright green to background
43 	Background Yellow 	    Applies non-bold/bright yellow to background
44 	Background Blue 	    Applies non-bold/bright blue to background
45 	Background Magenta 	    Applies non-bold/bright magenta to background
46 	Background Cyan 	    Applies non-bold/bright cyan to background
47 	Background White 	    Applies non-bold/bright white to background
48 	Background Extended 	Applies extended color value to the background (see details below)
49 	Background Default 	    Applies only the background portion of the defaults (see 0)

90 	Bright Foreground Black 	Applies bold/bright black to foreground
91 	Bright Foreground Red 	    Applies bold/bright red to foreground
92 	Bright Foreground Green 	Applies bold/bright green to foreground
93 	Bright Foreground Yellow 	Applies bold/bright yellow to foreground
94 	Bright Foreground Blue 	    Applies bold/bright blue to foreground
95 	Bright Foreground Magenta 	Applies bold/bright magenta to foreground
96 	Bright Foreground Cyan 	    Applies bold/bright cyan to foreground
97 	Bright Foreground White 	Applies bold/bright white to foreground

100 Bright Background Black 	Applies bold/bright black to background
101 Bright Background Red 	    Applies bold/bright red to background
102 Bright Background Green 	Applies bold/bright green to background
103 Bright Background Yellow 	Applies bold/bright yellow to background
104 Bright Background Blue 	    Applies bold/bright blue to background
105 Bright Background Magenta 	Applies bold/bright magenta to background
106 Bright Background Cyan 	    Applies bold/bright cyan to background
107 Bright Background White 	Applies bold/bright white to background
*/
