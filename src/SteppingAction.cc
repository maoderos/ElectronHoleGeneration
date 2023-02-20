#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4String.hh"
#include "G4UnitsTable.hh"
#include "G4Step.hh"
#include "G4AnalysisManager.hh"
#include "EventAction.hh"
#include "G4SteppingManager.hh"
#include "G4RunManager.hh"
#include <sstream>
#include <iostream>

using namespace std;

SteppingAction::SteppingAction(EventAction* _evt, DetectorConstruction* _det, PrimaryGeneratorAction* _primary): G4UserSteppingAction(), evt(_evt), det(_det), primary(_primary)
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  G4double eDep = step->GetTotalEnergyDeposit();
  if (eDep <= 0) return;
  G4double totalEnergyDep = step->GetTotalEnergyDeposit()/MeV;
  G4double nielEnergyDep = step->GetNonIonizingEnergyDeposit()/MeV;
  G4double ionizingEnergyDep = totalEnergyDep - nielEnergyDep;
  // Get the mean point in the step.
  G4double xPos = (step->GetPostStepPoint()->GetPosition().x() + step->GetPreStepPoint()->GetPosition().x() )/2;
  G4double yPos = (step->GetPostStepPoint()->GetPosition().y() + step->GetPreStepPoint()->GetPosition().y() )/2;
  G4double zPos = (step->GetPostStepPoint()->GetPosition().z() + step->GetPreStepPoint()->GetPosition().z() )/2;
  const G4ParticleDefinition* particle = step->GetTrack()->GetParticleDefinition();
  G4int trackID = step->GetTrack()->GetTrackID();
  G4int eventNumber = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  G4String materialName = det->GetMaterialName();
  G4double targetThickness = det->GetSensitiveThickness()/cm;
  G4double materialDensity = det->GetSensitiveMaterial()->GetDensity()/(g/cm3);
  // Enable for validation purposes]
  /*
  G4double stepLength = step->GetStepLength();
  G4cout << "STEP LENGTH: " << stepLength/nm << " nm" << G4endl; 
  */
  // Calculate the number of electron-hole pairs in the step
  G4double electronHolePairEnergy = det->GetElectronHolePairEnergy();
  G4int numberOfElectronHolePairs = 0;
  if (ionizingEnergyDep < 0) {
    std::cout << "ABSURD" << std::endl;
  }
  if (ionizingEnergyDep >= electronHolePairEnergy) {
    // Number of e-h 
    numberOfElectronHolePairs = ionizingEnergyDep/electronHolePairEnergy;
  }
  if (step->GetTrack()->GetVolume()->GetName() == "Sensitive") {

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    // Fill electron-hole N tuple
    if (numberOfElectronHolePairs != 0) {
      evt->AddEHNumber(numberOfElectronHolePairs);
      analysisManager->FillNtupleIColumn(1, 0, numberOfElectronHolePairs);
      analysisManager->FillNtupleDColumn(1, 1, xPos/um);
      analysisManager->FillNtupleDColumn(1, 2, yPos/um);
      analysisManager->FillNtupleDColumn(1, 3, zPos/um);
      analysisManager->FillNtupleSColumn(1, 4, materialName);
      analysisManager->FillNtupleDColumn(1, 5, primary->GetParticleGun()->GetParticleEnergy()/MeV);
      analysisManager->AddNtupleRow(1);
    }
    if (step->GetTrack()->GetParentID() == 0) {
       evt->AddEdepTotal(eDep/materialDensity/targetThickness);
       evt->AddEdepNiel(nielEnergyDep/materialDensity/targetThickness);
       evt->AddEdepIonizing(ionizingEnergyDep/materialDensity/targetThickness);
    }
  }
}
