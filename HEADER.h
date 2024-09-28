#include <windows.h>
#include<iostream>
#include<string>
#include<fstream>
#include<chrono>
#include<iomanip>


// ANSI C header [FOR COLORS ONLY]
#define ANSI_COLOR_RESET        "\x1b[0m "
#define ANSI_COLOR_RED          "\x1b[31m"
#define ANSI_COLOR_YELLOW       "\x1b[33m"
#define ANSI_COLOR_GREEN        "\x1b[32m"
#define ANSI_COLOR_BLUE         "\033[34m"
#define ANSI_COLOR_ORANGE       "\033[38;5;208m"
#define ANSI_COLOR_PINK         "\033[38;5;205m"
#define ANSI_COLOR_PURPLE       "\033[38;5;165m"
#define ANSI_COLOR_DARK_GREEN   "\033[38;5;22m"
#define CLEAR_SCREEN            "\x1B[2J\x1B[H"
#define ANSI_COLOR_BOLD_RED   "\033[1;31m"
#define ANSI_COLOR_BOLD_GREEN   "\033[1;32m"



//* LMS TITLE *//
void LMS();

// *[ LOADING LINE FUNCTION ]* //
void LOADING_LINE();

// *CLEAR-SCREEN FUNCTION* //
void clearScreen();


//* BUTTONS MENUE.*//
void buttons();