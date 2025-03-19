#include <stdio.h>

void ordenar(int arreglo[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arreglo[j] > arreglo[j + 1]) {
                int temp = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = temp;
            }
        }
    }
}

int dividirJugadores(int skills[], int n) {
    ordenar(skills, n); 
    int izquierda = 0, derecha = n - 1;
    int suma_total = skills[izquierda] + skills[derecha]; // Suma esperada de cada equipo
    int quimica_total = 0;
    
    while (izquierda < derecha) {
        if (skills[izquierda] + skills[derecha] != suma_total) {
            return -1; // No es posible dividir los jugadores en equipos con la misma suma de habilidades
        }
        quimica_total += skills[izquierda] * skills[derecha]; // Producto de habilidades del equipo
        izquierda++;
        derecha--;
    }
    
    return quimica_total;
}

int main() {
    int n;
    printf("Ingrese la cantidad de jugadores (debe ser un numero par): ");
    scanf("%d", &n);
    
    if (n % 2 != 0) {
        printf("El numero de jugadores debe ser par.\n");
        return 1;
    }
    
    int skills[n];
    
    for (int i = 0; i < n; i++) {
        printf("Ingrese las habilidades de el jugador %d: " ,i+1);
        scanf("%d", &skills[i]);
    }
    
    int resultado = dividirJugadores(skills, n);
    printf("la quimica del equipo es: %d\n", resultado);
    return 0;
}