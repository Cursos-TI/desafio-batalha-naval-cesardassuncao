#include <stdio.h>

#define TAM 10      // Tamanho tabuleiro
#define NAVIO 3     // Valor navio
#define HABILIDADE 5 // Valor área de habilidade

int main() {
    int tabuleiro[TAM][TAM];
    int i, j;

    // -------------------------------------------------------------------
    //                  1. Inicializando o Tabuleiro!
    // -------------------------------------------------------------------
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // -------------------------------------------------------------------
    //                  2. Posicionamento dos Navios!
    // -------------------------------------------------------------------
    int navioHorizontal[3] = {NAVIO, NAVIO, NAVIO};
    int navioVertical[3]   = {NAVIO, NAVIO, NAVIO};
    int navioDiagonal1[3]  = {NAVIO, NAVIO, NAVIO};
    int navioDiagonal2[3]  = {NAVIO, NAVIO, NAVIO};

    // Coords iniciais navios
    int linhaH = 1, colunaH = 2;
    int linhaV = 5, colunaV = 6;
    int linhaD1 = 3, colunaD1 = 1;
    int linhaD2 = 0, colunaD2 = 8;

    // Colocando os navios já no tabuleiro
    for (i = 0; i < 3; i++) {
        tabuleiro[linhaH][colunaH + i] = NAVIO;
        tabuleiro[linhaV + i][colunaV] = NAVIO;
        tabuleiro[linhaD1 + i][colunaD1 + i] = NAVIO;
        tabuleiro[linhaD2 + i][colunaD2 - i] = NAVIO;
    }

    // -------------------------------------------------------------------
    //                    3. Matriz das Habilidades
    // -------------------------------------------------------------------
    // Cada habilidade será uma matriz 5x5, 0 (não afetado) ou 1 (afetado)
    int cone[5][5];
    int cruz[5][5];
    int octaedro[5][5];

    // ------------------------------
    //    3.1 Habilidade 'Cone'
    // ------------------------------
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (j >= 2 - i && j <= 2 + i && i < 3)
                cone[i][j] = 1;
            else if (i >= 3 && j >= i - 2 && j <= 6 - i)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }

    // ------------------------------
    //    3.2 Habilidade 'Cruz'
    // ------------------------------
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (i == 2 || j == 2)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }

    // ------------------------------
    //    3.3 Habilidade 'Losango' (Octaedro)
    // ------------------------------
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (i + j >= 2 && i + j <= 6 && j - i <= 2 && i - j <= 2)
                octaedro[i][j] = 1;
            else
                octaedro[i][j] = 0;
        }
    }

    // -------------------------------------------------------------------
    //              4. Posição habilidades no tabuleiro
    // -------------------------------------------------------------------
    int origemCone[2] = {2, 4};
    int origemCruz[2] = {6, 3};
    int origemOcta[2] = {5, 8};


    int linhaCentro, colunaCentro;

    // 4.1 Cone
    linhaCentro = origemCone[0];
    colunaCentro = origemCone[1];
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            int linha = linhaCentro - 2 + i;
            int coluna = colunaCentro - 2 + j;
            // Garante que está dentro do tabuleiro
            if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM) {
                if (cone[i][j] == 1 && tabuleiro[linha][coluna] == 0)
                    tabuleiro[linha][coluna] = HABILIDADE;
            }
        }
    }

    // 4.2 Cruz
    linhaCentro = origemCruz[0];
    colunaCentro = origemCruz[1];
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            int linha = linhaCentro - 2 + i;
            int coluna = colunaCentro - 2 + j;
            if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM) {
                if (cruz[i][j] == 1 && tabuleiro[linha][coluna] == 0)
                    tabuleiro[linha][coluna] = HABILIDADE;
            }
        }
    }

    // 4.2 Losango (Octaedro)
    linhaCentro = origemOcta[0];
    colunaCentro = origemOcta[1];
    for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
            int linha = linhaCentro + i;
            int coluna = colunaCentro + j;
            if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM) {
                if ((i == 0) || (j == 0)) // forma de cruz (vertical + horizontal)
                    tabuleiro[linha][coluna] = HABILIDADE;
        }
    }
}

    // -------------------------------------------------------------------
    //                 5. Exibição final Tabuleiro
    // -------------------------------------------------------------------
    printf("\n--- Tabuleiro Batalha Naval ---\n\n");
    printf("OBS: Água = 0 | Navio = 3 | Área de habilidade = 5\n\n");

    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}