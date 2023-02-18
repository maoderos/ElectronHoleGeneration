#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4String.hh"

#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Optionally: choose a different Random engine...
   G4Random::setTheEngine(new CLHEP::RanecuEngine);
  
   G4String macro = "noMacro";
   G4int nThreads = 1;
  // Parsing argumetns 
   for (G4int i = 1; i < argc; i=i+2) {
     if (G4String(argv[i]) == "-m") {
       macro = argv[i+1];
     }
     else if (G4String(argv[i]) == "-t") {
       nThreads = G4UIcommand::ConvertToInt(argv[i+1]);
     }
   }
  // Construct the default run manager
  #ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  runManager->SetNumberOfThreads(nThreads);
  #else
  G4RunManager* runManager = new G4RunManager;
  #endif

  // Set mandatory initialization classes
  //
  // Detector construction
  DetectorConstruction* detector = new DetectorConstruction();
  runManager->SetUserInitialization(detector);

  // Physics list
  G4PhysListFactory physListFactory;
  const G4String plName = "FTFP_BERT_EMZ";
  G4VModularPhysicsList* pList = physListFactory.GetReferencePhysList(plName);
  pList->RegisterPhysics(new G4StepLimiterPhysics());
  runManager->SetUserInitialization(pList);
    
  // User action initialization
  runManager->SetUserInitialization(new ActionInitialization(detector));
  
  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  time_t systime = time(NULL);
  long seed = (long) systime;
  //long seed = 0;
  G4Random::setTheSeed(seed);

  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = macro;
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
  delete visManager;
  delete runManager;
}
