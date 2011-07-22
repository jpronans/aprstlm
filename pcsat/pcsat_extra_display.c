/* Put any extra display work that PCSAT requires here. Currently
/* this is  just a stub, but since the core checks if we have extra
/* ncurses work to do, and calls us if we do, we need a function to
/* permit the compile to work. This gets called AFTER the generic display*/

/* Only display stuff should appear here. Other extra stuff required */
/* for your satellite/device should appear in the correct _extra_ */
/* file. Uncomment the below include lines to get this to compile */
/* You shouldnt really need any other header files, unless they are */
/* specific to your satellite/device */

/* Anything in here should have equivalent code to handle the static */
/* marker in <bird>_extra_static.c */

#include <stdio.h> 
#include <stdbool.h>
#include <string.h> 
#include <ncurses.h> 
#include <panel.h>
#include <time.h>
#include <sys/time.h>

#include "../include/aprstlm.h" 
#include "../include/aprstlm-ncurses.h" 

void pcsat_extra_display(struct tlmframestruct *tlmframe, struct satstruct *sat, struct winstruct *screen)
{

   int i,j,k;
   int latestframe=99;			/* Latest RXed Frame */
   time_t latestrxtime=0;

   /* Handle Induvidual TNC RESET */
   for (j=0; j<=1; j++)
   {
      /* Handle the fact that the labels are the wrong way round for */
      /* this code, but correct for humans */

      if (j==0)
         k=1;
      else
         k=0;

      for (i=0; i<=3; i++)
      {
         if ((tlmframe[(j*4)+i].rxtime.tv_sec!=0) && (tlmframe[(j*4)+i].rxtime.tv_sec>latestrxtime))
         {
           latestframe=(j*4)+i;
           latestrxtime=tlmframe[(j*4)+i].rxtime.tv_sec;
         }
      }
   
      if (latestframe!=99) 
      {
         if (tlmframe[latestframe].cmdbits[3])
            mvwchgat(screen->bin_win,sat->cmdloc[0][k+8],sat->cmdloc[1][k+8],14,A_NORMAL,TLM_COLOUR_NOM,NULL);
         else
            mvwchgat(screen->bin_win,sat->cmdloc[0][k+8],sat->cmdloc[1][k+8],14,A_REVERSE,TLM_COLOUR_NOM,NULL);
      }
      latestframe=99;
      latestrxtime=0;
   }

   /* Now Handle the MITEL/GPS Format and QRP multiplexed bit. Note How */
   /* similar the code is to the multiplexed TNC reset code above. This */
   /* is a very good example of *why* the core code is written the way  */
   /* it is. Note that this display code just sets normal or reverse video */
   /* on screen locations that have already been setup in the setup, and */
   /* ncurses routines */

   latestframe=99;
   latestrxtime=0;

   for (j=0; j<=1; j++)
   {
      /* Handle the fact that the labels are the wrong way round for */
      /* this code, but correct for humans */

      if (j==0)
         k=1;
      else
         k=0;

      for (i=0; i<=3; i++)
      {
         if ((tlmframe[(j*4)+i].rxtime.tv_sec!=0) && (tlmframe[(j*4)+i].rxtime.tv_sec>latestrxtime))
         {
           latestframe=(j*4)+i;
           latestrxtime=tlmframe[(j*4)+i].rxtime.tv_sec;
         }
      }
   
      if (latestframe!=99) 
      {
         if (tlmframe[latestframe].cmdbits[5])
            mvwchgat(screen->bin_win,sat->cmdloc[0][k+10],sat->cmdloc[1][k+10],14,A_NORMAL,TLM_COLOUR_NOM,NULL);
         else
            mvwchgat(screen->bin_win,sat->cmdloc[0][k+10],sat->cmdloc[1][k+10],14,A_REVERSE,TLM_COLOUR_NOM,NULL);
      }
      latestframe=99;
      latestrxtime=0;
   }
}
