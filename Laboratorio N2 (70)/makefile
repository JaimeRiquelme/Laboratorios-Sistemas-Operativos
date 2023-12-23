all: lab2 broker worker

lab2: lab2.c
	gcc -Wall -g lab2.c -o lab2

broker: broker.c fbroker.o
	gcc -Wall -g broker.c fbroker.o -o broker

worker: worker.c fworker.o
	gcc -Wall -g worker.c fworker.o -o worker -lm

fbroker.o: fbroker.c
	gcc -Wall -g -c fbroker.c -o fbroker.o

fworker.o: fworker.c fworker.h
	gcc -Wall -g -c fworker.c -o fworker.o

clean:
	rm -f *.o lab2 broker worker out*.txt
