#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "../include/aprstlm.h"
#include "../include/aprstlm-sockets.h"

#define TRUE    1
#define FALSE	0

int pcsat_extra_detect(char *aprsbuf ,int aprscount, struct satstruct *sat, char *tlmpkt, int frameno)
{
   return(frameno);
}
