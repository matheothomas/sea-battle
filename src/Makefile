CC=gcc
OPT=-Wall -Wextra -I /usr/include/SDL2
OPTSDL=-lSDL2_image -lSDL2_ttf -lSDL2

seaBattle: seaBattle.o network.o main.o graphics.o
	${CC} ${OPT} seaBattle.o network.o main.o graphics.o -o seaBattle ${OPTSDL}
main.o: main.c
	${CC} ${OPT} main.c -c 
seaBattle.o: seaBattle.c
	${CC} ${OPT} seaBattle.c -c
network.o: network.c
	${CC} ${OPT} network.c -c
graphics.o: graphics.c
	${CC} ${OPT} graphics.c -c

clean:
	rm -f *.o *.gch

