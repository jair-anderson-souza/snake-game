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

void killScreen(){
	endwin();
}

void freeSnake(Snake* snake){
	free(snake);
}

void freeBoard(Screen* screen){
    free(screen);
}


Snake* createNewSnake(int y, int x){
	Snake* snake = (Snake*) malloc(sizeof(Snake));
	snake->coordinatey = y;
	snake->coordinatex = x;
}

Snake* calculateCoordinate(int y, int x, int newDirection){
	switch(newDirection){
		case left:
			x = x - 1;
			break;
		case right:
			x = x + 1;
			break;
		case up:
			y = y - 1;
			break;
		case down:
			y = y + 1;
			break;
		default:
			break;
	}
	return createNewSnake(y, x);
}


int keyPressed(int previous){
	int keyPressed = getch();
  	switch (keyPressed) {
    	case left:
			if (previous != right){ 
				return left;
	  		}
		case right:
      		if (previous != left){ 
			  return right;
			}
    	case down:
      		if (previous != up){ 
			  return down;
			  }
    	case up:
			if (previous != down){
				 return up;
			}
		default:
      		return previous;
  	}
}

void d(Snake* snake, Snake* snakeTemp){
	while(snake != NULL){
		snake->coordinatey == snakeTemp->coordinatey && snake->coordinatex == snakeTemp->coordinatex;
		snake = snake->next;
	}
}

void printSnake(Snake* snake) {
	while(snake != NULL){
		mvaddch(snake->coordinatey, snake->coordinatex, ACS_DIAMOND);
		snake = snake->next; 
	}
}


//novo cálculo passando as coordenadas
Snake* calculateNextCell(Screen* screen, Snake* newSnake){
	newSnake->next = screen->snake;
	screen->snake = newSnake;
	Snake* snakeTemp = screen->snake;

	while(snakeTemp->next->next){
		snakeTemp = snakeTemp->next;
	}
	free(snakeTemp->next);
	snakeTemp->next = NULL;
}

int nextMovement(Screen* screen, int movement){
	
	Snake* snakeTemp = calculateCoordinate(screen->snake->coordinatey, screen->snake->coordinatex, movement);
	// snakeTemp->next = snake;
	calculateNextCell(screen, snakeTemp);
	
	
	// snakeTemp->next = snake;
    // snake = snakeTemp;

	//checkNextMovementIsTheSame
		
	//checkTail
	//d(snake, snakeTemp);

	//check food

	//finally, move snake
	
	printSnake(screen->snake);

}



//a coordenada y é de cima pra baixo no ecrã
int main(int argc, char const *argv[]){	
	initscr();
	noecho();	
	cbreak();
	keypad(stdscr, TRUE); //teclas do teclado funcionarem
	curs_set(0); //desabilitar cursor
	timeout(100);
	
	// Screen* screen = createScreen(createSnake());


	
	Snake* snake1 = (Snake*) malloc(sizeof(Snake));
	snake1->coordinatey = 10;
	snake1->coordinatex = 10;
	
	Snake* snake2 = (Snake*) malloc(sizeof(Snake));
	snake2->coordinatey = 10;
	snake2->coordinatex = 9;
	
	snake1->next = snake2;

	Screen* screen = createScreen(snake1);
	int key = right;
	while(true){
		clear();
		printSnake(screen->snake);
		//moveSnake(screen->snake, key);
		key = keyPressed(key);
		nextMovement(screen, key);
		refresh();
		

	}	
	freeSnake(screen->snake);
	freeBoard(screen); 
	killScreen();
    return 0;
}
	 