/*

 Nombre     : minishellfunc.c
 Autor      : Anibal Bastias Soto
 ROL		: 2604215-1
 Carrera    : Ingenieria de Ejecucion en Informatica

 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include "include/Tarea1-Nav.h"

// Imprime mensaje de Bienvenida
void printWelcomeMessage()
{
  printf("\nBienvenido a mini-shell-abastias\n");
}

// Imprime prompt
void printPrompt()
{
  printf("mini-shell-abastias > ");
}

// Funcion que busca la path ingresada segun loque se ingresa
// en prompt
char *seekPath(char **argv, char **dir)
{
  char *result;
  char processName[MAX_PATH_LEN];
  if (*argv[0] == '/')
  {
    return argv[0];
  }
  else if (*argv[0] == '.')
  {
    if (*++argv[0] == '.')
    {
      if (getcwd(processName, sizeof(processName)) == NULL)
        perror("Error de path\n");
      else
      {
        *--argv[0];
        asprintf(&result, "%s%s%s", processName, "/", argv[0]);
      }
      return result;
    }
    *--argv[0];
    if (*++argv[0] == '/')
    {
      if (getcwd(processName, sizeof(processName)) == NULL)
        perror("Error de path\n");
      else
      {
        asprintf(&result, "%s%s", processName, argv[0]);
      }
      return result;
    }
  }

  // Acceso a PATH para verificar si esta archivo en directorio
  int i;
  for (i = 0; i < MAX_PATHS; i++)
  {
    if (dir[i] != NULL)
    {
      asprintf(&result, "%s%s%s", dir[i], "/", argv[0]);
      if (access(result, X_OK) == 0)
      {
        return result;
      }
    }
    else
      continue;
  }

  fprintf(stderr, "%s: command no encontrado\n", argv[0]);
  return NULL;
}

// Funcion que pobla y parsea la variable en ambiente PATH
int parsearRuta(char *dirs[])
{
  char *envPath;
  char *path;
  int i;

  for (i = 0; i < MAX_ARGS; i++)
    dirs[i] = NULL;
  envPath = (char *)getenv("PATH");
  path = (char *)malloc(strlen(envPath) + 1);
  strcpy(path, envPath);

  char *pch;
  pch = strtok(path, ":");
  int j = 0;

  // Bucle a traves de la path para delimitador ":"
  while (pch != NULL)
  {
    pch = strtok(NULL, ":");
    dirs[j] = pch;
    j++;
  }
}

// Funcion que parsea la linea de comandos en argv y argc en prompt
int parsearComando(char *commandLine, struct comando_t *command)
{
  char *pch;
  pch = strtok(commandLine, " ");
  int i = 0;
  while (pch != NULL)
  {
    command->argv[i] = pch;
    pch = strtok(NULL, " ");
    i++;
  }
  command->argc = i;
  command->argv[i++] = NULL;

  return 0;
}

// Funcion que lee y guarda la linea de command que ingresa el usuario
int leerComando(char *buffer, char *commandIn)
{
  bufferChars = 0;

  while ((*commandIn != '\n') && (bufferChars < LINE_LEN))
  {
    buffer[bufferChars++] = *commandIn;
    *commandIn = getchar();
  }
  buffer[bufferChars] = '\0';

  return 0;
}
