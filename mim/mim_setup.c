/* This is just a stub setup.c file. Copy it to your own directory, */
/* and add the code that you need */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <ncurses.h>
#include <panel.h>

#include "../include/aprstlm.h"
#include "../include/aprstlm-ncurses.h"

void mim_setup(struct satstruct *sat,struct tlmframestruct *tlmframe)
{

   int i;

   sat->epoch=0;			/* What do we want this set to ? */
   sprintf(sat->norad,"%d",0);
   sat->statictime=300;

   strcpy(sat->tlmhdr[0],"MIM TELEMETRY VALUES");

   sat->frametypes=0;
   sat->tlmviews=1;
   sat->extrabits=FALSE;

   tlmframe[0].rxtime.tv_sec=0;
   tlmframe[0].rxtime.tv_usec=0;

   strcpy(tlmframe[0].lbl[0],"         ");
   tlmframe[0].valtype[0]=TLM_VAL_TYPE_NONE;
   tlmframe[0].loc[0][0]=11;
   tlmframe[0].loc[1][0]=1;

   strcpy(tlmframe[0].lbl[1],"         ");
   tlmframe[0].valtype[1]=TLM_VAL_TYPE_NONE;
   tlmframe[0].loc[0][1]=12;
   tlmframe[0].loc[1][1]=1;

   strcpy(tlmframe[0].lbl[2],"         ");
   tlmframe[0].valtype[2]=TLM_VAL_TYPE_NONE;
   tlmframe[0].loc[0][2]=13;
   tlmframe[0].loc[1][2]=35;

   strcpy(tlmframe[0].lbl[3],"         ");
   tlmframe[0].valtype[3]=TLM_VAL_TYPE_NONE;
   tlmframe[0].loc[0][3]=11;
   tlmframe[0].loc[1][3]=61;

   strcpy(tlmframe[0].lbl[4],"         ");
   tlmframe[0].valtype[4]=TLM_VAL_TYPE_NONE;
   tlmframe[0].loc[0][4]=12;
   tlmframe[0].loc[1][4]=61;

   /* Dummy Values until we recieve the EQNS packet */

   for (i=0; i<=4; i++)
   {
      tlmframe[0].a[i]=0.00;
      tlmframe[0].b[i]=0.00;
      tlmframe[0].c[i]=1.00;
      tlmframe[0].d[i]=0.00;
   }

   /* Fake these until we have the LBLS packet */

   strcpy(sat->cmdstring[0],"              "); /* reserved for cmd bit 0 */
   strcpy(sat->cmdstring[1],"              "); /* reserved for cmd bit 1 */
   strcpy(sat->cmdstring[2],"              "); /* reserved for cmd bit 2 */
   strcpy(sat->cmdstring[3],"              "); /* reserved for cmd bit 3 */
   strcpy(sat->cmdstring[4],"              "); /* reserved for cmd bit 4 */
   strcpy(sat->cmdstring[5],"              "); /* reserved for cmd bit 5 */
   strcpy(sat->cmdstring[6],"              ");/* reserved for cmd bit 6 */
   strcpy(sat->cmdstring[7],"              ");/* reserved for cmd bit 7 */

   strcpy(sat->cmdstring[8],"              ");/* blank */
   strcpy(sat->cmdstring[9],"              ");/* blank */
   strcpy(sat->cmdstring[10],"              ");/* blank */
   strcpy(sat->cmdstring[11],"              ");/* blank */

   /* Setup the locations for each value */

   sat->cmdloc[0][0]=11;
   sat->cmdloc[0][1]=11;

   sat->cmdloc[1][0]=12;
   sat->cmdloc[1][1]=11;

   sat->cmdloc[1][0]=13;
   sat->cmdloc[1][1]=45;

   sat->cmdloc[0][0]=11;
   sat->cmdloc[0][1]=60;

   sat->cmdloc[1][0]=12;
   sat->cmdloc[1][1]=60;

   sat->extrancurses=TRUE;
   sat->extradetect=TRUE;
   sat->extradecode=FALSE;
   sat->extradisplay=TRUE;
   sat->extrastatic=FALSE;

}
