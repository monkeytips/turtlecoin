<<<<<<< HEAD
/* $Id: connecthostport.c,v 1.15 2015/10/09 16:26:19 nanard Exp $ */
/* vim: tabstop=4 shiftwidth=4 noexpandtab
 * Project : miniupnp
 * Author : Thomas Bernard
 * Copyright (c) 2010-2018 Thomas Bernard
=======
/* $Id: connecthostport.c,v 1.13 2014/03/31 12:36:36 nanard Exp $ */
/* Project : miniupnp
 * Author : Thomas Bernard
 * Copyright (c) 2010-2014 Thomas Bernard
>>>>>>> blood in blood out
 * This software is subject to the conditions detailed in the
 * LICENCE file provided in this distribution. */

/* use getaddrinfo() or gethostbyname()
 * uncomment the following line in order to use gethostbyname() */
#ifdef NO_GETADDRINFO
#define USE_GETHOSTBYNAME
#endif

#include <string.h>
#include <stdio.h>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <io.h>
#define MAXHOSTNAMELEN 64
#define snprintf _snprintf
#define herror
#define socklen_t int
#else /* #ifdef _WIN32 */
#include <unistd.h>
<<<<<<< HEAD
#include <sys/types.h>
#ifdef MINIUPNPC_SET_SOCKET_TIMEOUT
#include <sys/time.h>
#endif /* #ifdef MINIUPNPC_SET_SOCKET_TIMEOUT */
=======
>>>>>>> blood in blood out
#include <sys/param.h>
#include <sys/select.h>
#include <errno.h>
#define closesocket close
#include <netdb.h>
#include <netinet/in.h>
/* defining MINIUPNPC_IGNORE_EINTR enable the ignore of interruptions
 * during the connect() call */
#define MINIUPNPC_IGNORE_EINTR
<<<<<<< HEAD
#include <sys/socket.h>
#include <sys/select.h>
=======
#ifndef USE_GETHOSTBYNAME
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#endif /* #ifndef USE_GETHOSTBYNAME */
>>>>>>> blood in blood out
#endif /* #else _WIN32 */

/* definition of PRINT_SOCKET_ERROR */
#ifdef _WIN32
<<<<<<< HEAD
#define PRINT_SOCKET_ERROR(x)    fprintf(stderr, "Socket error: %s, %d\n", x, WSAGetLastError());
=======
#define PRINT_SOCKET_ERROR(x)    printf("Socket error: %s, %d\n", x, WSAGetLastError());
>>>>>>> blood in blood out
#else
#define PRINT_SOCKET_ERROR(x) perror(x)
#endif

#if defined(__amigaos__) || defined(__amigaos4__)
#define herror(A) printf("%s\n", A)
#endif

#include "connecthostport.h"

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 64
#endif

/* connecthostport()
 * return a socket connected (TCP) to the host and port
 * or -1 in case of error */
<<<<<<< HEAD
SOCKET connecthostport(const char * host, unsigned short port,
                       unsigned int scope_id)
{
	SOCKET s;
	int n;
=======
int connecthostport(const char * host, unsigned short port,
                    unsigned int scope_id)
{
	int s, n;
>>>>>>> blood in blood out
#ifdef USE_GETHOSTBYNAME
	struct sockaddr_in dest;
	struct hostent *hp;
#else /* #ifdef USE_GETHOSTBYNAME */
	char tmp_host[MAXHOSTNAMELEN+1];
	char port_str[8];
	struct addrinfo *ai, *p;
	struct addrinfo hints;
#endif /* #ifdef USE_GETHOSTBYNAME */
#ifdef MINIUPNPC_SET_SOCKET_TIMEOUT
	struct timeval timeout;
#endif /* #ifdef MINIUPNPC_SET_SOCKET_TIMEOUT */

#ifdef USE_GETHOSTBYNAME
	hp = gethostbyname(host);
	if(hp == NULL)
	{
		herror(host);
<<<<<<< HEAD
		return INVALID_SOCKET;
=======
		return -1;
>>>>>>> blood in blood out
	}
	memcpy(&dest.sin_addr, hp->h_addr, sizeof(dest.sin_addr));
	memset(dest.sin_zero, 0, sizeof(dest.sin_zero));
	s = socket(PF_INET, SOCK_STREAM, 0);
<<<<<<< HEAD
	if(ISINVALID(s))
	{
		PRINT_SOCKET_ERROR("socket");
		return INVALID_SOCKET;
=======
	if(s < 0)
	{
		PRINT_SOCKET_ERROR("socket");
		return -1;
>>>>>>> blood in blood out
	}
#ifdef MINIUPNPC_SET_SOCKET_TIMEOUT
	/* setting a 3 seconds timeout for the connect() call */
	timeout.tv_sec = 3;
	timeout.tv_usec = 0;
	if(setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(struct timeval)) < 0)
	{
<<<<<<< HEAD
		PRINT_SOCKET_ERROR("setsockopt SO_RCVTIMEO");
=======
		PRINT_SOCKET_ERROR("setsockopt");
>>>>>>> blood in blood out
	}
	timeout.tv_sec = 3;
	timeout.tv_usec = 0;
	if(setsockopt(s, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(struct timeval)) < 0)
	{
<<<<<<< HEAD
		PRINT_SOCKET_ERROR("setsockopt SO_SNDTIMEO");
=======
		PRINT_SOCKET_ERROR("setsockopt");
>>>>>>> blood in blood out
	}
#endif /* #ifdef MINIUPNPC_SET_SOCKET_TIMEOUT */
	dest.sin_family = AF_INET;
	dest.sin_port = htons(port);
	n = connect(s, (struct sockaddr *)&dest, sizeof(struct sockaddr_in));
#ifdef MINIUPNPC_IGNORE_EINTR
	/* EINTR The system call was interrupted by a signal that was caught
	 * EINPROGRESS The socket is nonblocking and the connection cannot
	 *             be completed immediately. */
<<<<<<< HEAD
	while(n < 0 && (errno == EINTR || errno == EINPROGRESS))
=======
	while(n < 0 && (errno == EINTR || errno = EINPROGRESS))
>>>>>>> blood in blood out
	{
		socklen_t len;
		fd_set wset;
		int err;
		FD_ZERO(&wset);
		FD_SET(s, &wset);
		if((n = select(s + 1, NULL, &wset, NULL, NULL)) == -1 && errno == EINTR)
			continue;
		/*len = 0;*/
		/*n = getpeername(s, NULL, &len);*/
		len = sizeof(err);
		if(getsockopt(s, SOL_SOCKET, SO_ERROR, &err, &len) < 0) {
			PRINT_SOCKET_ERROR("getsockopt");
			closesocket(s);
<<<<<<< HEAD
			return INVALID_SOCKET;
=======
			return -1;
>>>>>>> blood in blood out
		}
		if(err != 0) {
			errno = err;
			n = -1;
		}
	}
#endif /* #ifdef MINIUPNPC_IGNORE_EINTR */
	if(n<0)
	{
		PRINT_SOCKET_ERROR("connect");
		closesocket(s);
<<<<<<< HEAD
		return INVALID_SOCKET;
=======
		return -1;
>>>>>>> blood in blood out
	}
#else /* #ifdef USE_GETHOSTBYNAME */
	/* use getaddrinfo() instead of gethostbyname() */
	memset(&hints, 0, sizeof(hints));
	/* hints.ai_flags = AI_ADDRCONFIG; */
#ifdef AI_NUMERICSERV
	hints.ai_flags = AI_NUMERICSERV;
#endif
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = AF_UNSPEC; /* AF_INET, AF_INET6 or AF_UNSPEC */
	/* hints.ai_protocol = IPPROTO_TCP; */
	snprintf(port_str, sizeof(port_str), "%hu", port);
	if(host[0] == '[')
	{
		/* literal ip v6 address */
		int i, j;
		for(i = 0, j = 1; host[j] && (host[j] != ']') && i < MAXHOSTNAMELEN; i++, j++)
		{
			tmp_host[i] = host[j];
			if(0 == memcmp(host+j, "%25", 3))	/* %25 is just url encoding for '%' */
				j+=2;							/* skip "25" */
		}
		tmp_host[i] = '\0';
	}
	else
	{
		strncpy(tmp_host, host, MAXHOSTNAMELEN);
	}
	tmp_host[MAXHOSTNAMELEN] = '\0';
	n = getaddrinfo(tmp_host, port_str, &hints, &ai);
	if(n != 0)
	{
#ifdef _WIN32
		fprintf(stderr, "getaddrinfo() error : %d\n", n);
#else
		fprintf(stderr, "getaddrinfo() error : %s\n", gai_strerror(n));
#endif
<<<<<<< HEAD
		return INVALID_SOCKET;
=======
		return -1;
>>>>>>> blood in blood out
	}
	s = -1;
	for(p = ai; p; p = p->ai_next)
	{
		s = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
<<<<<<< HEAD
		if(ISINVALID(s))
=======
		if(s < 0)
>>>>>>> blood in blood out
			continue;
		if(p->ai_addr->sa_family == AF_INET6 && scope_id > 0) {
			struct sockaddr_in6 * addr6 = (struct sockaddr_in6 *)p->ai_addr;
			addr6->sin6_scope_id = scope_id;
		}
#ifdef MINIUPNPC_SET_SOCKET_TIMEOUT
		/* setting a 3 seconds timeout for the connect() call */
		timeout.tv_sec = 3;
		timeout.tv_usec = 0;
		if(setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(struct timeval)) < 0)
		{
			PRINT_SOCKET_ERROR("setsockopt");
		}
		timeout.tv_sec = 3;
		timeout.tv_usec = 0;
		if(setsockopt(s, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(struct timeval)) < 0)
		{
			PRINT_SOCKET_ERROR("setsockopt");
		}
#endif /* #ifdef MINIUPNPC_SET_SOCKET_TIMEOUT */
		n = connect(s, p->ai_addr, p->ai_addrlen);
#ifdef MINIUPNPC_IGNORE_EINTR
		/* EINTR The system call was interrupted by a signal that was caught
		 * EINPROGRESS The socket is nonblocking and the connection cannot
		 *             be completed immediately. */
		while(n < 0 && (errno == EINTR || errno == EINPROGRESS))
		{
			socklen_t len;
			fd_set wset;
			int err;
			FD_ZERO(&wset);
			FD_SET(s, &wset);
			if((n = select(s + 1, NULL, &wset, NULL, NULL)) == -1 && errno == EINTR)
				continue;
			/*len = 0;*/
			/*n = getpeername(s, NULL, &len);*/
			len = sizeof(err);
			if(getsockopt(s, SOL_SOCKET, SO_ERROR, &err, &len) < 0) {
				PRINT_SOCKET_ERROR("getsockopt");
				closesocket(s);
				freeaddrinfo(ai);
<<<<<<< HEAD
				return INVALID_SOCKET;
=======
				return -1;
>>>>>>> blood in blood out
			}
			if(err != 0) {
				errno = err;
				n = -1;
			}
		}
#endif /* #ifdef MINIUPNPC_IGNORE_EINTR */
		if(n < 0)
		{
			closesocket(s);
			continue;
		}
		else
		{
			break;
		}
	}
	freeaddrinfo(ai);
<<<<<<< HEAD
	if(ISINVALID(s))
	{
		PRINT_SOCKET_ERROR("socket");
		return INVALID_SOCKET;
=======
	if(s < 0)
	{
		PRINT_SOCKET_ERROR("socket");
		return -1;
>>>>>>> blood in blood out
	}
	if(n < 0)
	{
		PRINT_SOCKET_ERROR("connect");
<<<<<<< HEAD
		return INVALID_SOCKET;
=======
		return -1;
>>>>>>> blood in blood out
	}
#endif /* #ifdef USE_GETHOSTBYNAME */
	return s;
}

