/* name : network.h
 * author : matheo thomas
 * date : 09-11-23
 */

#ifndef network_h 
#define network_h

// Struct definitions
typedef struct netParams {
	int server_fd;
	int client_fd;
	int status;
	int new_socket;
	int valread;
	struct sockaddr_in address;
	struct sockaddr_in serv_addr;
} netParams;


// Functions definitions

// Defines and configures the socket for the server.
netParams mainNetworkServ();

// Defines and configures the socket for the client.
netParams mainNetworkClient(char IPADDR[]);

#endif

