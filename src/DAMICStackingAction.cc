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
    /*G4String Name = aTrack->GetDefinition()->GetParticleName();
    SetPartName(Name);
    //G4cout << "je rentre dans le stack" << G4endl;
    //G4cout << "bimbimoup" << G4endl;
    G4double energy = aTrack->GetTotalEnergy();
    G4double energykin = aTrack->GetKineticEnergy();
    SetPartEnergyKin(energykin);
    SetPartEnergyTot(energy);*/
    G4int IDpart = aTrack->GetParentID();
    G4String ProcessCreatorName;
    if (IDpart != 0){

      return fKill;
      ProcessCreatorName = aTrack->GetCreatorProcess()->GetProcessName();
    }
    /*if (energykin<1*eV && Name=="e-"){ // Kill particles with less than 1 eV  kinetic energy
        return fKill;
    }
    if (ProcessCreatorName == "eIoni" || ProcessCreatorName == "ionIoni" || ProcessCreatorName == "muIoni")
    {
      //G4cout << Name << G4endl;
      return fKill;
    }
    //G4cout << ProcessCreatorName << G4endl;
    //G4cout <<" je sors du stack "<< G4endl;*/
    return fUrgent;
}
