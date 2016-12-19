#ifndef DAMICSteppingAction_h
#define DAMICSteppingAction_h

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class DAMICEventAction;

class G4LogicalVolume;


class DAMICSteppingAction : public G4UserSteppingAction
{
  public:
    DAMICSteppingAction(DAMICEventAction* eventAction);
    virtual ~DAMICSteppingAction();

    virtual void UserSteppingAction(const G4Step*);

  private:
    DAMICEventAction*  fEventAction;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
