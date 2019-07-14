//#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include <unistd.h>

#include <math.h>

#define ITERMAX 5000

int getrandom_int() {
   return (int)sqrt(rand()^2);
}

void triangle() {
  long iter;
  int yi, xi;
  int y[3], x[3];
  int index;
  int maxlines, maxcols;

  initscr();
  cbreak();
  noecho();

  clear();

  maxlines = LINES -1;
  maxcols = COLS -1;

  y[0] = 0;
  x[0] = 0;
  y[1] = maxlines;
  x[1] = maxcols / 2;
  y[2] = 0;
  x[2] = maxcols;

  mvaddch(y[0], x[0], '0');
  mvaddch(y[1], x[1], '1');
  mvaddch(y[2], x[2], '2');

  yi = getrandom_int() % maxlines;
  xi = getrandom_int() % maxcols;

  mvaddch(yi, xi, '.');

  for (iter = 0; iter < ITERMAX; iter++) {
     index=getrandom_int() % 3;

     yi = (yi + y[index]) / 2;
     xi = (xi + x[index]) / 2;

     mvaddch(yi, xi, '*');
     refresh();
  }

  mvaddstr(maxlines, 0, "Press any key to quit");

  refresh();

  getch();
  endwin();
}

int main(void)
{   
   //triangle();
   
   initscr();
   int i = 0;

   while(1) {
      clear();
      printw("%d",i);
      refresh();
      usleep(100 * 1000);
      i++;
   }

   return 0;
}
