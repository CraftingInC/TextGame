#ifndef _VTS_H_
#define _VTS_H_

#define UNICODE
#include <errno.h>        // errno
#include <time.h>         // clock_t  clock()
#include <stdio.h>        // stdout  _fileno  wprintf()  LINUX --> getchar()

#ifdef _WIN64
#include <windows.h>      // HANDLE   DWORD   STD_OUTPUT_HANDLE   INVALID_HANDLE_VALUE   GetStdHandle()
                          // GetConsoleMode()   SetConsoleMode()    ENABLE_VIRTUAL_TERMINAL_PROCESSING
#include <fcntl.h>        // _setmode()   _O_U8TEXT
#include <stdio.h>        // stdout  _fileno  wprintf()
#include <conio.h>        // kbhit()    getch()
#else
#include "linuxfunctions.h"
#endif

int initConsoleColors();
void drawRectangle(int h, int v, int sizeH, int sizeV);
void clearScreen();
void setVerticalCursorPosition(int v);
void setHorizontalCursorPosition(int h);
void setCursorPosition(int h, int v);
void setBackgroundForgroundColor(int b, int f);
void setTextColor(int c);
void setDefaultColor();
void showCursor();
void hideCursor();
void setTitle(wchar_t* str);

#endif // _VTS_H_

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
