#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>
#include <math.h>

#include "../include/aprstlm.h"
#include "../include/aprstlm-sockets.h"

int decode_tlm_pkt(char *tlmpkt, struct satstruct *sat, struct tlmframestruct *tlmframe, int frameno)
{
   int i;					/* Command Bits Loop Counter */
   int j;					/* Quad Equation Loop Counter */
   int z;					/* DEBUG Loop Counter */

   struct timezone rxtz;			/* Just Discard It */
   char discard01,discard02,discard03;          /* Discard these chars */
   char discard04,discard05,discard06;          /* Discard these chars */

   char binarybits[15];				/* Temp Char Vers of cmd, */
                                                /* experiment, and end bits */

   char timestr[80];

   sscanf(tlmpkt,"%c%d%c%d%c%d%c%d%c%d%c%d%c%s",&discard01,&tlmframe[frameno].framecount,&discard02,&tlmframe[frameno].rawtlm[0],&discard03,&tlmframe[frameno].rawtlm[1],&discard04,&tlmframe[frameno].rawtlm[2],&discard05,&tlmframe[frameno].rawtlm[3],&discard05,&tlmframe[frameno].rawtlm[4],&discard06,&binarybits);

   /* Update timestamps */

   gettimeofday(&tlmframe[frameno].rxtime,&rxtz);

   /* Convert Cmd Bits to Binary for easier display processing */
   for (i=0; i<=7; i++)
   {
      tlmframe[frameno].cmdbits[i]=FALSE;
      if (binarybits[i]=='1')
         tlmframe[frameno].cmdbits[i]=TRUE;
   }

   if (sat->extrabits)
   {
      for (i=9; i<=10; i++)
      {
         tlmframe[frameno].sbits[i-9]=FALSE;
         if (binarybits[i]=='1')
            tlmframe[frameno].sbits[i-9]=TRUE;
      }
   
      tlmframe[frameno].endbit=FALSE;
      if (binarybits[14]=='1')
         tlmframe[frameno].endbit=TRUE;
   }

   for (j=0; j<=4; j++)
   {
      tlmframe[frameno].tlmval[j]=
       (float)((tlmframe[frameno].a[j]*(powf(tlmframe[frameno].rawtlm[j],3.0)))
             +(tlmframe[frameno].b[j]*(powf(tlmframe[frameno].rawtlm[j],2.0)))
             +(tlmframe[frameno].c[j]*tlmframe[frameno].rawtlm[j])
             +tlmframe[frameno].d[j]);
   }

   return(0);
}
