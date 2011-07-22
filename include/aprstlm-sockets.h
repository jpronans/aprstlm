#define MAX_UDP_BUF 1024
#define MAX_TCP_BUF 1024

struct predsatstruct
{
   char satname[10];		/* Satellite Name from Predict */
   float longitude,latitude;	/* Satellite Long and Late */
   float az,el;			/* Satellite Azimuth and Elevation */
   float aos,footprint;		/* Satellite AOS and Footprint */
   float range,altitude;	/* Satellite Range and Altitude */
   float velocity,orbit;	/* Satellite Velocity and Orbit Number */
   float visibility,phase;	/* Satellite Visibility and Orbit Phase */
   float eclipse,squint;	/* Satellite Eclipse and Squint */
   bool birdns,birdew;		/* Satellite N/S and E/W indicators */
};

struct met_tv
{
   double birdmet;              /* In Seconds!! */
   long metdays;                /* Complete Days in Orbit */
   long methours;               /* Extra Hours in Orbit */
   long metmins;                /* Extra Minutes in Orbit */
   long metsecs;                /* Extra Seconds in Orbit */
};
