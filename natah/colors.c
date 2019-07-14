#ifndef COLORS_C
	#define COLORS_C

#define COLOR_BLACK_D 0
#define COLOR_BLACK_L 8
#define COLOR_RED_L 9

#define BLACK_WHITE 0
#define BLACK_YELLOW 1
#define BLUE_BLACK 2
#define TEST 3
#define LINE_NUMBERS 4

void InitialiseColors() {
	start_color();
	init_pair(BLACK_WHITE, -1, -1);
	init_pair(LINE_NUMBERS, COLOR_YELLOW, -1);
	init_pair(BLUE_BLACK, COLOR_RED_L, -1);
	init_pair(TEST, 1, COLOR_BLACK_D);
}

#endif //COLORS_C