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

#ifndef __DINO_CONFIG_H__
#define __DINO_CONFIG_H__

/* ------------ configuration --------------------------------------------------------------- */

/* --- response --- */

/* --- LED --- */
#define     RED_LED             17                  /* pin for RED LED */
#define     GREEN_LED           27                  /* pin for GREEN LED */

/* --- sockets --- */
#define     RCV_BUFFER_SIZE  50
#define     RESPONSE_BUFFER_SIZE  50
#define     SERVICE_PORT        5001        /* port for server */

/* --- server states --- */
#define     NOT_STARTED         10          /*  */
#define     LISTENING           11          /*  */
#define     CONNECTED           12          /*  */
#define     FAILED              13          /*  */

/* --- trace --- */
#define     DGRAM_TRACE_FN        "dgram_server_trace.txt"

/* ------------------------------------------------------------------------------------------ */

#endif

/* ------------ END ------------------------------------------------------------------------- */
