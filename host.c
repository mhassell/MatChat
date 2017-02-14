#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// the host is in pure C without a Mex interface.

#define NCHARS   500
#define MAX_USERS 10

typedef struct connected_users{

    int n_users;
    str *user_addresses[MAX_USERS];

};

void echo(int PORTNUM){
   
    char str[NCHARS];
    int listen_fd, comm_fd;
    struct sockaddr_in servaddr;
    
    listen_fd = socket(AF_INET, SOCK_STREAM,0);
    bzero(&servaddr, sizeof(servaddr));
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(PORTNUM);

    printf("Listening on port %d\n", PORTNUM);
    
    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    
    // printf("Listening\n");
    
    listen(listen_fd, MAX_USERS);
    
    comm_fd = accept(listen_fd, (struct sockaddr *) NULL, NULL);
    printf("Connected\n");
    
    while(1)
    {
        bzero(str, NCHARS);
        read(comm_fd, str, NCHARS);
        if(strcmp(str, "")){
       		printf("Echoing back - %s\n", str);
        	write(comm_fd, str, strlen(str)+1);
        }
    }
    
}

int main(int argc, char* argv[]){

	int PORTNUM;

    struct


	if(argc == 2){
		PORTNUM =  atoi(argv[1]);
	}
	else{
		PORTNUM = 22000;
	}

	echo(PORTNUM);

}