#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Crear una matriz de tamaño n x n
int** crearMatriz(int n) {
    int** matriz = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matriz[i] = (int*)malloc(n * sizeof(int));
    }
    return matriz;
}

// Liberar memoria de una matriz
void liberarMatriz(int** matriz, int n) {
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

// Llenar una matriz con números aleatorios
void llenarMatriz(int** matriz, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = rand() % 10;  // Números entre 0 y 9
        }
    }
}

// Imprimir una matriz de tamaño n x n
/*void imprimirMatriz(int** matriz, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}*/

// Multiplicación tradicional de matrices
void multiplicarMatrices(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    int n;

    printf("Introduce el tamano de las matrices (potencia de 2): ");
    scanf("%d", &n);

    srand(time(NULL));  // Semilla para números aleatorios

    // Crear matrices dinámicamente
    int** A = crearMatriz(n);
    int** B = crearMatriz(n);
    int** C = crearMatriz(n);

    // Llenar las matrices A y B con números aleatorios
    llenarMatriz(A, n);
    llenarMatriz(B, n);

    // Imprimir matrices A y B antes de la multiplicación
    //printf("Matriz A:\n");
    //imprimirMatriz(A, n);

    //printf("Matriz B:\n");
    //imprimirMatriz(B, n);

    // Medir el tiempo de ejecución
    clock_t inicio = clock();

    multiplicarMatrices(A, B, C, n);

    clock_t fin = clock();

    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucin: %.6f segundos\n", tiempo);

    // Imprimir la matriz resultante C
    //printf("Matriz C (Resultado de A x B):\n");
    //imprimirMatriz(C, n);

    // Liberar memoria
    liberarMatriz(A, n);
    liberarMatriz(B, n);
    liberarMatriz(C, n);

    return 0;
}