#include <stdio.h>

#define N 4  // Numero de articulos
#define W 4  // Capacidad maxima de la mochila

int main() {
    int pesos[N+1] = {0, 1, 4, 3, 1};      // indice 0 no se usa
    int valores[N+1] = {0, 1500, 3000, 2000, 2000}; // indice 0 no se usa
    char* nombres[N+1] = {"", "Guitarra", "Estereo", "Laptop", "iPhone"};

    int dp[N+1][W+1];  // Tabla para programacion dinamica

    // Inicializar la tabla y mostrar paso a paso
    for (int i = 0; i <= N; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
                if (i == 0 || w == 0) {
                    printf("dp[%d][%d]=0 (ningun articulo o capacidad 0)\n", i, w);
                }
            } else if (pesos[i] <= w) {
                int incluir = valores[i] + dp[i-1][w - pesos[i]];
                int excluir = dp[i-1][w];
                dp[i][w] = (incluir > excluir) ? incluir : excluir;

                printf("dp[%d][%d]: evaluando %s (peso: %d, valor: %d)\n", i, w, nombres[i], pesos[i], valores[i]);
                printf(" - Incluirlo: valor = %d (valor actual: %d + mejor valor con peso restante: %d)\n", incluir, valores[i], dp[i-1][w - pesos[i]]);
                printf(" - Excluirlo: valor = %d\n", excluir);
                printf(" - Mejor opcion: %d\n", dp[i][w]);
            } else {
                dp[i][w] = dp[i-1][w];
                printf("dp[%d][%d]: %s no cabe (peso: %d > capacidad: %d)\n", i, w, nombres[i], pesos[i], w);
                printf(" - Mantengo el valor anterior: %d\n", dp[i][w]);
            }
        }
    }

    // Imprimir la tabla final
    printf("\nTabla DP final:\n");
    for (int i = 0; i <= N; i++) {
        for (int w = 0; w <= W; w++) {
            printf("%4d ", dp[i][w]);
        }
        printf("\n");
    }

    // Resultado final
    printf("\nValor maximo en la mochila de capacidad %d lb: $%d\n", W, dp[N][W]);

    // Recuperar los articulos seleccionados
    printf("Articulos seleccionados:\n");
    int w = W;
    for (int i = N; i > 0 && w > 0; i--) {
        if (dp[i][w] != dp[i-1][w]) {
            printf(" - %s (valor: $%d, peso: %d lb)\n", nombres[i], valores[i], pesos[i]);
            w -= pesos[i];
        }
    }

    return 0;
}
