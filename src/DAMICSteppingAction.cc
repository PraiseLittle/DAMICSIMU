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
  G4LogicalVolume* volume
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
  G4AnalysisManager* man = G4AnalysisManager::Instance();
  const G4StepPoint* endPoint = step->GetPostStepPoint();
  const G4StepPoint* begPoint = step->GetPreStepPoint();
  const G4VProcess* process   = endPoint->GetProcessDefinedStep();
  G4String nameProcess = process->GetProcessName();

  G4String NameVol = volume->GetName();
  /*G4String PartName = step->GetTrack()->GetDefinition()->GetParticleName();
  G4String Material = step->GetTrack()->GetMaterial()->GetName();
  G4int IDpart = step->GetTrack()->GetParentID();*/

  G4TouchableHandle theTouchable = endPoint->GetTouchableHandle();
  G4int copyNo = theTouchable->GetCopyNumber();
  G4ThreeVector preWorldPostion = begPoint->GetPosition();
  G4ThreeVector worldPosition = endPoint->GetPosition();
  G4ThreeVector localPosition = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldPosition);


  /*G4double lenghtStep = step->GetStepLength();
  G4double energyDeposit = step->GetTotalEnergyDeposit();
  G4double postest= volume->GetSolid()->DistanceToIn(pos);
  G4int secondaries = step->GetNumberOfSecondariesInCurrentStep();
  G4double PartEnergyTot= step->GetTrack()->GetTotalEnergy();
  G4double energyFin = PartEnergyTot-energyDeposit;

  G4String NamePrimary =  fEventAction->GetNamePrimary();
  G4double EnergyPrimary = fEventAction->GetEnergyPrimary();*/
  G4int IDEvent = fEventAction->GetID();

  G4double XCoord = 0;
  G4double YCoord = 0;
  G4double ZCoord = 0;
  G4int TopBot = 0;
  G4double Energy = 0;
  G4double EnergyDeposit = 0;
  G4int PDGNumber = 0;
  G4int PartID = 0;
  G4String Process = "NULL";
  G4double Time = 0;
  G4int CCDNum = 0;
  G4int PDGMother = 0;
  G4int IDMother = 0;
  G4double MotherEnergy = 0;
  G4String ProdVolume = "NULL";
  G4int APrimary = 0;
  G4int ZPrimary = 0;
  G4int IDPrimary = 0;

  if (IDEvent % 1000 == 0)
  {
    G4cout << " on est à l'event " <<  IDEvent <<G4endl;
  }
  G4String ProcessName = process->GetProcessName();
  if (NameVol == "CCDSensor" && ProcessName != "Transportation"){
    G4cout << step->GetTrack()->GetDefinition()->GetParticleName() << G4endl;

    G4double valueTopBot = worldPosition.getZ() - preWorldPostion.getZ();

    YCoord = localPosition.getY();
    ZCoord = localPosition.getZ();
    if (valueTopBot >= 0 ){
      TopBot = 0;
    }
    else{
      TopBot = 1;
    }
    Energy = step->GetTrack()->GetTotalEnergy();
    EnergyDeposit = step->GetTotalEnergyDeposit();
    PDGNumber = step->GetTrack()->GetDefinition()->GetPDGEncoding();
    PartID = step->GetTrack()->GetParentID();
    Process = ProcessName;
    Time = 0;
    CCDNum = 1;
    PDGMother = PDGNumber;
    IDMother = PartID;
    MotherEnergy = Energy;
    ProdVolume = "TEST";
    APrimary = fEventAction->GetAtomicMass();
    ZPrimary = fEventAction->GetAtomicNumber();
    IDPrimary = fEventAction->GetID();
    man->FillNtupleDColumn(0,0,XCoord);
    man->FillNtupleDColumn(0,1,YCoord);
    man->FillNtupleDColumn(0,2,ZCoord);
    man->FillNtupleIColumn(0,3,TopBot);
    man->FillNtupleDColumn(0,4,Energy);
    man->FillNtupleDColumn(0,5,EnergyDeposit);
    man->FillNtupleIColumn(0,6,PDGNumber);
    man->FillNtupleIColumn(0,7,PartID);
    man->FillNtupleSColumn(0,8,Process);
    man->FillNtupleDColumn(0,9,Time);
    man->FillNtupleIColumn(0,10,CCDNum);
    man->FillNtupleIColumn(0,11,PDGMother);
    man->FillNtupleIColumn(0,12,IDMother);
    man->FillNtupleDColumn(0,13,MotherEnergy);
    man->FillNtupleSColumn(0,14,ProdVolume);
    man->FillNtupleIColumn(0,15,APrimary);
    man->FillNtupleIColumn(0,16,ZPrimary);
    man->FillNtupleIColumn(0,17,IDPrimary);
    man->AddNtupleRow(0);
  }


}
