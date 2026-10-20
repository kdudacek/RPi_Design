/* ------------------------------------------------------------------------------------------ */
/*                                                                                            */
/*                                                                                            */
/*                           GPIO_utils.h                                                     */
/*                                                                                            */
/*                                                                                            */
/*                                                                                            */
/* ------------------------------------------------------------------------------------------ */


/* ------------ --- ------------------------------------------------------------------------- */

#ifndef _GPIO_UTILS_H_
#define _GPIO_UTILS_H_

/* ------------ --- ------------------------------------------------------------------------- */

#define GPIO_EXPORT             "/sys/class/gpio/export"
#define GPIO_GPIO               "/sys/class/gpio/gpio"

#define RISING_EDGE             "rising"                /* for port edge setting */
#define FALLING_EDGE            "falling"
#define BOTH_EDGES              "both"

/* ------------ --- ------------------------------------------------------------------------- */

int GPIO_export_pin(int pin_nr) ;

int GPIO_open_pin_write(int pin_nr) ;

int GPIO_write_pin(int pin_file, int pin_value) ;

int GPIO_open_pin_read(int pin_nr) ;

int GPIO_read_pin(int pin_file) ;

int GPIO_open_pin_interrupt(int pin_nr, const char *edge) ;

int GPIO_wait_edge(int pin_file) ;

int GPIO_close(int pin_file) ;

int GPIO_owc_pin(int pin_nr, int pin_value) ;

int GPIO_orc_pin(int pin_nr) ;

/* ------------ --- ------------------------------------------------------------------------- */

#endif

/* ------------ END ------------------------------------------------------------------------- */
