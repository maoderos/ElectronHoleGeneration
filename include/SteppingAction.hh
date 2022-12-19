#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"

class DetectorConstruction;
class PrimaryGeneratorAction;
class EventAction;

class SteppingAction: public G4UserSteppingAction {
  public:
    SteppingAction(EventAction*, DetectorConstruction*, PrimaryGeneratorAction*);
    virtual ~SteppingAction();

    virtual void UserSteppingAction(const G4Step*);
  private:
    EventAction* evt;
    DetectorConstruction* det;
    PrimaryGeneratorAction* primary;

};

#endif
