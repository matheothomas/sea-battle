CC=gcc
OPT=-Wall -Wextra

prog: seaBattle.o network.o main.o
	${CC} ${OPT} seaBattle.o network.o main.o -o prog
main.o: main.c
	${CC} ${OPT} main.c -c
seaBattle.o: seaBattle.c
	${CC} ${OPT} seaBattle.c -c
network.o: network.c
	${CC} ${OPT} network.c -c

clean:
	rm -f *.o *.gch

