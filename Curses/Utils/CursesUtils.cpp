#include "CursesUtils.hpp"

void InitializeCurses(bool noDelay){
  initscr();
  noecho();
  curs_set(false);
  nodelay(stdscr, noDelay);
  keypad(stdscr, true);
}

void ShutdownCurses(){
  endwin();
}

void ClearScreen(){
  clear();
}

void RefreshScreen(){
  refresh();
}

int ScreenWidth(){
  return COLS;
}

int ScreenHeight(){
  return LINES;
}

int GetChar(){
  return getch();
}

void DrawCharacter(int xPos, int yPos, char aCharacter){
  mvaddch(yPos, xPos, aCharacter);
}

void MoveCursor(int xPos, int yPos){
  move(yPos, xPos);
}
