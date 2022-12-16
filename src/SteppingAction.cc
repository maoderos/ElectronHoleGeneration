#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "RunAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4Step.hh"
#include "G4AnalysisManager.hh"
#include "G4SteppingManager.hh"
#include "G4RunManager.hh"
#include <sstream>
#include <iostream>

using namespace std;

SteppingAction::SteppingAction(DetectorConstruction* _det, PrimaryGeneratorAction* _primary): G4UserSteppingAction(), det(_det), primary(_primary)
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  G4double eDep = step->GetTotalEnergyDeposit();
  if (eDep <= 0) return;
  G4double totalEnergyDep = step->GetTotalEnergyDeposit();
  G4double nielEnergyDep = step->GetNonIonizingEnergyDeposit();
  G4double ionizingEnergyDep = totalEnergyDep - nielEnergyDep;
  // Get the mean point in the step.
  G4double xPos = (step->GetPostStepPoint()->GetPosition().x() - step->GetPreStepPoint()->GetPosition().x() )/2;
  G4double yPos = (step->GetPostStepPoint()->GetPosition().y() - step->GetPreStepPoint()->GetPosition().y() )/2;
  G4double zPos = (step->GetPostStepPoint()->GetPosition().z() - step->GetPreStepPoint()->GetPosition().z() )/2;
  const G4ParticleDefinition* particle = step->GetTrack()->GetParticleDefinition();
  G4int trackID = step->GetTrack()->GetTrackID();
  G4int eventNumber = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

  // Calculate the number of electron-hole pairs in the step
  G4double electronHolePairEnergy = det->GetElectronHolePairEnergy();
  if (ionizingEnergyDep > electronHolePairEnergy) {
    // Number of eh 
    G4double a = 1; // test
  }
  //G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  if (step->GetTrack()->GetVolume()->GetName() == "Sensitive" && step->GetTrack()->GetParentID() == 0) {
    std::cout << "Test" << std::endl;
       
  }
  
}
