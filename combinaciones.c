#include <stdio.h>
#include <string.h>


char map[10][5] = {
    "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};


void generar_combinaciones(char grupos[][5], int num_grupos, int idx[], int profundidad) {
    
    if (profundidad == num_grupos) {
        for (int i = 0; i < num_grupos; i++) {
            printf("%c", grupos[i][idx[i]]);
        }
        printf(" ");
        return;
    }

    
    for (int i = 0; grupos[profundidad][i] != '\0'; i++) {
        idx[profundidad] = i; 
        generar_combinaciones(grupos, num_grupos, idx, profundidad + 1); 
    }
}


int main() {
    char num[5]; 
    char grupos[4][5]; 
    int num_grupos;
    int idx[4] = {0}; 

    printf("Introduce hasta 4 numeros entre 2 y 9: ");
    scanf("%s", num);

    
    num_grupos = strlen(num);
    if (num_grupos < 1 || num_grupos > 4) {
        printf("Debes introducir entre 1 y 4 numeros entre 2 y 9.\n");
        return 1;
    }

    
    for (int i = 0; i < num_grupos; i++) {
        if (num[i] < '2' || num[i] > '9') {
            printf("Los numeros deben estar entre 2 y 9.\n");
            return 1;
        }
    }

    
    for (int i = 0; i < num_grupos; i++) {
        strcpy(grupos[i], map[num[i] - '0']);
    }

    
    printf("Las combinaciones posibles son:\n");
    generar_combinaciones(grupos, num_grupos, idx, 0);
    printf("\n");

    return 0;
}