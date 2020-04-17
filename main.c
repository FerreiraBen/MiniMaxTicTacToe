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
    const char VELHA = 'V';

typedef struct board{
    char board[3][3];
    char jogadorAtual;
} Tboard;

Tboard *createBoard(){
    Tboard *board = malloc(sizeof(Tboard));

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++)
            board->board[i][j] = EMPTY;
    }

    board->jogadorAtual = HUMAN;

    return board;
}



int iguais3(char a, char b, char c){
    if(a==b && b==c && a!=EMPTY)
        return 1;
    return 0;
}

int max(int a, int b){
    if(a>b)
        return a;
    return b;
}
int min(int a, int b){
    if(a<b)
        return a;
    return b;
}


char verificaGanhador(Tboard *board){
    char ganhador = EMPTY;
    int i,j;

    // Ganhador na Horizontal
    for(i=0; i<3; i++){
        if(iguais3(
            board->board[0][i],
            board->board[1][i],
            board->board[2][i]
            ))
            ganhador = board->board[0][i];
    }

    
    // Ganhador na Vertical
     for(i=0; i<3; i++){
        if(iguais3(
            board->board[i][0],
            board->board[i][1],
            board->board[i][2]
            ))
            ganhador = board->board[i][0];
    }

    // Ganhador na Diagonal
    if(iguais3(
        board->board[0][0],
        board->board[1][1],
        board->board[2][2]
        )){
        ganhador = board->board[0][0] ;
    }
    if(iguais3(
        board->board[0][2],
        board->board[1][1],
        board->board[2][0]
        )){
        ganhador = board->board[0][2] ;
    }

    int espacos = 0;

    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
        if(board->board[i][j] == EMPTY) {
          espacos++;
        }
      }
    }

    if(ganhador==EMPTY && espacos == 0)
        return VELHA;
    return ganhador;

}

int scores(char result){
    if(result == IA)
        return 10;
    else if(result == HUMAN)
        return -10;
    else if(result == VELHA)
        return 0;
}


int minimax(Tboard *board, int profundidade, int maximizando){
    char resultado = verificaGanhador(board);
    if(resultado!=EMPTY)
        return scores(resultado);

    if(maximizando){
       int melhorPonto = -INF;
       for(int i=0; i<3; i++){
           for(int j=0; j<3; j++){
               if(board->board[i][j] == EMPTY){
                   board->board[i][j] = IA;
                   int ponto = minimax(board, profundidade + 1, FALSE);
                   board->board[i][j] = EMPTY;
                   melhorPonto = max(ponto, melhorPonto);
               }
           }
       }
        return melhorPonto;
    }

    else{
        int melhorPonto = INF;
        for(int i=0; i<3; i++){
           for(int j=0; j<3; j++){
               if(board->board[i][j] == EMPTY){
                   board->board[i][j] = HUMAN;
                   int ponto = minimax(board, profundidade + 1, TRUE);
                   board->board[i][j] = EMPTY;
                   melhorPonto = min(ponto, melhorPonto);
               }
           }
       }
        return melhorPonto;
    }
}


void melhorMovimento(Tboard *board){
    int melhorPonto = -INF;
    int x,y,ponto;

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(board->board[i][j] == EMPTY){
                board->board[i][j] = IA;
                ponto = minimax(board, 0, FALSE);
                board->board[i][j] = EMPTY;
                if(ponto>melhorPonto){
                    melhorPonto = ponto;
                    x = i;
                    y = j;
                }
            }
        }
    }

    board->board[x][y] = IA;
    board->jogadorAtual = HUMAN;

}

void imprimirBoard(Tboard *board){
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
    printf("@Author: CAVALCANTE, Josias B. F.\n\n\n");
    system("pause");
    system("cls");
}

short int movimentoValido(Tboard *board, int i, int j){
    if(board->board[i][j] == EMPTY)
        return 1;
    return 0;
}


int main(){
    intro();

    int x,y,f;

    Tboard *quadro;
    short int loopGame = TRUE;
    short int loopAll = TRUE;


    while(loopAll){
        quadro = createBoard();

        while(loopGame){
            char comoTa = verificaGanhador(quadro);
            if(comoTa!=EMPTY){
                imprimirBoard(quadro);
                if(comoTa == HUMAN)
                    printf("\nPARABENS, VOCE VENCEU!\n");
                else if(comoTa == IA)
                    printf("\nPERDEU, OTARIO!\n");
                else if(comoTa == VELHA)
                    printf("\nVELHOU, OTARIO!\n");
                
                printf("Gostaria de jogar de novo? [0/1]\n");
                scanf("%d",&f);
                if(f==1){
                    quadro = createBoard();
                    break;
                }
                else if(f==0)
                    return 0;
            }

            else if(quadro->jogadorAtual == HUMAN){
                imprimirBoard(quadro);
                printf("\n\nDigite a linha e a coluna: (ex: 2 3)\n");
                scanf("%d %d", &x, &y);
                while(!movimentoValido(quadro, x-1, y-1)){
                    printf("Coordenada invalida. Tente novamente.\n");
                    scanf("%d %d", &x, &y);
                }
                quadro->board[x-1][y-1] = HUMAN;
                quadro->jogadorAtual = IA;

                if(comoTa = verificaGanhador(quadro) != VELHA)
                    melhorMovimento(quadro);
            }

            system("cls");
        }
    }


    return 0;
}