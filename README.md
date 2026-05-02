# Sistema Universidad

## Tecnologías
- C++
- MySQL
- MySQL Connector (mysql.h)

---

## Explicación del funcionamiento

### Conexión a la base de datos  
El programa se conecta a una base de datos llamada universidad usando la librería mysql.h. La conexión se hace al inicio con la función conectar(), conectándose al servidor local por el puerto 3306. Si ocurre un error, el programa muestra un mensaje y se cierra. Al salir (opción 6), la conexión se cierra correctamente.

---

### Menú principal  
Al iniciar el programa se muestra un menú con las opciones: Alumnos, Cursos, Secciones, Alumnos-Cursos, Alumnos-Sección y Salir. El menú se mantiene en un ciclo hasta que el usuario decide salir.

---

### Módulo Alumnos  
Permite listar, agregar, modificar y eliminar alumnos. El listado usa JOIN para mostrar también los cursos y la sección. Si no tiene datos, muestra “Sin cursos” o “Sin sección”. Al eliminar un alumno, primero se eliminan sus relaciones.

---

### Módulo Cursos  
Permite crear, ver, editar y eliminar cursos (nombre y código). Antes de eliminar un curso, se eliminan sus relaciones con alumnos.

---

### Módulo Secciones  
Permite listar, agregar, modificar y eliminar secciones (nombre y jornada). Al eliminar una sección, también se eliminan sus asignaciones.

---

### Alumnos-Cursos  
Permite asignar cursos a alumnos, listar asignaciones y eliminarlas. No permite duplicados gracias a una restricción UNIQUE.

---

### Alumnos-Sección  
Permite asignar una sección a cada alumno, así como modificarla o eliminarla. Cada alumno puede tener como máximo una sección activa.

---

## Evidencia

### Menú principal
<img width="980" height="516" alt="image" src="https://github.com/user-attachments/assets/66745428-249e-4a88-a7e7-8788258cfb91" />


### Operaciones del sistema
![img1](https://github.com/user-attachments/assets/ae8f7362-7ff6-41ba-bd54-d1efd05540c5)

![img2](https://github.com/user-attachments/assets/7e4a5a77-bdbf-444d-a0dc-0fc5a20de9f1)

![img3](https://github.com/user-attachments/assets/4cb2838a-22ae-40a4-8399-59314be29261)
