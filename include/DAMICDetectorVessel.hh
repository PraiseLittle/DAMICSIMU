#ifndef DAMICDetectorVessel_h
#define DAMICDetectorVessel_h

#include "globals.hh"
class G4LogicalVolume;

G4LogicalVolume* GetConstructionLowerEnd();
G4LogicalVolume* GetConstructionLowerTube();
G4LogicalVolume* GetConstructionLowerTubeAll();
G4LogicalVolume* GetConstructionLowerFlange();
G4LogicalVolume* GetConstructionLowerFlangeAll();
G4LogicalVolume* GetConstructionUpperFlange();

#endif
