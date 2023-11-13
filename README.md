# sea-battle

**seaBattle** is a game of sea battle developed in C, with the ability of playing it on two different machines on a same local network.

This game helped me understand sockets in C, and has been a great project to make from scratch.

## Roadmap
- [x] Build the core of the game.
- [x] Add local multiplayer mode.
- [x] Build a graphical interface with SDL2.
- [ ] Add a solo mode against a bot.

## Installation 
Clone the repository :
```bash
git clone https://github.com/matheothomas/sea-battle
```

Compile the code :
```bash
make
```
An executable named `prog` is created.

## How to play

### On the host/server machine
Execute `prog` :
```bash
./prog server
```

### On the client machine
Execute `prog` :
```bash
./prog client IP_ADDRESS
```
And replace `IP_ADDRESS` with the IP address of the host machine.


## Additional info
- The port 8080 is used for the socket.
- To test the program, `preconfig` can be added as a supplementary parameter to load a ship configuration.
