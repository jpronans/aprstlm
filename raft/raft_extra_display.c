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

void raft_extra_display(struct tlmframestruct *tlmframe, struct satstruct *sat, struct winstruct *screen)
{
   int i=0;
   int j;

   for (j=8; j<=11; j++)
   {
      if (tlmframe[i].cmdbits[j])
         mvwchgat(screen->bin_win,sat->cmdloc[0][j],sat->cmdloc[1][j],14,A_NORMAL,TLM_COLOUR_NOM,NULL);
      else
        mvwchgat(screen->bin_win,sat->cmdloc[0][j],sat->cmdloc[1][j],14,A_REVERSE,TLM_COLOUR_NOM,NULL);
    }
}



