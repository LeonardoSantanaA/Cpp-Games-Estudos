#include <iostream>
#include <ncurses.h>

int main( int argc , char **argv ){
  initscr(); //initialize screen
  printw("Hello World!");
  refresh();
  getch(); //get character (pause)
  endwin();

  return 0;
}

