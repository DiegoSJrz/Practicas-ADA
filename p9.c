#include <stdio.h>
#include <stdlib.h>

int calcular_agua(int* altura, int tamano) {
    if (tamano <= 2) return 0;

    int izquierda = 0;
    int derecha = tamano - 1;
    int max_izquierda = 0;
    int max_derecha = 0;
    int agua = 0;

    while (izquierda < derecha) {
        if (altura[izquierda] < altura[derecha]) {
            if (altura[izquierda] >= max_izquierda) {
                max_izquierda = altura[izquierda];
            } else {
                agua += max_izquierda - altura[izquierda];
            }
            izquierda++;
        } else {
            if (altura[derecha] >= max_derecha) {
                max_derecha = altura[derecha];
            } else {
                agua += max_derecha - altura[derecha];
            }
            derecha--;
        }
    }

    return agua;
}

int main() {
    int tamano;
    printf("Ingrese la cantidad de elementos: ");
    scanf("%d", &tamano);

    if (tamano <= 0) {
        printf("Tamano invalido.\n");
        return 1;
    }

    int* altura = (int*)malloc(tamano * sizeof(int));
    if (altura == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    printf("Ingrese los elementos separados por espacio:\n");
    for (int i = 0; i < tamano; i++) {
        scanf("%d", &altura[i]);
    }

    int resultado = calcular_agua(altura, tamano);
    printf("El agua atrapada es: %d\n", resultado);

    free(altura);
    return 0;
}