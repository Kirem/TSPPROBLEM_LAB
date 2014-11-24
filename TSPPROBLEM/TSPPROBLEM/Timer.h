#include <windows.h>

class Timer {
			LARGE_INTEGER start, stop;
			double czestotliwosc;


public:
	Timer(){
		LARGE_INTEGER czest;
        QueryPerformanceFrequency(&czest);
		czestotliwosc = (double)czest.QuadPart;
	}
	~Timer(){}

	
	LARGE_INTEGER startTimer() { 
		DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0); 
		QueryPerformanceCounter(&start); 
		SetThreadAffinityMask(GetCurrentThread(), oldmask); 
		return start; 
	}

	double endTimer() { 
		 DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0); 
		 QueryPerformanceCounter(&stop); 
		 SetThreadAffinityMask(GetCurrentThread(), oldmask); 
		 //zwraca wartosc w ms
		 return ((stop.QuadPart - start.QuadPart)/czestotliwosc)*1000000; 
	} 

};
