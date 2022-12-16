#include "ActionInitialization.hh"
#if (G4VERSION_NUMBER >= 1000)
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"


ActionInitialization::ActionInitialization(DetectorConstruction* det)
: G4VUserActionInitialization(), detector(det)
{}

ActionInitialization::~ActionInitialization()
{}

void ActionInitialization::BuildForMaster() const
{
  SetUserAction(new RunAction);
}

void ActionInitialization::Build() const
{
  SetUserAction(new PrimaryGeneratorAction);
  SetUserAction(new RunAction);
  SetUserAction(new SteppingAction);
}
#endif
