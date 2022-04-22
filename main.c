#include <stdio.h>
#include <stdlib.h>

void getInputs(int* pp, int* pl, int* pc) {
    printf("digite o comprimento do paralelepipedo no eixo x: ");
    scanf("%d", pc); //coloco o valor de colunas dado na variavel c
    if (*pc < 1) { //se for inserido um valor invalido, termino o programa, o mesmo acontece para o resto.
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
                printf("%d ", x[i][j][k]); //imprimo todos os elementos da matriz para cada plano
            }
            printf("\n");
        }
        printf("\n");
    }
}

void getRadius(float* px, float* py, float* pz) {
    printf("digite o raio do elipsoide no eixo x: "); // mesmo esquema da funcao getInputs
    scanf("%f", px);
    if (*px < 1) {
        printf("entrada invalida!");
        exit(0);
    }
    printf("\n");

    printf("digite o raio do elipsoide no eixo y: ");
    scanf("%f", py);
    if (*py < 1) {
        printf("entrada invalida!");
        exit(0);
    }
    printf("\n");

    printf("digite o raio do elipsoide no eixo z: ");
    scanf("%f", pz);
    if (*pz < 1) {
        printf("entrada invalida!");
        exit(0);
    }
    printf("\n");
}

void fillMatrix(int*** x, unsigned int p, unsigned int l, unsigned int c) {

    float rx, ry, rz, u, v, w; //inicializo as variaveis de raio e mais 3 variaveis temporarias para realizar a operacao
    u = (float)c; //essas 3 variaveis temporarias so servem para eu poder realizar operacoes com floats ja que o numero de planos, linhas e colunas sao inteiros
    v = (float)l;
    w = (float)p;

    getRadius(&rx, &ry, &rz); //recebo os valores dos raios

    for (int k = 0; k < p; k++) {
        for (int j = 0; j < l; j++) {
            for (int i = 0; i < c; i++){
                if ((i - (u - 1)/2)*(i - (u - 1)/2)/(rx*rx) + (j - (v - 1)/2)*(j - (v - 1)/2)/(ry*ry) + (k - (w - 1)/2)*(k - (w - 1)/2)/(rz*rz) <= 1.) { // faço o teste para saber se a coordenada esta dentro do elipsoide ou nao, baseado na formula geral de um elipsoide centrado no centro da matriz 3D (seria o comprimento de uma dimensao menos 1 e dividido por 2) e de raios rx, ry e rz.
                    x[i][j][k] = 1; // se sim, registrar 1
                } else {
                    x[i][j][k] = 0; // se nao, registrar 0
                }
            }
        }
    }
}

void printPlane(int*** x, unsigned int l, unsigned int c, unsigned int k) {
    for (int j = 0; j < l; j++) {
        for (int i = 0; i < c; i++) {
            printf("%d ", x[i][j][k]); //imprime o k-ésimo plano de uma matriz 3D de l linhas e c colunas
        }
        printf("\n");
    }
}

void userLoop(int*** x, unsigned int p, unsigned int l, unsigned int c) {
    int k; //a variavel que guarda a entrada do usuario
    unsigned char t = 1; // uma variavel que serve apenas para manter o loop permanentemente ativo ate o break.
    while(t) {
        printf("digite qual a coordenada z da secao reta que deseja vizualizar (os valores aceitos sao de 0 a %d, digite -1 para finalizar, digite -2 para imprimir todos as secoes retas): ", p - 1);
        scanf("%d", &k);
        if (k == -2) { // se o usuario digita -2, eu imprimo todos os planos da matriz.
            printMatrix(x, p, l, c);
        } else if (k == -1) { // se o usuario digita -1, saio do loop e finalizo o programa após liberar as memorias alocadas
            break;
        } else if (0 <= k && k < p) {
            printPlane(x, l, c, k); // se um dos valores de 0 ate p - 1 é inserido, imprimo apenas o plano correspondente
        } else {
            printf("entrada invalida!\n\n"); // se nao for isso, sinalizo.
        }
    }
}

int main() {

    unsigned int p, l, c; // inicializo as variaveis que irao conter o numero de planos, linhas e colunas

    getInputs(&p, &l, &c); // recebo os valores do usuario

    int*** x; //inicializo a variavel da matriz
    int i; //inicializo o contador
    x = (int***)malloc(c*sizeof(int**)); //aloco a memoria do primeiro bloco auxiliar

    x[0] = (int**)malloc(c*l*sizeof(int*)); // aloco a memoria do segundo bloco auxiliar e a registro na primeira posicao do bloco auxiliar
    for (i = 1; i < c; i++) { // registro os demais enderecos do segundo bloco auxiliar no primeiro bloco
        x[i] = x[i - 1] + l;
    }

    x[0][0] = (int*)malloc(p*l*c*sizeof(int)); // aloco a memoria para guardar os valores
    for (i = 1; i < c*l; i++) { // registro as linhas no segundo bloco auxiliar
        x[0][i] = x[0][i - 1] + p;
    }

    fillMatrix(x, p, l, c); // preencho a matriz segundo às regras dadas (1 dentro do elipsoide e 0 fora)

    userLoop(x, p, l, c); // executo o loop em que o usuário ficará para vizualizar as seções retas.

    free(x[0][0]); // libero a memória
    free(x[0]);
    free(x);

    return 0;
}
