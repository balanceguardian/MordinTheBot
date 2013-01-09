#include "ProbeManager.h"

#include <fstream>

std::ofstream fileLog("bwapi-data//AI//log", std::ios::out);
#define DEBUG(Message) fileLog << "Line:" << __LINE__ << ": " << Message << std::endl

using namespace BWAPI;

ProbeManager::ProbeManager()
	: numberOfProbesMining(0)
{
	probeUnits.clear();
	probesState.clear();
	probesTarget.clear();

	// Make a set of initially usable minerals, i.e. the minerals in the base region;
	// UnitSet baseMinerals = informationManager->homeLocation->getMinerals();
	UnitSet baseMinerals = BWTA::getStartLocation(Broodwar->self())->getMinerals();
	for (UnitSet::iterator it = baseMinerals.begin(); it != baseMinerals.end(); ++it)
		usableMinerals[(*it)] = 0;
}

ProbeManager::~ProbeManager()
{}

/** Describes what the working manager should do on every
 * logical frame of the game. */
void ProbeManager::onFrame()
{
	// Update probes' state;
	for (UnitSet::const_iterator probe = probeUnits.begin(); probe != probeUnits.end(); ++probe)
	{
		Unit* curProbe = (*probe);

		if (probesState[curProbe] == Gathering_Minerals &&
			curProbe->isGatheringMinerals() == false)
		{
			Unit* target = probesTarget[curProbe];

			if (target == 0)
			{
				std::string str = "[ERROR] Probe ";
				str += curProbe->getID();
				str += " has no target!";
				DEBUG(str);
			}
			else
				curProbe->rightClick(target);
		}
	}

	return;
}

/** Add a new probe to the set of probes. */
void ProbeManager::onProbeShow(Unit* newProbe)
{
	// Check the new probe
	probeUnits.insert(newProbe);
	probesState[newProbe] = Gathering_Minerals;
	++numberOfProbesMining;
	
	// Assign a mineral to the probe;
	Unit* bestMineral = findBestMineral();
	probesTarget[newProbe] = bestMineral;

	// Check the mineral is assigned. The number should be
	// kept lest than or equal to probesPerMineral;
	++usableMinerals[bestMineral];

	return;
}

/** Remove the probe from the set and free the mineral patch. */
void ProbeManager::onProbeDestroy(Unit* deadProbe)
{
	// Remove the probe;
	probeUnits.erase(deadProbe);
	probesState.erase(deadProbe);
	--numberOfProbesMining;

	// Free the probe's mineral patch;
	Unit* mineralPatch = probesTarget[deadProbe];
	probesTarget.erase(deadProbe);
	--usableMinerals[mineralPatch];

	return;
}

/** Returns true if the limit of workers per mineral patch
  * is not reached. */
bool ProbeManager::needProbes()
{
	int probesMining = getNumberOfProbesMining();

	if ((int)usableMinerals.size() * probesPerMineral > probesMining)
		return true;
	return false;
}

/** Find the mineral with lowest number of attached probes. */
Unit* ProbeManager::findBestMineral()
{
	Unit* bestMineral = 0;
	int minProbes = 9999; 

	for (ResourceToProbe::iterator it = usableMinerals.begin(); it != usableMinerals.end(); ++it)
		if (it->second < minProbes)
		{
			minProbes   = it->second;
			bestMineral = it->first;
		}

	return bestMineral;
}

/** Returns the number of probes mining. */
int ProbeManager::getNumberOfProbesMining()
{
	return numberOfProbesMining;
}