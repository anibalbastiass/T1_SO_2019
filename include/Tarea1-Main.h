/*
 *  Tarea 1 - Sistemas Operativos
 *  1 Semestre, 2019
 * 
 *  Autor:      Anibal Bastias Soto
 *  ROL:        2604215-1
 *  Carrera:    Ingenieria de Ejecucion en Informatica
 * 
 *  Archivo:    Tarea1-Main.h 
 *  
 *  Este archivo define todas las funciones de Tarea1-Main.c y Tarea1-Func.c como
 *  una especie de interfaz
 */

void clearScreen(void);
void showLaunchError(void);

char *getNumberPath(int);
char *concatenateString(char*, char*);
void createFolders(void);

void createFileInCardPath(void);
void moveCardToPathFolder(char *argv);

char *splitAndGetFirst(char *, char *);
void mapDirectory();

/* Función para devolver un error en caso de que ocurra */
void error(const char *s);

/* Función que hace algo con un archivo */
void procesoArchivo(char *archivo);

void error(const char *);
void processFile(char *);

// Navigation
void initNavigation(void);