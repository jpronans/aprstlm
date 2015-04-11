#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>
#include <panel.h>

#include "../include/aprstlm.h"
#include "../include/aprstlm-ncurses.h"

void pcsat_setup(struct satstruct *sat,struct tlmframestruct *tlmframe)
{

   int i;				/* tlmframe Loop Counter   */
   int j;				/* Channel Loop Counter */

   /* Epoch is used to calculate the Mission Elapsed Time, norad   */
   /* is used by predict, Set to 0 if you know this device isn't   */
   /* a satellite, the code will disable the predict server if you */
   /* requested it */

   sat->epoch=1001817600;
   snprintf(sat->norad,6,"%d",26931);

   /* Setup what we want the "RAW TELEMETRY VALUES", and "ENGINEERING   */
   /* TELEMETRY VALUES" to display. Most of the time, the defaults will */
   /* suffice, but we might want specific labels for small satellites or */
   /* MIM/OPENTRACKER and friends. [0] is the raw screen, [1] is the */
   /* engineering screen if it exists */

   strcpy(sat->tlmhdr[0],"RAW TELEMETRY VALUES");
   strcpy(sat->tlmhdr[1],"ENGINEERING TELEMETRY VALUES");

   /* Callsigns that the bird uses */

   strcpy(sat->asidecall[0],"W3ADO-1>");
   strcpy(sat->asidecall[1],"PCSAT-1>");
   strcpy(sat->bsidecall[0],"PCSAT-11>");

   /* Note we must also tell aprstlm how many calls each side has. */
   /* This is used for loop control, during the detection code */

   sat->asidecalls=2;
   sat->bsidecalls=1;

   /* We also need to specify the total number of frame types minus */
   /* one. This includes both sides. For a per side value, add 1, then */
   /* divide by 2. For satellites with only one frametype (EG RAFT), set */
   /*  to 0, and  /* set sat->bsidecalls to 0, so you just use the a-side */

   sat->frametypes=7;
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
 
   strcpy(tlmframe[0].lbl[0],"+X Cur  :");
   tlmframe[0].valtype[0]=TLM_VAL_TYPE_CURR;
   tlmframe[0].loc[0][0]=2;
   tlmframe[0].loc[1][0]=1;

   strcpy(tlmframe[0].lbl[1],"+Y Cur  :");
   tlmframe[0].valtype[1]=TLM_VAL_TYPE_CURR;
   tlmframe[0].loc[0][1]=3;
   tlmframe[0].loc[1][1]=TLM_ENG_COL_1;

   strcpy(tlmframe[0].lbl[2],"+Z Cur  :");
   tlmframe[0].valtype[2]=TLM_VAL_TYPE_CURR;
   tlmframe[0].loc[0][2]=4;
   tlmframe[0].loc[1][2]=TLM_ENG_COL_1;

   strcpy(tlmframe[0].lbl[3],"-X Cur  :");
   tlmframe[0].valtype[3]=TLM_VAL_TYPE_CURR;
   tlmframe[0].loc[0][3]=2;
   tlmframe[0].loc[1][3]=TLM_ENG_COL_3;

   strcpy(tlmframe[0].lbl[4],"5V Ref A:");
   tlmframe[0].valtype[4]=TLM_VAL_TYPE_VOLT;
   tlmframe[0].loc[0][4]=6;
   tlmframe[0].loc[1][4]=TLM_ENG_COL_2;

   strcpy(tlmframe[1].lbl[0],"+Y Temp :");
   tlmframe[1].valtype[0]=TLM_VAL_TYPE_TEMP;
   tlmframe[1].loc[0][0]=3;
   tlmframe[1].loc[1][0]=TLM_ENG_COL_2;

   strcpy(tlmframe[1].lbl[1],"Bat A  C:");
   tlmframe[1].valtype[1]=TLM_VAL_TYPE_TEMP_SHORTLBL;
   tlmframe[1].loc[0][1]=9;
   tlmframe[1].loc[1][1]=TLM_ENG_COL_1;

   strcpy(tlmframe[1].lbl[2],"TXA Temp:");
   tlmframe[1].valtype[2]=TLM_VAL_TYPE_TEMP;
   tlmframe[1].loc[0][2]=12;
   tlmframe[1].loc[1][2]=TLM_ENG_COL_1;

   strcpy(tlmframe[1].lbl[3],"+Z Temp :");
   tlmframe[1].valtype[3]=TLM_VAL_TYPE_TEMP;
   tlmframe[1].loc[0][3]=4;
   tlmframe[1].loc[1][3]=TLM_ENG_COL_2;

   strcpy(tlmframe[1].lbl[4],"5V Ref A:");
   tlmframe[1].valtype[4]=TLM_VAL_TYPE_VOLT;
   tlmframe[1].loc[0][4]=6;
   tlmframe[1].loc[1][4]=TLM_ENG_COL_2;

   strcpy(tlmframe[2].lbl[0],"+X Temp :");
   tlmframe[2].valtype[0]=TLM_VAL_TYPE_TEMP;
   tlmframe[2].loc[0][0]=2;
   tlmframe[2].loc[1][0]=TLM_ENG_COL_2;

   strcpy(tlmframe[2].lbl[1],"Stk A  C:");
   tlmframe[2].valtype[1]=TLM_VAL_TYPE_TEMP;
   tlmframe[2].loc[0][1]=8;
   tlmframe[2].loc[1][1]=TLM_ENG_COL_2;

   strcpy(tlmframe[2].lbl[2],"-Y Cur  :");
   tlmframe[2].valtype[2]=TLM_VAL_TYPE_CURR;
   tlmframe[2].loc[0][2]=3;
   tlmframe[2].loc[1][2]=TLM_ENG_COL_3;

   strcpy(tlmframe[2].lbl[3],"Bat A mA:");
   tlmframe[2].valtype[3]=TLM_VAL_TYPE_CURR;
   tlmframe[2].loc[0][3]=8;
   tlmframe[2].loc[1][3]=TLM_ENG_COL_1;

   strcpy(tlmframe[2].lbl[4],"5V Ref A:");
   tlmframe[2].valtype[4]=TLM_VAL_TYPE_VOLT;
   tlmframe[2].loc[0][4]=6;
   tlmframe[2].loc[1][4]=TLM_ENG_COL_2;

   strcpy(tlmframe[3].lbl[0],"Bat A-A :");
   tlmframe[3].valtype[0]=TLM_VAL_TYPE_VOLT;
   tlmframe[3].loc[0][0]=7;
   tlmframe[3].loc[1][0]=TLM_ENG_COL_1;

   strcpy(tlmframe[3].lbl[1],"Bat A-B :");
   tlmframe[3].valtype[1]=TLM_VAL_TYPE_VOLT;
   tlmframe[3].loc[0][1]=7;
   tlmframe[3].loc[1][1]=TLM_ENG_COL_2;

   strcpy(tlmframe[3].lbl[2],"TXA Out :");
   tlmframe[3].valtype[2]=TLM_VAL_TYPE_WATT;
   tlmframe[3].loc[0][2]=12;
   tlmframe[3].loc[1][2]=TLM_ENG_COL_2;

   strcpy(tlmframe[3].lbl[3],"8V Reg A:");
   tlmframe[3].valtype[3]=TLM_VAL_TYPE_VOLT;
   tlmframe[3].loc[0][3]=6;
   tlmframe[3].loc[1][3]=TLM_ENG_COL_1;

   strcpy(tlmframe[3].lbl[4],"5V Ref A:");
   tlmframe[3].valtype[4]=TLM_VAL_TYPE_VOLT;
   tlmframe[3].loc[0][4]=6;
   tlmframe[3].loc[1][4]=TLM_ENG_COL_2;

   strcpy(tlmframe[4].lbl[0],"-X Cur  :");
   tlmframe[4].valtype[0]=TLM_VAL_TYPE_CURR;
   tlmframe[4].loc[0][0]=2;
   tlmframe[4].loc[1][0]=TLM_ENG_COL_3;

   strcpy(tlmframe[4].lbl[1],"-Z Cur  :");
   tlmframe[4].valtype[1]=TLM_VAL_TYPE_CURR;
   tlmframe[4].loc[0][1]=4;
   tlmframe[4].loc[1][1]=TLM_ENG_COL_3;

   strcpy(tlmframe[4].lbl[2],"-Y Cur  :");
   tlmframe[4].valtype[2]=TLM_VAL_TYPE_CURR;
   tlmframe[4].loc[0][2]=3;
   tlmframe[4].loc[1][2]=TLM_ENG_COL_3;

   strcpy(tlmframe[4].lbl[3],"+X Cur  :");
   tlmframe[4].valtype[3]=TLM_VAL_TYPE_CURR;
   tlmframe[4].loc[0][3]=2;
   tlmframe[4].loc[1][3]=TLM_ENG_COL_1;

   strcpy(tlmframe[4].lbl[4],"5V Ref B:");
   tlmframe[4].valtype[4]=TLM_VAL_TYPE_VOLT;
   tlmframe[4].loc[0][4]=6;
   tlmframe[4].loc[1][4]=TLM_ENG_COL_4;

   strcpy(tlmframe[5].lbl[0],"-Y Temp :");
   tlmframe[5].valtype[0]=TLM_VAL_TYPE_TEMP;
   tlmframe[5].loc[0][0]=3;
   tlmframe[5].loc[1][0]=TLM_ENG_COL_4;

   strcpy(tlmframe[5].lbl[1],"Bat B  C:");
   tlmframe[5].valtype[1]=TLM_VAL_TYPE_TEMP_SHORTLBL;
   tlmframe[5].loc[0][1]=9;
   tlmframe[5].loc[1][1]=TLM_ENG_COL_3;

   strcpy(tlmframe[5].lbl[2],"TXB Temp:");
   tlmframe[5].valtype[2]=TLM_VAL_TYPE_TEMP;
   tlmframe[5].loc[0][2]=12;
   tlmframe[5].loc[1][2]=TLM_ENG_COL_3;

   strcpy(tlmframe[5].lbl[3],"-Z Temp :");
   tlmframe[5].valtype[3]=TLM_VAL_TYPE_TEMP;
   tlmframe[5].loc[0][3]=4;
   tlmframe[5].loc[1][3]=TLM_ENG_COL_4;

   strcpy(tlmframe[5].lbl[4],"5V Ref B:");
   tlmframe[5].valtype[4]=TLM_VAL_TYPE_VOLT;
   tlmframe[5].loc[0][4]=6;
   tlmframe[5].loc[1][4]=TLM_ENG_COL_4;

   strcpy(tlmframe[6].lbl[0],"-X Temp :");
   tlmframe[6].valtype[0]=TLM_VAL_TYPE_TEMP;
   tlmframe[6].loc[0][0]=2;
   tlmframe[6].loc[1][0]=TLM_ENG_COL_4;

   strcpy(tlmframe[6].lbl[1],"Stk B  C:");
   tlmframe[6].valtype[1]=TLM_VAL_TYPE_TEMP;
   tlmframe[6].loc[0][1]=8;
   tlmframe[6].loc[1][1]=TLM_ENG_COL_4;

   strcpy(tlmframe[6].lbl[2],"+Y Cur  :");
   tlmframe[6].valtype[2]=TLM_VAL_TYPE_CURR;
   tlmframe[6].loc[0][2]=3;
   tlmframe[6].loc[1][2]=TLM_ENG_COL_1;

   strcpy(tlmframe[6].lbl[3],"Bat B mA:");
   tlmframe[6].valtype[3]=TLM_VAL_TYPE_CURR;
   tlmframe[6].loc[0][3]=8;
   tlmframe[6].loc[1][3]=TLM_ENG_COL_3;

   strcpy(tlmframe[6].lbl[4],"5V Ref B:");
   tlmframe[6].valtype[4]=TLM_VAL_TYPE_VOLT;
   tlmframe[6].loc[0][4]=6;
   tlmframe[6].loc[1][4]=TLM_ENG_COL_4;

   strcpy(tlmframe[7].lbl[0],"Bat B-A :");
   tlmframe[7].valtype[0]=TLM_VAL_TYPE_VOLT;
   tlmframe[7].loc[0][0]=7;
   tlmframe[7].loc[1][0]=TLM_ENG_COL_3;

   strcpy(tlmframe[7].lbl[1],"Bat B-B :");
   tlmframe[7].valtype[1]=TLM_VAL_TYPE_VOLT;
   tlmframe[7].loc[0][1]=7;
   tlmframe[7].loc[1][1]=TLM_ENG_COL_4;

   strcpy(tlmframe[7].lbl[2],"TXB Out :");
   tlmframe[7].valtype[2]=TLM_VAL_TYPE_WATT;
   tlmframe[7].loc[0][2]=12;
   tlmframe[7].loc[1][2]=TLM_ENG_COL_4;

   strcpy(tlmframe[7].lbl[3],"8V Reg B:");
   tlmframe[7].valtype[3]=TLM_VAL_TYPE_VOLT;
   tlmframe[7].loc[0][3]=6;
   tlmframe[7].loc[1][3]=TLM_ENG_COL_3;

   strcpy(tlmframe[7].lbl[4],"5V Ref B:");
   tlmframe[7].valtype[4]=TLM_VAL_TYPE_VOLT;
   tlmframe[7].loc[0][4]=6;
   tlmframe[7].loc[1][4]=TLM_ENG_COL_4;

   /* setup the quadratic equations */

   /* These values get used in the quadratic equation: */
   /* y=A*(x^3) + B*(x^2) + (C*x) + D */

   /* Each a, b, c, and d value *MUST* be set. This example */
   /* just uses for loops because large amounts of the values */
   /* are zero, or the same value, and its easier just to set */
   /* the odd ones to zero, then reassign later */

   for (i=0; i<=7; i++)
   {
      for (j=0; j<=3; j++)
      {
         tlmframe[i].a[j]=0.0;
         tlmframe[i].b[j]=0.0;
         tlmframe[i].d[j]=-19.71;
      }
   }

   tlmframe[0].b[0]=0.0012;
   tlmframe[0].b[1]=0.0048;
   tlmframe[0].b[2]=0.0031;
   tlmframe[0].b[3]=0.0024;

   tlmframe[2].b[2]=0.0037;
   tlmframe[2].b[3]=0.0114;

   tlmframe[4].b[0]=0.0034;
   tlmframe[4].b[1]=0.0096;
   tlmframe[4].b[2]=0.0023;
   tlmframe[4].b[3]=0.003;

   tlmframe[6].b[2]=0.0038;
   tlmframe[6].b[3]=0.0158;

   tlmframe[0].c[0]=0.646;
   tlmframe[0].c[1]=0.75;
   tlmframe[0].c[2]=0.241;
   tlmframe[0].c[3]=0.414;

   tlmframe[1].c[0]=0.3414;
   tlmframe[1].c[1]=0.3414;
   tlmframe[1].c[2]=0.3414;
   tlmframe[1].c[3]=0.3414;

   tlmframe[2].c[0]=0.3414;
   tlmframe[2].c[1]=0.3414;
   tlmframe[2].c[2]=0.0264;
   tlmframe[2].c[3]=-2.56;

   tlmframe[3].c[0]=0.0984;
   tlmframe[3].c[1]=0.09826;
   tlmframe[3].c[2]=0.0311;
   tlmframe[3].c[3]=0.0356;

   tlmframe[4].c[0]=0.2284;
   tlmframe[4].c[1]=0.864;
   tlmframe[4].c[2]=0.473;
   tlmframe[4].c[3]=0.4;

   tlmframe[5].c[0]=0.3414;
   tlmframe[5].c[1]=0.3414;
   tlmframe[5].c[2]=0.3414;
   tlmframe[5].c[3]=0.3414;

   tlmframe[6].c[0]=0.3414;
   tlmframe[6].c[1]=0.3414;
   tlmframe[6].c[2]=0.0084;
   tlmframe[6].c[3]=-3.32;

   tlmframe[7].c[0]=0.09774;
   tlmframe[7].c[1]=0.09457;
   tlmframe[7].c[2]=0.0223;
   tlmframe[7].c[3]=0.0351;
   
   tlmframe[0].d[0]=-25.96;
   tlmframe[0].d[1]=-54.6;
   tlmframe[0].d[2]=-25.3;
   tlmframe[0].d[3]=-25.3;

   tlmframe[2].d[2]=-18.5;
   tlmframe[2].d[3]=252;

   tlmframe[3].d[0]=0.0;
   tlmframe[3].d[1]=0.0;
   tlmframe[3].d[2]=0.0;
   tlmframe[3].d[3]=0.0;

   tlmframe[4].d[0]=-26.6;
   tlmframe[4].d[1]=-53.8;
   tlmframe[4].d[2]=-23.2;
   tlmframe[4].d[3]=-26.6;

   tlmframe[6].d[2]=-19.8;
   tlmframe[6].d[3]=259;

   tlmframe[7].d[0]=0.0;
   tlmframe[7].d[1]=0.0;
   tlmframe[7].d[2]=0.0;
   tlmframe[7].d[3]=0.0;

   for (i=0; i<=7; i++)
   {
      tlmframe[i].a[4]=0.0;
      tlmframe[i].b[4]=0.0;
      tlmframe[i].c[4]=0.0235;
      tlmframe[i].d[4]=0.0;
   }

   /* Setup the strings for the command strings */
   /* 0-7 are bits 0-7 of the 8 command bits */
   /* 8-11 are user defined */

   strcpy(sat->cmdstring[0]," UHF-A-RX-OFF "); /* reserved for cmd bit 0 */
   strcpy(sat->cmdstring[1]," UHF-B-RX-OFF "); /* reserved for cmd bit 1 */
   strcpy(sat->cmdstring[2],"GPS-RX ENABLED"); /* reserved for cmd bit 2 */
   strcpy(sat->cmdstring[3]," RSET-OPP-TNC "); /* reserved for cmd bit 3 */
   strcpy(sat->cmdstring[4],"CLEAR-72H-FAIL"); /* reserved for cmd bit 4 */
   strcpy(sat->cmdstring[5]," MITELGPS/QRP "); /* reserved for cmd bit 5 */
   strcpy(sat->cmdstring[6],"80LEDTAILLIGHT");/* reserved for cmd bit 6 */
   strcpy(sat->cmdstring[7],"XCROSS-CONNECT");/* reserved for cmd bit 7 */
   strcpy(sat->cmdstring[8]," RESET-TNC-A  ");/* set if bit 3 is set on */
                                               /* B-Side */
   strcpy(sat->cmdstring[9]," RESET-TNC-B  ");/* set if bit 3 is set on */
                                               /* A-Side */
   strcpy(sat->cmdstring[10],"MITEL GPS FMT ");/* set if bit 5 is set on */
                                               /* B-Side */
   strcpy(sat->cmdstring[11],"LOW POWER/QRP ");/* set if bit 5 is set on */
                                               /* A-Side */


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

   sat->extrancurses=FALSE;
   sat->extradetect=FALSE;
   sat->extradecode=FALSE;
   sat->extradisplay=TRUE;
   sat->extrastatic=TRUE;

   sat->nogendetect=FALSE;
   sat->nogendecode=FALSE;
   sat->nogendisplay=FALSE;

}

