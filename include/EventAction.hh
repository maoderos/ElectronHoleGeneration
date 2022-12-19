#ifndef EventAction_h
#define EventAction_h 1


#include "G4UserEventAction.hh"
#include "globals.hh"

class PrimaryGeneratorAction;

class EventAction: public G4UserEventAction
{
  public:
    EventAction(PrimaryGeneratorAction*);
    ~EventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

    void AddEdepTotal(G4double eDep) {eDepTotal += eDep;};
    void AddEdepNiel(G4double eDep) {eDepNiel += eDep;};
    void AddEdepIonizing(G4double eDep) {eDepIonizing += eDep;};
    void AddEHNumber(G4int nEH) {numEH += nEH;};
    

  private:
    PrimaryGeneratorAction* primary;
    G4double eDepTotal;
    G4double eDepNiel;
    G4double eDepIonizing;
    G4int numEH;
};

#endif
