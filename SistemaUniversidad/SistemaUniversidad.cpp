#include <iostream>
#include <string>
#include <mysql.h>
using namespace std;

// CONEXION GLOBAL
MYSQL* conn;

void conectar() {
    conn = mysql_init(NULL);
    if (!conn) {
        cout << "Error al inicializar MySQL\n";
        exit(1);
    }
    if (!mysql_real_connect(conn, "localhost", "root", "Caudales1.", "universidad", 3306, NULL, 0)) {
        cout << "Error de conexion: " << mysql_error(conn) << "\n";
        exit(1);
    }
    cout << "Conexion exitosa a la base de datos.\n";
}

void ejecutarQuery(const string& sql) {
    if (mysql_query(conn, sql.c_str())) {
        cout << "Error SQL: " << mysql_error(conn) << "\n";
    }
}

// MODULO ALUMNOS
void listarAlumnos() {
    string sql =
        "SELECT a.id, a.nombres, a.apellidos, a.carnet, "
        "IFNULL(GROUP_CONCAT(c.nombre SEPARATOR ', '), 'Sin cursos') AS cursos, "
        "IFNULL(s.nombre, 'Sin seccion') AS seccion "
        "FROM alumnos a "
        "LEFT JOIN alumnos_cursos ac ON a.id = ac.alumno_id "
        "LEFT JOIN cursos c ON ac.curso_id = c.id "
        "LEFT JOIN alumnos_seccion ase ON a.id = ase.alumno_id "
        "LEFT JOIN secciones s ON ase.seccion_id = s.id "
        "GROUP BY a.id, a.nombres, a.apellidos, a.carnet, s.nombre";

    if (mysql_query(conn, sql.c_str())) {
        cout << "Error: " << mysql_error(conn) << "\n";
        return;
    }
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;
    cout << "\n--- Lista de Alumnos ---\n";
    cout << "ID | Nombres | Apellidos | Carnet | Cursos | Seccion\n";
    cout << string(70, '-') << "\n";
    while ((row = mysql_fetch_row(res))) {
        cout << row[0] << " | " << row[1] << " | " << row[2]
            << " | " << row[3] << " | " << row[4] << " | " << row[5] << "\n";
    }
    mysql_free_result(res);
}

void insertarAlumno() {
    string nombres, apellidos, carnet;
    cout << "Nombres: ";    cin.ignore(); getline(cin, nombres);
    cout << "Apellidos: ";  getline(cin, apellidos);
    cout << "Carnet: ";     getline(cin, carnet);
    string sql = "INSERT INTO alumnos (nombres, apellidos, carnet) VALUES ('"
        + nombres + "','" + apellidos + "','" + carnet + "')";
    ejecutarQuery(sql);
    cout << "Alumno grabado correctamente.\n";
}

void actualizarAlumno() {
    int id;
    string nombres, apellidos, carnet;
    cout << "ID del alumno a modificar: "; cin >> id;
    cout << "Nuevos nombres: ";   cin.ignore(); getline(cin, nombres);
    cout << "Nuevos apellidos: "; getline(cin, apellidos);
    cout << "Nuevo carnet: ";     getline(cin, carnet);
    string sql = "UPDATE alumnos SET nombres='" + nombres +
        "', apellidos='" + apellidos +
        "', carnet='" + carnet +
        "' WHERE id=" + to_string(id);
    ejecutarQuery(sql);
    cout << "Alumno modificado correctamente.\n";
}

void eliminarAlumno() {
    int id;
    cout << "ID del alumno a eliminar: "; cin >> id;
    ejecutarQuery("DELETE FROM alumnos_cursos WHERE alumno_id=" + to_string(id));
    ejecutarQuery("DELETE FROM alumnos_seccion WHERE alumno_id=" + to_string(id));
    ejecutarQuery("DELETE FROM alumnos WHERE id=" + to_string(id));
    cout << "Alumno eliminado correctamente.\n";
}

void menuAlumnos() {
    int op;
    do {
        cout << "\n===== MODULO ALUMNOS =====\n"
            << "1. Listar\n2. Grabar\n3. Modificar\n4. Eliminar\n5. Regresar\n"
            << "Opcion: ";
        cin >> op;
        switch (op) {
        case 1: listarAlumnos();   break;
        case 2: insertarAlumno();  break;
        case 3: actualizarAlumno(); break;
        case 4: eliminarAlumno();  break;
        case 5: break;
        default: cout << "Opcion invalida.\n";
        }
    } while (op != 5);
}

// MODULO CURSOS
void listarCursos() {
    if (mysql_query(conn, "SELECT id, nombre, codigo FROM cursos")) {
        cout << "Error: " << mysql_error(conn) << "\n"; return;
    }
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;
    cout << "\n--- Lista de Cursos ---\n";
    cout << "ID | Nombre | Codigo\n" << string(40, '-') << "\n";
    while ((row = mysql_fetch_row(res)))
        cout << row[0] << " | " << row[1] << " | " << row[2] << "\n";
    mysql_free_result(res);
}

void insertarCurso() {
    string nombre, codigo;
    cout << "Nombre del curso: "; cin.ignore(); getline(cin, nombre);
    cout << "Codigo: ";           getline(cin, codigo);
    ejecutarQuery("INSERT INTO cursos (nombre, codigo) VALUES ('" + nombre + "','" + codigo + "')");
    cout << "Curso grabado correctamente.\n";
}

void actualizarCurso() {
    int id; string nombre, codigo;
    cout << "ID del curso a modificar: "; cin >> id;
    cout << "Nuevo nombre: "; cin.ignore(); getline(cin, nombre);
    cout << "Nuevo codigo: "; getline(cin, codigo);
    ejecutarQuery("UPDATE cursos SET nombre='" + nombre + "', codigo='" + codigo + "' WHERE id=" + to_string(id));
    cout << "Curso modificado correctamente.\n";
}

void eliminarCurso() {
    int id;
    cout << "ID del curso a eliminar: "; cin >> id;
    ejecutarQuery("DELETE FROM alumnos_cursos WHERE curso_id=" + to_string(id));
    ejecutarQuery("DELETE FROM cursos WHERE id=" + to_string(id));
    cout << "Curso eliminado correctamente.\n";
}

void menuCursos() {
    int op;
    do {
        cout << "\n===== MODULO CURSOS =====\n"
            << "1. Listar\n2. Grabar\n3. Modificar\n4. Eliminar\n5. Regresar\n"
            << "Opcion: ";
        cin >> op;
        switch (op) {
        case 1: listarCursos();    break;
        case 2: insertarCurso();   break;
        case 3: actualizarCurso(); break;
        case 4: eliminarCurso();   break;
        case 5: break;
        default: cout << "Opcion invalida.\n";
        }
    } while (op != 5);
}

// MODULO SECCIONES
void listarSecciones() {
    if (mysql_query(conn, "SELECT id, nombre, jornada FROM secciones")) {
        cout << "Error: " << mysql_error(conn) << "\n"; return;
    }
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;
    cout << "\n--- Lista de Secciones ---\n";
    cout << "ID | Nombre | Jornada\n" << string(40, '-') << "\n";
    while ((row = mysql_fetch_row(res)))
        cout << row[0] << " | " << row[1] << " | " << row[2] << "\n";
    mysql_free_result(res);
}

void insertarSeccion() {
    string nombre, jornada;
    cout << "Nombre de la seccion: "; cin.ignore(); getline(cin, nombre);
    cout << "Jornada: ";              getline(cin, jornada);
    ejecutarQuery("INSERT INTO secciones (nombre, jornada) VALUES ('" + nombre + "','" + jornada + "')");
    cout << "Seccion grabada correctamente.\n";
}

void actualizarSeccion() {
    int id; string nombre, jornada;
    cout << "ID de la seccion a modificar: "; cin >> id;
    cout << "Nuevo nombre: ";  cin.ignore(); getline(cin, nombre);
    cout << "Nueva jornada: "; getline(cin, jornada);
    ejecutarQuery("UPDATE secciones SET nombre='" + nombre + "', jornada='" + jornada + "' WHERE id=" + to_string(id));
    cout << "Seccion modificada correctamente.\n";
}

void eliminarSeccion() {
    int id;
    cout << "ID de la seccion a eliminar: "; cin >> id;
    ejecutarQuery("DELETE FROM alumnos_seccion WHERE seccion_id=" + to_string(id));
    ejecutarQuery("DELETE FROM secciones WHERE id=" + to_string(id));
    cout << "Seccion eliminada correctamente.\n";
}

void menuSecciones() {
    int op;
    do {
        cout << "\n===== MODULO SECCIONES =====\n"
            << "1. Listar\n2. Grabar\n3. Modificar\n4. Eliminar\n5. Regresar\n"
            << "Opcion: ";
        cin >> op;
        switch (op) {
        case 1: listarSecciones();    break;
        case 2: insertarSeccion();    break;
        case 3: actualizarSeccion();  break;
        case 4: eliminarSeccion();    break;
        case 5: break;
        default: cout << "Opcion invalida.\n";
        }
    } while (op != 5);
}

// MODULO ALUMNOS-CURSOS
void listarAlumnosCursos() {
    string sql = "SELECT ac.id, a.nombres, a.apellidos, c.nombre "
        "FROM alumnos_cursos ac "
        "JOIN alumnos a ON ac.alumno_id = a.id "
        "JOIN cursos c ON ac.curso_id = c.id";
    if (mysql_query(conn, sql.c_str())) {
        cout << "Error: " << mysql_error(conn) << "\n"; return;
    }
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;
    cout << "\n--- Asignaciones Alumno-Curso ---\n";
    cout << "ID | Alumno | Curso\n" << string(50, '-') << "\n";
    while ((row = mysql_fetch_row(res)))
        cout << row[0] << " | " << row[1] << " " << row[2] << " | " << row[3] << "\n";
    mysql_free_result(res);
}

void asignarCurso() {
    int alumno_id, curso_id;
    cout << "ID del alumno: "; cin >> alumno_id;
    cout << "ID del curso: ";  cin >> curso_id;
    ejecutarQuery("INSERT INTO alumnos_cursos (alumno_id, curso_id) VALUES (" +
        to_string(alumno_id) + "," + to_string(curso_id) + ")");
    cout << "Curso asignado correctamente.\n";
}

void eliminarAlumnoCurso() {
    int id;
    cout << "ID de la asignacion a eliminar: "; cin >> id;
    ejecutarQuery("DELETE FROM alumnos_cursos WHERE id=" + to_string(id));
    cout << "Asignacion eliminada correctamente.\n";
}

void menuAlumnosCursos() {
    int op;
    do {
        cout << "\n===== MODULO ALUMNOS-CURSOS =====\n"
            << "1. Listar\n2. Asignar curso\n3. Eliminar asignacion\n4. Regresar\n"
            << "Opcion: ";
        cin >> op;
        switch (op) {
        case 1: listarAlumnosCursos(); break;
        case 2: asignarCurso();        break;
        case 3: eliminarAlumnoCurso(); break;
        case 4: break;
        default: cout << "Opcion invalida.\n";
        }
    } while (op != 4);
}

// MODULO ALUMNOS-SECCION
void listarAlumnosSeccion() {
    string sql = "SELECT ase.id, a.nombres, a.apellidos, s.nombre, s.jornada "
        "FROM alumnos_seccion ase "
        "JOIN alumnos a ON ase.alumno_id = a.id "
        "JOIN secciones s ON ase.seccion_id = s.id";
    if (mysql_query(conn, sql.c_str())) {
        cout << "Error: " << mysql_error(conn) << "\n"; return;
    }
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;
    cout << "\n--- Asignaciones Alumno-Seccion ---\n";
    cout << "ID | Alumno | Seccion | Jornada\n" << string(50, '-') << "\n";
    while ((row = mysql_fetch_row(res)))
        cout << row[0] << " | " << row[1] << " " << row[2]
        << " | " << row[3] << " | " << row[4] << "\n";
    mysql_free_result(res);
}

void asignarSeccion() {
    int alumno_id, seccion_id;
    cout << "ID del alumno: ";   cin >> alumno_id;
    cout << "ID de la seccion: "; cin >> seccion_id;
    ejecutarQuery("INSERT INTO alumnos_seccion (alumno_id, seccion_id) VALUES (" +
        to_string(alumno_id) + "," + to_string(seccion_id) + ")");
    cout << "Seccion asignada correctamente.\n";
}

void modificarSeccionAlumno() {
    int alumno_id, seccion_id;
    cout << "ID del alumno a modificar seccion: "; cin >> alumno_id;
    cout << "Nueva seccion ID: ";                   cin >> seccion_id;
    ejecutarQuery("UPDATE alumnos_seccion SET seccion_id=" + to_string(seccion_id) +
        " WHERE alumno_id=" + to_string(alumno_id));
    cout << "Seccion modificada correctamente.\n";
}

void eliminarAlumnoSeccion() {
    int id;
    cout << "ID de la asignacion a eliminar: "; cin >> id;
    ejecutarQuery("DELETE FROM alumnos_seccion WHERE id=" + to_string(id));
    cout << "Asignacion eliminada correctamente.\n";
}

void menuAlumnosSeccion() {
    int op;
    do {
        cout << "\n===== MODULO ALUMNOS-SECCION =====\n"
            << "1. Listar\n2. Asignar seccion\n3. Modificar seccion\n4. Eliminar asignacion\n5. Regresar\n"
            << "Opcion: ";
        cin >> op;
        switch (op) {
        case 1: listarAlumnosSeccion();     break;
        case 2: asignarSeccion();           break;
        case 3: modificarSeccionAlumno();   break;
        case 4: eliminarAlumnoSeccion();    break;
        case 5: break;
        default: cout << "Opcion invalida.\n";
        }
    } while (op != 5);
}

// MENU PRINCIPAL
int main() {
    conectar();
    int op;
    do {
        cout << "\n===== SISTEMA UNIVERSIDAD =====\n"
            << "1. Alumnos\n"
            << "2. Cursos\n"
            << "3. Secciones\n"
            << "4. Alumnos - Cursos\n"
            << "5. Alumnos - Seccion\n"
            << "6. Salir\n"
            << "Opcion: ";
        cin >> op;
        switch (op) {
        case 1: menuAlumnos();        break;
        case 2: menuCursos();         break;
        case 3: menuSecciones();      break;
        case 4: menuAlumnosCursos();  break;
        case 5: menuAlumnosSeccion(); break;
        case 6: cout << "Cerrando conexion...\n"; break;
        default: cout << "Opcion invalida.\n";
        }
    } while (op != 6);

    mysql_close(conn);
    cout << "Hasta luego.\n";
    system("pause");
    return 0;
}