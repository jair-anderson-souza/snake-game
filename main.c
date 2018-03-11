#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

typedef struct snake Snake;
struct snake{
	int coordinatex;
	int coordinatey;
	Snake* next;
};

typedef struct board Board;
struct board{
	Snake* snake;
	int coordinatex;
	int coordinatey;
};

int xmax, ymax;
	

void drawMenu(){
	int coordx = (COLS / 2) - 1;
	int coordy = (LINES / 2) - 1;
	mvprintw(coordy, coordx-9, "Snake Game");
	mvprintw(coordy+1, coordx-14, "Press Enter to Start");
	mvprintw(coordy+2, coordx-12, "Press ESC to Exit");
}

void draw(int *xmax, int *ymax){
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

void freeBoard(Board* board){
    free(board);
}

void shutdown(Board* board){
	printw("O programa foi finalizado, aperte Enter pra sair!!");
	getch();
	freeSnake(board->snake);
	freeBoard(board);
	killScreen();
}

Board* createBoard(int x, int y){
	Board* board = (Board*) malloc(sizeof(Board));	
	if(board != NULL){
		board->coordinatex = x;
		board->coordinatey = y;
		return board;
	}
	//lembrar de pesquisar como mandar erro pra tela
	return NULL;
	
}

Snake* createSnake(Board* board, int x, int y){
	Snake* snake = (Snake*) malloc(sizeof(Snake));	
	if(snake != NULL){
		snake->coordinatex = x;
		snake->coordinatey = y;
		board->snake = snake;
		return snake;
	}
	
}

//see addch(ACS_CKBOARD); printw("\n");
int main(int argc, char const *argv[])
{	
	draw(&xmax, &ymax);
    
	Board* board = createBoard(xmax, ymax);

	drawMenu();
	createSnake(board, xmax, ymax);

	int key = getch();

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
	
    return 0;
}
