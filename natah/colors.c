#ifndef COLORS_C
	#define COLORS_C

#define BLACK_WHITE 0
#define BLACK_YELLOW 1
#define BLUE_BLACK 2

void InitialiseColors() {
	start_color();
	init_pair(BLACK_WHITE, COLOR_BLACK, COLOR_WHITE);
	init_pair(BLACK_YELLOW, COLOR_BLACK, COLOR_YELLOW);
	init_pair(BLUE_BLACK, COLOR_BLUE, COLOR_BLACK);
}

#endif //COLORS_C