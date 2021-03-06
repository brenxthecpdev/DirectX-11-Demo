#ifndef SHIPPING_MODE

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include "misc.cpp"
#include "memory.cpp"
#include "hotload.cpp"
#include "threadQueue.cpp"

#else 

#include "app.cpp"

#endif

int CALLBACK WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR commandLine, int showCode) {

	#ifndef SHIPPING_MODE

	AllocConsole();
	freopen("conin$","r",stdin);
	freopen("conout$","w",stdout);
	freopen("conout$","w",stderr);

	HotloadDll hotloadDll;
	initDll(&hotloadDll, "app.dll", "appTemp.dll", "lock.tmp");

	#endif

	WindowsData wData = windowsData(instance, prevInstance, commandLine, showCode);

	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	int coreCount = sysinfo.dwNumberOfProcessors;

	ThreadQueue threadQueue;
	threadInit(&threadQueue, coreCount-1, 1000);

	AppMemory appMemory = {};

	bool firstFrame = true;
	bool secondFrame = false;
	bool isRunning = true;
	while(isRunning) {

		bool reload = false;

		#ifndef SHIPPING_MODE

		if(threadQueueFinished(&threadQueue)) reload = updateDll(&hotloadDll);
		platform_appMain = (appMainType*)getDllFunction(&hotloadDll, "appMain");
		platform_appMain(firstFrame, reload, &isRunning, wData, &threadQueue, &appMemory);

		#else 

		appMain(firstFrame, reload, &isRunning, wData, &threadQueue, &appMemory);

		#endif

		if(firstFrame) firstFrame = false;
	}

	return 0;
}
