# sea-battle

**seaBattle** is a game of sea battle developed in C, with the ability of playing it on two different machines on a same local network.

This game helped me understand sockets in C, and has been a great project to make from scratch.

## Roadmap
- [x] Build the core of the game.
- [x] Add local multiplayer mode.
- [x] Build a graphical interface with SDL2.
- [ ] Add a solo mode against a bot.

## Requirements
- The SDL2 C library
- git
- gcc

## Installation 
Clone the repository :
```bash
git clone https://github.com/matheothomas/sea-battle
```

Move into the folder :
```bash
cd sea-battle
```

Compile the code :
```bash
make
```
An executable named `seaBattle` is created.

## How to play

### On the host/server machine
Execute `seaBattle` :
```bash
./seaBattle server
```

### On the client machine
Execute `seaBattle` :
```bash
./seaBattle client IP_ADDRESS
```
And replace `IP_ADDRESS` with the IP address of the host machine.

### First part : ship configuration
For each ship, a direction is chosen using the arrows, then a case is selected in the lower map.

### Second part : play
A case is chosen in the upper map to attack the other player.
- If there is a ship, the case turns blue.
- If there isn't, a cross is shown.

The attacks of the other player are shown in the lower map.

The game is won when a player sunk all ships of the opponent.


## Additional info
- The port 8080 is used for the socket.
- To test the program, `preconfig` can be added as a supplementary parameter to load a ship configuration.
