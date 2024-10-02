all: getoptFunctions.o bmp.o funciones.o render.o lab1

getoptFunctions.o: getoptFunctions.c getoptFunctions.h
	gcc -c getoptFunctions.c

bmp.o: bmp.c bmp.h
	gcc -c bmp.c

funciones.o: funciones.c funciones.h
	gcc -c funciones.c
	
render.o: render.c render.h
	gcc -c render.c

lab1: render.o funciones.o bmp.o getoptFunctions.o lab1.c
	gcc getoptFunctions.o bmp.o funciones.o render.o lab1.c -o lab1

clean:
	rm -f *.o lab1