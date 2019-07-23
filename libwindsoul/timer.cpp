/*
 "               ..;;;;,                     ;;;,    
 '           ..;;;"` ;;:           ,;;;;;: ,;;;:.,;..          _/
 `     ,;..,;;"`    :;;'            :;;"`,;;;;;;"":;;         _/ 
       ;;;"  `:;;. ;;'           ..;;:  .;;,.;;:',;;"    _/_/_/_/_/
      .;;`   ,;;" .;"          ,;;;;;;" :;`',;",;;"         _/
     ,;;,:.,;;;  ,;:          :" ,;:` , `:.;;;;;'`         _/   
     ;;"'':;;:. .;; .          ,;;;,;:;;,;;;, ,;             _/
    :;;..;;;;;; :;' :.        :;;;"` `:;;;;;,;,.;.          _/
  .;;":;;`  '"";;:  ';;       '""   .;;`.;";:;;;;` ;,  _/_/_/_/_/
 ;;;" `'       "::. ,;;:          .;"`  ::. '   .,;;;     _/ 
 ""             ';;;;;;;"        ""     ';;;;;;;;;;`     _/
 
                        Windsoul++

                by 云风 (Cloud Wu)  1999-2001                        
 
		http://member.netease.com/~cloudwu
		mailto:cloudwu@263.net
 
		请阅读 readme.txt 中的版权信息
		See readme.txt for copyright information.

		Description:		风魂++ WTimer 模块
 		Original Author:	云风
		Authors:
		Create Time:		2000/10/20
		Modify Time:		2000/12/27

.:*W*:._.:*I*:._.:*N*:._.:*D*:._.:*S*:._.:*O*:._.:*U*:._.:*L*:._.:*/

#include <windows.h>
#include "windsoul.h"
#include "wstimer.h"
//#define new debug_new

//#define _WINDOWS_TIMER_

#define _MSVC
 ///	CPCODE 定义
//////////////////////

#ifdef _BCB
#pragma warn -8002
#endif

#ifdef _BCB
                #define CPU_ID _asm {db 0x0f}; _asm {db 0xa2}
                #define RDTSC  _asm {db 0x0f}; _asm {db 0x31}
#else
        #ifdef _MSVC
                #define CPU_ID _asm _emit 0x0f _asm _emit 0xa2
                #define RDTSC  _asm _emit 0x0f _asm _emit 0x31
        #else
                #error Must define _BCB or _MSVC
        #endif
#endif

DWORD WTimer::s_Cycle=0;
DWORD WTimer::s_CP10K=0;

// 时间检测
void WTimer::Start()
{
	static uINT64 tmp;
	m_hThread	= GetCurrentThread();		
	m_iPriority = GetThreadPriority(m_hThread);
	if ( m_iPriority != THREAD_PRIORITY_ERROR_RETURN )
		SetThreadPriority(m_hThread, THREAD_PRIORITY_TIME_CRITICAL);

	RDTSC;
#ifdef _BCB
	tmp.low=_EAX;
	tmp.high=_EDX;
#endif
#ifdef _MSVC
   	__asm {
       	mov tmp.low,eax;
        mov tmp.high,edx;
      	}
#endif
	m_i64Timer=tmp;
}

DWORD WTimer::Stop()
{
	static uINT64 tmp;
	tmp=m_i64Timer;
#ifdef _BCB
	_ECX=(DWORD)&tmp.low;
	RDTSC
	__asm {
		sub eax,[ecx]
		sbb edx,[ecx+4]
		}
#endif
#ifdef _MSVC
	RDTSC
	__asm {
		sub eax,dword ptr tmp.low;
		sbb edx,tmp.high;
		}
#endif
	__asm {
		shrd eax,edx,4;
		shr edx,4;
		}
#ifdef _BCB
	tmp.low=_EAX;
	tmp.high=_EDX;
#endif
#ifdef _MSVC
	__asm {
		mov tmp.low,eax;
		mov tmp.high,edx;
		}
#endif
	// Reset priority
	if ( m_iPriority != THREAD_PRIORITY_ERROR_RETURN )
			SetThreadPriority(m_hThread, m_iPriority);

	if (tmp.high>0) return 0;
	return tmp.low;  
}

#ifdef _WINDOWS_TIMER_

DWORD WTimer::GetTime()
{
	return DWORD(GetTickCount()*10) - m_StartTime;
}

void WTimer::Reset(int t)
{
	m_StartTime = (DWORD)(GetTickCount()*10) + t;
}

#else

// 返回时间
DWORD WTimer::GetTime()
{
	uINT64 timer;

	RDTSC;
#ifdef _BCB
	timer.high=_EDX;
	timer.low=_EAX;
#endif
#ifdef _MSVC
	__asm {
		mov timer.high,edx;
		mov timer.low,eax;
	}
#endif
	return DWORD(timer.time / s_CP10K) - m_StartTime;
}

void WTimer::Reset(int t)
{
	uINT64 timer;

	RDTSC;
#ifdef _BCB
	timer.low=_EAX;
	timer.high=_EDX;
#endif
#ifdef _MSVC
	__asm {
		mov timer.low,eax;
		mov timer.high,edx;
       	}
#endif

	m_StartTime = (DWORD)(timer.time / s_CP10K) + t;
}

#endif

WTimer::WTimer()
{
	static bool Inited=false;
	if (!Inited) {
		CPU();
		Inited=true;
	}
	Reset();
}

// 利用 RDTSC 指令获得 CPU 速度 (摘抄并修改自 Intel 开发并公开的自由代码)

#define ROUND_THRESHOLD		6

int WTimer::CPU()
{
	int raw_freq;		// Raw frequency of CPU in MHz
	
	int norm_freq;	// Normalized frequency of CPU
								//   in MHz.
	LARGE_INTEGER t0,t1;			// Variables for High-
									//   Resolution Performance
									//   Counter reads

	DWORD freq  =0;			// Most current frequ. calculation
	DWORD freq2 =0;			// 2nd most current frequ. calc.
	DWORD freq3 ;			// 3rd most current frequ. calc.
	
	DWORD total;			// Sum of previous three frequency
							//   calculations

	int tries=0;			// Number of times a calculation has
							//   been made on this call to 
							//   cpuspeed

	DWORD  total_cycles=0, cycles;	// Clock cycles elapsed 
									//   during test
	
	DWORD  stamp0, stamp1;			// Time Stamp Variable 
									//   for beginning and end 
									//   of test

	DWORD  total_ticks=0, ticks;	// Microseconds elapsed 
									//   during test
	
	LARGE_INTEGER count_freq;		// High Resolution 
									//   Performance Counter 
									//   frequency

#ifdef WIN32
	int iPriority;
	HANDLE hThread = GetCurrentThread();
	int stam=::SetThreadAffinityMask(hThread,1);
#endif // WIN32;

	if ( !QueryPerformanceFrequency ( &count_freq ) )
		return 0;

	// On processors supporting the Read 
	//   Time Stamp opcode, compare elapsed
	//   time on the High-Resolution Counter
	//   with elapsed cycles on the Time 
	//   Stamp Register.
	
	do {			// This do loop runs up to 20 times or
	   				//   until the average of the previous 
	   				//   three calculated frequencies is 
	   				//   within 1 MHz of each of the 
	   				//   individual calculated frequencies. 
					//   This resampling increases the 
					//   accuracy of the results since
					//   outside factors could affect this
					//   calculation
			
		tries++;		// Increment number of times sampled
						//   on this call to cpuspeed
			
		freq3 = freq2;	// Shift frequencies back to make
		freq2 = freq;	//   room for new frequency 
						//   measurement

#ifdef WIN32
		iPriority = GetThreadPriority(hThread);
		if ( iPriority != THREAD_PRIORITY_ERROR_RETURN )
		{
			SetThreadPriority(hThread, THREAD_PRIORITY_TIME_CRITICAL);
		}
		::SetThreadAffinityMask(hThread,stam);
#endif // WIN32

    	QueryPerformanceCounter(&t0);	
    					// Get high-resolution performance 
    					//   counter time
			
		t1.LowPart = t0.LowPart;		// Set Initial time
		t1.HighPart = t0.HighPart;

		while ( (DWORD )t1.LowPart - (DWORD )t0.LowPart<50) {	  
   						// Loop until 50 ticks have 
   						//   passed	since last read of hi-
						//	 res counter. This accounts for
						//   overhead later.

			QueryPerformanceCounter(&t1);

			RDTSC;						// Read Time Stamp
			_asm {
				MOV stamp0, EAX
			}
		}
			
			
		t0.LowPart = t1.LowPart;		// Reset Initial 
		t0.HighPart = t1.HighPart;		//   Time

   		while ((DWORD )t1.LowPart-(DWORD )t0.LowPart<10000 ) {
   						// Loop until 1000 ticks have 
   						//   passed	since last read of hi-
   						//   res counter. This allows for
						//   elapsed time for sampling.
   			
				
   			QueryPerformanceCounter(&t1);
   			

			RDTSC;						// Read Time Stamp
			__asm {
				MOV stamp1, EAX
			}
		}

			

#ifdef WIN32
		// Reset priority
		if ( iPriority != THREAD_PRIORITY_ERROR_RETURN )
		{
			SetThreadPriority(hThread, iPriority);
		}
#endif // WIN32

       	cycles = stamp1 - stamp0;	// Number of internal 
        							//   clock cycles is 
        							//   difference between 
        							//   two time stamp 
        							//   readings.

    	ticks = (DWORD ) t1.LowPart - (DWORD ) t0.LowPart;	
								// Number of external ticks is
								//   difference between two
								//   hi-res counter reads.
	

		// Note that some seemingly arbitrary mulitplies and
		//   divides are done below. This is to maintain a 
		//   high level of precision without truncating the 
		//   most significant data. According to what value 
		//   ITERATIIONS is set to, these multiplies and
		//   divides might need to be shifted for optimal
		//   precision.

		ticks = (DWORD)((double)ticks * 1000000/ count_freq.LowPart );	
							// Convert ticks to hundred
							//   thousandths of a tick
			
//		ticks = ticks / ( count_freq.LowPart/10 );		
							// Hundred Thousandths of a 
							//   Ticks / ( 10 ticks/second )
							//   = microseconds (us)

		total_ticks += ticks;
		total_cycles += cycles;

		if ( ticks%count_freq.LowPart > count_freq.LowPart/2 )
			ticks++;			// Round up if necessary
			
		freq = cycles/ticks;	// Cycles / us  = MHz
        										
     	if ( cycles%ticks > ticks/2 )
       		freq++;				// Round up if necessary
          	
		total = ( freq + freq2 + freq3 );
							// Total last three frequency 
							//   calculations

	} while ( (tries < 3 ) || 		
	          (tries < 20)&&
	          ((abs(long(3 * freq -total)) > 3 )||
			  (abs(long(3 * freq2 - total)) > 3) ||
			  (abs(long(3 * freq3 - total)) > 3)));
					// Compare last three calculations to 
	          		//   average of last three calculations.		

	// Try one more significant digit.
	freq3 = ( total_cycles * 10 ) / total_ticks;
	freq2 = ( total_cycles * 100 ) / total_ticks;


	if ( freq2 - (freq3 * 10) >= ROUND_THRESHOLD )
		freq3++;

	s_CP10K= (int) ((double)total_cycles / total_ticks * 100);
	s_Cycle = s_CP10K * 1000;
	raw_freq = total_cycles / total_ticks;
	norm_freq = raw_freq;

	freq = raw_freq * 10;
	if( (freq3 - freq) >= ROUND_THRESHOLD )
		norm_freq++;

	return norm_freq;
}

void WTimer::SetCpu(DWORD mhz)
{
	s_Cycle=mhz*100000;
	s_CP10K=s_Cycle/1000;
}

