#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1


#include "G4VUserDetectorConstruction.hh"
#include "G4Version.hh"
#include "G4Material.hh"
#include "G4String.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "DetectorMessenger.hh"

class G4Region;

class DetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        DetectorConstruction();
        virtual ~DetectorConstruction();

        virtual G4VPhysicalVolume* Construct();
        virtual void ConstructSDandField();
        void SetSensitiveThickness(G4double value);
        G4bool SetSensitiveMaterial(const G4String& value);
        inline G4double GetSensitiveThickness() const {return sensitiveThickness;};
        inline G4Material* GetSensitiveMaterial() const {return sensitiveMaterial;};
        inline G4double GetElectronHolePairEnergy() const {return electronHolePairEnergy;}
        inline G4String GetMaterialName() const {return materialName;};

    private:
        void DefineMaterials();

        DetectorMessenger* detectorMessenger;

        // World
        G4LogicalVolume* logicWorld;
        G4VPhysicalVolume* physWorld;
        G4Material* worldMaterial;
        // Sensitive volume
        G4Box* solidSensitive;
        G4LogicalVolume* logicSensitive;
        G4VPhysicalVolume* physSensitive;
        G4Material* sensitiveMaterial;
        G4double sensitiveThickness;
        // Materials
        G4Material* siMaterial;
        G4Material* sicMaterial;
        G4Material* cMaterial;

        std::map<G4String, G4double> electronHolePairEnergyMaterial;
        G4double electronHolePairEnergy;
        G4String materialName;
};
#endif
