#ifndef NCURSES_DISPLAY_H
#define NCURSES_DISPLAY_H

#include <curses.h>

#include "process.h"
#include "system.h"

namespace NCursesDisplay {
void Display(System& system, int n = 10);
void DisplaySystem(System& system, WINDOW* window);
void DisplayProcesses(std::vector<Process>& processes, WINDOW* window, int n);
std::string ProgressBar(float percent);
const char* mytext[] = {"            .-/+oo    oo+/-.               ",
                        "        `:+                  +:`           ",
                        "      -+                  yy    +-         ",
                        "    .o                  dMMMNy    o.       ",
                        "   /           hdmmNNmmyNMMMMh      /      ",
                        "  +         hmydMMMMMMMNddddy        +     ",
                        " /        hNMMMyhhyyyyhmNMMMNh        /    ",
                        ".        dMMMNh          hNMMMd        .   ",
                        "+    hhhyNMMNy            yNMMMy       +   ",
                        "o  yNMMMNyMMh              hmmmh       o           "
                        "Author: Alejandro  armiento :=)",
                        "o  yNMMMNyMMh              hmmmh       o   ",
                        "+    hhhyNMMNy            yNMMMy       +   ",
                        ".        dMMMNh          hNMMMd        .   ",
                        " /        hNMMMyhhyyyyhdNMMMNh        /    ",
                        "  +         dmydMMMMMMMMddddy        +     ",
                        "   /           hdmNNNNmyNMMMMh      /      ",
                        "    .o                  dMMMNy    o.       ",
                        "      -+                 yyy    +-         ",
                        "        `:+                  +:`           ",
                        "            .-/+oo    oo+/-.               "};

};  // namespace NCursesDisplay

#endif