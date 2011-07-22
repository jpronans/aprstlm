/* Put any extra static work that PCSAT requires here. Currently
/* this is  just a stub, but since the core checks if we have extra
/* ncurses work to do, and calls us if we do, we need a function to
/* permit the compile to work. This gets called AFTER the generic static */

/* Only static stuff should appear here. Other extra stuff required */
/* for your satellite/device should appear in the correct _extra_ */
/* file. Uncomment the below include lines to get this to compile */
/* You shouldnt really need any other header files, unless they are */
/* specific to your satellite/device */

/* Anything in here should have equivalent code to handle the display */
/* functionality in <bird>_extra_display.c */

#include <stdio.h> 
#include <stdbool.h> 
#include <string.h> 
#include <ncurses.h>
#include <panel.h> 
#include <time.h> 
#include <sys/time.h> 

#include "../include/aprstlm.h" 
#include "../include/aprstlm-ncurses.h" 

void pcsat_extra_static(struct tlmframestruct *tlmframe, struct satstruct *sat, struct winstruct *screen)
{
   int i;


   for (i=0; i<=7; i++)
   {
      if (tlmframe[i].rxtime.tv_sec!=0)
      {
         mvwchgat(screen->bin_win,sat->cmdloc[0][8],(sat->cmdloc[1][8])+15,1,A_NORMAL,TLM_COLOUR_STATIC,NULL);
         mvwchgat(screen->bin_win,sat->cmdloc[0][9],(sat->cmdloc[1][9])+15,1,A_NORMAL,TLM_COLOUR_STATIC,NULL);
         mvwchgat(screen->bin_win,sat->cmdloc[0][10],(sat->cmdloc[1][10])+15,1,A_NORMAL,TLM_COLOUR_STATIC,NULL);
         mvwchgat(screen->bin_win,sat->cmdloc[0][11],(sat->cmdloc[1][11])+15,1,A_NORMAL,TLM_COLOUR_STATIC,NULL);
      }
   }

  for (i=0; i<=3; i++)
  {
      if ((tlmframe[i].rxtime.tv_sec!=0) && (tlmframe[i].deltatime<sat->statictime))
      {
         mvwchgat(screen->bin_win,sat->cmdloc[0][9],(sat->cmdloc[1][9])+15,1,A_NORMAL,TLM_COLOUR_INVIS,NULL);
         mvwchgat(screen->bin_win,sat->cmdloc[0][11],(sat->cmdloc[1][11])+15,1,A_NORMAL,TLM_COLOUR_INVIS,NULL);
      }
   }

  for (i=4; i<=7; i++)
  {
      if ((tlmframe[i].rxtime.tv_sec!=0) && (tlmframe[i].deltatime<sat->statictime))
      {
         mvwchgat(screen->bin_win,sat->cmdloc[0][8],(sat->cmdloc[1][8])+15,1,A_NORMAL,TLM_COLOUR_INVIS,NULL);
         mvwchgat(screen->bin_win,sat->cmdloc[0][10],(sat->cmdloc[1][10])+15,1,A_NORMAL,TLM_COLOUR_INVIS,NULL);
      }
   }
 
}
