#include "DAMICPrimaryGeneratorAction.hh"
#include "DAMICDetectorConstruction.hh"

#include "G4Event.hh"
#include "DAMICParticleSource.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "globals.hh"
#include "G4LogicalVolume.hh"
#include "G4TransportationManager.hh"
#include "G4Material.hh"
#include "DAMICAnalysisManager.hh"
#include "G4IonTable.hh"
#include <iostream>

#include <string>

#include <fstream>
#include <math.h>
using namespace std;

DAMICPrimaryGeneratorAction::DAMICPrimaryGeneratorAction():G4VUserPrimaryGeneratorAction()
{

  particleGun = new DAMICParticleSource();
  energyPri=0;
  seeds[0] =-1;
  seeds[1] =-1;

}

DAMICPrimaryGeneratorAction::~DAMICPrimaryGeneratorAction()
{
  delete particleGun;
}

void DAMICPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{

  // seeds
  //G4cout << "je rentre dans prim" << G4endl;
  seeds[0] = *G4Random::getTheSeeds();
  seeds[1] = *(G4Random::getTheSeeds()+1);
  G4ParticleTable* tablePart = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particleInject = tablePart->FindParticle("mu-");
  //G4ParticleDefinition* IonInject = G4IonTable::GetIonTable()->GetIon(27,60);
  particleGun->DoVolume();
  particleGun->SetParticleEnergy(4*GeV);
  particleGun->SetParticleMomentumDirection(G4ParticleMomentum(0.,0.,-1));
  //particleGun->AddVolume("BottomPlatePV",1);
  //particleGun->AddVolume("RearPlatePV",1);
  //particleGun->AddVolume("TopPlatePV",1);
  //particleGun->AddVolume("EndCoverPlatePV",1);
  particleGun->AddVolume("muonsPV",1);
  particleGun->SetParticleDefinition(particleInject);
  particleGun->GeneratePrimaryVertex(anEvent);
  //G4cout << "je sors du prim" << G4endl;

}
