#include <stdio.h>
#include <stdlib.h>

short getInputs(int* pl, int* pc, int* pp) {
    printf("digite o raio do elipsoide no eixo x: ");
    scanf("%d", pl);
    if (*pl < 1) {
        printf("entrada invalida!");
        return 0;
    }
    printf("\n");

    printf("digite o raio do elipsoide no eixo y: ");
    scanf("%d", pc);
    if (*pc < 1) {
        printf("entrada invalida!");
        return 0;
    }
    printf("\n");

    printf("digite o raio do elipsoide no eixo z: ");
    scanf("%d", pp);
    if (*pp < 1) {
        printf("entrada invalida!");
        return 0;
    }
    printf("\n");

    return 1;
}

void printMatrix(int*** x, int p, int l, int c) {
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < l; j++) {
            for (int k = 0; k < c; k++){
                printf("%d ", x[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void getVals(int*** x, int p, int l, int c) {
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < l; j++) {
            for (int k = 0; k < c; k++){
                printf("entrada [%d][%d][%d] ", i, j, k);
                scanf("%d", &x[i][j][k]);
            }
        }
    }
}

int main() {

    unsigned int p, l, c;

    if (getInputs(&p, &l, &c) == 0) {
        return 0;
    }

    int*** x;
    int m, n;
    x = (int***)malloc(p*sizeof(int**));

    x[0] = (int**)malloc(p*l*sizeof(int*));
    for (m = 1; m < p; m++) {
        x[m] = x[m - 1] + l;
    }

    x[0][0] = (int*)malloc(p*l*c*sizeof(int));
    for (m = 1; m < p*l; m++) {
        x[0][m] = x[0][m - 1] + c;
    }

    

    free(x[0][0]);
    free(x[0]);
    free(x);

    return 0;
}