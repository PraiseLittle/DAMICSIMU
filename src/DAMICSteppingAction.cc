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
/*  //G4cout << "cl" << G4endl;
  G4String particle = step->GetTrack()->GetDefinition()->GetParticleName();
  //G4cout << "cla" << G4endl;
  G4String volume = "NULL";
  G4int id = step->GetTrack()->GetParentID();
  //G4cout << "clap" << G4endl;
  if ( particle != "e-" && particle != "anti_nu_e"){
    //G4cout << particle << G4endl;
    volume = step->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetName();
  }
  if (volume == "CCDSensor"){
    G4String inter = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    G4cout << inter << G4endl;
  }*/
}
