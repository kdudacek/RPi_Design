/* ------------------------------------------------------------------------------------------ */
/*                                                                                            */
/*                                                                                            */
/*                                dgram_client.c                                              */
/*                                                                                            */
/*                                                                                            */
/*      Procedures to create client socket, listen, open, write, read and close.              */
/*                                                                                            */
/* ------------------------------------------------------------------------------------------ */

/* ========================================================================================== */

#include    <stdio.h>
#include    <stdlib.h>
#include    <sys/types.h>
#include    <errno.h>

#include    <netdb.h>
#include    <netinet/in.h>
#include    <sys/socket.h>
#include    <arpa/inet.h>
#include    <string.h>
#include    <unistd.h>

#include    "config.h"
#include    "dgram_client.h"
#include    "trace.h"

/* ------------ module local data ----------------------------------------------------------- */

int         sockfd;                         /* client socket */
struct      sockaddr_in     client_addr;
struct      sockaddr_in     serv_addr;

int         msg_counter;                    /* for general purpose */

/* ============ dgram_client_start ========================================================== */

/* Open socket, accept connection and read message. Leave socket open, suppose it will be     */
/* closed after sending response.                                                             */

int dgram_client_start(void) {

    int     portno;
    int     n;
    struct  timeval      sock_timeout;
        
    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);   
   
    if (sockfd < 0) {
        trace_f("    ERROR opening socket\n");
        printf("    ERROR opening socket\n");
        return(1);
    }
   
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS);    /* IP convert string to number */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVICE_PORT);
    
//    addr_family = AF_INET;
//    ip_protocol = IPPROTO_IP;

    /* Initialize socket structure */
    bzero((char *) &client_addr, sizeof(client_addr));
    portno = SERVICE_PORT;
    
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = INADDR_ANY;
    client_addr.sin_port = htons(portno);
    
    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &client_addr, sizeof(client_addr)) < 0) {
        trace_f("    ERROR in binding\n");
        printf("    ERROR in binding\n");
        return(1);
    }
    
    /* timeout for sendidng & receiving */
    sock_timeout.tv_sec = 10;
    sock_timeout.tv_usec = 0;
    
    if(-1 == setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &sock_timeout, sizeof(sock_timeout)) ) {
        trace_f("ERROR in setsockopt SO_SNDTIMEO\n");
    }                       

    if(-1 == setsockopt(sockfd, SOL_SOCKET,SO_RCVTIMEO, &sock_timeout, sizeof(sock_timeout)) ) {
        trace_f("ERROR in setsockopt SO_RCVTIMEO\n");
    }
                           
    msg_counter = 0;
          
    return(0);
    
}

/* ============ command_dgram_send =========================================================== */

/* Send response and close socket. Suppose socket is open by dgram_server_start.               */

int command_dgram_send(uint8_t *cmd_buffer, int cmd_buffer_size) {

    int result_code;
    
    result_code = sendto(sockfd, cmd_buffer, cmd_buffer_size, 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if(-1 == result_code) {
    
        if(EAGAIN == errno) {
            printf("  sendto timeouted\n");
            return(UDP_TIMEOUTED);
        }
        else {
        /* some error */
            trace_fi("     ERROR in sendto: errno =  %i\n", errno);
            printf("      ERROR in sendto: errno =  %i\n", errno);
            return(UDP_ERROR);
        }        
    } 
    else {       
        return(UDP_OK);
    }
    
}

/* ============ server_response_read ======================================================= */

int server_response_read(unsigned char *buffer, int msg_length_max) {

    int     n;  

    bzero(buffer, msg_length_max);
      
    /* read server response */
    n = recvfrom(sockfd, buffer, msg_length_max, 0, NULL, 0);
   
    if(-1 == n) {
        if(EAGAIN == errno) {
            printf("  recvfrom timeouted\n");
            return(UDP_TIMEOUTED);
        }
        else {
        /* some error */
            trace_fi("     ERROR in recvfrom: errno =  %i\n", errno);
            printf("      ERROR in recvfrom: errno =  %i\n", errno);
            return(UDP_ERROR);
        }
        
    } 
    else {       
        return(n);
    }
      
}

/* ============ END ========================================================================= */
