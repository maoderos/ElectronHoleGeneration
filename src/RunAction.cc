#include "RunAction.hh"
#include "G4Run.hh"
#include "G4MTRunManager.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4EmCalculator.hh"
#include <sstream>
#include <filesystem>
#include <iostream>

using namespace std;

RunAction::RunAction(DetectorConstruction* _det, PrimaryGeneratorAction* _primary) : G4UserRunAction(), detectorConstruction(_det), primary(_primary), analysisManager(0)
{}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run* aRun) {

  if(IsMaster()) {
    cout << "Begin of RunAction" << endl;
    G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

  }
    
    if (primary == nullptr) return;
    // add info to Run object
    cout << "Finished BeginOfRunAction" << endl;
}

void RunAction::EndOfRunAction(const G4Run* aRun) {
    cout << "End of RunAction" << endl;
    /*
    if(analysisManager->IsActive()) {
      analysisManager->Write();
      analysisManager->CloseFile();
    }
    analysisManager->Clear();
    */
    if (!IsMaster()) return; // if is not the master run, return 

    
}

void RunAction::BookHisto() {
  // Create or get analysis manager
  std::cout << "BookHisto" << std::endl;
  analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetDefaultFileType("root");
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetActivation(true);  // enable inactivation of histograms
  
  analysisManager->CreateNtuple("PrimaryParticle", "PrimaryParticle");
  analysisManager->CreateNtupleDColumn("fEdep");
  analysisManager->CreateNtupleDColumn("fEdepIoni");
  analysisManager->CreateNtupleDColumn("fEdepNiel");
  analysisManager->CreateNtupleDColumn("fPrimaryEnergy");
  analysisManager->CreateNtupleDColumn("fZPos");
  analysisManager->CreateNtupleSColumn("fMaterial");
  analysisManager->SetNtupleMerging(true); //So that all is joined in one file
  analysisManager->FinishNtuple(0);
  
  analysisManager->CreateNtuple("Electron-Hole", "Electron-Hole");
  analysisManager->CreateNtupleIColumn("fNumberEH");
  analysisManager->CreateNtupleDColumn("fXPos");
  analysisManager->CreateNtupleDColumn("fYPos");
  analysisManager->CreateNtupleDColumn("fZPos");
  analysisManager->SetNtupleMerging(true);
  analysisManager->FinishNtuple(1);
  G4String fileName = "output.root";
  analysisManager->OpenFile(fileName);
  
}


