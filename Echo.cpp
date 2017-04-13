#define char16_t UINT16_T //shenanigans with the compiler

#include "mex.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

using namespace std;

#define MSGLEN 500

class mysocket{
private:
    struct sockaddr_in servaddr;    // ipv4 socket info
    int fd;

public:
    void bind(int fd,(struct sockaddr *) servaddr, size_t size);
    void mysocket();    // initialize servaddr etc
    void accept(int* listen_fd, (struct sockaddr *) NULL, NULL);
    void read(comm_fd, str, MSGLEN);
    void write(comm_fd, str, strlen(str)+1);
};


// void echo(){
   
//     char str[MSGLEN];
//     int listen_fd, comm_fd;
//     struct sockaddr_in servaddr;
    
//     listen_fd = socket(AF_INET, SOCK_STREAM,0);
//     bzero(&servaddr, sizeof(servaddr));
    
//     servaddr.sin_family = AF_INET;
//     servaddr.sin_addr.s_addr = htons(INADDR_ANY);
//     servaddr.sin_port = htons(22000);
    
//     bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    
//     mexPrintf("Listening on port %d\n", servaddr.sin_port);
    
//     listen(listen_fd, 10);
    
//     comm_fd = accept(listen_fd, (struct sockaddr *) NULL, NULL);
//     mexPrintf("Connected\n");
    
//     while(1)
//     {
//         bzero(str, MSGLEN);
//         read(comm_fd, str, MSGLEN);
//         mexPrintf("Echoing back - %s\n", str);
//         write(comm_fd, str, strlen(str)+1);
//     }
    
// }

// void mexFunction(int nlhs, mxArray *plhs[],
//                  int nrhs, const mxArray *prhs[])
// {
//     mexPrintf("Starting\n");
   
//     echo();
    
//     mexPrintf("Finishing\n");
// }