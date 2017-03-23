#include "DAMICSteppingAction.hh"
#include "DAMICEventAction.hh"
#include "DAMICDetectorConstruction.hh"


#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "DAMICAnalysisManager.hh"
#include "G4TouchableHistoryHandle.hh"
#include "G4TouchableHandle.hh"


DAMICSteppingAction::DAMICSteppingAction(DAMICEventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction)
{}

DAMICSteppingAction::~DAMICSteppingAction()
{}


void DAMICSteppingAction::UserSteppingAction(const G4Step* step)
{

  /*G4String nameProcess =step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
  G4int  subPro = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessSubType();

  if *//*(nameProcess != "eIoni" &&*//* nameProcess != "Transportation" && nameProcess != "Scintillation"){
    G4cout <<  step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessType() << G4endl;
    G4cout << nameProcess << G4endl;
    G4cout << "Process sub type : " << subPro << G4endl;
  }*/
}
