#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILAS 18
#define COLUMNAS 18
#define ACCIONES_POR_ESCENA 3
#define MAX_CARACTERES 200

void leerDatosDesdeArchivo(char* archivo, char* datos[], int numElementos) {
    FILE *fp = fopen(archivo, "r");
    if (fp == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    char linea[MAX_CARACTERES];
    int i = 0;
    while (fgets(linea, sizeof(linea), fp) != NULL && i < numElementos) {
        // Eliminar el salto de línea al final de la línea
        linea[strcspn(linea, "\n")] = '\0';
        datos[i] = strdup(linea);
        i++;
    }

    fclose(fp);
}

void leerMatrizDesdeArchivo(char* archivo, int matriz[FILAS][COLUMNAS]) {
    FILE *fp = fopen(archivo, "r");
    if (fp == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            fscanf(fp, "%d", &matriz[i][j]);
        }
    }

    fclose(fp);
}

void jugar(int matriz[FILAS][COLUMNAS], char* acciones[], char* comentarios[]) {
    int acciones_realizadas[FILAS] = {0};

    printf("Bienvenido a la tienda departamental!");
    getchar();
    printf("Elige las acciones que desees realizar");
    getchar();

    int escenas_repetidas = 0;

    while (escenas_repetidas < 2) {
        for (int i = 0; i < FILAS; ++i) {
            system("cls");
            printf("Escena %d:\n", i + 1);
            printf("Acciones disponibles:\n");

            int opciones_disponibles = 0;

            for (int j = 0; j < COLUMNAS; ++j) {
                if (matriz[i][j] == 1 && acciones_realizadas[j] == 0) {
                    printf("%d. %s\n", j + 1, acciones[j]);
                    opciones_disponibles = 1;
                }
            }

            if (!opciones_disponibles) {
                if (escenas_repetidas == 0) {
                    printf("No hay mas opciones en esta escena.\n");
                    getchar();
                } else
                    system("cls");
            } else {
                printf("Elige una accion: ");
                int eleccion;
                scanf("%d", &eleccion);

                if (eleccion < 1 || eleccion > COLUMNAS || acciones_realizadas[eleccion - 1] == 1 || matriz[i][eleccion - 1] != 1) {
                    printf("Accion no valida! Por favor, elige una accion disponible.\n");
                    --i; // Repetir la misma escena
                    getchar();
                    getchar();
                } else {
                    acciones_realizadas[eleccion - 1] = 1;
                    printf("%s. Accion realizada con exito!\n", comentarios[eleccion - 1]);
                    getchar();
                    getchar();
                }
            }
        }

        // Verificar si hay acciones disponibles para repetir
        int hay_acciones_disponibles = 0;
        for (int k = 0; k < COLUMNAS; ++k) {
            if (acciones_realizadas[k] == 0) {
                hay_acciones_disponibles = 1;
                break;
            }
        }

        if (hay_acciones_disponibles) {
            ++escenas_repetidas;
        } else {
            system("cls");
            printf("\nFelicidades! Has completado la historia de compras en la tienda departamental.\nLograste el nivel facil en Liverpool, la siguiente te tocara sobrevivir al infierno de Costco\n");
            break;
        }
    }
}

int main() {
    char* acciones[FILAS];
    char* comentarios[FILAS];
    int matriz[FILAS][COLUMNAS];

    // Leer datos desde archivos de texto
    leerDatosDesdeArchivo("acciones.txt", acciones, FILAS);
    leerDatosDesdeArchivo("comentarios.txt", comentarios, FILAS);
    leerMatrizDesdeArchivo("matriz.txt", matriz);

    // Iniciar el juego
    jugar(matriz, acciones, comentarios);

    // Liberar memoria
    for (int i = 0; i < FILAS; ++i) {
        free(acciones[i]);
        free(comentarios[i]);
    }

    return 0;
}


