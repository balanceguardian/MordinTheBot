#include "ProductionManager.h"

using namespace BWAPI;

ProductionManager::ProductionManager()
{
	nexuses.clear();
}

ProductionManager::~ProductionManager()
{
}

/** Executes on every frame. */
void ProductionManager::onFrame()
{
	// Create probes of 
	for (UnitSet::iterator nexus = nexuses.begin(); nexus != nexuses.end(); ++nexus)
	{
		// If the nexus is not built or the nexus is already training a probe, skip it;
		if ((*nexus)->isCompleted() == false || (*nexus)->isTraining() == true)
			continue;
		
		// Train more probes if needed;
		if (probeManager->needProbes() == true && canTrain(UnitTypes::Protoss_Probe) == true)
		{
			bool ok = (*nexus)->train(UnitTypes::Protoss_Probe);
			if (ok == false)
				Broodwar->printf("Probe training failes. Don't know why -_-");
		}
	}

	return;
}

/** Manage new buildings. */
void ProductionManager::onBuildingShow(Unit* building)
{
	if (building->getType() == UnitTypes::Protoss_Nexus)
		nexuses.insert(building);

	return;
}

/** Check whether we have enough resources to train/build
  * the given unit. */
bool ProductionManager::canTrain(UnitType type)
{
	int minerals = Broodwar->self()->minerals();
	int gas		 = Broodwar->self()->gas();
	int supply	 = Broodwar->self()->supplyTotal() - Broodwar->self()->supplyUsed();
	 
	if (type.mineralPrice()		> minerals ||
		type.gasPrice()			> gas ||
		type.supplyRequired()	> supply * 2)
		return false;
	return true;
}