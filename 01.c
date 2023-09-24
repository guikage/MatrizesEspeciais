#include <stdio.h>
#include <stdlib.h>

struct diagonal {
    int ordem;
    int *v;
};

typedef struct diagonal Diagonal;

Diagonal aloca_matriz(int ordem) {
    Diagonal diag;

    diag.ordem = ordem;
    diag.v = (int *)malloc(ordem * sizeof(int));

    if (diag.v == NULL) {
        printf("Erro fatal. Encerrando o programa...\n");
        exit(1);
    }

    return diag;
}

void preenche_matriz(Diagonal *diag) {
    for (int i = 0; i < diag->ordem; i++) {
        printf("Digite o elemento na posicao [%d,%d]: ", i, i);
        scanf("%d", &diag->v[i]);
    }
}

int consulta_matriz(Diagonal *diag, int i, int j) {
    if (i == j && i < diag->ordem) {
        return diag->v[i];
    }

    return 0;
}

void imprime_matriz(Diagonal *diag) {
    printf("   ");

    for (int j = 0; j < diag->ordem; j++) {
        printf(" %3d", j);
    }

    printf("\n");

    for (int i = 0; i < diag->ordem; i++) {
        printf("%3d", i);

        for (int j = 0; j < diag->ordem; j++) {
            printf(" %3d", consulta_matriz(diag, i, j));
        }

        printf("\n");
    }
}

void imprime_menu() {
    printf("Menu:\n");
    printf("a) Imprimir matriz\n");
    printf("b) Preencher matriz\n");
    printf("c) Consultar matriz\n");
    printf("s) Sair\n");
}

void realizar_operacao(Diagonal *diag, char opcao) {

    switch (opcao)
    {
    case 'a':
        imprime_matriz(diag);
        break;
    case 'b':
        preenche_matriz(diag);
        break;
    case 'c':
        {
            int linha, coluna;
            
            printf("Digite a linha e a coluna: ");
            scanf("%d %d", &linha, &coluna);

            printf("[%d, %d] = %d\n", linha, coluna, consulta_matriz(diag, linha, coluna));
        }
    }

    printf("\n");
}

int main() {
    int ordem;

    printf("Digite a ordem da matriz: ");
    scanf("%d", &ordem);

    Diagonal diag = aloca_matriz(ordem);

    char opcao;

    do {
        imprime_menu();
        printf("\nO que voce deseja fazer? ");

        scanf(" %c", &opcao);

        realizar_operacao(&diag, opcao);
    } while (opcao != 's');

    return 0;
}
