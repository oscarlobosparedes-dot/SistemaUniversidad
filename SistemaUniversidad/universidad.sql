DROP DATABASE IF EXISTS universidad;
CREATE DATABASE universidad;
USE universidad;

CREATE TABLE alumnos (
    id INT PRIMARY KEY AUTO_INCREMENT,
    nombres VARCHAR(50) NOT NULL,
    apellidos VARCHAR(50) NOT NULL,
    carnet VARCHAR(20) UNIQUE NOT NULL
);

CREATE TABLE cursos (
    id INT PRIMARY KEY AUTO_INCREMENT,
    nombre VARCHAR(100) NOT NULL,
    codigo VARCHAR(20) UNIQUE NOT NULL
);

CREATE TABLE secciones (
    id INT PRIMARY KEY AUTO_INCREMENT,
    nombre VARCHAR(50) NOT NULL,
    jornada VARCHAR(30) NOT NULL
);

CREATE TABLE alumnos_cursos (
    id INT PRIMARY KEY AUTO_INCREMENT,
    alumno_id INT NOT NULL,
    curso_id INT NOT NULL,
    UNIQUE(alumno_id, curso_id),
    FOREIGN KEY (alumno_id) REFERENCES alumnos(id),
    FOREIGN KEY (curso_id) REFERENCES cursos(id)
);

CREATE TABLE alumnos_seccion (
    id INT PRIMARY KEY AUTO_INCREMENT,
    alumno_id INT UNIQUE NOT NULL,
    seccion_id INT NOT NULL,
    FOREIGN KEY (alumno_id) REFERENCES alumnos(id),
    FOREIGN KEY (seccion_id) REFERENCES secciones(id)
);