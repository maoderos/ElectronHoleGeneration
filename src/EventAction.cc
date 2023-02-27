#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"

EventAction::EventAction(DetectorConstruction* _det, PrimaryGeneratorAction * _primary): G4UserEventAction(), det(_det),primary(_primary)
{
  eDepTotal = 0;
  eDepTotalPrimary = 0;
  eDepNiel = 0;
  eDepIonizing = 0;
}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{
  eDepTotal = 0;
  eDepTotalPrimary = 0;
  eDepNiel = 0;
  eDepIonizing = 0;

}

void EventAction::EndOfEventAction(const G4Event*)
{
 
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  //std::cout << "Fill Ntuple" << std::endl;
  analysisManager->FillNtupleDColumn(0, 0, eDepTotalPrimary);
  analysisManager->FillNtupleDColumn(0, 1, eDepTotal);
  analysisManager->FillNtupleDColumn(0, 2, eDepIonizing);
  analysisManager->FillNtupleDColumn(0, 3, eDepNiel);
  analysisManager->FillNtupleDColumn(0, 4, primary->GetParticleGun()->GetParticleEnergy()/MeV);
  analysisManager->FillNtupleSColumn(0, 5, det->GetMaterialName());  
  analysisManager->FillNtupleIColumn(0, 6, (eDepTotal/eV)*1.6e-4/(det->GetElectronHolePairEnergy()/eV)); // Convertion to fC
  analysisManager->AddNtupleRow(0);


}
