/* Processed by ecpg (16.9 (Ubuntu 16.9-0ubuntu0.24.04.1)) */
/* These include files are added by the preprocessor */
#include <ecpglib.h>
#include <ecpgerrno.h>
#include <sqlca.h>
/* End of automatic include section */

#line 1 "main.pgc"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* exec sql begin declare section */
          
         

#line 7 "main.pgc"
 short id ;
 
#line 8 "main.pgc"
 char nombre [ 250 ] ;
/* exec sql end declare section */
#line 9 "main.pgc"


/* exec sql whenever sqlerror  sqlprint ; */
#line 11 "main.pgc"

/* exec sql whenever sql_warning  sqlprint ; */
#line 12 "main.pgc"

/* exec sql whenever not found  sqlprint ; */
#line 13 "main.pgc"


void Conectar() {
    { ECPGconnect(__LINE__, 0, "lab02@localhost:5432" , "postgres" , NULL , NULL, 0); 
#line 16 "main.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 16 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 16 "main.pgc"


    if (sqlca.sqlcode!=0){
        printf("TIPO DE ERROR: %d\n", sqlca.sqlcode);
        printf("MENSAJE:%s\n", sqlca.sqlerrm.sqlerrmc);
    }
    else
        printf("Coneccion exitosa\n");
}

void Desconectar() {
    { ECPGdisconnect(__LINE__, "ALL");
#line 27 "main.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 27 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 27 "main.pgc"

}

void space() {
    printf("\n");
}

int main ()
{
 Conectar(); 


 Desconectar();
 return 0;

}

struct Persona {
    char nombre[250];
    int cedula;
    bool estacionamiento;
};

typedef struct {
    int anio;
    int mes;
    int dia;
} Fecha;

bool validarStructFecha(Fecha f) {
    if(f.anio <=2024) {
        printf("Debe de ingresar un anio valido");
        return false;
    }
    else if (f.mes < 1 || f.mes > 12) {
            printf("Debe de ingresar un mes valido");
            return false;
    }       
    else if (
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
        )
    {
        printf("Debe ingresar un día válido para el mes seleccionado.\n");
        return false;
    }
    return true;
}

int elegirParques() {
    int parques[100], parqueSeleccionado, i = 0;
    bool existeParque = false;
    /* declare cursor_parques cursor for select id , nombre from parque */
#line 90 "main.pgc"

    
    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare cursor_parques cursor for select id , nombre from parque", ECPGt_EOIT, ECPGt_EORT);
#line 92 "main.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 92 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 92 "main.pgc"

    while(1) {

        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch cursor_parques", ECPGt_EOIT, 
	ECPGt_char,(nombre),(long)250,(long)1,(250)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_short,&(id),(long)1,(long)1,sizeof(short), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);
#line 95 "main.pgc"

if (sqlca.sqlcode == ECPG_NOT_FOUND) sqlprint();
#line 95 "main.pgc"

if (sqlca.sqlwarn[0] == 'W') sqlprint();
#line 95 "main.pgc"

if (sqlca.sqlcode < 0) sqlprint();}
#line 95 "main.pgc"


        if (sqlca.sqlcode == 100) {     // Fin de los datos (no más filas)
            break;
        }

        if (sqlca.sqlcode < 0) {        // Ocurrió un error
            printf("Error en FETCH: %s\n", sqlca.sqlerrm.sqlerrmc);
            break;
        
        }
        printf("%s - %d\n", nombre, id);    
        parques[i] = id;
        i++;
        // Crear arreglo con el codigo de los parques
    }
    while(!existeParque) {
        printf("Elegi un parque");
        scanf("%d", &parqueSeleccionado);
        for (int j = 0; j < i; j++) {
            if(parques[i] == parqueSeleccionado) {
                existeParque = true;
                break;
            }
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

    //Listar parques(opcional)
    
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

    struct Persona arr[cantPersonas];  

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
        
        printf("Nombre: ");
        scanf(" %[^\n]", arr[i].nombre); 
        
        printf("Cédula: ");
        scanf("%d", &arr[i].cedula);
        
        printf("¿Tiene estacionamiento? (1 = sí, 0 = no): ");
        int estacionamientoInput;
        scanf("%d", &estacionamientoInput);
        arr[i].estacionamiento = (estacionamientoInput == 1);
        
        space();
    }

    space();
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
