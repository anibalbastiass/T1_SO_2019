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

#ifndef MINISHELL_H
#define MINISHELL_H

// Booleanos
#define FALSE 0
#define TRUE 1

// Maximo de ingreso de linea
#define LINE_LEN 80
#define MAX_ARGS 64
#define MAX_ARG_LEN 64
#define MAX_PATHS 64
#define MAX_PATH_LEN 96

// ASCII de espacio en blanco
#define WHITESPACE " .,\t&"

// Estandar de entrada y salida
#define STD_INPUT 0
#define STD_OUTPUT 1

// Valor nulo
#ifndef NULL
#define NULL 0
#endif

// Variables estaticas del programa
// para que esten vivas durante toda
// la duracion del programa
static char inCommand = '\0';
static int bufferChars = 0;
static char *pathv[MAX_PATHS];
static char tCommandLine[LINE_LEN];

// Estructura del Comando
struct comando_t
{
    char *name;
    int argc;
    char *argv[MAX_ARGS];
};

// Declaracion de Funciones
void initNavigation(void);
void printPrompt();
void printWelcomeMessage();
int leerComando(char *commandLine, char *commandInput);
int parsearComando(char *commandLine, struct comando_t *command);
char *seekPath(char **, char **);
int parsearRuta(char **);

#endif
