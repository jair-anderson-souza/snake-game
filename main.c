#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

typedef struct snake Snake;
struct snake{
	int coordinatey;
	int coordinatex;
	Snake* next;
};

typedef struct screen Screen;
struct screen{
	Snake* snake;
	int coordinatey;
	int coordinatex;
};

int xmax, ymax;
	

void drawMenu(){
	int coordx = (COLS / 2) - 1;
	int coordy = (LINES / 2) - 1;
	mvprintw(coordy, coordx-9, "Snake Game");
	mvprintw(coordy+1, coordx-14, "Press Enter to Start");
	mvprintw(coordy+2, coordx-12, "Press ESC to Exit");
}

void draw(int *ymax, int *xmax){
	initscr();
	noecho();	
	cbreak();
	keypad(stdscr, TRUE); //teclas do teclado funcionarem
	curs_set(0); //desabilitar cursor
	timeout(5000);
	getmaxyx(stdscr, *ymax, *xmax); // recupera as as coordenadas da tela -1
}

void killScreen(){
	endwin();
}

void freeSnake(Snake* snake){
	free(snake);
}

void freeBoard(Screen* screen){
    free(screen);
}

void shutdown(Screen* screen){
	printw("O programa foi finalizado, aperte Enter pra sair!!");
	getch();
	freeSnake(screen->snake);
	freeBoard(screen);
	killScreen();
}

Screen* createScreen(Snake* snake, int y, int x){
	Screen* screen = (Screen*) malloc(sizeof(Screen));	
	if(screen != NULL){
		screen->coordinatey = y;
		screen->coordinatex = x;
		screen->snake = snake;
		return screen;
	}
	//lembrar de pesquisar como mandar erro pra tela
	return NULL;
	
}
//return some error e.g.
Snake* createSnake(int y, int x){
	Snake* snake = (Snake*) malloc(sizeof(Snake));	
	if(snake != NULL){
		snake->coordinatey = y;
		snake->coordinatex = x;
		return snake;
	}
	
}

void display_points(Snake* snake) {
  while(snake != NULL) {
	mvaddch(snake->coordinatey, snake->coordinatex, ACS_DIAMOND);
    snake = snake->next;
  }
}

void display_points2(Snake* snake) {
  

}

int main(int argc, char const *argv[]){	
	draw(&ymax, &xmax);
    
	Screen* screen = createScreen(createSnake(ymax, xmax), ymax, xmax);

	//Essa função é o Menu que eu ainda pretendo fazer
	//drawMenu();

	mvaddch(screen->snake->coordinatey-1, screen->snake->coordinatex-1, ACS_BLOCK);
	refresh();





	/*while(true) {
    	int key = getch();
    	switch(key){
    		case KEY_LEFT:
    			display_points(screen->snake);
				refresh();
				display_points2(screen->snake);
				break;
    		case KEY_RIGHT:
				display_points(screen->snake);
    			refresh();
				break;
    		case KEY_UP:
    			display_points(screen->snake);
				refresh();
				break;
    		case KEY_DOWN:
				display_points(screen->snake);
    			refresh();
				break;
    	}
	}
//27 ESC
//10 ENTER

	//if(key == 27){
	//	printw("Jogo Finalizado", key);
	//	killScreen();
	//	exit(0);
	//}

	


	//mvaddch = esse comando coloca o caracter no X,Y específico
	/*while(board->snake) {
		clear();
    	mvaddch(board->snake->coordinatex, board->snake->coordinatey, ACS_DIAMOND);
    	board->snake = board->snake->next;
    	refresh();
    	int key = getch();
    	switch(key){
    		case KEY_LEFT:
    			display_points();
				mvaddch(board->snake->coordinatex, board->snake->coordinatey-1, ACS_DIAMOND);
    			break;
    		case KEY_RIGHT:
    			mvaddch(board->snake->coordinatex+1, board->snake->coordinatey, ACS_DIAMOND);
    			break;
    		case KEY_UP:
    			mvaddch(board->snake->coordinatex, board->snake->coordinatey+1, ACS_DIAMOND);
    			break;
    		case KEY_DOWN:
    			mvaddch(board->snake->coordinatex, board->snake->coordinatey-1, ACS_DIAMOND);
    			refresh();
    			break;
    	}

  	}
*/
	getch();
	killScreen();
    return 0;
}
