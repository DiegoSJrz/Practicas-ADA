#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int es_potencia_de_2(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

int** crear_matriz(int n) {
    int** matriz = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        matriz[i] = (int*)malloc(n * sizeof(int));
    return matriz;
}

void liberar_matriz(int** matriz, int n) {
    for (int i = 0; i < n; i++)
        free(matriz[i]);
    free(matriz);
}

/*void imprimir_matriz(int** matriz, int n, const char* nombre) {
    printf("\nMatriz %s:\n", nombre);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%3d ", matriz[i][j]);
        printf("\n");
    }
}*/

void sumar(int n, int** A, int** B, int** resultado) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            resultado[i][j] = A[i][j] + B[i][j];
}

void restar(int n, int** A, int** B, int** resultado) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            resultado[i][j] = A[i][j] - B[i][j];
}

void strassen(int n, int** A, int** B, int** C) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int mitad = n / 2;

    // Reservar submatrices
    int** A11 = crear_matriz(mitad); int** A12 = crear_matriz(mitad);
    int** A21 = crear_matriz(mitad); int** A22 = crear_matriz(mitad);
    int** B11 = crear_matriz(mitad); int** B12 = crear_matriz(mitad);
    int** B21 = crear_matriz(mitad); int** B22 = crear_matriz(mitad);
    int** M1 = crear_matriz(mitad);  int** M2 = crear_matriz(mitad);
    int** M3 = crear_matriz(mitad);  int** M4 = crear_matriz(mitad);
    int** M5 = crear_matriz(mitad);  int** M6 = crear_matriz(mitad);
    int** M7 = crear_matriz(mitad);
    int** temp1 = crear_matriz(mitad); int** temp2 = crear_matriz(mitad);

    // Dividir A y B
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

    // M1 = (A11 + A22) * (B11 + B22)
    sumar(mitad, A11, A22, temp1);
    sumar(mitad, B11, B22, temp2);
    strassen(mitad, temp1, temp2, M1);

    // M2 = (A21 + A22) * B11
    sumar(mitad, A21, A22, temp1);
    strassen(mitad, temp1, B11, M2);

    // M3 = A11 * (B12 - B22)
    restar(mitad, B12, B22, temp1);
    strassen(mitad, A11, temp1, M3);

    // M4 = A22 * (B21 - B11)
    restar(mitad, B21, B11, temp1);
    strassen(mitad, A22, temp1, M4);

    // M5 = (A11 + A12) * B22
    sumar(mitad, A11, A12, temp1);
    strassen(mitad, temp1, B22, M5);

    // M6 = (A21 - A11) * (B11 + B12)
    restar(mitad, A21, A11, temp1);
    sumar(mitad, B11, B12, temp2);
    strassen(mitad, temp1, temp2, M6);

    // M7 = (A12 - A22) * (B21 + B22)
    restar(mitad, A12, A22, temp1);
    sumar(mitad, B21, B22, temp2);
    strassen(mitad, temp1, temp2, M7);

    // Calcular C11, C12, C21, C22
    int** C11 = crear_matriz(mitad); int** C12 = crear_matriz(mitad);
    int** C21 = crear_matriz(mitad); int** C22 = crear_matriz(mitad);

    sumar(mitad, M1, M4, temp1);
    restar(mitad, temp1, M5, temp2);
    sumar(mitad, temp2, M7, C11);

    sumar(mitad, M3, M5, C12);
    sumar(mitad, M2, M4, C21);

    sumar(mitad, M1, M3, temp1);
    restar(mitad, temp1, M2, temp2);
    sumar(mitad, temp2, M6, C22);

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
    liberar_matriz(M1, mitad);  liberar_matriz(M2, mitad);
    liberar_matriz(M3, mitad);  liberar_matriz(M4, mitad);
    liberar_matriz(M5, mitad);  liberar_matriz(M6, mitad);
    liberar_matriz(M7, mitad);
    liberar_matriz(temp1, mitad); liberar_matriz(temp2, mitad);
    liberar_matriz(C11, mitad); liberar_matriz(C12, mitad);
    liberar_matriz(C21, mitad); liberar_matriz(C22, mitad);
}

int main() {
    int n;
    printf("Introduce el tamano de la matriz (potencia de 2): ");
    scanf("%d", &n);

    if (!es_potencia_de_2(n)) {
        printf("Error: el tamano debe ser una potencia de 2.\n");
        return 1;
    }

    int** A = crear_matriz(n);
    int** B = crear_matriz(n);
    int** C = crear_matriz(n);

    srand(time(NULL));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }

   // imprimir_matriz(A, n, "A");
    //imprimir_matriz(B, n, "B");

    clock_t inicio = clock();
    strassen(n, A, B, C);
    clock_t fin = clock();

   // imprimir_matriz(C, n, "C = A x B (Strassen)");

    double tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("\nTiempo de ejecucion: %.6f segundos\n", tiempo);

    liberar_matriz(A, n);
    liberar_matriz(B, n);
    liberar_matriz(C, n);

    return 0;
}