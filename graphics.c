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
			if(s2[i][j].touched == 1){
				printCrossTop(renderer, i, j);
			} else if(s2[i][j].touched == 2){
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

void afficherFenetre(SDL_Renderer *renderer, sea **s1, sea **s2, int y1, int x1){
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

	
	s2[x1][y1].touched = 1;
	printSea(renderer, s1, s2);	
	printCrossBottom(renderer, 3, 1);

	SDL_RenderPresent(renderer);
}





int main(void){
	sea **s1ships = initSea();
	sea **s1touches = initSea();
	loadPreConfig(s1ships);

	if(SDL_Init(SDL_INIT_VIDEO) <0){
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	
	int width = 1000;
	int height = 860;
	
	SDL_Window *window;
	window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			width, height,
			SDL_WINDOW_RESIZABLE);

	if(window == 0){
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
	}

	//SDL_Delay(500);

	SDL_Renderer *renderer;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == 0){
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
	}

	if (TTF_Init() != 0){
   		fprintf(stderr, "Erreur d'initialisation TTF : %s\n", TTF_GetError()); 
	}



	int flags=IMG_INIT_JPG|IMG_INIT_PNG;
	int initted=0;
	initted=IMG_Init(flags);
	if((initted&flags) != flags){
		printf("IMG_Init : Impossible d'initialiser le support des formats JPG et PNG requis.\n'");
		printf("IMG_Init : %s\n", IMG_GetError());
	}



	SDL_Event event;
	
	int running = 1;
	int x = 0;
	int y = 0;
	//initFenetre(renderer);
	
	while (running) {
	
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_WINDOWEVENT:
					printf("window event\n");
					switch (event.window.event)  
					{
						case SDL_WINDOWEVENT_CLOSE:  
							printf("appui sur la croix\n");	
							break;
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							width = event.window.data1;
							height = event.window.data2;
							printf("Size : %d%d\n", width, height);
						default:
							afficherFenetre(renderer, s1ships, s1touches, 0, 0);
					}   
				    break;
				case SDL_MOUSEBUTTONDOWN:
					//printf("Appui :%d %d\n", event.button.x, event.button.y);
					x = (event.button.x-20)/40;
					y = (event.button.y-20)/40;
					printf("Appui :%d %d\n", x, y);
					
					afficherFenetre(renderer, s1ships, s1touches, x, y);
					
					
					
					break;
				case SDL_QUIT : 
					printf("on quitte\n");    
					running = 0;
			}
		}	
		SDL_Delay(1); //  delai minimal
	}


	SDL_DestroyRenderer(renderer);

	//TTF_CloseFont(font1);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}
