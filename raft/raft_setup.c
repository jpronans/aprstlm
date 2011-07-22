#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>
#include <panel.h>

#include "../include/aprstlm.h"
#include "../include/aprstlm-ncurses.h"

void raft_setup(struct satstruct *sat,struct tlmframestruct *tlmframe)
{

   int i;

   sat->epoch=0;			/* What do we want this set to ? */
   sprintf(sat->norad,"%d",99999);	/* Fake until Launch */
   sat->statictime=300;

   strcpy(sat->tlmhdr[0],"RAFT TELEMETRY VALUES");

   strcpy(sat->asidecall[0],"RAFT>");

   /* Note we must also tell aprstlm how many calls each side has. */
   /* This is used for loop control, during the detection code */

   sat->asidecalls=1;
   sat->bsidecalls=0;


   sat->frametypes=0;
   sat->tlmviews=1;
   sat->extrabits=FALSE;

   tlmframe[0].rxtime.tv_sec=0;
   tlmframe[0].rxtime.tv_usec=0;

   strcpy(tlmframe[0].lbl[0],"Bus Volts");
   tlmframe[0].valtype[0]=TLM_VAL_TYPE_VOLT;
   tlmframe[0].loc[0][0]=11;
   tlmframe[0].loc[1][0]=1;

   strcpy(tlmframe[0].lbl[1],"Solar Cur");
   tlmframe[0].valtype[1]=TLM_VAL_TYPE_CURR;
   tlmframe[0].loc[0][1]=12;
   tlmframe[0].loc[1][1]=1;

   strcpy(tlmframe[0].lbl[2],"Batt Curr");
   tlmframe[0].valtype[2]=TLM_VAL_TYPE_CURR;
   tlmframe[0].loc[0][2]=13;
   tlmframe[0].loc[1][2]=35;

   strcpy(tlmframe[0].lbl[3],"Load Curr");
   tlmframe[0].valtype[3]=TLM_VAL_TYPE_CURR;
   tlmframe[0].loc[0][3]=11;
   tlmframe[0].loc[1][3]=61;

   strcpy(tlmframe[0].lbl[4],"S/C Temp ");
   tlmframe[0].valtype[4]=TLM_VAL_TYPE_TEMP;
   tlmframe[0].loc[0][4]=12;
   tlmframe[0].loc[1][4]=61;

   /* setup the quadratic equations */

   /* These values get used in the quadratic equation: */
   /* y=A*(x^3) + B*(x^2) + (C*x) + D */

   /* Each a, b, c, and d value *MUST* be set. This example */
   /* just uses for loops because large amounts of the values */
   /* are zero, or the same value, and its easier just to set */
   /* the odd ones to zero, then reassign later */


   for (i=0; i<=4; i++)
   {
      tlmframe[0].a[i]=0.00;
      tlmframe[0].b[i]=0.00;
      tlmframe[0].c[i]=0.00;
      tlmframe[0].d[i]=0.00;
   }

   tlmframe[0].c[0]=0.10;
   tlmframe[0].c[1]=2.00;
   tlmframe[0].c[2]=2.00;
   tlmframe[0].c[3]=2.00;

   tlmframe[0].a[4]=0.000009;
   tlmframe[0].b[4]=-0.0031;
   tlmframe[0].c[4]=0.7019;
   tlmframe[0].d[4]=-33.024;

   strcpy(sat->cmdstring[0]," Batt Curr Dir"); /* reserved for cmd bit 0 */
   strcpy(sat->cmdstring[1],"              "); /* reserved for cmd bit 1 */
   strcpy(sat->cmdstring[2],"              "); /* reserved for cmd bit 2 */
   strcpy(sat->cmdstring[3],"              "); /* reserved for cmd bit 3 */
   strcpy(sat->cmdstring[4],"              "); /* reserved for cmd bit 4 */
   strcpy(sat->cmdstring[5],"              "); /* reserved for cmd bit 5 */
   strcpy(sat->cmdstring[6],"              ");/* reserved for cmd bit 6 */
   strcpy(sat->cmdstring[7],"              ");/* reserved for cmd bit 7 */

   strcpy(sat->cmdstring[8],"BATT CHARGING ");/* blank *
   strcpy(sat->cmdstring[9],"  APRS DIGI  ");/* blank */
   strcpy(sat->cmdstring[10]," VOICE SYNTH  ");/* blank */
   strcpy(sat->cmdstring[11],"PSK-31 XPONDER");/* blank */

   /* Setup the locations for each value */


   for (i=0; i<=7; i++)
   {
      sat->cmdloc[i][0]=11-i;
      sat->cmdloc[i][1]=60;
   }

   for (i=8; i<=11; i++)
   {
      sat->cmdloc[i][0]=2;
   }

   sat->cmdloc[8][1]=TLM_ENG_COL_1;
   sat->cmdloc[9][1]=TLM_ENG_COL_2;
   sat->cmdloc[10][1]=TLM_ENG_COL_3;
   sat->cmdloc[11][1]=TLM_ENG_COL_4;

   sat->extrancurses=TRUE;
   sat->extradetect=TRUE;
   sat->extradecode=FALSE;
   sat->extradisplay=TRUE;
   sat->extrastatic=FALSE;

}
