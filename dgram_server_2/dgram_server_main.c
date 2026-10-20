/* ------------------------------------------------------------------------------------------ */
/*                                                                                            */
/*                                                                                            */
/*                               dgram_server_main.c                                           */
/*                                                                                            */
/*      Program to control LED lighting according to the command received via socket.         */
/*                                                                                            */
/* ------------------------------------------------------------------------------------------ */

#include    <time.h>
#include    <sys/time.h>            /* settimeofday */
#include    <unistd.h>
#include    <sys/types.h>
#include    <stdio.h>
#include    <stdlib.h>              /* exit() */
#include    <stdint.h>
#include    <fcntl.h>               /* O_RDWR */

#include    "commands.h"
#include    "config.h"
#include    "dgram_server_main.h"
#include    "dgram_server.h"
#include    "gpio_utils.h"
#include    "trace.h"

/* ========================================================================================== */

/* ------------ module local data ----------------------------------------------------------- */

uint8_t         rcv_buffer[RCV_BUFFER_SIZE];
uint8_t         response_buffer[RESPONSE_BUFFER_SIZE];

/* ========================================================================================== */

/* ============ main ======================================================================== */

int main(void) {

int             rcv_bufsize;
int             response_bufsize;
time_t          now;
time_t          xnow;
struct  tm      exp_now;
struct  timeval tm_xnow;
uint8_t         tmp;
int             rv;
uint8_t         rv2;
int             n_bytes;

    /* open trace file */
    trace_init(DGRAM_TRACE_FN);

    now = time(NULL);

    GPIO_export_pin(RED_LED);
    GPIO_export_pin(GREEN_LED);
    GPIO_owc_pin(RED_LED, 0);       /* LED off */
    GPIO_owc_pin(GREEN_LED, 0);     /* LED off */

    trace_f("\n----------------------------------------------\n");
    trace_fs("dgram_server_main started at %s", ctime(&now));
    trace_f("\n----------------------------------------------\n\n");

        now = time(NULL);
        trace_fs("dgram_server socket started at %s", ctime(&now));
        
        /* create and bind server socket */
        rv = dgram_server_start();
        if(rv == 0) {
            trace_f("returned OK\n");
        }
        else {
            trace_f("returned error\n");
        }
        
    while(1) {
                
        /* receive from socket */
        rcv_bufsize = RCV_BUFFER_SIZE;
        n_bytes = dgram_server_recvfrom(rcv_buffer, rcv_bufsize);

        if(-1 == n_bytes) {
            trace_f("dgram_server_recvfrom returned error\n");
        }
        else {

            /* process the received request */
            rv2 = client_request_processing(rcv_buffer, n_bytes);
            
            trace_f("sending response\n");
            
            response_bufsize = RESPONSE_BUFFER_SIZE;
            response_buffer[0] = rv2;
            
            /* send response and close */        
            rv = dgram_response_send(response_buffer, response_bufsize);     /* rv2 = COMMAND_EXECUTED or UNKNOWN_COMMAND */

            if(rv == 0) {
                trace_f("response sent OK\n");
            }
            else {
                trace_f("response sent with error\n");
            }
                   
            trace_f("-----------\n");        
        }
        
    }           /* end of while(1) */

    return(0);      
}

/* ============ client_request_processing =================================================== */

/* Decode command received from the socket and executing it.                                  */

uint8_t client_request_processing(uint8_t *buffer, int n_bytes) {

int     result;
int     cmd_pointer;        /* pointer to received commands buffer */

    result = COMMAND_EXECUTED;
    
    cmd_pointer = 0;
    
    while(  (CMD_END != (rcv_buffer[cmd_pointer])   /* regular end of data */
         && (n_bytes > cmd_pointer)                 /* if CMD_END is missing */
         && result != UNKNOWN_COMMAND) ) {          /* unknown command aborts processing */
    
        trace_fii("decoding command[%i] = %0X\n", cmd_pointer, rcv_buffer[cmd_pointer]);
        
        switch(rcv_buffer[cmd_pointer]) {
            case CMD_01:                    /* red LED on */
                GPIO_owc_pin(RED_LED, 1);   /* LED on */
                break;
                
            case CMD_02:                   /* red LED off */
                GPIO_owc_pin(RED_LED, 0);   /* LED off */
                break;
                
            case CMD_03:                  /* green LED on */
                GPIO_owc_pin(GREEN_LED, 1); /* LED on */
                break;
                
            case CMD_04:                 /* green LED off */
                GPIO_owc_pin(GREEN_LED, 0); /* LED off */
                break;
                
            case CMD_NO_ACTION:         /* do nothing */
                break;
                
            default:                        /* unknown command */
                result = UNKNOWN_COMMAND;
                break;
        } /* end of switch(rcv_buffer[cmd_pointer]) */
        
        cmd_pointer += 1;
        
    }            

    return(result);

}

/* ============ END ========================================================================= */
