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

void printInfo(SDL_Renderer *renderer, int stat){
	TTF_Font *font1;
	font1 = TTF_OpenFont("BebasNeue-Regular.ttf", 100);
	SDL_Color textColor = {100, 100, 200, 255};
	
	SDL_Surface *surfaceCoule;
	
	if(stat == 1){
		surfaceCoule = TTF_RenderText_Solid(font1, "Coule !", textColor);
	} else if(stat == 2){
		surfaceCoule = TTF_RenderText_Solid(font1, "Gagne !", textColor);
	} else if (stat == 3){
		surfaceCoule = TTF_RenderText_Solid(font1, "Perdu...", textColor);
	}
	
	SDL_Texture *coule = SDL_CreateTextureFromSurface(renderer, surfaceCoule);
	SDL_Rect couleRect;
	couleRect.x = 470;
	couleRect.y = 200;
	couleRect.w = 280;
	couleRect.h = 60;
	SDL_RenderCopy(renderer, coule, NULL, &couleRect);
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

void afficherFenetre(SDL_Renderer *renderer, sea **s1, sea **s2, int stat){
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
	
	// Font
	TTF_Font *font1;
	font1 = TTF_OpenFont("BebasNeue-Regular.ttf", 100);
	SDL_Color textColor = {100, 100, 100, 255};
	
	// Title
	rect.x = 440;
	rect.y = 20;
	rect.w = 340;
	rect.h = 80;
	SDL_RenderFillRect(renderer, &rect);
	SDL_Surface *surfaceTitle = TTF_RenderText_Solid(font1, "seaBattle", textColor);
	SDL_Texture *title = SDL_CreateTextureFromSurface(renderer, surfaceTitle);
	SDL_Rect titleRect;
	titleRect.x = 450; 
	titleRect.y = 30;
	titleRect.w = 320;
	titleRect.h = 60;
	SDL_RenderCopy(renderer, title, NULL, &titleRect);
	
	
	// Game status
	rect.x = 440;
	rect.y = 120;
	rect.w = 340;
	rect.h = 160;
	SDL_RenderFillRect(renderer, &rect);
	SDL_Surface *surfaceStatus = TTF_RenderText_Solid(font1, "Game status", textColor);
	SDL_Texture *status = SDL_CreateTextureFromSurface(renderer, surfaceStatus);
	SDL_Rect statusRect;
	statusRect.x = 450;
	statusRect.y = 130;
	statusRect.w = 320;
	statusRect.h = 60;
	SDL_RenderCopy(renderer, status, NULL, &statusRect);
	
	// Arrows for ship orientation
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	rect.x = 440;
	rect.y = 440;
	rect.w = 340;
	rect.h = 400;
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	rect.x = 510;
	rect.y = 640;
	rect.w = 60;
	rect.h = 60;
	SDL_RenderFillRect(renderer, &rect);
	rect.x += 70;
	rect.y -= 70;
	rect.w = 60;
	rect.h = 60;
	SDL_RenderFillRect(renderer, &rect);
	rect.x += 70;
	rect.y += 70;
	rect.w = 60;
	rect.h = 60;
	SDL_RenderFillRect(renderer, &rect);
	rect.x -= 70;
	rect.y += 70;
	rect.w = 60;
	rect.h = 60;
	SDL_RenderFillRect(renderer, &rect);
		
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	for(int i = 1; i < 10; i++){
			SDL_RenderDrawLine(renderer, 20, 20 + 40*i, 420, 20 + 40*i);
			SDL_RenderDrawLine(renderer, 20 + 40*i, 20, 20 + 40*i, 420);
			
			SDL_RenderDrawLine(renderer, 20, 440 + 40*i, 420, 440 + 40*i);
			SDL_RenderDrawLine(renderer, 20 + 40*i, 440, 20 + 40*i, 840);
	}
	
	if(stat != 0){
		printInfo(renderer, stat);
	}

	printSea(renderer, s1, s2);	

	SDL_RenderPresent(renderer);
}
