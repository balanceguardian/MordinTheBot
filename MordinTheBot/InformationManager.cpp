#include "InformationManager.h"

InformationManager::InformationManager()
	: mapAnalyzed(false)
{}

InformationManager::~InformationManager()
{}

// A separate thread for the map analysis;
//DWORD WINAPI AnalyzeMapThread()
//{
//	BWTA::analyze();
//	informationManager->mapAnalyzed = true;
//
//	informationManager->homeLocation = BWTA::getStartLocation(BWAPI::Broodwar->self());
//
//	return 0;
//}

void InformationManager::analyzeMap()
{
	if (mapAnalyzed == false)
	{
		BWTA::readMap();
		// CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AnalyzeMapThread, NULL, 0, NULL);
		BWTA::analyze();
		mapAnalyzed = true;

		homeLocation = BWTA::getStartLocation(BWAPI::Broodwar->self());
	}

	return;
}