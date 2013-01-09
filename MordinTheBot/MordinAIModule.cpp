#include "MordinAIModule.h"

using namespace BWAPI;

MordinAIModule::MordinAIModule()
{
}

MordinAIModule::~MordinAIModule()
{
	delete informationManager;
	delete probeManager;
	delete productionManager;
}

void MordinAIModule::onStart()
{
	Broodwar->sendText("gg hf");

	if (Broodwar->isReplay()) 
		return;

	Broodwar->enableFlag(Flag::UserInput);
	Broodwar->enableFlag(Flag::CompleteMapInformation);

	// Sets the speed of the game to the given number. 
	// Lower numbers are faster. 0 is the fastest speed Starcraft can handle.
	// Negative numbers set the default speed;
	Broodwar->setLocalSpeed(-1);

	informationManager = new InformationManager();
	informationManager->analyzeMap();

	probeManager		= new ProbeManager();
	productionManager	= new ProductionManager();

	return;
}

void MordinAIModule::onEnd(bool isWinner)
{
	if (isWinner)
		Broodwar->printf("You have just make it to level over 9000 with your first win !!!\n");
	else
		Broodwar->printf("No problem, you're just level 2 so far!");

	return;
}

void MordinAIModule::onFrame()
{
	if (Broodwar->isReplay())
		return;

	probeManager->onFrame();
	productionManager->onFrame();

	return;
}

void MordinAIModule::onSendText(std::string text)
{
	if (text == "speed on")
		Broodwar->setLocalSpeed(0);
	else if (text == "speed off")
		Broodwar->setLocalSpeed(-1);
	else
	{
		Broodwar->printf("You typed '%s'!", text.c_str());
		Broodwar->sendText("%s", text.c_str());
	}

	return;
}

void MordinAIModule::onReceiveText(BWAPI::Player* player, std::string text)
{
	Broodwar->printf("%s said '%s'", player->getName().c_str(), text.c_str());

	return;
}

void MordinAIModule::onPlayerLeft(BWAPI::Player* player)
{
	Broodwar->sendText("%s left the game.", player->getName().c_str());

	return;
}

void MordinAIModule::onNukeDetect(BWAPI::Position target)
{
	return;
}

void MordinAIModule::onUnitDiscover(BWAPI::Unit* unit)
{
	return;
}

void MordinAIModule::onUnitEvade(BWAPI::Unit* unit)
{
	return;
}

void MordinAIModule::onUnitShow(BWAPI::Unit* unit)
{
	if (Broodwar->self() != unit->getPlayer())
		return;

	if (unit->getType() == UnitTypes::Protoss_Probe)
		probeManager->onProbeShow(unit);
	else if (unit->getType().isBuilding())
		productionManager->onBuildingShow(unit);

	return;
}

void MordinAIModule::onUnitHide(BWAPI::Unit* unit)
{
	return;
}

void MordinAIModule::onUnitCreate(BWAPI::Unit* unit)
{
	return;
}

void MordinAIModule::onUnitDestroy(BWAPI::Unit* unit)
{
	if (Broodwar->self() != unit->getPlayer())
		return;

	if (unit->getType() == UnitTypes::Protoss_Probe)
		probeManager->onProbeDestroy(unit);

	return;
}

void MordinAIModule::onUnitMorph(BWAPI::Unit* unit)
{
	return;
}

void MordinAIModule::onUnitRenegade(BWAPI::Unit* unit)
{
	return;
}

void MordinAIModule::onSaveGame(std::string gameName)
{
	return;
}
