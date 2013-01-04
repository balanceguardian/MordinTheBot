#pragma once
#include <BWAPI.h>
#include <BWTA.h>

// New types:
typedef std::set<BWAPI::Unit*> UnitSet;

// Common managers:
class InformationManager;
class ProbeManager;

extern InformationManager* informationManager;
extern ProbeManager* probeManager;