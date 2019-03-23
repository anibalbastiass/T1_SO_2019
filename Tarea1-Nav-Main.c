/*

 Nombre     : minishell.c
 Autor      : Anibal Bastias Soto
 ROL		: 2604215-1
 Carrera    : Ingenieria de Ejecucion en Informatica

 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include "include/Tarea1-Nav.h"

struct comando_t command;

// Limpieza de pantalla
void limpiarPantalla()
{
  printf("\033[2J\033[1;1H");
}

// Comando "cd" de cambio de directorio
void cambiarDirectorio()
{
  if (command.argv[1] == NULL)
  {
    chdir(getenv("HOME"));
  }
  else
  {
    if (chdir(command.argv[1]) == -1)
    {
      printf(" %s: no es un directorio valido\n", command.argv[1]);
    }
  }
}

// Funcion que verifica los comandos reservados como "cd" y "clear"
int comprobarComandosInternos()
{

  if (strcmp("cd", command.argv[0]) == 0)
  {
    cambiarDirectorio();
    return 1;
  }
  if (strcmp("clear", command.argv[0]) == 0)
  {
    limpiarPantalla();
    return 1;
  }
  return 0;
}

// Funcion que ejecuta command, si es 0 es exitoso.
int ejecutarComando()
{
  int proccessChildId;
  int stateProccess;
  pid_t tProcessChildId;

  proccessChildId = fork();
  if (proccessChildId < 0)
  {
    fprintf(stderr, "Comando Fork fallo: \n");
    return 1;
  }
  else if (proccessChildId == 0)
  {
    /* Proceso hijo */
    execve(command.name, command.argv, 0);
    printf("Ejecucion de proceso hijo fallo\n");
    return 1;
  }
  else if (proccessChildId > 0)
  {
    /* Proceso Padre */
    do
    {
      tProcessChildId = waitpid(proccessChildId, &stateProccess, WUNTRACED | WCONTINUED);
      if (tProcessChildId == -1)
      {
        perror("waitpid");
        exit(EXIT_FAILURE);
      }

      if (WIFEXITED(stateProccess))
      {
        return 0;
      }
      else if (WIFSIGNALED(stateProccess))
      {
        printf("Proceso terminado por senal %d\n", WTERMSIG(stateProccess));
      }
      else if (WIFSTOPPED(stateProccess))
      {
        printf("Detenido por senal %d\n", WSTOPSIG(stateProccess));
      }
      else if (WIFCONTINUED(stateProccess))
      {
        printf("Continuado\n");
      }
    } while (!WIFEXITED(stateProccess) && !WIFSIGNALED(stateProccess));
    return 0;
  }
}

// Funcion Main del programa
void initNavigation()
{
  parsearRuta(pathv);
  printWelcomeMessage();

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
      // Lee command
      leerComando(tCommandLine, &inCommand);

      if ((strcmp(tCommandLine, "exit") == 0) || (strcmp(tCommandLine, "quit") == 0))
        break;

      parsearComando(tCommandLine, &command);

      if (comprobarComandosInternos() == 0)
      {
        command.name = seekPath(command.argv, pathv);

        if (command.name == NULL)
        {
          printf("Stub: error\n");
          continue;
        }

        ejecutarComando();
      }
    }
  }

  printf("\n");
  exit(EXIT_SUCCESS);
}
