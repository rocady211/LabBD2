#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

EXEC SQL BEGIN DECLARE SECTION;
        short int id;
        char name[250];
EXEC SQL END DECLARE SECTION;

EXEC SQL WHENEVER SQLERROR SQLPRINT;
EXEC SQL WHENEVER SQLWARNING SQLPRINT;
EXEC SQL WHENEVER NOT FOUND SQLPRINT;

void Conectar() {
    EXEC SQL CONNECT TO rrhh@127.0.0.1:5432 USER postgres;

    if (sqlca.sqlcode!=0)
    {
    printf("TIPO DE ERROR: %d\n", sqlca.sqlcode);
    printf("MENSAJE:%s\n", sqlca.sqlerrm.sqlerrmc);
    }
}

void Desconectar() {
    EXEC SQL DISCONNECT ALL;
}

void space() {
    printf("\n-------------------------------\n");
}

int main ()
{
 Conectar(); 


 Desconectar();
 return 0;

};

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
    snprintf(buffer, size, "%04d-%02d-%02d", f.anio, f.mes, f.dia);
}

bool validarStructFecha(Fecha f) {
    if(f.anio <=2024) {
        printf("Debe de ingresar un anio valido);
        return false
    } else if (f.mes < 1 || f.mes > 12) {
        printf("Debe de ingresar un mes valido);
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
        printf("Debe ingresar un día válido para el mes seleccionado.\n");
        return false;
    }
}

int elegirParques() {
    int parques[100], parqueSeleccionado, i = 0;
    bool existeParque = false;
    char nombre[50];
    int id_parque;

    EXEC SQL DECLARE cursor_parques CURSOR FOR
        SELECT id_parque, nombre FROM parque;

    EXEC SQL OPEN cursor_parques;

    while (1) {
        EXEC SQL FETCH cursor_parques INTO :id_parque, :nombre;

        if (sqlca.sqlcode == 100) {  // Fin de datos
            break;
        }

        if (sqlca.sqlcode < 0) {
            printf("Error en FETCH: %s\n", sqlca.sqlerrm.sqlerrmc);
            break;
        }

        printf("%s - %d\n", nombre, id_parque);
        parques[i] = id_parque;
        i++;
    }

    EXEC SQL CLOSE cursor_parques;

    while (!existeParque) {
        printf("Elegí un parque válido: ");
        scanf("%d", &parqueSeleccionado);

        for (int j = 0; j < i; j++) {
            if (parques[j] == parqueSeleccionado) {
                existeParque = true;
                break;
            }
        }

        if (!existeParque) {
            printf("Parque no válido. Intente nuevamente.\n");
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
    int resultado;
    int estacionamientos = 0;

    obtenerParques();

    printf("Selecciona el parque al que desea asistir: ");
    parqueSeleccionado = elegirParques();

    space();

    while(esFechaValida == false) {
        printf("Ingrese la fecha de la visita (formato AAAA-MM-DD): ");
        scanf("%d-%d-%d", &fechaVenta.anio, &fechaVenta.mes, &fechaVenta.dia);

        esFechaValida = validarStructFecha(fechaVenta);
    }

    space();

    printf("Ingrese el número de personas que desea registrar: ");
    scanf("%d", &cantPersonas); 

    Persona arr[cantPersonas];  

    if (cantPersonas > 1) {
        printf("Ingrese la cédula del responsable: ");
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

        printf("Cédula: ");
        scanf("%d", &arr[i].cedula);

        printf("¿Tiene estacionamiento? (1 = sí, 0 = no): ");
        int estacionamientoInput;
        scanf("%d", &estacionamientoInput);
        arr[i].estacionamiento = (estacionamientoInput == 1);
        if(estacionamientoInput) {
            estacionamientos ++;
        }        
        space();
    }

    space();

    char fechaStr[20];
    fechaToString(fechaVenta, fechaStr, sizeof(fechaStr));


    EXEC SQL SELECT check_venta(:id_parque, TO_TIMESTAMP(:fechaStr, 'YYYY-MM-DD HH24:MI:SS'), 
                            :cantEntradas, :estacionamientos, :parking)
    INTO :resultado;

    if(resultado == true) {
        printf("La venta se ha registrado exitosamente");
    }
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
