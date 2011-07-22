/* Put any extra ncurses setup that PCSAT requires here. Currently
/* this is  just a stub, but since the core checks if we have extra
/* ncurses work to do, and calls us if we do, we need a function to
/* permit the compile to work. Do *NOT* put anything in here that could */
/* or should be done in pcsat_setup.c or ncurses_setup(). Ask
g7iii@g7iii.net if youre not sure */

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

void pcsat2_extra_ncurses(struct winstruct *screen, struct satstruct *sat, struct tlmframestruct *tlmframe)
{
   mvwprintw(screen->tlm_win[1],9,4,"RELAY A1 ARMED S  RELAY A2 ARMED S  RELAY B1 ARMED S  RELAY B2 ARMED S");
   mvwprintw(screen->tlm_win[1],11,4," 48-HOUR TIMER S   60-HOUR TIMER S  LOW-VOLT SHUNT S  TLM COUNT ROLL S");

   mvwchgat(screen->tlm_win[1],9,4,71,A_NORMAL,TLM_COLOUR_INVIS,NULL);
   mvwchgat(screen->tlm_win[1],11,4,71,A_NORMAL,TLM_COLOUR_INVIS,NULL);
}



