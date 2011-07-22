/* Put any extra decode work that PCSAT requires here. Currently
/* this is  just a stub, but since the core checks if we have extra
/* ncurses work to do, and calls us if we do, we need a function to
/* permit the compile to work. This gets called AFTER the generic decode*/

/* Only decode stuff should appear here. Other extra stuff required */
/* for your satellite/device should appear in the correct _extra_ */
/* file. Uncomment the below include lines to get this to compile */
/* You shouldnt really need any other header files, unless they are */
/* specific to your satellite/device */

 #include <stdio.h> 
 #include <stdlib.h> 
 #include <stdbool.h>
/* #include <string.h> */
 #include <ncurses.h> 
/* #include <panel.h> */
 #include <time.h> 
 #include <sys/time.h> 
/* #include <math.h> */

 #include "../include/aprstlm.h"
/* #include "../include/aprstlm-ncurses.h"  */

void pollux_extra_decode(char *aprsbuf,int aprscount, struct satstruct *sat, char *tlmpkt, struct tlmframestruct *tlmframe)
{
   int i,j,k;
   char tlmval[32][16];	/* Maximum of 32 tlm values, 16 characters each */
   int l;

   struct timezone rxtz;	/* Like the generic code, just discard */

   fprintf(stderr,"aprsbuf:%s\n",aprsbuf);
   fprintf(stderr,"tlmpkt:%s\n",tlmpkt);

   for (i=0; i<=7; i++)
   {
      gettimeofday(&tlmframe[i].rxtime,&rxtz);
   };
   j=0;
   k=0;
   for (i=0; i<aprscount; i++)
   {
      if (tlmpkt[i]!=' ')
      {
        tlmval[j][k]=tlmpkt[i];
        k++;
      }
      else
      { 
         tlmval[j][k]=0;
         k=0;
         j++;
      }
   }

   /* Transfer each value to the correct tlm frame position */

   tlmframe[2].tlmval[2]=strtol(tlmval[6], NULL, 16);
   tlmframe[2].tlmval[3]=(int)strtol(tlmval[5], NULL, 16)/256.0;
   tlmframe[2].tlmval[4]=strtol(tlmval[14], NULL, 16);
   tlmframe[3].tlmval[0]=(int)strtol(tlmval[13], NULL, 16)/256.0;

   tlmframe[3].tlmval[1]=strtol(tlmval[8], NULL, 16);
   tlmframe[3].tlmval[2]=strtol(tlmval[7], NULL, 16)/256.0;
   tlmframe[3].tlmval[3]=strtol(tlmval[16], NULL, 16);
   tlmframe[3].tlmval[4]=strtol(tlmval[15], NULL, 16)/256.0;

   tlmframe[4].tlmval[0]=strtol(tlmval[10], NULL, 16);
   tlmframe[4].tlmval[1]=strtol(tlmval[9], NULL, 16)/256.0;
   tlmframe[4].tlmval[2]=strtol(tlmval[20], NULL, 16)/256;
   tlmframe[4].tlmval[3]=strtol(tlmval[18], NULL, 16)/256;

   tlmframe[4].tlmval[4]=strtol(tlmval[12], NULL, 16);
   tlmframe[5].tlmval[0]=strtol(tlmval[11], NULL, 16)/256.0;

   tlmframe[5].tlmval[1]=atoi(tlmval[3]);
   tlmframe[5].tlmval[2]=atoi(tlmval[4]);

}



