#ifndef DAMICCCDHit_h
#define DAMICCCDHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

class G4AttDef;
class G4AttValue;

/// DAMIC hit
///
/// It records:
/// A ton of things
///

class DAMICCCDHit : public G4VHit
{
public:
    DAMICCCDHit(G4int i);
    DAMICCCDHit(const DAMICCCDHit &right);
    virtual ~DAMICCCDHit();

    inline void *operator new(size_t);
    inline void operator delete(void*aHit);

    void Draw();
    void Print();


    void SetPos(G4ThreeVector val) { fPos = val; }
    G4ThreeVector GetPos() const { return fPos; }

    void SetTopBot(G4int val) {fTopBot = val;}
    G4int GetTopBot() const {return fTopBot;}

    void SetEnergyDeposit(G4double val) { fEnergyDeposit = val; }
    G4double GetEnergyDeposit() const { return fEnergyDeposit; }

    void SetPartIDElec(G4int val) { fPartIDElec = val; }
    G4double GetPartIDElec() const { return fPartIDElec; }

    void SetProcess(G4String val) { fProcess = val; }
    G4String GetProcess() const { return fProcess; }


//

    void SetPDGNumber(G4int val) { fPDGNumber = val; }
    G4int GetPDGNumber() const { return fPDGNumber; }

    void SetPartID(G4int val) { fPartID = val; }
    G4int GetPartID() const { return fPartID; }

    void SetEnergy(G4double val) { fEnergy = val; }
    G4double GetEnergy() const { return fEnergy; }

    void SetProdVolume(G4String val ) { fProdVolume = val; }
    G4String GetProdVolume() const { return fProdVolume; }

//

    void SetTime(G4double val) { fTime = val; }
    G4double GetTime() const { return fTime; }

    void SetPDGPrimaryNuc(G4int val) { fPDGPrimaryNuc = val; }
    G4int GetPDGPrimaryNuc() const { return fPDGPrimaryNuc; }

    void SetEventID(G4int val) { fEventID = val; }
    G4int GetEventID() const { return fEventID; }

    //

    void SetPDGSecondaryNuc(G4int val) { fPDGSecondaryNuc = val; }
    G4int GetPDGSecondaryNuc() const { return fPDGSecondaryNuc; }

    //


    void SetPDGPartASecond(G4int val) { fPDGPartASecond = val; }
    G4int GetPDGPartASecond() const { return fPDGPartASecond; }

    void SetEnergyPartASecond(G4double val) { fEnergyPartASecond = val; }
    G4double GetEnergyPartASecond() const { return fEnergyPartASecond; }

    // CCD NUM
    void SetCCDNum(G4int val) { fCCDNum = val; }
    G4int GetCCDNum() const { return fCCDNum; }


private:
    G4ThreeVector fPos;
    G4int fTopBot;
    G4double fEnergyDeposit;
    G4int fPartIDElec;
    G4String fProcess;
    //
    G4int fPDGNumber;
    G4int fPartID;
    G4String fProdVolume;
    G4double fEnergy;
    //Primary Nuc
    G4double fTime;
    G4int fPDGPrimaryNuc;
    G4int fEventID;
    //Secondary Nuc
    G4int fPDGSecondaryNuc;
    //Part after Second
    G4int fPDGPartASecond;
    G4double fEnergyPartASecond;
    // CCD
    G4int fCCDNum;
};

typedef G4THitsCollection<DAMICCCDHit> DAMICCCDHitsCollection;

extern G4ThreadLocal G4Allocator<DAMICCCDHit>* DAMICCCDHitAllocator;

inline void* DAMICCCDHit::operator new(size_t)
{
    if (!DAMICCCDHitAllocator)
        DAMICCCDHitAllocator = new G4Allocator<DAMICCCDHit>;
    return (void*)DAMICCCDHitAllocator->MallocSingle();
}

inline void DAMICCCDHit::operator delete(void*aHit)
{
    DAMICCCDHitAllocator->FreeSingle((DAMICCCDHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
