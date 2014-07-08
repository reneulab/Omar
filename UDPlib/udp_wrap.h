
/*

   udp_wrap.h
   Simple Two Way UDP Communication Implementation
   
   Author: Omar Medjaouri
   Last Updated: July 7th, 2014
   
   This is a simple implementation of two way UDP communication.
   
   The user must first call commInit, which will initialize a 
   socket on localhost and a user provided port. It will also
   define an address struct with information like destination 
   IP address and destination port number for the rest of the 
   program to use when sending. The commInit function will
   printf an error to the command line if there was an issue
   with the socket creation. The other two functions, userWrite
   and userRead, allow the user to send and receive data from
   someone else using the library, or any implementation that 
   uses a UDP socket. 

   The write function takes a user provided array and sends it 
   to the destination address provided by the user when they 
   call commInit. It will immediately call sendto and it will
   return the number of bytes sent. If it returns a -1, it
   means that there was some error in the communication.

   Similarly, the read function reads from localhost on a user
   provided port, writes to the user provided buffer, and 
   returns the number of bytes read. In the case that there is
   nothing on the buffer, the function does not write anything
   to the user provided array and returns a -1.

   The last two functions, clientInit and socketInit, are not
   needed by the user, and will be called by commInit.

*/

#ifndef UDP_WRAP_H
#define UDP_WRAP_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>


/* 
   USER MAY ADJUST THESE VALUES FOR THEIR OWN PERSONAL USE
*/
#define MAX_RECV_LENGTH 512
#define MAX_SEND_LENGTH 512
#define MAX_BUFFER_LENGTH 4086
#define MAX_MESSAGES 8


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

#endif /*UDP_WRAP_H*/
