#include <stdio.h>
#include <stdlib.h>

void verificar_alocacao(void *resultado)
{
    if (resultado != NULL) {
        return;
    }

    printf("Oops, ocorreu um problema ao realizar a alocação.\n");
    printf("Encerrando...\n");
    exit(1);
}

int ***aloca_matriz(int m, int n, int z) {
    int ***mat = (int ***)malloc(m * sizeof(int **));
    verificar_alocacao(mat);

    for (int i = 0; i < m; i++) {
        mat[i] = (int **)malloc(n * sizeof(int *));
        verificar_alocacao(mat[i]);

        for (int j = 0; j < n; j++) {
            mat[i][j] = (int *)malloc(z * sizeof(int));
            verificar_alocacao(mat[i][j]);
        }
    }

    return mat;
}

void preenche_matriz(int m, int n, int z, int ***mat){
    printf("Preenchimento:\n");

    for (int k = 0; k < z; k++) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                printf("Digite o elemento na posicao [%d, %d, %d]: ", i, j, k);
                scanf("%d", &mat[i][j][k]);
            }
        }
    }
}

void imprime_matriz(int m, int n, int z, int ***mat) {
    printf("\nVisualizacao:\n");

    for (int k = 0; k < z; k++) {
        printf("k = %d\n", k);
        printf("   ");

        for (int j = 0; j < n; j++) {
            printf(" %3d", j);
        }

        printf("\n");

        for (int i = 0; i < m; i++) {
            printf("%3d", i);

            for (int j = 0; j < n; j++) {
                printf(" %3d", mat[i][j][k]);
            }
            
            printf("\n");
        }

        printf("\n\n");
    }
}

int main() {
    int m, n, z;

    printf("Digite o numero de linhas, de colunas e de profundidade da matriz: ");
    scanf("%d %d %d", &m, &n, &z);

    int ***mat = aloca_matriz(m, n, z);

    preenche_matriz(m, n, z, mat);
    imprime_matriz(m, n, z, mat);

    return 0;
}
