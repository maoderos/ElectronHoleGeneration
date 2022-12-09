#include "SteppingAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4Step.hh"
#include "G4AnalysisManager.hh"
#include "G4SteppingManager.hh"
#include <sstream>
#include <iostream>

using namespace std;

SteppingAction::SteppingAction(): G4UserSteppingAction()
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  G4double eDep = step->GetTotalEnergyDeposit();
  if (eDep <= 0) return;

  //G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  // fill ntuple
  //If Particle is inside the sensitive volume
  if (step->GetTrack()->GetVolume()->GetName() == "Sensitive" && step->GetTrack()->GetParentID() == 0) {
    if (step->IsFirstStepInVolume()) return;
     
    //analysisManager->FillH1(0, z/um, eDep/MeV);
       
  }


  
}
