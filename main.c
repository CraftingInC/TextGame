
// Console Virtual Terminal Sequences
/* WINDOWS : gcc -Wall -m64 -Os -static main.c vts.c -o questrunner -s */
/* LINUX   : gcc -Wall -m64 -Os -static main.c vts.c linuxfunctions.c -o questrunner -s */

#include "vts.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESCAPE 27
#define GAMEVERSION 0.1

enum GAMESTATE
{
    MAINMENU = 0,
    NEWGAME,
    LOADGAME,
    GENERATE,
    GAMELOOP,
    QUITGAME
};

void showMenu();
void showMainScreen();
void gameLoop();
void generateWorld();
void delay(int number_of_seconds);
void getKey();
void spindleCharacters(int h, int v);
void menuBackground();

int spin = 0;
enum GAMESTATE getGameState;

int main()
{
    if(initConsoleColors())
    {
        getGameState = MAINMENU;
        hideCursor();
        while(getGameState != QUITGAME)
        {
            gameLoop();
        }
        clearScreen();
        showCursor();
        wprintf(L"\x1b[94mThanks for playing.\n");
        setDefaultColor();
#ifdef _WIN64
        ShowScrollBar(GetConsoleWindow(), SB_VERT, 1);  // disable scrollbar
#endif // _WIN64
    } else {
        wprintf(L"ERROR: We are unable to initialize the console colors properly.\n");
        return errno;
    }

    return errno;
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
        switch(getch()) // takes the key input
        {
            case 'q':
            {
                getGameState = QUITGAME;
                break;
            }
            case ESCAPE:
            {
                getGameState = QUITGAME;  // Fix this per menu levels
                break;
            }
            case 'm':
            {
                getGameState = MAINMENU;
                break;
            }
            case 'n':
            {
                if(getGameState == MAINMENU)
                {
                    getGameState = NEWGAME;
                }
                break;
            }
            case 'l':
            {
                if(getGameState == MAINMENU)
                {
                    getGameState = LOADGAME;
                }
                break;
            }
        }
    }
}

void gameLoop()
{
    showMenu();
}

void generateWorld()
{

}

void showMainScreen()
{

}

void showMenu()
{
    clearScreen();
    menuBackground();
    wprintf(L"\x1b[90m");
    if(getGameState == MAINMENU)
    {
        drawRectangle(48, 3, 19, 4);
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
        while(getGameState == MAINMENU)
        {
            getKey();
            if(getGameState != QUITGAME || getGameState != NEWGAME) {spindleCharacters(49, 4);}
        }
    } else if(getGameState == NEWGAME)
    {
        drawRectangle(48, 3, 28, 5);
        setCursorPosition(53, 3);
        wprintf(L"\x1b[91mNEW GAME\x1b[0m\n");
        setHorizontalCursorPosition(51);
        wprintf(L"\x1b[94mG = Generate Character \x1b[0m\n");
        setHorizontalCursorPosition(51);
        wprintf(L"\x1b[94mM = MAIN MENU\x1b[0m\n");
        setHorizontalCursorPosition(51);
        wprintf(L"\x1b[94mQ = Quit Game\x1b[0m\n");
        while(getGameState == NEWGAME)
        {
            getKey();
            if(getGameState != QUITGAME || getGameState != MAINMENU) {spindleCharacters(49, 4);}
        }
    }
}

void delay(int number_of_milliseconds)
{
#ifdef _WIN64
    Sleep(number_of_milliseconds * 60);
    clock_t clock_time = clock();
    while(clock() < clock_time + (number_of_milliseconds * 60));
#else
    usleep(number_of_milliseconds * 5000);
#endif // _WIN64
}

void menuBackground()
{
    wprintf(L"\n\n\
    \x1b[93m█████   █    ██ \x1b[91m▓\x1b[93m█████   ██████ ▄▄▄█████\x1b[91m▓             \n\
  \x1b[31m▒\x1b[93m██\x1b[91m▓\x1b[93m  ██\x1b[31m▒ \x1b[93m██  \x1b[91m▓\x1b[93m██\x1b[31m▒\x1b[91m▓\x1b[93m█   ▀ \x1b[31m▒\x1b[93m██    \x1b[31m▒ \x1b[91m▓  \x1b[93m██\x1b[31m▒ \x1b[91m▓\x1b[31m▒             \n\
  ▒\x1b[93m██\x1b[31m▒  \x1b[93m██\x1b[31m░\x1b[91m▓\x1b[93m██  \x1b[91m▒\x1b[93m██\x1b[91m░▒\x1b[93m███   \x1b[91m░ ▓\x1b[93m██▄ \x1b[91m  ▒ ▓\x1b[93m██\x1b[91m░ ▒░             \n\
  ░\x1b[93m██  █▀ \x1b[91m░▓▓\x1b[93m█  \x1b[31m░\x1b[93m██\x1b[91m░▒▓\x1b[93m█  ▄   \x1b[91m▒   \x1b[93m██\x1b[91m▒░ ▓\x1b[93m██\x1b[91m▓ ░              \n\
  ░▒\x1b[93m███\x1b[91m▒\x1b[93m█▄ \x1b[91m▒▒\x1b[93m█████\x1b[91m▓ ░▒\x1b[93m████\x1b[91m▒▒\x1b[93m██████\x1b[91m▒▒  ▒\x1b[93m██\x1b[91m▒ ░            \n\
  \x1b[31m░░ ▒▒░ ▒ ░▒▓▒ ▒ ▒ ░░ ▒░ ░▒ ▒▓▒ ▒ ░  ▒ ░░\n\
   ░ ▒░  ░ ░░▒░ ░ ░  ░ ░  ░░ ░▒  ░ ░    ░             \x1b[95mv%.1f\x1b[31m\n\
     ░   ░  ░░░ ░ ░    ░   ░  ░  ░    ░                   \n\
      ░       ░        ░  ░      ░                        \n\n\
     \x1b[93m██▀███   █    ██  ███▄    █  ███▄    █ \x1b[91m▓\x1b[93m█████  ██▀███  \n\
    \x1b[91m▓\x1b[93m██ \x1b[91m▒ \x1b[93m██\x1b[91m▒ \x1b[93m██  \x1b[91m▓\x1b[93m██\x1b[31m▒ \x1b[93m██ ▀█   █  ██ ▀█   █ \x1b[91m▓\x1b[93m█   ▀ \x1b[91m▓\x1b[93m██ \x1b[91m▒ \x1b[93m██\x1b[91m▒\n\
    ▓\x1b[93m██ \x1b[31m░\x1b[93m▄█ \x1b[91m▒▓\x1b[93m██  \x1b[91m▒\x1b[93m██\x1b[31m░\x1b[91m▓\x1b[93m██  ▀█ ██\x1b[31m▒\x1b[91m▓\x1b[93m██  ▀█ ██\x1b[91m▒▒\x1b[93m███   \x1b[91m▓\x1b[93m██ \x1b[31m░\x1b[93m▄█ \x1b[91m▒\n\
    ▒\x1b[93m██▀▀█▄  \x1b[91m▓▓\x1b[93m█  \x1b[31m░\x1b[93m██\x1b[31m░\x1b[91m▓\x1b[93m██\x1b[91m▒  \x1b[93m▐▌██\x1b[91m▒▓\x1b[93m██\x1b[91m▒  \x1b[93m▐▌██\x1b[91m▒▒▓\x1b[93m█  ▄ \x1b[91m▒\x1b[93m██▀▀█▄  \n\
    \x1b[31m░\x1b[93m██\x1b[91m▓ ▒\x1b[93m██\x1b[91m▒▒▒\x1b[93m█████\x1b[91m▓ ▒\x1b[93m██\x1b[31m░   \x1b[91m▓\x1b[93m██\x1b[31m░▒\x1b[93m██\x1b[31m░   \x1b[91m▓\x1b[93m██\x1b[91m░░▒\x1b[93m████\x1b[91m▒\x1b[31m░\x1b[93m██\x1b[91m▓ ▒\x1b[93m██\x1b[91m▒\n\
    \x1b[31m░ ▒▓ ░▒▓░░▒▓\x1b[91m▒ ▒ ▒ \x1b[31m░ \x1b[91m▒\x1b[31m░\x1b[91m   ▒ ▒ \x1b[31m░ \x1b[91m▒\x1b[31m░   \x1b[91m▒ ▒ \x1b[31m░░ \x1b[91m▒\x1b[31m░ ░░ ▒\x1b[91m▓ \x1b[31m░\x1b[91m▒\x1b[91m▓\x1b[31m░\n\
      ░\x1b[91m▒ \x1b[31m░ \x1b[91m▒\x1b[31m░░░\x1b[91m▒\x1b[31m░ ░ ░ ░ ░░   ░ \x1b[91m▒\x1b[31m░░ ░░   ░ \x1b[91m▒\x1b[31m░ ░ ░  ░  ░\x1b[91m▒\x1b[31m ░ \x1b[91m▒\x1b[31m░\n\
      ░░   ░  ░░░ ░ ░    ░   ░ ░    ░   ░ ░    ░     ░░   ░ \n\
       ░        ░ \x1b[92mCraftingInC 2022 \x1b[31m     ░       ░   ░     \x1b[0m\
", GAMEVERSION);
}


