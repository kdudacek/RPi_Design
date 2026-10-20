/* ------------------------------------------------------------------------------------------ */
/*                                                                                            */
/*                                                                                            */
/*                               dgram_server.c                                               */
/*                                                                                            */
/*      Procedures to create server socket, listen, accept and close. Uses datagram.          */
/*                                                                                            */
/* ------------------------------------------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include    "config.h"
#include    "commands.h"
#include    "dgram_server.h"
#include    "trace.h"

/* ========================================================================================== */

/* ------------ module local data ----------------------------------------------------------- */

struct sockaddr_in      serv_addr;
struct sockaddr_in      cli_addr;

int         sockfd;             /* server socket */
int         newsockfd;          /* socket for client */

int         cli_len;            /* size of client address */
int         msg_counter;        /* for display output only */

/* ============ dgram_server_start =========================================================== */

/* Open socket, accept connection and read message. Leave socket open, suppose it will be     */
/* closed after sending response.                                                             */

int dgram_server_start(void) {

    int portno;
    int  n;
    
    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
   
    if (sockfd < 0) {
        trace_f("    ERROR opening socket\n");
        printf("    ERROR opening socket\n");
        return(1);
    }
   
    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = SERVICE_PORT;
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    
    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        trace_f("    ERROR on binding\n");
        printf("    ERROR on binding\n");
        return(1);
    }
    
    msg_counter = 0;
          
    return(0);
    
}

/* ============ dgram_server_recvfrom ======================================================= */

/* Wait for incomming message.                                                                */

int dgram_server_recvfrom(uint8_t *buffer_ptr, int buffer_size) {

    int bytes_recv;     /* number of received bytes */

    cli_len = sizeof(cli_addr);

    trace_f("     waiting for recvfrom\n");
    printf("     waiting for recvfrom\n");
    
    bytes_recv = recvfrom(sockfd, buffer_ptr, buffer_size, 0, (struct sockaddr *) &cli_addr, &cli_len);
    if(-1 == bytes_recv) {
        /* some error */
        trace_f("     error in recvfrom\n");
        printf("     error in recvfrom\n");
    
        close(sockfd);
    }
    else {
        /* recvfrom OK */
        trace_fis("     received %i bytes from \n", bytes_recv, inet_ntoa(cli_addr.sin_addr));
        printf("     %i: received %i bytes from \n", msg_counter, bytes_recv, inet_ntoa(cli_addr.sin_addr));
    }    
        
    msg_counter += 1;
    
    return(bytes_recv);
    
}

/* ============ dgram_response_send ========================================================== */

/* Send response and close socket. Suppose socket is open by dgram_server_start.               */

int dgram_response_send(uint8_t *s_response, int respose_size) {

    int result_code;
    
    result_code = sendto(sockfd, s_response, respose_size, 0, (struct sockaddr *) &cli_addr, cli_len);
    if(-1 == result_code) {
        /* some error */
        trace_fi("     error in sendto: errno =  %i\n", errno);
        printf("      error in sendto: errno =  %i\n", errno);
    }        
    
    return(0);
    
}


/* ============ sockets_close =============================================================== */

/* Close both sockets.                                                                        */

int sockets_close(void) {

    if(close(newsockfd) != 0) {
        trace_f("    error closing newsock\n");
    }
    
    if(close(sockfd) != 0) {
        trace_f("    error closing sockfd\n");
    }

    trace_f("     sockets closed\n");

    return(0);
    
}


/* ============ END ========================================================================= */

