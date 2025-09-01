#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
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

void desenharCampoFutebol(char quadro[TAM_V][TAM_H]) {
    // Limpar quadro
    for (int i = 0; i < TAM_V; i++) {
        for (int j = 0; j < TAM_H; j++) {
            quadro[i][j] = ' ';
        }
    }

    // Bordas externas do campo
    for (int i = 0; i < TAM_V; i++) {
        quadro[i][0] = '|';
        quadro[i][TAM_H - 1] = '|';
    }
    for (int j = 0; j < TAM_H; j++) {
        quadro[0][j] = '-';
        quadro[TAM_V - 1][j] = '-';
    }

    // Linha central
    int cx = TAM_H / 2;
    for (int i = 1; i < TAM_V - 1; i++) {
        quadro[i][cx] = '|';
    }

    // Círculo central (aproximado)
    int cy = TAM_V / 2;
    quadro[cy][cx] = ' ';
    quadro[cy - 1][cx] = '|';
    quadro[cy + 1][cx] = '|';
    quadro[cy][cx - 1] = '[';
    quadro[cy][cx + 1] = ']';

    // Gol esquerdo (retângulo fechado com | e -)
    int gol_altura = 8;
    int gol_largura = 10;
    int gol_linha_inicio = (TAM_V - gol_altura) / 2;
    int gol_coluna_inicio = 1; // logo após a borda

    for (int i = gol_linha_inicio; i < gol_linha_inicio + gol_altura; i++) {
        for (int j = gol_coluna_inicio; j < gol_coluna_inicio + gol_largura; j++) {
            if (i == gol_linha_inicio || i == gol_linha_inicio + gol_altura - 1) {
                quadro[i][j] = '-'; // topo e fundo do gol
            }
            if (j == gol_coluna_inicio || j == gol_coluna_inicio + gol_largura - 1) {
                quadro[i][j] = '|'; // lados do gol
            }
        }
    }

    // Gol direito (retângulo fechado com | e -)
    gol_coluna_inicio = TAM_H - 1 - gol_largura; // logo antes da borda direita
    for (int i = gol_linha_inicio; i < gol_linha_inicio + gol_altura; i++) {
        for (int j = gol_coluna_inicio; j < gol_coluna_inicio + gol_largura; j++) {
            if (i == gol_linha_inicio || i == gol_linha_inicio + gol_altura - 1) {
                quadro[i][j] = '-'; // topo e fundo do gol
            }
            if (j == gol_coluna_inicio || j == gol_coluna_inicio + gol_largura - 1) {
                quadro[i][j] = '|'; // lados do gol
            }
        }
    }
}

void desenharBolaAleatoria(char quadro[TAM_V][TAM_H]) {
    int linha, coluna;

    // Escolhe posição aleatória dentro do campo (ignorando bordas externas e gols)
    do {
        linha = 1 + rand() % (TAM_V - 2);       // evita primeira e última linha
        coluna = 1 + rand() % (TAM_H - 2);      // evita primeira e última coluna
    } while (quadro[linha][coluna] != ' ' || 
             quadro[linha][coluna-1] != ' ' || 
             quadro[linha][coluna+1] != ' '); // evita sobrescrever algo

    // Desenha a bola (__)
    quadro[linha][coluna - 1] = '(';
    quadro[linha][coluna] = '_';
    quadro[linha][coluna + 1] = ')';
}

bool bolaNoGol(char quadro[TAM_V][TAM_H]) {
    int gol_altura = 8;
    int gol_largura = 10;
    int gol_linha_inicio = (TAM_V - gol_altura) / 2;

    // Gol esquerdo
    int gol_esq_col_inicio = 1; // logo após a borda esquerda
    int gol_esq_col_fim = gol_esq_col_inicio + gol_largura - 1;
    int gol_linha_fim = gol_linha_inicio + gol_altura - 1;

    // Gol direito
    int gol_dir_col_inicio = TAM_H - 1 - gol_largura;
    int gol_dir_col_fim = TAM_H - 2;

    // Percorre o quadro procurando a bola
    for (int i = gol_linha_inicio; i <= gol_linha_fim; i++) {
        for (int j = 0; j < TAM_H; j++) {
            if (quadro[i][j] == '_') { // bola representada por '_'
                // Verifica se a posição da bola está dentro do gol esquerdo
                if (j >= gol_esq_col_inicio && j <= gol_esq_col_fim) {
                    return true;
                }
                // Verifica se a posição da bola está dentro do gol direito
                if (j >= gol_dir_col_inicio && j <= gol_dir_col_fim) {
                    return true;
                }
            }
        }
    }
    return false;
}

#define QNTD_BONECOS 4

void gerarBonecoDetalhado(char quadro[TAM_V][TAM_H], int quantidade) {
    int linha, coluna;

    for (int n = 0; n < quantidade; n++) {
        int valido;
        do {
            valido = 1;
            // Escolhe posição aleatória para a "cabeça" do boneco
            linha = 1 + rand() % (TAM_V - 4);   // deixa espaço para corpo e pernas
            coluna = 1 + rand() % (TAM_H - 3);  // deixa espaço para braços

            // Verifica se as posições estão livres
            for (int i = 0; i < 3; i++) {       // linhas do boneco
                for (int j = -1; j <= 1; j++) { // colunas relativas à cabeça
                    if (quadro[linha + i][coluna + j] != ' ') {
                        valido = 0;
                        break;
                    }
                }
                if (!valido) break;
            }
        } while (!valido);

        // Desenha boneco
        quadro[linha][coluna] = 'O';              // cabeça
        quadro[linha + 1][coluna - 1] = '/';      // braços
        quadro[linha + 1][coluna] = '|';
        quadro[linha + 1][coluna + 1] = '\\';
        quadro[linha + 2][coluna - 1] = '/';      // pernas
        quadro[linha + 2][coluna + 1] = '\\';
    }
}

int verificaGolComDefesa(char quadro[TAM_V][TAM_H]) {
    int gol_altura = 8;
    int gol_largura = 10;
    int gol_linha_inicio = (TAM_V - gol_altura) / 2;

    // Limites dos gols
    int gol_esq_col_inicio = 1; 
    int gol_esq_col_fim = gol_esq_col_inicio + gol_largura - 1;
    int gol_dir_col_inicio = TAM_H - 1 - gol_largura;
    int gol_dir_col_fim = TAM_H - 2;
    int gol_linha_fim = gol_linha_inicio + gol_altura - 1;

    // Percorre o quadro procurando a bola
    for (int i = 0; i < TAM_V; i++) {
        for (int j = 0; j < TAM_H; j++) {
            if (quadro[i][j] == '_') { // encontrou a bola
                // Verifica se está dentro do gol esquerdo
                if (i >= gol_linha_inicio && i <= gol_linha_fim && j >= gol_esq_col_inicio && j <= gol_esq_col_fim) {
                    // Checa se há algum boneco na posição da bola (3x3)
                    for (int bi = i - 1; bi <= i + 1; bi++) {
                        for (int bj = j - 1; bj <= j + 1; bj++) {
                            if (bi >= 0 && bi < TAM_V && bj >= 0 && bj < TAM_H) {
                                char c = quadro[bi][bj];
                                if (c == 'O' || c == '/' || c == '|' || c == '\\') {
                                    return 2; // defesa
                                }
                            }
                        }
                    }
                    return 1; // gol
                }
                // Verifica se está dentro do gol direito
                if (i >= gol_linha_inicio && i <= gol_linha_fim && j >= gol_dir_col_inicio && j <= gol_dir_col_fim) {
                    for (int bi = i - 1; bi <= i + 1; bi++) {
                        for (int bj = j - 1; bj <= j + 1; bj++) {
                            if (bi >= 0 && bi < TAM_V && bj >= 0 && bj < TAM_H) {
                                char c = quadro[bi][bj];
                                if (c == 'O' || c == '/' || c == '|' || c == '\\') {
                                    return 2; // defesa
                                }
                            }
                        }
                    }
                    return 1; // gol
                }
            }
        }
    }
    return 0; // fora do gol
}


int main() {
    int qntd_pontos = 20;
    Posicoes posicoesGlobais[qntd_pontos*5]; 
    int indice = 0;
    int *indiceGlobal = &indice;

    srand(time(NULL));
    char quadro[TAM_V][TAM_H];
    preencherQuadro(quadro);
    desenharCampoFutebol(quadro);
    gerarBonecoDetalhado(quadro, 4);
    desenharBolaAleatoria(quadro);
    imprimirQuadro(quadro);
    int resultado = verificaGolComDefesa(quadro);
    if (resultado == 0) {
        printf("Bola fora do gol.\n");
    } else if (resultado == 1) {
        printf("GOOOOL!!!\n");
    } else if (resultado == 2) {
        printf("DEFESA!\n");
    }

    

    return 0;
}