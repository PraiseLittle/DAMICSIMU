#ifndef DAMICParticleSourceMessenger_h
#define DAMICParticleSourceMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class DAMICParticleSource;

class G4ParticleTable;
class G4UIcommand;
class G4UIdirectory;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3Vector;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithABool;
class G4UIcmdWithoutParameter;

class DAMICParticleSourceMessenger: public G4UImessenger{

  public:
    DAMICParticleSourceMessenger(DAMICParticleSource *fPartSource);
    ~DAMICParticleSourceMessenger();

    void SetNewValue(G4UIcommand *command, G4String newValues);

  private:

    DAMICParticleSource *fParticleGun;
    G4ParticleTable *particleTable;

  private:
    G4UIdirectory *gunDirectory;

    G4UIcmdWithADoubleAndUnit* EnergyCmd;
    G4UIcmdWithADouble* ChargeCmd;
    G4UIcmdWith3Vector* MomentumCmd;
    G4UIcmdWithAString* ParticleCmd;
    G4UIcmdWith3VectorAndUnit* PositionSourceCmd;
    G4UIcmdWithAString* VolumeSourceCmd;
    G4UIcmdWithAString* MaterialSourceCmd;
    G4UIcmdWithAString* MotherSourceCmd;
    G4UIcmdWithoutParameter* DoVolumeCmd;
    G4UIcmdWithoutParameter* DoMaterialCmd;
    G4UIcmdWithoutParameter* DoSourceCmd;
    G4UIcommand* IonCmd;
    G4UIcmdWithoutParameter* ListCmd;

  private:
    G4bool   fShootIon;
    G4int    fAtomicNumber;
    G4int    fAtomicMass;
    G4int    fIonCharge;
    G4double fIonExciteEnergy;
};

#endif
