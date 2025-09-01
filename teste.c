#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main() {
    srand(time(NULL));
    int n = 10; // tamanho do labirinto (10x10)

    printf("Digite o tamanho do caminho desejado: ");
    scanf("%d", &max_cells);

    gerar_labirinto(0, 0);
    imprimir_labirinto(n);

    return 0;
}
