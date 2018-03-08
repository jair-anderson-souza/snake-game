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

int main(int argc, char const *argv[])
{
	//    printw("Checker board (stipple)     "); addch(ACS_CKBOARD); printw("\n");
    initScreen();

    int ch = getch();
    printw("%d", ch);
    getch();
    killScreen();
    return 0;
}
