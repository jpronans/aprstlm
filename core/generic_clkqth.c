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

void generic_clkqth(struct winstruct *screen, struct satstruct *sat,
                 struct tlmframestruct *tlmframe, struct timeval *epochtime,
		 struct predsatstruct *predsat, bool preden,int datefmt)
{

   extern char *tzname[2];		/* Timezone */
   struct tm tmzulu,tmlocal;		/* Time Structures for zulu and */
                                        /* local times */
   struct tm tlmzulu,tlmlocal;		/* Time Structures for telemetry */
                                        /* for both zulu and local times */

   struct timeval elapsedtime;		/* Elapsed Time */

   struct met_tv met;			/* Structure for MET */
   struct met_tv tlmmet;		/* Structure for MET for tlm frame */
   struct met_tv tlmelp;		/* Structure for Elapsed tlm time */

   char nsind, ewind;			/* N/S and E/W Indicators */

   int i,w;

   gmtime_r(&epochtime->tv_sec,&tmzulu);
   localtime_r(&epochtime->tv_sec,&tmlocal);


   /* UTC and LCL Clocks Update */

   mvwprintw(screen->clk_win,1,3,"%4d/%02d/%02d %02d:%02d:%02d UTC",(tmzulu.tm_year+1900),(tmzulu.tm_mon+1),tmzulu.tm_mday,tmzulu.tm_hour,tmzulu.tm_min,tmzulu.tm_sec);

   if (tmlocal.tm_isdst==0)
      mvwprintw(screen->clk_win,2,3,"%4d/%02d/%02d %02d:%02d:%02d %s",(tmlocal.tm_year+1900),(tmlocal.tm_mon+1),tmlocal.tm_mday,tmlocal.tm_hour,tmlocal.tm_min,tmlocal.tm_sec,tzname[0]);
   else
      mvwprintw(screen->clk_win,2,3,"%4d/%02d/%02d %02d:%02d:%02d %s",(tmlocal.tm_year+1900),(tmlocal.tm_mon+1),tmlocal.tm_mday,tmlocal.tm_hour,tmlocal.tm_min,tmlocal.tm_sec,tzname[1]);

   met.birdmet=difftime(epochtime->tv_sec,sat->epoch);

   met.metdays=met.birdmet/86400.0;

   met.birdmet=met.birdmet-(met.metdays*86400.0);
   met.methours=met.birdmet/3600.0;
        
   met.birdmet=met.birdmet-(met.methours*3600.0);
   met.metmins=met.birdmet/60.0;

   met.birdmet=met.birdmet-(met.metmins*60.0);
   met.metsecs=met.birdmet;

   for (i=0; i<=sat->frametypes; i++)
   {
      if (i<=3)
         w=0;
      else
         w=2;
  
      if (tlmframe[i].rxtime.tv_sec!=0)
      {
         gmtime_r(&tlmframe[i].rxtime.tv_sec,&tlmzulu);
         localtime_r(&tlmframe[i].rxtime.tv_sec,&tlmlocal); 
         tlmframe[i].deltatime=difftime(epochtime->tv_sec,tlmframe[i].rxtime.tv_sec);
         switch(datefmt)
         {
            case 0:
               if (sat->frametypes!=0)
                  mvwprintw(screen->tlm_win[0],3+w+i,49,"%4d/%02d/%02d %02d:%02d:%02d UTC",(tlmzulu.tm_year+1900),(tlmzulu.tm_mon+1),tlmzulu.tm_mday,tlmzulu.tm_hour,tlmzulu.tm_min,tlmzulu.tm_sec);
               else
                  mvwprintw(screen->tlm_win[0],0,1,"%4d/%02d/%02d %02d:%02d:%02d UTC",(tlmzulu.tm_year+1900),(tlmzulu.tm_mon+1),tlmzulu.tm_mday,tlmzulu.tm_hour,tlmzulu.tm_min,tlmzulu.tm_sec);

               break;
            case 1:
               if (sat->frametypes!=0)
               {
                  if (tmlocal.tm_isdst==0)
                     mvwprintw(screen->tlm_win[0],3+w+i,49,"%4d/%02d/%02d %02d:%02d:%02d %s",(tlmlocal.tm_year+1900),(tlmlocal.tm_mon+1),tlmlocal.tm_mday,tlmlocal.tm_hour,tlmlocal.tm_min,tlmlocal.tm_sec,tzname[0]);
                  else
                     mvwprintw(screen->tlm_win[0],3+w+i,49,"%4d/%02d/%02d %02d:%02d:%02d %s",(tlmlocal.tm_year+1900),(tlmlocal.tm_mon+1),tlmlocal.tm_mday,tlmlocal.tm_hour,tlmlocal.tm_min,tlmlocal.tm_sec,tzname[1]);
               } 
               else
               {
                  if (tmlocal.tm_isdst==0)
                     mvwprintw(screen->tlm_win[0],0,1,"%4d/%02d/%02d %02d:%02d:%02d %s",(tlmlocal.tm_year+1900),(tlmlocal.tm_mon+1),tlmlocal.tm_mday,tlmlocal.tm_hour,tlmlocal.tm_min,tlmlocal.tm_sec,tzname[0]);
                 else 
                     mvwprintw(screen->tlm_win[0],0,1,"%4d/%02d/%02d %02d:%02d:%02d %s",(tlmlocal.tm_year+1900),(tlmlocal.tm_mon+1),tlmlocal.tm_mday,tlmlocal.tm_hour,tlmlocal.tm_min,tlmlocal.tm_sec,tzname[1]);
               }
               break;
            case 2:
               tlmmet.birdmet=difftime(tlmframe[i].rxtime.tv_sec,sat->epoch);
               tlmmet.metdays=tlmmet.birdmet/86400.0;

               tlmmet.birdmet=tlmmet.birdmet-(tlmmet.metdays*86400.0);
               tlmmet.methours=tlmmet.birdmet/3600.0;
        
               tlmmet.birdmet=tlmmet.birdmet-(tlmmet.methours*3600.0);
               tlmmet.metmins=tlmmet.birdmet/60.0;

               tlmmet.birdmet=tlmmet.birdmet-(tlmmet.metmins*60.0);
               tlmmet.metsecs=tlmmet.birdmet;

               if (preden)
                  mvwprintw(screen->tlm_win[0],3+w+i,49,"%05d/%04d %02d:%02d:%02d MET",(int)predsat->orbit,(int)tlmmet.metdays,(int)tlmmet.methours,(int)tlmmet.metmins,(int)tlmmet.metsecs);
               else
               {
                  if (sat->frametypes!=0)
                     mvwprintw(screen->tlm_win[0],3+w+i,49,"-----/%04d %02d:%02d:%02d MET",(int)tlmmet.metdays,(int)tlmmet.methours,(int)tlmmet.metmins,(int)tlmmet.metsecs);
                  else
                     mvwprintw(screen->tlm_win[0],0,1,"-----/%04d %02d:%02d:%02d MET",(int)tlmmet.metdays,(int)tlmmet.methours,(int)tlmmet.metmins,(int)tlmmet.metsecs);
               }
               break;

            case 3: 
               tlmelp.birdmet=difftime(epochtime->tv_sec,tlmframe[i].rxtime.tv_sec);
               tlmelp.metdays=tlmelp.birdmet/86400.0;

               tlmelp.birdmet=tlmelp.birdmet-(tlmelp.metdays*86400.0);
               tlmelp.methours=tlmelp.birdmet/3600.0;
        
               tlmelp.birdmet=tlmelp.birdmet-(tlmelp.methours*3600.0);
               tlmelp.metmins=tlmelp.birdmet/60.0;

               tlmelp.birdmet=tlmelp.birdmet-(tlmelp.metmins*60.0);
               tlmelp.metsecs=tlmelp.birdmet;

               if (sat->frametypes!=0)
                  mvwprintw(screen->tlm_win[0],3+w+i,49,"    T+%d Days %02d:%02d:%02d   ",tlmelp.metdays,tlmelp.methours,tlmelp.metmins,tlmelp.metsecs);
               else
                  mvwprintw(screen->tlm_win[0],0,1,"    T+%d Days %02d:%02d:%02d   ",tlmelp.metdays,tlmelp.methours,tlmelp.metmins,tlmelp.metsecs);

               break;
         }
         if (i>3)
            w=2;
         else
            w=0;

      }
   }

   if (preden)
   {
      if (predsat->birdew)
         ewind='E';
      else
         ewind='W';

      if (predsat->birdns)
         nsind='S';
      else
         nsind='N';

      mvwprintw(screen->qth_win,1,3,"Long %2.2f%c  Lat %2.2f%c",predsat->longitude,ewind,predsat->latitude,nsind);
      mvwprintw(screen->qth_win,3,3,"Range %5.0fkm Ecl %2.2f",predsat->range,predsat->eclipse);
      mvwprintw(screen->clk_win,3,3,"%05d/%04d %02d:%02d:%02d MET",(int)predsat->orbit,(int)met.metdays,(int)met.methours,(int)met.metmins,(int)met.metsecs);
   }
   else
   {
      mvwprintw(screen->qth_win,1,1,"                          ");
      mvwprintw(screen->qth_win,2,1,"PREDICT SERVER UNAVAILABLE");
      mvwprintw(screen->qth_win,3,1,"                          ");
      mvwprintw(screen->clk_win,3,3,"-----/%04d %02d:%02d:%02d MET",(int)met.metdays,(int)met.methours,(int)met.metmins,(int)met.metsecs);
   }
}
