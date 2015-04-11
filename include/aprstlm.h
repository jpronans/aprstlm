#define APRSTLMVER "1.4.1"

#define SAT_PCSAT 0
#define SAT_PCSAT2 1		/* Obsolete, But kept to prevent clashes with
				/* previous code versions */
#define SAT_RAFT 2
#define SAT_ANDE 3

#define SAT_MIMMODULE 4		/* For MIM Modules - not a satellite */

#define SAT_CASTOR 5		/* Twin of Pollux - AX25 Bird */
#define SAT_POLLUX 6		/* Twin of Castor - AX25 Bird */

/* tlmframestruct contains all of the telemetry frames, as well as */
/* enough detail to simplify display, and static detection/display */

struct tlmframestruct
{
   int framecount;		/* T#nnn */
   char tlmstring[43];		/* Actual Telemetry String */
   int rawtlm[5];		/* Raw TLM Values, CH1-5 */
   float tlmval[5];		/* Decoded TLM Values, CH1-5 */
   float a[5];			/* A Value For Decode Equation, CH1-5 */
   float b[5];			/* B Value For Decode Equation, CH1-5 */
   float c[5];			/* C Value For Decode Equation, CH1-5 */
   float d[5];			/* D Value For Decode Equation, CH1-5 */
   bool cmdbits[8];		/* The 8 Command Bits, interpret manually */
   bool sbits[4];		/* The 4 extra bits, post cmd bits */
   bool endbit;			/* The End bit */
				/* Note, some Birds may not have the binary */
                                /* bits */
   struct timeval rxtime;	/* When we received this Frame */
                                /* 0=No TLM RX Yet             */
   double deltatime;		/* difference between current time and */
				/* rxtime. If => statictime, then frame */
				/* is static */
   char lbl[5][10];		/* Label For Each tlmvalue */
   int loc[2][5];		/* Y/X Location on the tlm window */
				/* [0] is Y, [1] is X, as per ncurses */
   int valtype[5];		/* 0=Volts, 1=Current, 2=Temp */
				/* Used to determine the suffix of each */
				/* tlm value in the tlm window */
};

struct satstruct
{
   char label[10];		/* Satellite Text Name For HDR Win */
   char norad[6];		/* NORAD Number */
   time_t epoch;		/* L+0, or Deployment+0 */

   char tlmhdr[2][78];		/* "RAW TELEMETRY VALUES" */
   char asidecall[8][10];	/* 8 Callsigns should be enough!! */
   char bsidecall[8][10];	/* 8 Callsigns should be enough!! */
   int asidecalls;
   int bsidecalls;
   int frametypes;		/* How many different types of frames */
				/* does this bird have per side ? Multiply */
				/* by two for a total value */
   time_t statictime;		/* When our tlm frames go static */
   int tlmviews;		/* Number of Telemetry Views. Usually 2 */
   bool extrabits;		/* Do we have the ,bbbb,z bits on this bird */

   bool extrancurses;		/* Do we have extra ncurses setup to do ? */
                                /* call <bird>_extra_ncurses() if so */
   bool extradetect;		/* Do we have extra detect work to do ? */
                                /* call <bird>_extra_detect() if so */
   bool extradecode;		/* Do we have extra decode work to do ? */
                                /* call <bird>_extra_decode() if so */
   bool extradisplay;		/* Do we have extra display stuff to do ? */
                                /* call <bird>_extra_display() if so */
   bool extrastatic;		/* Do we have extra static stuff to so ? */
                                /* call <bird>_extra_static() if so */
   bool nogendetect;		/* Do we disable the generic detect ? */
   bool nogendecode;		/* Do we Disable the Generic Decode ? */
   bool nogendisplay;		/* Do we Disable the Generic Display ? */
   char cmdstring[12][16];	/* Strings for the command bits */
   int cmdloc[2][12];		/* Y/X Location the of the command bits */
				/* [0] is Y, [1] is X, as per ncurses */

};

