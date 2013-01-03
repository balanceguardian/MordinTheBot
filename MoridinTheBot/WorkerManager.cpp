#include "WorkerManager.h"
#include <fstream>

std::ofstream fileLog("bwapi-data//AI//log", std::ios::out);
#define DEBUG(Message) fileLog << "Line:" << __LINE__ << ": " << Message << std::endl

using namespace BWAPI;

WorkerManager::WorkerManager()
{}

/** Describes what the working manager should do on every
 * logical frame of the game. */
void WorkerManager::onFrame()
{
	// Every 2 seconds.
	if (Broodwar->getFrameCount() % 24 == 2)
	{
		Broodwar->printf("Number of probes: %d\n", workerUnits.size());

		if (workerUnits.size() > 0)
		{
			std::set<Unit*>::const_iterator probe = workerUnits.begin();
			DEBUG("BOZA!");
		}
	}

	return;
}

/** Add a new probe to the set of probes. */
void WorkerManager::addUnit(Unit* newProbe)
{
	workerUnits.insert(newProbe);

	return;
}