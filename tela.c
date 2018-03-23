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
/**typedef struct comida Comida;
struct comida{
     Comida* comida;
     int coordinatex;
     int coordinatey;
	/* data /
};*/

main(){
    printf(" _______________________________________________ \n");
    printf("|                                               |\n");
	printf("|  _____   ___    _   ______   _   _   _______  |\n");
	printf("| |#####| |# #|  |#| |######| |#| |#| |#######| |\n");
	printf("| |#|___  |#||#| |#| |#|  |#| |#||#|  |#|____   |\n");
	printf("| |#####| |#| |#||#| |#|__|#| |###|   |######|  |\n");
	printf("|  ___|#| |#|  |###| |######| |#||#|  |#|_____  |\n");
	printf("| |#####| |#|   |##| |#|  |#| |#| |#| |#######| |\n");
	printf("|                                               |\n");
	printf("|_______________________________________________|\n");
	printf("\n\n");
    printf(" ______________________________________\n");
	printf("|................PARA..................|\n");
	printf("|...............INICIAR................|\n");
	printf("|......................................|\n");
	printf("|..............SELECIONE...............|\n");
	printf("|......................................|\n");
	printf("|.............O NUMERO (1)..............|\n");
	printf("|......................................|\n");
	printf("|______________________________________|\n");
	int opcao;
	scanf("%i,",&opcao);
    switch (opcao){
           case 1:{

           }

   }
}
