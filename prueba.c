#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void opcionMenu();

typedef struct {
    char nombre1[50], nombre2[50], apellido1[50], apellido2[50];
    int cedula;
} Persona;

void connect (bool conectar) {
    if(conectar) {
        //EXEC SQL CONNECT TO 'lab02@localhost' USER postgres IDENTIFIED BY postgres;
        return;
    } 
    // EXEC SQL DISCONNECT;
}


void RealizarVenta () {
    int idParque;
    mostrarParques();

    printf("Seleccione el numero del paruqe al que desea ingresar");

    bool hayReponsable = false;
    int cantPersonas = 0;
    
    scanf("%d", &cantPersonas);
    Persona arr[cantPersonas];

    for(int i = 0; i < cantPersonas; i++) {
        Persona p;
        printf("Por favor ingrese los siguientes datos de la persona\n", i);
        
        printf("Cedula de identidad \n", i);
        scanf("%d", &p.cedula);

        printf("Primer nombre\n", i);
        scanf("%s", &p.nombre1);
        
        printf("Segundo nombre (Si aplica, sino presione Enter) \n", i);
        scanf("%s", &p.nombre2);
        
        printf("Primer apellido\n");
        scanf("%s", &p.apellido1);

        printf("Segundo apellido (Si aplica, sino presione Enter) \n", i);
        scanf("%s", &p.apellido2);        
    }
};

int elegirParques() {
    int parques[100], parqueSeleccionado, i = 0;
    bool existeParque = false;
    EXEC SQL DECLARE cursor_parques CURSOR FOR
        SELECT id, nombre FROM parque;
    
    EXEC SQL OPEN cursor_parques;
    while(1) {

        EXEC SQL FETCH mi_cursor INTO :nombre, :id;

        if (sqlca.sqlcode == 100) {     // Fin de los datos (no más filas)
            break;
        }

        if (sqlca.sqlcode < 0) {        // Ocurrió un error
            printf("Error en FETCH: %s\n", sqlca.sqlerrm.sqlerrmc);
            break;
        
        }
        printf("%s - %d\n", nombre, id);    
        parques[i] = id;
        i++
        // Crear arreglo con el codigo de los parques
    }
    while(!existeParque) {
        printf("Elegi un parque");
        scanf("%d", parqueSeleccionado);
        for (int j = 0; j < i, j++) {
            if(parques[i] == parqueSeleccionado) {
                existeParque = true;
                break;
            }
        }        
    }

    return parqueSeleccionado;
}
    

int main() {

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

/*      // Como usar cursor
//Declarar cursor
    EXEC SQL DECLARE mi_cursor CURSOR FOR
        SELECT nombre, edad FROM personas;

//Abrir el cursor
    EXEC SQL OPEN mi_cursor;

//Recuperar fila por fila
    while (1) {
        EXEC SQL FETCH mi_cursor INTO :nombre, :edad;

        if (sqlca.sqlcode == 100) {     // Fin de los datos (no más filas)
            break;
        }

        if (sqlca.sqlcode < 0) {        // Ocurrió un error
            printf("Error en FETCH: %s\n", sqlca.sqlerrm.sqlerrmc);
            break;
        }

        printf("Nombre: %s, Edad: %d\n", nombre, edad);
    }

// Cerrar cursor 
    EXEC SQL CLOSE mi_cursor;

*/