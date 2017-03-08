// need to play with some stuff

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// http://stackoverflow.com/questions/8824057/pointer-to-string-array-in-c

// typedef necessary here?
struct connected_users{

	int num_users;
	char (*ip_addresses[10])[15];
	//char (*this_ip[15]);
};

int main(){

	struct connected_users *userPtr, users;
    userPtr = &users;   

    userPtr->num_users = 7;
    strcpy(*(userPtr->ip_addresses[0]),"127.0.0.1");

    printf("%d\n", userPtr->num_users);
    printf("%s\n", *(userPtr->ip_addresses[0]));

    return 0;
}
