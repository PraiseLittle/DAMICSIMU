#include "DAMICStackingAction.hh"

#include "G4RunManager.hh"
#include "G4Track.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


DAMICStackingAction::DAMICStackingAction()
:G4UserStackingAction(),PartName("ez"), PartEnergyKin(0.), PartEnergyTot(0.)
{
}

DAMICStackingAction::~DAMICStackingAction()
{ }

void DAMICStackingAction::SetPartName(G4String name)
{
    PartName = name;
}

void DAMICStackingAction::SetPartEnergyKin(G4double nrj)
{
    PartEnergyKin = nrj;
}

void DAMICStackingAction::SetPartEnergyTot(G4double nrj)
{
    PartEnergyTot = nrj;
}


G4ClassificationOfNewTrack DAMICStackingAction::ClassifyNewTrack(const G4Track* aTrack)
{
    G4String Name = aTrack->GetDefinition()->GetParticleName();
    SetPartName(Name);


    G4double energy = aTrack->GetTotalEnergy();
    G4double energykin = aTrack->GetKineticEnergy();
    SetPartEnergyKin(energykin);
    SetPartEnergyTot(energy);
    G4int IDpart = aTrack->GetParentID();
    if (IDpart != 0){
      return fKill;
    }
    if (energykin<1*eV && Name!="neutron"){
        return fKill;
    }


    return fUrgent;
}
