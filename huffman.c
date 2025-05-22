#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 256

typedef struct Nodo {
    char caracter;
    int frecuencia;
    struct Nodo *izq, *der;
} Nodo;

typedef struct MinHeap {
    int tamano;
    int capacidad;
    Nodo** array;
} MinHeap;

Nodo* nuevoNodo(char caracter, int frecuencia) {
    Nodo* nodo = (Nodo*) malloc(sizeof(Nodo));
    nodo->caracter = caracter;
    nodo->frecuencia = frecuencia;
    nodo->izq = nodo->der = NULL;
    return nodo;
}

MinHeap* crearMinHeap(int capacidad) {
    MinHeap* minHeap = (MinHeap*) malloc(sizeof(MinHeap));
    minHeap->tamano = 0;
    minHeap->capacidad = capacidad;
    minHeap->array = (Nodo**) malloc(capacidad * sizeof(Nodo*));
    return minHeap;
}

void intercambiarNodo(Nodo** a, Nodo** b) {
    Nodo* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* minHeap, int i) {
    int menor = i;
    int izq = 2 * i + 1;
    int der = 2 * i + 2;

    if (izq < minHeap->tamano && minHeap->array[izq]->frecuencia < minHeap->array[menor]->frecuencia)
        menor = izq;

    if (der < minHeap->tamano && minHeap->array[der]->frecuencia < minHeap->array[menor]->frecuencia)
        menor = der;

    if (menor != i) {
        intercambiarNodo(&minHeap->array[i], &minHeap->array[menor]);
        minHeapify(minHeap, menor);
    }
}

void insertarMinHeap(MinHeap* minHeap, Nodo* nodo) {
    int i = minHeap->tamano++;
    while (i && nodo->frecuencia < minHeap->array[(i - 1)/2]->frecuencia) {
        minHeap->array[i] = minHeap->array[(i - 1)/2];
        i = (i - 1)/2;
    }
    minHeap->array[i] = nodo;
}

Nodo* extraerMin(MinHeap* minHeap) {
    Nodo* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[--minHeap->tamano];
    minHeapify(minHeap, 0);
    return temp;
}

MinHeap* construirMinHeap(int frecuencia[]) {
    MinHeap* minHeap = crearMinHeap(TAM);
    for (int i = 0; i < TAM; ++i) {
        if (frecuencia[i]) {
            insertarMinHeap(minHeap, nuevoNodo((char)i, frecuencia[i]));
        }
    }
    return minHeap;
}

Nodo* construirHuffman(int frecuencia[]) {
    MinHeap* minHeap = construirMinHeap(frecuencia);
    while (minHeap->tamano > 1) {
        Nodo* izq = extraerMin(minHeap);
        Nodo* der = extraerMin(minHeap);

        Nodo* fusion = nuevoNodo('$', izq->frecuencia + der->frecuencia);
        fusion->izq = izq;
        fusion->der = der;

        insertarMinHeap(minHeap, fusion);
    }
    return extraerMin(minHeap);
}

void generarCodigos(Nodo* raiz, int arr[], int top, char* codigos[]) {
    if (raiz->izq) {
        arr[top] = 0;
        generarCodigos(raiz->izq, arr, top + 1, codigos);
    }

    if (raiz->der) {
        arr[top] = 1;
        generarCodigos(raiz->der, arr, top + 1, codigos);
    }

    if (!(raiz->izq) && !(raiz->der)) {
        codigos[(unsigned char)raiz->caracter] = (char*) malloc(top + 1);
        for (int i = 0; i < top; ++i)
            codigos[(unsigned char)raiz->caracter][i] = arr[i] + '0';
        codigos[(unsigned char)raiz->caracter][top] = '\0';
    }
}

void codificarArchivo(const char* nombreArchivo, char* codigos[], int* originalBits, int* comprimidoBits) {
    FILE* archivo = fopen(nombreArchivo, "r");
    FILE* salida = fopen("codificado.txt", "w");
    if (!archivo || !salida) {
        printf("Error abriendo archivos.\n");
        return;
    }

    char c;
    while ((c = fgetc(archivo)) != EOF) {
        *originalBits += 8;
        fputs(codigos[(unsigned char)c], salida);
        *comprimidoBits += strlen(codigos[(unsigned char)c]);
    }

    fclose(archivo);
    fclose(salida);
}

void decodificarArchivo(Nodo* raiz, const char* archivoCodificado) {
    FILE* entrada = fopen(archivoCodificado, "r");
    if (!entrada) {
        printf("Error abriendo codificado.txt para decodificar.\n");
        return;
    }

    printf("\nTexto decodificado:\n");
    Nodo* actual = raiz;
    char bit;
    while ((bit = fgetc(entrada)) != EOF) {
        if (bit == '0') actual = actual->izq;
        else if (bit == '1') actual = actual->der;

        if (!actual->izq && !actual->der) {
            putchar(actual->caracter);
            actual = raiz;
        }
    }
    putchar('\n');
    fclose(entrada);
}

int main() {
    char nombreArchivo[] = "entrada.txt";
    FILE* archivo = fopen(nombreArchivo, "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo '%s'.\n", nombreArchivo);
        return 1;
    }

    int frecuencia[TAM] = {0};
    char c;
    while ((c = fgetc(archivo)) != EOF) {
        frecuencia[(unsigned char)c]++;
    }
    fclose(archivo);

    Nodo* raiz = construirHuffman(frecuencia);
    char* codigos[TAM] = {0};
    int arr[100];
    generarCodigos(raiz, arr, 0, codigos);

    printf("Caracter\tFrecuencia\tCodigo de Huffman\n");
    for (int i = 0; i < TAM; ++i) {
        if (codigos[i]) {
            if (i == '\n')
                printf("'\\n'\t\t%d\t\t%s\n", frecuencia[i], codigos[i]);
            else if (i == '\t')
                printf("'\\t'\t\t%d\t\t%s\n", frecuencia[i], codigos[i]);
            else if (i == ' ')
                printf("' '\t\t%d\t\t%s\n", frecuencia[i], codigos[i]);
            else
                printf("'%c'\t\t%d\t\t%s\n", i, frecuencia[i], codigos[i]);
        }
    }

    int originalBits = 0, comprimidoBits = 0;
    codificarArchivo(nombreArchivo, codigos, &originalBits, &comprimidoBits);

    printf("\nTamano original: %d bits\n", originalBits);
    printf("Tamano comprimido: %d bits\n", comprimidoBits);
    if (originalBits != 0)
        printf("Tasa de compresion: %.2f%%\n", 100.0 * (1 - (float)comprimidoBits / originalBits));

    decodificarArchivo(raiz, "codificado.txt");

    // Liberar memoria
    for (int i = 0; i < TAM; ++i)
        if (codigos[i])
            free(codigos[i]);

    return 0;
}
