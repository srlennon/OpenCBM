/*
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version
 *  2 of the License, or (at your option) any later version.
 *
 *  Copyright 1997-2005 Joe Forster <sta@c64.org>
 *  Copyright 1997-2005 Wolfgang Moser <womo(at)d81(dot)de>
 *  Copyright      2005 Spiro Trikaliotis <cbm4win@trikaliotis.net>
 *
 */

/*! ************************************************************** 
** \file sys/libiec/checkdevice.c \n
** \author Spiro Trikaliotis \n
** \version $Id: checkdevice.c,v 1.2 2005-07-16 19:47:21 strik Exp $ \n
** \authors Based on code from SC written by 
**    Joe Forster & Wolfgang Moser
** \n
** \brief Fast IEC drive detection: Check if there is some device
**        attached, and the bus is not blocked.
**
****************************************************************/

#include <wdm.h>
#include "cbm_driver.h"
#include "i_iec.h"

/*! \brief Fast IEC drive detection

 This function has two purposes: First of all, it tries to find
 out if there are devices responding on the IEC bus.
 Secondly, it finds out if the bus is blocked by a device, for
 example, because the device is busy.

 \param Pdx
   Pointer to the device extension.
 
 \param CheckDevice:
   Pointer to a IEC_CHECKDEVICE variable which will contain the status of the
   bus: IEC_CHECKDEVICE_NODEVICE indicates that there is no device attached,
   IEC_CHECKDEVICE_BUSBUSY indicates that the bus is still busy, and
   IEC_CHECKDEVICE_BUSFREE indicates we are free to use the bus.

 \return 
   If the routine succeeds, it returns STATUS_SUCCESS. Otherwise, it
   returns one of the error status values.
*/
NTSTATUS
cbmiec_check_device(IN PDEVICE_EXTENSION Pdx, OUT IEC_CHECKDEVICE *CheckDevice)
{
    FUNC_ENTER();

    DBG_ASSERT(CheckDevice != NULL);

    do
    {
        CBMIEC_RELEASE(PP_ATN_OUT | PP_CLK_OUT | PP_DATA_OUT | PP_RESET_OUT);

        // wait for the drive to have time to react
        cbmiec_schedule_timeout(100);

        // assert ATN
        CBMIEC_SET(PP_ATN_OUT);

        // now, wait for the drive to have time to react
        cbmiec_schedule_timeout(100);

        // if DATA is still unset, we have a problem.
        if (!CBMIEC_GET(PP_DATA_IN))
        {
            *CheckDevice = IEC_CHECKDEVICE_NODEVICE;
            break;
        }

        // ok, at least one drive reacted. Now, test releasing ATN:

        CBMIEC_RELEASE(PP_ATN_OUT);
        cbmiec_schedule_timeout(100);

        if (!CBMIEC_GET(PP_DATA_IN))
            *CheckDevice = IEC_CHECKDEVICE_BUSFREE;
        else
            *CheckDevice = IEC_CHECKDEVICE_BUSBUSY;

    } while (FALSE);

    CBMIEC_RELEASE(PP_ATN_OUT | PP_CLK_OUT | PP_DATA_OUT | PP_RESET_OUT);

    FUNC_LEAVE_NTSTATUS_CONST(STATUS_SUCCESS);
}
