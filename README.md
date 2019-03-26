# Tarea 1 - Sistemas Operativos

``` 
1 Semestre 2019
Autor:      Anibal Bastias Soto
ROL:        2604215-1
Carrera:    Ingenieria de Ejecucion en Informatica
```

### Introduccion
 
El objetivo de esta tarea es realizar llamadas a sistema para la manipulacion
de archivos y directorios. Dentro de estos, se utiliza creacion de directorios, 
recorrerlos, abrir, leer y escribir archivos.

### Explicacion de la aplicacion
En esta aplicacion, siguiendo los supuestos de la tarea, se inventaron personajes
y ediciones aleatoriamente de las series de Comics Marvel.

* Tipos (3): Magico, Normal, Raro
* Edicion (5): Kree, Shi Ar, Skrull, Titan, Zen La 
* Supuesto de 100 numeros para este caso (Se crean todas las carpetas de 1 a 100)

- Al iniciar la aplicacion, se puede ejecutar de 2 formas:

* Leer un archivo
* Leer muchos archivos de un directorio

Al ejecutar, la aplicacion crea el arbol de directorio segun los datos indicados y al terminar este proceso, comienza a leer la informacion del archivo test. Obtiene estos datos y los pasa a un struct Card. 

Para completar la ruta de carpetas con una raiz "Cartas", y luego los demas atributos. Al terminar de recorrer la ruta,  se crea el nuevo archivo, con el nombre de la primera linea del archivo origen (Nombre del personaje), y se crea. 

En caso de ser una llamada recursiva, sigue con el siguiente archivo del directorio

## Navegacion de cartas

Luego de haber creado las carpetas y archivos, se puede ejecutar un navegador, donde muestra
la lista de carpetas donde contiene cartas ingresadas, y se puede ver la informacion de cada 
carta introduciendo la opcion que solicita la apliacacion.

### Estructura del Proyecto

El proyecto consta de 2 carpetas:

- src: Directorio que contiene los archivos .c (Variables y funciones en ingles, comentarios en espanol)
- src/include: Directorio donde contiene los archivos .h (Cabeceras para definir variables y funciones)
- obj: Directorio donde se generan los objetos despues de compilar
- Makefile: Archivo base para compilar mediante GCC la aplicacion programada en lenguaje C
- tests: Directorio de set de cartas para probar la aplicacion
- carta-test.txt: Archivo para probar la aplicacion con comando -f (Probar de un archivo)
- README.md: Archivo que explica con detalle el desarrollo de la tarea

Despues de compilar, se generará la carpeta "Cartas" donde contendra las cartas ordenadas.

### Modo de compilacion
El compilador GCC de Unix genera archivos object en la carpeta obj (.o) y el ejecutable para usar
la aplicacion. En el Makefile se definieron las siguientes reglas:

- make clean (Limpia el ejecutable, .o y directorio de Cartas generadas)
- make (Compila la aplicacion y genera objetos y ejecutable)

Se recomienda ejecutar estos 2 scripts para modo de pruebas

### Modo de ejecucion
- Al iniciar la aplicacion, se puede ejecutar de 2 formas:

* Leer un archivo: (-f)
* Leer muchos archivos de un directorio (-d)
* Navegar el directorio de carpetas (-n) seguido con el nombre de la carpeta

Ejemplos:

* ./Tarea1-2604215-1 -f carta-test.txt
* ./Tarea1-2604215-1 -d tests
* ./Tarea1-2604215-1 -n Cartas

### Set de pruebas
Dentro de esta tarea, se encuentra una carpeta llamada "tests" con 10 archivos
donde se puede llamar de forma recursiva y ver como se insertan todas las cartas
en sus respectivas carpetas

*by @anibalbastiass*

PD: Si desea ver este README con estilos, puede acceder a un lector Markdown Online :)