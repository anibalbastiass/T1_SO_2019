/*
 *  Tarea 1 - Sistemas Operativos
 *  1 Semestre, 2019
 * 
 *  Autor:      Anibal Bastias Soto
 *  ROL:        2604215-1
 *  Carrera:    Ingenieria de Ejecucion en Informatica
 * 
 *  Archivo:    Tarea1-Main.c 
 *  
 *  Este archivo implementa las funciones de Tarea1-Func.c y Tarea1-Nav.c para hacer todas las
 *  acciones necesarias que requieren esta tarea en un metodo Main, para la ejecucion
 *  de la aplicacion
 */

#include <stdio.h>
#include <string.h>
#include "include/Tarea1-Main.h"
#include "include/Tarea1-Nav.h"

// Inline functions
#define clearScreen() printf("\033[H\033[J")

int main(int argc, char *argv[])
{
  clearScreen();

  // Esta aplicación tiene 2 metodos de entrada
  // -f: Lectura de Archivo
  // -d: Lectura de Directorio, para recorrer archivos de forma recursiva
  //
  // Si no tiene argumentos, no se podra ejecutar la aplicacion

  // Lee Archivo de entrada por teclado los argumentos
  switch (argc)
  {
  case 3:
  { 
    if (strcmp(argv[1], "-f") == 0)
    {
      // Luego Guarda los datos del archivo, hace match de tipos de cartas
      // Y crea las carpetas
      createFolders();

      // Despues copia este archivo según la ubicación de la carpeta correspondiente
      moveCardToPathFolder(argv[2]);

      // Muestra mini shell para navegar en las carpetas de las cartas
    }
    else if (strcmp(argv[1], "-d") == 0)
    {
      createFolders();
      
      // Mueve las cartas de un directorio test de forma recursiva
      mapDirectory(argv[2]);
    }
    else if (strcmp(argv[1], "-n") == 0)
    {
      // Primero checkeamos si hay contenido o si existe el directorio

      // Luego iniciamos la navegacion
      initNavigation();
    }
    else
    {
      showLaunchError();
    }
  }
  break;
  default:
    showLaunchError();
    break;
  }
  return 0;
}

void showLaunchError()
{
  printf("TAREA 1 - SO - ABS: 2604215-1\n");
  printf("=============================\n\n");
  printf("Debes ejecutar de 2 formas:\n\n");

  printf("* Leer un archivo: (-f)\n");
  printf("* Leer muchos archivos de un directorio (-d)\n\n");

  printf("Ejemplos:\n\n");
  printf("./Tarea1-2604215-1 -f carta-test1.txt\n");
  printf("./Tarea1-2604215-1 -d cartas_test\n\n");
}