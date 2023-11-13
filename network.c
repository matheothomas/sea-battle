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

netParams mainNetworkServ(){
	netParams p;
	
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
	if(setsockopt(p.server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))){
		perror("setsockopt\n");
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

netParams mainNetworkClient(char IPADDR[]){
	netParams p;
		
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
