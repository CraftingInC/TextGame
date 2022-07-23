#ifndef _LINUX_FUNCTIONS_H_
#define _LINUX_FUNCTIONS_H_

#ifndef _WIN64
#include <termios.h>
#include <stdio.h>        // stdout  _fileno  wprintf()  LINUX --> getchar()
#include <wchar.h>        // wprintf()
#include <locale.h>       // setlocale()   LC_ALL
#include <unistd.h>       // usleep()
#include <sys/ioctl.h>
#include <sys/select.h>

int getch(void);
int kbhit(void);
#endif // _WIN64

#endif // _LINUX_FUNCTIONS_H_


