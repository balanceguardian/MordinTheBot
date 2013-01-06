#include "MoridinAIModule.h"

using namespace BWAPI;

MoridinAIModule::MoridinAIModule()
{
}

MoridinAIModule::~MoridinAIModule()
{
	delete informationManager;
	delete probeManager;
	delete productionManager;
}

void MoridinAIModule::onStart()
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

void MoridinAIModule::onEnd(bool isWinner)
{
	if (isWinner)
		Broodwar->printf("You have just make it to level over 9000 with your first win !!!\n");
	else
		Broodwar->printf("No problem, you're just level 2 so far!");

	return;
}

void MoridinAIModule::onFrame()
{
	if (Broodwar->isReplay())
		return;

	probeManager->onFrame();
	productionManager->onFrame();

	return;
}

void MoridinAIModule::onSendText(std::string text)
{
    Broodwar->printf("You typed '%s'!", text.c_str());
    Broodwar->sendText("%s", text.c_str());

	return;
}

void MoridinAIModule::onReceiveText(BWAPI::Player* player, std::string text)
{
	Broodwar->printf("%s said '%s'", player->getName().c_str(), text.c_str());

	return;
}

void MoridinAIModule::onPlayerLeft(BWAPI::Player* player)
{
	Broodwar->sendText("%s left the game.", player->getName().c_str());

	return;
}

void MoridinAIModule::onNukeDetect(BWAPI::Position target)
{
	return;
}

void MoridinAIModule::onUnitDiscover(BWAPI::Unit* unit)
{
	return;
}

void MoridinAIModule::onUnitEvade(BWAPI::Unit* unit)
{
	return;
}

void MoridinAIModule::onUnitShow(BWAPI::Unit* unit)
{
	if (Broodwar->self() != unit->getPlayer())
		return;

	if (unit->getType() == UnitTypes::Protoss_Probe)
		probeManager->addUnit(unit);
	else if (unit->getType().isBuilding())
		productionManager->onBuildingShow(unit);

	return;
}

void MoridinAIModule::onUnitHide(BWAPI::Unit* unit)
{
	return;
}

void MoridinAIModule::onUnitCreate(BWAPI::Unit* unit)
{
	return;
}

void MoridinAIModule::onUnitDestroy(BWAPI::Unit* unit)
{
	return;
}

void MoridinAIModule::onUnitMorph(BWAPI::Unit* unit)
{
	return;
}

void MoridinAIModule::onUnitRenegade(BWAPI::Unit* unit)
{
	return;
}

void MoridinAIModule::onSaveGame(std::string gameName)
{
	return;
}
