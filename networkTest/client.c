/* name : client.c
 * author : matheo thomas
 * date : 09-11-23
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include"network.h"


#define PORT 8080
#define IPADDR "127.0.0.1"

netParamsClient mainNetworkClient(){
	netParamsClient p;
		
	char *hello = "Hello from client\n";
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
	printf("Hello message sent\n");
	p.valread = read(p.client_fd, buffer, 1024 -1);
	printf("%s\n", buffer);
	return p;
}


int main(void){
	netParamsClient p = mainNetworkClient();
	
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
	
	
	
	return 0;
}

