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

void pcsat2_extra_display(struct tlmframestruct *tlmframe, struct satstruct *sat, struct winstruct *screen)
{
   int i;
   int latestframe=99;
   time_t latesttime=0;

   /* Now We Have To Handle The 6/7 bits again */
   /* This is PCSAT2 Specific, and we need to */
   /* override any REVERSE setting of position 8*/
   /* Set Position 7 REVERSED only if bit 7 is 0 */
   /* and bit 8 is 1. Do not call touchwin until */
   /* we fix the potentially incorrect highlighting */


   /* Find the latest tlm frame */

   for (i=0; i<=3; i++)
   {
      if (tlmframe[i].rxtime.tv_sec!=0)
      { 
         mvwchgat(screen->bin_win,sat->cmdloc[0][6],sat->cmdloc[1][6],15,A_NORMAL,TLM_COLOUR_NOM,NULL);
         mvwchgat(screen->bin_win,sat->cmdloc[0][7],sat->cmdloc[1][7],15,A_NORMAL,TLM_COLOUR_NOM,NULL);
         if (tlmframe[i].rxtime.tv_sec>latesttime)
         {
            latestframe=i;
            latesttime=tlmframe[i].rxtime.tv_sec;
         }

         /* We can handle the display of each of the ARMED bits here, as */
         /* we don't care about which frame is the latest */

         if (tlmframe[i].endbit==1)
            mvwchgat(screen->tlm_win[1],9,4+(18*i),14,A_REVERSE,TLM_COLOUR_NOM,NULL);
         else
            mvwchgat(screen->tlm_win[1],9,4+(18*i),14,A_NORMAL,TLM_COLOUR_NOM,NULL);
      }
   }
   /* Now do the logic */
   if (latestframe!=99)
   {
      if ((!(tlmframe[latestframe].cmdbits[6])) && (tlmframe[latestframe].cmdbits[7]))
      {
         mvwchgat(screen->bin_win,sat->cmdloc[0][6],sat->cmdloc[1][6],15,A_REVERSE,TLM_COLOUR_NOM,NULL);
      } 
   }

   /* Handle 48 Hour Timer */

   if (tlmframe[3].rxtime.tv_sec!=0)
   {
      if (tlmframe[3].tlmval[4]<1.00)
         mvwchgat(screen->tlm_win[1],11,4,14,A_REVERSE,TLM_COLOUR_NOM,NULL);
      else
         mvwchgat(screen->tlm_win[1],11,4,14,A_NORMAL,TLM_COLOUR_NOM,NULL);
   }   
}
