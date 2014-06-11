/*
  * Abstraction API/layer for the various ways PvPGN can inspect sockets state
  * 2003 (C) 
  *
  * Code is based on the ideas found in thttpd project.
  *
  * *BSD kqueue(2) based backend
  *
  * This program is free software; you can redistribute it and/or
  * modify it under the terms of the GNU General Public License
  * as published by the Free Software Foundation; either version 2
  * of the License, or (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program; if not, write to the Free Software
  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
  */

#include "common/setup_before.h"
#ifdef STDC_HEADERS
# include <stdlib.h>
#else
# ifdef HAVE_MALLOC_H
#  include <malloc.h>
# endif
#endif
#ifdef HAVE_STRING_H
# include <string.h>
#else
# ifdef HAVE_STRINGS_H
#  include <strings.h>
# endif
#endif
#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif
#ifdef HAVE_SYS_EVENT_H
//# include <sys/event.h>
#endif
#ifdef HAVE_SYS_TIME_H
# include <sys/time.h>
#endif
#include "fdwatch.h"
#include "common/eventlog.h"
#include "common/xalloc.h"
#include "common/setup_after.h"

#ifdef HAVE_KQUEUE
static int sr;
static int kq;
static struct kevent *kqchanges = NULL;		/* changes to make to kqueue */
static struct kevent *kqevents = NULL;		/* events to investigate */
/* r/w indices from idx to the kqchanges index where the change is stored */
static int *_rridx, *_wridx;
static unsigned nochanges;

static int fdw_kqueue_init(int nfds);
static int fdw_kqueue_close(void);
static int fdw_kqueue_add_fd(int idx, t_fdwatch_type rw);
static int fdw_kqueue_del_fd(int idx);
static int fdw_kqueue_watch(long timeout_msecs);
static void fdw_kqueue_handle(void);

t_fdw_backend fdw_kqueue = {
    fdw_kqueue_init,
    fdw_kqueue_close,
    fdw_kqueue_add_fd,
    fdw_kqueue_del_fd,
    fdw_kqueue_watch,
    fdw_kqueue_handle
};

static int fdw_kqueue_init(int nfds)
{
    /**
    int i;

    if ((kq = kqueue()) == -1)
	return -1;
    kqevents = (struct kevent *) xmalloc(sizeof(struct kevent) * nfds);
    kqchanges = (struct kevent *) xmalloc(sizeof(struct kevent) * nfds * 2);
    _rridx = (int *) xmalloc(sizeof(int) * nfds);
    _wridx = (int *) xmalloc(sizeof(int) * nfds);

    memset(kqchanges, 0, sizeof(struct kevent) * nfds);
    for (i = 0; i < nfds; i++)
    {
	_rridx[i] = -1;
	_wridx[i] = -1;
    }
    sr = 0;
    nochanges = 0;

    eventlog(eventlog_level_info, __FUNCTION__, "fdwatch kqueue() based layer initialized (max %d sockets)", nfds);
     */
    return 0;
}

static int fdw_kqueue_close(void)
{
    if (_rridx) { xfree((void *) _rridx); _rridx = NULL; }
    if (_wridx) { xfree((void *) _wridx); _wridx = NULL; }
    if (kqchanges) { xfree((void *) kqchanges); kqchanges = NULL; }
    if (kqevents) { xfree((void *) kqevents); kqevents = NULL; }
    sr = 0;
    nochanges = 0;

    return 0;
}

static int fdw_kqueue_add_fd(int idx, t_fdwatch_type rw)
{
    

    return 0;
}


static int fdw_kqueue_del_fd(int idx)
{
   /* here we presume the calling code does close() on the socket and if so
 * it is automatically removed from any kernel kqueues */

    return 0;
}


static int fdw_kqueue_watch(long timeout_msec)
{
    static struct timespec ts;

    ts.tv_sec = timeout_msec / 1000L;
    ts.tv_nsec = (timeout_msec % 1000L) * 1000000L;
    sr = kevent(kq, nochanges > 0 ? kqchanges : NULL, nochanges, kqevents, fdw_maxcons, &ts);
    nochanges = 0;
    return sr;
}

static void fdw_kqueue_handle(void)
{

    sr = 0;
}

#endif				/* HAVE_KQUEUE */
