/* Processed by ecpg (16.9 (Ubuntu 16.9-0ubuntu0.24.04.1)) */
/* These include files are added by the preprocessor */
#include <ecpglib.h>
#include <ecpgerrno.h>
#include <sqlca.h>
/* End of automatic include section */

#line 1 "main.pgc"
#include <stdio.h>
#include <stdlib.h>


#line 1 "/usr/include/postgresql/sqlca.h"
#ifndef POSTGRES_SQLCA_H
#define POSTGRES_SQLCA_H

#ifndef PGDLLIMPORT
#if  defined(WIN32) || defined(__CYGWIN__)
#define PGDLLIMPORT __declspec (dllimport)
#else
#define PGDLLIMPORT
#endif							/* __CYGWIN__ */
#endif							/* PGDLLIMPORT */

#define SQLERRMC_LEN	150

#ifdef __cplusplus
extern "C"
{
#endif

struct sqlca_t
{
	char		sqlcaid[8];
	long		sqlabc;
	long		sqlcode;
	struct
	{
		int			sqlerrml;
		char		sqlerrmc[SQLERRMC_LEN];
	}			sqlerrm;
	char		sqlerrp[8];
	long		sqlerrd[6];
	/* Element 0: empty						*/
	/* 1: OID of processed tuple if applicable			*/
	/* 2: number of rows processed				*/
	/* after an INSERT, UPDATE or				*/
	/* DELETE statement					*/
	/* 3: empty						*/
	/* 4: empty						*/
	/* 5: empty						*/
	char		sqlwarn[8];
	/* Element 0: set to 'W' if at least one other is 'W'	*/
	/* 1: if 'W' at least one character string		*/
	/* value was truncated when it was			*/
	/* stored into a host variable.             */

	/*
	 * 2: if 'W' a (hopefully) non-fatal notice occurred
	 */	/* 3: empty */
	/* 4: empty						*/
	/* 5: empty						*/
	/* 6: empty						*/
	/* 7: empty						*/

	char		sqlstate[5];
};

struct sqlca_t *ECPGget_sqlca(void);

#ifndef POSTGRES_ECPG_INTERNAL
#define sqlca (*ECPGget_sqlca())
#endif

#ifdef __cplusplus
}
#endif

#endif

#line 4 "main.pgc"

void opcionMenu();

int main() {
    { ECPGconnect(__LINE__, 0, "Lab2BD2" , "postgres" , "'postgres'" , NULL, 0); }
#line 8 "main.pgc"


    if (sqlca.sqlcode != 0) {
        printf("Error al conectar: %s\n", sqlca.sqlerrm.sqlerrmc);
        return 1;
    }

    printf("Conexión exitosa a la base de datos.\n");

    { ECPGdisconnect(__LINE__, "CURRENT");}
#line 17 "main.pgc"


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
