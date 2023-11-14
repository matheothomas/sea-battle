/* name : graphics.h
 * author : matheo thomas
 * date : 13-11-23
 */

#ifndef graphics_h 
#define graphics_h

// Functions definitions

// Prints a ship symbol on the top map
void placeShipTop(SDL_Renderer *renderer, int y, int x);

// Prints a ship symbol on the bottom map
void placeShipBottom(SDL_Renderer *renderer, int y, int x);

// Prints a cross symbol on the top map
void printCrossTop(SDL_Renderer *renderer, int y, int x);

// Prints a cross symbol on the bottom map
void printCrossBottom(SDL_Renderer *renderer, int y, int x);

// Prints "Coulé !" in the status area
void printCoule(SDL_Renderer *renderer);

// Prints the ships and crosses of a player 
void printSea(SDL_Renderer *renderer, sea **s1, sea **s2);

// Loads everything to be displayed in the window
void afficherFenetre(SDL_Renderer *renderer, sea **s1, sea **s2);
#endif

