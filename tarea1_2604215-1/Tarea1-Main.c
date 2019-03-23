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
 *  Este archivo implementa las funciones de Tarea1-Func.c para hacer todas las
 *  acciones necesarias que requieren esta tarea en un metodo Main, para la ejecucion
 *  de la aplicacion
 */ 

#include <stdio.h>
#include "Tarea1-Main.h"

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

  // Lee Archivo de entrada por teclado
  if (2 != argc)
  {
    printf("\nDebes introducir un archivo .txt o directorio para ejecutar la aplicacion.\n\n");
    return 1;
  }

  // Luego Guarda los datos del archivo, hace match de tipos de cartas
  // Y crea las carpetas
  createFolders();

  // Despues copia este archivo según la ubicación de la carpeta correspondiente
  //moveCardToPathFolder(argv);

  // Mueve las cartas de un directorio test de forma recursiva
  mapDirectory();

  // Muestar mini shell para navegar en las carpetas de las cartas

  return 0;
}