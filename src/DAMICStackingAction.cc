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
    //G4cout << "je rentre ClassifyNewTrack" << G4endl;
    G4double energy = aTrack->GetTotalEnergy();
    G4double energykin = aTrack->GetKineticEnergy();
    SetPartEnergyKin(energykin);
    SetPartEnergyTot(energy);
    G4int IDpart = aTrack->GetParentID();
    G4int ProcessCreatorSub;
    G4int ProcessCreatorType;

    G4String nameVolume = "NULL";

    if (IDpart != 0){
      ProcessCreatorSub = aTrack->GetCreatorProcess()->GetProcessSubType();
      ProcessCreatorType = aTrack->GetCreatorProcess()->GetProcessType();
      nameVolume = aTrack->GetVolume()->GetLogicalVolume()->GetName();
    }
    else {
      ProcessCreatorSub = -1;
      ProcessCreatorType = -1;
      nameVolume = "NULL";
    }
    if (energykin<1*eV && Name=="e-"){ // Kill particles with less than 1 eV  kinetic energy
        return fKill;
    }
    if ((ProcessCreatorSub == 2 || ProcessCreatorSub == 3 ) && energykin < 10*keV && nameVolume == "CCDSensor" && ProcessCreatorType == 2)
    {
      return fKill;
    }
    if (ProcessCreatorSub == 2 && ProcessCreatorType == 2){//&& energykin < 20*keV)){
      return fKill;
    }
    G4cout << Name<< G4endl;
    return fUrgent;
}
