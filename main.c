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

void printMatrix(int*** x, unsigned int p, unsigned int l, unsigned int c) {
    for (int k = 0; k < p; k++) {
        for (int j = 0; j < l; j++) {
            for (int i = 0; i < c; i++){
                printf("%d ", x[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void getVals(int*** x, int p, int l, int c) {
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < l; j++) {
            for (int k = 0; k < p; k++){
                printf("entrada [%d][%d][%d] ", i, j, k);
                scanf("%d", &x[i][j][k]);
            }
        }
    }
}

void fillMatrix(int*** x, unsigned int rx, unsigned int ry, unsigned int rz) {

    unsigned int p, l, c;
    p = 2*rz + 1;
    l = 2*ry + 1;
    c = 2*rx + 1;

    float u, v, w;
    u = (float)rx;
    v = (float)ry;
    w = (float)rz;

    for (int k = 0; k < p; k++) {
        for (int j = 0; j < l; j++) {
            for (int i = 0; i < c; i++){
                if ((i - u)*(i - u)/(u*u) + (j - v)*(j - v)/(v*v) + (k - w)*(k - w)/(w*w) <= 1.) {
                    x[i][j][k] = 1;
                } else {
                    x[i][j][k] = 0;
                }
            }
        }
    }
}

int main() {

    unsigned int rx, ry, rz;

    if (getInputs(&rx, &ry, &rz) == 0) {
        return 0;
    }

    unsigned int p, l, c;
    p = 2*rz + 1;
    l = 2*ry + 1;
    c = 2*rx + 1;

    int*** x;
    int i;
    x = (int***)malloc(c*sizeof(int**));

    x[0] = (int**)malloc(c*l*sizeof(int*));
    for (i = 1; i < c; i++) {
        x[i] = x[i - 1] + l;
    }

    x[0][0] = (int*)malloc(p*l*c*sizeof(int));
    for (i = 1; i < c*l; i++) {
        x[0][i] = x[0][i - 1] + p;
    }

    fillMatrix(x, rx, ry, rz);

    printMatrix(x, p, l, c);

    free(x[0][0]);
    free(x[0]);
    free(x);

    return 0;
}
