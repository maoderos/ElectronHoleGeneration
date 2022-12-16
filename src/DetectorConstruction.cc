#include <iostream>
#include <map>
#include "DetectorConstruction.hh"
#include "G4MTRunManager.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4VisAttributes.hh"
#include "G4Element.hh"
#include "G4Box.hh"
#include "G4UserLimits.hh"
#include "G4SDManager.hh"
#include "G4ProductionCuts.hh"


//G4ThreadLocal G4UniformElectricField* DetectorConstruction::fEMfield = 0;
// Constructor
DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(), logicWorld(0),physWorld(0), worldMaterial(0), sensitiveThickness(2*cm), materialName("SiC")
{
    detectorMessenger = new DetectorMessenger(this);
    DefineMaterials();
}

// Destructor
DetectorConstruction::~DetectorConstruction(){
  delete detectorMessenger;
}

void DetectorConstruction::DefineMaterials(){

    // Get materials from NIST database
    G4NistManager* nist = G4NistManager::Instance();

    // Creating world material - Vaccumm
    worldMaterial = nist->FindOrBuildMaterial("G4_Galactic");
    //Si
    siMaterial = nist->FindOrBuildMaterial("G4_Si");
    electronHolePairEnergyMaterial["Si"] = 3.6*eV; //doi: 10.3390/s18072289
    //C - Diamond
    cMaterial = nist->FindOrBuildMaterial("G4_C");
    electronHolePairEnergyMaterial["C"] = 13.0*eV;
    //SiC - Silicon Carbide 

    sicMaterial = new G4Material("G4_SiC", 3.16*g/cm3, 2);
    sicMaterial->AddMaterial(siMaterial, 50*perCent);
    sicMaterial->AddMaterial(cMaterial, 50*perCent);
    electronHolePairEnergyMaterial["SiC"] = 8.4*eV; //doi: 10.3390/s18072289

    sensitiveMaterial = sicMaterial;
}

G4VPhysicalVolume* DetectorConstruction::Construct(){

    //World Geometry
    G4double size_xyz = 4*cm;

    G4Box* solidWorld = new G4Box("BoxWorld", 0.5*size_xyz, 0.5*size_xyz, 0.5*size_xyz);
    logicWorld = new G4LogicalVolume(solidWorld, worldMaterial,"logicWorld");
    physWorld = new G4PVPlacement(0,G4ThreeVector(), logicWorld, "World",0,false,0);

    G4cout << "Drawing target of " << sensitiveMaterial->GetName() << "material" << G4endl;

    G4double targetSizeXY = 2*cm;
    solidSensitive = new G4Box("boxSensitive", targetSizeXY, targetSizeXY, 0.5*sensitiveThickness);
    logicSensitive = new G4LogicalVolume(solidSensitive, sensitiveMaterial, "logicSensitive");
    physSensitive = new G4PVPlacement(0,G4ThreeVector(0,0,0.5*sensitiveThickness), logicSensitive, "Sensitive", logicWorld, false, 0, true);

    // World Visualization
    G4VisAttributes* worldVis = new G4VisAttributes();
    worldVis->SetColor(0.1, 0.3, 0.8, 0.5);
    logicWorld->SetVisAttributes(worldVis);

    //Sensitive visualization
    G4VisAttributes* sensitiveVis = new G4VisAttributes();
    sensitiveVis->SetColor(1.0, 0.0, 0); //red
    logicSensitive->SetVisAttributes(sensitiveVis);

    return physWorld;

}

void DetectorConstruction::ConstructSDandField()
{
  
}

void DetectorConstruction::SetSensitiveThickness(G4double value){
  sensitiveThickness = value/2;
  G4cout << "Changing sensitive volume thickness" << G4endl;
  G4MTRunManager::GetRunManager()->ReinitializeGeometry();
}

G4bool DetectorConstruction::SetSensitiveMaterial(const G4String& value) {
  if (value == "Si") {
    sensitiveMaterial = siMaterial;
  } else if (value == "SiC") {
    sensitiveMaterial = sicMaterial;
  } else if (value == "C") {
    sensitiveMaterial = cMaterial;
  }

    electronHolePairEnergy = electronHolePairEnergyMaterial[value];
    materialName = value;

  if (logicSensitive){
    logicSensitive->SetMaterial(sensitiveMaterial);
    G4MTRunManager::GetRunManager()->PhysicsHasBeenModified();
    G4MTRunManager::GetRunManager()->GeometryHasBeenModified();
    G4cout << "The material of the sensitive volume has been changed to " << sensitiveMaterial << G4endl;
  }
  return true;
}
