--PREGUNTA 4

--INCISO A

--Ranking de los top10 vendedores, ordenados de mayor a menor, que
--tuvieron mayor cobertura en el mes de abril. La salida debe verse así:

--PARA USAR EL ROWNUM
SELECT v.id_vendedor AS CODIGO, v.nombre AS NOMBRE_VENDEDOR, COUNT(*) AS CLIENTES_DISTINTOS 
FROM EX1_VENDEDOR v, EX1_ZONA z , EX1_CLIENTE c
WHERE v.id_vendedor  = z.id_vendedor and z.id_zona = c.id_zona and c.id_cliente in ( --Select anidada
                                                                            SELECT id_cliente FROM EX1_FACTURA 
                                                                            WHERE TO_NUMBER(TO_CHAR(fecha, 'MM')) = 4) --Clientes que tengan facturas en el mes de abril
GROUP BY v.id_vendedor, v.nombre
ORDER BY COUNT(*) DESC
--FETCH FIRST 10 ROWS ONLY

--ROWNUM
SELECT * 
FROM(
    SELECT v.id_vendedor AS CODIGO, v.nombre AS NOMBRE_VENDEDOR, COUNT(*) AS CLIENTES_DISTINTOS 
    FROM EX1_VENDEDOR v, EX1_ZONA z , EX1_CLIENTE c
    WHERE v.id_vendedor  = z.id_vendedor and z.id_zona = c.id_zona and c.id_cliente in ( --Select anidada
                                                                            SELECT id_cliente FROM EX1_FACTURA 
                                                                            WHERE TO_NUMBER(TO_CHAR(fecha, 'MM')) = 4)--Clientes que tengan facturas en el mes de abril
    GROUP BY v.id_vendedor, v.nombre
    ORDER BY COUNT(*) DESC
    )
WHERE ROWNUM <= 10;

--INCISO B

--Ranking de los vendedores, ordenados de mayor a menor, de acuerdo
--al monto total vendido en el mes de abril, pero solo aquellos que hicieron ventas
--acumuladas de 4500 soles a más. La salida debe visualizarse así:

SELECT v.id_vendedor AS CODIGO_vendedor, v.nombre AS NOMBRE_VENDEDOR, TO_CHAR(SUM(f.total), 'L9G999', 'NLS_CURRENCY=''s/.''') AS TOTAL_VENDIDO --Si valía que aparezca punto en vez de coma
-- SELECT v.id_vendedor AS CODIGO_vendedor, v.nombre AS NOMBRE_VENDEDOR, 's/'||'.'||TO_CHAR(SUM(f.total),'9,999') AS TOTAL_VENDIDO --opcion 2 
FROM EX1_VENDEDOR v, EX1_ZONA z , EX1_CLIENTE c, EX1_FACTURA f                                                                                 
WHERE v.id_vendedor  = z.id_vendedor and z.id_zona = c.id_zona and c.id_cliente = f.id_cliente
AND TO_NUMBER(TO_CHAR(f.fecha, 'MM')) = 4 --Mes de abril
GROUP BY v.id_vendedor, v.nombre
HAVING SUM(f.total) >= 4500 -- Ventas acumuladas Mayor o igual a 4500
ORDER BY SUM(f.total) DESC







