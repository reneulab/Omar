
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <iostream>
#include <fstream>
#include "udp_wrap.h"

#define TRIALNUMBER 10000
#define MESSAGESIZE 500
int addr_len;
char recv_data[MESSAGESIZE];
int send_data[MESSAGESIZE];
float trial[TRIALNUMBER];
char address[] = "146.6.84.201";

int main(){
   int sock, sockout, quit, portno, portno_other, i, sent, bytes;
   float time;
   float sum;

   commInit(address, 5121, 5000);

   for(int j = 0; j<(MESSAGESIZE-1); j++){
      send_data[j] = 1;  
   }   
   send_data[MESSAGESIZE-1] = '\0';
   addr_len = sizeof(struct sockaddr); 
   //TIMING CODE
   //Clock init
   i = 0;
   clock_t diff;
   clock_t start;
   while(i<TRIALNUMBER){
      start = clock();
      //snprintf(send_data, 100, "%f", out);
      //printf("Prepare to send\n");
      sent = userWrite(send_data, MESSAGESIZE);
      //printf("Sent Bytes: %d\n", sent);
      bytes = userRead(recv_data, MESSAGESIZE);
      recv_data[bytes] = '\0';
      //printf("Recevied: %s\n", recv_data);
      //Busy wait for received data
      while(recv_data[0] != 'h'){
         bytes = userRead(recv_data, MESSAGESIZE);
         recv_data[bytes] = '\0';
        // printf("Received: %s\n", recv_data);
      }
      
      //printf("Recevied: %s\n", recv_data);
      //MEASURE DIFFERENCE FROM START OF PROCESS END.
      diff = clock() - start;
      float time = diff*1000000/CLOCKS_PER_SEC;
      
      trial[i] = time;
      //printf("Time to Send/Receive: %d msecs to send %d bytes\n", msec, bytes);
      //fprintf(outfile, "Time to Send/Receive: %d msecs to send %d bytes\n", msec, bytes);
      recv_data[0] = '2';
      //recv_data[1] = '\0';
      //printf("Received cleared to: %s\n", recv_data);
      i++;
   }
   sum = 0;
   for(int x = 0; x < TRIALNUMBER; x++){
      sum += trial[x];
      //printf("Trial time: %f secs\n", trial[x]);
   }
   printf("Bytes Sent: %d\n", MESSAGESIZE);
   printf("Total time: %f seconds\n", sum/1000000);
   sum = sum/TRIALNUMBER;
   printf("Avg time: %f msecs\n", sum);
}
