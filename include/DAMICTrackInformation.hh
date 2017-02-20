#ifndef DAMICTrackInformation_h
#define DAMICTrackInformation_h 1

#include "globals.hh"
#include "G4VUserTrackInformation.hh"
#include <vector>

class DAMICTrackInformation: public G4VUserTrackInformation
{
  public:
    DAMICTrackInformation(G4int VPDGParticle, G4double VEnergyParticle, G4int VParticleID, G4String VMaterialProd);
    DAMICTrackInformation(const DAMICTrackInformation* InfoTrack);
    DAMICTrackInformation(const DAMICTrackInformation* InfoTrack, G4int VPDGParticle, G4double VEnergyParticle, G4int VParticleID, G4String VMaterialProd);
    ~DAMICTrackInformation();

    virtual void Print() const {};

    void AddPDGParticle(G4int val) { PDGParticle.push_back(val); }
    std::vector<G4int> GetPDGParticle() const { return PDGParticle; }

    void AddEnergyParticle(G4double val) { EnergyParticle.push_back(val); }
    std::vector<G4double> GetEnergyParticle() const { return EnergyParticle; }

    void AddParticleID(G4int val) { ParticleID.push_back(val); }
    std::vector<G4int> GetParticleID() const { return ParticleID; }

    void AddMaterialProd(G4String val) { MaterialProd.push_back(val) ; }
    std::vector<G4String> GetMaterialProd() const { return MaterialProd; }




  private:
    std::vector<G4int> PDGParticle;
    std::vector<G4double> EnergyParticle;
    std::vector<G4int> ParticleID;
    std::vector<G4String> MaterialProd;


};

#endif
