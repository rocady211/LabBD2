#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

EXEC SQL BEGIN DECLARE SECTION;
    char nombre[100];
    int id_parque;
    char fechaStr[20];
    int cantEntradas;
    int estacionamientos;
    int parking;
    int resultado;
EXEC SQL END DECLARE SECTION;

EXEC SQL WHENEVER SQLWARNING SQLPRINT;
EXEC SQL WHENEVER NOT FOUND SQLPRINT;

void Conectar() {
    EXEC SQL CONNECT TO lab02BD:5432 USER postgres;

    if (sqlca.sqlcode != 0) {
        printf("TIPO DE ERROR: %ld\n", sqlca.sqlcode);
        printf("MENSAJE: %s\n", sqlca.sqlerrm.sqlerrmc);
    }
}

void Desconectar() {
    EXEC SQL DISCONNECT ALL;
}

void space() {
    printf("\n-------------------------------\n");
}

typedef struct {
    char nombre1[50], nombre2[50], apellido1[50], apellido2[50];
    int cedula;
    bool estacionamiento;
} Persona;

typedef struct {
    int anio;
    int mes;
    int dia;
} Fecha;

void fechaToString(Fecha f, char* buffer, size_t size) {
    snprintf(buffer, size, "%04d-%02d-%02d 00:00:00", f.anio, f.mes, f.dia);
}

bool validarStructFecha(Fecha f) {
    if (f.anio <= 2024) {
        printf("Debe de ingresar un anio valido\n");
        return false;
    } else if (f.mes < 1 || f.mes > 12) {
        printf("Debe de ingresar un mes valido\n");
        return false;
    } else if (
        (f.mes == 1 && (f.dia < 1 || f.dia > 31)) ||
        (f.mes == 2 && (f.dia < 1 || f.dia > 28)) ||
        (f.mes == 3 && (f.dia < 1 || f.dia > 31)) ||
        (f.mes == 4 && (f.dia < 1 || f.dia > 30)) ||
        (f.mes == 5 && (f.dia < 1 || f.dia > 31)) ||
        (f.mes == 6 && (f.dia < 1 || f.dia > 30)) ||
        (f.mes == 7 && (f.dia < 1 || f.dia > 31)) ||
        (f.mes == 8 && (f.dia < 1 || f.dia > 31)) ||
        (f.mes == 9 && (f.dia < 1 || f.dia > 30)) ||
        (f.mes == 10 && (f.dia < 1 || f.dia > 31)) ||
        (f.mes == 11 && (f.dia < 1 || f.dia > 30)) ||
        (f.mes == 12 && (f.dia < 1 || f.dia > 31))
    ) {
        printf("Debe ingresar un d\u00eda v\u00e1lido para el mes seleccionado.\n");
        return false;
    }
    return true;
}

int elegirParques() {
    int parques[100], parqueSeleccionado, i = 0;
    bool existeParque = false;

    EXEC SQL DECLARE cursor_parques CURSOR FOR
        SELECT id_parque, nombre FROM parque;

    EXEC SQL OPEN cursor_parques;

    while (1) {
        EXEC SQL FETCH cursor_parques INTO :id_parque, :nombre;

        if (sqlca.sqlcode == 100) {
            break;
        }

        if (sqlca.sqlcode < 0) {
            printf("Error en FETCH: %s\n", sqlca.sqlerrm.sqlerrmc);
            break;
        }

        printf("\n%d - %s",id_parque, nombre);
        parques[i] = id_parque;
        i++;
    }

    EXEC SQL CLOSE cursor_parques;
    space();
    while (!existeParque) {
        printf("\nElegi un parque valido: ");
        scanf("%d", &parqueSeleccionado);

        for (int j = 0; j < i; j++) {
            if (parques[j] == parqueSeleccionado) {
                existeParque = true;
                break;
            }
        }

        if (!existeParque) {
            printf("Parque no v\u00e1lido. Intente nuevamente.\n");
        }
    }

    return parqueSeleccionado;
}

void RealizarVenta() {
    bool hayResponsable = false;
    int cantPersonas = 0;
    int parqueSeleccionado = 0;
    int ciResponsable = 0;
    Fecha fechaVenta;
    bool esFechaValida = false;
    estacionamientos = 0;

    printf("Selecciona el parque al que desea asistir: ");
    parqueSeleccionado = elegirParques();

    space();

    while (!esFechaValida) {
        printf("Ingrese la fecha de la visita (formato AAAA-MM-DD): ");
        scanf("%d-%d-%d", &fechaVenta.anio, &fechaVenta.mes, &fechaVenta.dia);

        esFechaValida = validarStructFecha(fechaVenta);
    }

    space();

    printf("Ingrese el n\u00famero de personas que desea registrar: ");
    scanf("%d", &cantPersonas);

    Persona arr[cantPersonas];

    if (cantPersonas > 1) {
        printf("Ingrese la c\u00e9dula del responsable: ");
        scanf("%d", &ciResponsable);
        hayResponsable = true;
    }

    space();

    printf("Ingrese los datos de las personas:\n");
    space();

    for (int i = 0; i < cantPersonas; i++) {
        printf("Persona #%d:\n", i + 1);

        printf("Primer nombre: ");
        scanf(" %[^\n]", arr[i].nombre1);

        printf("Segundo nombre (Si aplica): ");
        scanf(" %[^\n]", arr[i].nombre2);

        printf("Primer apellido: ");
        scanf(" %[^\n]", arr[i].apellido1);

        printf("Segundo apellido: ");
        scanf(" %[^\n]", arr[i].apellido2);

        printf("C\u00e9dula: ");
        scanf("%d", &arr[i].cedula);

        printf("\u00bfTiene estacionamiento? (1 = s\u00ed, 0 = no): ");
        int estacionamientoInput;
        scanf("%d", &estacionamientoInput);
        arr[i].estacionamiento = (estacionamientoInput == 1);
        if (estacionamientoInput) {
            estacionamientos++;
        }
        space();
    }

    space();

    id_parque = parqueSeleccionado;
    cantEntradas = cantPersonas;

    fechaToString(fechaVenta, fechaStr, sizeof(fechaStr));

    EXEC SQL SELECT check_venta(:id_parque, TO_TIMESTAMP(:fechaStr, 'YYYY-MM-DD HH24:MI:SS'),
                                :cantEntradas, :estacionamientos, :parking)
    INTO :resultado;

    if (resultado == 1) {
        printf("La venta se ha registrado exitosamente\n");
    } else {
        printf("No se pudo registrar la venta\n");
    }
}

void opcionMenu() {
    int opcion;
    do {
        printf("Bienvenido, elija una opci\u00f3n:\n\n");
        printf("1: Realizar una venta\n");
        printf("2: Validar la entrada\n");
        printf("3: Total recaudado\n");
        printf("4: Salir\n\n");
        printf("Opci\u00f3n: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                RealizarVenta();
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
                printf("Opci\u00f3n no v\u00e1lida. Por favor intente de nuevo.\n");
        }
    } while (opcion != 4);
}

int main() {
    Conectar();
    opcionMenu();
    Desconectar();
    return 0;
}