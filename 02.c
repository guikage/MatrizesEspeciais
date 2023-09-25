#include <stdio.h>
#include <stdlib.h>

struct lista
{
    int linha;
    int coluna;
    int info;
    struct lista *prox;
};

typedef struct lista Lista;

struct esparsa
{
    int linhas;
    int colunas;
    struct lista *prim;
};

typedef struct esparsa Esparsa;

Esparsa matriz_esparsa_criar(int linhas, int colunas) {
    return (Esparsa) {
        .linhas = linhas,
        .colunas = colunas,
        .prim = NULL
    };
}

int matriz_esparsa_tamanho(Esparsa *esparsa) {
    int tamanho = 0;
    
    for (Lista *no = esparsa->prim; no != NULL; no = no->prox) {
        tamanho++;
    }

    return tamanho;
}

double matriz_esparsa_porcentagem_preenchido(Esparsa *esparsa) {
    int preenchido = matriz_esparsa_tamanho(esparsa);
    int total = esparsa->linhas * esparsa->colunas;

    return (double)preenchido / total * 100.0;
}

void matriz_esparsa_remover_elemento(Esparsa *esparsa, int linha, int coluna)
{
    Lista *anterior = NULL;
    Lista *atual = esparsa->prim;

    while (atual && (atual->linha != linha || atual->coluna != coluna)) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        return;
    }

    if (anterior == NULL) {
        esparsa->prim = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
}


void matriz_esparsa_inserir_elemento(Esparsa *esparsa, int linha, int coluna, int info) {
    matriz_esparsa_remover_elemento(esparsa, linha, coluna);

    if (info == 0) {
        return;
    }

    Lista *no = (Lista *)malloc(sizeof(Lista));

    if (no == NULL) {
        printf("Ocorreu um problema ao alocar o no [%d, %d] = %d\n", linha, coluna, info);
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

        if (linha < 0 || coluna < 0) {
            continue;
        }

        if (linha >= esparsa->linhas || coluna >= esparsa->colunas) {
            printf("A posicao [%d, %d] nao faz parte da matriz.\n\n", linha, coluna);
            continue;
        }

        int info;

        printf("[%d, %d] = ", linha, coluna);
        scanf("%d", &info);

        matriz_esparsa_inserir_elemento(esparsa, linha, coluna, info);
        
        printf("\n");
    } while (linha >= 0 && coluna >= 0);
}

void matriz_esparsa_imprimir(Esparsa *esparsa) {
    printf("   ");

    for (int j = 0; j < esparsa->colunas; j++) {
        printf(" %3d", j);
    }

    printf("\n");

    for (int i = 0; i < esparsa->linhas; i++) {
        printf("%3d", i);

        for (int j = 0; j < esparsa->colunas; j++) {
            int elemento = matriz_esparsa_consultar_elemento(esparsa, i, j);
            printf(" %3d", elemento);
        }

        printf("\n");
    }

    printf("\n");
}

void imprimir_menu() {
    printf("\nMenu:\n");
    printf("a) Imprimir matriz\n");
    printf("b) Preencher elementos\n");
    printf("c) Consultar elemento\n");
    printf("d) Somar linha\n");
    printf("i) Informacoes\n");
    printf("s) Sair\n\n");
}

void realizar_operacao(Esparsa *esparsa, char opcao) {
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

                printf("[%d, %d] = %d\n", linha, coluna, elemento);
                break;
            }
        case 'd':
            {
                int linha;
                printf("Digite a linha para somar: ");
                scanf("%d", &linha);

                printf("Soma: %d\n", matriz_esparsa_somar_linha(esparsa, linha));

                break;
            }
        case 'i':
            {
                double porcentagem = matriz_esparsa_porcentagem_preenchido(esparsa);
                printf("Total preenchido: %.2lf%%\n", porcentagem);

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

        realizar_operacao(&esparsa, opcao);        
    } while (opcao != 's');

    return 0;
}