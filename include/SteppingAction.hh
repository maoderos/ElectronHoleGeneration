#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"

class DetectorConstruction;
class PrimaryGeneratorAction;

class SteppingAction: public G4UserSteppingAction {
  public:
    SteppingAction(DetectorConstruction*, PrimaryGeneratorAction*);
    virtual ~SteppingAction();

    virtual void UserSteppingAction(const G4Step*);
  private:
    DetectorConstruction* det;
    PrimaryGeneratorAction* primary;

};

#endif
