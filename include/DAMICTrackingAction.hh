#ifndef TrackingAction_h
#define TrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"

class DetectorConstruction;

class DAMICTrackingAction : public G4UserTrackingAction {

  public:
    DAMICTrackingAction();
   ~DAMICTrackingAction();

    virtual void  PreUserTrackingAction(const G4Track*);
    virtual void PostUserTrackingAction(const G4Track*);

};

#endif
