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

/* #include <stdio.h> */
/* #include <stdbool.h> */
/* #include <string.h> */
#include <ncurses.h> 
#include <panel.h> 
#include <time.h> 
#include <sys/time.h> 

#include "../include/aprstlm.h" 
#include "../include/aprstlm-ncurses.h"

void pollux_extra_ncurses(struct winstruct *screen)
{
   screen->curtlmview=1;
   show_panel(screen->tlm_pan[screen->curtlmview]);
}
