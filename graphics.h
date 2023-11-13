/* name : graphics.h
 * author : matheo thomas
 * date : 13-11-23
 */

#ifndef graphics_h 
#define graphics_h

// Struct definitions



// Functions definitions
void placeShipTop(SDL_Renderer *renderer, int y, int x);

void placeShipBottom(SDL_Renderer *renderer, int y, int x);

void printCrossTop(SDL_Renderer *renderer, int y, int x);

void printCrossBottom(SDL_Renderer *renderer, int y, int x);

void printSea(SDL_Renderer *renderer, sea **s1, sea **s2);

void afficherFenetre(SDL_Renderer *renderer, sea **s1, sea **s2);
#endif

