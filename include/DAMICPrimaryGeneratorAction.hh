#ifndef DAMICPrimaryGeneratorAction_hh
#define DAMICPrimaryGeneratorAction_hh



#include <stdio.h>


#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "globals.hh"
using namespace std;

class G4Event;

class DAMICPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  DAMICPrimaryGeneratorAction();
  ~DAMICPrimaryGeneratorAction();

public:
    void GeneratePrimaries(G4Event* anEvent);
private:
    G4GeneralParticleSource* particleGun;

private:
    long seeds[2];
    G4double energyPri;
public:
  const long* GetEventSeeds() const       {return seeds;};
  G4double GetEnergyPrimary() const  {return energyPri;};
};

#endif
