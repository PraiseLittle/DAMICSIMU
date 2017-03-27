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
    DAMICStackingActionMessenger(DAMICStackingAction *fStackSource);
    ~DAMICStackingActionMessenger();

  void SetNewValue(G4UIcommand *command, G4String newValues);


  private:

    DAMICStackingAction *fStackAction;
    G4ParticleTable *particleTable;

  private:

    G4UIdirectory* stackDirectory;
    G4UIcmdWithoutParameter* ListCmd;

    G4UIcommand* IonLimitCmd;
    G4UIcmdWithAString* AddPartKillCmd;
    G4UIcmdWithoutParameter* ResetCmd;

};
#endif
