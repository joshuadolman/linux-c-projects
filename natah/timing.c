#ifndef TIMING_C
	#define TIMING_C

#include <sys/types.h>
#include <time.h>

//For some reason, all of this does not seem to be defined in time.h so I've done it myself -joshua 2019/07/14
typedef struct timespec {
	time_t tv_sec;
	long tv_nsec;
} timespec;

int clock_getres(clockid_t clk_id, struct timespec *res);
int clock_gettime(clockid_t clk_id, struct timespec *tp);
int clock_settime(clockid_t clk_id, const struct timespec *tp);

#define CLOCK_REALTIME 0
#define CLOCK_MONOTONIC 1

//After I've fixed up time.h, everything below here is my own wrapper code for getting timings the way I want -joshua 2019/07/14

f64 GetTimingMS() {
	timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	f64 seconds = (f64)(ts.tv_sec);
	f64 nanoseconds = (f64)(ts.tv_nsec);
	f64 milliseconds = seconds*1000.0 + nanoseconds/1000000.0;
	return milliseconds;
}





#endif //TIMING_C