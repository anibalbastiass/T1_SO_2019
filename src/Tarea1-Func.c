/*
 *  Tarea 1 - Sistemas Operativos
 *  1 Semestre, 2019
 * 
 *  Autor:      Anibal Bastias Soto
 *  ROL:        2604215-1
 *  Carrera:    Ingenieria de Ejecucion en Informatica
 * 
 *  Archivo:    Tarea1-Func.c 
 *  
 *  Este archivo realiza las funciones necesarias para procesar los datos
 *  de entrada a traves de un archivo o recorrer en una carpeta todos los
 *  archivos, creando la ruta de carpetas, moviendo el archivo a al ruta respectiva
 *  y algunas funciones utiles que se utilizan en otras funciones
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

// Constantes
#define FOLDER_PERMISSIONS 07777
#define STRING_LENGTH 1024
#define NUMBER_CARD_LENGTH 100
#define CARD_TYPE_LENGTH 3
#define CARD_EDIT_LENGTH 5

// Variables globales
char root_folder[STRING_LENGTH] = "Cartas";
char type_arr[CARD_TYPE_LENGTH][STRING_LENGTH] = {"/Normal", "/Magico", "/Raro"};
char edition_arr[CARD_EDIT_LENGTH][STRING_LENGTH] = {"/Skrull", "/Kree",
                                                     "/Shi Ar", "/Titan", "/Zen La"};

// Estructura Nodo de Carta
typedef struct card
{
  char title[STRING_LENGTH];
  char type[STRING_LENGTH];
  char edition[STRING_LENGTH];
  char number[STRING_LENGTH];
} Card;

// Variables globales para retorno de funciones
// con el proposito de que no quede memoria basura
// en el stack al momento de finalizar cada metodo
Card card;
char dest[STRING_LENGTH];
char strToNumber[100];
char *strNumberSplited;
int initSize;

// Funciones utiles
char *getNumberPath(int number)
{
  char slash = '/';
  sprintf(strToNumber, "%c%d", slash, number);
  return strToNumber;
}

// Concatena un String variable con una constante
char *concatenateString(char *text1, char *text2)
{
  char src[STRING_LENGTH];
  strcpy(src, text2);
  strcpy(dest, text1);
  strcat(dest, src);

  return dest;
}

// Funcion Split, para separar string por un caracter separador
// y obtener solo la primera posicion
char *splitAndGetFirst(char *str, char *delim)
{
  initSize = strlen(str);
  char *ptr = strtok(str, delim);

  int i = 0;
  while (ptr != NULL)
  {
    if (i == 0)
    {
      strNumberSplited = ptr;
    }
    ptr = strtok(NULL, delim);
    i++;
  }
  return strNumberSplited;
}

// Crea carpetas segun los arreglos definidos por los
// supuestos de la tarea
void createFolders()
{
  int i, j, k;

  // Crea Carpeta raiz
  printf("Creación de Carpeta Raiz:\n\n");
  printf("  Carpeta creada: [%s]\n", root_folder);
  mkdir(root_folder, FOLDER_PERMISSIONS);

  printf("\nCreación de Carpetas de Tipos:\n\n");

  char dest_edic[STRING_LENGTH];

  for (i = 0; i < CARD_TYPE_LENGTH; ++i)
  {
    // Crea String para ruta principal de cartas y tipos
    char src_type[STRING_LENGTH], dest_type[STRING_LENGTH];
    strcpy(src_type, type_arr[i]);
    strcpy(dest_type, root_folder);
    strcat(dest_type, src_type);

    mkdir(dest_type, FOLDER_PERMISSIONS);

    for (j = 0; j < CARD_EDIT_LENGTH; j++)
    {
      // Crea String para ruta concatenada con Raiz, tipos y ediciones
      char src_edic[STRING_LENGTH];
      strcpy(src_edic, edition_arr[j]);
      strcpy(dest_edic, dest_type);
      strcat(dest_edic, src_edic);

      mkdir(dest_edic, FOLDER_PERMISSIONS);

      for (k = 1; k <= NUMBER_CARD_LENGTH; k++)
      {
        // Crea String para ruta concatenada con Raiz, tipos, ediciones y numeros
        char src_num[STRING_LENGTH], dest_num[STRING_LENGTH];
        char *numberPath = getNumberPath(k);

        strcpy(src_num, numberPath);
        strcpy(dest_num, dest_edic);
        strcat(dest_num, src_num);

        mkdir(dest_num, FOLDER_PERMISSIONS);
      }
      printf("  Carpeta creada: [%s]\n", dest_edic);
    }
    printf("  Carpeta creada de Numeros: 0 - 100\n\n");
  }
}

// Funcion que mueve actual archivo de prueba a ruta
// indicada segun el tipo, edicion y numero
void moveCardFromDirectoryToPathFolder(char *path)
{
  FILE *ptr_file;
  ptr_file = fopen(path, "r");

  if (!ptr_file)
  {
    printf("No se puede abrir archivo\n");
    return;
  }

  Card card_temp;
  fscanf(ptr_file, "%[^\t\n]\n%[^\t\n]\n%[^\t\n]\n%[^\t\n]", card_temp.title, card_temp.type, card_temp.edition, card_temp.number);
  printf("%s - %s - %s - %s\n", card_temp.title, card_temp.type, card_temp.edition, card_temp.number);
  card = card_temp;

  fclose(ptr_file);

  createFileInCardPath();
}

void moveCardToPathFolder(char *argv)
{
  FILE *ptr_file;
  ptr_file = fopen(argv, "r");

  if (!ptr_file)
  {
    printf("No se puede abrir archivo\n");
    return;
  }

  // Se inicializa nodo temporal para guardar muchas instancias
  Card card_temp;

  fscanf(ptr_file, "%[^\t\n]\n%[^\t\n]\n%[^\t\n]\n%[^\t\n]", card_temp.title, card_temp.type, card_temp.edition, card_temp.number);
  card = card_temp;

  fclose(ptr_file);

  createFileInCardPath();
}

void createFileInCardPath()
{
  // Concatenar path con cada parametro de struct Card

  // 1. Root + Tipo
  char src_type[STRING_LENGTH], dest_type[STRING_LENGTH];
  strcpy(src_type, concatenateString("/", card.type));
  strcpy(dest_type, root_folder);
  strcat(dest_type, src_type);

  // 2. Tipo + Edicion
  char src_edic[STRING_LENGTH], dest_edic[STRING_LENGTH];
  strcpy(src_edic, concatenateString("/", card.edition));
  strcpy(dest_edic, dest_type);
  strcat(dest_edic, src_edic);

  // 3. Edicion + Numero
  char src_num[STRING_LENGTH], dest_num[STRING_LENGTH];
  strcpy(src_num, concatenateString("/", splitAndGetFirst(card.number, "/")));
  strcpy(dest_num, dest_edic);
  strcat(dest_num, src_num);

  // 4. Ruta + Nombre Archivo
  char src_path_num[STRING_LENGTH], dest_path_file[STRING_LENGTH];
  strcpy(src_path_num, concatenateString("/", card.title));
  strcpy(dest_path_file, dest_num);
  strcat(dest_path_file, src_path_num);

  // 5. Nombre Archivo + formato txt
  char src_file[STRING_LENGTH], dest_file[STRING_LENGTH];
  strcpy(src_file, ".txt");
  strcpy(dest_file, dest_path_file);
  strcat(dest_file, src_file);

  FILE *fp;
  mkdir(dest_num, 0777);
  fp = fopen(dest_file, "w+");

  if (!fp)
  {
    printf("No es posible crear archivo, no cumple con las reglas de la aplicacion\n");
    return;
  }
  else
  {
    // Escribir atributo de Card en archivo por linea
    fprintf(fp, "%s", concatenateString(card.title, "\n"));
    fprintf(fp, "%s", concatenateString(card.type, "\n"));
    fprintf(fp, "%s", concatenateString(card.edition, "\n"));
    fprintf(fp, "%s", concatenateString(card.number, "\n"));

    printf("Carta Insertada: [%s]\n\n", dest_file);
  }

  // Se cierra puntero para escribir en archivo
  fclose(fp);
}

void mapDirectories(char *directory)
{
  DIR *dir;

  //Información sobre el archivo
  struct dirent *ent;

  dir = opendir(directory);

  if (dir == NULL)
    error("No es posible abrir el directorio");

  // Lectura de archivos por directorio
  while ((ent = readdir(dir)) != NULL)
  {
    // Directorio actual (.) y el anterior (..), tal como la llamada Unix "ls"
    if ((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0))
    {
      // Procesamiento de cada carta test de forma recursiva
      // Concatenacion de paths variables
      char src[STRING_LENGTH], dest[STRING_LENGTH];
      strcpy(src, ent->d_name);
      strcpy(dest, concatenateString(directory, "/"));
      strcat(dest, src);
      
      moveCardFromDirectoryToPathFolder(dest);
    }
  }
  closedir(dir);
}

// Funcion de error generco
void error(const char *s)
{
  perror(s);
  exit(EXIT_FAILURE);
}
