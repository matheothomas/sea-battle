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

//typedef struct netParamsServ {
//	int server_fd;
//	int new_socket;
//	struct sockaddr_in address;
//} netParamsServ;

//typedef struct netParamsClient {
//	int client_fd;
//	int status;
//	int valread;
//	struct sockaddr_in serv_addr;
//} netParamsClient;


// Functions definitions
netParams mainNetworkServ();

netParams mainNetworkClient(char IPADDR[]);

#endif

