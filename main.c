#include <stdio.h>

void opcionMenu();

int main() {
    opcionMenu();
    return 0;
}

void opcionMenu() {
    int opcion;
    do {
        printf("Bienvenido, elija una opción:\n\n");
        printf("1: Realizar una venta\n");
        printf("2: Validar la entrada\n");
        printf("3: Total recaudado\n");
        printf("4: Salir\n\n");
        printf("Opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Realizando una venta...\n");
                break;
            case 2:
                printf("Validando la entrada...\n");
                break;
            case 3:
                printf("Calculando el total recaudado...\n");
                break;
            case 4:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Por favor intente de nuevo.\n");
        }
    } while (opcion < 1 || opcion > 4);
}
