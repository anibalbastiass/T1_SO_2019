/*
 *  Tarea 1 - Sistemas Operativos
 *  1 Semestre, 2019
 * 
 *  Autor:      Anibal Bastias Soto
 *  ROL:        2604215-1
 *  Carrera:    Ingenieria de Ejecucion en Informatica
 * 
 *  Archivo:    Tarea1-Nav-Main.c 
 *  
 *  Este archivo realiza las funciones necesarias para ejecutar los comandos
 *  esenciales del mini shell como cambiar directorio, crear, direccionar, entre otros
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <ctype.h>
#include "include/Tarea1-Main.h"

#include <errno.h>
#include <limits.h>

#define STRING_LENGTH 1024
#define LINE_LEN 80

char inCommand = '\0';
int charBuffer = 0;
char tCommandLine[LINE_LEN];

char dest[STRING_LENGTH];
int countFiles = 1;

char *files_arr[STRING_LENGTH];
char *ptrFiles[STRING_LENGTH];

// Funcion Main del programa
void initNavigation(char *directory)
{
  printWelcomeMessage();

  listDir(directory);
  printf("\n");

  // main loop
  while (TRUE)
  {
    printPrompt();

    inCommand = getchar();
    if (inCommand == '\n')
    {
      continue;
    }
    else
    {
      // Lee comando
      readCommand(tCommandLine, &inCommand);

      if ((strcmp(tCommandLine, "exit") == 0) || (strcmp(tCommandLine, "quit") == 0))
        break;

      int option = convertStringToNumber(tCommandLine);
      readFile(ptrFiles[option]);
    }
  }

  printf("\n");
  exit(EXIT_SUCCESS);
}

// Imprime mensaje de Bienvenida
void printWelcomeMessage()
{
  printf("TAREA 1 - SO - ABS: 2604215-1\n");
  printf("=============================\n");
  printf("\nNavegador de Cartas\n");
  printf("\nEscoja el numero para ver informacion de la carta insertada:\n");
  printf("\nPara salir, digite exit o quit:\n\n");
}

// Imprime prompt
void printPrompt()
{
  printf("Navegador-Cartas > ");
}

// Funcion que lee y guarda la linea de comando que ingresa el usuario
int readCommand(char *buffer, char *commandIn)
{
  charBuffer = 0;

  while ((*commandIn != '\n') && (charBuffer < LINE_LEN))
  {
    buffer[charBuffer++] = *commandIn;
    *commandIn = getchar();
  }
  buffer[charBuffer] = '\0';

  return 0;
}

// Listar directorio recursivamente
void listDir(char *dir_name)
{
  DIR *d;
  d = opendir(dir_name);

  if (!d)
  {
    fprintf(stderr, "No es posible abrir el directorio '%s': %s\n",
            dir_name, strerror(errno));
    exit(EXIT_FAILURE);
  }
  while (1)
  {
    struct dirent *entry;
    char *d_name;

    entry = readdir(d);
    if (!entry)
    {
      // No hay mas directorios
      break;
    }

    d_name = entry->d_name;

    // Imprime el archivo que termina en .txt
    if (endsWith(d_name, ".txt") == 1)
    {
      printf("%d. %s/%s\n", countFiles, dir_name, d_name);

      // Agrega ruta al arreglo de paths para mostrar informacion de archivo
      char *path = (char *)malloc(1024 * sizeof(char));
      sprintf(path, "%s/%s", dir_name, d_name);

      ptrFiles[countFiles] = path;
      countFiles++;
    }

#if 0

#endif
    if (entry->d_type & DT_DIR)
    {
      // Verifica si el directorio no tiene padre
      if (strcmp(d_name, "..") != 0 &&
          strcmp(d_name, ".") != 0)
      {
        int path_length;
        char path[PATH_MAX];

        path_length = snprintf(path, PATH_MAX, "%s/%s", dir_name, d_name);

        if (endsWith(d_name, ".txt") == 1)
          printf("%s\n", path);

        if (path_length >= PATH_MAX)
        {
          fprintf(stderr, "El largo del directorio es muy largo.\n");
          exit(EXIT_FAILURE);
        }
        // Llamada recursiva para listar directorio
        listDir(path);
      }
    }
  }

  // Despues de recorrer todas las entradas, cierra el directorio
  if (closedir(d))
  {
    fprintf(stderr, "No es posible cerrar el directorio '%s': %s\n",
            dir_name, strerror(errno));
    exit(EXIT_FAILURE);
  }
}

// Leer archivo
void readFile(char *directory)
{
  FILE *fptr;
  char c;

  // Abre archivo
  fptr = fopen(directory, "r");
  if (fptr == NULL)
  {
    printf("Elige una opcion correcta \n");
    exit(0);
  }

  // Lee contenido de archivo
  printf("\nContenido de la carta: %s\n\n", directory);

  c = fgetc(fptr);
  while (c != EOF)
  {
    printf("%c", c);
    c = fgetc(fptr);
  }

  printf("\n");

  fclose(fptr);
}

// Funcion para verificar si un string termina con algun sufijo
int endsWith(const char *str, const char *suffix)
{
  if (!str || !suffix)
    return 0;
  size_t lenstr = strlen(str);
  size_t lensuffix = strlen(suffix);
  if (lensuffix > lenstr)
    return 0;
  return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

// Concatena un String variable con una constante
char *concatenateStringNav(char *text1, char *text2)
{
  char src[STRING_LENGTH];
  strcpy(src, text2);
  strcpy(dest, text1);
  strcat(dest, src);

  return dest;
}

// Funciones utiles
int convertStringToNumber(char *text)
{
  int i, len;
  int result = 0;

  len = strlen(text);

  for (i = 0; i < len; i++)
  {
    result = result * 10 + (text[i] - '0');
  }
  return result;
}