#
#  Tarea 1 - Sistemas Operativos
#  1 Semestre, 2019
# 
#  Autor: 	Anibal Bastias Soto
#  ROL: 	2604215-1
#  Carrera: Ingenieria de Ejecucion en Informatica
# 
#  Archivo: Makefile
#  
#  Este archivo construye la aplicacion leyendo las carpetas src, src/include
#  encontrando archivos .c y .h para luego generar objetos en la carpeta obj/
#  y el ejecutabl en la ruta principal con el compilador GCC
# 

TARGET = Tarea1-2604215-1
TARGET_OUTPUT = Cartas
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall
ODIR=obj
HDIR=include
SDIR=src

.CLEARALL: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(wildcard $(SDIR)/*.c))
HEADERS = $(wildcard $(SDIR)/$(HDIR)/*.h)

$(ODIR)/%.o: $(SDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f $(ODIR)/*.o
	-rm -f $(TARGET)
	-rm -r $(TARGET_OUTPUT)