<<<<<<< HEAD
/* $Id: upnperrors.h,v 1.2 2008/07/02 23:31:15 nanard Exp $ */
/* (c) 2007-2015 Thomas Bernard
=======
/* $Id: upnperrors.h,v 1.4 2012/09/27 15:42:11 nanard Exp $ */
/* (c) 2007 Thomas Bernard
>>>>>>> blood in blood out
 * All rights reserved.
 * MiniUPnP Project.
 * http://miniupnp.free.fr/ or http://miniupnp.tuxfamily.org/
 * This software is subjet to the conditions detailed in the
 * provided LICENCE file. */
#ifndef UPNPERRORS_H_INCLUDED
#define UPNPERRORS_H_INCLUDED

<<<<<<< HEAD
#include "miniupnpc_declspec.h"
=======
#include "declspec.h"
>>>>>>> blood in blood out

#ifdef __cplusplus
extern "C" {
#endif

/* strupnperror()
 * Return a string description of the UPnP error code
 * or NULL for undefinded errors */
<<<<<<< HEAD
MINIUPNP_LIBSPEC const char * strupnperror(int err);
=======
LIBSPEC const char * strupnperror(int err);
>>>>>>> blood in blood out

#ifdef __cplusplus
}
#endif

#endif
