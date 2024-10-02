all: getoptFunctions.o bmp.o fbroker.o fworker.o lab2 broker worker

getoptFunctions.o: getoptFunctions.c getoptFunctions.h
	gcc -Wall -c getoptFunctions.c

bmp.o: bmp.c bmp.h
	gcc -Wall -c bmp.c

fbroker.o: fbroker.c fbroker.h
	gcc -Wall -c fbroker.c

fworker.o: fworker.c fworker.h
	gcc -Wall -c fworker.c

lab2: getoptFunctions.o lab2.c
	gcc getoptFunctions.o lab2.c -o lab2

broker: fbroker.o bmp.o broker.c
	gcc fbroker.o bmp.o broker.c -o broker

worker: fworker.o bmp.o worker.c
	gcc fworker.o bmp.o worker.c -o worker

clean:
	rm -f *.o lab2 broker worker