#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <time.h>
#include <errno.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdarg.h>
#include <fcntl.h>

#include "strf.h"


#define SIZE_BLOCK 1024

static int count_threads = 0;

typedef struct {
    char *ports;
    int port;
    int v_num1;
    int v_num2;
    int v_num3;
    int v_num4;

} p_args;

typedef struct params_scan {

    char * a_host;
    char * a_port;

} p_scan;

typedef struct {

    u_int16_t one;
    u_int16_t two;
    u_int16_t three;
    u_int16_t four;

} s_host;

typedef struct {

    u_int16_t one;
    u_int16_t two;
    u_int16_t three;
    u_int16_t four;

} e_host;

extern int     scanning          (p_args *                          );

extern int     in_main_thread    (p_args *                          );
extern int     setArgv           (int,char *[]                      );

extern int     getParams         (int, char *[],struct params_scan *);
extern int     scan_target       (s_host*, e_host*,p_scan*          );

extern int     lensplit          (char *,char                       );
extern void    logo              (                                  );