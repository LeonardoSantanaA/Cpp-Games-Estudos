#include <curses.h>
#include <iostream>
#include <ncurses.h>
#include <string>

int main( int argc , char **argv ){
  initscr(); //initialize screen
  curs_set(false); //invisible cursor

  int windowMaxX = 0;
  int windowMaxY = 0;

  //stdscr = standard screen
  //
  getmaxyx(stdscr, windowMaxY, windowMaxX);

        //y  //x
  //move(15, 10); //changes cursor position
  //printw("Hello world!");
  //mvprintw(20, 15, "Hello world! (c string)");

  std::string helloString = "c++ string";
  //LINES is the number of rows of our window
  //mvprintw(LINES/2, COLS/2 - helloString.length()/2, helloString.c_str());
  //mvprintw(windowMaxY/2, windowMaxX/2 - helloString.length()/2, helloString.c_str());

  addch('*'); //add character
  mvaddch(15, 10, '*');

  clear();

  refresh();
  getch(); //get character (pause)
  endwin();

  return 0;
}

