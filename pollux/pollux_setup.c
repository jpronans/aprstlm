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

void pollux_setup(struct satstruct *sat,struct tlmframestruct *tlmframe)
{

   int i,j;

   sat->epoch=0; /* FIXME */
   sprintf(sat->norad,"%d",00000); /*FIXME */
   sat->statictime=300;

   strcpy(sat->tlmhdr[0],"RAW TELEMETRY VALUES");
   strcpy(sat->tlmhdr[1],"ENGINEERING TELEMETRY VALUES");

   strcpy(sat->asidecall[0],"POLLUX-1>"); 

   sat->asidecalls=1;
   sat->bsidecalls=0;

   sat->frametypes=6;
   sat->tlmviews=2;
   sat->extrabits=FALSE;

   for (i=0; i<=sat->frametypes; i++)
   {
      /* We MUST initialise these to zero, else the display code */
      /* will get very very confused                             */

      tlmframe[i].rxtime.tv_sec=0;
      tlmframe[i].rxtime.tv_usec=0;
   }

   strcpy(tlmframe[0].lbl[0],"         ");
   tlmframe[0].valtype[0]=TLM_VAL_TYPE_NONE;
   tlmframe[0].loc[0][0]=2;
   tlmframe[0].loc[1][0]=TLM_ENG_COL_1;

   strcpy(tlmframe[0].lbl[1],"         ");
   tlmframe[0].valtype[1]=TLM_VAL_TYPE_NONE;
   tlmframe[0].loc[0][1]=3;
   tlmframe[0].loc[1][1]=TLM_ENG_COL_1;

   strcpy(tlmframe[0].lbl[2],"         ");
   tlmframe[0].valtype[2]=TLM_VAL_TYPE_NONE;
   tlmframe[0].loc[0][2]=4;
   tlmframe[0].loc[1][2]=TLM_ENG_COL_1;
   
   strcpy(tlmframe[0].lbl[3],"         ");
   tlmframe[0].valtype[3]=TLM_VAL_TYPE_NONE;
   tlmframe[0].loc[0][3]=2;
   tlmframe[0].loc[1][3]=TLM_ENG_COL_2;

   strcpy(tlmframe[0].lbl[4],"         ");
   tlmframe[0].valtype[4]=TLM_VAL_TYPE_NONE;
   tlmframe[0].loc[0][4]=3;
   tlmframe[0].loc[1][4]=TLM_ENG_COL_2;

   strcpy(tlmframe[1].lbl[0],"         ");
   tlmframe[1].valtype[0]=TLM_VAL_TYPE_NONE;
   tlmframe[1].loc[0][0]=4;
   tlmframe[1].loc[1][0]=TLM_ENG_COL_2;

   strcpy(tlmframe[1].lbl[1],"         ");
   tlmframe[1].valtype[1]=TLM_VAL_TYPE_NONE;
   tlmframe[1].loc[0][1]=2;
   tlmframe[1].loc[1][1]=TLM_ENG_COL_3;

   strcpy(tlmframe[1].lbl[2],"         ");
   tlmframe[1].valtype[2]=TLM_VAL_TYPE_NONE;
   tlmframe[1].loc[0][2]=3;
   tlmframe[1].loc[1][2]=TLM_ENG_COL_3;

   strcpy(tlmframe[1].lbl[3],"         ");
   tlmframe[1].valtype[3]=TLM_VAL_TYPE_NONE;
   tlmframe[1].loc[0][3]=4;
   tlmframe[1].loc[1][3]=TLM_ENG_COL_3;

   strcpy(tlmframe[1].lbl[4],"        ");
   tlmframe[1].valtype[4]=TLM_VAL_TYPE_NONE;
   tlmframe[1].loc[0][4]=2;
   tlmframe[1].loc[1][4]=TLM_ENG_COL_4;

   strcpy(tlmframe[2].lbl[0],"        ");
   tlmframe[2].valtype[0]=TLM_VAL_TYPE_NONE;
   tlmframe[2].loc[0][0]=3;
   tlmframe[2].loc[1][0]=TLM_ENG_COL_4;

   strcpy(tlmframe[2].lbl[1],"        ");
   tlmframe[2].valtype[1]=TLM_VAL_TYPE_NONE;
   tlmframe[2].loc[0][1]=4;
   tlmframe[2].loc[1][1]=TLM_ENG_COL_4;

   strcpy(tlmframe[2].lbl[2],"Light 1 :");
   tlmframe[2].valtype[2]=TLM_VAL_TYPE_RAW;
   tlmframe[2].loc[0][2]=6;
   tlmframe[2].loc[1][2]=TLM_ENG_COL_1;
   
   strcpy(tlmframe[2].lbl[3],"Temp 1  :");
   tlmframe[2].valtype[3]=TLM_VAL_TYPE_TEMP;
   tlmframe[2].loc[0][3]=6;
   tlmframe[2].loc[1][3]=TLM_ENG_COL_2;

   strcpy(tlmframe[2].lbl[4],"Light 5 :");
   tlmframe[2].valtype[4]=TLM_VAL_TYPE_RAW;
   tlmframe[2].loc[0][4]=6;
   tlmframe[2].loc[1][4]=TLM_ENG_COL_3;
   
   strcpy(tlmframe[3].lbl[0],"Temp 5  :");
   tlmframe[3].valtype[0]=TLM_VAL_TYPE_TEMP;
   tlmframe[3].loc[0][0]=6;
   tlmframe[3].loc[1][0]=TLM_ENG_COL_4;

   strcpy(tlmframe[3].lbl[1],"Light 2 :");
   tlmframe[3].valtype[1]=TLM_VAL_TYPE_RAW;
   tlmframe[3].loc[0][1]=7;
   tlmframe[3].loc[1][1]=TLM_ENG_COL_1;
   
   strcpy(tlmframe[3].lbl[2],"Temp 2  :");
   tlmframe[3].valtype[2]=TLM_VAL_TYPE_TEMP;
   tlmframe[3].loc[0][2]=7;
   tlmframe[3].loc[1][2]=TLM_ENG_COL_2;

   strcpy(tlmframe[3].lbl[3],"Light 6 :");
   tlmframe[3].valtype[3]=TLM_VAL_TYPE_RAW;
   tlmframe[3].loc[0][3]=7;
   tlmframe[3].loc[1][3]=TLM_ENG_COL_3;
   
   strcpy(tlmframe[3].lbl[4],"Temp 6  :");
   tlmframe[3].valtype[4]=TLM_VAL_TYPE_TEMP;
   tlmframe[3].loc[0][4]=7;
   tlmframe[3].loc[1][4]=TLM_ENG_COL_4;

   strcpy(tlmframe[4].lbl[0],"Light 3 :");
   tlmframe[4].valtype[0]=TLM_VAL_TYPE_RAW;
   tlmframe[4].loc[0][0]=8;
   tlmframe[4].loc[1][0]=TLM_ENG_COL_1;
   
   strcpy(tlmframe[4].lbl[1],"Temp 3  :");
   tlmframe[4].valtype[1]=TLM_VAL_TYPE_TEMP;
   tlmframe[4].loc[0][1]=8;
   tlmframe[4].loc[1][1]=TLM_ENG_COL_2;

   strcpy(tlmframe[4].lbl[2],"Batt mA :");
   tlmframe[4].valtype[2]=TLM_VAL_TYPE_CURR;
   tlmframe[4].loc[0][2]=8;
   tlmframe[4].loc[1][2]=TLM_ENG_COL_3;

   strcpy(tlmframe[4].lbl[3],"Batt V  :");
   tlmframe[4].valtype[3]=TLM_VAL_TYPE_VOLT;
   tlmframe[4].loc[0][3]=8;
   tlmframe[4].loc[1][3]=TLM_ENG_COL_4;

   strcpy(tlmframe[4].lbl[4],"Light 4 :");
   tlmframe[4].valtype[4]=TLM_VAL_TYPE_RAW;
   tlmframe[4].loc[0][4]=9;
   tlmframe[4].loc[1][4]=TLM_ENG_COL_1;
   
   strcpy(tlmframe[5].lbl[0],"Temp 4  :");
   tlmframe[5].valtype[0]=TLM_VAL_TYPE_TEMP;
   tlmframe[5].loc[0][0]=9;
   tlmframe[5].loc[1][0]=TLM_ENG_COL_2;

   strcpy(tlmframe[5].lbl[1],"TLM Int :");
   tlmframe[5].valtype[1]=TLM_VAL_TYPE_RAW;
   tlmframe[5].loc[0][1]=9;
   tlmframe[5].loc[1][1]=TLM_ENG_COL_3;

   strcpy(tlmframe[5].lbl[2],"Sat Mode:");
   tlmframe[5].valtype[2]=TLM_VAL_TYPE_RAW;
   tlmframe[5].loc[0][2]=9;
   tlmframe[5].loc[1][2]=TLM_ENG_COL_4;

  for (i=0; i<=7; i++)
   {
      for (j=0; j<=3; j++)
      {
         tlmframe[i].a[j]=0.0;
         tlmframe[i].b[j]=0.0;
         tlmframe[i].c[j]=1.0;
         tlmframe[i].d[j]=0.0;
      }
   }

   strcpy(sat->cmdstring[0],"              "); /* reserved for cmd bit 0 */
   strcpy(sat->cmdstring[1],"              "); /* reserved for cmd bit 1 */
   strcpy(sat->cmdstring[2],"              "); /* reserved for cmd bit 2 */
   strcpy(sat->cmdstring[3],"              "); /* reserved for cmd bit 3 */
   strcpy(sat->cmdstring[4],"              "); /* reserved for cmd bit 4 */
   strcpy(sat->cmdstring[5],"              "); /* reserved for cmd bit 5 */
   strcpy(sat->cmdstring[6],"              ");/* reserved for cmd bit 6 */
   strcpy(sat->cmdstring[7],"              ");/* reserved for cmd bit 7 */
   strcpy(sat->cmdstring[8],"              ");/* set if bit 3 is set on */
                                               /* B-Side */
   strcpy(sat->cmdstring[9],"              ");/* set if bit 3 is set on */
                                               /* A-Side */
   strcpy(sat->cmdstring[10],"              ");/* set if bit 5 is set on */
                                               /* B-Side */
   strcpy(sat->cmdstring[11],"              ");/* set if bit 5 is set on */
                                               /* A-Side */

   for (i=0; i<=3; i++)
   {
      sat->cmdloc[0][i]=1;
      sat->cmdloc[1][i]=1+(i*18);
      sat->cmdloc[0][i+4]=2;
      sat->cmdloc[1][i+4]=1+(i*18);
      sat->cmdloc[0][i+8]=3;
      sat->cmdloc[1][i+8]=1+(i*18);
   }

   for (i=0; i<=7; i++)
   {
      for (j=0; j<=7; j++)
      {
         tlmframe[i].cmdbits[j]=TRUE;
      }
   }

   sat->extrancurses=TRUE;
   sat->extradetect=TRUE;
   sat->extradecode=TRUE;
   sat->extradisplay=FALSE;
   sat->extrastatic=FALSE;


   sat->nogendetect=FALSE;
   sat->nogendecode=TRUE;
   sat->nogendisplay=FALSE;
 
}
