#ifndef _TIME_H_
#define _TIME_H_

#define CLOCKS_PER_SEC  (long)1000000

/* CPU clock ticks since program started, only user time is measured */
long clock();

/* real time (i.e., wall-clock time) in seconds */
long time();

#endif /* _TIME_H_ */