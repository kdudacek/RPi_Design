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

#ifndef __DGRAM_CONFIG_H__
#define __DGRAM_CONFIG_H__

/* ------------ configuration --------------------------------------------------------------- */

/* --- configuration --- */
#define     VERSION_STRING     "1.1"                  

/* --- response --- */
#define     COMMAND_EXECUTED    1                  
#define     UNKNOWN_COMMAND     2                  

#define     RESPONSE_VALID      1                  
#define     UNKNOWN_RESPONSE    2                  

/* --- sockets --- */
#define     COMMAND_BUFFER_SIZE  255
#define     RESPONSE_BUFFER_SIZE  255

#define     SERVICE_PORT        5001            /* port for server */
//#define     SERVICE_IP_ADDRESS  "192.168.0.19"  /* raspberry_02 */

#define     IP_RPI              "10.11.0.21"  /* RPi #1 */
#define     IP_BBU              "10.11.0.19"  /* BBU */
#define     IP_ESP              "10.11.0.20"  /* ESP32 */

#define     SERVER_IP_ADDRESS   IP_RPI  

/* --- trace --- */
#define     DGRAM_TRACE_FN        "dgram_client_trace.txt"

/* --- LED --- */
#define     GREEN_ON            1                  
#define     GREEN_OFF           2                  
#define     RED_ON              3                  
#define     RED_OFF             4                  

/* ------------------------------------------------------------------------------------------ */

#endif

/* ------------ END ------------------------------------------------------------------------- */
