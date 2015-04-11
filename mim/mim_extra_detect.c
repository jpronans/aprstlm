#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ncurses.h>
#include <panel.h>
#include <time.h>
#include <sys/time.h>

#include "../include/aprstlm.h"
#include "../include/aprstlm-ncurses.h"

#define MIM_PARM_PKT 1
#define MIM_UNIT_PKT 2
#define MIM_EQNS_PKT 3
#define MIM_BITS_PKT 4

int mim_extra_detect(char *aprsbuf ,int aprscount, struct satstruct *sat, struct tlmframestruct *tlmframe, struct winstruct *screen, int frameno)
{

   int i,j,k,l,m;

   int z;
   bool mimsetup=FALSE;
   int pkttype=0;
   char mimpkt[160];

   char lblch;
   char lbl[7]; 
   size_t eoparm,oldeop;
   size_t eobits,eohdr,hdrlen;
   char tlmhdr[43];

   char tmplbl[10];

   float tmpeqn;

   strcpy(mimpkt,"  ");

   for (j=0; j<sat->asidecalls; j++)
   {
      if (strncmp(aprsbuf,sat->asidecall[j],strlen(sat->asidecall[j]))==0)
         mimsetup=TRUE;
   }

   if (mimsetup)
   {
      for (i=0; i<=((strlen(aprsbuf))-4); i++)
      {
         if (aprsbuf[i]=='P')
         {
            i++;
            if (aprsbuf[i]=='A')
            {
               i++;
               if (aprsbuf[i]=='R')
               {
                  i++;
                  if (aprsbuf[i]=='M')
                  {
                     pkttype=MIM_PARM_PKT;
                     for (k=i; k<=strlen(aprsbuf); k++)
                     {
                        mimpkt[k-i]=aprsbuf[k];
                     }
                  }
               }
            }
         }
      }

      if (pkttype==0)
      {
         for (i=0; i<=((strlen(aprsbuf))-4); i++)
         {
            if (aprsbuf[i]=='U')
            {
               i++;
               if (aprsbuf[i]=='N')
               {
                  i++;
                  if (aprsbuf[i]=='I')
                  {
                     i++;
                     if (aprsbuf[i]=='T')
                     {
                        pkttype=MIM_UNIT_PKT;
                        for (k=i; k<=strlen(aprsbuf); k++)
                        {
                           mimpkt[k-i]=aprsbuf[k];
                        }
                     }
                  }
               }
            }
         }
      }

      if (pkttype==0)
      {
         for (i=0; i<=((strlen(aprsbuf))-4); i++)
         {
            if (aprsbuf[i]=='E')
            {
               i++;
               if (aprsbuf[i]=='Q')
               {
                  i++;
                  if (aprsbuf[i]=='N')
                  {
                     i++;
                     if (aprsbuf[i]=='S')
                     {
                        pkttype=MIM_EQNS_PKT;
                        for (k=i; k<=strlen(aprsbuf); k++)
                        {
                           mimpkt[k-i]=aprsbuf[k];
                        }
                     }
                  }
               }
            }
         }
      }

      if (pkttype==0)
      {
         for (i=0; i<=((strlen(aprsbuf))-4); i++)
         {
            if (aprsbuf[i]=='B')
            {
               i++;
               if (aprsbuf[i]=='I')
               {
                  i++;
                  if (aprsbuf[i]=='T')
                  {
                     i++;
                     if (aprsbuf[i]=='S')
                     {
                        pkttype=MIM_BITS_PKT;
                        for (k=i; k<=strlen(aprsbuf); k++)
                        {
                           mimpkt[k-i]=aprsbuf[k];
                        }
                     }
                  }
               }
            }
         }
      }

      switch(pkttype)
      {
         case MIM_PARM_PKT:
            k=0;
            m=0;
            for (l=2; l<=strlen(mimpkt); l++)
            {
              if ((mimpkt[l]!=',') && (mimpkt[l]!='\0') && (mimpkt[l]!=13))
              {
                 tmplbl[m]=mimpkt[l];
                 m++;
              }
              else
              {
                 if (k<5)
                 {
                    tmplbl[m]=':';
                    tmplbl[m+1]='\0';
                    strcpy(tlmframe[0].lbl[k],tmplbl);
                 }
                 else
                 {
                    tmplbl[m]='\0';
                    strcpy(sat->cmdstring[k-5],tmplbl);
                 }
                 m=0;
                 tmplbl[m]='\0';
                 k++;
              }
            }
            for (j=0; j<=4; j++)
            {
               mvwprintw(screen->tlm_win[0],tlmframe[0].loc[0][j],tlmframe[0].loc[1][j],"%s",tlmframe[0].lbl[j]);
            }
            for (j=0; j<=7; j++)
            {
               mvwprintw(screen->tlm_win[0],10-j,61,sat->cmdstring[j]);
            }
            touchwin(screen->tlm_win[0]);

            break;

         case MIM_EQNS_PKT:
            k=0;
            m=0;
            for (l=2; l<=strlen(mimpkt); l++)
            {
              if ((mimpkt[l]!=',') && (mimpkt[l]!='\0') && (mimpkt[l]!='\n'))
              {
                 tmplbl[m]=mimpkt[l];
                 m++;
              }
              else
              {
                 tmplbl[m]='\0';
                 tmpeqn=atol(tmplbl);
                 switch (k)
                 {
                    case 0:
                       tlmframe[0].b[0]=tmpeqn;
                       break;
                    case 1:
                       tlmframe[0].c[0]=tmpeqn;
                       break;
                    case 2:
                       tlmframe[0].d[0]=tmpeqn;
                       break;
                    case 3:
                       tlmframe[0].b[1]=tmpeqn;
                       break;
                    case 4:
                       tlmframe[0].c[1]=tmpeqn;
                       break;
                    case 5:
                       tlmframe[0].d[1]=tmpeqn;
                       break;
                    case 6:
                       tlmframe[0].b[2]=tmpeqn;
                       break;
                    case 7:
                       tlmframe[0].c[2]=tmpeqn;
                       break;
                    case 8:
                       tlmframe[0].d[2]=tmpeqn;
                       break;
                    case 9:
                       tlmframe[0].b[3]=tmpeqn;
                       break;
                    case 10:
                       tlmframe[0].c[3]=tmpeqn;
                       break;
                    case 11:
                       tlmframe[0].d[3]=tmpeqn;
                       break;
                    case 12:
                       tlmframe[0].b[4]=tmpeqn;
                       break;
                    case 13:
                       tlmframe[0].c[4]=tmpeqn;
                       break;
                    case 14:
                       tlmframe[0].d[4]=tmpeqn;
                       break;
                 }

                 m=0;
                 tmplbl[m]='\0';
                 k++;
              }
           }
           break;
         case MIM_BITS_PKT:
            eobits=strcspn(mimpkt,",");
            eobits++;

            for (k=eobits; k<=strlen(mimpkt); k++)
            {
               tlmhdr[k-eobits]=mimpkt[k];
            }
            tlmhdr[k]='\0';
            mvwprintw(screen->tlm_win[0],0,28,"%s","                      ");
            mvwprintw(screen->tlm_win[0],0,(78-strlen(tlmhdr))/2,"%s",tlmhdr);

            break;
         case MIM_UNIT_PKT:
            k=0;
            m=0;
            for (l=2; l<=strlen(mimpkt); l++)
            {
              if ((mimpkt[l]!=',') && (mimpkt[l]!='\0') && (mimpkt[l]!=13))
              {
                 tmplbl[m]=mimpkt[l];
                 m++;
              }
              else
              {
                 tmplbl[m]='\0';
                 if (k<5)
                 {
		 // Changed from if (strcasestr(tmplbl,"deg C") != NULL)
                    if (!strcasestr(tmplbl,"deg C"))
                    {
                       tlmframe[0].valtype[k]=TLM_VAL_TYPE_TEMP;
                    }
                 }
                 k++;
                 m=0;
                 tmplbl[m]='\0';
              }
           }
           break;
      }
   }

   return(frameno);
}
