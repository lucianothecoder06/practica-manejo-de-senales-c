#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#define CARRERAS_LIST {"ICC", "ITT", "ISS", "IC", "IME", "IE", "DER", "MED", "PSI"}
#define NOMBRES_LIST {"Oscar", "Ana", "Luis", "Maria", "Juan", "Pedro", "Lucia", "Marta", "Carmen", "Jose", "Sofia", "Diego", "Elena", "Alvaro", "Isabel", "Javier", "Laura", "Miguel", "Sara", "Rafael"}

volatile sig_atomic_t stop = 0;


void handler(int sig)
{
    printf("Recibi la senal %d\n", sig);
    stop = 1;
};

typedef struct Student
{
    int id;
    char nombre[100];
    char carrera[5];
} Student;

int genRandomId()
{
    return rand() % 1000;
}
int genRandomCareer()
{
    return rand() % 5;
}
int genRandomName()
{
    return rand() % 20;
}

Student genStudent()
{
    char *carreras[] = CARRERAS_LIST;
    char *nombres[] = NOMBRES_LIST;
    Student s = {genRandomId(), "", ""};
    strcpy(s.nombre, nombres[genRandomName()]);
    strcpy(s.carrera, carreras[genRandomCareer()]);
    return s;
}

void saveStudent(Student s, FILE *f)
{
    if (f == NULL)
    {
        printf("Error al abrir el archivo\n");
        return;
    }
    fprintf(f, "%d,%s,%s\n", s.id, s.nombre, s.carrera);
}
int main(int argc, char *argv[])
{
    srand(time(0));

    signal(SIGINT, handler);
    signal(SIGTERM, handler);
    FILE *f = fopen("data.log", "a");
    while (!stop)
    {
        Student s = genStudent();
        saveStudent(s, f);
        printf("ID: %d, Nombre: %s, Carrera: %s\n", s.id, s.nombre, s.carrera);
        sleep(1);
    }
    fclose(f);

    return 0;
}
