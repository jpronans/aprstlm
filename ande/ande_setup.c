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

void ande_setup(struct satstruct *sat,struct tlmframestruct *tlmframe)
{

   int i;                               /* tlmframe Loop Counter   */
   int j;                               /* Channel Loop Counter */

   /* Epoch is used to calculate the Mission Elapsed Time, norad   */
   /* is used by predict, Set to 0 if you know this device isn't   */
   /* a satellite, the code will disable the predict server if you */
   /* requested it */

   sat->epoch=1001817600;
   sprintf(sat->norad,"%d",99998);
   sat->statictime=300;

   strcpy(sat->tlmhdr[0],"RAW TELEMETRY VALUES");
   strcpy(sat->tlmhdr[1],"ENGINEERING TELEMETRY VALUES");

  /* Callsigns that the bird uses */

   strcpy(sat->asidecall[0],"ANDE-1>");
   strcpy(sat->bsidecall[0],"ANDE-2>");

   /* Note we must also tell aprstlm how many calls each side has. */
   /* This is used for loop control, during the detection code */

   sat->asidecalls=1;
   sat->bsidecalls=1;

   sat->frametypes=7;
   sat->tlmviews=2;
   sat->extrabits=FALSE;

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

   strcpy(tlmframe[0].lbl[0],"B2 Temp :");
   tlmframe[0].valtype[0]=TLM_VAL_TYPE_TEMP;
   tlmframe[0].loc[0][0]=8;
   tlmframe[0].loc[1][0]=TLM_ENG_COL_4;

   strcpy(tlmframe[0].lbl[1],"Clock   :");
   tlmframe[0].valtype[1]=TLM_VAL_TYPE_RAW;
   tlmframe[0].loc[0][1]=11;
   tlmframe[0].loc[1][1]=TLM_ENG_COL_2;

   strcpy(tlmframe[0].lbl[2],"Laser  C:");
   tlmframe[0].valtype[2]=TLM_VAL_TYPE_TEMP_SHORTLBL;
   tlmframe[0].loc[0][2]=12;
   tlmframe[0].loc[1][2]=TLM_ENG_COL_1;

   strcpy(tlmframe[0].lbl[3],"TimeToGo:");
   tlmframe[0].valtype[3]=TLM_VAL_TYPE_RAW;
   tlmframe[0].loc[0][3]=12;
   tlmframe[0].loc[1][3]=TLM_ENG_COL_2;

   strcpy(tlmframe[0].lbl[4],"On Time :");
   tlmframe[0].valtype[4]=TLM_VAL_TYPE_RAW;
   tlmframe[0].loc[0][4]=13;
   tlmframe[0].loc[1][4]=TLM_ENG_COL_2;

   strcpy(tlmframe[1].lbl[0],"Laser V :");
   tlmframe[1].valtype[0]=TLM_VAL_TYPE_VOLT;
   tlmframe[1].loc[0][0]=13;
   tlmframe[1].loc[1][0]=TLM_ENG_COL_1;
   
   strcpy(tlmframe[1].lbl[1],"A1 Curr :");
   tlmframe[1].valtype[1]=TLM_VAL_TYPE_CURR;
   tlmframe[1].loc[0][1]=7;
   tlmframe[1].loc[1][1]=TLM_ENG_COL_1;
   
   strcpy(tlmframe[1].lbl[2],"A2 Curr :");
   tlmframe[1].valtype[2]=TLM_VAL_TYPE_CURR;
   tlmframe[1].loc[0][2]=7;
   tlmframe[1].loc[1][2]=TLM_ENG_COL_2;
   
   strcpy(tlmframe[1].lbl[3],"B1 Curr :");
   tlmframe[1].valtype[3]=TLM_VAL_TYPE_CURR;
   tlmframe[1].loc[0][3]=7;
   tlmframe[1].loc[1][3]=TLM_ENG_COL_3;
   
   strcpy(tlmframe[1].lbl[4],"B2 Curr :");
   tlmframe[1].valtype[4]=TLM_VAL_TYPE_CURR;
   tlmframe[1].loc[0][4]=7;
   tlmframe[1].loc[1][4]=TLM_ENG_COL_4;
   
   strcpy(tlmframe[2].lbl[0],"B1 Temp :");
   tlmframe[2].valtype[0]=TLM_VAL_TYPE_TEMP;
   tlmframe[2].loc[0][0]=8;
   tlmframe[2].loc[1][0]=TLM_ENG_COL_3;

   strcpy(tlmframe[2].lbl[1],"+X Temp :");
   tlmframe[2].valtype[1]=TLM_VAL_TYPE_TEMP;
   tlmframe[2].loc[0][1]=2;
   tlmframe[2].loc[1][1]=TLM_ENG_COL_2;

   strcpy(tlmframe[2].lbl[2],"+Y Temp :");
   tlmframe[2].valtype[2]=TLM_VAL_TYPE_TEMP;
   tlmframe[2].loc[0][2]=3;
   tlmframe[2].loc[1][2]=TLM_ENG_COL_2;

   strcpy(tlmframe[2].lbl[3],"+Z Temp :");
   tlmframe[2].valtype[3]=TLM_VAL_TYPE_TEMP;
   tlmframe[2].loc[0][3]=4;
   tlmframe[2].loc[1][3]=TLM_ENG_COL_2;

   strcpy(tlmframe[2].lbl[4],"Retro  C:");
   tlmframe[2].valtype[4]=TLM_VAL_TYPE_TEMP_SHORTLBL;
   tlmframe[2].loc[0][4]=11;
   tlmframe[2].loc[1][4]=TLM_ENG_COL_1;

   strcpy(tlmframe[3].lbl[0],"+12V A  :");
   tlmframe[3].valtype[0]=TLM_VAL_TYPE_VOLT;
   tlmframe[3].loc[0][0]=6;
   tlmframe[3].loc[1][0]=TLM_ENG_COL_2;

   strcpy(tlmframe[3].lbl[1],"+X Curr :");
   tlmframe[3].valtype[1]=TLM_VAL_TYPE_CURR;
   tlmframe[3].loc[0][1]=2;
   tlmframe[3].loc[1][1]=TLM_ENG_COL_1;

   strcpy(tlmframe[3].lbl[2],"+Y Curr :");
   tlmframe[3].valtype[2]=TLM_VAL_TYPE_CURR;
   tlmframe[3].loc[0][2]=3;
   tlmframe[3].loc[1][2]=TLM_ENG_COL_1;

   strcpy(tlmframe[3].lbl[3],"+Z Curr :");
   tlmframe[3].valtype[3]=TLM_VAL_TYPE_CURR;
   tlmframe[3].loc[0][3]=4;
   tlmframe[3].loc[1][3]=TLM_ENG_COL_1;

   strcpy(tlmframe[3].lbl[4],"5V Ref A:");
   tlmframe[3].valtype[4]=TLM_VAL_TYPE_VOLT;
   tlmframe[3].loc[0][4]=6;
   tlmframe[3].loc[1][4]=TLM_ENG_COL_1;

   strcpy(tlmframe[4].lbl[0],"A2 Temp: ");
   tlmframe[4].valtype[0]=TLM_VAL_TYPE_TEMP;
   tlmframe[4].loc[0][0]=8;
   tlmframe[4].loc[1][0]=TLM_ENG_COL_2;
   
   strcpy(tlmframe[4].lbl[1],"Clock   :");
   tlmframe[4].valtype[1]=TLM_VAL_TYPE_RAW;
   tlmframe[4].loc[0][1]=11;
   tlmframe[4].loc[1][1]=TLM_ENG_COL_4;

   strcpy(tlmframe[4].lbl[2],"Laser  C:");
   tlmframe[4].valtype[2]=TLM_VAL_TYPE_TEMP_SHORTLBL;
   tlmframe[4].loc[0][2]=12;
   tlmframe[4].loc[1][2]=TLM_ENG_COL_3;

   strcpy(tlmframe[4].lbl[3],"TimeToGo:");
   tlmframe[4].valtype[3]=TLM_VAL_TYPE_RAW;
   tlmframe[4].loc[0][3]=12;
   tlmframe[4].loc[1][3]=TLM_ENG_COL_4;

   strcpy(tlmframe[4].lbl[4],"On Time :");
   tlmframe[4].valtype[4]=TLM_VAL_TYPE_RAW;
   tlmframe[4].loc[0][4]=13;
   tlmframe[4].loc[1][4]=TLM_ENG_COL_4;

   strcpy(tlmframe[5].lbl[0],"Laser V :");
   tlmframe[5].valtype[0]=TLM_VAL_TYPE_VOLT;
   tlmframe[5].loc[0][0]=13;
   tlmframe[5].loc[1][0]=TLM_ENG_COL_3;
   
   strcpy(tlmframe[6].lbl[0],"A1 Temp :");
   tlmframe[6].valtype[0]=TLM_VAL_TYPE_TEMP;
   tlmframe[6].loc[0][0]=8;
   tlmframe[6].loc[1][0]=TLM_ENG_COL_1;

   strcpy(tlmframe[6].lbl[1],"-X Temp :");
   tlmframe[6].valtype[1]=TLM_VAL_TYPE_TEMP;
   tlmframe[6].loc[0][1]=2;
   tlmframe[6].loc[1][1]=TLM_ENG_COL_4;

   strcpy(tlmframe[6].lbl[2],"-Y Temp :");
   tlmframe[6].valtype[2]=TLM_VAL_TYPE_TEMP;
   tlmframe[6].loc[0][2]=3;
   tlmframe[6].loc[1][2]=TLM_ENG_COL_4;

   strcpy(tlmframe[6].lbl[3],"-Z Temp :");
   tlmframe[6].valtype[3]=TLM_VAL_TYPE_TEMP;
   tlmframe[6].loc[0][3]=4;
   tlmframe[6].loc[1][3]=TLM_ENG_COL_4;

   strcpy(tlmframe[6].lbl[4],"Retro  C:");
   tlmframe[6].valtype[4]=TLM_VAL_TYPE_TEMP_SHORTLBL;
   tlmframe[6].loc[0][4]=11;
   tlmframe[6].loc[1][4]=TLM_ENG_COL_3;

   strcpy(tlmframe[7].lbl[0],"+12V B  :");
   tlmframe[7].valtype[0]=TLM_VAL_TYPE_VOLT;
   tlmframe[7].loc[0][0]=6;
   tlmframe[7].loc[1][0]=TLM_ENG_COL_4;

   strcpy(tlmframe[7].lbl[1],"-X Curr :");
   tlmframe[7].valtype[1]=TLM_VAL_TYPE_CURR;
   tlmframe[7].loc[0][1]=2;
   tlmframe[7].loc[1][1]=TLM_ENG_COL_3;

   strcpy(tlmframe[7].lbl[2],"-Y Curr :");
   tlmframe[7].valtype[2]=TLM_VAL_TYPE_CURR;
   tlmframe[7].loc[0][2]=3;
   tlmframe[7].loc[1][2]=TLM_ENG_COL_3;

   strcpy(tlmframe[7].lbl[3],"-Z Curr :");
   tlmframe[7].valtype[3]=TLM_VAL_TYPE_CURR;
   tlmframe[7].loc[0][3]=4;
   tlmframe[7].loc[1][3]=TLM_ENG_COL_3;

   strcpy(tlmframe[7].lbl[4],"5V Ref B:");
   tlmframe[7].valtype[4]=TLM_VAL_TYPE_VOLT;
   tlmframe[7].loc[0][4]=6;
   tlmframe[7].loc[1][4]=TLM_ENG_COL_3;

   /* setup the quadratic equations */

   /* These values get used in the quadratic equation: */
   /* y=A*(x^3) + B*(x^2) + (C*x) + D */
   /* Each a, b, c, and d value *MUST* be set. This example */
   /* just uses for loops because large amounts of the values */
   /* are zero, or the same value, and its easier just to set */
   /* the odd ones to zero, then reassign later */

   for (j=0; j<=7; j++)
   {
      for (i=0; i<=4; i++)
      {
         tlmframe[j].a[i]=0.00;
         tlmframe[j].b[i]=0.00;
         tlmframe[j].c[i]=0.00;
         tlmframe[j].d[i]=0.00;
      }
   }

   tlmframe[0].a[0]=0.00001;
   tlmframe[0].b[0]=-0.0039;
   tlmframe[0].c[0]=0.829;
   tlmframe[0].d[0]=-40.4;
   
   tlmframe[0].a[2]=0.00001;
   tlmframe[0].b[2]=-0.0039;
   tlmframe[0].c[2]=0.829;
   tlmframe[0].d[2]=-40.4;

   tlmframe[0].c[1]=1.00;
   tlmframe[0].c[3]=1.00;
   tlmframe[0].c[4]=1.00;

   tlmframe[1].c[0]=0.100;
   tlmframe[5].c[0]=0.100;

   strcpy(sat->cmdstring[0],"              "); /* reserved for cmd bit 0 */
   strcpy(sat->cmdstring[1],"              "); /* reserved for cmd bit 1 */
   strcpy(sat->cmdstring[2],"              "); /* reserved for cmd bit 2 */
   strcpy(sat->cmdstring[3],"              "); /* reserved for cmd bit 3 */
   strcpy(sat->cmdstring[4],"              "); /* reserved for cmd bit 4 */
   strcpy(sat->cmdstring[5],"              "); /* reserved for cmd bit 5 */
   strcpy(sat->cmdstring[6],"              ");/* reserved for cmd bit 6 */
   strcpy(sat->cmdstring[7],"              ");/* reserved for cmd bit 7 */

   strcpy(sat->cmdstring[8],"              ");/* blank *
   strcpy(sat->cmdstring[9],"              ");/* blank */
   strcpy(sat->cmdstring[10],"              ");/* blank */
   strcpy(sat->cmdstring[11],"              ");/* blank */

   /* Setup the locations for each value */

   for (i=0; i<=7; i++)
   {
      sat->cmdloc[i][0]=11-i;
      sat->cmdloc[i][1]=60;
   }

   sat->extrancurses=TRUE;
   sat->extradetect=TRUE;
   sat->extradecode=FALSE;
   sat->extradisplay=TRUE;
   sat->extrastatic=FALSE;

   for (i=1; i<=4; i++)
   {
      tlmframe[1].c[i]=1.7;
      tlmframe[1].d[i]=-4;
      tlmframe[5].c[i]=1.7;
      tlmframe[5].d[i]=-4;
   }

   for (i=0; i<=4; i++)
   {
      tlmframe[2].a[i]=0.00001;
      tlmframe[2].b[i]=-0.0039;
      tlmframe[2].c[i]=0.829;
      tlmframe[2].d[i]=-40.4;
      tlmframe[6].a[i]=0.00001;
      tlmframe[6].b[i]=-0.0039;
      tlmframe[6].c[i]=0.829;
      tlmframe[6].d[i]=-40.4;
   }

   tlmframe[4].a[0]=0.00001;
   tlmframe[4].b[0]=-0.0039;
   tlmframe[4].c[0]=0.829;
   tlmframe[4].d[0]=-40.4;
   
   tlmframe[4].a[2]=0.00001;
   tlmframe[4].b[2]=-0.0039;
   tlmframe[4].c[2]=0.829;
   tlmframe[4].d[2]=-40.4;
   
   tlmframe[4].c[1]=1.00;
   tlmframe[4].c[3]=1.00;
   tlmframe[4].c[4]=1.00;

   tlmframe[3].c[0]=0.100;
   tlmframe[7].c[0]=0.100;

   for (i=1; i<=3; i++)
   {
      tlmframe[3].c[i]=-0.196;
      tlmframe[7].c[i]=-0.196;

      tlmframe[3].d[i]=1.00;
      tlmframe[7].d[i]=1.00;
   }

   tlmframe[3].c[4]=0.0235;
   tlmframe[7].c[4]=0.0235;
  
}
