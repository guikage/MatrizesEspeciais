#include <stdio.h>
#include <stdlib.h>

struct diagonal{
    int ordem;
    int *v;
};
typedef struct diagonal Diagonal;

void aloca_vetor(Diagonal *diag, int ordem){
    diag->ordem = ordem;
    diag->v = (int*)malloc(ordem * sizeof(int));
    if (diag->v == NULL){
        printf("\nErro fatal. Encerrando o programa.");
        exit(1);
    }
}

void preenche_vetor(Diagonal *diag){
    int i;
    for(i = 0; i < diag->ordem; i++){
        printf("\nDigite o elemento na posicao [%d,%d]: ", i, i);
        scanf("%d", &diag->v[i]);
    }
}

void imprime_matriz(Diagonal *diag){
    int i, j;
    putchar('\n');
    for(i = 0; i < diag->ordem; i++){
        putchar('\n');
        for(j = 0; j < diag->ordem; j++){
            if(i == j){
                printf("%d\t", diag->v[i]);
            }
            else{
                printf("0\t");
            }
        }
    }
}

int consulta_elemento(Diagonal diag, int i, int j){
    if(i < diag.ordem && j < diag.ordem){
        if(i = j){
            return diag.v[i];
        }
        else{
            return 0;
        }
    }
    return 0;
}

int main(){
    Diagonal d;
    int ordem;
    printf("Digite a ordem da matriz: ");
    scanf("%d", &ordem);
    aloca_vetor(&d, ordem);
    preenche_vetor(&d);
    imprime_matriz(&d);

    return 0;
}
