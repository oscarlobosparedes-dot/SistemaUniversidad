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
<img width="992" height="520" alt="image" src="https://github.com/user-attachments/assets/d263b3a0-fe25-4c43-82ba-a8f9b058b113" />

<img width="992" height="506" alt="image" src="https://github.com/user-attachments/assets/1e5c1328-2ec4-4cfc-93c3-d543030553a2" />

<img width="990" height="518" alt="image" src="https://github.com/user-attachments/assets/178c929d-ca5d-4d4e-af6a-aedddca06d91" />

<img width="972" height="518" alt="image" src="https://github.com/user-attachments/assets/2d79244c-5e01-40d1-ae0f-0de96acc87c2" />


