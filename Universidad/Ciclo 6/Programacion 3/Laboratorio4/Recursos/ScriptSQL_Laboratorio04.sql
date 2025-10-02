DROP TABLE IF EXISTS videojuego;
CREATE TABLE videojuego(
	id_videojuego INT PRIMARY KEY AUTO_INCREMENT,
    titulo VARCHAR(150),
    fecha_lanzamiento DATE,
    clasificacion ENUM('Everyone','Teen','Mature','Adults'),
    precio DECIMAL(10,2),
    es_multijugador TINYINT,
    numero_max_jugadores INT
)ENGINE=InnoDB;
INSERT INTO videojuego (titulo, fecha_lanzamiento, clasificacion, precio, es_multijugador, numero_max_jugadores) VALUES ('Hollow Knight', '2017-02-24', 'Teen', 14.99, FALSE, 1);
INSERT INTO videojuego (titulo, fecha_lanzamiento, clasificacion, precio, es_multijugador, numero_max_jugadores) VALUES ('Red Dead Redemption 2', '2018-10-26', 'Mature', 59.99, TRUE, 32);
INSERT INTO videojuego (titulo, fecha_lanzamiento, clasificacion, precio, es_multijugador, numero_max_jugadores) VALUES ('Cuphead', '2017-09-29', 'Everyone', 19.99, TRUE, 2);