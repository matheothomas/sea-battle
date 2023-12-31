/* name : seaBattle.h
 * author : matheo thomas
 * date : 08-11-23
 */

#ifndef seaBattle_h 
#define seaBattle_h

// Struct definitions

typedef struct sea {
	int isShip;
	int touched;	// 0 if not aimed, 1 if aimed but empty, 2 if touched
} sea;


// Functions definitions

// creates and initialises a map.
sea **initSea();

// prints the two maps on the standard output.
void showSea(sea **s1, sea **s2);

// Verifies that the coordinates are empty and with the area.
int checkCoords(sea **s, int c1, int c2);

// Places the specified ship in the area if the coordinates are valid.
int placeShip(sea **s, int id, int c1, int c2, char dir);

// Asks the user where to put the ships to initiate the game.
void placeShips(sea **sships, sea **stouches);


// returns 2 if game is won, 1 if ship is sunk, else 0.
int victoire(int id);

// Modifies the upper map according to the sent coordinates.
void sent(sea **stouches, int c1, int c2, int isShipTouched);

// Modifies the lower map according to the received coordinates.
int received(sea **sships, int c1, int c2);

// frees the memory of a sea.
void freeSea(sea **s);

// loads a pre-configured map for testing purposes.
void loadPreConfig(sea **s);

#endif

