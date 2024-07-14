
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


extern int     split        (char *,  char ,   char [][1024]   );
extern int     splet        (char *, char ,   char *[]         );

extern char *  mvstring     (int   ,   int,   int, int         );
extern char *  mvsymbol     (int                               );

extern char *  concat       (char*[] , int                     );