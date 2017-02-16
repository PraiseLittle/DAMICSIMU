#ifndef DAMICParticleSource_h
#define DAMICParticleSource_h

#include "G4VPrimaryGenerator.hh"
#include "G4Navigator.hh"
#include "G4ParticleMomentum.hh"
#include "G4ParticleDefinition.hh"

#include "DAMICParticleSourceMessenger.hh"

class DAMICParticleSource: public G4VPrimaryGenerator{
  public:
    DAMICParticleSource();
    ~DAMICParticleSource();
    void GeneratePrimaryVertex(G4Event* evt);
  public:
    //Particle Sets
    void SetParticleEnergy(G4double);
    void SetParticleCharge(G4double);
    void SetParticleMomentumDirection(G4ParticleMomentum);
    void SetParticleTime(G4double);
    void SetParticleDefinition(G4ParticleDefinition*);
    void SetParticlePosition(G4ThreeVector);

    //Position Sets
    void SetSourcePosition(G4ThreeVector);
    void SetMaterial(G4String);
    void SetVolumeSource(G4String);
    void SetMaterialSource(G4String);
    void SetMotherVolume(G4String);
    void SetSurface(G4bool);
    void SetVolume(G4bool);
    void SetMaterial(G4bool);

    //bools

    G4bool IsSurface();
    G4bool IsVolume();
    G4bool IsMaterial();

    //changes bools

    void DoVolume();
    void DoMaterial();
    void DoSource();

    //coordinatesCreation

    void MaterialCoordinates();
    void VolumeCoordinates();
    void SourceCoordinates();
    void CalculPosition(G4String, G4String, G4String);

    //Mother Volume Hit and Miss

    void FindInMother(); // hit and miss

  private:
    // Particle Carac

    G4double ParticleEnergy;
    G4double ParticleCharge;
    G4ParticleMomentum ParticleMomentumDirection;
    G4double ParticleTime;
    G4ParticleDefinition* ParticleDefinition;
    G4ThreeVector ParticlePosition;

    //Position
    G4bool bSurface; //True on surface
    G4bool bVolume; //True if Volume
    G4bool bMaterial;
    G4ThreeVector SourcePosition; // IF SOURCE MODE
    G4String VolumeSource; // IF VOLUME MODE
    G4String MaterialSource; // IF MATERIAL MODE
    G4String MotherVolume;
    G4String Material;

    //Navigator for Geometry
    G4Navigator* gNavigator;
    // Messenger

    DAMICParticleSourceMessenger* Messenger;
};

#endif
