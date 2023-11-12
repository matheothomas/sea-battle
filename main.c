/* name : main.c
 * author : matheo thomas
 * date : 10-11-23
 */

#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include"network.h"
#include"seaBattle.h"


int main(int argc, char *argv[]){
	sea **s1ships   = initSea();
	sea **s1touches = initSea();
	sea **s2ships   = initSea();
	sea **s2touches = initSea();
	//loadPreConfig(s1ships);
	//loadPreConfig(s2ships);
		
	
	if(argc >= 2){
		if(strcmp(argv[1], "server") == 0){
			netParams p = mainNetworkServ();
			
			placeShips(s1ships, s1touches);
	
			char buffer1[1024] = { 0 };
			char s1[2];
			char posSent1[2];
			
			int c1, c2, c3, c4;
			int isShipTouched;
			int gameStatus;
			while(strcmp(buffer1, "zz") != 0){
				memset(buffer1, 0, sizeof(buffer1));
				memset(s1, 0, sizeof(s1));
				memset(posSent1, 0, sizeof(posSent1));
				
				showSea(s1ships, s1touches);
				
				// Sending coordinates
				printf("Enter first coordinate : ");
				scanf("%c%*c", &s1[0]);
				printf("Enter second coordinate : ");
				scanf("%c%*c", &s1[1]);
				send(p.new_socket, s1, strlen(s1), 0);
				
				// Receiving coordinates
				//printf("---Receiving coordinates---\n");
				p.valread = read(p.new_socket, buffer1, 1024-1);
				//printf("buffer1 : %s\n", buffer1);
				buffer1[2] = '\0';
				c1 = atoi(buffer1)/10;
				c2 = atoi(&buffer1[1]);
				memset(buffer1, 0, sizeof(buffer1));
				isShipTouched = received(s1ships, c1, c2);
				if(isShipTouched == 2){
					gameStatus = victoire(s1ships[c1][c2].isShip);
				} else {
					gameStatus = 0;
				}
				//printf("gameStatus : %d\n", gameStatus);
				
				// Sending results
				//printf("---Sending results---\n");
				posSent1[0] = isShipTouched + '0';
				posSent1[1] = gameStatus + '0';
				sleep(1);	
				send(p.new_socket, posSent1, strlen(posSent1), 0);
				if(gameStatus == 2){
					printf("Perdu...\n");
					break;
				}	

				// Applying results
				//printf("---Applying results---\n");
				p.valread = read(p.new_socket, buffer1, 1024-1);
				//printf("buffer1 : %s\n", buffer1);
				s1[2] = '\0';
				c1 = atoi(&s1[0])/10;
				c2 = atoi(&s1[1]);
				c3 = atoi(&buffer1[0])/10;
				c4 = atoi(&buffer1[1]);
				//printf("c3 : %d\n", c3);
				//printf("c4 : %d\n", c4);
				sent(s1touches, c1, c2, c3); //Filling the upper map
				if(c4 == 2){
					printf("Gagné !\n");
					break;
				} else if(c4 == 1){
					printf("Coulé !\n");
				}	
				
				//printf("buffer1 : %s\n", buffer1);
			}
			showSea(s1ships, s1touches);
			
			// closing the connected socket
			close(p.new_socket);
			// closing the listening socket
			close(p.server_fd);
		
		} else if(strcmp(argv[1], "client") == 0){
			char *IPADDR = argv[2];
			printf("ip address : %s\n", IPADDR);
			netParams p = mainNetworkClient(IPADDR);
			
			placeShips(s2ships, s2touches);

			char buffer2[1024] = { 0 };
			char s2[2];
			char posSent2[2];
			int c1, c2, c3, c4;
			int isShipTouched;
			int gameStatus;
			while(strcmp(buffer2, "zz") != 0){
				memset(buffer2, 0, sizeof(buffer2));
				memset(s2, 0, sizeof(s2));
				memset(posSent2, 0, sizeof(posSent2));
				
				showSea(s2ships, s2touches);
		
				// Sending coordinates
				printf("Enter first coordinate : ");
				scanf("%c%*c", &s2[0]);
				printf("Enter second coordinate : ");
				scanf("%c%*c", &s2[1]);	
				send(p.client_fd, s2, strlen(s2), 0);
		
				// Receiving coordinates
				//printf("---Receiving coordinates---\n");
				p.valread = read(p.client_fd, buffer2, 1024-1);
				//printf("buffer2 : %s\n", buffer2);
				buffer2[2] = '\0';
				c1 = atoi(buffer2)/10;
				c2 = atoi(&buffer2[1]);
				memset(buffer2, 0, sizeof(buffer2));
				isShipTouched = received(s2ships, c1, c2);
				if(isShipTouched == 2){
					gameStatus = victoire(s2ships[c1][c2].isShip);
				} else {
					gameStatus = 0;
				}
				//printf("gameStatus : %d\n", gameStatus);
				
				// Sending results
				//printf("---Sending results---\n");
				posSent2[0] = isShipTouched + '0';
				posSent2[1] = gameStatus + '0';
				sleep(1);	
				send(p.client_fd, posSent2, strlen(posSent2), 0);
				if(gameStatus == 2){
					printf("Perdu...\n");
					break;
				}	
				
				// Applying results
				//printf("---Applying results---\n");
				p.valread = read(p.client_fd, buffer2, 1024-1);
				//printf("buffer2 : %s\n", buffer2);
				s2[2] = '\0';
				c1 = atoi(&s2[0])/10;
				c2 = atoi(&s2[1]);
				c3 = atoi(&buffer2[0])/10;
				c4 = atoi(&buffer2[1]);
				//printf("c3 : %d\n", c3);
				//printf("c4 : %d\n", c4);
				sent(s2touches, c1, c2, c3);
				if(c4 == 2){
					printf("Gagné !\n");
					break;
				} else if(c4 == 1){
					printf("Coulé !\n");
				}	
				
				//printf("buffer2 : %s\n", buffer2);
			}
			showSea(s2ships, s2touches);
			// Closing the connected socket
			close(p.client_fd);	
		
		} else {
			printf("Wrong parameter entered, enter server or client.\n");
		}
	
	} else {
		printf("Type \"./prog server\" or \"./prog client SERVER_IP_ADDRESS\".\n");
	}
	
	
	freeSea(s1ships);
	freeSea(s1touches);
	freeSea(s2ships);
	freeSea(s2touches);
	
	return 0;
}

