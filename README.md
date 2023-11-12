# sea-battle

seaBattle is a game of sea battle coded in C, with the ability of playing it on two different machines on a same local network.

This game helped me understand sockets in C, and has been a great project to make from scratch.

## Roadmap
- [x] Build the core of the game.
- [x] Add local multiplayer mode.
- [ ] Build a graphical interface with SDL2.


## How to play

First, compile the code :
```bash
make
```
It will create a `prog` executable.

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
