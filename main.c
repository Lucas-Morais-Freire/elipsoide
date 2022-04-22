#include <stdio.h>
#include <stdlib.h>

void getInputs(int* pp, int* pl, int* pc) {
    printf("digite o comprimento do paralelepipedo no eixo x: ");
    scanf("%d", pc);
    if (*pc < 1) {
        printf("entrada invalida!");
        exit(0);
    }
    printf("\n");

    printf("digite o comprimento do paralelepipedo no eixo y: ");
    scanf("%d", pl);
    if (*pl < 1) {
        printf("entrada invalida!");
        exit(0);
    }
    printf("\n");

    printf("digite o comprimento do paralelepipedo no eixo z: ");
    scanf("%d", pp);
    if (*pp < 1) {
        printf("entrada invalida!");
        exit(0);
    }
    printf("\n");
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

void fillMatrix(int*** x, unsigned int p, unsigned int l, unsigned int c) {

    float u, v, w;
    u = (float)c;
    v = (float)l;
    w = (float)p;

    for (int k = 0; k < p; k++) {
        for (int j = 0; j < l; j++) {
            for (int i = 0; i < c; i++){
                if ((i - (u - 1)/2)*(i - (u - 1)/2)/((u - 1)/2*(u - 1)/2) + (j - (v - 1)/2)*(j - (v - 1)/2)/((v - 1)/2*(v - 1)/2) + (k - (w - 1)/2)*(k - (w - 1)/2)/((w - 1)/2*(w - 1)/2) <= 1.) {
                    x[i][j][k] = 1;
                } else {
                    x[i][j][k] = 0;
                }
            }
        }
    }
}

void printPlane(int*** x, unsigned int l, unsigned int c, unsigned int k) {
    for (int j = 0; j < l; j++) {
        for (int i = 0; i < c; i++) {
            printf("%d ", x[i][j][k]);
        }
        printf("\n");
    }
}

void userLoop(int*** x, unsigned int p, unsigned int l, unsigned int c) {
    int k;
    unsigned char t = 1;
    while(t) {
        printf("digite qual a coordenada z da secao reta que deseja vizualizar (os valores aceitos sao de 0 a %d, digite -1 para finalizar, digite -2 para imprimir todos as secoes retas): ", p - 1);
        scanf("%d", &k);
        if (k == -2) {
            printMatrix(x, p, l, c);
        } else if (k == -1) {
            break;
        } else if (0 <= k && k < p) {
            printPlane(x, l, c, k);
        } else {
            printf("entrada invalida!\n\n");
        }
    }
}

int main() {

    unsigned int p, l, c;

    getInputs(&p, &l, &c);

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

    fillMatrix(x, p, l, c);

    userLoop(x, p, l, c);

    free(x[0][0]);
    free(x[0]);
    free(x);

    return 0;
}
