
#ifndef _ANSI_ARTWORK_H_
#define _ANSI_ARTWORK_H_

#include <stdio.h>
#define GAMEVERSION 0.1

void gameInterface()
{
    wprintf(L"");
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

#endif // _ANSI_ARTWORK_H_
