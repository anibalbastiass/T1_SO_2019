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
y ediciones aleatoriamente de las series de Marvel.

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

Luego de haber creado las carpetas y archivos, se ejecuta un mini shell, donde se 
puede ir al directorio de cartas y acceder a la informacion de cada uno.

Se utilizan los comandos de navegacion en Unix cd (Cambio de directorio), cd .. 
(Retroceder a directorio anterior) y ls (Listar contenido de directorio)

### Modo de ejecucion
- Al iniciar la aplicacion, se puede ejecutar de 2 formas:

* Leer un archivo: (-f)
* Leer muchos archivos de un directorio (-d)

Ejemplos:

./Tarea1-2604215-1 -f carta-test1.txt
./Tarea1-2604215-1 -d cartas_test

### Test de pruebas
Dentro de esta tarea, se encuentra una carpeta llamada "cartas_test" con 10 archivos
donde se puede llamar de forma recursiva y ver como se insertan todas las cartas
en sus respectivas carpetas

*by @anibalbastiass*