#ifndef RUNACTION_h
#define RUNACTION_h 1


#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"

class DetectorConstruction;
class PrimaryGeneratorAction;

class RunAction: public G4UserRunAction
{
    public:
        RunAction(DetectorConstruction* _det, PrimaryGeneratorAction* _primary = nullptr);
        ~RunAction();

        void BeginOfRunAction(const G4Run*);
        void EndOfRunAction(const G4Run*);
    
    private:
        DetectorConstruction* detectorConstruction;
        PrimaryGeneratorAction* primary;
        G4AnalysisManager* analysisManager;
}; 

#endif
