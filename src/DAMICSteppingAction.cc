#include "DAMICSteppingAction.hh"
#include "DAMICEventAction.hh"
#include "DAMICDetectorConstruction.hh"


#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"


DAMICSteppingAction::DAMICSteppingAction(DAMICEventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction)
{}

DAMICSteppingAction::~DAMICSteppingAction()
{}


void DAMICSteppingAction::UserSteppingAction(const G4Step* step)
{

  G4LogicalVolume* volume
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();

  G4String Name = volume->GetName();

  G4cout << " La particule à toucher le volume: " << Name << G4endl;

}
