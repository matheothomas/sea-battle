/* name : network.c
 * author : matheo thomas
 * date : 09-11-23
 */

#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include"network.h"

#define PORT 8080

netParamsServ mainNetworkServ(){
	netParamsServ p;
	
	int opt = 1;
	socklen_t addrlen = sizeof(p.address);
	char buffer[1024] = { 0 };
	char *hello = "Connected to server.\n";
	
	// Creating socket file descriptor
	if((p.server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket failed\n");
		exit(EXIT_FAILURE);
	}
	
	// Forcefully attaching socket to the port 8080
	if(setsockopt(p.server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
		perror("sesockopt\n");
		exit(EXIT_FAILURE);
	}
	p.address.sin_family = AF_INET;
	p.address.sin_addr.s_addr = INADDR_ANY;
	p.address.sin_port = htons(PORT);
	
	// Forcefully attaching socket to the port 8080
	if(bind(p.server_fd, (struct sockaddr*)&p.address, sizeof(p.address)) < 0){
		perror("bind failed\n");
		exit(EXIT_FAILURE);
	}
	if(listen(p.server_fd, 3) < 0){
		perror("listen\n");
		exit(EXIT_FAILURE);
	}
	if((p.new_socket = accept(p.server_fd, (struct sockaddr*)&p.address, &addrlen)) < 0){
		perror("accept\n");
		exit(EXIT_FAILURE);
	}
	
	p.valread = read(p.new_socket, buffer, 1024 -1); // substract 1 for the null terminator at the end
	printf("%s\n", buffer);
	send(p.new_socket, hello, strlen(hello), 0);
	return p;
}




netParamsClient mainNetworkClient(char IPADDR[]){
	netParamsClient p;
		
	char *hello = "Connected to client.\n";
	char buffer[1024] = { 0 };
	
	if((p.client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("Socket creation error \n");
		exit(EXIT_FAILURE);
	}
	
	p.serv_addr.sin_family = AF_INET;
	p.serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, IPADDR, &p.serv_addr.sin_addr) <= 0){
		printf("Invalid address/Address not supported\n");
		exit(EXIT_FAILURE);
	}
	
	if((p.status = connect(p.client_fd, (struct sockaddr*)&p.serv_addr, sizeof(p.serv_addr))) < 0){
		printf("Connection failed\n");
		exit(EXIT_FAILURE);
	}
	
	send(p.client_fd, hello, strlen(hello), 0);
	p.valread = read(p.client_fd, buffer, 1024 -1);
	printf("%s\n", buffer);
	return p;
}



int main(int argc, char *argv[]){
	if(argc >= 2){
		if(strcmp(argv[1], "server") == 0){
			netParamsServ p = mainNetworkServ();
	
			char buffer[1024] = { 0 };
			char s[1024];
			while(strcmp(buffer, "end") != 0){
				memset(buffer, 0, sizeof(buffer));
		
			printf("Enter message : ");
				scanf("%s", s);
		
				send(p.new_socket, s, strlen(s), 0);
		
				p.valread = read(p.new_socket, buffer, 1024 -1);
				printf("%s\n", buffer);
			}
			// closing the connected socket
			close(p.new_socket);
			// closing the listening socket
			close(p.server_fd);
		} else if(strcmp(argv[1], "client") == 0){
			char *IPADDR = argv[2];
			printf("ip address : %s\n", IPADDR);
			netParamsClient p = mainNetworkClient(IPADDR);

			char buffer[1024] = { 0 };
			char s[1024];
			while(strcmp(buffer, "end") != 0){
				memset(buffer, 0, sizeof(buffer));
		
				printf("Enter message : ");
				scanf("%s", s);
		
				send(p.client_fd, s, strlen(s), 0);
		
				p.valread = read(p.client_fd, buffer, 1024-1);
				printf("%s\n", buffer);
			}
	
			// Closing the connected socket
			close(p.client_fd);	
		} else {
			printf("Wrong parameter entered, enter server or client.\n");
		}
	} else {
		printf("Type \"./network server\" or \"./network client SERVER_IP_ADDRESS\".\n");
	}
	
	return 0;
}

