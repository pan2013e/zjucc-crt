#ifndef _SYS_FCNTL_H_
#define _SYS_FCNTL_H_

#include "sys/stat.h"

#define O_ACCMODE	   0003
#define O_RDONLY	     00
#define O_WRONLY	     01
#define O_RDWR		     02
#ifndef O_CREAT
# define O_CREAT	   0100	/* Not fcntl.  */
#endif
#ifndef O_EXCL
# define O_EXCL		   0200	/* Not fcntl.  */
#endif
#ifndef O_NOCTTY
# define O_NOCTTY	   0400	/* Not fcntl.  */
#endif
#ifndef O_TRUNC
# define O_TRUNC	  01000	/* Not fcntl.  */
#endif
#ifndef O_APPEND
# define O_APPEND	  02000
#endif
#ifndef O_NONBLOCK
# define O_NONBLOCK	  04000
#endif
#ifndef O_NDELAY
# define O_NDELAY	O_NONBLOCK
#endif
#ifndef O_SYNC
# define O_SYNC	       04010000
#endif
#define O_FSYNC		O_SYNC
#ifndef O_ASYNC
# define O_ASYNC	 020000
#endif
#ifndef __O_LARGEFILE
# define __O_LARGEFILE	0100000
#endif
#ifndef __O_DIRECTORY
# define __O_DIRECTORY	0200000
#endif
#ifndef __O_NOFOLLOW
# define __O_NOFOLLOW	0400000
#endif
#ifndef __O_CLOEXEC
# define __O_CLOEXEC   02000000
#endif
#ifndef __O_DIRECT
# define __O_DIRECT	 040000
#endif
#ifndef __O_NOATIME
# define __O_NOATIME   01000000
#endif
#ifndef __O_PATH
# define __O_PATH     010000000
#endif
#ifndef __O_DSYNC
# define __O_DSYNC	 010000
#endif
#ifndef __O_TMPFILE
# define __O_TMPFILE   (020000000 | __O_DIRECTORY)
#endif

# define S_IRUSR	__S_IREAD       /* Read by owner.  */
# define S_IWUSR	__S_IWRITE      /* Write by owner.  */
# define S_IXUSR	__S_IEXEC       /* Execute by owner.  */
/* Read, write, and execute by owner.  */
# define S_IRWXU	(__S_IREAD|__S_IWRITE|__S_IEXEC)

# define S_IRGRP	(S_IRUSR >> 3)  /* Read by group.  */
# define S_IWGRP	(S_IWUSR >> 3)  /* Write by group.  */
# define S_IXGRP	(S_IXUSR >> 3)  /* Execute by group.  */
/* Read, write, and execute by group.  */
# define S_IRWXG	(S_IRWXU >> 3)

# define S_IROTH	(S_IRGRP >> 3)  /* Read by others.  */
# define S_IWOTH	(S_IWGRP >> 3)  /* Write by others.  */
# define S_IXOTH	(S_IXGRP >> 3)  /* Execute by others.  */
/* Read, write, and execute by others.  */
# define S_IRWXO	(S_IRWXG >> 3)

#endif /* _SYS_FCNTL_H_ */