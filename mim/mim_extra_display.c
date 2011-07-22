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


void mim_extra_display(struct tlmframestruct *tlmframe, struct satstruct *sat, struct winstruct *screen)
{

   int j;
   for (j=0; j<=4; j++)
   {
      switch(tlmframe[0].valtype[j])
      {
         case TLM_VAL_TYPE_VOLT:
            mvwprintw(screen->tlm_win[0],tlmframe[0].loc[0][j],tlmframe[0].loc[1][j]+15,"V S");
            break;
         case TLM_VAL_TYPE_CURR:
            mvwprintw(screen->tlm_win[0],tlmframe[0].loc[0][j],tlmframe[0].loc[1][j]+14,"mA S");
            break;
         case TLM_VAL_TYPE_TEMP:
            mvwprintw(screen->tlm_win[0],tlmframe[0].loc[0][j],tlmframe[0].loc[1][j]+15,"C S");
            mvwaddch(screen->tlm_win[0],tlmframe[0].loc[0][j],tlmframe[0].loc[1][j]+14,ACS_DEGREE);
            break;
         case TLM_VAL_TYPE_TEMP_SHORTLBL:
            mvwprintw(screen->tlm_win[0],tlmframe[0].loc[0][j],tlmframe[0].loc[1][j]+15,"C S");
            mvwaddch(screen->tlm_win[0],tlmframe[0].loc[0][j],tlmframe[0].loc[1][j]+14,ACS_DEGREE);
            mvwaddch(screen->tlm_win[0],tlmframe[0].loc[0][j],tlmframe[0].loc[1][j]+6,ACS_DEGREE);
            break;
         case TLM_VAL_TYPE_WATT:
            mvwprintw(screen->tlm_win[0],tlmframe[0].loc[0][j],tlmframe[0].loc[1][j]+15,"W S");
            break;
      }
      mvwchgat(screen->tlm_win[0],tlmframe[0].loc[0][j],tlmframe[0].loc[1][j]+17,1,A_NORMAL,TLM_COLOUR_INVIS,NULL);
   }
}



