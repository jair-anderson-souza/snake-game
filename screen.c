#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>


int setupScreen(){
	noecho();	
	raw();
	return 1;
}
void initScreen(){
	initscr();
	setupScreen();
}


void killScreen(){
	endwin();
}



