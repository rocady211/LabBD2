
--------------------------REALIZAR VENTA----------------------------
CREATE OR REPLACE FUNCTION check_venta(id_parque INTEGER, fecha TIMESTAMP, cantEntradas INTEGER, cantiParking INTEGER, nombreCliente TEXT, PARKING INTEGER) 
RETURNS BOOLEAN
AS $$
DECLARE
    existe_parque BOOLEAN;
    capacidadParque INTEGER;
    capacidadOcupada INTEGER;
BEGIN
    existe_parque := false;
    capacidadParque := 0;
    capacidadOcupada := 0;
    --Chequeo parque
    SELECT INTO existe_parque
    EXISTS(SELECT 1 FROM parque p WHERE id_parque = p.id_parque);

    IF NOT existe_parque THEN
        RAISE EXCEPTION 'No existe el parque';
    END IF;
    --Capacidad parque
    SELECT capacidad INTO capacidadParque 
    FROM parque p 
    WHERE p.id_parque = id_parque;

    --Capacidad ocupada del parque
    SELECT COUNT(*) INTO capacidadOcupada
    FROM pase p 
    WHERE p.id_parque = id_parque AND p.fecha = fecha; 

    if(capacidadOcupada + cantEntradas <= capacidadParque) THEN 
        RETURN TRUE;
    END IF;
    
    RAISE EXCEPTION "No hay espacio disponible";

END;
$$ LANGUAGE plpgsql;

--------------------------VALIDAR ENTRADA----------------------------

CREATE OR REPLACE FUNCTION validar(fecha_input DATE, ci_input INTEGER) 
RETURNS TEXT
AS $$
DECLARE
    existe_pase BOOLEAN;
    ultimo_movimiento BOOLEAN;
BEGIN

    IF fecha_input <= CURRENT_DATE THEN
        RETURN 'Fecha inválida';
    END IF;

    SELECT EXISTS (
        SELECT 1
        FROM Pase
        WHERE fecha = fecha_input AND ci_visitante = ci_input
    ) INTO existe_pase;

    IF NOT existe_pase THEN
        RETURN 'Entrada NO válida';
    END IF;

    SELECT r.entrada_salida INTO ultimo_movimiento FROM Registro r JOIN Pase p
    ON r.codigo = p.codigo
    WHERE p.ci_visitante = ci_input AND p.fecha = fecha_input
    ORDER BY r.hora DESC
    LIMIT 1;

    IF ultimo_movimiento IS NULL OR ultimo_movimiento = FALSE THEN
        RETURN 'Entrada válida';
    ELSE
        RETURN 'Entrada NO válida, ya dentro del parque';
    END IF;
END;
$$ LANGUAGE plpgsql;

-------------------------TOTAL RECAUDADO-------------------------------

CREATE OR REPLACE FUNCTION total(mes_input INTEGER, anio_input INTEGER) 
RETURNS NUMERIC(7,2)
AS $$
DECLARE
    total NUMERIC(7,2);
BEGIN
    SELECT COALESCE(SUM(precio), 0.00)
    INTO total
    FROM Pase
    WHERE EXTRACT(MONTH FROM fecha) = mes_input
        AND EXTRACT(YEAR FROM fecha) = anio_input;

    RETURN total;
END;
$$ LANGUAGE plpgsql;



----------------SALIR--------------

#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

PGconn *conexion;

void finalizar_aplicacion() {
    // Cerrar la conexión
    if (conexion != NULL) {
        PQfinish(conexion);
        printf("Conexión a PostgreSQL cerrada correctamente.\n");
    }

    // Finalizar programa
    printf("Saliendo de la aplicación...\n");
    exit(EXIT_SUCCESS);
}