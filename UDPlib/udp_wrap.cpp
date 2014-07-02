#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <iostream>
#include "strings.h"
#include "string.h"

#define MAX_RECV_LENGTH 512
#define MAX_SEND_LENGTH 512
#define MAX_BUFFER_LENGTH 4086
#define MAX_MESSAGES 12

struct sockaddr_in server_addr, client_addr;
int sock;

/*
   Initializes a socket for the Receive process to listen to for
   incoming messages.

*/
int socketInit(int sockfd, int type, int domain, int protocol,
               int portno){
   if((sockfd = socket(type, domain, protocol))==-1){
      perror("Socket\n");
      exit(1);
   }
   
   server_addr.sin_family = type;
   server_addr.sin_port = htons(portno);
   server_addr.sin_addr.s_addr = INADDR_ANY;
   //initialize memory
   bzero(&(server_addr.sin_zero),8);
   return sockfd;
}

/*
   Initializes destination address, port and communication type
*/
void clientInit(int type, int portno, char* IPaddr){
   client_addr.sin_family = type;
   client_addr.sin_port = htons(portno);
   inet_pton(type, IPaddr, &(client_addr.sin_addr));
   bzero(&(client_addr.sin_zero),8);
}

/*
   User Input Function
   
   Allows the user to pass messages onto the outqueue to be sent 
   by Send as soon as possible. This allows the user to move onto 
   other tasks without having to worry about waiting for sendto

*/
int userWrite(void* message, int size){
   int bytes;
   bytes = sendto(sock, message, size,0 ,
                  (struct sockaddr*)&client_addr, 
                  sizeof(struct sockaddr));
   return bytes;
}

/*
   User Input Function
   
   Checks socket for data from communication partner
*/
int userRead(void* buffer, int size){
   int bytes;
   bytes = recvfrom(sock, buffer, size, 0, 
                   (struct sockaddr*)&server_addr,
                   (socklen_t*)sizeof(struct sockaddr));
   return bytes;
}

void commInit(char* IPaddr, int dest_portnumber, int portno){
   
   //Initialize sock
   sock = socketInit(sock, AF_INET, SOCK_DGRAM, 0, portno);
   //Initialize Destination
   clientInit(AF_INET, dest_portnumber, IPaddr);
   
   //Bind socket to localhost
   if(bind(sock, (struct sockaddr*)&server_addr, 
           sizeof(struct sockaddr)) == -1){
      perror("Unable to Bind\n");
      exit(1);
   }
   
}

   

