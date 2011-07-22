#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include <panel.h>
#include <time.h>
#include <sys/time.h>

#include "../include/aprstlm.h"
#include "../include/aprstlm-ncurses.h"

void ncurses_setup(struct winstruct *screen, struct satstruct *sat, struct tlmframestruct *tlmframe)
{

  int i,j;					/* Loop Counters */
  int w;					/* Raw Win Vert Offset */
  int tlmwin;					/* 0 if we are a 1 pkt bird */

  char hdr_gen_txt[28];				/* Header Text */

  /* Setup ncurses stuff */

   initscr();
   curs_set(0);                                 /* Turn the Cursor Off */
   cbreak();                                    /* Raw, Immediate Input */
   noecho();                                    /* Don't Do Any Echoing */
   nodelay(stdscr,TRUE);                        /* No Delays! */

   if(has_colors() == TRUE)
   {
      start_color();
      init_pair(TLM_COLOUR_HDR, COLOR_YELLOW, COLOR_BLACK); 
      init_pair(TLM_COLOUR_CLK, COLOR_RED, COLOR_BLACK); /* also QTH */
      init_pair(TLM_COLOUR_NOM, COLOR_WHITE, COLOR_BLACK);
      init_pair(TLM_COLOUR_STATIC, COLOR_BLACK, COLOR_CYAN);
      init_pair(TLM_COLOUR_DERIVED, COLOR_BLUE, COLOR_BLACK);   
      init_pair(TLM_COLOUR_INVIS, COLOR_BLACK, COLOR_BLACK); 
   }

   /* Create the clock, header, location, and binary windows. */
   /* Also create their borders */

   screen->hdr_win=newwin(5,25,0,28);
   screen->clk_win=newwin(5,29,0,0);
   screen->qth_win=newwin(5,28,0,52);
   screen->bin_win=newwin(5,80,19,0);

   wborder(screen->hdr_win,0,0,0,0,ACS_TTEE,ACS_TTEE,ACS_BTEE,ACS_BTEE);
   wborder(screen->clk_win,0,0,0,0,0,ACS_TTEE,ACS_LTEE,ACS_BTEE);
   wborder(screen->qth_win,0,0,0,0,ACS_TTEE,0,ACS_BTEE,ACS_RTEE);
   wborder(screen->bin_win,0,0,0,0,ACS_LTEE,ACS_RTEE,0,0);

   /* Setup non standard colours */

   if (has_colors() == TRUE)
   {
      wattrset(screen->hdr_win,COLOR_PAIR(TLM_COLOUR_HDR));
      wattrset(screen->clk_win,COLOR_PAIR(TLM_COLOUR_CLK));
      wattrset(screen->qth_win,COLOR_PAIR(TLM_COLOUR_QTH));
   }

   /* Now create the actual telemetry windows and panels, and border them */
   /* Also add the header line, to save another for loop */

   for (i=0; i<sat->tlmviews; i++)
   {
      screen->tlm_win[i]=newwin(15,80,5,0);
      screen->tlm_pan[i]=new_panel(screen->tlm_win[i]);
      wborder(screen->tlm_win[i],ACS_VLINE,ACS_VLINE,' ',ACS_HLINE,ACS_VLINE,ACS_VLINE,ACS_LTEE,ACS_RTEE);
      mvwprintw(screen->tlm_win[i],0,((80-strlen(sat->tlmhdr[i]))/2),sat->tlmhdr[i]);
   } 

   /* Setup Any Window Headers */

   strcpy(hdr_gen_txt,"APRS TELEMETRY VIEWER");
   mvwprintw(screen->hdr_win,2,((25-strlen(hdr_gen_txt))/2),hdr_gen_txt);
   mvwprintw(screen->hdr_win,1,((25-strlen(sat->label))/2),sat->label);


   if (sat->frametypes>0)
      mvwprintw(screen->tlm_win[0],2,1,"FRAME T#NNN CH1 CH2 CH3 CH4 CH5 CMD BITS SF Z     PACKET RECIEVED DATE");
   else
      mvwprintw(screen->tlm_win[0],2,24,"T#nnn --- --- --- --- --- CMD-BITS");

   /* Display the tlm labels */

   if (sat->frametypes==0)
      tlmwin=0;
   else
      tlmwin=1;

   for (i=0; i<=sat->frametypes; i++)
   {
      if (i<=3)
         w=0;
      else
         w=2;

      for (j=0; j<=4; j++)
      {
         mvwprintw(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j],"%s",tlmframe[i].lbl[j]);

         switch(tlmframe[i].valtype[j])
         {
            case TLM_VAL_TYPE_VOLT:
               mvwprintw(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+15,"V S");
               break;
            case TLM_VAL_TYPE_CURR:
               mvwprintw(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+14,"mA S");
               break;
            case TLM_VAL_TYPE_TEMP:
               mvwprintw(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+15,"C S");
               mvwaddch(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+14,ACS_DEGREE);
               break;
            case TLM_VAL_TYPE_TEMP_SHORTLBL:
               mvwprintw(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+15,"C S");
               mvwaddch(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+14,ACS_DEGREE);
               mvwaddch(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+6,ACS_DEGREE);
               break;
            case TLM_VAL_TYPE_WATT:
               mvwprintw(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+15,"W S");
               break;
            case TLM_VAL_TYPE_RAW:
               mvwprintw(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+15,"  S");
               break;

         }
         mvwchgat(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+17,1,A_NORMAL,TLM_COLOUR_INVIS,NULL);
      }

      if (sat->frametypes!=0)
      {
         mvwprintw(screen->tlm_win[0],3+w+i,78,"S");
         mvwchgat(screen->tlm_win[0],3+w+i,78,1,A_NORMAL,TLM_COLOUR_INVIS,NULL);
      }
      else
      {
         mvwprintw(screen->tlm_win[0],0,26,"S");
         mvwchgat(screen->tlm_win[0],0,26,1,A_NORMAL,TLM_COLOUR_INVIS,NULL);
         mvwprintw(screen->tlm_win[0],2,59,"S");
         mvwchgat(screen->tlm_win[0],2,59,1,A_NORMAL,TLM_COLOUR_INVIS,NULL);
      }
   }
   
   /* Setup cmd bits strings */

   for (i=0; i<=11; i++)
   {
      mvwprintw(screen->bin_win,sat->cmdloc[0][i],sat->cmdloc[1][i],sat->cmdstring[i]);
      mvwprintw(screen->bin_win,sat->cmdloc[0][i],(sat->cmdloc[1][i])+15,"S"); 
      mvwchgat(screen->bin_win,sat->cmdloc[0][i],sat->cmdloc[1][i],17,A_NORMAL,TLM_COLOUR_INVIS,NULL); 
   }

   /* Set raw view to be the default */

   screen->curtlmview=0;
   show_panel(screen->tlm_pan[screen->curtlmview]);
}
