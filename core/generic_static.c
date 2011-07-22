#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>
#include <panel.h>

#include "../include/aprstlm.h"
#include "../include/aprstlm-ncurses.h"
#include "../include/aprstlm-sockets.h"

int generic_static(struct tlmframestruct *tlmframe, struct satstruct *sat, struct winstruct *screen)
{
   int i;				/* Loop Counter */
   int j;
   int k;

   int w;				/* B-Side vertical offset */

   char rawstring[77];
   char tmpvalstr[3];

   for (i=0; i<=sat->frametypes; i++)
   {
      if (i<=3)
         w=0;
      else
         w=2;

      for (j=0; j<=4; j++)
      {
         /* If we've recieved this telemetry frame, assume its static */

         if (tlmframe[i].rxtime.tv_sec!=0) 
         {
            if (sat->frametypes!=0)
            {
               mvwchgat(screen->tlm_win[0],3+w+i,78,1,A_NORMAL,TLM_COLOUR_STATIC,NULL);
               /* This if only evalutes true if we set the value type for */
               /* the telemetry vslue in question to NONE. This means it  */
               /* isn't displayed, so the static flag is also not needed */

               if (tlmframe[i].valtype[j]!=TLM_VAL_TYPE_NONE)
                  mvwchgat(screen->tlm_win[1],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+17,1,A_NORMAL,TLM_COLOUR_STATIC,NULL);
               for (k=0; k<=7; k++)
               {
                  mvwchgat(screen->bin_win,sat->cmdloc[0][k],(sat->cmdloc[1][k])+15,1,A_NORMAL,TLM_COLOUR_STATIC,NULL);
               }
            }
            else
            {
               mvwchgat(screen->tlm_win[0],2,59,1,A_NORMAL,TLM_COLOUR_STATIC,NULL);
            }
 
         }
      }

      /* Handle Raw TLM Window */

      if (tlmframe[i].rxtime.tv_sec!=0) 
      {
         if (sat->frametypes!=0) 
            mvwchgat(screen->tlm_win[0],3+w+i,78,1,A_NORMAL,TLM_COLOUR_STATIC,NULL);
         else
         {
            mvwchgat(screen->tlm_win[0],0,26,1,A_NORMAL,TLM_COLOUR_STATIC,NULL);
            mvwchgat(screen->tlm_win[0],2,59,1,A_NORMAL,TLM_COLOUR_STATIC,NULL);
         }
      }
   }

   /* Now we unset the static flag for those that are not static */

   for (i=0; i<=sat->frametypes; i++)
   {
      if (i<=3)
         w=0;
      else
         w=2;

      for (j=0; j<=4; j++)
      {
         /* Note, we need to double check if we've recieved this frame */

         if ((tlmframe[i].rxtime.tv_sec!=0) && (tlmframe[i].deltatime<sat->statictime))
         {
            if(sat->frametypes!=0) 
            {
               mvwchgat(screen->tlm_win[1],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+17,1,A_NORMAL,TLM_COLOUR_INVIS,NULL);
               for (k=0; k<=7; k++)
               {
                  mvwchgat(screen->bin_win,sat->cmdloc[0][k],(sat->cmdloc[1][k])+15,1,A_NORMAL,TLM_COLOUR_INVIS,NULL);
               }
            }
            else
               mvwchgat(screen->tlm_win[0],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+17,1,A_NORMAL,TLM_COLOUR_INVIS,NULL);
         }
      }
      
      /* Handle Raw TLM Window */

      if ((tlmframe[i].rxtime.tv_sec!=0) && (tlmframe[i].deltatime<sat->statictime))
      {
         if(sat->frametypes!=0)
            mvwchgat(screen->tlm_win[0],3+w+i,78,1,A_NORMAL,TLM_COLOUR_INVIS,NULL);
         else
         {
            mvwchgat(screen->tlm_win[0],0,26,1,A_NORMAL,TLM_COLOUR_INVIS,NULL);
            mvwchgat(screen->tlm_win[0],2,59,1,A_NORMAL,TLM_COLOUR_INVIS,NULL);
         }
      }
   }
}
