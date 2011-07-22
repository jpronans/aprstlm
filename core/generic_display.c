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

int generic_display(struct tlmframestruct *tlmframe, struct satstruct *sat, struct winstruct *screen)
{
   int i;				/* Loop Counter */
   int j;
   int k;

   int w;				/* B-Side vertical offset */

   int tlmwin;				/* 0=single frame sat, 1=multi */
                                        /* frame sat                   */
   char rawstring[77];
   char tmpvalstr[4];


   if (sat->frametypes!=0)
      tlmwin=1;
   else
      tlmwin=0;

   for (i=0; i<=sat->frametypes; i++)
   {
      if (tlmframe[i].rxtime.tv_sec!=0)
      {
         if (i<=3)
         {
            if (sat->bsidecalls!=0)
               strcpy(rawstring,"A-");
            else
               strcpy(rawstring,"F-");

            w=0;
         }
         else
         {
            strcpy(rawstring,"B-");
            w=2;
         }      
         if ((i==0) || (i==4))
            strcat(rawstring,"00");
         if ((i==1) || (i==5))
            strcat(rawstring,"01");
         if ((i==2) || (i==6))
            strcat(rawstring,"10");
         if ((i==3) || (i==7))
            strcat(rawstring,"11");

         if (sat->frametypes==0)
            strcpy(rawstring,"T#");
         else 
            strcat(rawstring,"  T#");

         sprintf(tmpvalstr,"%03d",tlmframe[i].framecount);
         
         strcat(rawstring,tmpvalstr);

         for (j=0; j<=4; j++)
         {
            strcat(rawstring," ");
            sprintf(tmpvalstr,"%03d",tlmframe[i].rawtlm[j]);
            strcat(rawstring,tmpvalstr);
         }

         strcat(rawstring," ");

         for (k=0; k<=7; k++)
         {
            if (tlmframe[i].cmdbits[k])
               strcat(rawstring,"1");
            else
               strcat(rawstring,"0");
         }

         if (sat->extrabits)
         {
            strcat(rawstring," ");

            for (k=0; k<=1; k++)
            {
               if (tlmframe[i].sbits[k])
                  strcat(rawstring,"1");
               else
                  strcat(rawstring,"0");
            }

            strcat(rawstring," ");

            if (tlmframe[i].endbit)
              strcat(rawstring,"1");
            else
              strcat(rawstring,"0");

         }
         if (sat->frametypes!=0)
            mvwprintw(screen->tlm_win[0],3+w+i,1,"%s",rawstring);
         else
            mvwprintw(screen->tlm_win[0],2,24,"%s",rawstring);


         for (j=0; j<=4; j++)
         {
            switch(tlmframe[i].valtype[j])
            {
/*
               case TLM_VAL_TYPE_NONE:
                  if (tlmframe[i].tlmval[j]<10.00)
                     mvwprintw(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+10,"%2.2f",tlmframe[i].tlmval[j]);
                  else
                     mvwprintw(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+9,"%2.2f",tlmframe[i].tlmval[j]);
                  break;
*/
               case TLM_VAL_TYPE_VOLT:
                  if (tlmframe[i].tlmval[j]<10.00)
                     mvwprintw(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+10,"%2.2f",tlmframe[i].tlmval[j]);
                  else
                     mvwprintw(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+9,"%2.2f",tlmframe[i].tlmval[j]);
                  break;
               case TLM_VAL_TYPE_TEMP:
                  if (tlmframe[i].tlmval[j]<10.00)
                     mvwprintw(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+10,"%2.2f",tlmframe[i].tlmval[j]);
                  else
                     mvwprintw(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+9,"%2.2f",tlmframe[i].tlmval[j]);

                  break;
               case TLM_VAL_TYPE_TEMP_SHORTLBL:
                  if (tlmframe[i].tlmval[j]<10.00)
                     mvwprintw(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+10,"%2.2f",tlmframe[i].tlmval[j]);
                  else
                     mvwprintw(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+9,"%2.2f",tlmframe[i].tlmval[j]);
                  break;
               case TLM_VAL_TYPE_CURR:
                  mvwprintw(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+9,"%4.0f",tlmframe[i].tlmval[j]);
                  break;
               case TLM_VAL_TYPE_WATT:
                  mvwprintw(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+9,"%2.2f",tlmframe[i].tlmval[j]);
                  break;
               case TLM_VAL_TYPE_RAW:
                 if (tlmframe[i].tlmval[j]<100.00)
                 {
                    if (tlmframe[i].tlmval[j]<10.00)
                       mvwprintw(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+12,"%3.0f",tlmframe[i].tlmval[j]);
                   else
                       mvwprintw(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+11,"%3.0f",tlmframe[i].tlmval[j]);
                 }
                 else
                 {
                       mvwprintw(screen->tlm_win[tlmwin],tlmframe[i].loc[0][j],tlmframe[i].loc[1][j]+10,"%3.0f",tlmframe[i].tlmval[j]);
                 } 
            }	
         }
         /* display command bits */
         for (j=0; j<=7; j++)
         {
              if (tlmframe[i].cmdbits[j])
                 mvwchgat(screen->bin_win,sat->cmdloc[0][j],sat->cmdloc[1][j],14,A_NORMAL,TLM_COLOUR_NOM,NULL);
              else
                 mvwchgat(screen->bin_win,sat->cmdloc[0][j],sat->cmdloc[1][j],14,A_REVERSE,TLM_COLOUR_NOM,NULL);
         }
      }
   }
}
