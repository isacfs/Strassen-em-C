
#include <stdio.h>
#include <time.h> 
#include <stdlib.h>
#include <math.h>

//Declaração de todas a funções usadas
int mult_matriz(int *, int *, int *, int);
int strassen(int *, int *, int *, int, int);
void imprimindo(int *, int);
int strassen_reduzido(int *, int *, int *, int, int);

/*A função (strassen_reduzido) é uma combinação do método de STRASSEN com o
método de multiplicação comum de matriz, quando o numero de linhas/colunas 
for <= 4 a função (strassen reduzido) chama a multiplicação comum de matrizes O(n³);

Pelos testes ela começa a ter ganho de performacena multiplicação em matrizes >= 25x25*/

int strassen_reduzido(int *A, int *B, int *C, int m, int n){
    if(m<=2){
        mult_matriz(A, B, C, m);
    }
    else{
        m=m/2;
        int *A1, *A2, *A3, *A4, *B1, *B2, *B3, *B4, *C1, *C2, *C3, *C4;

        //Posição de memória do Início dos 4 quadrantes de A
        A1 = A;
        A2 = A+m;
        A3 = A + m*n;
        A4 = A + m*(n+1);

        //Posição de memória do Início dos 4 quadrantes de B
        B1 = B;
        B2 = B+m;
        B3 = B + m*n;
        B4 = B + m*(n+1);

        //Posição de memória do Início dos 4 quadrantes de C
        C1 = C;
        C2 = C + m;
        C3 = C + m*n;
        C4 = C + m*(n+1);

        //1º e 2º quadrantes de A  x  1º e 3º quadrantes de B
        strassen(A1, B1, C1, m, n);
        strassen(A2, B3, C1, m, n);

        //1º e 2º quadrantes de A  x  2º e 4º quadrantes de B
        strassen(A1, B2, C2, m, n);
        strassen(A2, B4, C2, m, n);

        //3º e 4º quadrantes de A  x  1º e 3º quadrantes de B
        strassen(A3, B1, C3, m, n);
        strassen(A4, B3, C3, m, n);

        //3º e 4º quadrantes de A  x  2º e 4º quadrantes de B
        strassen(A3, B2, C4, m, n);
        strassen(A4, B4, C4, m, n);
    }
}
/*A função (strassen), é um método de multiplição de matrizes que visa reduzir o tempo 
de execução subdividindo as matrizes principais em outras 4, enxugando termos
pelo caminho e reduzinho a complexidade de execução de O(N^3) para O(N^2,8) aproximadamente;*/

int strassen(int *A, int *B, int *C, int m, int n){
    if(m==2){
        int A1, A2, A3, A4, B1, B2, B3, B4, *C1, *C2, *C3, *C4;
        //Valor dos 4 elementos de A
        A1 = *(A);
        A2 = *(A+1);
        A3 = *(A + n);
        A4 = *(A +  n + 1);

        //Valor dos 4 elementos de B
        B1 = *(B);
        B2 = *(B+1);
        B3 = *(B + n);
        B4 = *(B + n+1);

        //Posição de memória do Início dos 4 elementos de C
        C1 = C;
        C2 = (C + 1);
        C3 = (C + n);
        C4 = (C + n+1);

        int P1 = (A1)*(B2-B4);
        int P2 = (A1+A2)*(B4);
        int P3 = (A3+A4)*(B1);
        int P4 = (A4)*(B3-B1);
        int P5 = (A1+A4)*(B1+B4);
        int P6 = (A2-A4)*(B3+B4);
        int P7= (A1-A3)*(B1+B2);

        *(C1) = (*(C1) + P5 + P4 - P2 + P6);
        *(C2) = (*(C2) + P1 + P2);
        *(C3) = (*(C3) + P3 + P4);
        *(C4) = (*(C4) + P1 + P5 - P3 - P7);
    }
    else{
        m=m/2;
        int *A1, *A2, *A3, *A4, *B1, *B2, *B3, *B4, *C1, *C2, *C3, *C4;

        //Posição de memória do Início dos 4 quadrantes de A
        A1 = A;
        A2 = A+m;
        A3 = A + m*n;
        A4 = A + m*(n+1);

        //Posição de memória do Início dos 4 quadrantes de B
        B1 = B;
        B2 = B+m;
        B3 = B + m*n;
        B4 = B + m*(n+1);

        //Posição de memória do Início dos 4 quadrantes de C
        C1 = C;
        C2 = C + m;
        C3 = C + m*n;
        C4 = C + m*(n+1);

        //1º e 2º quadrantes de A  x  1º e 3º quadrantes de B
        strassen(A1, B1, C1, m, n);
        strassen(A2, B3, C1, m, n);

        //1º e 2º quadrantes de A  x  2º e 4º quadrantes de B
        strassen(A1, B2, C2, m, n);
        strassen(A2, B4, C2, m, n);

        //3º e 4º quadrantes de A  x  1º e 3º quadrantes de B
        strassen(A3, B1, C3, m, n);
        strassen(A4, B3, C3, m, n);

        //3º e 4º quadrantes de A  x  2º e 4º quadrantes de B
        strassen(A3, B2, C4, m, n);
        strassen(A4, B4, C4, m, n);
    }
}
/*Função que printa uma matriz*/
void imprimindo(int *C, int n){
    int i,j;

    for ( i = 0; i < n; i++)
    {
        for ( j = 0; j < n; j++)
        {
            printf("%d ", C[i*n+j]);
        }
        printf("\n");
    }

}

/*Função que multiplica duas matrizes, A e B, pelo jeito tradicional, com 3 FOR
e armazena em C, possui complexidade O(n^3)*/
int mult_matriz(int *A, int *B, int *C, int n)
{
    srand(time(NULL));
    int i, j, k;
    //Preparando a matriz C para receber os valores//
    for ( i = 0; i < n; i++)
    {
        for ( j = 0; j < n; j++)
        {
            C[i*n+j]=0;
        }
    } 
    for(i=0; i< n; i++)
    {
        for(j = 0; j < n; j++)
        {
            for(k=0; k < n; k++)
            {
                    C[i*n+j] = C[i*n+j] + (A[i*n+k] * B[k*n+j]);
            }
        }
    }
}
void main(int argc, char **argv)
{
    int i, j, k, n;
    clock_t t;
    int *A;
    int *B;
    int *C;
//Se a chamada do programa não tiver parametros, argc==1.,,,,,
    if (argc==1)
    {
        printf("Linhas/Colunas das matrizes A e B: ");
        scanf("%i", &n);


        //alocando espaço para nossas matrizes (A, B, C);
        A = (int *) malloc((n*n) * sizeof(int));
        if(A == NULL){
            printf("Erro de memória!");
        }

        B = (int *) malloc((n*n) * sizeof(int));
        if(B == NULL){
            printf("Erro de memória!");
        }

        C = (int *) malloc((n*n) * sizeof(int));
        if(B == NULL){
            printf("Erro de memória!");
        }

        //Recebendo valores da matriz A
        for ( i = 0; i < n; i++)
        {
            for ( j = 0; j < n; j++)
            {
                printf("Digite os valores dos elementos da matriz A: ");
                printf("matriz A [%i][%i] = ", i, j);
                scanf("%d", &A[i*n+j]);
            }
        }
        for ( i = 0; i < n; i++)
        {
            for ( j = 0; j < n; j++)
            {
                printf("%d ", A[i*n+j]);
            }
            printf("\n");
        }
        
        //Recebendo valores da matriz B
        for ( i = 0; i < n; i++)
        {
            for ( j = 0; j < n; j++)
            {
                printf("Digite os valores dos elementos da matriz B: ");
                printf("matriz B [%i][%i] = ", i, j);
                scanf("%d", &B[i*n+j]);
            }
        }
        //Preparando a matriz C para receber os valores//
        for ( i = 0; i < n; i++)
        {
            for ( j = 0; j < n; j++)
            {
                C[i*n+j]=0;
            }
        } 

        printf("Tradicional:\n");
        clock_t tempo;
        tempo = clock();

        //Chamando a Multiplicação de Matrizes pelo método tradicional
        mult_matriz(A, B, C, n);
        printf("Tempo da multiĺicação NORMAL:%f *10^(-3) ms\n", (clock() - tempo) / ((double)CLOCKS_PER_SEC)*1000);
        imprimindo(C, n);
        //Preparando matrizes para nova chamada pelo metodo strassen
        for ( i = 0; i < n; i++)
        {
            for ( j = 0; j < n; j++)
            {
                C[i*n+j]=0;
            }
        } 
        //Chamando a Multiplicação de Matrizes pelo método de strassen
        printf("STRASSEN:\n");
        tempo = clock();
        strassen(A, B, C, n, n);
        printf("Tempo da multiĺicação STRASSEN:%f *10^(-3) ms\n", (clock() - tempo) / ((double)CLOCKS_PER_SEC)*1000);
        imprimindo(C, n);
        //Preparando matrizes para nova chamada pelo metodo strassen_reduzido
        for ( i = 0; i < n; i++)
        {
            for ( j = 0; j < n; j++)
            {
                C[i*n+j]=0;
            }
        } 
        //Chamando a Multiplicação de Matrizes pelo método de strassen
        printf("STRASSEN REDUZIDO:\n");
        tempo = clock();
        strassen_reduzido(A, B, C, n, n);
        printf("Tempo da multiĺicação STRASSEN:%f *10^(-3) ms\n", (clock() - tempo) / ((double)CLOCKS_PER_SEC)*1000);
        imprimindo(C, n);
        return;
    }

//Se a chamada do programa tiver parametro, argc==2.
    if (argc==2) 
    {
        
        srand(time(NULL));
        //Transformando parametro string em int
        char *letr;
        long conv=strtol(argv[1], &letr, 10);
        n=conv;
//A dimensão das matrizes deve ser 2^n para a implementação do método de strassen
        if ((n%2)!=0)
        {
            printf("\nApenas dimensões na faixa de 2^n.\n\n" );
            return;
        }

        //alocando espaço para nossas matrizes (A, B, C);
        A = (int *) malloc((n*n) * sizeof(int));
        if(A == NULL){
            printf("Erro de memória!");
        }

        B = (int *) malloc((n*n) * sizeof(int));
        if(B == NULL){
            printf("Erro de memória!");
        }

        C = (int *) malloc((n*n) * sizeof(int));
        if(B == NULL){
            printf("Erro de memória!");
        }

        //preenchendo as matrizes (A, B) com valores de 0 a 9;
        for ( i = 0; i < n; i++)
        {
            for ( j = 0; j < n; j++)
            {
                A[i*n+j]=random()%10;
                B[i*n+j]=random()%10;
            }
        }

        //Preparando matriz para nova chamada pelo metodo tradicional
        for ( i = 0; i < n; i++)
        {
            for ( j = 0; j < n; j++)
            {
                C[i*n+j]=0;
            }
        } 
        printf("Tradicional:\n");
        clock_t tempo;
        tempo = clock();
        mult_matriz(A, B, C, n);
        printf("Tempo da multiĺicação NORMAL:%f *10^(-3) ms\n", (clock() - tempo) / ((double)CLOCKS_PER_SEC)*1000);
        imprimindo(C, n);

        //Preparando matrizes para nova chamada pelo metodo strassen
        for ( i = 0; i < n; i++)
        {
            for ( j = 0; j < n; j++)
            {
                C[i*n+j]=0;
            }
        } 
        printf("STRASSEN:\n");
        tempo = clock();
        strassen(A, B, C, n, n);
        printf("Tempo da multiĺicação STRASSEN:%f *10^(-3) ms\n", (clock() - tempo) / ((double)CLOCKS_PER_SEC)*1000);
        imprimindo(C, n);

        //Preparando matrizes para nova chamada pelo metodo strassen_reduzido
        for ( i = 0; i < n; i++)
        {
            for ( j = 0; j < n; j++)
            {
                C[i*n+j]=0;
            }
        } 

        printf("STRASSEN REDUZIDO:\n");
        tempo = clock();
        strassen_reduzido(A, B, C, n, n);
        printf("Tempo da multiĺicação STRASSEN REDUZIDO:%f *10^(-3) ms\n", (clock() - tempo) / ((double)CLOCKS_PER_SEC)*1000);
        imprimindo(C, n);

        return;
    
    }

    //Caso tenha sido passado mais de 1 parametro, encerrar programa.
    else
    {
        printf("Voce digitou mais parâmetros que o pedido.\n");
        return;
    }

    //Limpando a casa :)
    free(A);
    free(B);
    free(C);

}  
