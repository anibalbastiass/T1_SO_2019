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

// Booleanos
#define FALSE 0
#define TRUE 1

void clearScreen(void);
void showLaunchError(void);

char *getNumberPath(int);
char *concatenateString(char *, char *);
void createFolders(void);

void createFileInCardPath(void);
void moveCardToPathFolder(char *argv);

char *splitAndGetFirst(char *, char *);
void mapDirectories(char *);

void error(const char *s);

// Navigation
void initNavigation(char *);
void readFilesDirectory(char *);
void printWelcomeMessage(void);
void printPrompt(void);

int readCommand(char *, char *);

void listDir(char *);
int endsWith(const char *, const char *);
char *concatenateStringNav(char *, char *);
void readFile(char *);

int convertStringToNumber(char *);