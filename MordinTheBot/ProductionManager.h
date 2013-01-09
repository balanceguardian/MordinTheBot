#pragma once
#include "Common.h"
#include "InformationManager.h"
#include "ProbeManager.h"

class ProductionManager
{
public:
	ProductionManager();
	~ProductionManager();

	void onFrame();
	void onBuildingShow(BWAPI::Unit* unit);

	UnitSet nexuses;

private:
	bool canTrain(BWAPI::UnitType type);
};