#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>
#include <panel.h>

#include "../include/aprstlm.h"
#include "../include/aprstlm-ncurses.h"

void pcsat2_setup(struct satstruct *sat,struct tlmframestruct *tlmframe)
{

   int i;				/* tlmframe Loop Counter   */
   int j;				/* Channel Loop Counter */

   /* Epoch is used to calculate the Mission Elapsed Time, norad   */
   /* is used by predict, Set to 0 if you know this device isn't   */
   /* a satellite, the code will disable the predict server if you */
   /* requested it */

   sat->epoch=1123067820;
   sprintf(sat->norad,"%d",25544);

   /* Setup what we want the "RAW TELEMETRY VALUES", and "ENGINEERING   */
   /* TELEMETRY VALUES" to display. Most of the time, the defaults will */
   /* suffice, but we might want specific labels for small satellites or */
   /* MIM/OPENTRACKER and friends. [0] is the raw screen, [1] is the */
   /* engineering screen if it exists */

   strcpy(sat->tlmhdr[0],"RAW TELEMETRY VALUES");
   strcpy(sat->tlmhdr[1],"ENGINEERING TELEMETRY VALUES");

   /* Callsigns that the bird uses */

   strcpy(sat->asidecall[0],"PCSAT2>");

   /* Note we must also tell aprstlm how many calls each side has. */
   /* This is used for loop control, during the detection code */

   sat->asidecalls=1;
   sat->bsidecalls=0;

   /* We also need to specify the total number of frame types minus */
   /* one. This includes both sides. For a per side value, add 1, then */
   /* divide by 2. For satellites with only one frametype (EG RAFT), set */
   /*  to 0, and  /* set sat->bsidecalls to 0, so you just use the a-side */

   sat->frametypes=3;
   sat->tlmviews=2;
   sat->extrabits=TRUE;

   for (i=0; i<=sat->frametypes; i++)
   {
      /* We MUST initialise these to zero, else the display code */
      /* will get very very confused                             */

      tlmframe[i].rxtime.tv_sec=0;
      tlmframe[i].rxtime.tv_usec=0;
   }

   /* Setup The Telemetry Labels. Note they should be 10 Chars long */
   /* set the valtype to TLM_VAL_TYPE_NONE if you dont want any suffix */
   /* after the value. If you do this, you probably want to define your */
   /* own extra display function */

   /* loc[0][n] is the Y position of the label, loc[1][n] is the X */
   /* position, as per ncurses. The DEFINEs here are just for ease,*/
   /* the actual value is an int. */
 
   strcpy(tlmframe[0].lbl[0],"RXA Cur :");
   tlmframe[0].valtype[0]=TLM_VAL_TYPE_CURR;
   tlmframe[0].loc[0][0]=2;
   tlmframe[0].loc[1][0]=TLM_ENG_COL_3;

   strcpy(tlmframe[0].lbl[1],"RXB Cur :");
   tlmframe[0].valtype[1]=TLM_VAL_TYPE_CURR;
   tlmframe[0].loc[0][1]=3;
   tlmframe[0].loc[1][1]=TLM_ENG_COL_3;

   strcpy(tlmframe[0].lbl[2],"Cell 3  :");
   tlmframe[0].valtype[2]=TLM_VAL_TYPE_VOLT;
   tlmframe[0].loc[0][2]=4;
   tlmframe[0].loc[1][2]=TLM_ENG_COL_1;

   strcpy(tlmframe[0].lbl[3],"TNC A mA:");
   tlmframe[0].valtype[3]=TLM_VAL_TYPE_CURR;
   tlmframe[0].loc[0][3]=5;
   tlmframe[0].loc[1][3]=TLM_ENG_COL_2;

   strcpy(tlmframe[0].lbl[4],"TNC B mA:");
   tlmframe[0].valtype[4]=TLM_VAL_TYPE_CURR;
   tlmframe[0].loc[0][4]=6;
   tlmframe[0].loc[1][4]=TLM_ENG_COL_2;

   strcpy(tlmframe[1].lbl[0],"Bat Temp:");
   tlmframe[1].valtype[0]=TLM_VAL_TYPE_TEMP;
   tlmframe[1].loc[0][0]=3;
   tlmframe[1].loc[1][0]=TLM_ENG_COL_4;

   strcpy(tlmframe[1].lbl[1],"PEC Temp:");
   tlmframe[1].valtype[1]=TLM_VAL_TYPE_TEMP;
   tlmframe[1].loc[0][1]=6;
   tlmframe[1].loc[1][1]=TLM_ENG_COL_3;

   strcpy(tlmframe[1].lbl[2],"TXA Curr:");
   tlmframe[1].valtype[2]=TLM_VAL_TYPE_CURR;
   tlmframe[1].loc[0][2]=4;
   tlmframe[1].loc[1][2]=TLM_ENG_COL_3;

   strcpy(tlmframe[1].lbl[3],"TXB Curr:");
   tlmframe[1].valtype[3]=TLM_VAL_TYPE_CURR;
   tlmframe[1].loc[0][3]=5;
   tlmframe[1].loc[1][3]=TLM_ENG_COL_3;

   strcpy(tlmframe[1].lbl[4],"Cell 1  :");
   tlmframe[1].valtype[4]=TLM_VAL_TYPE_VOLT;
   tlmframe[1].loc[0][4]=2;
   tlmframe[1].loc[1][4]=TLM_ENG_COL_1;

   strcpy(tlmframe[2].lbl[0],"TXA Temp:");
   tlmframe[2].valtype[0]=TLM_VAL_TYPE_TEMP;
   tlmframe[2].loc[0][0]=4;
   tlmframe[2].loc[1][0]=TLM_ENG_COL_4;

   strcpy(tlmframe[2].lbl[1],"TXB Temp:");
   tlmframe[2].valtype[1]=TLM_VAL_TYPE_TEMP;
   tlmframe[2].loc[0][1]=5;
   tlmframe[2].loc[1][1]=TLM_ENG_COL_4;

   strcpy(tlmframe[2].lbl[2],"Cell 2  :");
   tlmframe[2].valtype[2]=TLM_VAL_TYPE_VOLT;
   tlmframe[2].loc[0][2]=3;
   tlmframe[2].loc[1][2]=TLM_ENG_COL_1;

   strcpy(tlmframe[2].lbl[3],"RX Temp :");
   tlmframe[2].valtype[3]=TLM_VAL_TYPE_TEMP;
   tlmframe[2].loc[0][3]=2;
   tlmframe[2].loc[1][3]=TLM_ENG_COL_4;

   strcpy(tlmframe[2].lbl[4],"TLM Temp:");
   tlmframe[2].valtype[4]=TLM_VAL_TYPE_TEMP;
   tlmframe[2].loc[0][4]=6;
   tlmframe[2].loc[1][4]=TLM_ENG_COL_4;

   strcpy(tlmframe[3].lbl[0],"Batt V  :");
   tlmframe[3].valtype[0]=TLM_VAL_TYPE_VOLT;
   tlmframe[3].loc[0][0]=5;
   tlmframe[3].loc[1][0]=TLM_ENG_COL_1;

   strcpy(tlmframe[3].lbl[1],"Batt Cur:");
   tlmframe[3].valtype[1]=TLM_VAL_TYPE_CURR;
   tlmframe[3].loc[0][1]=3;
   tlmframe[3].loc[1][1]=TLM_ENG_COL_2;

   strcpy(tlmframe[3].lbl[2],"Load Cur:");
   tlmframe[3].valtype[2]=TLM_VAL_TYPE_CURR;
   tlmframe[3].loc[0][2]=2;
   tlmframe[3].loc[1][2]=TLM_ENG_COL_2;

   strcpy(tlmframe[3].lbl[3],"Sol Curr:");
   tlmframe[3].valtype[3]=TLM_VAL_TYPE_CURR;
   tlmframe[3].loc[0][3]=4;
   tlmframe[3].loc[1][3]=TLM_ENG_COL_2;

   strcpy(tlmframe[3].lbl[4],"5V Ref A:");
   tlmframe[3].valtype[4]=TLM_VAL_TYPE_VOLT;
   tlmframe[3].loc[0][4]=6;
   tlmframe[3].loc[1][4]=TLM_ENG_COL_1;

   /* setup the quadratic equations */

   /* These values get used in the quadratic equation: */
   /* y=A*(x^3) + B*(x^2) + (C*x) + D */

   /* Each a, b, c, and d value *MUST* be set. This example */
   /* just uses for loops because large amounts of the values */
   /* are zero, or the same value, and its easier just to set */
   /* the odd ones to zero, then reassign later */

   for (i=0; i<=sat->frametypes; i++)
   {
      for (j=0; j<=3; j++)
      {
         tlmframe[i].a[j]=0.0;
         tlmframe[i].b[j]=0.0;
         tlmframe[i].c[j]=0.0;
         tlmframe[i].d[j]=0.0;
      }
   }

   tlmframe[0].c[0]=2.00;
   tlmframe[0].c[1]=2.00;
   tlmframe[0].c[2]=0.0498;
   tlmframe[0].c[3]=2.00;
   tlmframe[0].c[4]=2.00;

   tlmframe[1].a[0]=0.00001;
   tlmframe[1].a[1]=0.00001;

   tlmframe[1].b[0]=-0.0034;
   tlmframe[1].b[1]=-0.0034;

   tlmframe[1].c[0]=0.7134;
   tlmframe[1].c[1]=0.7134;
   tlmframe[1].c[2]=5.0;
   tlmframe[1].c[3]=5.0;
   tlmframe[1].c[4]=0.0504;

   tlmframe[1].d[0]=-33.49;
   tlmframe[1].d[1]=-33.49;
   tlmframe[1].d[2]=-5.0;

   tlmframe[2].a[0]=0.00001;
   tlmframe[2].a[1]=0.00001;
   tlmframe[2].a[3]=0.00001;
   tlmframe[2].a[4]=0.00001;

   tlmframe[2].b[0]=-0.0034;
   tlmframe[2].b[1]=-0.0034;
   tlmframe[2].b[3]=-0.0034;
   tlmframe[2].b[4]=-0.0034;

   tlmframe[2].c[0]=0.7134;
   tlmframe[2].c[1]=0.7134;
   tlmframe[2].c[2]=0.0500;
   tlmframe[2].c[3]=0.7134;
   tlmframe[2].c[4]=0.7134;

   tlmframe[2].d[0]=-33.49;
   tlmframe[2].d[1]=-33.49;
   tlmframe[2].d[3]=-33.49;
   tlmframe[2].d[4]=-33.49;

   tlmframe[3].c[0]=0.1;
   tlmframe[3].c[1]=-22.44;
   tlmframe[3].c[2]=15.43;
   tlmframe[3].c[3]=7.843;
   tlmframe[3].c[4]=0.0235;

   tlmframe[3].d[1]=2842;
   tlmframe[3].d[2]=20;
   tlmframe[3].d[3]=-7;

   /* Setup the strings for the command strings */
   /* 0-7 are bits 0-7 of the 8 command bits */
   /* 8-15 are user defined */

   strcpy(sat->cmdstring[0],"96HR TIMER TOG"); /* reserved for cmd bit 0 */
   strcpy(sat->cmdstring[1],"RSET-OTHER-TNC"); /* reserved for cmd bit 1 */
   strcpy(sat->cmdstring[2],"RX HEATERS ENB"); /* reserved for cmd bit 2 */
   strcpy(sat->cmdstring[3],"VHF-TX ENABLED"); /* reserved for cmd bit 3 */
   strcpy(sat->cmdstring[4],"TOG-SHUNT-REF "); /* reserved for cmd bit 4 */
   strcpy(sat->cmdstring[5],"PSK-31 ENABLED"); /* reserved for cmd bit 5 */
   strcpy(sat->cmdstring[6],"FM REPEATER ON");/* reserved for cmd bit 6 */
   strcpy(sat->cmdstring[7],"              ");/* reserved for cmd bit 7 */
   strcpy(sat->cmdstring[8],"              ");/* user defined */
   strcpy(sat->cmdstring[9],"              ");/* user defined */
   strcpy(sat->cmdstring[10],"              ");/* user defined */
   strcpy(sat->cmdstring[11],"              ");/* user defined */


   /* setup the positions for each of the command bits. Note that while */
   /* these are in pcsat_setup(), they are infact generic, and you should */
   /* duplicate these lines in your own setup function. */

   for (i=0; i<=3; i++)
   {
      sat->cmdloc[0][i]=1;
      sat->cmdloc[1][i]=1+(i*18);
      sat->cmdloc[0][i+4]=2;
      sat->cmdloc[1][i+4]=1+(i*18);
      sat->cmdloc[0][i+8]=3;
      sat->cmdloc[1][i+8]=1+(i*18);
   }

   /* setup if we have extra, satellite specific code to be called */

   sat->extrancurses=TRUE;
   sat->extradetect=FALSE;
   sat->extradecode=FALSE;
   sat->extradisplay=TRUE;
   sat->extrastatic=FALSE;

   sat->nogendetect=FALSE;
   sat->nogendecode=FALSE;
   sat->nogendisplay=FALSE;

}

