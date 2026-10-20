/* ------------------------------------------------------------------------------------------ */
/*                                                                                            */
/*                                                                                            */
/*                           GPIO_utils.c                                                     */
/*                                                                                            */
/*      Procedures to setup and control GPIO                                                  */
/*                                                                                            */
/* ------------------------------------------------------------------------------------------ */

#include    <unistd.h>
#include    <sys/types.h>
#include    <stdio.h>
#include    <stdlib.h>              /* exit() */
#include    <stdint.h>
#include    <fcntl.h>               /* O_RDWR */
#include    <sys/poll.h>            /* poll */
#include    <sys/ioctl.h>
#include    <string.h>              /* memcpy */

#include    "gpio_utils.h"
#include    "trace.h"

/* ------------ module local data ----------------------------------------------------------- */

#define     BUF_LEN        80

/* ------------ GPIO_export_pin ------------------------------------------------------------- */

/* Suppose pin parameters are set via device tree overlay */

int GPIO_export_pin(int pin_nr) {

char    buf[BUF_LEN];                               /* buffer for strings */
int     n_char;
int     GPIO_file;

//trace_fi("    Exporting pin %i: ... ", pin_nr);

    n_char = snprintf(buf, BUF_LEN, "%d", pin_nr);   /* convert pin number to string */

    GPIO_file = open(GPIO_EXPORT, O_WRONLY);        /* open export */
    if(GPIO_file < 0) {
        internal_error(__FILE__, __LINE__, "Error opening export");
        return(1);
    }

    write(GPIO_file, buf, n_char);                  /* export pin */
    close(GPIO_file);

//    trace_f("OK\n");
    
    return(0);

}

/* ------------ GPIO_open_pin_write --------------------------------------------------------- */

/* Suppose pin parameters are set via device tree overlay and pin is initialized (exported).  */
/* Returns pin_value file id.                                                                 */

int GPIO_open_pin_write(int pin_nr) {

char    buf[BUF_LEN];                                                   /* buffer for strings */
int     n_char;
int     GPIO_file;

//    trace_fi("    Opening pin %i for writing.\n", pin_nr);

    /* setting pin direction to "out" */
    n_char = snprintf(buf, BUF_LEN, GPIO_GPIO"%d/direction", pin_nr);   /* convert pin number to string */

    GPIO_file = open(buf, O_WRONLY);                                    /* open pin value */
    if(GPIO_file < 0) {
        internal_error(__FILE__, __LINE__, "Error opening pin direction");
        return(1);
    }
    else {
        n_char = write(GPIO_file, "out", 4);                            /* setting direction to "out" */
        if(n_char != 4) {
            internal_error(__FILE__, __LINE__, "Error opening pin direction");
            close(GPIO_file);                                           /* closing direction file */
            return(1);
        }
        close(GPIO_file);                                               /* closing direction file */
    }

    /* opening pin file */
    n_char = snprintf(buf, BUF_LEN, GPIO_GPIO"%d/value", pin_nr);       /* convert pin number to string */

    GPIO_file = open(buf, O_WRONLY);                                    /* open pin value */
    if(GPIO_file < 0) {
        internal_error(__FILE__, __LINE__, "Error opening pin value");
        return(1);
    }
    else {
    }

    return(GPIO_file);

}

/* ------------ GPIO_write_pin -------------------------------------------------------------- */

/* Suppose pin file is opened and set to output mode.                                         */

int GPIO_write_pin(int pin_file, int pin_value) {

int     nn;

    if(pin_value == 0) {
        nn = write(pin_file, "0", 2);                       /* write string "0" incl. 0x00 */
        if(nn != 2) {
            internal_error(__FILE__, __LINE__, "Error writing pin value 0");
            return(1);
        }
    }
    else {
        nn = write(pin_file, "1", 2);                       /* write string "1" */
        if(nn != 2) {
            internal_error(__FILE__, __LINE__, "Error writing pin value 1");
            return(1);
        }
    }

    return(0);

}

/* ------------ GPIO_open_pin_read  --------------------------------------------------------- */

/* Suppose pin parameters are set via device tree overlay and pin is initialized (exported).  */
/* Returns pin_value file id.                                                                 */

int GPIO_open_pin_read(int pin_nr) {

char    buf[BUF_LEN];                                               /* buffer for strings */
int     n_char;
int     GPIO_file;

//    trace_fi("    Opening pin %i for reading.\n", pin_nr);

    /* setting pin direction to "in" */
    n_char = snprintf(buf, BUF_LEN, GPIO_GPIO"%d/direction", pin_nr);   /* convert pin number to string */

    GPIO_file = open(buf, O_WRONLY);                                    /* open pin value */
    if(GPIO_file < 0) {
        internal_error(__FILE__, __LINE__, "Error opening pin direction");
        return(1);
    }
    else {
        n_char = write(GPIO_file, "in", 3);                             /* setting direction to "in" */
        if(n_char != 3) {
            internal_error(__FILE__, __LINE__, "Error opening pin direction");
            close(GPIO_file);                                           /* closing direction file */
            return(1);
        }
        close(GPIO_file);                                               /* closing direction file */
    }

    /* opening pin file */
    n_char = snprintf(buf, BUF_LEN, GPIO_GPIO"%d/value", pin_nr);       /* convert pin number to string */

    GPIO_file = open(buf, O_RDONLY);                                    /* open pin value */
    if(GPIO_file < 0) {
        internal_error(__FILE__, __LINE__, "Error opening pin value");
    }
    else {
    }

    return(GPIO_file);

}

/* ------------ GPIO_read_pin --------------------------------------------------------------- */

/* Suppose pin file is opened and set to input mode.                                         */

int GPIO_read_pin(int pin_file) {

    char    x_inp;

    lseek(pin_file, 0, SEEK_SET);       /* set file position to SOF */
    read(pin_file, &x_inp, 1);

    if(x_inp != '0') {
        return(1);                    /* return integer value */
    }
    else {
        return(0);                    /* return integer value */
    }

}

/* ------------ GPIO_open_pin_interrupt ----------------------------------------------------- */

/* Suppose pin parameters are set via device tree overlay and pin is initialized (exported).  */
/* Returns pin_value file id. Set "edge" for interrupt.                                       */

int GPIO_open_pin_interrupt(int pin_nr, const char *edge) {

char    buf[BUF_LEN];                                               /* buffer for strings */
int     n_char;
int     GPIO_file;

    trace_fi("    Opening pin %i for interrupt: ", pin_nr);

    /* setting pin direction to "in" */
    n_char = snprintf(buf, BUF_LEN, GPIO_GPIO"%d/direction", pin_nr);   /* convert pin number to string */

    GPIO_file = open(buf, O_WRONLY);                                    /* open pin value */
    if(GPIO_file < 0) {
        internal_error(__FILE__, __LINE__, "Error opening pin direction");
        return(1);
    }
    else {
        n_char = write(GPIO_file, "in", 3);                             /* setting direction to "in" */
        if(n_char != 3) {
            internal_error(__FILE__, __LINE__, "Error opening pin direction");
            close(GPIO_file);                                           /* closing direction file */
            return(1);
        }
        close(GPIO_file);                                               /* closing direction file */
        trace_f("direction = in, ");
        
    }

    /* setting pin edge to required value */
    n_char = snprintf(buf, BUF_LEN, GPIO_GPIO"%d/edge", pin_nr);        /* convert pin number to string */

    GPIO_file = open(buf, O_WRONLY);                                    /* open pin value */
    if(GPIO_file < 0) {
        internal_error(__FILE__, __LINE__, "Error opening pin edge");
        return(1);
    }
    else {
        n_char = write(GPIO_file, edge, strlen(edge));                  /* setting direction to "in" */
        if(n_char != strlen(edge)) {
            internal_error(__FILE__, __LINE__, "Error writing pin edge");
            close(GPIO_file);                                           /* closing direction file */
            return(1);
        }
        close(GPIO_file);                                               /* closing direction file */
        trace_fs("edge = %s.\n", (char *)edge);
    }

    /* opening pin file */
    n_char = snprintf(buf, BUF_LEN, GPIO_GPIO"%d/value", pin_nr);       /* convert pin number to string */

    GPIO_file = open(buf, O_RDONLY);                                    /* open pin value */
    if(GPIO_file < 0) {
        internal_error(__FILE__, __LINE__, "Error opening pin value");
    }
    else {
    }

    return(GPIO_file);

}

/* ------------ GPIO_wait_edge -------------------------------------------------------------- */

/* Wait for edge on selected pin.                                                             */

int GPIO_wait_edge(int pin_file) {


    int     pv;
    char    x_inp;
    struct  pollfd fds;

    fds.fd = pin_file;                  /* GPIO value file */
    fds.events = POLLPRI | POLLERR;     /* event type */

    pv = poll(&fds, 1, -1);             /* wait for interrupt */
    if(pv == -1) {                      /* error */
        perror("Error in poll");
    }

    lseek(pin_file, 0, SEEK_SET);       /* set file position to SOF */
    read(pin_file, &x_inp, 1);
//    lseek(pin_file, 0, SEEK_SET);       /* set file position to SOF */

    if(x_inp != '0') {
        return(1);                    /* return integer value */
    }
    else {
        return(0);                    /* return integer value */
    }

}

/* ------------ GPIO_close ------------------------------------------------------------------ */

/* Close GPIO file.                                                                           */

int GPIO_close(int pin_file) {

    close(pin_file);

    return(0);

}

/* ------------ GPIO_owc_pin ---------------------------------------------------------------- */

/* Open pin file, write value, close pin file. (owc = open-write-close)                       */

int GPIO_owc_pin(int pin_nr, int pin_value) {

int     pin_file;

    pin_file = GPIO_open_pin_write(pin_nr);         /* open pin file */
    if(pin_file >= 0) {
        GPIO_write_pin(pin_file, pin_value);
        GPIO_close(pin_file);
        return(0);
    }
    else {
        return(-1);
    }

}

/* ------------ GPIO_orc_pin ---------------------------------------------------------------- */

/* Open pin file, read value, close pin file. (orc = open-read-close)                         */

int GPIO_orc_pin(int pin_nr) {

int     pin_file;
int     x;

    x = -1;                                     /* return value if open/read fails */

    pin_file = GPIO_open_pin_read(pin_nr);      /* open pin file */
    if(pin_file >= 0) {
        x = GPIO_read_pin(pin_file);
        GPIO_close(pin_file);
    }
    return(x);

}

/* ------------ END ------------------------------------------------------------------------- */
