#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include <panel.h>
#include <time.h>
#include <sys/time.h>

#include "../include/aprstlm.h"
#include "../include/aprstlm-ncurses.h"

int generic_keyboard(struct winstruct *screen, int keypress, int datefmt, int tlmviews)
{
   if (keypress=='\t')
   {
      screen->curtlmview++;
      if (screen->curtlmview>=tlmviews)
         screen->curtlmview=0;
      show_panel(screen->tlm_pan[screen->curtlmview]);
   }

   if ((keypress=='t') || (keypress=='T'))
   {
      datefmt++;
      if (datefmt>3)
         datefmt=0;
   }

   return(datefmt);
}
