/* The TLM_VAL_TYPE #defines are used to decide which suffix to give */
/* decoded telemetry values in the tlm window. They enable the */
/* display routine to be two for loops, and a switch/case statement */

#define TLM_VAL_TYPE_NONE 0
#define TLM_VAL_TYPE_VOLT 1
#define TLM_VAL_TYPE_CURR 2
#define TLM_VAL_TYPE_TEMP 3
#define TLM_VAL_TYPE_TEMP_SHORTLBL  4
#define TLM_VAL_TYPE_WATT 5
#define TLM_VAL_TYPE_RAW 6

/* The TLM_ENG_COL #defines are used to set the x location of each */
/* of the engineering telemetry values. This enables things to be a */
/* little simpler in setup routines */

#define TLM_ENG_COL_1	1
#define TLM_ENG_COL_2	21
#define TLM_ENG_COL_3	41
#define TLM_ENG_COL_4	61

/* The TLM_COLOUR values are used to change the colours of certain */
/* values and labels. These are backwards compatible with earlier */
/* versions of aprstlm, but do have extra colours added */

#define TLM_COLOUR_HDR 1         /* Header Window Colour */
#define TLM_COLOUR_CLK 2         /* Clocks Window Colour */
#define TLM_COLOUR_QTH 2            /* Location Window Colour */
#define TLM_COLOUR_NOM 3        /* Nominal Values */
#define TLM_COLOUR_STATIC 4         /* Static Values Colour */
#define TLM_COLOUR_DERIVED 5	    /* Values that have been derived */
				    /* from other values */
#define TLM_COLOUR_INVIS 6          /* Invisible Hack */
#define TLM_COLOUR_ALERT 7	/* Value is outside of expected range */

#define TLM_VIEW_COUNT 2	/* Number of tlm panels. */

struct winstruct
{
   WINDOW *clk_win;			/* Clocks Window */
   WINDOW *hdr_win;			/* Header Window */
   WINDOW *qth_win;			/* Predict/Location Window */
   WINDOW *tlm_win[TLM_VIEW_COUNT];	/* Telemetry Window */
   PANEL *tlm_pan[TLM_VIEW_COUNT];	/* Telemetry Panels */
   WINDOW *bin_win;			/* Binary Window */

   int curtlmview;			/* Current tlm view */
};


