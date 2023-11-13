/* name : graphics.c
 * author : matheo thomas
 * date : 13-11-23
 */

#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include"seaBattle.h"


void placeShipTop(SDL_Renderer *renderer, int y, int x){
	int x1 = 20 + 40*x;
	int y1 = 20 + 40*y;
	SDL_SetRenderDrawColor(renderer, 100, 100, 200, 255);
	SDL_Rect rect;
	rect.x = x1 + 5;
	rect.y = y1 + 5;
	rect.w = rect.h = 31;
	SDL_RenderFillRect(renderer,&rect);
}

void placeShipBottom(SDL_Renderer *renderer, int y, int x){
	int x1 = 20 + 40*x;
	int y1 = 440 + 40*y;
	SDL_SetRenderDrawColor(renderer, 100, 100, 200, 255);
	SDL_Rect rect;
	rect.x = x1 + 5;
	rect.y = y1 + 5;
	rect.w = rect.h = 31;
	SDL_RenderFillRect(renderer,&rect);
}	

void printCrossTop(SDL_Renderer *renderer, int y, int x){
	int x1 = 20 + 40*x;
	int y1 = 20 + 40*y;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(renderer, x1+5, y1+5, x1+36, y1+36);
	SDL_RenderDrawLine(renderer, x1+36, y1+5, x1+5, y1+36);
}

void printCrossBottom(SDL_Renderer *renderer, int y, int x){
	int x1 = 20 + 40*x;
	int y1 = 440 + 40*y;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(renderer, x1+5, y1+5, x1+36, y1+36);
	SDL_RenderDrawLine(renderer, x1+36, y1+5, x1+5, y1+36);
}

void printSea(SDL_Renderer *renderer, sea **s1, sea **s2){
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			if((s2[i][j].touched > 99 && s2[i][j].touched < 200) || s2[i][j].touched == 1){ 	// s2[i][j].touched == 1
				printCrossTop(renderer, i, j);
			} else if(s2[i][j].touched > 200 || s2[i][j].touched == 2){						// s2[i][j].touched == 2
				placeShipTop(renderer, i, j);
			}
			if(s1[i][j].isShip != 0){
				placeShipBottom(renderer, i, j);
			}
			if(s1[i][j].touched != 0){
				printCrossBottom(renderer, i, j);
			}
		}
	}
}

void afficherFenetre(SDL_Renderer *renderer, sea **s1, sea **s2){
	SDL_Rect rect;

	SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	rect.x = rect.y = 20;
	rect.w = rect.h = 400;
	SDL_RenderFillRect(renderer, &rect);
	
	rect.x = 20;
	rect.y = 440;
	rect.w = rect.h = 400;
	SDL_RenderFillRect(renderer, &rect);
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	for(int i = 1; i < 10; i++){
			SDL_RenderDrawLine(renderer, 20, 20 + 40*i, 420, 20 + 40*i);
			SDL_RenderDrawLine(renderer, 20 + 40*i, 20, 20 + 40*i, 420);
			
			SDL_RenderDrawLine(renderer, 20, 440 + 40*i, 420, 440 + 40*i);
			SDL_RenderDrawLine(renderer, 20 + 40*i, 440, 20 + 40*i, 840);
	}

	
	printSea(renderer, s1, s2);	

	SDL_RenderPresent(renderer);
}
