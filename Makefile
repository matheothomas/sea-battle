CC=gcc
OPT=-Wall -Wextra

prog: seaBattle.o
	${CC} ${OPT} seaBattle.o -o prog
seaBattle.o: seaBattle.c
	${CC} ${OPT} seaBattle.c -c

clean:
	rm -f *.o *.gch

