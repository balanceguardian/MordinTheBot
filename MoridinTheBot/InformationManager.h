#pragma once
#include "Common.h"
#include <windows.h>

// A separate thread for the map analysis;
DWORD WINAPI AnalyzeMapThread();

class InformationManager
{
public:
	InformationManager();
	~InformationManager();

	void analyzeMap();

	bool				mapAnalyzed;
	BWTA::BaseLocation* homeLocation;
};