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
/*  G4AnalysisManager* man = G4AnalysisManager::Instance();
  G4String Material = step->GetPreStepPoint()->GetMaterial()->GetName();

  if (Material == "G4_Cu"){
    G4String nameProcess = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    G4int IDPart = step->GetTrack()->GetDefinition()->GetPDGEncoding();
    G4String volumeName = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName();

    if (nameProcess== "eIoni" || nameProcess == "ionIoni" || nameProcess == "compt" || nameProcess == "phot"){
      const G4TrackVector* secondaries = step->GetSecondary();
      size_t nSeco = secondaries->size();
      for (size_t i = 0; i< nSeco; i++){
        G4String NamePart = (*secondaries)[i]->GetParticleDefinition()->GetParticleName();
        G4double EnergyPart = (*secondaries)[i]->GetKineticEnergy();
        if (NamePart == "gamma" ){

          man->FillNtupleSColumn(4,0,volumeName);
          man->FillNtupleDColumn(4,1,EnergyPart);
          man->FillNtupleIColumn(4,2,IDPart);
          man->AddNtupleRow(4);*/
          /*G4cout << nameProcess << G4endl;
          G4cout << volumeName << G4endl;
          G4cout << "Partcle Name: "  << namePart << G4endl;
          G4cout << " Secondaire " << i  << "  :" << NamePart << G4endl;
          G4cout << " Energy :" << EnergyPart << G4endl;*/
        /*}
      }
    }
  }*/
}
