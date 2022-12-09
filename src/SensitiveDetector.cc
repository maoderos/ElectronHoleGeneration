#include <iostream>
#include "SensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4Electron.hh"
#include "DetectorConstruction.hh"

using namespace std;

SensitiveDetector::SensitiveDetector(const G4String& name, const G4String& hitsCollectionName, DetectorConstruction* _det)
: G4VSensitiveDetector(name), hitsCollection(0), hcid(-1), det(_det)
{
  collectionName.insert(hitsCollectionName);
  //  electronHoleCreationEnergy = det->GetElectronHolePairEnergy();
  cout << "Creating Sensitive Detector named: " << name << endl;

}

SensitiveDetector::~SensitiveDetector() {}

void SensitiveDetector::Initialize(G4HCofThisEvent* hce) 
{
  // Create hitsCollection
  hitsCollection = new HitsCollection(SensitiveDetectorName, collectionName[0]);
  if (hcid<0) hcid = G4SDManager::GetSDMpointer()->GetCollectionID(hitsCollection);
  hce->AddHitsCollection(hcid, hitsCollection);

  eventID = -1;

}


G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* history) 
{
    //cout << "Proccessing hit "<< endl;
    G4double totalEnergyDep = step->GetTotalEnergyDeposit();
    G4double nielEnergyDep = step->GetNonIonizingEnergyDeposit();
    G4double ionizingEnergyDep = totalEnergyDep - nielEnergyDep;
    const G4ParticleDefinition* particle = step->GetTrack()->GetParticleDefinition();
    G4int trackID = step->GetTrack()->GetTrackID();
    G4int eventNumber = G4RunManager::GetRunManager()-> GetCurrentEvent()->GetEventID();
    
    return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent* hce)
{
    
}
