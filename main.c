#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

//https://www.mkssoftware.com/docs/man3/curs_attr.3.asp
//https://www.mkssoftware.com/docs/man3/curs_color.3.asp

#define size_screen_y getmaxy(stdscr)
#define size_screen_x getmaxx(stdscr)
// #define begin_screen_y getbegy(stdscr)
// #define begin_screen_x getbegx(stdscr)

#define down 0402		
#define up 0403		
#define left 0404		
#define right 0405

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

Screen* createScreen(Snake* snake){
	Screen* screen = (Screen*) malloc(sizeof(Screen));	
	if(screen != NULL){
		screen->coordinatey = size_screen_y;
		screen->coordinatex = size_screen_x;
		screen->snake = snake;
		return screen;
	}
	//lembrar de pesquisar como mandar erro pra tela
	return NULL;	
}

int calculateMiddleScreen(int value){
	return value / 2;
}

//return some error e.g.
Snake* createSnake(){
	int middley = calculateMiddleScreen(size_screen_y);
	int middlex = calculateMiddleScreen(size_screen_x);
	Snake* snake = (Snake*) malloc(sizeof(Snake));	
	if(snake != NULL){
		snake->coordinatey = middley;
		snake->coordinatex = middlex;
		return snake;
	}
}	

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

void calculateCoordinate(Snake* snake, int ch){
	int y = snake->coordinatey;
	int x = snake->coordinatex;
	switch(ch){
		case KEY_LEFT:
			x = x - 1;
			break;
		case KEY_RIGHT:
			x = x + 1;
			break;
		case KEY_UP:
			y = y - 1;
			break;
		case KEY_DOWN:
			y = y + 1;
			break;
		default:
			break;
	}
	snake->coordinatex = x;
	snake->coordinatey = y;
}

void moveSnake(Snake* snake, int ch) {
	while(snake != NULL){
		calculateCoordinate(snake, ch);
		mvaddch(snake->coordinatey, snake->coordinatex, ACS_DIAMOND);
		//refresh();
		snake = snake->next; 
	}
}

int d(int previous){
	int ch = getch();
  switch (ch) {
    case left:
      if (previous != right) return left;
    case right:
      if (previous != left) return right;
    case down:
      if (previous != up) return down;
    case up:
      if (previous != down) return up;
    default:
      return previous;
  }
}


//a coordenada y é de cima pra baixo no ecrã
int main(int argc, char const *argv[]){	
	// printw("%d", begin_screen_y);
	// printw("%d", begin_screen_x);
	// getch();
	initscr();
	noecho();	
	cbreak();
	keypad(stdscr, TRUE); //teclas do teclado funcionarem
	curs_set(0); //desabilitar cursor
	timeout(100);
	
	Screen* screen = createScreen(createSnake());
	int key = KEY_RIGHT;
	while(true){
		clear();
		moveSnake(screen->snake, key);
		refresh();
		key = d(key);

	}

	
	freeSnake(screen->snake);
	freeBoard(screen); 
	killScreen();
    return 0;
}
	 



	//key = nextMove(screen->snake);

	//showSnake(screen->snake);



	//Essa função é o Menu que eu ainda pretendo fazer
	//drawMenu();

	
	//moveSnake(screen->snake);

	// refresh();

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

