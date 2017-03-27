#include "DAMICTrackingAction.hh"
#include "DAMICTrackInformation.hh"

#include "G4TrackingManager.hh"
#include "G4RunManager.hh"
#include "G4Track.hh"


#include "G4SystemOfUnits.hh"


DAMICTrackingAction::DAMICTrackingAction():G4UserTrackingAction()
{}

DAMICTrackingAction::~DAMICTrackingAction()
{
}

void DAMICTrackingAction::PreUserTrackingAction(const G4Track* aTrack){
  //G4cout << "je rentre dans le trackpre" << G4endl;

  G4int IDTrack = aTrack->GetParentID();
  if (IDTrack == 0){
  G4int ParticlePDG = aTrack->GetParticleDefinition()->GetPDGEncoding();
  G4double Energy = aTrack->GetKineticEnergy();
  G4String VolumeName = aTrack->GetVolume()->GetName();
  G4ThreeVector Position = aTrack->GetPosition();
  G4double vTime = aTrack->GetGlobalTime()/s;
  fpTrackingManager->SetStoreTrajectory(true);


  fpTrackingManager->SetUserTrackInformation(new DAMICTrackInformation(ParticlePDG, Energy, IDTrack, VolumeName, Position, vTime));
  }

}


void DAMICTrackingAction::PostUserTrackingAction(const G4Track* aTrack){
  //G4cout << "je rentre dans le trackpost" << G4endl;
  G4TrackVector* secondaries = fpTrackingManager->GimmeSecondaries();
  if(secondaries)
    {

      DAMICTrackInformation* info = (DAMICTrackInformation*)(aTrack->GetUserInformation());
      size_t nSeco = secondaries->size();
      if(nSeco>0)
      {
        for(size_t i=0; i < nSeco; i++)
        {
          G4int ProcessCreatorSub = -1;
          G4int ProcessCreatorType = -1;
          G4int IDTrack = (*secondaries)[i]->GetParentID();
          G4String VolumeName = "NULL";
          G4double energykin = (*secondaries)[i]->GetKineticEnergy();

          if (IDTrack != 0){
            ProcessCreatorSub = (*secondaries)[i]->GetCreatorProcess()->GetProcessSubType();
            ProcessCreatorType = (*secondaries)[i]->GetCreatorProcess()->GetProcessType();
          }

          G4bool ElecIo = (ProcessCreatorSub == 2 && ProcessCreatorType == 2 && energykin < 20*keV);

          if (!ElecIo){
            VolumeName = (*secondaries)[i]->GetVolume()->GetName();
          }

          G4bool BremCCD = (ProcessCreatorSub == 3  && energykin < 1*keV && VolumeName == "CCDSensor" && ProcessCreatorType == 2);
          G4bool Brem = (ProcessCreatorSub == 3  && energykin < 10*keV && VolumeName != "CCDSensor" && ProcessCreatorType == 2);

          if (!ElecIo && !BremCCD && !Brem){

            G4int ParticlePDG = (*secondaries)[i]->GetParticleDefinition()->GetPDGEncoding();

            G4double Energy = (*secondaries)[i]->GetKineticEnergy();
            G4ThreeVector Position = (*secondaries)[i]->GetPosition();
            G4double vTime = (*secondaries)[i]->GetGlobalTime()/s;

            DAMICTrackInformation* infoNew = new DAMICTrackInformation(info, ParticlePDG, Energy, IDTrack, VolumeName, Position, vTime);

            (*secondaries)[i]->SetUserInformation(infoNew);
          }

        }
      }
    }
}
