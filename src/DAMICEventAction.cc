#include "DAMICEventAction.hh"
#include "DAMICRunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DAMICEventAction::~DAMICEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DAMICEventAction::BeginOfEventAction(const G4Event* Event)
{
  SetID(Event->GetEventID());
  SetNamePrimary(Event->GetPrimaryVertex()->GetPrimary()->GetParticleDefinition()->GetParticleName());
  SetAtomicNumber( Event->GetPrimaryVertex()->GetPrimary()->GetParticleDefinition()->GetAtomicNumber());
  SetAtomicMass (Event->GetPrimaryVertex()->GetPrimary()->GetParticleDefinition()->GetAtomicMass());
  SetEnergyPrimary(Event->GetPrimaryVertex()->GetPrimary()->GetTotalEnergy());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DAMICEventAction::EndOfEventAction(const G4Event*)
{
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
