/* Put any extra decode work that PCSAT requires here. Currently
/* this is  just a stub, but since the core checks if we have extra
/* ncurses work to do, and calls us if we do, we need a function to
/* permit the compile to work. This gets called AFTER the generic decode*/

/* Only decode stuff should appear here. Other extra stuff required */
/* for your satellite/device should appear in the correct _extra_ */
/* file. Uncomment the below include lines to get this to compile */
/* You shouldnt really need any other header files, unless they are */
/* specific to your satellite/device */

/* #include <stdio.h> */
/* #include <stdbool.h> */
/* #include <string.h> */
/* #include <ncurses.h> */
/* #include <panel.h> */
/* #include <time.h> */
/* #include <sys/time.h> */
/* #include <math.h> */

/* #include "../include/aprstlm.h" */
/* #include "../include/aprstlm-ncurses.h" */

void stubs_extra_decode()
{
}



