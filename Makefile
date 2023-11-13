CC=gcc
OPT=-Wall -Wextra -I /usr/include/SDL2
OPTSDL=-lSDL2_image -lSDL2_ttf -lSDL2

prog: seaBattle.o network.o main.o graphics.o
	${CC} ${OPT} seaBattle.o network.o main.o graphics.o -o prog ${OPTSDL}
main.o: main.c
	${CC} ${OPT} main.c -c ${OPTSDL}
seaBattle.o: seaBattle.c
	${CC} ${OPT} seaBattle.c -c
network.o: network.c
	${CC} ${OPT} network.c -c
graphics.o: graphics.c
	${CC} ${OPT} graphics.c -c ${OPTSDL}

clean:
	rm -f *.o *.gch

