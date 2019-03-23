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
#  Esta archivo implementa las funciones de Tarea1-Func.c para hacer todas las
#  acciones necesarias que requieren esta tarea en un metodo Main, para la ejecucion
#  de la aplicacion
# 

TARGET = Tarea1-2604215-1
TARGET_OUTPUT = Cartas
LIBS = -lm
CC = gcc
CFLAGS = -g -Wall
ODIR=obj
HDIR=include

.CLEARALL: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.c, $(ODIR)/%.o, $(wildcard *.c))
HEADERS = $(wildcard $(HDIR)/*.h)

$(ODIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f $(ODIR)/*.o
	-rm -f $(TARGET)
	-rm -r $(TARGET_OUTPUT)