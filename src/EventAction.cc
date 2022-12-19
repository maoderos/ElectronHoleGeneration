#include "EventAction.hh"
#include "G4AnalysisManager.hh"

EventAction::EventAction(PrimaryGeneratorAction * _primary): G4UserEventAction(), primary(_primary)
{
  eDepTotal = 0;
  eDepNiel = 0;
  eDepIonizing = 0;
  numEH = 0;
}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{
  eDepTotal = 0;
  eDepNiel = 0;
  eDepIonizing = 0;
  numEH = 0;

}

void EventAction::EndOfEventAction(const G4Event*)
{
 
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  std::cout << "Fill Ntuple" << std::endl;

}
