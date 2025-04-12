#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Verifica si un número es potencia de 2
int es_potencia_de_2(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

// Crea una matriz dinámica de tamaño n x n
int** crear_matriz(int n) {
    int** matriz = (int**) malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matriz[i] = (int*) malloc(n * sizeof(int));
    }
    return matriz;
}

// Libera la memoria de una matriz
void liberar_matriz(int** matriz, int n) {
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

// Imprime una matriz
/*void imprimir_matriz(int** matriz, int n, const char* nombre) {
    printf("\nMatriz %s:\n", nombre);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d ", matriz[i][j]);
        }
        printf("\n");
    }
}*/

// Suma de matrices
void sumar(int n, int** A, int** B, int** resultado) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            resultado[i][j] = A[i][j] + B[i][j];
}

// Multiplicación por Divide and Conquer
void multiplicar_DAC(int n, int** A, int** B, int** C) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int mitad = n / 2;

    // Crear submatrices
    int** A11 = crear_matriz(mitad); int** A12 = crear_matriz(mitad);
    int** A21 = crear_matriz(mitad); int** A22 = crear_matriz(mitad);
    int** B11 = crear_matriz(mitad); int** B12 = crear_matriz(mitad);
    int** B21 = crear_matriz(mitad); int** B22 = crear_matriz(mitad);
    int** C11 = crear_matriz(mitad); int** C12 = crear_matriz(mitad);
    int** C21 = crear_matriz(mitad); int** C22 = crear_matriz(mitad);
    int** M1  = crear_matriz(mitad); int** M2  = crear_matriz(mitad);

    // Dividir matrices en submatrices
    for (int i = 0; i < mitad; i++) {
        for (int j = 0; j < mitad; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + mitad];
            A21[i][j] = A[i + mitad][j];
            A22[i][j] = A[i + mitad][j + mitad];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mitad];
            B21[i][j] = B[i + mitad][j];
            B22[i][j] = B[i + mitad][j + mitad];
        }
    }

    // C11 = A11*B11 + A12*B21
    multiplicar_DAC(mitad, A11, B11, M1);
    multiplicar_DAC(mitad, A12, B21, M2);
    sumar(mitad, M1, M2, C11);

    // C12 = A11*B12 + A12*B22
    multiplicar_DAC(mitad, A11, B12, M1);
    multiplicar_DAC(mitad, A12, B22, M2);
    sumar(mitad, M1, M2, C12);

    // C21 = A21*B11 + A22*B21
    multiplicar_DAC(mitad, A21, B11, M1);
    multiplicar_DAC(mitad, A22, B21, M2);
    sumar(mitad, M1, M2, C21);

    // C22 = A21*B12 + A22*B22
    multiplicar_DAC(mitad, A21, B12, M1);
    multiplicar_DAC(mitad, A22, B22, M2);
    sumar(mitad, M1, M2, C22);

    // Combinar submatrices en C
    for (int i = 0; i < mitad; i++) {
        for (int j = 0; j < mitad; j++) {
            C[i][j] = C11[i][j];
            C[i][j + mitad] = C12[i][j];
            C[i + mitad][j] = C21[i][j];
            C[i + mitad][j + mitad] = C22[i][j];
        }
    }

    // Liberar memoria
    liberar_matriz(A11, mitad); liberar_matriz(A12, mitad);
    liberar_matriz(A21, mitad); liberar_matriz(A22, mitad);
    liberar_matriz(B11, mitad); liberar_matriz(B12, mitad);
    liberar_matriz(B21, mitad); liberar_matriz(B22, mitad);
    liberar_matriz(C11, mitad); liberar_matriz(C12, mitad);
    liberar_matriz(C21, mitad); liberar_matriz(C22, mitad);
    liberar_matriz(M1, mitad);  liberar_matriz(M2, mitad);
}

int main() {
    int n;
    printf("Introduce el tamano de la matriz (potencia de 2): ");
    scanf("%d", &n);

    if (!es_potencia_de_2(n)) {
        printf("Error: el tamano debe ser una potencia de 2.\n");
        return 1;
    }

    // Crear matrices dinámicamente
    int** A = crear_matriz(n);
    int** B = crear_matriz(n);
    int** C = crear_matriz(n);

    // Llenar A y B con valores aleatorios y mostrar
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }

    //imprimir_matriz(A, n, "A");
    //imprimir_matriz(B, n, "B");

    // Medir tiempo
    clock_t inicio = clock();
    multiplicar_DAC(n, A, B, C);
    clock_t fin = clock();

    //imprimir_matriz(C, n, "C = A x B");

    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("\nTiempo de ejecucion: %.6f segundos\n", tiempo);

    // Liberar memoria
    liberar_matriz(A, n);
    liberar_matriz(B, n);
    liberar_matriz(C, n);

    return 0;
}