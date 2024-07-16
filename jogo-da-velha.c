#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* difines */
#define DIM 3
#define ESPACO ' '

/* funcoes */
void iniciar(char s[][DIM]);
void mostrar(char s[DIM][DIM]);
void ia(char s[DIM][DIM]);
int ganhou(char g[DIM][DIM]);

/* inicia o tabuleiro */
void iniciar(char s[][DIM])
{
    int i, j;
    for(i = 0; i < DIM; i++)
        for(j = 0; j < DIM; j++)
            s[i][j] = ESPACO;
}

/* mostra o tabuleiro vazio */
void mostrar(char s[DIM][DIM])
{
    printf("\n\n     1   2   3\n");
    for (int i = 0; i < DIM; i++)
    {
        printf(" %d ", i + 1);
        for (int j = 0; j < DIM; j++)
            printf("| %c ", s[i][j]);
        printf("|\n");
        if (i < DIM - 1)
            printf("   |---|---|---|\n");
    }
}

/* a maquina da prioridade ao centro, caso ja ocupado escolhe de forma aleatoria outro lugar do jogo da velha */
void ia(char s[DIM][DIM])
{
    int px, py;
    srand(time(NULL));
    if (s[1][1] == ESPACO)
        s[1][1] = 'o';
    else
    {
        px = rand() % 3;
        py = rand() % 3;
        while (s[px][py] != ESPACO)
        {
            px = rand() % 3;
            py = rand() % 3;
        }
        s[px][py] = 'o';
    }
}

/* verifica se o jogador do caractere 'x' ganhou, retorna 1 quando ganha */
int xganhou(char g[DIM][DIM])
{
    int i = 0, j = 0;
    while (i < DIM)
    {
        if (g[i][0] == g[i][1] && g[i][1] == g[i][2] && g[i][0] == 'x')
            return 1;
        i++;
    }
    while (j < DIM)
    {
        if (g[0][j] == g[1][j] && g[1][j] == g[2][j] && g[0][j] == 'x')
            return 1;
        j++;
    }
    if ((g[0][0] == g[1][1] && g[2][2] == g[1][1] && g[0][0] == 'x') || (g[0][2] == g[1][1] && g[2][0] == g[1][1] && g[0][2] == 'x'))
        return 1;
    return 0;
}

/* verifica se o jogador do caractere 'o' ganhou, retorna 1 quando ganhou */
int oganhou(char g[DIM][DIM])
{
    int i = 0, j = 0;
    while (i < DIM)
    {
        if (g[i][0] == g[i][1] && g[i][1] == g[i][2] && g[i][0] == 'o')
            return 1;
        i++;
    }
    while (j < DIM)
    {
        if (g[0][j] == g[1][j] && g[1][j] == g[2][j] && g[0][j] == 'o')
            return 1;
        j++;
    }
    if ((g[0][0] == g[1][1] && g[2][2] == g[1][1] && g[0][0] == 'o') || (g[0][2] == g[1][1] && g[2][0] == g[1][1] && g[0][2] == 'o'))
        return 1;
    return 0;
}

int main(void)
{
    char velha[DIM][DIM];
    int px, py;
    int n_jogada = 0;

    system("clear");

    iniciar(velha);
    while (1)
    {
        n_jogada++;
        mostrar(velha);
        printf("\nOnde deseja jogar.");
        printf("\nLinha: ");
        scanf("%d", &px);
        printf("Coluna: ");
        scanf("%d", &py);
        if (px > DIM || py > DIM)
        {
            printf("\n\n Valores invalidos \n\n");
                continue;
        }
        px--;
        py--;
        if (velha[px][py] == ESPACO)
        {
            velha[px][py] = 'x';
            if (n_jogada == 5)
            {
                printf("\n\n DEU VELHA! \n\n");
                break;
            }
            if (xganhou(velha))
            {
                printf("\n\n Parabens, vc ganhou!! \n\n");
                break;
            }
            ia(velha);
            if (oganhou(velha))
            {
                printf("\n\n Voce perdeu!! \n\n");
                break;
            }
        }
        else
            printf("Local ja ocupado! \nJogue novamente!!\n");

    }
    mostrar(velha);
}
