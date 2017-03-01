#include "DAMICEventAction.hh"
#include "DAMICRunAction.hh"
#include "DAMICAnalysisManager.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"


DAMICEventAction::DAMICEventAction(DAMICRunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction)
{
  ID = 0;
  NamePrimary = "NULL";
  EnergyPrimary = 0;
  AtomicNumber = 0;
  AtomicMass = 0;
}



DAMICEventAction::~DAMICEventAction()
{}



void DAMICEventAction::BeginOfEventAction(const G4Event* Event)
{
  //G4cout << "je rentre dans le eventbeg" << G4endl;
  SetID(Event->GetEventID());
  SetNamePrimary(Event->GetPrimaryVertex()->GetPrimary()->GetParticleDefinition()->GetParticleName());
  SetAtomicNumber( Event->GetPrimaryVertex()->GetPrimary()->GetParticleDefinition()->GetAtomicNumber());
  SetAtomicMass (Event->GetPrimaryVertex()->GetPrimary()->GetParticleDefinition()->GetAtomicMass());
  SetEnergyPrimary(Event->GetPrimaryVertex()->GetPrimary()->GetTotalEnergy());
  G4int eventID = Event->GetEventID();
  if (eventID%100 == 0){
    G4cout << eventID << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DAMICEventAction::EndOfEventAction(const G4Event*)
{
  //G4cout << "je rentre dans le eventend" << G4endl;
}

void DAMICEventAction::SetID(G4int id)
{
    ID = id;
}

void DAMICEventAction::SetNamePrimary(G4String name)
{
    NamePrimary = name;
}

void DAMICEventAction::SetEnergyPrimary(G4double nrj){
    EnergyPrimary = nrj;
}
void DAMICEventAction:: SetAtomicNumber ( G4int Z){
  AtomicNumber = Z;
}

void DAMICEventAction::SetAtomicMass(G4int A){
  AtomicMass = A;
}
