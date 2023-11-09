/* name : network.h
 * author : matheo thomas
 * date : 09-11-23
 */

#ifndef network_h 
#define network_h

// Struct definitions
typedef struct netParamsServ {
	int server_fd;
	int new_socket;
	ssize_t valread;
	struct sockaddr_in address;
} netParamsServ;

typedef struct netParamsClient {
	int status;
	int valread;
	int client_fd;
	struct sockaddr_in serv_addr;
} netParamsClient;


// Functions definitions


#endif

