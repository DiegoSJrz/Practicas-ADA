#include <stdio.h>
#include <stdlib.h>

int main() {
    int dividendo, divisor;
    
    printf("Ingrese el dividendo: ");
    scanf("%d", &dividendo);
    
    printf("Ingrese el divisor: ");
    scanf("%d", &divisor);

    if (divisor == 0) {
        printf("Error: Division por cero no permitida.\n");
        return 1;
    }

    int cociente = 0;
    int negativo = 0;

    // Verificar si el resultado debe ser negativo
    if (dividendo < 0 && divisor >= 0) {
        negativo = 1;
        dividendo = abs(dividendo);
    } else if (dividendo >= 0 && divisor < 0) {
        negativo = 1;
        divisor = abs(divisor);
    } else if (dividendo < 0 && divisor < 0) {
        // Si ambos son negativos, convertimos ambos a positivos
        dividendo = abs(dividendo);
        divisor = abs(divisor);
    }

    // Realizar la división
    while (dividendo >= divisor) {
        dividendo -= divisor;
        cociente++;
    }

    // Si el resultado debe ser negativo, lo ponemos negativo
    if (negativo) {
        cociente = -cociente;
    }

    printf("El cociente es: %d\n", cociente);
    return 0;
}