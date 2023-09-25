#include <stdio.h>
#include <stdlib.h>

struct elemento {
    int linha;
    int coluna;

    int valor;

    struct elemento *proximo;
};

typedef struct elemento Elemento;

struct matriz_identidade {
    int ordem;
    Elemento *violacoes;
};

typedef struct matriz_identidade MatrizIdentidade;

void matriz_identidade_remover_violacao(MatrizIdentidade *matriz, int linha, int coluna)
{
    Elemento *anterior = NULL;
    Elemento *atual = matriz->violacoes;

    while (atual && (atual->linha != linha || atual->coluna != coluna)) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        return;
    }

    if (anterior == NULL) {
        matriz->violacoes = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
}

void matriz_identidade_inserir_elemento(MatrizIdentidade *matriz, int linha, int coluna, int valor) {
    matriz_identidade_remover_violacao(matriz, linha, coluna);

    if ((linha == coluna && valor == 1) || (linha != coluna && valor == 0)) {
        return;
    }

    Elemento *violacao = (Elemento *)malloc(sizeof(Elemento));

    if (violacao == NULL) {
        printf("ERRO: nao foi possivel alocar o elemento [%d, %d] = %d\n", linha, coluna, valor);
        exit(1);
    }

    violacao->linha = linha;
    violacao->coluna = coluna;
    violacao->valor = valor;
    violacao->proximo = matriz->violacoes;

    matriz->violacoes = violacao;
}

MatrizIdentidade matriz_identidade_criar(int ordem) {
    MatrizIdentidade matriz = { ordem, NULL };

    for (int i = 0; i < ordem; i++) {
        matriz_identidade_inserir_elemento(&matriz, i, i, 0);
    }

    return matriz;
}

void matriz_identidade_preencher(MatrizIdentidade *matriz) {
    int linha, coluna;

    printf("Preenchimento:\n");

    do {
        printf("Digite a linha e a coluna (-1 -1 para finalizar): ");
        scanf("%d %d", &linha, &coluna);

        if (linha < 0 || coluna < 0) {
            continue;
        }

        if (linha >= matriz->ordem || coluna >= matriz->ordem) {
            printf("A posicao [%d, %d] nao faz parte da matriz.\n", linha, coluna);
            continue;
        }

        int valor;

        printf("[%d, %d] = ", linha, coluna);
        scanf("%d", &valor);

        matriz_identidade_inserir_elemento(matriz, linha, coluna, valor);
    } while (linha >= 0 && coluna >= 0);

    printf("\n");
}

void matriz_identidade_imprimir_violacoes(MatrizIdentidade *matriz) {
    if (matriz->violacoes == NULL) {
        printf("Voce formou uma matriz identidade.");
        return;
    }

    printf("Violacoes:\n");

    for (Elemento *violacao = matriz->violacoes; violacao != NULL; violacao = violacao->proximo) {
        printf("[%d, %d] = %d\n", violacao->linha, violacao->coluna, violacao->valor);
    }
}

int main() {
    int ordem;
    
    printf("Digite a ordem da matriz identidade: ");
    scanf("%d", &ordem);

    MatrizIdentidade matriz = matriz_identidade_criar(ordem);

    matriz_identidade_preencher(&matriz);
    matriz_identidade_imprimir_violacoes(&matriz);

    return 0;
}