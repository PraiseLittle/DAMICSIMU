#include "DAMICPrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "globals.hh"
#include <iostream>

#include <string>

#include <fstream>
#include <math.h>
using namespace std;

DAMICPrimaryGeneratorAction::DAMICPrimaryGeneratorAction():G4VUserPrimaryGeneratorAction()
{

  particleGun = new G4GeneralParticleSource();
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

  energyPri = 0.;

  // seeds
  seeds[0] = *G4Random::getTheSeeds();
  seeds[1] = *(G4Random::getTheSeeds()+1);

  particleGun->GeneratePrimaryVertex(anEvent);

  energyPri = particleGun->GetParticleEnergy();
}
