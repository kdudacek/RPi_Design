/* ------------------------------------------------------------------------------------------ */
/*                                                                                            */
/*                                                                                            */
/*                                config.h                                                    */
/*                                                                                            */
/*                                                                                            */
/*      Procedures to create server socket, listen, accept and close.                         */
/*                                                                                            */
/* ------------------------------------------------------------------------------------------ */

/* ------------ --- ------------------------------------------------------------------------- */

#ifndef __GPIO_GET_SET_CONFIG_H__
#define __GPIO_GET_SET_CONFIG_H__

/* ------------ configuration --------------------------------------------------------------- */

/* GPIO registers for RPi */
#define GPFSEL0_OFFSET                  (0x00 / 4)  /* offset of 32bit register is /4 */
#define GPFSEL1_OFFSET                  (0x04 / 4)  /* offset of 32bit register is /4 */

#define GPSET0_OFFSET                   (0x1C / 4)  /* offset of 32bit register is /4 */
#define GPCLR0_OFFSET                   (0x28 / 4)  /* offset of 32bit register is /4 */

#define GPLEV0_OFFSET                   (0x34 / 4)  /* offset of 32bit register is /4 */

//#define GPFSEL0_OFFSET                  (0x00)  /* offset of 32bit register is /4 */
//#define GPFSEL1_OFFSET                  (0x04)  /* offset of 32bit register is /4 */

//#define GPSET0_OFFSET                   (0x1C)  /* offset of 32bit register is /4 */
//#define GPCLR0_OFFSET                   (0x28)  /* offset of 32bit register is /4 */
//#define GPLEV0_OFFSET                   (0x34)  /* offset of 32bit register is /4 */

#define GPPUD_OFFSET                    (0x94 / 4)  /* offset of 32bit register is /4 */
#define GPPUDCLK0_OFFSET                (0x98 / 4)  /* offset of 32bit register is /4 */
#define PULLUP                          0x00000002
//#define GPIO_REGISTER_BASE              (0x20000000 + 0x200000) /* base addr. of GPIO on Raspberry Pi */
#define GPIO_REGISTER_BASE              (0x3F000000 + 0x200000) /* base addr. of GPIO on Raspberry Pi */

/* --- GPIO --- */

#define     GPIO_OUT_PIN        11                  /*  */
#define     GPIO_IN_PIN         9                  /*  */

#define     GPIO_11_FSEL_MASK  0x00000038   /* mask for 3bit FSEL */
#define     GPIO_11_FSEL_OUT   0x00000008   /* GPIO_11 = output */
#define     GPIO_11_BIT_MASK   (0x00000001 << GPIO_OUT_PIN)   /*  */

/* --- trace --- */
#define     HW_SET_SET_TRACE_FN        "hw_set_set_trace.txt"

/* ------------------------------------------------------------------------------------------ */

#endif

/* ------------ END ------------------------------------------------------------------------- */
