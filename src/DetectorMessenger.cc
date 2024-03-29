#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"
#include "G4SystemOfUnits.hh"

DetectorMessenger::DetectorMessenger(DetectorConstruction* _detector)
:detector(_detector)
{

  changeTargetDir = new G4UIdirectory("/setTarget/");
  changeTargetDir -> SetGuidance("Command to set the Target parameters");

  // Change sensitive volume XY
  changeSensitiveThickness = new G4UIcmdWithADoubleAndUnit("/setTarget/sensitiveXY", this);
  changeSensitiveThickness->SetGuidance("Set sensitive volume XYsize");
  changeSensitiveThickness->SetDefaultUnit("um");
  changeSensitiveThickness->SetParameterName("SensitiveXY", false);
  changeSensitiveThickness->SetRange("SensitiveXY>0");
  changeSensitiveThickness->SetUnitCandidates("nm um mm cm");
  changeSensitiveThickness->AvailableForStates(G4State_PreInit, G4State_Idle);


  // Change sensitive volume thickness
  changeSensitiveThickness = new G4UIcmdWithADoubleAndUnit("/setTarget/sensitiveThickness", this);
  changeSensitiveThickness->SetGuidance("Set sensitive volume thickness");
  changeSensitiveThickness->SetDefaultUnit("um");
  changeSensitiveThickness->SetParameterName("SensitiveThickness", false);
  changeSensitiveThickness->SetRange("SensitiveThickness>0");
  changeSensitiveThickness->SetUnitCandidates("nm um mm cm");
  changeSensitiveThickness->AvailableForStates(G4State_PreInit, G4State_Idle);

  // Change sensitive volume material
  changeSensitiveMaterial = new G4UIcmdWithAString("/setTarget/material", this);
  changeSensitiveMaterial->SetGuidance("Set sensitive material");
  changeSensitiveMaterial->SetParameterName("SensitiveMaterial",false);
  changeSensitiveMaterial->SetCandidates("Si SiC C");
  changeSensitiveMaterial->SetDefaultValue("SiC");
  changeSensitiveMaterial->AvailableForStates(G4State_PreInit, G4State_Idle);
}

DetectorMessenger::~DetectorMessenger()
{
  delete changeTargetDir;
  delete changeSensitiveThickness;
  delete changeSensitiveMaterial;
  delete changeSensitiveXY;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  if (command == changeSensitiveThickness) {
    detector->SetSensitiveThickness(changeSensitiveThickness->GetNewDoubleValue(newValue));
  } else if (command == changeSensitiveMaterial) {
    detector->SetSensitiveMaterial(newValue);
  } else if (command == changeSensitiveXY) {
    detector->setSensitiveXY(changeSensitiveXY->GetNewDoubleValue(newValue));
  }
}
