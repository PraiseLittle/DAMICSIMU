#include <cmath>

#include "DAMICParticleSource.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4PrimaryParticle.hh"
#include "G4Event.hh"
#include "Randomize.hh"
#include "G4TransportationManager.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4IonTable.hh"
#include "G4Ions.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "G4Material.hh"


DAMICParticleSource::DAMICParticleSource(){

      ParticleEnergy= 0.0* MeV;
      ParticleCharge = 0.0;
      ParticleMomentumDirection = G4ParticleMomentum(1.,0.,0.);
      ParticleTime = 0.0;
      ParticleDefinition = NULL;
      ParticlePosition = G4ThreeVector(0.,0.,0.0);

      //Position
      bSurface = false; //True on surface
      bVolume = false; //True if Volume
      bMaterial = false;
      SourcePosition = G4ThreeVector(0.0,0.0,0.0);
      VolumeSource = "Volume"; // choose between Volume and Material
      MotherVolume = "MotherVolume";
      Material = "Material";
      MaterialSource = "MaterialSource";
      VolumesUse = {};
      VolumesUseMass = {};
      VolumesConcentration = {};
      Proba = {};
      changes = false;

      //Navigator for Geometry
      gNavigator = G4TransportationManager::GetTransportationManager()
    ->GetNavigatorForTracking();

    //Messenger
    Messenger = new DAMICParticleSourceMessenger(this);
}

DAMICParticleSource::~DAMICParticleSource(){
  delete Messenger;
}

void DAMICParticleSource::SetParticleEnergy(G4double Energy){
  ParticleEnergy = Energy;
}

void DAMICParticleSource::SetParticleCharge(G4double Charge){
  ParticleCharge = Charge;
}

void DAMICParticleSource::SetParticleMomentumDirection(G4ParticleMomentum Momentum){
  ParticleMomentumDirection = Momentum;
}

void DAMICParticleSource::SetParticleTime(G4double Time){
  ParticleTime = Time;
}

void DAMICParticleSource::SetParticleDefinition(G4ParticleDefinition* Def){
  ParticleDefinition = Def;
  G4double charge = ParticleDefinition->GetPDGCharge();
  SetParticleCharge(charge);
}

void DAMICParticleSource::SetParticlePosition(G4ThreeVector Pos){
  ParticlePosition = Pos;
}

//POSITION SETS

void DAMICParticleSource::SetSourcePosition(G4ThreeVector Source){
  SourcePosition = Source;
}

void DAMICParticleSource::SetMaterial(G4String Mat){
  Material = Mat;
}

void DAMICParticleSource::SetVolumeSource(G4String Vol){
  VolumeSource = Vol;
}

void DAMICParticleSource::SetMaterialSource(G4String MatSource){
  Material = MatSource;
}

void DAMICParticleSource::SetMotherVolume(G4String MotherVol){
  MotherVolume = MotherVol;
}
//Position Sets

void DAMICParticleSource::SetSurface(G4bool Sur){
  bSurface = Sur;
}

void DAMICParticleSource::SetVolume(G4bool Vol){
  bVolume = Vol;
}

void DAMICParticleSource::SetMaterial(G4bool Mat){
  bMaterial = Mat;
}

G4bool DAMICParticleSource::IsSurface(){
  return bSurface;
}

G4bool DAMICParticleSource::IsVolume(){
  return bVolume;
}

G4bool DAMICParticleSource::IsMaterial(){
  return bMaterial;
}

void DAMICParticleSource::DoVolume(){
  SetMaterial(false);
  SetVolume(true);
}

void DAMICParticleSource::DoMaterial(){
  SetMaterial(true);
  SetVolume(false);
}

void DAMICParticleSource::DoSource(){
  SetMaterial(false);
  SetVolume(false);
}

void DAMICParticleSource::AddVolume(G4String Volume, G4double Concentration){


  G4PhysicalVolumeStore* PVStore = G4PhysicalVolumeStore::GetInstance();
  G4int i = 0;
  G4bool found = false;
  G4double Mass;
  G4double Dens;
  G4VPhysicalVolume* tempPV;
  //G4cout << " je suis addvol" << G4endl;
  while (!found && i<(G4int)PVStore->size())
    {
      tempPV = (*PVStore)[i];
      found  = tempPV->GetName() == Volume;

      if (!found){i++;}
    }
    //G4cout << found << G4endl;


  if(found == true) {
    Mass = tempPV->GetLogicalVolume()->GetMass();
  }
  else {
    G4cout << " **** Error: Volume does not exist **** " << G4endl;
    G4cout << " Ignoring confine condition" << G4endl;

    Mass = 0;
  }
  G4int sizeV= VolumesUse.size();
  G4bool same = false;
  //G4cout << sizeV << G4endl;
  if ( sizeV != 0){
    for (G4int j = 0;j<sizeV;j++){
      if (VolumesUse[j]==Volume)
      {
        //G4cout << " ca change " << G4endl;
        same = true;
      }
    }
  }
  //G4cout << same << G4endl;
  if (!same){
    VolumesUse.push_back(Volume);
    VolumesUseMass.push_back(Mass);
    VolumesConcentration.push_back(Concentration);
    changes = true;
  }


  VolumesConcentration.push_back(Concentration);
}

void DAMICParticleSource::CalculProba()
{
  G4cout << " je suis calcProba" << G4endl;
  if (changes){
    //G4cout << "changes" << G4endl;
    Proba={};
    G4double total = 0;
    G4int sizevols = VolumesUse.size();
    G4cout << sizevols << G4endl;
    for (G4int i = 0; i <sizevols; i++){
      G4double temp = VolumesConcentration[i]*VolumesUseMass[i];
      total += temp;
      Proba.push_back(temp);
    }

    for (G4int i =0; i <sizevols; i++){
      Proba[i] = Proba[i]/total;
      //G4cout << Proba[i] << G4endl;
    }
    changes = false;
    for (G4int i =1; i <sizevols;i++){
      Proba[i] += Proba[i-1];
      //G4cout << Proba[i] << G4endl;
    }
  }
}

void DAMICParticleSource::ChooseVolume()
{
  G4cout << " je suis chovol" << G4endl;
  G4double tryVol = 1*G4UniformRand();
  G4bool found = false;
  G4int i = 0;
  while(!found){
    if (tryVol <= Proba[i]){
      G4cout << VolumesUse[i] << G4endl;

      found = true;
      VolumeSource = VolumesUse[i];
    }
    i++;
  }
  G4cout << VolumeSource << G4endl;
}

void DAMICParticleSource::CalculPosition(G4String MotherUse, G4String MaterialUse, G4String VolumeUse){

  G4double posx = 0;
  G4double posy = 0;
  G4double posz = 0;
  G4bool found = false;
  G4VPhysicalVolume* theVolume;
  G4String theVolName;
  G4String theMaterialName;
  G4bool MaterialFit;
  G4bool VolumeFit;
  while(!found){
    if (MotherUse == "WorldLV" ){
      posx = 2.0*m*G4UniformRand()-1*m;
      posy = 2.0*m*G4UniformRand()-1*m;
      posz = 2.0*m*G4UniformRand()-1*m;
    }
    else if (MotherUse == "VesselLV" || MotherUse =="Assembly1"|| MotherUse =="Assembly2"){
      posx = 2.0*m*G4UniformRand()-1*m;
      posy = 2.0*m*G4UniformRand()-1*m;
      posz = 2.0*m*G4UniformRand()-1*m;
    }
    else if (MotherUse == "PrinTubLV"){
      //G4cout << "ici" << G4endl;

      G4double RadiusRan = 191.287/2*mm * G4UniformRand();
      G4double AngleRan = M_PI*2*G4UniformRand();
      G4double HeightRan = 413.512*mm *(G4UniformRand()-0.5);
      posx = RadiusRan* cos(AngleRan);
      posy = RadiusRan* sin(AngleRan);
      posz = -120*mm+ HeightRan;
    }
    else {
      G4double tempX = 120*mm*(G4UniformRand()-0.5);
      G4double tempY = 120*mm*(G4UniformRand()-0.5);
      G4double tempZ = 160*mm*(G4UniformRand()-0.5);
      posx = tempX;
      posy = tempY;
      posz = tempZ -120*mm - 121.5*mm;
    }
    G4ThreeVector *ptr;
    theVolume=gNavigator->LocateGlobalPointAndSetup(G4ThreeVector(posx,posy, posz),ptr,true);
    theVolName = theVolume->GetName();
    theMaterialName = theVolume->GetLogicalVolume()->GetMaterial()->GetName();

    MaterialFit = theMaterialName == MaterialUse;
    VolumeFit = theVolName == VolumeUse;
    if (MaterialFit && IsMaterial()){
      found = true;
    }
    if (VolumeFit && IsVolume()){
      found = true;
    }
  }
  SourcePosition = G4ThreeVector(posx, posy, posz);

}


void DAMICParticleSource::MaterialCoordinates(){
  CalculPosition(MotherVolume, Material, "NULL");
}

void DAMICParticleSource::VolumeCoordinates(){
  G4VPhysicalVolume *tempPV      = NULL;
  G4PhysicalVolumeStore *PVStore = 0;
  G4String theRequiredVolumeName = VolumeSource;
  PVStore = G4PhysicalVolumeStore::GetInstance();

  G4int i = 0;
  G4bool found = false;
  while (!found && i<(G4int)PVStore->size())
    {
      tempPV = (*PVStore)[i];
      found  = tempPV->GetName() == theRequiredVolumeName;

      if (!found){i++;}
    }


  if(found == true) {
      SetMotherVolume(tempPV->GetMotherLogical()->GetName());
      SetMaterial(tempPV->GetLogicalVolume()->GetMaterial()->GetName());
      CalculPosition(MotherVolume, Material, VolumeSource);
  }
  else {
    G4cout << " **** Error: Volume does not exist **** " << G4endl;
    G4cout << " Ignoring confine condition" << G4endl;
    VolumeSource = "NULL";

  }
}

void DAMICParticleSource::SourceCoordinates(){
  SetSourcePosition(ParticlePosition);
}


void DAMICParticleSource::GeneratePrimaryVertex(G4Event* evt){

  if(ParticleDefinition == NULL){
    G4cout << "No particle has been defined!" << G4endl;
    return;
  }

  // Look for the coordinates
  if (IsMaterial()){
    MaterialCoordinates();
  }
  if (IsVolume()){
    CalculProba();
    ChooseVolume();
    VolumeCoordinates();
  }

  if (!(IsVolume() || IsMaterial())){
    SourceCoordinates();
  }

  G4PrimaryVertex* vertex = new G4PrimaryVertex(SourcePosition, ParticleTime);
  G4double mass = ParticleDefinition->GetPDGMass();
  G4double Energy = ParticleEnergy + mass;
  G4double pmom = std::sqrt(Energy*Energy-mass*mass);
  G4double px = pmom*ParticleMomentumDirection.x();
  G4double py = pmom*ParticleMomentumDirection.y();
  G4double pz = pmom*ParticleMomentumDirection.z();

  G4PrimaryParticle* particle = new G4PrimaryParticle(ParticleDefinition, px, py, pz);
  particle->SetMass( mass );
  particle->SetCharge( ParticleCharge );
  vertex->SetPrimary( particle );
  evt->AddPrimaryVertex(vertex);
}
