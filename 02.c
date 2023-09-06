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

Esparsa matriz_esparsa_criar(int linhas, int colunas) {
    return (Esparsa) {
        .linhas = linhas,
        .colunas = colunas,
        .prim = NULL
    };
}

int matriz_esparsa_quantidade_de_elementos(Esparsa *esparsa) {
    int tamanho = 0;
    
    for (Lista *no = esparsa->prim; no != NULL; no = no->prox) {
        tamanho++;
    }

    return tamanho;
}

double matriz_esparsa_preenchido(Esparsa *esparsa) {
    int preenchido = matriz_esparsa_quantidade_de_elementos(esparsa);
    int total = esparsa->linhas * esparsa->colunas;

    return (double)preenchido / total;
}

void matriz_esparsa_inserir_elemento(Esparsa *esparsa, int linha, int coluna, int info) {
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

int matriz_esparsa_consultar_elemento(Esparsa *esparsa, int linha, int coluna) {
    for (Lista *no = esparsa->prim; no != NULL; no = no->prox) {
        if (no->linha == linha && no->coluna == coluna) {
            return no->info;
        }
    }

    return 0;
}

int matriz_esparsa_somar_linha(Esparsa *esparsa, int linha) {
    int soma = 0;

    for (Lista *no = esparsa->prim; no != NULL; no = no->prox) {
        if (no->linha == linha) {
            soma += no->info;
        }
    }

    return soma;
}

void matriz_esparsa_preencher(Esparsa *esparsa) {
    int linha, coluna;

    do {

        printf("Digite a linha e a coluna (-1 -1 para finalizar): ");
        scanf("%d %d", &linha, &coluna);

        if (linha > -1 && coluna > -1) {
            int info;

            printf("[%d, %d] = ", linha, coluna);
            scanf("%d", &info);

            if (info != 0) {
                matriz_esparsa_inserir_elemento(esparsa, linha, coluna, info);
            }
        }
        
        printf("\n");
    } while (linha > -1 && coluna > -1);
}

void matriz_esparsa_imprimir(Esparsa *esparsa) {
    printf("   ");

    for (int j = 0; j < esparsa->colunas; j++) {
        printf(" %03d", j);
    }

    printf("\n");

    for (int i = 0; i < esparsa->linhas; i++) {
        printf("%03d", i);

        for (int j = 0; j < esparsa->colunas; j++) {
            int elemento = matriz_esparsa_consultar_elemento(esparsa, i, j);
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

void escolher_opcao(Esparsa *esparsa, char opcao) {
    switch (opcao) {
        case 'a':
            matriz_esparsa_imprimir(esparsa);
            break;
        case 'b':
            matriz_esparsa_preencher(esparsa);
            break;
        case 'c':
            {
                int linha, coluna;
                printf("Digite a linha e a coluna para consultar: ");
                scanf("%d %d", &linha, &coluna);

                int elemento = matriz_esparsa_consultar_elemento(esparsa, linha, coluna);

                printf("[%d, %d] = %d\n\n", linha, coluna, elemento);
                break;
            }
        case 'd':
            {
                int linha;
                printf("Digite a linha para somar: ");
                scanf("%d", &linha);

                printf("Soma: %d\n\n", matriz_esparsa_somar_linha(esparsa, linha));

                break;
            }
        case 'i':
            {
                double porcentagem = matriz_esparsa_preenchido(esparsa);
                printf("Total preenchido: %.2lf%%\n\n", porcentagem * 100);

                break;
            }
    }
}

int main() {
    int linhas, colunas;
    
    printf("Digite o numero de linhas da matriz: ");
    scanf("%d", &linhas);

    printf("Digite o numero de colunas da matriz: ");
    scanf("%d", &colunas);

    Esparsa esparsa = matriz_esparsa_criar(linhas, colunas);

    char opcao;

    do {
        imprimir_menu();

        printf("O que voce deseja fazer? ");
        scanf(" %c", &opcao);

        escolher_opcao(&esparsa, opcao);        
    } while (opcao != 's');
}