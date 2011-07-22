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

void castor_extra_decode(char *aprsbuf,int aprscount, struct satstruct *sat, char *tlmpkt, struct tlmframestruct *tlmframe)
{
   int i,j,k;
   char tlmval[32][16];	/* Maximum of 32 tlm values, 16 characters each */
   int l;

   struct timezone rxtz;	/* Like the generic code, just discard */

   fprintf(stderr,"Entered castor_extra_decod(e)\n");
 

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
         fprintf(stderr,"Found space!i=%d j=%d k=%d\n",i,j,k);
         tlmval[j][k]=0;
         k=0;
         j++;
      }
   }

   for (l=0; l<31; l++)
      fprintf(stderr,"tlmval[%d]:%s\n", l, tlmval[l]);

   /* Transfer each value to the correct tlm frame position */

   tlmframe[0].tlmval[0]=(float)atof(tlmval[27]);
   tlmframe[0].tlmval[1]=(float)atof(tlmval[28]);
   tlmframe[0].tlmval[2]=(float)atof(tlmval[29]);

   fprintf(stderr,"tlm-27:%2.2f \n",tlmframe[0].tlmval[0]);
   fprintf(stderr,"tlm-27:%2.2f \n",tlmframe[0].tlmval[1]);
   fprintf(stderr,"tlm-27:%2.2f \n",tlmframe[0].tlmval[2]);
 
   tlmframe[0].tlmval[3]=atof(tlmval[20]);
   tlmframe[0].tlmval[4]=atof(tlmval[21]);
   tlmframe[1].tlmval[0]=atof(tlmval[22]);

   tlmframe[1].tlmval[1]=atof(tlmval[23]);
   tlmframe[1].tlmval[2]=atof(tlmval[24]);
   tlmframe[1].tlmval[3]=atof(tlmval[25]);

   tlmframe[1].tlmval[4]=atof(tlmval[17]);
   tlmframe[2].tlmval[0]=atof(tlmval[19]);
   tlmframe[2].tlmval[1]=atof(tlmval[18]);

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
   tlmframe[4].tlmval[2]=atoi(tlmval[4]);

   tlmframe[4].tlmval[4]=strtol(tlmval[12], NULL, 16);
   tlmframe[5].tlmval[0]=strtol(tlmval[11], NULL, 16)/256.0;
   tlmframe[5].tlmval[1]=atoi(tlmval[3]);
   tlmframe[5].tlmval[2]=atof(tlmval[26]);


}



