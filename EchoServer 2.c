#define char16_t UINT16_T //shenanigans with the compiler

#include "mex.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

char str[100];
pthread_mutex_t print_mutex;

void *printFun(void *vargp){

    pthread_mutex_lock(&print_mutex);
    
    mexPrintf("Starting...");
    
    while(1){
        if(strlen(str[0]) != 0){
            mexPrintf("Echoing back - %s\n", str);
        }
    }

    pthread_mutex_unlock(&print_mutex);
    
    return NULL;
    
}
 
// A normal C function that is executed as a thread when its name
// is specified in pthread_create()
void *myThreadFun(void *vargp)
{
//     char str[100];
    bool done = 0;
    int listen_fd, comm_fd;
    struct sockaddr_in servaddr;
    
    listen_fd = socket(AF_INET, SOCK_STREAM,0);
    bzero(&servaddr, sizeof(servaddr));
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(22000);

    
    //mexPrintf("Connecting to port %d\n", servaddr.sin_port);
    
    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    
    //mexPrintf("Listening on port %d\n", servaddr.sin_port);
    
    listen(listen_fd, 10);
    
    comm_fd = accept(listen_fd, (struct sockaddr *) NULL, NULL);
    // mexPrintf("Connected\n");

    while(!done){
        bzero(str, 100);
        read(comm_fd, str, 100);
        // mexPrintf("Echoing back - %s\n", str);
        write(comm_fd, str, strlen(str)+1);
        if(str[0]==';'){
            done = 1;
        }
    }

//     
//     while(1)
//     {
//         bzero(str, 100);
//         read(comm_fd, str, 100);
//         mexPrintf("Echoing back - %s\n", str);
//         write(comm_fd, str, strlen(str)+1);
//     }
    return NULL;
}

void mexFunction( int nlhs, mxArray *plhs[],
              int nrhs, const mxArray *prhs[])
{
    
//     mexPrintf("Starting...");
    
    pthread_t tid[2];

    pthread_create(&tid[0], NULL, myThreadFun,NULL);
    pthread_create(&tid[1], NULL, printFun,NULL);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    
}