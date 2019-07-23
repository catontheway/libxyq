
#include "CCStdC.h"

#ifndef __MINGW32__

// NS_CC_BEGIN
// 
// int gettimeofday(struct timeval * val, struct timezone *)
// {
// 	if (val)
// 	{
// 		LARGE_INTEGER liTime, liFreq;
// 		QueryPerformanceFrequency(&liFreq);
// 		QueryPerformanceCounter(&liTime);
// 		val->tv_sec = (long)(liTime.QuadPart / liFreq.QuadPart);
// 		val->tv_usec = (long)(liTime.QuadPart * 1000000.0 / liFreq.QuadPart - val->tv_sec * 1000000.0);
// 	}
// 	return 0;
// }
// 
// NS_CC_END

#endif // __MINGW32__