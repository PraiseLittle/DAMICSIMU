#ifndef DAMICAnalysisManager_hh
#define DAMICAnalysisManager_hh

#include <stdio.h>


#include "globals.hh"

#include "g4root.hh"
//#include "g4xml.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DAMICAnalysisManager
{
public:
    DAMICAnalysisManager();
    ~DAMICAnalysisManager();

private:
    void Book();
    G4String fFileName;
};
#endif
