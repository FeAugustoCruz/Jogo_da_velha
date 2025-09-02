#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Jogador {
    char nome1[30];
    char caractere;
};

typedef struct Jogador jogador;

void ShowNumbers();
void ShowHash(char p[3][3]);
bool IsEmpty(char p[3][3], int posi);
void Mark(char p[3][3], int posi, char letter);
int IsEnd(char p[3][3], char name1[30], char name2[30], int turns, jogador player[]);
void WhoWin(char letter, char name1[30], char name2[30], int turns, jogador player[]);

int main() {
    jogador jogadores[2];
    int posi1, posi2, turno = 0;
    char hash[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
    int op;
    
    printf("-----------------JOGO DA VELHA-----------------\n");
    printf("Nome do primeiro jogador: \n");
    fgets(jogadores[0].nome1, 30, stdin);
    jogadores[0].nome1[strcspn(jogadores[0].nome1, "\n")] = 0;

    do{
        printf("Deseja ser X ou O?\n1 - para X\n2 - para O:\n");
        scanf("%d", &op);
        getchar();

        if (op == 1) {
            jogadores[0].caractere = 'X';
            jogadores[1].caractere = 'O';
        } else {
            jogadores[0].caractere = 'O';
            jogadores[1].caractere = 'X';
        }
    }while (op != 1 && op != 2);
    
    
    printf("Nome do segundo jogador: \n");
    fgets(jogadores[1].nome1, 30, stdin);
    jogadores[1].nome1[strcspn(jogadores[1].nome1, "\n")] = 0;
    
    while(true){
        turno++;
        ShowNumbers();
        ShowHash(hash);
        do{
            printf("Player 1 - Digite uma posição para marcar: \n");
            scanf("%d", &posi1);
        } while(IsEmpty(hash, posi1));
        Mark(hash, posi1, jogadores[0].caractere);
        if(IsEnd(hash, jogadores[0].nome1, jogadores[1].nome1, turno, jogadores)){
            break;
        }
        do{
            printf("Player 2 - Digite uma posição para marcar: \n");
            scanf("%d", &posi2);
        }while(IsEmpty(hash, posi2));
        Mark(hash, posi2, jogadores[1].caractere);
        if(IsEnd(hash, jogadores[0].nome1, jogadores[1].nome1, turno, jogadores)){
            break;
        }
    };
    
    return 0;
}

void ShowNumbers() {
    int cont = 1;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            printf(" [%d] ", cont);
            cont++;
        }
        printf("\n");
    }
}

void ShowHash(char p[3][3]) {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            printf(" [%c] ", p[x][y]);
        }
        printf("\n");
    }
}

bool IsEmpty(char p[3][3], int posi) {
    if (posi < 1 || posi > 9) {
        return false; // Posição inválida
    }

    int cont = 1;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (cont == posi) {
                if (p[x][y] != ' '){
                    return true;
                }
                else{
                    return false; // 1 se ocupada, 0 se livre
                }
            }
            cont++;
        }
    }
    return false; // Se não encontrou a posição, retorna 1
}


void Mark(char p[3][3], int posi, char letter) {
    int cont = 1;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (cont == posi) {
                p[x][y] = letter;
            }
            cont++;
        }
    }
}

int IsEnd(char p[3][3], char name1[30], char name2[30], int turns, jogador player[]) {
    for (int x = 0; x < 3; x++) {
        if ((p[x][0] == p[x][1] && p[x][1] == p[x][2]) && (p[x][0] != ' ')) {
            WhoWin(p[x][0], name1, name2, turns, player);
            return 1;
        }
        if ((p[0][x] == p[1][x] && p[1][x] == p[2][x]) && (p[0][x] != ' ')) {
            WhoWin(p[0][x], name1, name2, turns, player);
            return 1;
        }
    }
    
    if ((p[0][0] == p[1][1] && p[1][1] == p[2][2]) && (p[0][0] != ' ')) {
        WhoWin(p[0][0], name1, name2, turns, player);
        return 1;
    } else if ((p[0][2] == p[1][1] && p[1][1] == p[2][0]) && (p[0][2] != ' ')) {
        WhoWin(p[1][1], name1, name2, turns, player);
        return 1;
    }
    int cont = 0;
    for (int x = 0; x < 3; x ++){
        for(int y = 0; y < 3; y ++){
            if (p[x][y] == 'X' || p[x][y] == 'O'){
                cont++;
            } 
        }
    }
    if (cont == 9){
        printf("DEU EMPATE!");
        return 1;
    }
    
    return 0;
}

void WhoWin(char letter, char name1[30], char name2[30], int turns, jogador player[]) {
    if (letter == player[0].caractere) {
        printf("%s Ganhou! Quantidade de turnos: %d Pontuação: %d\n", player[0].nome1, turns, 50 - turns * 2);
    } else {
        printf("%s Ganhou! Quantidade de turnos: %d Pontuação: %d\n", player[1].nome1, turns, 50 - turns * 2);
    }
}