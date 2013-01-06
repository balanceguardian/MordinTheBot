#pragma once
#include "Common.h"

typedef std::map<BWAPI::Unit*, BWAPI::Unit*> ProbeToTarget;
typedef std::map<BWAPI::Unit*, int>			 ResourceToProbe;

class ProbeManager
{
public:
	enum State
	{
		Gathering_Minerals,
		Gathering_Gas,
		Building,
		Defending,
		Attacking,
		Scouting
	};

	ProbeManager();
	~ProbeManager();

	void onFrame();
	void addUnit(BWAPI::Unit* unit);
	bool needProbes();

private:
	BWAPI::Unit* findBestMineral();
	int			 getNumberOfProbesMining();

	static const int probesPerMineral = 2;
	static const int probesPerGayser  = 2;

	UnitSet										probeUnits;
	ProbeToTarget								probesTarget;
	ResourceToProbe								usableMinerals;
	std::map<BWAPI::Unit*, ProbeManager::State>	probesState;
	int											numberOfProbesMining;
};