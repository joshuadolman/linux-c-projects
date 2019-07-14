#include <stdlib.h>
#include <string.h>

#include <ncurses.h>
#include <utf8proc.h>

#include "../_shared/joshua.h"
#include "colors.c"
#include "timing.c"

#define DESIRED_FRAME_RATE 10

global_variable b32 Running = true;

typedef struct Memory {
	u64 TotalSize;
	u64 UsedSize;
	void* pointer;
} Memory;

void PrintLineNumbers(WINDOW* window) {
	i32 windowWidth, windowHeight;
	getmaxyx(window, windowHeight, windowWidth);
	if (windowWidth < 0) {
		windowWidth = 0;
	} else if (windowWidth > 9) {
		windowWidth = 9;
	}
	wattron(window, COLOR_PAIR(LINE_NUMBERS));
	wattron(window, A_REVERSE);
	for (i32 i = 0; i < windowHeight; i++) {
		mvwprintw(window, i, 0, "%*.*i", windowWidth, windowWidth, i+1);
	}
	wattroff(window, COLOR_PAIR(LINE_NUMBERS));
	wattroff(window, A_REVERSE);
}

void PrintTextBuffer(WINDOW* window, Memory buffer) {
	i32 windowWidth, windowHeight, lineCounter = 0;
	getmaxyx(window, windowHeight, windowWidth);
	wattron(window, COLOR_PAIR(BLACK_WHITE));
	wmove(window,0,0);
	for (i32 i = 0; i < buffer.TotalSize; i++) {
		//if (*((u8*)(buffer.pointer + i)) == '\n') {
		//	lineCounter++;
		//	if (lineCounter > windowHeight) { break; }
		//}
		wprintw(window, "%c", *((u8*)(buffer.pointer + i)));
	}
	wattroff(window, COLOR_PAIR(BLACK_WHITE));
}

void KillOurself(u8* str) {
	endwin();
	printf(str);
	printf("\n");
	exit(1);
}

//returns line count for now -joshua 2019/07/14
i32 ReadFileIntoBuffer(u8* fileName, Memory* buffer) {
	i32 fileSize;
	FILE* file = fopen(fileName, "r");
	if (file) {
		fseek(file,0,SEEK_END);
		fileSize = ftell(file);
		fseek(file,0,SEEK_SET);
	} else {
		KillOurself("Could not open file!");
	}

	i32 lineCount = 0;
	for (int i = 0; i < fileSize; i++) {
		if (!fseek(file,i,SEEK_SET)) {
			if (fgetc(file)=='\n') {
				lineCount++;
			}
		} else {
			KillOurself("fseek failed!");
		}
	}

	fseek(file,0,SEEK_SET);

	buffer->TotalSize = fileSize*2;
	buffer->UsedSize = fileSize;
	buffer->pointer = malloc(buffer->TotalSize);
	i32 elementsRead = fread(buffer->pointer, 1, buffer->TotalSize, file);

	fclose(file);
	return lineCount;
}


int main(int argc, char** argv)
{   
	initscr();
	noecho();
	cbreak();
	//scrollok(stdscr, FALSE);
	use_default_colors();
	
	if (has_colors()==false) {
		KillOurself("Your terminal does not support color!");
	} else {
		InitialiseColors();
	}
	
	if (argc!=2) {
		KillOurself("natah requires exactly 1 argument which is the name of a text file");
	}

	i32 termMaxX, termMaxY;
	getmaxyx(stdscr, termMaxY, termMaxX);
	
	//ncurses windows
	i32 lineNumberWidth = 3;
	i32 marginWidth = 1;
	WINDOW* win_lineNumbers = newwin(termMaxY,lineNumberWidth,0,0);
	WINDOW* win_textBuffer = newwin(termMaxY,termMaxX-lineNumberWidth,0,lineNumberWidth+marginWidth);
	
	
	Memory buffer = {0};
	i32 lineCount = ReadFileIntoBuffer(argv[argc-1], &buffer);

	/*i32 fileSize = 0;
	FILE* file = fopen(argv[argc-1], "r");
	if (file) {
		fseek(file,0,SEEK_END);
		fileSize = ftell(file);
		fseek(file,0,SEEK_SET);
	} else {
		KillOurself("Could not open file!");
	}

	i32 lineCount = 0;
	for (int i = 0; i < fileSize; i++) {
		if (!fseek(file,i,SEEK_SET)) {
			if (fgetc(file)=='\n') {
				lineCount++;
			}
		} else {
			KillOurself("fseek failed!");
		}
	}
	
	fseek(file,0,SEEK_SET);

	
	buffer.TotalSize = fileSize*2;
	buffer.UsedSize = fileSize;
	buffer.pointer = malloc(buffer.TotalSize);
	i32 elementsRead = fread(buffer.pointer, 1, buffer.TotalSize, file);

	//fclose(file);
	*/
	//

	i32 input;

	//timing variables
	f64 MsPerFrame = (1.0f / (f64)DESIRED_FRAME_RATE)*1000;
	f64 beginTime = 0;
	f64 endTime = 0;
	f64 timeElapsed = 0;

	while(Running) {
		beginTime = GetTimingMS();
		getmaxyx(stdscr, termMaxY, termMaxX);
		
		wresize(win_lineNumbers, termMaxY, lineNumberWidth);
		wresize(win_textBuffer, termMaxY, termMaxX-lineNumberWidth-marginWidth);

		erase();
		
		PrintLineNumbers(win_lineNumbers);
		PrintTextBuffer(win_textBuffer, buffer);
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
		} else if (input=='w') {
			ReadFileIntoBuffer("test2.txt", &buffer);
		} else {
			
		}
	}
	
	endwin();
	return 0;
}

void AddCharacterToBuffer(u8 character, Memory buffer) {

}
