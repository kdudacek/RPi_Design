/* ------------------------------------------------------------------------------------------ */
/*                                                                                            */
/*                                                                                            */
/*                               gpio_get_set.c                                           */
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
#include    <sys/poll.h>            /* poll */
#include    <sys/ioctl.h>

#include    "config.h"
#include    "gpio_get_set.h"
#include    "gpio_utils.h"
#include    "trace.h"

/* ========================================================================================== */

/* ------------ module local data ----------------------------------------------------------- */

/* ========================================================================================== */

/* ============ main ======================================================================== */

int main(void) {

time_t          now;
time_t          xnow;
struct  tm      exp_now;
struct  timeval tm_xnow;

int     gpio_in_file;           /* file for input pin */
int     gpio_out_file;          /* file for output pin */
struct  pollfd fds;             /* for interrupt detection */

char    x_inp[2];               /* input value in x_inp[0], 0x00 in x_inp[1] */
int     nn;
int     pv;

    /* open trace file */
    trace_init(GPIO_GET_SET_TRACE_FN);

    now = time(NULL);

    trace_f("\n----------------------------------------------\n");
    trace_fs("gpio_get_set started at %s", ctime(&now));
    trace_f("\n----------------------------------------------\n\n");

    now = time(NULL);
    
    GPIO_export_pin(GPIO_OUT_PIN);
    GPIO_export_pin(GPIO_IN_PIN);

    gpio_out_file = GPIO_open_pin_write(GPIO_OUT_PIN);
    gpio_in_file = GPIO_open_pin_interrupt(GPIO_IN_PIN, "both");
    
    x_inp[1] = 0x00;
    
    while(1) {
                
        /* wait for interrupt and then set out gpio pin */
        fds.fd = gpio_in_file;              /* GPIO value file */
        fds.events = POLLPRI | POLLERR;     /* event type */

        pv = poll(&fds, 1, POLL_TIMEOUT);   /* wait for interrupt or timeout */

        /* edge has been detected */
        if(pv == -1) {                      /* error */
            internal_error(__FILE__, __LINE__, "poll in edge detect thread");
        }

        lseek(gpio_in_file, 0, SEEK_SET);       /* set file position to SOF */
        read(gpio_in_file, x_inp, 1);           /* read to x_inp[0] */

        nn = write(gpio_out_file, x_inp, 2);         /* write string */
        if(nn != 2) {
            internal_error(__FILE__, __LINE__, "Error writing pin value 1");
            return(1);
        }
                  
    }           /* end of while(1) */

    return(0);      
}

/* ============ END ========================================================================= */
