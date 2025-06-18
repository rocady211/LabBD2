
--------------------------REALIZAR VENTA----------------------------
CREATE OR REPLACE FUNCTION check_venta(id_parque INTEGER, fecha TIME, cantEntradas INTEGER, cantiParking INTEGER) 
RETURNS BOOLEAN
AS $$
DECLARE
    existe_parque BOOLEAN;
    capacidadParque INTEGER;
    capacidadOcupada INTEGER;
BEGIN
    existe_parque := false;
    capacidadParque := 0;
    IF NOT existe_parque THEN
        RAISE EXCEPTION 'No existe el parque';
    END IF;
    --Capacidad parque
    SELECT capacidad INTO capacidadParque 
    FROM parque p WHERE p.id_parque = id_parque; 
    IF(capacidadParque >= cantEntradas) THEN 
        RETURN TRUE;
    END IF;
    RAISE EXCEPTION 'No hay espacio disponible';
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION validarEntrada(fecha_input DATE, ci_input INTEGER) 
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




--------------------------TRIGGERS--------------------
--Trigger Validar en Respondable
CREATE OR REPLACE FUNCTION validandoResponsable() 
RETURNS TRIGGER AS $$
DECLARE
    existe BOOLEAN;
BEGIN 
    SELECT EXISTS (
        SELECT 1
        FROM Respondable r
        WHERE NEW.ci = r.ci
    ) INTO existe;

    IF existe THEN
        RETURN NULL;
    ELSE
        RETURN NEW;
    END IF;

END; $$
LANGUAGE plpgsql;

CREATE TRIGGER validarResponsable
BEFORE INSERT ON Responsable FOR EACH ROW EXECUTE PROCEDURE validandoResponsable();


--Trigger para validar antes de insertar en Visitante
CREATE OR REPLACE FUNCTION validandoVisitante() 
RETURNS TRIGGER AS $$
DECLARE
    existe BOOLEAN;
BEGIN 
	
    SELECT EXISTS (
        SELECT 1
        FROM Visitante v
        WHERE NEW.ci = v.ci
    ) INTO existe;

    IF existe THEN
        RETURN NULL;
    ELSE
        RETURN NEW;
    END IF;

END; $$
LANGUAGE plpgsql;

CREATE TRIGGER validarVisitante
BEFORE INSERT ON Visitante FOR EACH ROW EXECUTE PROCEDURE validandoVisitante();


--Trigger insertar en Visitante
CREATE OR REPLACE FUNCTION InsertandoVisitante() 
RETURNS TRIGGER AS $$
BEGIN 
    INSERT INTO Visitante (ci_visitante)
        VALUES(NEW.ci_visitante);
END; $$
LANGUAGE plpgsql;

CREATE TRIGGER insertarVisitante
AFTER INSERT ON PASE FOR EACH ROW EXECUTE PROCEDURE InsertandoVisitante();


CREATE OR REPLACE FUNCTION InsertandoFactura() 
RETURNS TRIGGER AS $$
BEGIN 
    INSERT INTO Factura (fecha, codigo)
        VALUES(NOW(), NEW.codigo);
END; $$
LANGUAGE plpgsql;

CREATE TRIGGER insertarFactura
BEFORE INSERT ON PASE FOR EACH ROW EXECUTE PROCEDURE InsertandoFactura();