/* Put any extra ncurses setup that PCSAT requires here. Currently
/* this is  just a stub, but since the core checks if we have extra
/* ncurses work to do, and calls us if we do, we need a function to
/* permit the compile to work. Do *NOT* put anything in here that could */
/* or should be done in pcsat_setup.c or ncurses_setup(). Ask */
/* g7iii@g7iii.net if youre not sure */

/* Only ncurses stuff should appear here. Other extra stuff required */
/* for your satellite/device should appear in the correct _extra_ */
/* file. Uncomment the below include lines to get this to compile */
/* You shouldnt really need any other header files, unless they are */
/* specific to your satellite/device */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include <panel.h>
#include <time.h>
#include <sys/time.h>

#include "../include/aprstlm.h"
#include "../include/aprstlm-ncurses.h"

void mim_extra_ncurses(struct winstruct *screen, struct satstruct *sat, struct tlmframestruct *tlmframe)
{
   int i,j,k;					/* Loop Counters */

   for (i=0; i<=7; i++)
   {
      mvwaddch(screen->tlm_win[0],3,i+50,ACS_VLINE);
      mvwaddch(screen->tlm_win[0],10-i,50+i,ACS_LLCORNER); 
      mvwaddch(screen->tlm_win[0],3+i,58,ACS_HLINE); 
      mvwaddch(screen->tlm_win[0],3+i,59,ACS_HLINE); 

      mvwprintw(screen->tlm_win[0],3+i,60,sat->cmdstring[7-i]);

      for (j=0; j<=7; j++)
      {
         if (j<i)
            mvwaddch(screen->tlm_win[0],10-i,50+j,ACS_VLINE);
         else
            mvwaddch(screen->tlm_win[0],10-i,51+j,ACS_HLINE);
         
         if (j<=4)
            mvwaddch(screen->tlm_win[0],3+i,31+(4*j),ACS_VLINE);
      }
   }
   mvwaddch(screen->tlm_win[0],3,57,ACS_LLCORNER); 

   mvwaddch(screen->tlm_win[0],11,47,ACS_LLCORNER);
   mvwaddch(screen->tlm_win[0],11,31,ACS_LRCORNER);

   mvwaddch(screen->tlm_win[0],12,43,ACS_LLCORNER);
   mvwaddch(screen->tlm_win[0],12,35,ACS_LRCORNER);

   mvwaddch(screen->tlm_win[0],11,35,ACS_VLINE);
   mvwaddch(screen->tlm_win[0],11,39,ACS_VLINE);
   mvwaddch(screen->tlm_win[0],11,43,ACS_VLINE);

   mvwaddch(screen->tlm_win[0],12,39,ACS_VLINE);

   for (i=0; i<=1; i++)
   {
      for (j=0; j<=4; j++)
      {
         for (k=48+(4*j)-(4*i); k<=59; k++)
         {
            mvwaddch(screen->tlm_win[0],11+i,k,ACS_HLINE);
            mvwaddch(screen->tlm_win[0],11+i,k-29+(i*4),ACS_HLINE);
         }
      }
   }
}


