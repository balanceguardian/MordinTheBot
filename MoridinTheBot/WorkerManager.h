#pragma once
#include <BWAPI.h>

class WorkerManager
{
public:
	WorkerManager();

	void onFrame();
	void addUnit(BWAPI::Unit* unit);

private:
	std::set<BWAPI::Unit*> workerUnits;
};