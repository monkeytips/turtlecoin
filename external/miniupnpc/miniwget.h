<<<<<<< HEAD
/* $Id: miniwget.h,v 1.12 2016/01/24 17:24:36 nanard Exp $ */
/* Project : miniupnp
 * Author : Thomas Bernard
 * Copyright (c) 2005-2016 Thomas Bernard
=======
/* $Id: miniwget.h,v 1.8 2012/09/27 15:42:10 nanard Exp $ */
/* Project : miniupnp
 * Author : Thomas Bernard
 * Copyright (c) 2005-2012 Thomas Bernard
>>>>>>> blood in blood out
 * This software is subject to the conditions detailed in the
 * LICENCE file provided in this distribution.
 * */
#ifndef MINIWGET_H_INCLUDED
#define MINIWGET_H_INCLUDED

<<<<<<< HEAD
#include "miniupnpc_declspec.h"
=======
#include "declspec.h"
>>>>>>> blood in blood out

#ifdef __cplusplus
extern "C" {
#endif

<<<<<<< HEAD
MINIUPNP_LIBSPEC void * miniwget(const char *, int *, unsigned int, int *);

MINIUPNP_LIBSPEC void * miniwget_getaddr(const char *, int *, char *, int, unsigned int, int *);
=======
LIBSPEC void * getHTTPResponse(int s, int * size);

LIBSPEC void * miniwget(const char *, int *, unsigned int);

LIBSPEC void * miniwget_getaddr(const char *, int *, char *, int, unsigned int);
>>>>>>> blood in blood out

int parseURL(const char *, char *, unsigned short *, char * *, unsigned int *);

#ifdef __cplusplus
}
#endif

#endif
<<<<<<< HEAD
=======

>>>>>>> blood in blood out
