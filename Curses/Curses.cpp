#include <curses.h>
#include <iostream>
#include <ncurses.h>
#include <string>

int main( int argc , char **argv ){
  initscr(); //initialize screen
  curs_set(false); //invisible cursor
  noecho(); //doesn´t show what i'm typing
  //nodelay(stdscr, true); //true means no delay - getch() to not block
  keypad(stdscr, true); //enables the arrow keys

  int windowMaxX = 0;
  int windowMaxY = 0;

  //stdscr = standard screen
  //
  //getmaxyx(stdscr, windowMaxY, windowMaxX);

        //y  //x
  //move(15, 10); //changes cursor position
  //printw("Hello world!");
  //mvprintw(20, 15, "Hello world! (c string)");

  std::string helloString = "c++ string";

  //LINES is the number of rows of our window
  //mvprintw(LINES/2, COLS/2 - helloString.length()/2, helloString.c_str());
  //mvprintw(windowMaxY/2, windowMaxX/2 - helloString.length()/2, helloString.c_str());
  /*
  addch('*'); //add character
  mvaddch(15, 10, '*');

  clear();

  bool quit = false;
  int input;
  while(!quit){
  input = getch(); //read 1 character from input
    if(input == KEY_DOWN)
      quit = true;

    mvprintw(20, 20, "Hello Everyone");
    refresh();

  }
  */ 

  if(!has_colors()){
    endwin();
    std::cout << "Your console doesn't support colors! Too bad..." << std::endl;
    return 0;
  }

  start_color();

  init_pair(1, COLOR_RED, COLOR_BLACK); //the first parameter is an id. 

  attron(A_STANDOUT); 
  attron(A_BOLD);
  attron(COLOR_PAIR(1)); //the id 1
  mvprintw(LINES/2, COLS/2 - helloString.length()/2, helloString.c_str());+

  attroff(A_STANDOUT);
  mvprintw(LINES/2 + 1, COLS/2 - helloString.length()/2, helloString.c_str()); 

  attroff(A_BOLD);
  mvprintw(LINES/2 + 2, COLS/2 - helloString.length()/2, helloString.c_str());


  getch(); //get character (pause)
  
  endwin();

  return 0;
}

