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
  G4int IDTrack = aTrack->GetParentID();
  G4int ParticlePDG = aTrack->GetParticleDefinition()->GetPDGEncoding();
  G4double Energy = aTrack->GetKineticEnergy();
  G4String VolumeName = aTrack->GetVolume()->GetName();
  fpTrackingManager->SetStoreTrajectory(true);
  if (IDTrack == 0){
    fpTrackingManager->SetUserTrackInformation(new DAMICTrackInformation(ParticlePDG, Energy, IDTrack, VolumeName));
  }
}


void DAMICTrackingAction::PostUserTrackingAction(const G4Track* aTrack){

  //VTrackingManager = G4TrackingManager->GetTrackingManager();
  G4TrackVector* secondaries = fpTrackingManager->GimmeSecondaries();
  if(secondaries)
    {
      DAMICTrackInformation* info = (DAMICTrackInformation*)(aTrack->GetUserInformation());
      size_t nSeco = secondaries->size();
      if(nSeco>0)
      {
        for(size_t i=0; i < nSeco; i++)
        {
          G4String ProcessCreator;
          G4int IDTrack = (*secondaries)[i]->GetParentID();
          if (IDTrack != 0){
            ProcessCreator = (*secondaries)[i]->GetCreatorProcess()->GetProcessName();
          }
          //ssG4cout << ProcessCreator << G4endl;

          if (ProcessCreator != "eIoni" && ProcessCreator != "ionIoni"){


            //G4cout << i << G4endl;
            G4int ParticlePDG = (*secondaries)[i]->GetParticleDefinition()->GetPDGEncoding();
            //G4cout << ParticlePDG << G4endl;
            G4double Energy = (*secondaries)[i]->GetKineticEnergy();
            G4String VolumeName = (*secondaries)[i]->GetVolume()->GetName();
            //G4cout << ProcessCreator << G4endl;
            
            DAMICTrackInformation* infoNew = new DAMICTrackInformation(info, ParticlePDG, Energy, IDTrack, VolumeName);

            (*secondaries)[i]->SetUserInformation(infoNew);
          }
        }
      }
      //G4cout << nSeco << G4endl;
    }
}
