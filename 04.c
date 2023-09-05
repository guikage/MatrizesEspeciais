#include <stdio.h>
#include <stdlib.h>

int ***aloca_matriz(int x, int y, int z){
    int i, j, k;
    int ***m = (int***)malloc(x * sizeof(int**));
    if (m == NULL){
        printf("Ops, ocorreu um problema.");
        exit(1);
    }
    for(i = 0; i < x; i++){
        m[i] = (int**)malloc(y * sizeof(int*));
        if(m[i] == NULL){
            printf("Ops, ocorreu um problema.");
            exit(1);
        }
        for(j = 0; j < y; j++){
            m[i][j] = (int*)malloc(z * sizeof(int));
            if(m[i][j] == NULL){
                printf("Ops, ocorreu um problema.");
                exit(1);
            }
        }
    }
    return m;
}

void preenche_matriz(int x, int y, int z, int ***mat){
    int i, j, k;
    for(i = 0; i < x; i++){
        for(j = 0; j < y; j++){
            for(k = 0; k < z; k++){
                printf("Digite o elemento na posicao [%d][%d][%d]: ", i, j, k);
                scanf("%d", &mat[i][j][k]);
            }
        }
    }
}

void imprime_matriz(int x, int y, int z, int ***mat){
    int i, j, k;
    for(i = 0; i < x; i++){
        for(j = 0; j < y; j++){
            for(k = 0; k < z; k++){
                printf("%d\t", mat[i][j][k]);
            }
            putchar('\n');
        }
        putchar('\n');
    }
}

int main(){
    int ***m, x, y, z;
    printf("Digite as dimensoes x, y e z da matriz: ");
    scanf("%d %d %d", &x, &y, &z);
    m = aloca_matriz(x, y, z);
    preenche_matriz(x, y, z, m);
    imprime_matriz(x, y, z, m);
    return 0;
}
