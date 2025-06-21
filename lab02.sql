CREATE TABLE pase (
    codigo SERIAL,
    ci_visitante CHAR(8),
    nro_tarjeta INT,
    estacionamiento BOOLEAN DEFAULT false,
    id_parque INT,
    precio DECIMAL(10,2),	
    fecha DATE,
    url_pase VARCHAR(1000)
);

CREATE TABLE parque (
    nombre VARCHAR(100),
    id_parque SERIAL,
    id_parking INT,
    capacidad INT
);

CREATE TABLE registro (
    id_registro SERIAL,
    entrada_salida BOOLEAN DEFAULT true,
    hora TIME,
    codigo INT
);

CREATE TABLE precio (
    id_precio SERIAL,
    id_parque INT,
    fecha_ini DATE NOT NULL,
    fecha_fin DATE NOT NULL,
    precio DECIMAL(10,2)
);

CREATE TABLE actividad (
    id_actividad SERIAL,
    id_parque INT,
    nombre VARCHAR(50),
    tipo VARCHAR(20)
);

CREATE TABLE pase_actividad (
    codigo INT,
    id_actividad INT,
    hora TIME
);


CREATE TABLE fotografia (
    id_foto SERIAL, 
    fecha DATE DEFAULT CURRENT_DATE,
    hora TIME DEFAULT CURRENT_TIME,
    url_foto VARCHAR(1000),
    id_actividad INT
);

CREATE TABLE parking (
    id_parking SERIAL,
    capacidad INT,
    precio DECIMAL(10,2)
);

CREATE TABLE cliente (
    ci CHAR(8), 
    nombre1 VARCHAR(50), 
    nombre2 VARCHAR(50),
    apellido1 VARCHAR(50),
    apellido2 VARCHAR(50)
);

CREATE TABLE visitante (
    ci_visitante CHAR(8)
);

CREATE TABLE responsable (
    ci_responsable CHAR(8)
);

CREATE TABLE tarjeta (
    nro_tarjeta INT,
    ci_responsable CHAR(8),
    tipo VARCHAR(50),
    cvv CHAR(3),
    vencimiento CHAR(50)
);

CREATE TABLE dolar (
    valor DECIMAL(10,2),
    fecha DATE DEFAULT CURRENT_DATE,
    hora TIME DEFAULT CURRENT_TIME
);

CREATE TABLE factura (
    id_factura SERIAL,
    descripcion VARCHAR(500),
    fecha DATE DEFAULT CURRENT_DATE,
    codigo INT
);


--Cliente

ALTER TABLE cliente ADD CONSTRAINT pk_cliente PRIMARY KEY (ci);

--Visitante

ALTER TABLE visitante ADD CONSTRAINT pk_visitante PRIMARY KEY (ci_visitante);

ALTER TABLE visitante ADD CONSTRAINT fk_cliente FOREIGN KEY (ci_visitante) REFERENCES cliente(ci);

--Responsable

ALTER TABLE responsable ADD CONSTRAINT pk_responsable PRIMARY KEY (ci_responsable);

ALTER TABLE responsable ADD CONSTRAINT fk_cliente FOREIGN KEY (ci_responsable) REFERENCES cliente(ci);

--Tarjeta

ALTER TABLE tarjeta ADD CONSTRAINT pk_tarjeta  PRIMARY KEY (nro_tarjeta);

ALTER TABLE tarjeta ADD CONSTRAINT fk_responsable FOREIGN KEY (ci_responsable) REFERENCES responsable(ci_responsable);

--Parking

ALTER TABLE parking ADD CONSTRAINT pk_primary PRIMARY KEY (id_parking);

--Parque:

ALTER TABLE parque ADD CONSTRAINT pk_parque  PRIMARY KEY (id_parque);

ALTER TABLE parque ADD CONSTRAINT fk_parking FOREIGN KEY(id_parking)
REFERENCES parking(id_parking);

--Pase:

ALTER TABLE pase ADD CONSTRAINT pk_pase PRIMARY KEY (codigo);

ALTER TABLE pase ADD CONSTRAINT fk_visitante FOREIGN KEY (ci_visitante)
REFERENCES visitante(ci_visitante);

ALTER TABLE pase ADD CONSTRAINT fk_tarjeta FOREIGN KEY  (nro_tarjeta)
REFERENCES tarjeta(nro_tarjeta);

ALTER TABLE pase ADD CONSTRAINT fk_parque FOREIGN KEY (id_parque)
REFERENCES parque(id_parque);

--Registro:

ALTER TABLE registro ADD CONSTRAINT pk_registro PRIMARY KEY (id_registro);

ALTER TABLE registro ADD CONSTRAINT fk_pase FOREIGN KEY (codigo)
REFERENCES pase(codigo);

--Precio

ALTER TABLE precio ADD CONSTRAINT pk_precio PRIMARY KEY (id_precio);

ALTER TABLE precio ADD CONSTRAINT fk_parque FOREIGN KEY (id_parque) 
REFERENCES parque(id_parque);


--Actividad

ALTER TABLE actividad ADD CONSTRAINT pk_actividad PRIMARY KEY (id_actividad);

ALTER TABLE actividad ADD CONSTRAINT uq_tipo CHECK (tipo IN ('entretenimiento', 'juegos'));

ALTER TABLE actividad ADD CONSTRAINT fk_parque FOREIGN KEY (id_parque) 
REFERENCES parque(id_parque);

--Pase_actividad

ALTER TABLE pase_actividad ADD CONSTRAINT pk_codigo_actividad PRIMARY KEY (codigo, id_actividad, hora);

ALTER TABLE pase_actividad ADD CONSTRAINT fk_pase FOREIGN KEY (codigo)
REFERENCES pase(codigo);

ALTER TABLE pase_actividad ADD CONSTRAINT fk_actividad FOREIGN KEY (id_actividad) REFERENCES actividad(id_actividad);

--Fotografia

ALTER TABLE fotografia ADD CONSTRAINT pk_fotografia PRIMARY KEY (id_foto);

ALTER TABLE fotografia ADD CONSTRAINT fk_actividad FOREIGN KEY (id_actividad) 
REFERENCES  actividad(id_actividad); 

--Dolar

ALTER TABLE dolar ADD CONSTRAINT pk_dolar PRIMARY KEY (valor, fecha, hora);

--Factura

ALTER TABLE factura ADD CONSTRAINT pk_factura PRIMARY KEY (id_factura);

ALTER TABLE factura ADD CONSTRAINT fk_factura FOREIGN KEY (codigo) 
REFERENCES  pase(codigo);





-- Parking
INSERT INTO parking (id_parking, capacidad, precio) VALUES 
(1, 100, 50),
(2, 150, 60),
(3, 200, 75);

-- Parque
INSERT INTO parque (nombre, id_parque, id_parking, capacidad) VALUES 
('parque 1',1, 1, 300),
('parque 2',2, 2, 250),
('parque 3',3, 3, 400);

-- Cliente
INSERT INTO cliente (ci, nombre1, nombre2, apellido1, apellido2) VALUES 
('10000001', 'Juan', 'Carlos', 'Pérez', 'Gómez'),
('10000002', 'Ana', 'María', 'Rodríguez', 'López'),
('10000003', 'Luis', 'Alberto', 'Martínez', 'Sosa'),
('10000004', 'Lucía', 'Beatriz', 'Fernández', 'Díaz'),
('10000005', 'Pedro', 'Manuel', 'Suárez', 'Molina'),
('10000006', 'Elena', 'Soledad', 'Mendoza', 'Paz'),
('10000007', 'Carlos', 'Eduardo', 'Navarro', 'Ríos'),
('10000008', 'Marcos', 'Antonio', 'López', 'Castro'),
('10000009', 'Florencia', 'Cecilia', 'Ortega', 'Salas'),
('10000010', 'Diego', 'Hernán', 'García', 'Reyes');

-- Visitante
INSERT INTO visitante (ci_visitante) VALUES 
('10000001'),
('10000003'),
('10000005'),
('10000006'),
('10000009'),
('10000010');

-- Responsable
INSERT INTO responsable (ci_responsable) VALUES 
('10000002'),
('10000004'),
('10000007'),
('10000008');

-- Tarjeta
INSERT INTO tarjeta (nro_tarjeta, ci_responsable, tipo, cvv, vencimiento) VALUES 
(1111, '10000002', 'crédito', '123', '2030-12-31'),
(2222, '10000004', 'débito', '456', '2026-06-30'),
(3333, '10000007', 'crédito', '789', '2027-11-30'),
(4444, '10000008', 'débito', '321', '2028-09-30');

-- Pase
INSERT INTO pase (codigo, ci_visitante, nro_tarjeta, estacionamiento, id_parque, precio, fecha, url_pase) VALUES 
(1, '10000001', 1111, true, 1, 120, CURRENT_DATE, 'https://ejemplo.com/pase1.png'),
(2, '10000003', 2222, false, 2, 100, CURRENT_DATE, 'https://ejemplo.com/pase2.png'),
(3, '10000005', 1111, true, 3, 130, CURRENT_DATE, 'https://ejemplo.com/pase3.png'),
(4, '10000006', 3333, false, 1, 110, CURRENT_DATE, 'https://ejemplo.com/pase4.png'),
(5, '10000009', 4444, true, 2, 115, CURRENT_DATE, 'https://ejemplo.com/pase5.png'),
(6, '10000010', 3333, false, 3, 105, CURRENT_DATE, 'https://ejemplo.com/pase6.png'),
(7, '10000001', 1111, true, 2, 125, CURRENT_DATE, 'https://ejemplo.com/pase7.png'),
(8, '10000003', 2222, false, 3, 95, CURRENT_DATE, 'https://ejemplo.com/pase8.png'),
(9, '10000005', 1111, true, 1, 140, CURRENT_DATE, 'https://ejemplo.com/pase9.png'),
(10, '10000006', 3333, false, 2, 110, CURRENT_DATE, 'https://ejemplo.com/pase10.png');


INSERT INTO registro (id_registro, entrada_salida, hora, codigo) VALUES 
(1, true, '10:00:00', 1),
(2, false, '12:00:00', 1),
(3, true, '11:30:00', 2),
(4, false, '13:00:00', 2),
(5, true, '09:45:00', 3),
(6, false, '11:15:00', 3),
(7, true, '10:15:00', 4),
(8, false, '12:30:00', 4),
(9, true, '09:00:00', 5),
(10, false, '10:45:00', 5);


INSERT INTO factura (id_factura, descripcion, fecha, codigo) VALUES 
(1, 'pase creado', CURRENT_DATE,1),
(2, 'pase creado', CURRENT_DATE,2),
(3, 'pase creado', CURRENT_DATE,3),
(4, 'pase creado', CURRENT_DATE,4),
(5, 'pase creado', CURRENT_DATE,5),
(6, 'pase creado', CURRENT_DATE,6),
(7, 'pase creado', CURRENT_DATE,7),
(8, 'pase creado', CURRENT_DATE,8),
(9, 'pase creado', CURRENT_DATE,9),
(10, 'pase creado', CURRENT_DATE,10);

-- Precio
INSERT INTO precio (id_precio, id_parque, fecha_ini, fecha_fin, precio) VALUES 
(1, 1, '2025-04-01', '2025-04-30', 100),
(2, 2, '2025-04-01', '2025-04-30', 120),
(3, 3, '2025-04-01', '2025-04-30', 90),
(4, 1, '2025-05-01', '2025-05-31', 110),
(5, 2, '2025-05-01', '2025-05-31', 130),
(6, 3, '2025-05-01', '2025-05-31', 95),
(7, 1, '2025-06-01', '2025-06-30', 105),
(8, 2, '2025-06-01', '2025-06-30', 125),
(9, 3, '2025-06-01', '2025-06-30', 100),
(10, 1, '2025-07-01', '2025-07-31', 115);

-- Actividad
INSERT INTO actividad (id_actividad, id_parque, nombre, tipo) VALUES 
(1, 1, 'Tobogán', 'entretenimiento'),
(2, 1, 'Laberinto', 'juegos'),
(3, 2, 'Show de Magia', 'entretenimiento'),
(4, 2, 'Cine 3D', 'juegos'),
(5, 3, 'Rueda', 'juegos'),
(6, 3, 'Teatro', 'entretenimiento'),
(7, 1, 'Piscina', 'entretenimiento'),
(8, 2, 'Escalada', 'juegos'),
(9, 3, 'Paintball', 'juegos'),
(10, 2, 'Tirolesa', 'entretenimiento');

-- Pase_actividad
INSERT INTO pase_actividad (codigo, id_actividad, hora) VALUES 
(1, 1, '12:45:00'),
(1, 2, '13:30:00'),
(2, 3, '15:00:00'),
(2, 4, '12:50:00'),
(3, 5, '17:00:00'),
(3, 6, '12:00:00'),
(4, 7, '15:45:00'),
(5, 8, '10:20:00'),
(6, 9, '18:10:00'),
(6, 10, '14:30:00');

-- Fotografía
INSERT INTO fotografia (id_foto, fecha, hora, url_foto, id_actividad) VALUES 
(1, CURRENT_DATE, '10:00:00', 'https://ejemplo.com/foto1.jpg', 1),
(2, CURRENT_DATE, '11:00:00', 'https://ejemplo.com/foto2.jpg', 3),
(3, CURRENT_DATE, '12:00:00', 'https://ejemplo.com/foto3.jpg', 5),
(4, CURRENT_DATE, '13:00:00', 'https://ejemplo.com/foto4.jpg', 4),
(5, CURRENT_DATE, '14:00:00', 'https://ejemplo.com/foto5.jpg', 6),
(6, CURRENT_DATE, '15:00:00', 'https://ejemplo.com/foto6.jpg', 2),
(7, CURRENT_DATE, '16:00:00', 'https://ejemplo.com/foto7.jpg', 7),
(8, CURRENT_DATE, '17:00:00', 'https://ejemplo.com/foto8.jpg', 8),
(9, CURRENT_DATE, '18:00:00', 'https://ejemplo.com/foto9.jpg', 9),
(10, CURRENT_DATE, '19:00:00', 'https://ejemplo.com/foto10.jpg', 10);

INSERT INTO dolar (valor, fecha, hora) VALUES 
(39.15, '2025-04-20', '09:00:00'),
(39.42, '2025-04-20', '12:00:00'),
(39.30, '2025-04-20', '15:00:00'),
(39.70, '2025-04-21', '09:00:00'),
(39.85, '2025-04-21', '12:00:00'),
(39.55, '2025-04-21', '15:00:00'),
(39.90, '2025-04-22', '09:00:00'),
(40.10, '2025-04-22', '12:00:00'),
(40.25, '2025-04-22', '15:00:00'),
(40.60, '2025-04-23', '09:00:00'),
(40.20, '2025-04-23', '12:00:00'),
(39.95, '2025-04-23', '15:00:00'),
(39.10, '2025-04-24', '09:00:00'),
(38.95, '2025-04-24', '12:00:00'),
(39.05, '2025-04-24', '15:00:00');


CREATE MATERIALIZED VIEW vista_entradas_2024 AS
SELECT pa.id_parque, SUM(ps.precio / 40) AS ingreso_total_usd, COUNT(ps.codigo) AS cantidad_entradas
FROM pase ps
JOIN parque pa ON ps.id_parque = pa.id_parque
WHERE ps.fecha BETWEEN '2024-01-01' AND '2024-12-31'
GROUP BY pa.id_parque;
REFRESH MATERIALIZED VIEW vista_entradas_2024;



------------------------------------
------------------------------------
-------------Funciones--------------
------------------------------------
------------------------------------



CREATE OR REPLACE FUNCTION check_venta(p_id_parque INTEGER, fecha_reserva DATE, cantEntradas INTEGER, cantiParking INTEGER) 
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
    EXISTS(SELECT 1 FROM parque p WHERE p_id_parque = p.id_parque);

    IF NOT existe_parque THEN
        RAISE EXCEPTION 'No existe el parque';
    END IF;
    --Capacidad parque
    SELECT capacidad INTO capacidadParque 
    FROM parque p 
    WHERE p.id_parque = p_id_parque;

    --Capacidad ocupada del parque
    SELECT COUNT(*) INTO capacidadOcupada
    FROM pase p 
    WHERE p.id_parque = p_id_parque AND p.fecha = fecha_reserva; 

    if(capacidadOcupada + cantEntradas <= capacidadParque) THEN 
        RETURN TRUE;
    END IF;
    
	RAISE EXCEPTION 'No hay espacio disponible';

END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION validarEntrada(fecha_input DATE, ci_input TEXT) 
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
    existeV BOOLEAN;
	existeC BOOLEAN;
BEGIN 
	
    SELECT EXISTS (
        SELECT 1
        FROM Visitante v
        WHERE NEW.ci = v.ci
    ) INTO existeV;

    IF existeV THEN
        RETURN NULL;
    ELSE
        RETURN NEW;
    END IF;

END; $$
LANGUAGE plpgsql;

CREATE TRIGGER validarVisitante
BEFORE INSERT ON Visitante FOR EACH ROW EXECUTE PROCEDURE validandoVisitante();


--Trigger insertar en Visitante
CREATE OR REPLACE FUNCTION insertarcliente(
    ci TEXT,
    nom1 TEXT,
    nom2 TEXT,
    ape1 TEXT,
    ape2 TEXT,
    esResp BOOLEAN
) RETURNS BOOLEAN AS $$
DECLARE
    existe_cliente BOOLEAN := FALSE;
    existe_visitante BOOLEAN := FALSE;
    existe_responsable BOOLEAN := FALSE;
BEGIN
    SELECT EXISTS (
        SELECT 1 FROM cliente WHERE ci = ci
    ) INTO existe_cliente;

    IF NOT existe_cliente THEN
        INSERT INTO cliente (ci, nombre1, nombre2, apellido1, apellido2)
        VALUES (ci, nom1, nom2, ape1, ape2);
    END IF;

    IF NOT esResp THEN 
        SELECT EXISTS (
            SELECT 1 FROM visitante WHERE ci_visitante = ci
        ) INTO existe_visitante;

        IF NOT existe_visitante THEN
            INSERT INTO visitante (ci_visitante, nombre1, nombre2, apellido1, apellido2)
            VALUES (ci, nom1, nom2, ape1, ape2);
        END IF;
    END IF;

    IF esResp THEN 
        SELECT EXISTS (
            SELECT 1 FROM responsable WHERE ci_responsable = ci
        ) INTO existe_responsable;

        IF NOT existe_responsable THEN
            INSERT INTO responsable (ci_responsable)
            VALUES (ci);
        END IF;
    END IF;

    RETURN TRUE;
END;
$$ LANGUAGE plpgsql;

CREATE OR REPLACE FUNCTION InsertandoFactura() 
RETURNS TRIGGER AS $$
BEGIN 
    INSERT INTO Factura (fecha, codigo)
        VALUES(NOW(), NEW.codigo);
END; $$
LANGUAGE plpgsql;

CREATE TRIGGER insertarFactura
BEFORE INSERT ON PASE FOR EACH ROW EXECUTE PROCEDURE InsertandoFactura();