#include "DAMICCCDSD.hh"
#include "DAMICCCDHit.hh"
#include "DAMICTrackInformation.hh"
#include "DAMICAnalysisManager.hh"

#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4TouchableHandle.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <cmath>


DAMICCCDSD::DAMICCCDSD(G4String name)
: G4VSensitiveDetector(name), fHitsCollection(0), fHitID(-1)
{
    G4String HCname = "CCDColl";
    collectionName.insert(HCname);
    fPositionCCD = {-305.405, -285.405, -265.405, -245.405, -225.405, -205.405};
    fThickCCD = 0.675*mm;
}


DAMICCCDSD::~DAMICCCDSD()
{}


void DAMICCCDSD::Initialize(G4HCofThisEvent* hce)
{
    fHitsCollection = new DAMICCCDHitsCollection
    (SensitiveDetectorName,collectionName[0]);
    if (fHitID<0)
    { fHitID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection); }
    hce->AddHitsCollection(fHitID,fHitsCollection);
}


G4bool DAMICCCDSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
    //G4cout << " je rentre dans le SD" << G4endl;
    G4AnalysisManager* man = G4AnalysisManager::Instance();
    G4String nameProcess =step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    G4TouchableHandle theTouchablePre = step->GetPreStepPoint()->GetTouchableHandle();
    G4TouchableHandle theTouchable = step->GetPostStepPoint()->GetTouchableHandle();
    G4String volumeNname = theTouchable->GetVolume()->GetLogicalVolume()->GetName();
    G4String volumeNnname = theTouchablePre->GetVolume()->GetLogicalVolume()->GetName();
    //G4cout << nameProcess << G4endl;
    //G4cout << volumeNname << G4endl;
    //G4cout << volumeNnname << G4endl;
    G4ThreeVector preWorldPostion = step->GetPreStepPoint()->GetPosition();
    G4ThreeVector worldPosition = step->GetPostStepPoint()->GetPosition();
    G4ThreeVector localPosition = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldPosition);
    //G4cout << " c'est la position world  " << worldPosition << G4endl;
    //G4cout << " c'est la position locale  " << localPosition << G4endl;
    G4TouchableHistory* touchable
      = (G4TouchableHistory*)(step->GetPreStepPoint()->GetTouchable());
    G4int copyNo = GetCCDNumber(worldPosition.getZ());
    //G4cout << " c la copie" << G4endl;
    //G4cout << copyNo << G4endl;
    G4ThreeVector tesVector = G4ThreeVector(worldPosition.getX(), worldPosition.getY(), fPositionCCD[copyNo-1]);
    G4ThreeVector localTest = theTouchable->GetHistory()->GetTopTransform().TransformPoint(tesVector);
    //G4cout << "tesVector" << tesVector << G4endl;
    //G4cout << " local test" << localTest << G4endl;;
    G4int TopBot = 0;
    G4ThreeVector Position = localPosition;
    if (worldPosition.getZ()>preWorldPostion.getZ()){
      TopBot = 0;
    }
    else if(worldPosition.getZ()<preWorldPostion.getZ()){
      TopBot = 1;
    }
    else{
      TopBot = 2;
    }

    G4double EnergyDep = 0;
    G4int PartIDElec = step->GetTrack()->GetParentID();;
    G4String Process = "NULL";
    //
    G4int PDGNumber = 0;
    G4int PartID = 0;
    G4String ProdVolume = "NULL";
    G4double Energy = 0;
    //Primary Nuc
    G4double Time = 0;
    G4int PDGPrimaryNuc = 0;
    G4int EventID = 0;
    //Secondary Nuc
    G4int PDGSecondaryNuc = 0;
    //Part after Second
    G4int PDGPartASecond = 0;
    G4double EnergyPartASecond = 0;
    // CCD
    G4int CCDNum = copyNo;
    G4String ProcessCreatorName = "NULL";

    if (PartIDElec != 0){
      ProcessCreatorName = step->GetTrack()->GetCreatorProcess()->GetProcessName();
    }
    else{
      ProcessCreatorName ="Prim";
    }

    //G4cout << "bimbimoup" << G4endl;
    DAMICTrackInformation* info = (DAMICTrackInformation*)(step->GetTrack()->GetUserInformation());
    //G4cout << "bimbimoup" << G4endl;
    const std::vector<const G4Track*>*  SecondariesB =step->GetSecondaryInCurrentStep() ;
    const std::vector<const G4Track*> Secondaries = *SecondariesB ;
    //G4cout << "bimbimoup" << G4endl;
    if (nameProcess == "eIoni" || nameProcess == "ionIoni" || nameProcess == "muIoni" )
    {
      //G4cout << " Original Track ID " << info->GetPDGParticle()[1] << G4endl;
      //G4cout << "bimbimoup" << G4endl;
      std::vector<G4int> Particles = info->GetPDGParticle();
      G4int Lenght = Particles.size();
      Process = ProcessCreatorName;
      PDGNumber = Particles[Lenght-1];
      PartID = info->GetParticleID()[Lenght-1];
      ProdVolume = info->GetMaterialProd()[Lenght-1];
      Energy = info->GetEnergyParticle()[Lenght-1];
      G4int PosSecondNuc = 0;
      PDGPrimaryNuc = Particles[0];
      EventID = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
      for (G4int i = 0; i <Lenght; i++){
        G4int result = Particles[i] - 1000000000;
        if (result > 0){
          PosSecondNuc = i;
        }
      }
      PDGSecondaryNuc = Particles[PosSecondNuc];
      //G4cout<< PDGSecondaryNuc << G4endl;
      PDGPartASecond = Particles[PosSecondNuc+1];
      EnergyPartASecond = info->GetEnergyParticle()[PosSecondNuc+1];
      //G4cout << "bimbimoup" << G4endl;



      G4int NumberSecond = step->GetNumberOfSecondariesInCurrentStep();
      for (G4int i =0; i<NumberSecond; i++){
        EnergyDep += Secondaries[i]->GetKineticEnergy();
      }
      EnergyDep += step->GetTotalEnergyDeposit();


      DAMICCCDHit* hit = new DAMICCCDHit(copyNo);
      G4VPhysicalVolume* physical = touchable->GetVolume();

      hit->SetPos(Position);
      hit->SetTopBot(TopBot);
      hit->SetEnergyDeposit(EnergyDep);
      hit->SetProcess(Process);
      hit->SetPartIDElec(PartIDElec);
      //
      hit->SetPDGNumber(PDGNumber);
      hit->SetPartID(PartID);
      hit->SetProdVolume(ProdVolume);
      hit->SetEnergy(Energy);
      //
      hit->SetTime(Time);
      hit->SetPDGPrimaryNuc(PDGPrimaryNuc);
      hit->SetEventID(EventID);
      //
      hit->SetPDGSecondaryNuc(PDGSecondaryNuc);
      //
      hit->SetPDGPartASecond(PDGPartASecond);
      hit->SetEnergyPartASecond(EnergyPartASecond);
      //
      hit->SetCCDNum(CCDNum);
      fHitsCollection->insert(hit);

      G4double XCoord = Position.getX();
      G4double YCoord = Position.getY();
      G4double ZCoord = Position.getZ();
      // Elec deposit
      man->FillNtupleDColumn(0,0,XCoord);
      man->FillNtupleDColumn(0,1,YCoord);
      man->FillNtupleDColumn(0,2,ZCoord);
      man->FillNtupleIColumn(0,3,TopBot);
      man->FillNtupleDColumn(0,4,EnergyDep);
      man->FillNtupleIColumn(0,5,PartIDElec);
      man->FillNtupleSColumn(0,6,Process);
      //Particle that created Elec
      man->FillNtupleIColumn(0,7,PDGNumber);
      man->FillNtupleIColumn(0,8,PartID);
      man->FillNtupleSColumn(0,9,ProdVolume);
      man->FillNtupleDColumn(0,10,Energy);
    /*  // Primary
      man->FillNtupleDColumn(0,11,Time);
      man->FillNtupleIColumn(0,12,PDGPrimaryNuc);
      man->FillNtupleIColumn(0,13,EventID);
      //Secondary Nucleus
      man->FillNtupleIColumn(0,14,PDGSecondaryNuc);
      //Part after Secodary
      man->FillNtupleIColumn(0,15,PDGPartASecond);
      man->FillNtupleDColumn(0,16,EnergyPartASecond);
      // CCD Num
      man->FillNtupleIColumn(0,17,CCDNum);
      man->AddNtupleRow(0);*/

      man->FillNtupleDColumn(0,11,Time);
      man->FillNtupleIColumn(0,12,PDGPrimaryNuc);
      man->FillNtupleIColumn(0,13,EventID);
      //Secondary Nucleus
      man->FillNtupleIColumn(0,14,0);
      //Part after Secodary
      man->FillNtupleIColumn(0,15,0);
      man->FillNtupleDColumn(0,16,0);
      // CCD Num
      man->FillNtupleIColumn(0,17,CCDNum);
      man->AddNtupleRow(0);
    }


    return true;
}

G4int DAMICCCDSD::GetCCDNumber(G4double globZ)
{
  G4int numberCCD = fPositionCCD.size();
  G4int CCDnum = 0;
  for (G4int i = 0;i <=numberCCD;i++){
    G4double space = fabs(globZ) - fabs(fPositionCCD[i]);
    //G4cout << globZ << "     " << fPositionCCD[i] << G4endl;
    //G4cout<< " try " << space << G4endl;
    if (fabs(space) <= fThickCCD/2){
      CCDnum = i+1;
      //G4cout << CCDnum << G4endl;
      break;
    }
  }
  return CCDnum;
}
