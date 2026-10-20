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
//#include    <pthread.h>
#include    <sys/mman.h>            /* mmap */

#include    "config.h"
#include    "hw_set_set.h"
#include    "gpio_utils.h"
#include    "trace.h"

/* ========================================================================================== */

/* ------------ module local data ----------------------------------------------------------- */

/* ========================================================================================== */

uint32_t        *mapped_register_base;  /* addres to which registers are mapped (uint32_t *) */

/* ============ main ======================================================================== */

int main(void) {

time_t          now;
time_t          xnow;
struct  tm      exp_now;
struct  timeval tm_xnow;

    /* open trace file */
    trace_init(HW_SET_SET_TRACE_FN);

    now = time(NULL);

    trace_f("\n----------------------------------------------\n");
    trace_fs("hw_set_set started at %s", ctime(&now));
    trace_f("\n----------------------------------------------\n\n");

    now = time(NULL);
    
    rpi_map_registers();
    
    while(1) {
    
        *(mapped_register_base + GPSET0_OFFSET) = 0x00000800;
//        printf("GPIO_value = %X\n", *( (uint32_t *)mapped_register_base + GPLEV0_OFFSET) );
//        sleep(1);
                
        *(mapped_register_base + GPCLR0_OFFSET) = 0x00000800;
//        printf("GPIO_value = %X\n", *( (uint32_t *)mapped_register_base + GPLEV0_OFFSET) );
//        sleep(1);
                  
    }           /* end of while(1) */

    return(0);      
}

/* ============ END ========================================================================= */

/* ------------ rpi_map_registers ----------------------------------------------------------- */

/*                              */

int rpi_map_registers(void) {

int             mem_file;
int             i;
void            *mapped_region;         /* addres to which registers are mapped (void *)     */
unsigned long   reg_base;

uint32_t         reg_copy;

    reg_base = GPIO_REGISTER_BASE;      /* GPIO register block address */

    /* open memory file */
    trace_f("Opening memory file /dev/mem ... ");
    mem_file = open("/dev/mem", O_RDWR | O_SYNC);
    if(mem_file < 0) {
        internal_error(__FILE__, __LINE__, "Error opening memory file");
        return(1);
    }
    trace_f("OK\n");

    /* map register address range to accessible memory */
    trace_fi("Mapping register address range %X ... ", reg_base);
    mapped_region = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, mem_file, reg_base);
    if(mapped_region == MAP_FAILED) {
        internal_error(__FILE__, __LINE__, "Error opening memory file");
        return(1);
    }
    trace_fi("mapped to %X\n", (int)mapped_region);

    mapped_register_base = (uint32_t *)mapped_region;   /* change type of ptr */

    /* set mode for GPIO 11 */
    reg_copy = *(mapped_register_base + GPFSEL1_OFFSET);    /* read mode register */
    printf("reg_copy after read = %X\n", reg_copy);
    
    reg_copy &= ~GPIO_11_FSEL_MASK;         /* set GPIO 11 to output mode */
    reg_copy |= GPIO_11_FSEL_OUT;           /* set GPIO 11 to output mode */
//    reg_copy &= (~GPIO_11_FSEL_MASK);     /*  */

    *(mapped_register_base + GPFSEL1_OFFSET) = reg_copy;
    printf("reg_copy after write = %X\n", *(mapped_register_base + GPFSEL1_OFFSET));
    
//    trace_f("Unmapping register address range\n");
//    munmap(mapped_region, 4096);

//    trace_f("Closing memory file\n");
//    close(mem_file);

    return(0);

}


