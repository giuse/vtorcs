/***************************************************************************

    file                 : img_server.cpp
    created              : Tue Jun 12 13:41:04 CEST 2012
    copyright            : (C) 2002 Giuseppe Cuccu

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <math.h>

#include <tgf.h> 
#include <track.h> 
#include <car.h> 
#include <raceman.h> 
#include <robottools.h>
#include <robot.h>

#include "driver.h"
#include "img_server.h"

static const int BUFSIZE = 20;
static const int NBBOTS = 3;
static char * botname[NBBOTS] = { "img1_Red", "img2_Green", "img3_Blue" };
static Driver * driver[NBBOTS];


/* 
 * Module entry point  
 */ 
extern "C" int 
img_server(tModInfo *modInfo) 
{
    /* clear all structures */
    memset(modInfo, 0, 10*sizeof(tModInfo));

    for (int i = 0; i < NBBOTS; i++) {
        modInfo[i].name    = botname[i];  /* name of the module (short) */
        modInfo[i].desc    = "";          /* description of the module */
        modInfo[i].fctInit = InitFuncPt;  /* init function */
        modInfo[i].gfId    = ROB_IDENT;   /* supported framework version */
        modInfo[i].index   = i;           /* indices from 0 to 9 */
    }

    return 0; 
} 


/* Module interface initialization. */
static int 
InitFuncPt(int index, void *pt) 
{ 
    tRobotItf *itf  = (tRobotItf *)pt; 

    /* create robot instance for index */
    driver[index] = new Driver(index);
    
    itf->rbNewTrack = initTrack; /* Give the robot the track view called */ 
				 /* for every track change or new race */ 
    itf->rbNewRace  = newrace; 	 /* Start a new race */
    itf->rbDrive    = drive;	 /* Drive during race */
    itf->rbPitCmd   = pitcmd;    /* Pit commands */
    itf->rbEndRace  = endrace;	 /* End of the current race */
    itf->rbShutdown = shutdown;	 /* Called before the module is unloaded */
    itf->index      = index; 	 /* Index used if multiple interfaces */
    return 0;     
} 


/* Called for every track change or new race. */
static void  
initTrack(int index, tTrack* track, void *carHandle, void **carParmHandle, tSituation *s) 
{ 
    driver[index]->initTrack(track, carHandle, carParmHandle, s);
} 


/* Start a new race. */
static void  
newrace(int index, tCarElt* car, tSituation *s) 
{ 
    driver[index]->newRace(car, s);
} 


/* Drive during race. */
static void  
drive(int index, tCarElt* car, tSituation *s) 
{ 
    driver[index]->drive(car, s);
}


/* Pitstop callback */
static int pitcmd(int index, tCarElt* car, tSituation *s)
{
    return driver[index]->pitCommand(car, s);
}


/* End of the current race */
static void
endrace(int index, tCarElt *car, tSituation *s)
{
    driver[index]->endRace(car, s);
}


/* Called before the module is unloaded */
static void
shutdown(int index)
{
  free(botname[index]);
  delete driver[index];
}



