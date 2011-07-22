#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include <panel.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <math.h>

#include "../include/aprstlm.h"
#include "../include/aprstlm-ncurses.h"
#include "../include/aprstlm-sockets.h"

int main(int argc, char **argv)
{

   int argp;				/* Arg pointer */
   struct winstruct screen;		/* All our ncurses windows */	
   struct satstruct sat;		/* Not strictly needed for aprstlm */
					/* as we are single sat, but aprsrrd */
					/* is multisat, as future code maybe */
					/* as well */
   struct predsatstruct predsat;	/* Predict Satellite Structure */
   struct tlmframestruct tlmframe[8];	/* Space for all our tlm frames */
   sat.statictime=300;			/* Set Default Static Time */

   int selsat;				/* Selected Satellite */

   int keypress=0;  			/* Incoming keypress */

   extern char *tzname[2];		/* Timezone for gettimeofday call */
   struct timeval epochtime;		/* Current time since the epoch */
   struct timezone epochtz;		/* Current Timezone */

   char mycall[10];			/* Callsign to send to aprs server */

   bool preden=FALSE;			/* Predict Enabled ? */
   bool predever=FALSE;			/* Predict Ever Enabled ? */
   char predhost[256];			/* Predict Host */
   char predport[6];			/* Predict Port */
   int predsock;			/* Predict Socket */
   int predstat;			/* Predict Call Status */
   char predbuf[MAX_UDP_BUF];		/* Predict Buffer */

   struct pollfd predpoll;		/* Predict Poll */
   struct pollfd aprspoll;		/* APRS Poll */

   bool use_stdin=FALSE;		/* Do we want to read from stdin ? */
   char aprshost[256];			/* APRS Host */
   char aprsport[6];			/* APRS Port */
   int aprssock;			/* APRS Socket */

   char aprsbuf[MAX_TCP_BUF];		/* APRS Buffer */
   char aprsout[MAX_TCP_BUF];		/* APRS Outbound Buffer */

   char aprschar;			/* APRS Character */
   int aprscount;			/* APRS Counter */
   int aprsstat;			/* APRS Status */

   char satside=' ';			/* Which Side of the Satellite */
   char tlmpkt[256];			/* The Telemetry Packet */
   int frameno;				/* Frame in the aprs stream */
   int tmpframeno;

   int datefmt=0;			/* TLM Date Format in raw tlm win */   
   int tmpdatefmt=0;			/* TLM Date Format in raw tlm win */   
   int i;				/* Loop Counter */

   strcpy(mycall,"NOCALL");

   sat.extrabits=FALSE;			/* Assume Not, Set in xxxxx_setup() */
   sat.extrancurses=FALSE;
   sat.extradecode=FALSE;
   sat.extradisplay=FALSE;
   sat.extrastatic=FALSE;

   /* Parse Command Arguments, and setup sat structure */

   if (argc==1)
   {
      printf("Usage:\n\n");
      printf("-sat <sat> \t\t Satellite or Device to Monitor\n");
      printf("-mycall <sat> \t\t Callsign to send to the APRS Server\n");
      printf("-aprs <host> <port> \t APRS Host and Port to Connect to\n");
      printf("-pred <host> <port> \t Predict Host and Port to Connect to\n");
      exit(1);
   }
   for (argp=0; argp<argc; argp++)
   {
      /* Show Version */
      if (strcmp(argv[argp],"-v")==0)
      {
         fprintf(stdout,"aprstlm version :%s\n",APRSTLMVER);
         exit(0);
      }

      /* Which Satellite Do We Want To Monitor ? */
      if (strcmp(argv[argp],"-sat")==0)
      {
         argp++;
         strcpy(sat.label,argv[argp]);

         if (strcmp(sat.label,"PCSAT")==0)
         {
            selsat=SAT_PCSAT;
            pcsat_setup(&sat,&tlmframe);
         }

         if (strcmp(sat.label,"PCSAT2")==0)
         {
            selsat=SAT_PCSAT2;
            pcsat2_setup(&sat,&tlmframe);
         }

         if (strcmp(sat.label,"MIMMODULE")==0)
         {
            selsat=SAT_MIMMODULE;
            mim_setup(&sat,&tlmframe);
         }

         if (strcmp(sat.label,"RAFT")==0)
         {
            selsat=SAT_RAFT;
            raft_setup(&sat,&tlmframe);
         }

         if (strcmp(sat.label,"ANDE")==0)
         {
            selsat=SAT_ANDE;
            ande_setup(&sat,&tlmframe);
         }

         if (strcmp(sat.label,"CASTOR")==0)
         {
            selsat=SAT_CASTOR;
            castor_setup(&sat,&tlmframe);
         }
         if (strcmp(sat.label,"POLLUX")==0)
         {
            selsat=SAT_POLLUX;
            pollux_setup(&sat,&tlmframe);
         }
      }

      /* If we are using the MIM Module, check for mimcall */
      if (selsat==SAT_MIMMODULE)
      {
         if (strcmp(argv[argp],"-mimcall")==0)
         {
            argp++;
            strcpy(sat.asidecall[0],argv[argp]);
            sat.asidecalls=1;
            sat.bsidecalls=0;
         }
      }

      /* Which Predict Server do we want to use ? */
      if (strcmp(argv[argp],"-pred")==0)
      {
         argp++;
         strcpy(predhost,argv[argp]);
         argp++;
         strcpy(predport,argv[argp]);
         preden=TRUE;
         predever=TRUE;
      }

      /* Which APRS Server do we want to use ? */
      if (strcmp(argv[argp],"-aprs")==0)
      {
         argp++;
         strcpy(aprshost,argv[argp]);
         argp++;
         strcpy(aprsport,argv[argp]);
      }

      /* Or should we read from stdin ? Note, overrides -aprs */
      if (strcmp(argv[argp],"-stdin")==0)
      {
         use_stdin=TRUE;
      }

      /* My Call */

      if (strcmp(argv[argp],"-mycall")==0)
      {
         argp++;
         strcpy(mycall,argv[argp]);
      }
   }


   ncurses_setup(&screen,&sat,&tlmframe);   /* Initial ncurses screen setup  */

   if (sat.extrancurses)
   {
      switch(selsat)
      {
         case SAT_PCSAT:
            pcsat_extra_ncurses(&screen,&sat,&tlmframe);
            break;
         case SAT_PCSAT2:
            pcsat2_extra_ncurses(&screen,&sat,&tlmframe);
            break;
         case SAT_MIMMODULE:
            mim_extra_ncurses(&screen,&sat,&tlmframe);
            break;
         case SAT_RAFT:
            raft_extra_ncurses(&screen,&sat,&tlmframe);
            break;
         case SAT_CASTOR:
            castor_extra_ncurses(&screen);
            break;
         case SAT_POLLUX:
            pollux_extra_ncurses(&screen);
            break;
      }
   }
   /* Setup sockets */

   if (sat.norad==0)
      preden=0;

   if (preden)
   {
      predsock=connect_client(predhost,predport,AF_UNSPEC, SOCK_DGRAM);
      if (predsock==-1)
         preden=FALSE;
   }

   if (preden)
   {
      predpoll.fd=predsock;
      predpoll.events=POLLIN;
   }

   if (!use_stdin)
   {
      aprssock=connect_client(aprshost,aprsport,AF_UNSPEC, SOCK_STREAM);
      if (aprssock==-1)
      {
         endwin();
         printf("Couldnt Connect to APRS Server. Exiting.\n");
         exit(1);
      }


      /* Construct Outbound Registration/Filter Message */

      strcpy(aprsout,"USER ");
      strcat(aprsout,mycall);
      strcat(aprsout," PASS -1 vers aprstlm v");
      strcat(aprsout,APRSTLMVER);
      strcat(aprsout," filter p");

      for (i=0; i<=sat.asidecalls-1; i++)
      {
         strcat(aprsout,"/");
         strncat(aprsout,sat.asidecall[i],(strlen(sat.asidecall[i])-1));
      }
      for (i=0; i<=sat.bsidecalls-1; i++)
      {
         strcat(aprsout,"/");
         strncat(aprsout,sat.bsidecall[i],(strlen(sat.bsidecall[i])-1));
      }
      strcat(aprsout,"\n");

      write(aprssock,aprsout,strlen(aprsout));
   }
   else
   {
       aprssock=0;	/* stdin */
   } 
      aprspoll.fd=aprssock;
      aprspoll.events=POLLIN;
      aprscount=0;

   aprsstat=read(aprssock,&aprschar,1);

   if (!use_stdin)
      keypress=getch();

   while ((keypress!='q') && (keypress!='Q'))
   {
      /* Handle Keyboard */
      tmpdatefmt=datefmt;
      if (!use_stdin)
          datefmt=generic_keyboard(&screen,keypress,tmpdatefmt,sat.tlmviews);
      update_panels();
      doupdate();

      /* Get Predict Data if needed */
      if (preden)
      {
         strcpy(predbuf,"GET_SAT ");
         strcat(predbuf,sat.norad);
         strcat(predbuf,"\n");

         predstat = write(predsock,&predbuf,sizeof(predbuf));

         if (predstat==-1)
            preden=FALSE;
      }
      if (preden)
      {
         memset(predbuf,0,sizeof(predbuf));
         if (poll(&predpoll,1,100)>=1)
            predstat = read(predsock,predbuf,sizeof(predbuf));
         else
            predstat=-1;

         if (predstat==-1)
            preden=FALSE;
      }

      if (preden)
      {
         predbuf[predstat] = 0;
         sscanf(predbuf,"%s%f%f%f%f%f%f%f%f%f%f%f%f%f%f",predsat.satname,&predsat.longitude,&predsat.latitude,&predsat.az,&predsat.el,&predsat.aos,&predsat.footprint,&predsat.range,&predsat.altitude,&predsat.velocity,&predsat.orbit,&predsat.visibility,&predsat.phase,&predsat.eclipse,&predsat.squint);

         predsat.birdew=FALSE;
         if (predsat.longitude<180.0)
         {
            predsat.birdew=TRUE;
            predsat.longitude=-predsat.longitude;
            predsat.longitude=predsat.longitude*(-1);
         }
         else if (predsat.longitude>180.0)
            predsat.longitude=360.0-predsat.longitude;

         predsat.birdns=FALSE;
         if (predsat.latitude<0.0)
         {
            predsat.birdns=TRUE;
            predsat.latitude=predsat.latitude*(-1);
         }
      }

      /* Update Clock and QTH Windows [ncurses_clkqth()] */
      gettimeofday(&epochtime, &epochtz);

      generic_clkqth(&screen, &sat, &tlmframe, &epochtime, &predsat, preden, datefmt); 

      if (poll(&aprspoll,1,100)>=1)
      {
         aprsstat=read(aprssock,&aprschar,1);
         if ((aprschar!=10) && (aprschar!=13))
         {
            aprsbuf[aprscount]=aprschar;
            aprscount++;
         }
      }

      
      if (((aprschar==10) || (aprschar==13))&& (aprscount!=0))
      {
         if (!sat.nogendetect)
         {
            frameno=detect_tlm_pkt(&aprsbuf,aprscount, &sat, &tlmpkt); 
         }
         if ((sat.extradetect) && (frameno!=99))
         {
            tmpframeno=frameno;
            switch(selsat)
            {
               case SAT_PCSAT:
                  frameno=pcsat_extra_detect(&aprsbuf,aprscount, &sat, &tlmpkt,frameno); 
                  break;
               case SAT_PCSAT2:
                  frameno=pcsat2_extra_detect(&aprsbuf,aprscount, &sat, &tlmpkt,frameno); 
                  break;
               case SAT_MIMMODULE:
                  frameno=mim_extra_detect(&aprsbuf,aprscount, &sat, &tlmframe, &screen, frameno); 
               case SAT_ANDE:
                  frameno=ande_extra_detect(&aprsbuf,aprscount, &sat, &tlmpkt); 
                  break;
               case SAT_CASTOR:
                  frameno=castor_extra_detect(&aprsbuf,aprscount, &sat, &tlmpkt); 
                  break;
               case SAT_POLLUX:
                  frameno=pollux_extra_detect(&aprsbuf,aprscount, &sat, &tlmpkt); 
                  break;
            }
         }

         if (frameno!=99)
         {
            if (!sat.nogendecode)
            {
               decode_tlm_pkt(tlmpkt, &sat, &tlmframe,frameno); 
            }
            if (sat.extradecode)
            {
               switch(selsat)
               {
                  case SAT_PCSAT:
                     pcsat_extra_decode(&aprsbuf,aprscount, &sat, &tlmpkt); 
                     break;
                  case SAT_PCSAT2:
                     pcsat2_extra_decode(&aprsbuf,aprscount, &sat, &tlmpkt); 
                     break;
                  case SAT_MIMMODULE:
                     mim_extra_decode(&aprsbuf,aprscount, &sat, &tlmpkt); 
                     break;
                  case SAT_CASTOR:
                     castor_extra_decode(&aprsbuf,aprscount, &sat, &tlmpkt, &tlmframe);
                     break;
                  case SAT_POLLUX:
                     pollux_extra_decode(&aprsbuf,aprscount, &sat, &tlmpkt, &tlmframe);
                     break;
               }
            }
         }
         aprscount=0;
         memset(aprsbuf,0,sizeof(aprsbuf));
      }

      if (!sat.nogendisplay)
         generic_display(&tlmframe,&sat,&screen);

      if (sat.extradisplay)
      {
         switch(selsat)
         {
            case SAT_PCSAT:
               pcsat_extra_display(&tlmframe,&sat,&screen);
               break;
            case SAT_PCSAT2:
               pcsat2_extra_display(&tlmframe,&sat,&screen);
               break;
            case SAT_MIMMODULE:
               mim_extra_display(&tlmframe,&sat,&screen);
               break;
            case SAT_RAFT:
               raft_extra_display(&tlmframe,&sat,&screen);
               break;
         }
      }
      generic_static(&tlmframe,&sat,&screen);
      if (sat.extrastatic)
      {
         switch(selsat)
         {
            case SAT_PCSAT:
               pcsat_extra_static(&tlmframe,&sat,&screen);
               break;
            case SAT_PCSAT2:
               pcsat2_extra_static(&tlmframe,&sat,&screen);
               break;
         }
      }

      touchwin(screen.hdr_win);
      touchwin(screen.clk_win);
      touchwin(screen.qth_win);
      touchwin(screen.bin_win);

      /* FIXME: USE A BLEEDING LOOP!! */
      
      touchwin(screen.tlm_win[0]);
/*      touchwin(screen.tlm_win[1]); */

      wrefresh(screen.hdr_win);
      wrefresh(screen.clk_win);
      wrefresh(screen.qth_win);
      wrefresh(screen.bin_win); 
      if (!use_stdin)
         keypress=getch();

      if ((predever) && (!preden))
      {
         close(predsock);
         preden=TRUE;
         predsock=connect_client(predhost,predport,AF_UNSPEC, SOCK_DGRAM);
         if (predsock==-1)
            preden=FALSE;

         if (preden)
         {
            predpoll.fd=predsock;
            predpoll.events=POLLIN;

            mvwprintw(screen.qth_win,2,1,"                          ");
         }
      }
   }
   endwin();
}
