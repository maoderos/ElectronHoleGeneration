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
  SetUserAction(new RunAction(detector));
}

void ActionInitialization::Build() const
{
  PrimaryGeneratorAction* primary = new PrimaryGeneratorAction();
  SetUserAction(primary);
  SetUserAction(new RunAction(detector, primary));
  SetUserAction(new SteppingAction);
}
#endif