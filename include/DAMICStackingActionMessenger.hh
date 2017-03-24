#ifndef DAMICStackingActionMessenger_h
#define DAMICStackingActionMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class DAMICStackingAction;

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


class DAMICStackingActionMessenger: public G4UImessenger{

  public:
    DAMICStackingActionMessenger(DAMICStackingAction *fPartSource);
    ~DAMICStackingActionMessenger();

  void SetNewValue(G4UIcommand *command, G4String newValues);

  private:

    DAMICStackingAction *fParticleGun;
    G4ParticleTable *particleTable;

  private:

    G4UIdirectory* gunDirectory;

    G4UIcommand* IonLastCmd;

};
#endif
