/* name : seaBattle.c
 * author : matheo thomas
 * date : 08-11-23
 */

#include<stdio.h>
#include<stdlib.h>
#include"seaBattle.h"

#define SIZE 10

int infoShip[] = { -1, 5, 4, 3, 3, 2 };

sea **initSea(){
	sea **s = (sea **)malloc(SIZE*sizeof(sea *));
	for(int i = 0; i < SIZE; i++){
		s[i] = (sea *)malloc(SIZE*sizeof(sea));
		for(int j = 0; j < SIZE; j++){
			s[i][j].touched = 0;
			s[i][j].isShip = 0;
		}
	}
	return s;
}

void showSea(sea **s1, sea **s2){
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			if(s2[i][j].touched == 0){
				printf(". ");
			} else if(s2[i][j].touched == 1){
				printf("o ");
			} else {
				printf("x ");
			}
		}
		printf("\n");
	}
	printf("-------------------\n");
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			if(s1[i][j].isShip == 0){
				if(s1[i][j].touched != 0){
					printf("o ");
				} else {
					printf(". ");
				}
			} else if(s1[i][j].isShip != 0){
				if(s1[i][j].touched != 0){
					printf("X ");
				} else {
					printf("x ");
				}
			}
		}
		printf("\n");
	}
	printf("\n");
}

int checkCoords(sea **s, int c1, int c2){
	int res = 0;
	if(s[c1][c2].isShip != 0){
		res = 1;
	}
	if(c1 < 0 || c1 > SIZE || c2 < 0 || c2 > SIZE){
		res = 1;
	}
	return res;
}

int placeShip(sea **s, int id, int c1, int c2, char dir){
	int validCoords = 0;
	validCoords += checkCoords(s, c1, c2);
	for(int j = 1; j < infoShip[id]; j++){
		if(dir == 'u'){
			validCoords += checkCoords(s, c1-j, c2);
		} else if(dir == 'd'){
			validCoords += checkCoords(s, c1+j, c2);
		} else if(dir == 'l'){
			validCoords += checkCoords(s, c1, c2-j);
		} else {
			validCoords += checkCoords(s, c1, c2+j);
		}
	}
	if(validCoords == 0){
		s[c1][c2].isShip = id;
		for(int j = 1; j < infoShip[id]; j++){
			if(dir == 'u'){
				s[c1-j][c2].isShip = id;
			} else if(dir == 'd'){
				s[c1+j][c2].isShip = id;
			} else if(dir == 'l'){
				s[c1][c2-j].isShip = id;
			} else {
				s[c1][c2+j].isShip = id;
			}
		}
	} else {
		printf("Wrong coordinates ! Retry.\n");
	}
	return validCoords;
}

void placeShips(sea **sships, sea **stouches){
	int coord1;
	int coord2;
	char dir;
	
	for(int i = 1; i < 6; i++){
		printf("Enter first coordinate of ship of size %d : ", infoShip[i]);
		scanf("%d%*c", &coord1);
		printf("Enter second coordinate of ship of size %d : ", infoShip[i]);
		scanf("%d%*c", &coord2);
		printf("Enter orientation of ship of size %d : (u, d, r, l)", infoShip[i]);
		scanf("%c%*c", &dir);
		
		coord1--;
		coord2--;
		
		if(placeShip(sships, i, coord1, coord2, dir) != 0){
			i--;
		} else {
			showSea(sships, stouches);
		}	
	}
}

void sent(sea **stouches, int c1, int c2, int isShipTouched){
	printf("Sent c1 : %d\n", c1);
	printf("Sent c2 : %d\n", c2);
	printf("Sent isShipTouched : %d\n", isShipTouched);
	stouches[c1][c2].touched = isShipTouched;
}

int received(sea **sships, int c1, int c2){
	int touched = 1;
	printf("Received c1 : %d\n", c1);
	printf("Received c2 : %d\n", c2);
	if(sships[c1][c2].isShip != 0){
		sships[c1][c2].touched = 2;
		touched = 2;
	} else {
		sships[c1][c2].touched = 1;
	}
	return touched;
}



void freeSea(sea **s){
	for(int i = 0; i < SIZE; i++){
		free(s[i]);
	}
	free(s);
}

void loadPreConfig(sea **s){
	placeShip(s, 1, 1, 1, 'd');
	placeShip(s, 2, 1, 5, 'r');
	placeShip(s, 3, 4, 3, 'd');
	placeShip(s, 4, 6, 7, 'r');
	placeShip(s, 5, 9, 1, 'r');
}
/*
int main(void){
	sea **s1ships = initSea();
	sea **s1touches = initSea();
	
	showSea(s1ships, s1touches);
	//placeShips(s1ships, s1touches);
	loadPreConfig(s1ships);
	
	sent(s1touches, 1, 1, received(s1ships, 1, 1));
	sent(s1touches, 3, 5, received(s1ships, 3, 5));

	showSea(s1ships, s1touches);

	freeSea(s1ships);
	freeSea(s1touches);
	return 0;
}
*/
