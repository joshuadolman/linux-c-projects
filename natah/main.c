//#include <stdio.h>
#include <stdlib.h>

#include "../_shared/joshua.h"

#include <ncurses.h>
#include <string.h>

#include "colors.c"
#include "timing.c"
//#include <unistd.h>

#define DESIRED_FRAME_RATE 10

global_variable b32 Running = true;

typedef struct Memory {
	void* pointer;
	u64 TotalSize;
	u64 UsedSize;
} Memory;

void PrintLineNumbers(WINDOW* window) {
	i32 windowWidth, windowHeight;
	getmaxyx(window, windowHeight, windowWidth);
	if (windowWidth < 0) {
		windowWidth = 0;
	} else if (windowWidth > 9) {
		windowWidth = 9;
	}
	wattron(window, COLOR_PAIR(BLACK_YELLOW));
	for (i32 i = 0; i < windowHeight; i++) {
		mvwprintw(window, i, 0, "%*.*i", windowWidth, windowWidth, i+1);
	}
	wattroff(window, COLOR_PAIR(BLACK_YELLOW));
}

void PrintTextBuffer(WINDOW* window, Memory buffer) {
	i32 windowWidth, windowHeight;
	getmaxyx(window, windowHeight, windowWidth);
	wattron(window, COLOR_PAIR(BLUE_BLACK));
	wmove(window,0,0);
	for (i32 i = 0; i < buffer.TotalSize; i++) {
		wprintw(window, "%c", *((u8*)(buffer.pointer + i)));
	}
	wattroff(window, COLOR_PAIR(BLUE_BLACK));
}

//#include <math.h>
int main(void)
{   
	initscr();
	noecho();
	cbreak();
	
	if (has_colors()==false) {
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	} else {
		InitialiseColors();
	}
	
	i32 termMaxX, termMaxY;
	getmaxyx(stdscr, termMaxY, termMaxX);
	
	//ncurses windows
	i32 lineNumberWidth = 3;
	i32 marginWidth = 1;
	WINDOW* win_lineNumbers = newwin(termMaxY,lineNumberWidth,0,0);
	WINDOW* win_textBuffer = newwin(termMaxY,termMaxX-lineNumberWidth,0,lineNumberWidth+marginWidth);
	
	Memory buffer = {0};
	buffer.TotalSize = 50;
	buffer.pointer = malloc(buffer.TotalSize);

	FILE* file = fopen("test.txt", "r");

	i32 count = 10;
	i32 elementsRead = fread(buffer.pointer, 1, count, file);

	//memset(buffer.pointer,0,buffer.TotalSize);

	i32 input;

	//timing variables
	f64 MsPerFrame = (1.0f / (f64)DESIRED_FRAME_RATE)*1000;
	f64 beginTime = 0;
	f64 endTime = 0;
	f64 timeElapsed = 0;

	while(Running) {
		beginTime = GetTimingMS();
		getmaxyx(stdscr, termMaxY, termMaxX);
		
		erase();
		
		
		
		PrintLineNumbers(win_lineNumbers);
		PrintTextBuffer(win_textBuffer, buffer);
		//refresh();
		//box(win_lineNumbers,0,0);
		wnoutrefresh(stdscr);
		wnoutrefresh(win_lineNumbers);
		wnoutrefresh(win_textBuffer);
		doupdate();	
		//Check how long this frame has taken so far and then wait for user input
		//for the remainder of the frame time, as set by the DESIRED_FRAME_RATE -joshua 2019/07/14
		endTime = GetTimingMS();
		timeElapsed=endTime-beginTime;
		timeout((i64)(MsPerFrame-timeElapsed));

		input = getch();
		if (input=='q') {
			Running=false;
		} else {
			
		}

		
	}
	
	endwin();
	return 0;
}

void AddCharacterToBuffer(u8 character, Memory buffer) {

}
