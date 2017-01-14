#include "DAMICSteppingAction.hh"
#include "DAMICEventAction.hh"
#include "DAMICDetectorConstruction.hh"


#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "DAMICAnalysisManager.hh"


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
  G4AnalysisManager* man = G4AnalysisManager::Instance();

  const G4StepPoint* endPoint = step->GetPostStepPoint();
  const G4VProcess* process   = endPoint->GetProcessDefinedStep();
  G4String nameProcess = process->GetProcessName();

  G4String PartName = step->GetTrack()->GetDefinition()->GetParticleName();
  G4String Material = step->GetTrack()->GetMaterial()->GetName();
  G4int IDpart = step->GetTrack()->GetParentID();

  G4String NameVol = volume->GetName();
  G4ThreeVector pos = step->GetPreStepPoint()->GetPosition();
  G4ThreeVector pos2 = step->GetPostStepPoint()->GetPosition();
  G4double lenghtStep = step->GetStepLength();
  G4double energyDeposit = step->GetTotalEnergyDeposit();
  G4double postest= volume->GetSolid()->DistanceToIn(pos);
  G4int secondaries = step->GetNumberOfSecondariesInCurrentStep();
  G4double PartEnergyTot= step->GetTrack()->GetTotalEnergy();
  G4double energyFin = PartEnergyTot-energyDeposit;
  G4int IDEvent = fEventAction->GetID();
  G4String NamePrimary =  fEventAction->GetNamePrimary();
  G4double EnergyPrimary = fEventAction->GetEnergyPrimary();

  man->FillNtupleSColumn(0,0,NamePrimary);
  man->FillNtupleDColumn(0,1,EnergyPrimary);
  man->FillNtupleIColumn(0,2,IDEvent);
  man->FillNtupleSColumn(0,3,PartName);
  man->FillNtupleIColumn(0,4,IDpart);
  man->FillNtupleDColumn(0,5,energyDeposit);
  man->FillNtupleDColumn(0,6,PartEnergyTot);
  man->FillNtupleDColumn(0,7,energyFin);
  man->FillNtupleSColumn(0,8,nameProcess);
  man->FillNtupleDColumn(0,9,pos[0]);
  man->FillNtupleDColumn(0,10,pos[1]);
  man->FillNtupleDColumn(0,11,pos[2]);
  man->FillNtupleDColumn(0,12,pos2[0]);
  man->FillNtupleDColumn(0,13,pos2[1]);
  man->FillNtupleDColumn(0,14,pos2[2]);
  man->FillNtupleDColumn(0,15,lenghtStep);
  man->FillNtupleSColumn(0,16,NameVol);
  man->FillNtupleSColumn(0,17,Material);
  man->FillNtupleIColumn(0,18,secondaries);
  man->AddNtupleRow(0);
  if (IDEvent%100 == 0 && IDpart == 0){
    G4cout << "NUMERO" << IDEvent << G4endl;

  }

}
