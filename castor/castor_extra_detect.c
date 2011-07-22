#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "../include/aprstlm.h"
#include "../include/aprstlm-sockets.h"

#define TRUE    1
#define FALSE	0

int castor_extra_detect(char *aprsbuf ,int aprscount, struct satstruct *sat, char *tlmpkt)
{

   char systlmhdr[25];
   int hdrlen;
   int i,j,k;
   strcpy(systlmhdr, sat->asidecall[0]);
   strcat(systlmhdr, "CQ,TELEM");
   hdrlen=strlen(systlmhdr);

   for (i=hdrlen; i<strlen(aprsbuf); i++)
   {
      if (aprsbuf[i]==':')
      {
         j=i;
      }
   }
  
   if (aprsbuf[j+1]=='S')
   {
      if (strncmp(aprsbuf,systlmhdr, hdrlen)==0)
      {
          for (k=j+6; k<strlen(aprsbuf); k++)
          {
             tlmpkt[k-j-6]=aprsbuf[k];
          }
          tlmpkt[k-hdrlen]=0;
      }
   }

   return(98);
}
