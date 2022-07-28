
// Console Virtual Terminal Sequences
/* WINDOWS 10 : gcc -Wall -m64 -Os -static main.c vts.c -o questrunner -s */
/* LINUX      : gcc -Wall -m64 -Os -static main.c vts.c linuxfunctions.c -o questrunner -s */

#include "vts.h"

#include "ansiartwork.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESCAPE 27

enum GAMESTATE
{
    MAINMENU = 0,
    NEWGAME,
    OPTIONS,
    RESUMEGAME,
    LOADGAME,
    SAVEGAME,
    QUITGAME
};

void showMenu();
void generateWorld();
void delay(int number_of_seconds);
void getKey();
void spindleCharacters(int h, int v);
void menuBackground();
void newGame();

int spin = 0;
int initialMenu = 1;
enum GAMESTATE getGameState;

int main()
{
    if(initConsoleColors())
    {
        getGameState = MAINMENU;
        hideCursor();
        clearScreen();
        menuBackground();
        while(getGameState != QUITGAME)
        {
            if(getGameState == NEWGAME)
            {
                newGame();
            } else if(getGameState == RESUMEGAME)
            {

            }
            showMenu();
        }
        clearScreen();
        showCursor();
        wprintf(L"\x1b[94mThanks for playing.\n");
        restoreDefaultWindow();
    } else {
        wprintf(L"ERROR: We are unable to initialize the console colors properly.\n");
        return errno;
    }
    return errno;
}

void generateWorld()
{
    wprintf(L"World Generation - Hit ESC to see Menu\n");
}

void newGame()
{
    clearScreen();
    generateWorld();
    while(1)
    {
        getKey();
        if(getGameState != NEWGAME) {break;}
    }
}

void resumeGame()
{
    clearScreen();
    generateWorld();
    while(1)
    {
        getKey();
        if(getGameState != RESUMEGAME) {break;}
    }
}

void spindleCharacters(int h, int v)
{
    setCursorPosition(h, v);
    if(spin == 0) {wprintf(L"\\");}
    if(spin == 1) {wprintf(L"|");}
    if(spin == 2) {wprintf(L"/");}
    if(spin == 3) {wprintf(L"-");}
    spin++;
    if(spin > 3){spin = 0;}
    delay(1);
}

void getKey()
{
    if(kbhit()) // listens if user pressed a key
    {
        switch(getch()) // processes the key input
        {
            case 'q':
            {
                getGameState = QUITGAME;
                break;
            }
            case ESCAPE:
            {
                if(getGameState == NEWGAME || getGameState == RESUMEGAME)
                {
                    getGameState = OPTIONS;
                } else if(getGameState == MAINMENU)
                {
                    getGameState = QUITGAME;
                } else if(getGameState == SAVEGAME || getGameState == LOADGAME)
                {
                    initialMenu = 1;
                    getGameState = MAINMENU;
                } else if(getGameState == OPTIONS)
                {
                    getGameState = RESUMEGAME;
                    resumeGame();
                }
                break;
            }
            case 'm':
            {
                if(getGameState != MAINMENU)
                {
                    initialMenu = 1;
                    getGameState = MAINMENU;
                }
                break;
            }
            case 'n':
            {
                if(getGameState == MAINMENU)
                {
                    initialMenu = 1;
                    getGameState = NEWGAME;
                }
                break;
            }
            case 'l':
            {
                if(getGameState == MAINMENU)
                {
                    initialMenu = 1;
                    getGameState = LOADGAME;
                }
                break;
            }
            case 's':
            {
                if(getGameState == MAINMENU)
                {
                    initialMenu = 1;
                    getGameState = SAVEGAME;
                }
                break;
            }
            case 'r':
            {
                if(getGameState == MAINMENU)
                {
                    getGameState = RESUMEGAME;
                    resumeGame();
                }
                break;
            }
        }
    }
}

void showMenu()
{
    if(getGameState == MAINMENU && initialMenu == 1)
    {
        initialMenu = 0;
        clearRectangle();
        drawRectangle(48, 3, 19, 4, L"\x1b[90m");
        setCursorPosition(53, 3);
        wprintf(L"\x1b[91mMAIN MENU\x1b[0m\n");
        setHorizontalCursorPosition(51);
        wprintf(L"\x1b[94mN = New Game \x1b[0m\n");
        setHorizontalCursorPosition(51);
        wprintf(L"\x1b[94mS = Save Game\x1b[0m\n");
        setHorizontalCursorPosition(51);
        wprintf(L"\x1b[94mL = Load Game\x1b[0m\n");
        setHorizontalCursorPosition(51);
        wprintf(L"\x1b[94mQ = Quit Game\x1b[0m\n");
    } else if(getGameState == NEWGAME && initialMenu == 1)
    {
        initialMenu = 0;
        clearRectangle();
        drawRectangle(48, 3, 28, 3, L"\x1b[90m");
        setCursorPosition(53, 3);
        wprintf(L"\x1b[91mNEW GAME\x1b[0m\n");
        setHorizontalCursorPosition(51);
        wprintf(L"\x1b[94mM = MAIN MENU\x1b[0m\n");
        setHorizontalCursorPosition(51);
        wprintf(L"\x1b[94mQ = Quit Game\x1b[0m\n");
    } else if(getGameState == LOADGAME && initialMenu == 1)
    {
        initialMenu = 0;
        clearRectangle();
        drawRectangle(48, 3, 28, 3, L"\x1b[90m");
        setCursorPosition(53, 3);
        wprintf(L"\x1b[91mLOAD GAME\x1b[0m\n");
        setHorizontalCursorPosition(51);
        wprintf(L"\x1b[94mM = MAIN MENU\x1b[0m\n");
        setHorizontalCursorPosition(51);
        wprintf(L"\x1b[94mQ = Quit Game\x1b[0m\n");
    } else if(getGameState == SAVEGAME && initialMenu == 1)
    {
        initialMenu = 0;
        clearRectangle();
        drawRectangle(48, 3, 24, 3, L"\x1b[90m");
        setCursorPosition(53, 3);
        wprintf(L"\x1b[91mSAVE GAME\x1b[0m\n");
        setHorizontalCursorPosition(51);
        wprintf(L"\x1b[94mM = MAIN MENU\x1b[0m\n");
        setHorizontalCursorPosition(51);
        wprintf(L"\x1b[94mQ = Quit Game\x1b[0m\n");
    } else if(getGameState == OPTIONS)
    {
        drawRectangle(48, 3, 24, 3, L"\x1b[90m");
        setCursorPosition(53, 3);
        wprintf(L"\x1b[91mOPTIONS MENU\x1b[0m\n");
        setHorizontalCursorPosition(51);
        wprintf(L"\x1b[94mM = MAIN MENU\x1b[0m\n");
        setHorizontalCursorPosition(51);
        wprintf(L"\x1b[94mR = RESUME GAME\x1b[0m\n");
        setHorizontalCursorPosition(51);
        wprintf(L"\x1b[94mQ = Quit Game\x1b[0m\n");
    }
    getKey();
    spindleCharacters(49, 4);
}


