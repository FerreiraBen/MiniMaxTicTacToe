#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

const int INF = INT_MAX;
const short int TRUE = 1;
const short int FALSE = 0;


// GLOBAL THINGS
    const char EMPTY = '-';
    const char IA = 'X';
    const char HUMAN = 'O';
    const char DRAW = 'V';

typedef struct board{
    char board[3][3];
    char currentPlayer;
} Tboard;

Tboard *createBoard(){
    Tboard *board = malloc(sizeof(Tboard));

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++)
            board->board[i][j] = EMPTY;
    }

    board->currentPlayer = HUMAN;

    return board;
}



int triEquals(char a, char b, char c){
    return (a==b && b==c && a!=EMPTY) ? 1 : 0;
}

int max(int a, int b){
    return (a>b) ? a: b;
}
int min(int a, int b){
    return (a<b) ? a : b;
}


char verifyWinner(Tboard *board){
    char winner = EMPTY;
    int i,j;

    // winner horizontally
    for(i=0; i<3; i++){
        if(triEquals(
            board->board[0][i],
            board->board[1][i],
            board->board[2][i]
            ))
            winner = board->board[0][i];
    }

    // winner vertically
     for(i=0; i<3; i++){
        if(triEquals(
            board->board[i][0],
            board->board[i][1],
            board->board[i][2]
            ))
            winner = board->board[i][0];
    }

    // winner diagonally
    if(triEquals(
        board->board[0][0],
        board->board[1][1],
        board->board[2][2]
        )){
        winner = board->board[0][0] ;
    }
    if(triEquals(
        board->board[0][2],
        board->board[1][1],
        board->board[2][0]
        )){
        winner = board->board[0][2] ;
    }

    int spaces = 0;

    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
        if(board->board[i][j] == EMPTY) {
          spaces++;
        }
      }
    }

    if(winner==EMPTY && spaces == 0)
        return DRAW;
    return winner;

}

int scores(char result){
    switch(result){
        case IA: return 10;
        case HUMAN: return -10;
        case DRAW: return 0;
        default: return 0;
    }
}


int minimax(Tboard *board, int deepth, int maximizing){
    char result = verifyWinner(board);
    if(result!=EMPTY)
        return scores(result);

    if(maximizing){
       int bestPoint = -INF;
       for(int i=0; i<3; i++){
           for(int j=0; j<3; j++){
               if(board->board[i][j] == EMPTY){
                   board->board[i][j] = IA;
                   int point = minimax(board, deepth + 1, FALSE);
                   board->board[i][j] = EMPTY;
                   bestPoint = max(point, bestPoint);
               }
           }
       }
        return bestPoint;
    }

    else{
        int bestPoint = INF;
        for(int i=0; i<3; i++){
           for(int j=0; j<3; j++){
               if(board->board[i][j] == EMPTY){
                   board->board[i][j] = HUMAN;
                   int point = minimax(board, deepth + 1, TRUE);
                   board->board[i][j] = EMPTY;
                   bestPoint = min(point, bestPoint);
               }
           }
       }
        return bestPoint;
    }
}


void bestMove(Tboard *board){
    int bestPoint = -INF;
    int x,y,point;

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(board->board[i][j] == EMPTY){
                board->board[i][j] = IA;
                point = minimax(board, 0, FALSE);
                board->board[i][j] = EMPTY;
                if(point>bestPoint){
                    bestPoint = point;
                    x = i;
                    y = j;
                }
            }
        }
    }

    board->board[x][y] = IA;
    board->currentPlayer = HUMAN;

}

void printBoard(Tboard *board){
    for(int i=0; i<3; i++){
        if(i!=2)
            printf("\t\t_%c_|_%c_|_%c_\n", board->board[i][0], board->board[i][1], board->board[i][2]);
        else
            printf("\t\t %c | %c | %c ", board->board[i][0], board->board[i][1], board->board[i][2]);
    }
}



void intro(){
    printf("\t\t\t╭━━━━┳━━┳━━━╮\n");
    printf("\t\t\t┃╭╮╭╮┣┫┣┫╭━╮┃\n");
    printf("\t\t\t╰╯┃┃╰╯┃┃┃┃╱╰╯\n");
    printf("\t\t\t╱╱┃┃╱╱┃┃┃┃╱╭┳━━╮\n");
    printf("\t\t\t╱╱┃┃╱╭┫┣┫╰━╯┣━━╯\n");
    printf("\t\t\t╱╱╰╯╱╰━━┻━━━╯\n");
    printf("\t\t\t╭━━━━┳━━━┳━━━╮\n");
    printf("\t\t\t┃╭╮╭╮┃╭━╮┃╭━╮┃\n");
    printf("\t\t\t╰╯┃┃╰┫┃╱┃┃┃╱╰╯\n");
    printf("\t\t\t╱╱┃┃╱┃╰━╯┃┃╱╭┳━━╮\n");
    printf("\t\t\t╱╱┃┃╱┃╭━╮┃╰━╯┣━━╯\n");
    printf("\t\t\t╱╱╰╯╱╰╯╱╰┻━━━╯\n");
    printf("\t\t\t╭━━━━┳━━━┳━━━╮\n");
    printf("\t\t\t┃╭╮╭╮┃╭━╮┃╭━━╯\n");
    printf("\t\t\t╰╯┃┃╰┫┃╱┃┃╰━━╮\n");
    printf("\t\t\t╱╱┃┃╱┃┃╱┃┃╭━━╯\n");
    printf("\t\t\t╱╱┃┃╱┃╰━╯┃╰━━╮\n");
    printf("\t\t\t╱╱╰╯╱╰━━━┻━━━╯\n\n");
    printf("@Author: CAVALCANTE, Josias B. F.\n\n\n\n\n");
    system("pause");
    system("cls");
}


short int validMove(Tboard *board, int i, int j){
    return (board->board[i][j] == EMPTY) ? 1 : 0;
}


int main(){
    intro();

    int x,y,f;

    Tboard *board;
    short int loopGame = TRUE;
    short int loopAll = TRUE;


    while(loopAll){
        board = createBoard();
        system("cls");
        printf("Would you like to start with the first move?? (0/1)\n");
        short int start;
        scanf("%hd", &start);
        while(start != 0 && start != 1){
            system("cls");
            printf("Invalid answer. Press 0 for No, or 1 for Yes..\n");
            printf("Would you like to start with the first move?? (0/1)\n");
            scanf("%hd", &start);
        }
        system("cls");
        if(!start){
            board->currentPlayer = IA;
            bestMove(board);
        }

        while(loopGame){
            char comoTa = verifyWinner(board);
            if(comoTa!=EMPTY){
                printf("\n");
                printBoard(board);
                if(comoTa == HUMAN)
                    printf("\nCongradulations!! You won!\n");
                else if(comoTa == IA)
                    printf("\nOh, No! You lose.\n");
                else if(comoTa == DRAW)
                    printf("\nDraw, babe.\n");

                printf("Would you like to play again? (0/1)\n");
                scanf("%d",&f);
                while(f != 0 && f != 1){
                    system("cls");
                    printf("Invalid answer. Press 0 for No, or 1 for Yes..\n");
                    printf("Would you like to play again? (0/1)\n");
                    scanf("%d",&f);
                }
                if(f==1){
                    board = createBoard();
                    break;
                }
                else if(f==0){
                    printf("\n\t\t You just used a program made by CAVALCANTE, Josias B. F.\n\t\t\tThank you!\n\n");
                    system("pause");
                    return 0;
                }
            }

            else if(board->currentPlayer == HUMAN){
                printf("\n");
                printBoard(board);
                printf("\n\nType the line and column (exemple: 2 3):\n");
                scanf("%d %d", &x, &y);
                while(!validMove(board, x-1, y-1)){
                    printf("Invalid coordinate. Try again.\n");
                    scanf("%d %d", &x, &y);
                }
                board->board[x-1][y-1] = HUMAN;
                board->currentPlayer = IA;

                if(comoTa == verifyWinner(board) != DRAW)
                    bestMove(board);
            }

            system("cls");
        }
    }


    return 0;
}

  
