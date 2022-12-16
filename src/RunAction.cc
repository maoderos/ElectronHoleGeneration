#include "RunAction.hh"
#include "Run.hh"
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

G4Run* RunAction::GenerateRun(){
    cout << "Generating Run" << endl;
    run = new Run();
    cout << "Run generated successfully" << endl;
    return run;
}

void RunAction::BeginOfRunAction(const G4Run* aRun) {

  if(IsMaster()) {
    cout << "Begin of RunAction" << endl;
    G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

  }

    
    if (primary == nullptr) return;
    // add info to Run object
    run->SetPrimaryInformation(primary->GetParticleGun()->GetParticleDefinition(),  primary->GetParticleGun()->GetParticleEnergy());
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

    
    /*
    // Create a directory for storing the data 
    stringstream resultFolder;
    resultFolder << "./result/";
    
    // if forlder does not exist, create one
     if(!filesystem::exists(resultFolder.str().c_str())){
        G4String command_mkdir = "mkdir -p " + resultFolder.str();
        int mkdirFlag = system(command_mkdir.c_str());
        if(mkdirFlag == -1){
        G4cerr << "mkdir command is not performed in your system!!" << G4endl;
        }
     }

    
    ofstream ofp;
    stringstream resultFileName;

    resultFileName << resultFolder.str() << "data.dat";

    // If file does not exist, create file and add header
    if(!filesystem::exists(resultFileName.str().c_str())){
        ofp.open(resultFileName.str().c_str());
        ofp << "Thickness(um) Edep(MeV) Error(%) KinecticEnergy(MeV) ElectronsInSi ElectronsInMetal ElectronHolePairs" << G4endl;
    } else {
        ofp.open(resultFileName.str().c_str(),ios_base::app);
    }

    Run* theRun = (Run*)aRun;
    //Calculate mean Edep and error

    G4double eDep = theRun->GetEDep()/(MeV);
    G4double nEvent = theRun->GetNEvent();
    G4double squaredEdep = theRun->GetSquaredEDep();
    G4double meanEDep = eDep/nEvent;
    G4double varianceEdep = (squaredEdep/nEvent - (meanEDep*meanEDep)/nEvent)/(nEvent-1);
    G4double primaryEnergy = theRun->GetKineticEnergy()/(MeV);

    ofp << detectorConstruction->GetSensitiveThickness()/(um) << " " << meanEDep/(MeV) << " " 
        << sqrt(sqrt(varianceEdep*varianceEdep)) << " " << primaryEnergy << " " << electronsInSensitive << " " << electronsInMetal << " " << electronHolePairs << " " << G4endl;

    ofp.close();
*/
}

void RunAction::BookHisto() {
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in HistoManager.hh
  std::cout << "BookHisto" << std::endl;
  analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetDefaultFileType("root");
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetActivation(true);  // enable inactivation of histograms
  G4int nbins = 100;
  //analysisManager->CreateH1("Edep","Edep in sensitive volume", nbins,(2*detectorConstruction->GetMetalThickness())/(um),(2*detectorConstruction->GetMetalThickness() + 2*detectorConstruction->GetSensitiveThickness())/(um));
  
  analysisManager->CreateNtuple("SiDetector", "physics");
  analysisManager->SetNtupleMerging(true); //So that all is joined in one file
  analysisManager->FinishNtuple();
  
  G4String fileName = "output.root";
  analysisManager->OpenFile(fileName);
  
}


