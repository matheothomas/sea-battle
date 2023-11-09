/* name : server.c
 * author : matheo thomas
 * date : 09-11-23
 */

#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
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
	char *hello = "Hello from server";
	
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
	printf("Hello message sent\n");
	return p;
}



int main(void){
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
	
	
	return 0;
}

