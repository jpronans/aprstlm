#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "../include/aprstlm.h"
#include "../include/aprstlm-sockets.h"

#define TRUE    1
#define FALSE	0

int ande_extra_detect(char *aprsbuf ,int aprscount, struct satstruct *sat, char *tlmpkt)
{

   int frameno=0;

   if ((strlen(tlmpkt))>26)
   {
      if (tlmpkt[25]=='1')
         frameno=2;
      if (tlmpkt[26]=='1')
         frameno++;
   }
   return(frameno);

}
