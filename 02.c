#include <stdio.h>
#include <stdlib.h>

struct lista
{
    int linha;
    int coluna;
    int info;
    struct lista* prox;
};

typedef struct lista Lista;

struct esparsa
{
    int linhas;
    int colunas;
    struct lista* prim;
};

typedef struct esparsa Esparsa;

Esparsa criar_matriz_esparsa(int linhas, int colunas) {
    return (Esparsa) {
        .linhas = linhas,
        .colunas = colunas,
        .prim = NULL
    };
}

int quantidade_preenchida_matriz_esparsa(Esparsa *esparsa) {
    int tamanho = 0;
    
    for (Lista *no = esparsa->prim; no != NULL; no = no->prox) {
        tamanho++;
    }

    return tamanho;
}

double percentual_preenchido_matriz_esparsa(Esparsa *esparsa) {
    int preenchido = quantidade_preenchida_matriz_esparsa(esparsa);
    int total = esparsa->linhas * esparsa->colunas;

    return (double)preenchido / total;
}

void inserir_elemento_matriz_esparsa(Esparsa *esparsa, int linha, int coluna, int info) {
    Lista *no = (Lista *)malloc(sizeof(Lista));

    if (no == NULL) {
        printf("Ocorreu um problema ao alocar o no [%d, %d] = %d\n");
        exit(1);
    }

    no->linha = linha;
    no->coluna = coluna;
    no->info = info;
    no->prox = esparsa->prim;

    esparsa->prim = no;
}

int consultar_elemento_matriz_esparsa(Esparsa *esparsa, int linha, int coluna) {
    for (Lista *no = esparsa->prim; no != NULL; no = no->prox) {
        if (no->linha == linha && no->coluna == coluna) {
            return no->info;
        }
    }

    return 0;
}

int somar_linha_matriz_esparsa(Esparsa *esparsa, int linha) {
    int soma = 0;

    for (Lista *no = esparsa->prim; no != NULL; no = no->prox) {
        if (no->linha == linha) {
            soma += no->info;
        }
    }

    return soma;
}

void preencher_matriz_esparsa(Esparsa *esparsa) {
    int linha, coluna;

    do {

        printf("Em qual linha e em qual coluna voce deseja inserir (-1 -1 para finalizar)? ");
        scanf("%d %d", &linha, &coluna);

        if (linha > -1 && coluna > -1) {
            int info;

            printf("[%d, %d] = ", linha, coluna);
            scanf("%d", &info);

            if (info != 0) {
                inserir_elemento_matriz_esparsa(esparsa, linha, coluna, info);
            }
        }
        
        printf("\n");
    } while (linha > -1 && coluna > -1);
}

void imprimir_matriz_esparsa(Esparsa *esparsa) {
    printf("   ");

    for (int j = 0; j < esparsa->colunas; j++) {
        printf(" %03d", j);
    }

    printf("\n");

    for (int i = 0; i < esparsa->linhas; i++) {
        printf("%03d", i);

        for (int j = 0; j < esparsa->colunas; j++) {
            int elemento = consultar_elemento_matriz_esparsa(esparsa, i, j);
            printf(" %3d", elemento);
        }

        printf("\n");
    }

    printf("\n");
}

void imprimir_menu() {
    printf("Menu:\n");
    printf("a) Imprimir matriz\n");
    printf("b) Preencher elementos\n");
    printf("c) Consultar elemento\n");
    printf("d) Somar linha\n");
    printf("i) Informacoes\n");
    printf("s) Sair\n\n");
}

int main() {
    int linhas, colunas;
    
    printf("Digite o numero de linhas da matriz: ");
    scanf("%d", &linhas);

    printf("Digite o numero de colunas da matriz: ");
    scanf("%d", &colunas);

    Esparsa esparsa = criar_matriz_esparsa(linhas, colunas);

    char opcao;

    do {
        imprimir_menu();

        printf("O que voce deseja fazer? ");
        scanf(" %c", &opcao);

        switch (opcao)
        {
            case 'a':
                imprimir_matriz_esparsa(&esparsa);
                break;
            case 'b':
                preencher_matriz_esparsa(&esparsa);
                break;
            case 'c':
                {
                    int linha, coluna;
                    printf("Digite a linha e a coluna para consultar: ");
                    scanf("%d %d", &linha, &coluna);

                    int elemento = consultar_elemento_matriz_esparsa(&esparsa, linha, coluna);

                    printf("[%d, %d] = %d\n\n", linha, coluna, elemento);
                    break;
                }
            case 'd':
                {
                    int linha;
                    printf("Digite a linha para somar: ");
                    scanf("%d", &linha);

                    printf("Soma: %d\n\n", somar_linha_matriz_esparsa(&esparsa, linha));

                    break;
                }
            case 'i':
                {
                    double porcentagem = percentual_preenchido_matriz_esparsa(&esparsa);
                    printf("Total preenchido: %.2lf%%\n\n", porcentagem * 100);

                    break;
                }

        }
    } while (opcao != 's');


}