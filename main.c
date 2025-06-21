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

     
     
     
     
     
     
     
     

     
     
     
     
     
     
       
     

     
     
     
     

     
     
     
     
     

     
     
     

    
       
       



#line 8 "main.pgc"
 char nombre [ 100 ] ;
 
#line 9 "main.pgc"
 int id_parque_ ;
 
#line 10 "main.pgc"
 char fechaStr_ [ 20 ] ;
 
#line 11 "main.pgc"
 int cantEntradas_ ;
 
#line 12 "main.pgc"
 int cant_estacionamientos_ ;
 
#line 13 "main.pgc"
 char resultado_ [ 1 ] ;
 
#line 14 "main.pgc"
 char resultado2_ [ 100 ] ;
 
#line 15 "main.pgc"
 char fechita [ 20 ] ;
 
#line 17 "main.pgc"
 char nombre1_ [ 100 ] ;
 
#line 18 "main.pgc"
 char nombre2_ [ 100 ] ;
 
#line 19 "main.pgc"
 char apellido1_ [ 100 ] ;
 
#line 20 "main.pgc"
 char apellido2_ [ 100 ] ;
 
#line 21 "main.pgc"
 char ci_visitante_ [ 8 ] ;
 
#line 22 "main.pgc"
 int estacionamiento_ ;
 
#line 23 "main.pgc"
 double precio_ = 0 ;
 
#line 24 "main.pgc"
 char url_pase_ [ 255 ] ;
 
#line 26 "main.pgc"
 int nro_tarjeta_ ;
 
#line 27 "main.pgc"
 char cvv_ [ 3 ] ;
 
#line 28 "main.pgc"
 char tipo_ [ 50 ] ;
 
#line 29 "main.pgc"
 char vencimiento_ [ 50 ] ;
 
#line 31 "main.pgc"
 char ciResp_ [ 8 ] ;
 
#line 32 "main.pgc"
 char nombre1_resp_ [ 100 ] ;
 
#line 33 "main.pgc"
 char nombre2_resp_ [ 100 ] ;
 
#line 34 "main.pgc"
 char apellido1_resp_ [ 100 ] ;
 
#line 35 "main.pgc"
 char apellido2_resp_ [ 100 ] ;
 
#line 37 "main.pgc"
 int mes_ ;
 
#line 38 "main.pgc"
 int anio_ ;
 
#line 39 "main.pgc"
 float total_ ;
 
#line 42 "main.pgc"
 int esResp = 1 ;
 
#line 43 "main.pgc"
 int esVisitante = 0 ;
/* exec sql end declare section */
#line 46 "main.pgc"




void Conectar() {
    { ECPGconnect(__LINE__, 0, "lab02@localhost:5432" , "postgres" , NULL , NULL, 0); }
#line 51 "main.pgc"


    if (sqlca.sqlcode != 0) {
        printf("TIPO DE ERROR: %ld\n", sqlca.sqlcode);
        printf("MENSAJE: %s\n", sqlca.sqlerrm.sqlerrmc);
    }
}

void Desconectar() {
    { ECPGdisconnect(__LINE__, "ALL");}
#line 60 "main.pgc"

}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // Limpiar buffer
}

void space() {
    printf("\n-------------------------------\n");
}

typedef struct {
    char nombre1[100], nombre2[100], apellido1[100], apellido2[100];
    char cedula[8];
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

    /* declare cursor_parques cursor for select id_parque , nombre from parque */
#line 120 "main.pgc"


    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "declare cursor_parques cursor for select id_parque , nombre from parque", ECPGt_EOIT, ECPGt_EORT);}
#line 122 "main.pgc"


    while (1) {
        { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "fetch cursor_parques", ECPGt_EOIT, 
	ECPGt_int,&(id_parque_),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(nombre),(long)100,(long)1,(100)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 125 "main.pgc"


        if (sqlca.sqlcode == 100) {
            break;
        }

        if (sqlca.sqlcode < 0) {
            printf("Error en FETCH: %s\n", sqlca.sqlerrm.sqlerrmc);
            break;
        }

        printf("\n%d - %s",id_parque_, nombre);
        parques[i] = id_parque_;
        i++;
    }

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "close cursor_parques", ECPGt_EOIT, ECPGt_EORT);}
#line 141 "main.pgc"

    space();
    while (!existeParque) {
    printf("\nElegí un parque válido: ");
    int res = scanf("%d", &parqueSeleccionado);
    if (res != 1) {
        printf("Entrada inválida. Por favor ingrese un número.\n");
        limpiarBuffer();
        continue;
    }

    existeParque = false;
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
    char ciResponsable[8];

    Fecha fechaVenta;
    bool esFechaValida = false;
    int cantEstacionamientos = 0;
    int nroTarjeta = 0;
    Persona responsable;

    printf("Selecciona el parque al que desea asistir: ");
    parqueSeleccionado = elegirParques();

    space();

    while (!esFechaValida) {
        printf("Ingrese la fecha de la visita (formato AAAA-MM-DD): ");
        int resultado = scanf("%d-%d-%d", &fechaVenta.anio, &fechaVenta.mes, &fechaVenta.dia);

        if (resultado != 3) {
            printf("Formato inválido. Intente nuevamente.\n");
            limpiarBuffer();
            continue;
        }

        esFechaValida = validarStructFecha(fechaVenta);

        if (!esFechaValida) {
            printf("Fecha no válida lógicamente. Intente de nuevo.\n");
        }
    }

    space();

    printf("Ingrese el número de personas que desea registrar: ");
    scanf("%d", &cantPersonas);
    limpiarBuffer();

    if (cantPersonas <= 0) {
        printf("Debe ingresar al menos una persona.\n");
        return;
    }

    Persona arr[cantPersonas];
    int nro_tarjeta;
    char tipo[50];
    char cvv[4];
    char vencimiento[50];

    if (cantPersonas > 1) {
        printf("Ingrese los datos del responsable: ");

        printf("\nPrimer nombre: ");
        scanf(" %[^\n]", responsable.nombre1);

        printf("Segundo nombre (Si aplica): ");
        scanf(" %[^\n]", responsable.nombre2);

        printf("Primer apellido: ");
        scanf(" %[^\n]", responsable.apellido1);

        printf("Segundo apellido: ");
        scanf(" %[^\n]", responsable.apellido2);

        printf("Ingrese datos de la tarjeta: ");

        printf("\n    Número de tarjeta: ");
        scanf("%d", &nro_tarjeta);
        limpiarBuffer();

        printf("    Tipo (crédito / débito): ");
        scanf(" %49[^\n]", tipo);

        printf("    CVV: ");
        scanf(" %3[^\n]", cvv);

        printf("    Vencimiento: ");
        scanf(" %49[^\n]", vencimiento);

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
        scanf(" %7[^\n]", arr[i].cedula);

        int estacionamientoInput;
        do {
            printf("\n¿Tiene estacionamiento? (1 = Sí, 0 = No): ");
            int res = scanf("%d", &estacionamientoInput);

            if (res != 1) {
                printf("Entrada inválida. Por favor ingrese 1 o 0.\n");
                limpiarBuffer();
                continue;
            }

            if (estacionamientoInput != 0 && estacionamientoInput != 1) {
                printf("Por favor ingrese solo 1 (Sí) o 0 (No).\n");
            }
        } while (estacionamientoInput != 0 && estacionamientoInput != 1);

        arr[i].estacionamiento = (estacionamientoInput == 1);
        if (estacionamientoInput) {
            cantEstacionamientos++;
        }
        limpiarBuffer();
    }

    space();

    id_parque_ = parqueSeleccionado;
    cant_estacionamientos_ = cantEstacionamientos;
    cantEntradas_ = cantPersonas;

    fechaToString(fechaVenta, fechaStr_, sizeof(fechaStr_));

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select check_venta ( $1  , TO_DATE ( $2  , 'YYYY-MM-DD' ) , $3  , $4  )", 
	ECPGt_int,&(id_parque_),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(fechaStr_),(long)20,(long)1,(20)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(cantEntradas_),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(cant_estacionamientos_),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_char,&(resultado_),(long)1,(long)1,(1)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 311 "main.pgc"


    printf("res es %s\n", resultado_);

    if (sqlca.sqlcode < 0) {
        printf("Error en check_venta: %s\n", sqlca.sqlerrm.sqlerrmc);
    } else {
        if (strcmp(resultado_, "t") == 0) {
            if (cantPersonas > 1) {
                memcpy(ciResp_, responsable.cedula, sizeof(responsable.cedula));
                memcpy(nombre1_resp_, responsable.nombre1, sizeof(responsable.nombre1));
                memcpy(nombre2_resp_, responsable.nombre2, sizeof(responsable.nombre2));
                memcpy(apellido1_resp_, responsable.apellido1, sizeof(responsable.apellido1));
                memcpy(apellido2_resp_, responsable.apellido2, sizeof(responsable.apellido2));

                { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select insertarcliente ( $1  , $2  , $3  , $4  , $5  , $6  )", 
	ECPGt_char,(ciResp_),(long)8,(long)1,(8)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(nombre1_resp_),(long)100,(long)1,(100)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(nombre2_resp_),(long)100,(long)1,(100)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(apellido1_resp_),(long)100,(long)1,(100)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(apellido2_resp_),(long)100,(long)1,(100)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(esResp),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 327 "main.pgc"

            } else {
                memcpy(ci_visitante_, arr[0].cedula, sizeof(arr[0].cedula));
                strcpy(nombre1_, arr[0].nombre1);
                strcpy(nombre2_, arr[0].nombre2);
                strcpy(apellido1_, arr[0].apellido1);
                strcpy(apellido2_, arr[0].apellido2);

                { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select insertarcliente ( $1  , $2  , $3  , $4  , $5  , $6  )", 
	ECPGt_char,(ciResp_),(long)8,(long)1,(8)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(nombre1_),(long)100,(long)1,(100)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(nombre2_),(long)100,(long)1,(100)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(apellido1_),(long)100,(long)1,(100)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(apellido2_),(long)100,(long)1,(100)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(esResp),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 336 "main.pgc"


            }

            bool huboError = false;

            for (int i = 0; i < cantPersonas && !huboError; i++) {
                // Copiar datos a variables de SQL
                strcpy(nombre1_, arr[i].nombre1);
                strcpy(nombre2_, arr[i].nombre2);
                strcpy(apellido1_, arr[i].apellido1);
                strcpy(apellido2_, arr[i].apellido2);
                strcpy(url_pase_, "no hay url");
                memcpy(ci_visitante_, arr[i].cedula, sizeof(arr[i].cedula));
                estacionamiento_ = arr[i].estacionamiento;
                nro_tarjeta_ = nro_tarjeta;
                id_parque_ = parqueSeleccionado;
                printf("Precio: %.2f\n", precio_);
                { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select ( select precio from precio p where p . id_parque = $1  and TO_DATE ( $2  , 'YYYY-MM-DD' ) between p . fecha_ini and p . fecha_fin order by p . fecha_ini desc limit 1 )", 
	ECPGt_int,&(id_parque_),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(fechaStr_),(long)20,(long)1,(20)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_double,&(precio_),(long)1,(long)1,sizeof(double), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 361 "main.pgc"

                printf("Precio: %.2f\n", precio_);
        
                if (sqlca.sqlcode == 100) {
                    printf("No se encontró un precio válido para esa fecha.\n");
                    huboError = true;
                    { ECPGtrans(__LINE__, NULL, "rollback");}
#line 367 "main.pgc"

                    return;
                }
                else if (sqlca.sqlcode < 0) {
                    printf("Error al obtener precio: %s\n", sqlca.sqlerrm.sqlerrmc);
                    huboError = true;
                    { ECPGtrans(__LINE__, NULL, "rollback");}
#line 373 "main.pgc"

                    return;
                }

                if (sqlca.sqlcode < 0) {
                    printf("Error al obtener precio: %s\n", sqlca.sqlerrm.sqlerrmc);
                    huboError = true;
                    break;
                }

                { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "insert into pase ( ci_visitante , nro_tarjeta , estacionamiento , id_parque , precio , fecha , url_pase ) values ( $1  , $2  , $3  , $4  , $5  , TO_DATE ( $6  , 'YYYY-MM-DD' ) , $7  )", 
	ECPGt_char,(ci_visitante_),(long)8,(long)1,(8)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(nro_tarjeta_),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(estacionamiento_),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(id_parque_),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_double,&(precio_),(long)1,(long)1,sizeof(double), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(fechaStr_),(long)20,(long)1,(20)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(url_pase_),(long)255,(long)1,(255)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 389 "main.pgc"


                if (sqlca.sqlcode < 0) {
                    printf("Error al insertar pase: %s\n", sqlca.sqlerrm.sqlerrmc);
                    huboError = true;
                    break;
                }

                { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select insertarcliente ( $1  , $2  , $3  , $4  , $5  , $6  )", 
	ECPGt_char,(ci_visitante_),(long)8,(long)1,(8)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(nombre1_),(long)100,(long)1,(100)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(nombre2_),(long)100,(long)1,(100)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(apellido1_),(long)100,(long)1,(100)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(apellido2_),(long)100,(long)1,(100)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(esVisitante),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 399 "main.pgc"


                if (sqlca.sqlcode < 0) {
                    printf("Error al insertar cliente: %s\n", sqlca.sqlerrm.sqlerrmc);
                    huboError = true;
                    break;
                }
            }

            if (!huboError) {
                { ECPGtrans(__LINE__, NULL, "commit");}
#line 409 "main.pgc"

                printf("Commit exitoso.\n");
            } else {
                { ECPGtrans(__LINE__, NULL, "rollback");}
#line 412 "main.pgc"

                printf("Ocurrió un error. Se deshicieron los cambios.\n");
            }

        } else {
            printf("No se pudo registrar la venta\n");
        }
    }
}



void validarEntrada() {
    Fecha fechaVenta;
    bool esFechaValida = false;
    char cedula[8];

    while (!esFechaValida) {
        printf("Ingrese la fecha de la visita (formato AAAA-MM-DD): ");
        
        int resultado = scanf("%d-%d-%d", &fechaVenta.anio, &fechaVenta.mes, &fechaVenta.dia);

        if (resultado != 3) {
            printf("Formato inválido. Intente nuevamente.\n");

            limpiarBuffer();
            continue;
        }

        esFechaValida = validarStructFecha(fechaVenta);

        if (!esFechaValida) {
            printf("Fecha no válida lógicamente. Intente de nuevo.\n");
        }
    }

    printf("C\u00e9dula: ");
    scanf("%c", cedula);

    fechaToString(fechaVenta, fechaStr_, sizeof(fechaStr_));
    memcpy(ci_visitante_, cedula, sizeof(cedula));

    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select validarEntrada ( TO_DATE ( fechaStr_ , 'YYYY-MM-DD' ) , $1  ) , $2 ", 
	ECPGt_char,(ci_visitante_),(long)8,(long)1,(8)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_char,(resultado2_),(long)100,(long)1,(100)*sizeof(char), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, ECPGt_EORT);}
#line 454 "main.pgc"

    printf("%s", resultado2_);
}

void totalRecaudado() {
    int mes, anio;
    float total = 0.0;
    printf("Ingrese la fecha a consultar (formato AAAA-MM): ");
    scanf("%d-%d", &anio, &mes);

    mes_ = mes;
    anio_ = anio;
    total_ = total;
    { ECPGdo(__LINE__, 0, 1, NULL, 0, ECPGst_normal, "select total ( $1  , $2  )", 
	ECPGt_int,&(mes_),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, 
	ECPGt_int,&(anio_),(long)1,(long)1,sizeof(int), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EOIT, 
	ECPGt_float,&(total_),(long)1,(long)1,sizeof(float), 
	ECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ECPGt_EORT);}
#line 470 "main.pgc"

    
    printf("El total recaudado en la fecha elegida es: ");
    printf("%f", total_);
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
                validarEntrada();
                break;
            case 3:
                totalRecaudado();
                break;
            case 4:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Por favor intente de nuevo.\n");
        }
    } while (opcion != 4);
}

int main() {
    Conectar();
    opcionMenu();
    Desconectar();
    return 0;
}