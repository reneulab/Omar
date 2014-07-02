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


/*

   FOR LIBRARY USE, NOT NEEDED BY USER
   
   Initializes a socket to listen to for incoming messages
   
   Inputs:
      int sockfd = uninitialized integer
      int type = AF_INET (Iv4)
      int domain = SOCK_DGRAM, SOCK_STREAM, etc.
      int protocol = 0
      int portno = port number of the socket
   Outputs:
      Returns the id of a socket

*/
int socketInit(int sockfd, int type, int domain, int protocol,
               int portno);

/*

   FOR LIBRARY USE, NOT NEEDED BY USER

   Initializes a sockaddr variable with information about destination
   
   Inputs:
      int type = AF_INET(Iv4)
      int portno = port number of the socket at destination
      char* IPaddr = Destination IP address

*/
void clientInit(int type, int portno, char* IPaddr);

/*

   FOR USE BY THE USER
   
   Calls sendto to send a user provided message. User must also 
   provide size of message to be sent. The function returns the 
   number of bytes sent or a -1 if error

   Inputs:
      char* message =  the message to be sent
      int size = size of the message sent
   Outputs:
      Returns number of bytes put on queue or -1 if error in send

*/
int userWrite(void* message, int size);

/*

   FOR USE BY THE USER

   Calls recvfrom and checks for a received message. User provides
   the buffer for the message to be stored in and the size of the 
   buffer. Function returns -1 if no messages, otherwise returns
   the number of bytes of the message
   
   Inputs:
      char* buffer = buffer for the function to write the message
   Ouputs:
      Returns -1 if no messages, otherwise returns number of bytes
      in the message.

*/
int userRead(void* buffer, int size);

/*

   FOR USE BY THE USER

   Initializes the library by creating the socket for the library
   to listen on as well as taking data like destination address
   and port and making that information usable by library functions.

   Inputs:
      char* IPaddr = Destination IP address
      int destination_portnumber = Port number of destination
      int portno = Port number the library will listen on.

*/
void commInit(char* IPaddr, int dest_portnumber, int portno);

