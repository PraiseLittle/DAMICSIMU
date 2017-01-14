#include "DAMICEventAction.hh"
#include "DAMICRunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DAMICEventAction::DAMICEventAction(DAMICRunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DAMICEventAction::~DAMICEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DAMICEventAction::BeginOfEventAction(const G4Event* Event)
{
  SetID(Event->GetEventID());
  SetNamePrimary(Event->GetPrimaryVertex()->GetPrimary()->GetParticleDefinition()->GetParticleName());
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
