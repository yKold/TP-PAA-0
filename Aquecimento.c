#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ACHAR '*'
#define BCHAR '*'
#define CCHAR '*'
#define TAM_V 20
#define TAM_H 80
typedef struct Posicoes
{
    int linha;
    int coluna;
} Posicoes;

int numero_aleatorio(int min, int max) {
    return min + rand() % (max - min + 1);
}

void preencherQuadro( char quadro[TAM_V][TAM_H]) {
    for (int i = 0; i < TAM_V; i++)
    {
        for (int j = 0; j < TAM_H; j++)
        {
            quadro[i][j] = ' ';
            if (j == 0 || j == 79) quadro[i][j] = '|';
            if (i == 0 || i == 19) quadro[i][j] = '-';
        }
    }
}

void imprimirQuadro( char quadro[TAM_V][TAM_H] ) {
    for (int i = 0; i < TAM_V; i++)
    {
        for (int j = 0; j < TAM_H; j++)
        {
            printf("%c", quadro[i][j]);
        }
        printf("\n");
    }
}

int verificaPosicao(Posicoes posicoes[], int linha, int coluna, int *indiceGlobal, char quadro[TAM_V][TAM_H]) {
    for (int j = 0; j < *indiceGlobal; j++) {
        if (
            (linha == posicoes[j].linha && coluna == posicoes[j].coluna) 
            || (quadro[linha][coluna] == '-') 
            || (quadro[linha][coluna] == '|')
    ) {
            printf("Houve colisao: (%d, %d)\n", linha, coluna);
            return 0;
        }
    }
    // Se não encontrou colisão, atualiza a posição
    posicoes[*indiceGlobal].linha = linha;
    posicoes[*indiceGlobal].coluna = coluna;
    return 1;
}

void gerarPontos( char quadro[TAM_V][TAM_H], int qntd_pontos, Posicoes posicoesGlobais[], int *indiceGlobal ) {
    
    // Loop para gerar pontos e inserir no quadro
    for (int i = 0; i < qntd_pontos; i++)
    {
        int val_linha = numero_aleatorio(1, 18);
        int *linha = &val_linha;
        int val_coluna = numero_aleatorio(1, 78);
        int *coluna = &val_coluna;
        
        verificaPosicao(posicoesGlobais, *linha, *coluna, indiceGlobal, quadro);
        
        quadro[*linha][*coluna] = ACHAR ;
    }
}

void verificaSoma(Posicoes posicoes1[], int qntd_pontos, int *linha, int *coluna, int *indiceGlobal, char quadro[TAM_V][TAM_H]) {
    // Verifica todas as posicoes da SOMA
    int a = verificaPosicao(posicoes1, *linha, *coluna, indiceGlobal, quadro);

    int linha_b = *linha - 1;
    int b = verificaPosicao(posicoes1, linha_b, *coluna, indiceGlobal, quadro);

    int coluna_c = *coluna + 1;
    int c = verificaPosicao(posicoes1, *linha, coluna_c, indiceGlobal, quadro);

    int linha_d = *linha + 1;
    int d = verificaPosicao(posicoes1, linha_d, *coluna, indiceGlobal, quadro);

    int coluna_e = *coluna - 1;
    int e = verificaPosicao(posicoes1, *linha, coluna_e, indiceGlobal, quadro);

    // Se algum ponto da soma colidiu, ele gera tudo novamente
    if (
        a == 0 ||
        b == 0 ||
        c == 0 ||
        d == 0 ||
        e == 0
    )
    {
        *linha = numero_aleatorio(1, 18);
        *coluna = numero_aleatorio(1, 78);
        verificaSoma( posicoes1, qntd_pontos, linha, coluna, indiceGlobal, quadro);
    }

    posicoes1[*indiceGlobal].linha = *linha;
    posicoes1[*indiceGlobal].coluna = *coluna;

    posicoes1[*indiceGlobal+1].linha = *linha+1;
    posicoes1[*indiceGlobal+1].coluna = *coluna;

    posicoes1[*indiceGlobal+2].linha = *linha;
    posicoes1[*indiceGlobal+2].coluna = *coluna+1;

    posicoes1[*indiceGlobal+3].linha = *linha-1;
    posicoes1[*indiceGlobal+3].coluna = *coluna;

    posicoes1[*indiceGlobal+4].linha = *linha;
    posicoes1[*indiceGlobal+4].coluna = *coluna-1;
    
}

void gerarSoma( char quadro[TAM_V][TAM_H], int qntd_pontos, Posicoes posicoesGlobais[], int *indiceGlobal ) {
    // Loop para gerar pontos e inserir no quadro
    for (int i = 0; i < qntd_pontos; i++)
    {
        
        int val_linha = numero_aleatorio(1, 18);
        int *linha = &val_linha;
        int val_coluna = numero_aleatorio(1, 78);
        int *coluna = &val_coluna;

        verificaSoma(posicoesGlobais, qntd_pontos, linha, coluna, indiceGlobal, quadro);
        *indiceGlobal += 5;
        quadro[*linha][*coluna] = BCHAR ;
        quadro[*linha-1][*coluna] = BCHAR ;
        quadro[*linha][*coluna+1] = BCHAR ;
        quadro[*linha+1][*coluna] = BCHAR ;
        quadro[*linha][*coluna-1] = BCHAR ;
    }
}

void verificaX(Posicoes posicoes1[], int qntd_pontos, int *linha, int *coluna, int *indiceGlobal, char quadro[TAM_V][TAM_H]) {
    // Verifica todas as posicoes da SOMA
    int a = verificaPosicao(posicoes1, *linha, *coluna, indiceGlobal, quadro);

    int linha_b = *linha - 1;
    int linha_d = *linha + 1;
    int coluna_c = *coluna + 1;
    int coluna_e = *coluna - 1;

    int b = verificaPosicao(posicoes1, linha_b, coluna_e, indiceGlobal, quadro);

    int c = verificaPosicao(posicoes1, linha_b, coluna_c, indiceGlobal, quadro);

    int d = verificaPosicao(posicoes1, linha_d, coluna_c, indiceGlobal, quadro);

    int e = verificaPosicao(posicoes1, linha_d, coluna_e, indiceGlobal, quadro);

    // Se algum ponto da soma colidiu, ele gera tudo novamente
    if (
        a == 0 ||
        b == 0 ||
        c == 0 ||
        d == 0 ||
        e == 0
    )
    {
        *linha = numero_aleatorio(1, 18);
        *coluna = numero_aleatorio(1, 78);
        verificaX( posicoes1, qntd_pontos, linha, coluna, indiceGlobal, quadro);
    }

    posicoes1[*indiceGlobal].linha = *linha;
    posicoes1[*indiceGlobal].coluna = *coluna;

    posicoes1[*indiceGlobal+1].linha = *linha+1;
    posicoes1[*indiceGlobal+1].coluna = *coluna+1;

    posicoes1[*indiceGlobal+2].linha = *linha+1;
    posicoes1[*indiceGlobal+2].coluna = *coluna-1;

    posicoes1[*indiceGlobal+3].linha = *linha-1;
    posicoes1[*indiceGlobal+3].coluna = *coluna+1;

    posicoes1[*indiceGlobal+4].linha = *linha-1;
    posicoes1[*indiceGlobal+4].coluna = *coluna-1;
    
}

void gerarX( char quadro[TAM_V][TAM_H], int qntd_pontos, Posicoes posicoesGlobais[], int *indiceGlobal ) {
    // Loop para gerar pontos e inserir no quadro
    for (int i = 0; i < qntd_pontos; i++)
    {
        
        int val_linha = numero_aleatorio(1, 18);
        int *linha = &val_linha;
        int val_coluna = numero_aleatorio(1, 78);
        int *coluna = &val_coluna;

        verificaX(posicoesGlobais, qntd_pontos, linha, coluna, indiceGlobal, quadro);
        *indiceGlobal += 5;
        quadro[*linha][*coluna] = CCHAR ;
        quadro[*linha-1][*coluna-1] = CCHAR ;
        quadro[*linha+1][*coluna+1] = CCHAR ;
        quadro[*linha+1][*coluna-1] = CCHAR ;
        quadro[*linha-1][*coluna+1] = CCHAR ;
    }
}

void gerarMix( char quadro[TAM_V][TAM_H], int qntd_pontos, Posicoes posicoesGlobais[], int *indiceGlobal ) {

    for (int i = 0; i < qntd_pontos; i++)
    {
        int aleatorio = numero_aleatorio(1,3);
        switch (aleatorio)
        {
        case 1:
            gerarSoma(quadro, 1, posicoesGlobais, indiceGlobal);
            break;

        case 2:
            gerarPontos(quadro, 1, posicoesGlobais, indiceGlobal);
            break;

        case 3:
            gerarX(quadro, 1, posicoesGlobais, indiceGlobal);
            break;

        default:
            break;
        }
    }
}


void Especial( char quadro[TAM_V][TAM_H], int qntd_pontos, Posicoes posicoesGlobais[], int *indiceGlobal ) {
    // Loop para gerar pontos e inserir no quadro
    for (int i = 0; i < qntd_pontos; i++)
    {
        int val_linha = numero_aleatorio(1, 18);
        int *linha = &val_linha;
        int val_coluna = numero_aleatorio(1, 78);
        int *coluna = &val_coluna;

        verificaSoma(posicoesGlobais, qntd_pontos, linha, coluna, indiceGlobal, quadro);
        *indiceGlobal += 5;

        if (i = 0)
        {
            // desenho da casa
            quadro[*linha][*coluna] = '*' ;
            quadro[*linha-1][*coluna-1] = '*' ;
            quadro[*linha+1][*coluna+1] = '*' ;
            quadro[*linha+1][*coluna-1] = '*' ;
            quadro[*linha-1][*coluna+1] = '*' ;
        }
        else{
            int aleatorio = numero_aleatorio(1,5);
            switch (aleatorio)
            {
            case 1:
                gerarCasa(quadro, qntd_pontos, posicoesGlobais, indiceGlobal); 
                break;

            case 2:
                gerarGato(quadro, qntd_pontos, posicoesGlobais, indiceGlobal); 
                break;

            case 3:
                gerarPeixe(quadro, qntd_pontos, posicoesGlobais, indiceGlobal); 
                break;

            case 4:
                gerarArvore(quadro, qntd_pontos, posicoesGlobais, indiceGlobal); 
                break;

            default:
                break;
            }
        }
    }
}


int main() {
    int qntd_pontos = 20;
    Posicoes posicoesGlobais[qntd_pontos*5]; 
    int indice = 0;
    int *indiceGlobal = &indice;

    srand(time(NULL));
    char quadro[TAM_V][TAM_H];
    preencherQuadro(quadro);
    Especial(quadro, qntd_pontos, posicoesGlobais, indiceGlobal);
    imprimirQuadro(quadro);
    

    return 0;
}