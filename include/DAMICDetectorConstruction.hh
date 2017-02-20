#ifndef DAMICDetectorConstruction_h
#define DAMICDetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4VSensitiveDetector;


class DAMICDetectorConstruction: public G4VUserDetectorConstruction
{
public:
    DAMICDetectorConstruction();
    ~DAMICDetectorConstruction();
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

private:
    G4bool fCheckOverlaps;
    G4LogicalVolume* fCCDSensor;

};

#endif
