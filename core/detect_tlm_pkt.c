#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "../include/aprstlm.h"
#include "../include/aprstlm-sockets.h"

#define TRUE    1
#define FALSE	0

int detect_tlm_pkt(char *aprsbuf ,int aprscount, struct satstruct *sat, char *tlmpkt)
{

   int i=0;					/* Loop Counter */
   int j;					/* Callsign Loop Counter */
   int k=0;					/* Tlmpkt Loop Counter */

   bool aside=FALSE;				/* Do We Have A-Side */
   bool bside=FALSE;				/* Do We Have B-Side */

   int frameno=0;
   for (j=0; j<sat->asidecalls; j++)
   {
      if (strncmp(aprsbuf,sat->asidecall[j],strlen(sat->asidecall[j]))==0)
      {
         aside=TRUE;
         bside=FALSE;
      }
   }

   for (j=0; j<sat->bsidecalls; j++)
   {
      if (strncmp(aprsbuf,sat->bsidecall[j],strlen(sat->bsidecall[j]))==0)
      {
         aside=FALSE;
         bside=TRUE;
      }
   }

   if ((aside) || (bside))
   {
      for (i=0; i<=((strlen(aprsbuf))-4); i++)
      {
         if (aprsbuf[i]==':')
         {
            i++;
            if (aprsbuf[i]=='T')
            {
               i++;
               if (aprsbuf[i]=='#')
               {
                  for (k=i; k<=strlen(aprsbuf); k++)
                  {
                     tlmpkt[k-i]=aprsbuf[k];
                  }

                  if ((strlen(aprsbuf))>35)
                  {
                     if (aprsbuf[i+36]=='1')
                        frameno=2;
                     if (aprsbuf[i+37]=='1')
                        frameno++;

                     if (bside)
                        frameno=frameno+(((sat->frametypes)+1)/2);
                  }
                  else
                     frameno=0;

                  return (frameno);
               }
            }
         }
      }
      return (128);
   }

   return(99);
}
