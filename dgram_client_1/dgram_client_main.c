/* ------------------------------------------------------------------------------------------ */
/*                                                                                            */
/*                                                                                            */
/*                               dino_client_main.c                                           */
/*                                                                                            */
/*      Program to send requests to set LEDs on and off. Waiting for response.                */
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

#include    "config.h"
#include    "commands.h"
#include    "dgram_client_main.h"
#include    "dgram_client.h"
#include    "trace.h"

/* ========================================================================================== */

/* ------------ module local data ----------------------------------------------------------- */

unsigned char            command_buffer[COMMAND_BUFFER_SIZE];
unsigned char            response_buffer[RESPONSE_BUFFER_SIZE];

/* ========================================================================================== */

/* ============ main ======================================================================== */

int main(void) {

time_t          now;
time_t          xnow;

struct  tm      exp_now;
struct  timeval tm_xnow;
uint8_t         tmp;
int             rv;
int             n_bytes;

    /* open trace file */
    trace_init(DGRAM_TRACE_FN);

    now = time(NULL);

    trace_f("\n----------------------------------------------\n");
    trace_fs("dgram_client version: %s\n", VERSION_STRING);
    trace_f("\n----------------------------------------------\n");
    trace_fs("dgram_client_main started at %s", ctime(&now));
    trace_f("----------------------------------------------\n\n");

    now = time(NULL);
    trace_fs("dino_client socket opening at %s", ctime(&now));
    
    /* start create and bind socket */
    rv = dgram_client_start();
    if(rv == 0) {
        trace_f("returned OK\n");
    }
    else {
        trace_f("returned error\n");
    }
        
    while(1) {

        /* prepare command msg */
        prepare_command_msg(command_buffer, &n_bytes);
        
        /* send command msg */        
        trace_f("sending command \n");
        do {
            trace_f("  sending ... ");
            rv = command_dgram_send(command_buffer, COMMAND_BUFFER_SIZE);
        } while(UDP_TIMEOUTED == rv);
        
        /* read response */        
        trace_f("waiting for response\n ");
        do {
            trace_f("  waiting ... ");
            rv = server_response_read(response_buffer, RESPONSE_BUFFER_SIZE);     /* rv = number of received bytes */
        } while(UDP_TIMEOUTED == rv);
        
        if(rv >= 0) {
            trace_f("response read OK\n");
            /* decode response */
            response_decode(response_buffer, rv);                      
        }
        else {
            trace_f("response read with error\n");
        }
        
        trace_f("-----------\n");
        
    }           /* end of while(1) */

    return(0);      

}

/* ============ response_decode ============================================================= */

/* Decode response received from server.                                                      */

int response_decode(unsigned char *r_buffer, int n_char) {

int     result;

    trace_fi("decoding response %0X\n", r_buffer[0]);
    result = RESPONSE_VALID;
    
    switch(r_buffer[0]) {
        case COMMAND_EXECUTED:          /* server executed command OK */
            trace_f("Response: Command executed\n");
            break;
            
        case UNKNOWN_COMMAND:           /* server did not recognize the command */
            trace_f("Response: Unknown command\n");
            break;
                        
        default:                        /* unknown response */
            trace_fi("Unknown response code (%i)\n", r_buffer[0]);
            result = UNKNOWN_RESPONSE;
            break;
        }            

    return(result);

}

/* ============ prepare_command_msg ========================================================= */

/*                                   */

int prepare_command_msg(unsigned char *cmd_buffer, int *nb) {

int     inp;

    printf("Command (1 = RED_ON, 2 = RED_OFF, 3 = GREEN_ON, 4 = GREEN_OFF): ");
    scanf("%i", inp);

#ifdef  OLD_COMMANDS
    if(( 0 < inp) && (5 > inp)) {
        cmd_buffer[0] = (unsigned char)inp;
    } 
    else {
        cmd_buffer[0] = 0;      /* dummy value */     
    }

#else 
   
    switch(inp) {
        case 1:       
            cmd_buffer[0] = CMD_01;
            break;
        case 2:       
            cmd_buffer[0] = CMD_02;
            break;
        case 3:       
            cmd_buffer[0] = CMD_03;
            break;
        case 4:       
            cmd_buffer[0] = CMD_04;
            break;
        default:
            cmd_buffer[0] = CMD_END;     
            break;
    }
                    
#endif
    
    cmd_buffer[1] = CMD_END;     

    *nb = 2;
    
    return(*nb);
    
}

/* ============ END ========================================================================= */
