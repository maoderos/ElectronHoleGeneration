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
{

  analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetDefaultFileType("root");
  analysisManager->SetVerboseLevel(0);
  analysisManager->SetActivation(true);  // enable inactivation of histograms
  // Only merge in MT mode to avoid warning when running in Sequential mode
  #ifdef G4MULTITHREADED
  analysisManager->SetNtupleMerging(true);
  #endif
  G4int nbins = 100;
  G4double sensitiveThickness = 100*um;
  analysisManager->CreateH1("Energia depositada (eV)", "Energia depositada", nbins, ((sensitiveThickness - 20*um)/um),(sensitiveThickness/um));
  analysisManager->SetH1Title(0,"Histograma de energia depositada");
  analysisManager->SetH1XAxisTitle(0,"z (um)");
  analysisManager->SetH1YAxisTitle(0, "dE/dx (eV/angstrom)");
  //Create directory for storing data
  analysisManager->CreateNtuple("Event", "Event");
  analysisManager->CreateNtupleDColumn("fdEdxPrimary");
  analysisManager->CreateNtupleDColumn("fEdep");
  analysisManager->CreateNtupleDColumn("fEdepIoni");
  analysisManager->CreateNtupleDColumn("fEdepNiel");
  analysisManager->CreateNtupleDColumn("fPrimaryEnergy");
  analysisManager->CreateNtupleSColumn("fMaterial");
  analysisManager->CreateNtupleDColumn("fCharge");
  analysisManager->FinishNtuple();

  analysisManager->CreateNtuple("Step", "Step");
  analysisManager->CreateNtupleDColumn("fEdep");
  analysisManager->CreateNtupleDColumn("fXPos");
  analysisManager->CreateNtupleDColumn("fYPos");
  analysisManager->CreateNtupleDColumn("fZPos");
  analysisManager->FinishNtuple();

}

RunAction::~RunAction()
{}

void RunAction::BeginOfRunAction(const G4Run* aRun) {

  if(IsMaster()) {
    //cout << "Begin of RunAction" << endl;
    G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

  }

  G4int runId = aRun->GetRunID();
  std::stringstream strRunId;
  strRunId << runId;
  G4String fileName =  "output_" + detectorConstruction->GetMaterialName() + "_" + strRunId.str() + ".root";
  analysisManager->OpenFile(fileName);

  if (primary == nullptr) return;
    // add info to Run object
    //cout << "Finished BeginOfRunAction" << endl;
}

void RunAction::EndOfRunAction(const G4Run* aRun) {
 
  G4int nbofEvents = aRun->GetNumberOfEvent();
  G4double binWidth = analysisManager->GetH1Width(0);
  G4double fac = 1/(nbofEvents*binWidth);
  if(IsMaster()) analysisManager->ScaleH1(0,fac);
  analysisManager->Write();
  analysisManager->CloseFile();
  if (!IsMaster()) return; // if is not the master run, return 
  //std::cout << "End of RunAction" << std::endl;

    
}


