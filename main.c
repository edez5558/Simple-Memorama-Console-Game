
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CHECKPOINT_FILE "checkpoint.data"
#define GRID_VERTICAL 5 
#define GRID_HORIZONTAL 6 
#define FULL_GRID (GRID_VERTICAL * GRID_HORIZONTAL)

typedef struct{
    char icon;
    char visible;
} card;

card board[GRID_VERTICAL * GRID_HORIZONTAL];

void load_checkpoint(FILE* checkpoint,int* found,char* turn,size_t* load_card);
void save_checkpoint(FILE* checkpoint,int* found,char* turn,size_t load_card);

void play_game(FILE* checkpoint,int* found,char* turn,size_t load_card);
void fill_board();
void print_board();
int* search_free(int*);

int main(){
    srand(time(NULL));
    FILE* checkpoint = fopen(CHECKPOINT_FILE,"rb");
    int found = 0;
    char turn = 0;
    size_t load_card = 0;

    if(checkpoint != NULL){
        load_checkpoint(checkpoint,&found,&turn,&load_card);
        remove(CHECKPOINT_FILE);
    }
    else
        fill_board();

    checkpoint = fopen(CHECKPOINT_FILE,"wb");

    play_game(checkpoint,&found,&turn,load_card); 

    fclose(checkpoint);
    remove(CHECKPOINT_FILE);

    puts("Has ganado!!!");
    getchar();
}

void fill_board(){
    unsigned int rand_pos;
    memset(board,0,FULL_GRID * sizeof(card));
    for(int n_card = 0; n_card < FULL_GRID/2; n_card++){
        char icon = 97 + n_card;

        rand_pos = rand()%FULL_GRID;
        board[*search_free(&rand_pos)].icon = icon;

        rand_pos = rand()%FULL_GRID;
        board[*search_free(&rand_pos)].icon = icon;
    }
}


int* search_free(int* init_pos){
    while(board[*init_pos].icon != 0)
        *init_pos = (*init_pos + 1)%FULL_GRID;

    return init_pos;
}

void print_board(){
    putchar('\t');
    for(int x = 0; x < GRID_HORIZONTAL; x++)
        printf("%d\t",x);
    putchar('\n');

    for(int y = 0; y < GRID_VERTICAL; y++){
        printf("%d\t",y);
        for(int x = 0; x < GRID_HORIZONTAL; x++){
            card current = board[y * GRID_HORIZONTAL + x];

            if(current.icon == 0){
                printf(".\t");
                continue;
            }

            if(!current.visible)
                printf("#\t");
            else  
                printf("%c\t",current.icon);

        }

        putchar('\n');
    }
    putchar('\n');
}

void play_game(FILE* checkpoint,int* found,char* turn,size_t load_card){
    char buffer[250];
    int y;
    int x;

    card* last_card = board + load_card;
    card* current_card = NULL;

    save_checkpoint(checkpoint,found,turn,last_card - board);
    while(*found < FULL_GRID/2){
        system("cls");
        print_board();
        printf("Selecciona una casilla (y,x):");

        fflush(stdin);

        if(fgets(buffer,sizeof(buffer),stdin) == NULL){
            continue;
        }

        if(sscanf(buffer,"%d,%d",&y,&x) != 2){
            continue; 
        }

        if(y < 0 || y >= GRID_VERTICAL || x < 0 || x >= GRID_HORIZONTAL)
            continue;

        current_card = &board[y * GRID_HORIZONTAL + x];

        if(current_card->icon == 0 || current_card->visible == 1)
            continue;
        

        if(!*turn){
            current_card->visible = 1;
            goto change_turn;
        }

        current_card->visible = 1;
        if(last_card && last_card->icon == current_card->icon){
            system("cls");

            print_board();
            puts("Par encontrado\nPresiona Enter...");
            getchar();

            last_card->icon = 0;
            current_card->icon = 0;
            (*found)++;
        }else{
            system("cls");

            print_board();
            puts("No son iguales encontrado\nPresiona Enter...");
            getchar();

            
            last_card->visible = 0;
            current_card->visible = 0;
        }


        change_turn: 

        *turn = !*turn;
        last_card = current_card;

        save_checkpoint(checkpoint,found,turn,last_card - board);
    }
}

void load_checkpoint(FILE* checkpoint,int* found,char* turn,size_t* load_card){
    fread(found,sizeof(int),1,checkpoint);
    fread(turn,sizeof(char),1,checkpoint);
    fread(load_card,sizeof(size_t),1,checkpoint);
    fread(board,sizeof(card),FULL_GRID,checkpoint);

    fclose(checkpoint);
}

void save_checkpoint(FILE* checkpoint,int* found,char* turn,size_t load_card){
    fseek(checkpoint,0,SEEK_SET);
    
    fwrite(found,sizeof(int),1,checkpoint);
    fwrite(turn,sizeof(char),1,checkpoint);
    fwrite(&load_card,sizeof(size_t),1,checkpoint);
    fwrite(board,sizeof(card),FULL_GRID,checkpoint);
}