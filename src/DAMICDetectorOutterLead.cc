#include "DAMICDetectorOutterLead.hh"
#include "DAMICDetectorVessel.hh"
#include "DAMICDetectorCopperBox.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4VSolid.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trap.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4RunManager.hh"

#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4MultiUnion.hh"
#include "G4Transform3D.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <cmath>


G4LogicalVolume* GetConstructionVesselandOutter(){

  G4double boxX = 0.62*m;
  G4double boxY = 0.62*m;
  G4double boxZ = 0.62*m;


  G4Box* BaseGeo = new G4Box("BaseGeo", boxX, boxY, boxZ);
  G4Material* Nitro = G4Material::GetMaterial("G4_N");
  G4LogicalVolume* Base = new G4LogicalVolume(BaseGeo, Nitro, "OutterLead");

  G4LogicalVolume* LowerTubeAllLV = GetConstructionLowerTubeAll();

  G4LogicalVolume* LowerEndLV = GetConstructionLowerEnd();
  G4double PosZLowerEnd = -755.65*mm/2-(12.7*mm+3.175*mm)/2+3.175*mm;
  G4double PosYLowerEnd = 0;
  G4double PosXLowerEnd = 0;
  G4ThreeVector VectLowerEnd = G4ThreeVector(PosXLowerEnd, PosYLowerEnd, PosZLowerEnd);


  G4LogicalVolume* LowerFlangeAllLV = GetConstructionLowerFlangeAll();
  G4double PosZLowerFlange = 755.65/2*mm+28.448/2*mm;
  G4double PosYLowerFlange = 0;
  G4double PosXLowerFlange = 0;
  G4ThreeVector VectLowerFlange = G4ThreeVector(PosXLowerFlange, PosYLowerFlange, PosZLowerFlange);

  G4LogicalVolume* UpperFlangeLV = GetConstructionUpperFlange();
  G4double PosZUpperFlange = PosZLowerFlange + 28.448*mm;
  G4double PosYUpperFlange = 0;
  G4double PosXUpperFlange = 0;
  G4ThreeVector VectUpperFlange = G4ThreeVector(PosXUpperFlange, PosYUpperFlange, PosZUpperFlange);


  /*-----------------------LEAD---------------------*/

  G4LogicalVolume* Assembly1LV = GetConstructionAssembly1();
  G4double PosZAssembly1 = PosZLowerEnd - 1.5748/2*mm - (12.7*mm+3.175*mm)/2;
  G4ThreeVector VectAssembly1 = G4ThreeVector(0,0,PosZAssembly1);

  G4LogicalVolume* Assembly2LV = GetConstructionAssembly2();


  /*--------BottomLead------*/

  G4double BottomLeadX = 304.800*mm;
  G4double BottomLeadY = 304.800*mm;
  G4double BottomLeadZ = 50.800*mm;

  G4Box* boxBottomLeadFinal = new G4Box("boxBottomLeadFinal", BottomLeadX/2, BottomLeadY/2, BottomLeadZ/2);
  G4Material* LeadMain = G4Material::GetMaterial("G4_Pb");
  G4LogicalVolume * BoxBottomLead = new G4LogicalVolume(boxBottomLeadFinal, LeadMain,"BoxBottomLead");

  /*------InsideLead------*/

  G4double boxInsideX = 304.800*mm;
  G4double boxInsideY = 304.800*mm;
  G4double boxInsideZ = 203.2*mm;
  G4double rmBoxX = 203.2*mm;
  G4double rmBoxY = 203.2*mm;
  G4double rmBoxZ = 203.2*mm;


  G4Box* boxInside = new G4Box("BoxInside", boxInsideX/2, boxInsideY/2, boxInsideZ/2);
  G4Box* rmBoxInside = new G4Box("rmBoxInside", rmBoxX/2, rmBoxY/2, rmBoxZ);

  G4ThreeVector InsideVect = G4ThreeVector(0,0,0);
  G4RotationMatrix* rot0Inside = new G4RotationMatrix;
  G4Transform3D InsideTr = G4Transform3D(*rot0Inside, InsideVect);

  G4SubtractionSolid* InsideLeadFinal = new G4SubtractionSolid("InsideLeadFinal", boxInside, rmBoxInside, InsideTr);

  G4LogicalVolume* InsideLead1 = new G4LogicalVolume(InsideLeadFinal, LeadMain, "InsideLead1");
  G4LogicalVolume* InsideLead2 = new G4LogicalVolume(InsideLeadFinal, LeadMain, "InsideLead2");

  /*-------------TopLead-----------*/

  G4double TopLeadX = 304.800*mm;
  G4double TopLeadY = 304.800*mm;
  G4double TopLeadZ = 25.4*mm;

  G4double rmBoxXTop = 203.2*mm;
  G4double rmBoxYTop = 203.2*mm;
  G4double rmBoxZTop = 25.4*mm;

  G4Box* boxTopLead = new G4Box("boxTopLead", TopLeadX/2, TopLeadY/2, TopLeadZ/2);
  G4Box* rmBoxTop = new G4Box("rmBoxTop", rmBoxXTop/2, rmBoxYTop/2, rmBoxZTop);

  G4ThreeVector TopVect = G4ThreeVector(0,0,0);
  G4RotationMatrix* rot0Top = new G4RotationMatrix;
  G4Transform3D TopTr = G4Transform3D(*rot0Inside, InsideVect);

  G4SubtractionSolid* boxTopLeadFinal = new G4SubtractionSolid("BoxTopLeadFinal", boxTopLead, rmBoxTop, TopTr);

  G4LogicalVolume * BoxTopLead = new G4LogicalVolume(boxTopLeadFinal, LeadMain,"BoxTopLead");


  /*---------BoxBottomLeadPos-------*/

  G4double BoxBottomLeadZ = PosZAssembly1 - 26.188*mm;
  G4ThreeVector BoxBottomLeadVect = G4ThreeVector(0,0,BoxBottomLeadZ);

  /*------InsideLead1Pos------*/
  G4double InsideLead1Z = PosZAssembly1 + 102.3874*mm;
  G4ThreeVector InsideLead1Vect = G4ThreeVector(0,0,InsideLead1Z);

  /*------Assembly2Pos----*/
  G4double Assembly2Z = InsideLead1Z + 102.3874*mm;
  G4ThreeVector Assembly2Vect = G4ThreeVector(0,0,Assembly2Z);

  /*-----InsideLead2Pos-----*/
  G4double InsideLead2Z = Assembly2Z + 102.3874*mm;
  G4ThreeVector InsideLead2Vect = G4ThreeVector(0,0,InsideLead2Z);

  /*------TopLeadPos-----*/
  G4double TopLeadPosZ = InsideLead2Z + 114.3*mm;
  G4ThreeVector TopLeadVect = G4ThreeVector(0,0,TopLeadPosZ);


/*-------------------------------------CopperBox---------------------------------*/

  G4double PosZCopperInner = -120;

/*----------------------------ShieldingLead--------------------------*/
  G4LogicalVolume* ShieldingLeadLV = GetConstructionShieldingLead();
  G4double PosZShieldingLead = PosZCopperInner-70*mm + 1.0498*mm;
  G4ThreeVector VectShieldingLead = G4ThreeVector(0,0,PosZShieldingLead);

/*----------------------------LeadCastleFrame----------*/

  G4LogicalVolume* LeadCastleFrameLV = GetConstructionLeadCastleFrame();
  G4double PosZLeadCastle = PosZShieldingLead + 101.6/2*mm - 4.826*mm;
  G4ThreeVector VectoLeadCastle = G4ThreeVector(0,0,PosZLeadCastle);


/*-------------------PartLeadCastle-------------*/

  G4LogicalVolume* PartLeadCastle1LV = GetConstructionPartLeadCastle();
  G4LogicalVolume* PartLeadCastle2LV = GetConstructionPartLeadCastle();
  G4LogicalVolume* PartLeadCastle3LV = GetConstructionPartLeadCastle();
  G4LogicalVolume* PartLeadCastle4LV = GetConstructionPartLeadCastle();

  G4double PosZPartLeadCastle = PosZLeadCastle;
  G4double PosYPartLeadCastle = 0.8/2*mm + 609.6/2*mm;
  G4double PosXPartLeadCastle = 0.8/2*mm + 609.6/2*mm;

  G4ThreeVector VectPartLead1 = G4ThreeVector(0, PosYPartLeadCastle, PosZPartLeadCastle);
  G4ThreeVector VectPartLead2 = G4ThreeVector(0, -PosYPartLeadCastle, PosZPartLeadCastle);
  G4ThreeVector VectPartLead3 = G4ThreeVector(PosXPartLeadCastle, 0, PosZPartLeadCastle);
  G4ThreeVector VectPartLead4 = G4ThreeVector(-PosXPartLeadCastle, 0,PosZPartLeadCastle);

  G4ThreeVector uPartLead = G4ThreeVector(0,-1,0);
  G4ThreeVector vPartLead = G4ThreeVector(1,0,0);
  G4ThreeVector wPartLead = G4ThreeVector(0,0,1);
  G4RotationMatrix* RotPartLead = new G4RotationMatrix(uPartLead, vPartLead, wPartLead);

  G4PVPlacement* LowerTubeAllPV = new G4PVPlacement(0, G4ThreeVector(0,0,0), LowerTubeAllLV, "LowerTubeAllPV", Base, false, 0, false);
  G4PVPlacement* LowerEndPV = new G4PVPlacement(0, VectLowerEnd, LowerEndLV, "LowerEndPV", Base, false, 0, false);
  G4PVPlacement* LowerFlangeAllPV = new G4PVPlacement(0, VectLowerFlange, LowerFlangeAllLV, "LowerFlangeAllPV", Base, false, 0, false);
  G4PVPlacement* UpperFlangePV = new G4PVPlacement(0, VectUpperFlange, UpperFlangeLV, "UpperFlangePV", Base, false, 0, false);
  //G4PVPlacement* Assembly1PV = new G4PVPlacement(0, VectAssembly1, Assembly1LV, "Assembly1PV", Base, false, 0, false);
  //G4PVPlacement* Assembly2PV = new G4PVPlacement(0, Assembly2Vect, Assembly2LV, "Assembly2PV", Base, false, 0, false);
  //G4PVPlacement* BoxTopLeadPV = new G4PVPlacement(0, TopLeadVect, BoxTopLead, "BoxTopLeadPV", Base, false, 0, false);
  //G4PVPlacement* BoxBottomLeadPV = new G4PVPlacement(0, BoxBottomLeadVect, BoxBottomLead, "BoxBottomLeadPV", Base, false, 0, false);
  //G4PVPlacement* InsideLead1PV = new G4PVPlacement(0, InsideLead1Vect, InsideLead1, "InsideLead1PV", Base, false, 0, false);
  //G4PVPlacement* InsideLead2PV = new G4PVPlacement(0, InsideLead2Vect, InsideLead2, "InsideLead2PV", Base, false, 0, false);
  //G4PVPlacement* ShieldingLeadPV = new G4PVPlacement(0, VectShieldingLead, ShieldingLeadLV, "ShieldingLeadPV", Base, false, 0, false);
  //G4PVPlacement* LeadCastlePV = new G4PVPlacement(0, VectoLeadCastle, LeadCastleFrameLV, "LeadCastlePV", Base, false, 0, false);
  //G4PVPlacement* PartLeadCastle1PV = new G4PVPlacement(0, VectPartLead1, PartLeadCastle1LV, "PartLeadCastle1PV", Base, false, 0, false);
  //G4PVPlacement* PartLeadCastle2PV = new G4PVPlacement(0, VectPartLead2, PartLeadCastle2LV, "PartLeadCastle2PV", Base, false, 0, false);
  //G4PVPlacement* PartLeadCastle3PV = new G4PVPlacement(RotPartLead, VectPartLead3, PartLeadCastle3LV, "PartLeadCastle3PV", Base, false, 0, false);
  //G4PVPlacement* PartLeadCastle4PV = new G4PVPlacement(RotPartLead, VectPartLead4, PartLeadCastle4LV, "PartLeadCastle4PV", Base, false, 0, false);

  return Base;
}


G4LogicalVolume* GetConstructionAssembly1()
{
  G4double boxAssembly1X = 203.2*mm;
  G4double boxAssembly1Y = 203.2*mm;
  G4double boxAssembly1Z = 1.5748*mm+9.525*mm+25.4*mm;

  G4double box2X = 303.53*mm;
  G4double box2Y = 303.53*mm;
  G4double box2Z = 1.5748*mm;

  G4double rmTubR = 203.2*mm;
  G4double rmTubH = 1.5748*mm+9.525*mm+25.4*mm;
  G4double A0 = 0;
  G4double A360 = 2*M_PI+1;

  G4Box* box1 = new G4Box("box1", boxAssembly1X/2, boxAssembly1Y/2, boxAssembly1Z/2);
  G4Box* box2 = new G4Box("box2", box2X/2, box2Y/2, box2Z/2);
  G4Tubs* Tub = new G4Tubs("Tub",A0, rmTubR/2, rmTubH,A0, A360);

  G4double PosUnionZ = (9.525*mm+25.4*mm+1.5748)/2;
  G4ThreeVector VectUnion = G4ThreeVector(0,0,PosUnionZ);
  G4RotationMatrix* rotrien = new G4RotationMatrix;
  G4Transform3D TrUnion = G4Transform3D(*rotrien, VectUnion);

  G4Transform3D TRRM = G4Transform3D(*rotrien, G4ThreeVector(0,0,0));

  G4UnionSolid* Union1  = new G4UnionSolid("Union1", box2,box1, TrUnion);
  G4SubtractionSolid* boxAssembly1 = new G4SubtractionSolid("Assembly1", Union1, Tub, TRRM);

  G4LogicalVolume* RestraintSheetLV = GetConstructionRestraintSheet();
  G4LogicalVolume* RestraintBlocks1LV = GetConstructionRestraintBlocks();
  G4LogicalVolume* RestraintBlocks2LV = GetConstructionRestraintBlocks();
  G4LogicalVolume* RestraintBlocks3LV = GetConstructionRestraintBlocks();
  G4LogicalVolume* RestraintBlocks4LV = GetConstructionRestraintBlocks();
  G4LogicalVolume* CornerBlocks1LV = GetConstructionCornerLead();
  G4LogicalVolume* CornerBlocks2LV = GetConstructionCornerLead();
  G4LogicalVolume* CornerBlocks3LV = GetConstructionCornerLead();
  G4LogicalVolume* CornerBlocks4LV = GetConstructionCornerLead();

  /*--------RestraintBlocks1Pos*-------*/
  G4double RestraintBlocks1Z = 6.3373*mm;
  G4double RestraintBlocks1Y = -101.346*sqrt(2)/2*mm-0.237;
  G4double RestraintBlocks1X = -101.346*sqrt(2)/2*mm-0.237;
  G4ThreeVector RestraintBlocks1Vect = G4ThreeVector(RestraintBlocks1X, RestraintBlocks1Y, RestraintBlocks1Z);
  G4ThreeVector uRestraint1 = G4ThreeVector(1,0,0);
  G4ThreeVector vRestraint1 = G4ThreeVector(0,1,0);
  G4ThreeVector wRestraint1 = G4ThreeVector(0,0,1);
  G4RotationMatrix* RestraintBlocks1Rot = new G4RotationMatrix(uRestraint1, vRestraint1, wRestraint1);

  /*--------RestraintBlocks2Pos*-------*/
  G4double RestraintBlocks2Z = RestraintBlocks1Z;
  G4double RestraintBlocks2Y = RestraintBlocks1Y;
  G4double RestraintBlocks2X = -RestraintBlocks1X;
  G4ThreeVector RestraintBlocks2Vect = G4ThreeVector(RestraintBlocks2X, RestraintBlocks2Y, RestraintBlocks2Z);
  G4ThreeVector uRestraint2 = G4ThreeVector(0,-1,0);
  G4ThreeVector vRestraint2 = G4ThreeVector(1,0,0);
  G4ThreeVector wRestraint2 = G4ThreeVector(0,0,1);
  G4RotationMatrix* RestraintBlocks2Rot = new G4RotationMatrix(uRestraint2, vRestraint2, wRestraint2);

  /*--------RestraintBlocks3Pos*-------*/
  G4double RestraintBlocks3Z = RestraintBlocks1Z;
  G4double RestraintBlocks3Y = -RestraintBlocks1Y;
  G4double RestraintBlocks3X = -RestraintBlocks1X;
  G4ThreeVector RestraintBlocks3Vect = G4ThreeVector(RestraintBlocks3X, RestraintBlocks3Y, RestraintBlocks3Z);
  G4ThreeVector uRestraint3 = G4ThreeVector(-1,0,0);
  G4ThreeVector vRestraint3 = G4ThreeVector(0,-1,0);
  G4ThreeVector wRestraint3 = G4ThreeVector(0,0,1);
  G4RotationMatrix* RestraintBlocks3Rot = new G4RotationMatrix(uRestraint3, vRestraint3, wRestraint3);

  /*--------RestraintBlocks4Pos*-------*/
  G4double RestraintBlocks4Z = RestraintBlocks1Z;
  G4double RestraintBlocks4Y = -RestraintBlocks1Y;
  G4double RestraintBlocks4X = RestraintBlocks1X;
  G4ThreeVector RestraintBlocks4Vect = G4ThreeVector(RestraintBlocks4X, RestraintBlocks4Y, RestraintBlocks4Z);
  G4ThreeVector uRestraint4 = G4ThreeVector(0,1,0);
  G4ThreeVector vRestraint4 = G4ThreeVector(-1,0,0);
  G4ThreeVector wRestraint4 = G4ThreeVector(0,0,1);
  G4RotationMatrix* RestraintBlocks4Rot = new G4RotationMatrix(uRestraint4, vRestraint4, wRestraint4);

  /*-------CornerBlocks1Pos--------*/
  G4double CornerBlocks1Z = RestraintBlocks1Z + 17.4625*mm;
  G4double CornerBlocks1Y = RestraintBlocks1Y;
  G4double CornerBlocks1X = RestraintBlocks1X;
  G4ThreeVector CornerBlocks1Vect = G4ThreeVector(CornerBlocks1X, CornerBlocks1Y, CornerBlocks1Z);
  G4ThreeVector uCorner1 = G4ThreeVector(1,0,0);
  G4ThreeVector vCorner1 = G4ThreeVector(0,1,0);
  G4ThreeVector wCorner1 = G4ThreeVector(0,0,1);
  G4RotationMatrix* CornerBlocks1Rot = new G4RotationMatrix(uCorner1, vCorner1, wCorner1);

  /*-------CornerBlocks2Pos--------*/
  G4double CornerBlocks2Z = CornerBlocks1Z;
  G4double CornerBlocks2Y = RestraintBlocks2Y;
  G4double CornerBlocks2X = RestraintBlocks2X;
  G4ThreeVector CornerBlocks2Vect = G4ThreeVector(CornerBlocks2X, CornerBlocks2Y, CornerBlocks2Z);
  G4ThreeVector uCorner2 = G4ThreeVector(0,-1,0);
  G4ThreeVector vCorner2 = G4ThreeVector(1,0,0);
  G4ThreeVector wCorner2 = G4ThreeVector(0,0,1);
  G4RotationMatrix* CornerBlocks2Rot = new G4RotationMatrix(uCorner2, vCorner2, wCorner2);

  /*-------CornerBlocks3Pos--------*/
  G4double CornerBlocks3Z = CornerBlocks1Z;
  G4double CornerBlocks3Y = RestraintBlocks3Y;
  G4double CornerBlocks3X = RestraintBlocks3X;
  G4ThreeVector CornerBlocks3Vect = G4ThreeVector(CornerBlocks3X, CornerBlocks3Y, CornerBlocks3Z);
  G4ThreeVector uCorner3 = G4ThreeVector(-1,0,0);
  G4ThreeVector vCorner3 = G4ThreeVector(0,-1,0);
  G4ThreeVector wCorner3 = G4ThreeVector(0,0,1);
  G4RotationMatrix* CornerBlocks3Rot = new G4RotationMatrix(uCorner3 ,vCorner3, wCorner3);

  /*-------CornerBlocks4Pos--------*/
  G4double CornerBlocks4Z = CornerBlocks1Z;
  G4double CornerBlocks4Y = RestraintBlocks4Y;
  G4double CornerBlocks4X = RestraintBlocks4X;
  G4ThreeVector CornerBlocks4Vect = G4ThreeVector(CornerBlocks4X, CornerBlocks4Y, CornerBlocks4Z);
  G4ThreeVector uCorner4 = G4ThreeVector(0,1,0);
  G4ThreeVector vCorner4 = G4ThreeVector(-1,0,0);
  G4ThreeVector wCorner4 = G4ThreeVector(0,0,1);
  G4RotationMatrix* CornerBlocks4Rot = new G4RotationMatrix(uCorner4, vCorner4, wCorner4);


  G4Material* Nitro = G4Material::GetMaterial("G4_N");
  G4LogicalVolume* Assembly1 = new G4LogicalVolume(boxAssembly1, Nitro, "Assembly1");



  G4PVPlacement* RestraintSheet1PV = new G4PVPlacement(0, G4ThreeVector(0,0,0), RestraintSheetLV, "RestraintSheet1PV", Assembly1, false, 0, false);
  G4PVPlacement* RestraintBlocks1PV = new G4PVPlacement(RestraintBlocks1Rot, RestraintBlocks1Vect, RestraintBlocks1LV, "RestraintBlocks1PV", Assembly1, false, 0, false);
  G4PVPlacement* RestraintBlocks2PV = new G4PVPlacement(RestraintBlocks2Rot, RestraintBlocks2Vect, RestraintBlocks2LV, "RestraintBlocks2PV", Assembly1, false, 0, false);
  G4PVPlacement* RestraintBlocks3PV = new G4PVPlacement(RestraintBlocks3Rot, RestraintBlocks3Vect, RestraintBlocks3LV, "RestraintBlocks3PV", Assembly1, false, 0, false);
  G4PVPlacement* RestraintBlocks4PV = new G4PVPlacement(RestraintBlocks4Rot, RestraintBlocks4Vect, RestraintBlocks4LV, "RestraintBlocks4PV", Assembly1, false, 0, false);
  G4PVPlacement* CornerBlocks1PV = new G4PVPlacement(CornerBlocks1Rot, CornerBlocks1Vect, CornerBlocks1LV, "CornerBlocks1PV", Assembly1, false, 0, false);
  G4PVPlacement* CornerBlocks2PV = new G4PVPlacement(CornerBlocks2Rot, CornerBlocks2Vect, CornerBlocks2LV, "CornerBlocks2PV", Assembly1, false, 0, false);
  G4PVPlacement* CornerBlocks3PV = new G4PVPlacement(CornerBlocks3Rot, CornerBlocks3Vect, CornerBlocks3LV, "CornerBlocks3PV", Assembly1, false, 0, false);
  G4PVPlacement* CornerBlocks4PV = new G4PVPlacement(CornerBlocks4Rot, CornerBlocks4Vect, CornerBlocks4LV, "CornerBlocks4PV", Assembly1, false, 0, false);

  return Assembly1;

}

G4LogicalVolume* GetConstructionAssembly2()
{
  G4double boxAssembly1X = 203.2*mm;
  G4double boxAssembly1Y = 203.2*mm;
  G4double boxAssembly1Z = 1.5748*mm+9.525*mm*2;

  G4double box2X = 303.53*mm;
  G4double box2Y = 303.53*mm;
  G4double box2Z = 1.5748*mm;

  G4double rmTubR = 203.2*mm;
  G4double rmTubH = 1.5748*mm+9.525*2*mm;
  G4double A0 = 0;
  G4double A360 = 2*M_PI+1;

  G4Box* box1 = new G4Box("box1", boxAssembly1X/2, boxAssembly1Y/2, boxAssembly1Z/2);
  G4Box* box2 = new G4Box("box2", box2X/2, box2Y/2, box2Z/2);
  G4Tubs* Tub = new G4Tubs("Tub",A0, rmTubR/2, rmTubH,A0, A360);

  G4double PosUnionZ = 0;
  G4ThreeVector VectUnion = G4ThreeVector(0,0,PosUnionZ);
  G4RotationMatrix* rotrien = new G4RotationMatrix;
  G4Transform3D TrUnion = G4Transform3D(*rotrien, VectUnion);

  G4Transform3D TRRM = G4Transform3D(*rotrien, G4ThreeVector(0,0,0));

  G4UnionSolid* Union1  = new G4UnionSolid("Union1", box2,box1, TrUnion);
  G4SubtractionSolid* boxAssembly2 = new G4SubtractionSolid("Assembly1", Union1, Tub, TRRM);


  G4LogicalVolume* RestraintSheetLV = GetConstructionRestraintSheet();
  G4LogicalVolume* RestraintBlocks1LV = GetConstructionRestraintBlocks();
  G4LogicalVolume* RestraintBlocks2LV = GetConstructionRestraintBlocks();
  G4LogicalVolume* RestraintBlocks3LV = GetConstructionRestraintBlocks();
  G4LogicalVolume* RestraintBlocks4LV = GetConstructionRestraintBlocks();
  G4LogicalVolume* RestraintBlocks5LV = GetConstructionRestraintBlocks();
  G4LogicalVolume* RestraintBlocks6LV = GetConstructionRestraintBlocks();
  G4LogicalVolume* RestraintBlocks7LV = GetConstructionRestraintBlocks();
  G4LogicalVolume* RestraintBlocks8LV = GetConstructionRestraintBlocks();



  /*--------RestraintBlocks1Pos*-------*/
  G4double RestraintBlocks1Z = (1.5748*mm+9.525*mm)/2;
  G4double RestraintBlocks1Y = -101.346*sqrt(2)/2*mm-0.237;
  G4double RestraintBlocks1X = -101.346*sqrt(2)/2*mm-0.237;
  G4ThreeVector RestraintBlocks1Vect = G4ThreeVector(RestraintBlocks1X, RestraintBlocks1Y, RestraintBlocks1Z);
  G4ThreeVector uRestraint1 = G4ThreeVector(1,0,0);
  G4ThreeVector vRestraint1 = G4ThreeVector(0,1,0);
  G4ThreeVector wRestraint1 = G4ThreeVector(0,0,1);
  G4RotationMatrix* RestraintBlocks12Rot = new G4RotationMatrix(uRestraint1, vRestraint1, wRestraint1);

  /*--------RestraintBlocks2Pos*-------*/
  G4double RestraintBlocks2Z = -RestraintBlocks1Z;
  G4double RestraintBlocks2Y = RestraintBlocks1Y;
  G4double RestraintBlocks2X = RestraintBlocks1X;
  G4ThreeVector RestraintBlocks2Vect = G4ThreeVector(RestraintBlocks2X, RestraintBlocks2Y, RestraintBlocks2Z);

  /*--------RestraintBlocks3Pos*-------*/
  G4double RestraintBlocks3Z = RestraintBlocks1Z;
  G4double RestraintBlocks3Y = RestraintBlocks1Y;
  G4double RestraintBlocks3X = -RestraintBlocks1X;
  G4ThreeVector RestraintBlocks3Vect = G4ThreeVector(RestraintBlocks3X, RestraintBlocks3Y, RestraintBlocks3Z);
  G4ThreeVector uRestraint3 = G4ThreeVector(0,-1,0);
  G4ThreeVector vRestraint3 = G4ThreeVector(1,0,0);
  G4ThreeVector wRestraint3 = G4ThreeVector(0,0,1);
  G4RotationMatrix* RestraintBlocks34Rot = new G4RotationMatrix(uRestraint3, vRestraint3, wRestraint3);

  /*--------RestraintBlocks4Pos*-------*/
  G4double RestraintBlocks4Z = -RestraintBlocks1Z;
  G4double RestraintBlocks4Y = RestraintBlocks1Y;
  G4double RestraintBlocks4X = -RestraintBlocks1X;
  G4ThreeVector RestraintBlocks4Vect = G4ThreeVector(RestraintBlocks4X, RestraintBlocks4Y, RestraintBlocks4Z);

  /*--------RestraintBlocks5Pos*-------*/
  G4double RestraintBlocks5Z = RestraintBlocks1Z;
  G4double RestraintBlocks5Y = -RestraintBlocks1Y;
  G4double RestraintBlocks5X = -RestraintBlocks1X;
  G4ThreeVector RestraintBlocks5Vect = G4ThreeVector(RestraintBlocks5X, RestraintBlocks5Y, RestraintBlocks5Z);
  G4ThreeVector uRestraint5 = G4ThreeVector(-1,0,0);
  G4ThreeVector vRestraint5 = G4ThreeVector(0,-1,0);
  G4ThreeVector wRestraint5 = G4ThreeVector(0,0,1);
  G4RotationMatrix* RestraintBlocks56Rot = new G4RotationMatrix(uRestraint5, vRestraint5, wRestraint5);

  /*--------RestraintBlocks6Pos*-------*/
  G4double RestraintBlocks6Z = -RestraintBlocks1Z;
  G4double RestraintBlocks6Y = -RestraintBlocks1Y;
  G4double RestraintBlocks6X = -RestraintBlocks1X;
  G4ThreeVector RestraintBlocks6Vect = G4ThreeVector(RestraintBlocks6X, RestraintBlocks6Y, RestraintBlocks6Z);

  /*--------RestraintBlocks7Pos*-------*/
  G4double RestraintBlocks7Z = RestraintBlocks1Z;
  G4double RestraintBlocks7Y = -RestraintBlocks1Y;
  G4double RestraintBlocks7X = RestraintBlocks1X;
  G4ThreeVector RestraintBlocks7Vect = G4ThreeVector(RestraintBlocks7X, RestraintBlocks7Y, RestraintBlocks7Z);
  G4ThreeVector uRestraint7 = G4ThreeVector(0,1,0);
  G4ThreeVector vRestraint7 = G4ThreeVector(-1,0,0);
  G4ThreeVector wRestraint7 = G4ThreeVector(0,0,1);
  G4RotationMatrix* RestraintBlocks78Rot = new G4RotationMatrix(uRestraint7, vRestraint7, wRestraint7);

  /*--------RestraintBlocks8Pos*-------*/
  G4double RestraintBlocks8Z = -RestraintBlocks1Z;
  G4double RestraintBlocks8Y = -RestraintBlocks1Y;
  G4double RestraintBlocks8X = RestraintBlocks1X;
  G4ThreeVector RestraintBlocks8Vect = G4ThreeVector(RestraintBlocks8X, RestraintBlocks8Y, RestraintBlocks8Z);


  G4Material* Nitro = G4Material::GetMaterial("G4_N");
  G4LogicalVolume* Assembly2 = new G4LogicalVolume(boxAssembly2, Nitro, "Assembly2");


  G4PVPlacement* RestraintSheet2PV = new G4PVPlacement(0, G4ThreeVector(0,0,0), RestraintSheetLV, "RestraintSheet2PV", Assembly2, false, 0, false);
  G4PVPlacement* RestraintBlocks5PV = new G4PVPlacement(RestraintBlocks12Rot, RestraintBlocks1Vect, RestraintBlocks1LV, "RestraintBlocks5V", Assembly2, false, 0, false);
  G4PVPlacement* RestraintBlocks6PV = new G4PVPlacement(RestraintBlocks12Rot, RestraintBlocks2Vect, RestraintBlocks2LV, "RestraintBlocks6PV", Assembly2, false, 0, false);
  G4PVPlacement* RestraintBlocks7PV = new G4PVPlacement(RestraintBlocks34Rot, RestraintBlocks3Vect, RestraintBlocks3LV, "RestraintBlocks7PV", Assembly2, false, 0, false);
  G4PVPlacement* RestraintBlocks8PV = new G4PVPlacement(RestraintBlocks34Rot, RestraintBlocks4Vect, RestraintBlocks4LV, "RestraintBlocks8PV", Assembly2, false, 0, false);
  G4PVPlacement* RestraintBlocks9PV = new G4PVPlacement(RestraintBlocks56Rot, RestraintBlocks5Vect, RestraintBlocks5LV, "RestraintBlocks9PV", Assembly2, false, 0, false);
  G4PVPlacement* RestraintBlocks10PV = new G4PVPlacement(RestraintBlocks56Rot, RestraintBlocks6Vect, RestraintBlocks6LV, "RestraintBlocks10PV", Assembly2, false, 0, false);
  G4PVPlacement* RestraintBlocks11PV = new G4PVPlacement(RestraintBlocks78Rot, RestraintBlocks7Vect, RestraintBlocks7LV, "RestraintBlocks11PV", Assembly2, false, 0, false);
  G4PVPlacement* RestraintBlocks12PV = new G4PVPlacement(RestraintBlocks78Rot, RestraintBlocks8Vect, RestraintBlocks8LV, "RestraintBlocks12PV", Assembly2, false, 0, false);


  return Assembly2;
}

G4LogicalVolume* GetConstructionCornerLead()
{
  G4double bigBoxX = 50.8*mm;
  G4double bigBoxY = 50.8*mm;
  G4double bigBoxZ = 25.4*mm;
  G4double rmTubR= 107.682*mm;
  G4double rmTubH = 25.4*mm;
  G4double angle0 = 0;
  G4double angle360 =  M_PI*2+1;

  G4Box *bigBox = new G4Box("BigBox", bigBoxX/2, bigBoxY/2, bigBoxZ/2);
  G4Tubs *rmTub = new G4Tubs("RmTub", angle0,rmTubR, rmTubH,angle0, angle360 );

  G4RotationMatrix *rot0 = new G4RotationMatrix;
  G4double rmTubVecXY = 76.2*mm;
  G4ThreeVector rmTubVec = G4ThreeVector(rmTubVecXY, rmTubVecXY,0);
  G4Transform3D rmTubTr = G4Transform3D(*rot0, rmTubVec);

  G4SubtractionSolid* cornerLeadFinal = new G4SubtractionSolid("CornerLeadFinal", bigBox, rmTub, rmTubTr);
  G4Material* Lead = G4Material::GetMaterial("G4_Pb");
  G4LogicalVolume * cornerLead = new G4LogicalVolume(cornerLeadFinal, Lead,"CornerLead");

  return cornerLead;

}

G4LogicalVolume* GetConstructionRestraintBlocks()
{
  G4double bigBoxX = 50.8*mm;
  G4double bigBoxY = 50.8*mm;
  G4double bigBoxZ = 9.525*mm;
  G4double rmBoxX = 66.294;
  G4double rmBoxY = 66.294;
  G4double rmBoxZ = 66.294;

  G4Box * bigBox = new G4Box("BigBox", bigBoxX/2, bigBoxY/2, bigBoxZ/2);
  G4Box * rmBox = new G4Box("RmBox", rmBoxX/2, rmBoxY, rmBoxZ);

  G4RotationMatrix * rot45 = new G4RotationMatrix;
  rot45->rotateZ(M_PI/4);
  G4double rmBoxVecX = 46.99/2*mm;
  G4double rmBoxVecY = 46.99/2*mm;
  G4ThreeVector rmBoxVec = G4ThreeVector(rmBoxVecX,rmBoxVecY,0);
  G4Transform3D rmBoxTr = G4Transform3D(*rot45, rmBoxVec);


  G4SubtractionSolid* restraintBlocksFinal = new G4SubtractionSolid("RestraintBlocksFinal", bigBox, rmBox, rmBoxTr);
  G4Material* Copper = G4Material::GetMaterial("G4_Cu");
  G4LogicalVolume * restraintBlocks = new G4LogicalVolume(restraintBlocksFinal, Copper,"RestraintBlocks");

  return restraintBlocks;



}

G4LogicalVolume* GetConstructionRestraintSheet()
{
  G4double bigBoxX = 303.53*mm;
  G4double bigBoxY = 303.53*mm;
  G4double bigBoxZ = 1.5748*mm;
  G4double rmTubR = 209.55/2*mm;
  G4double rmTubH = 1.5748*mm;
  G4double angle0 = 0;
  G4double angle360 = M_PI*2+1;

  G4Box * bigBox = new G4Box("BigBox", bigBoxX/2, bigBoxY/2, bigBoxZ/2);
  G4Tubs* rmTub = new G4Tubs("RmTub", angle0, rmTubR, rmTubH, angle0, angle360);
  G4RotationMatrix* rot0= new G4RotationMatrix;
  G4ThreeVector tubVec = G4ThreeVector(0,0,0);
  G4Transform3D tubTR = G4Transform3D(*rot0, tubVec);

  G4SubtractionSolid * restraintSheetFinal = new G4SubtractionSolid("RestraintSheetFinal", bigBox, rmTub, tubTR);

  G4Material* Copper = G4Material::GetMaterial("G4_Cu");
  G4LogicalVolume * restraintSheet = new G4LogicalVolume(restraintSheetFinal, Copper,"RestraintSheet");

  return restraintSheet;

}


G4LogicalVolume* GetConstructionShieldingLead(){
  G4double mainBoxX = 609.6*mm;
  G4double mainBoxY = mainBoxX;
  G4double mainBoxZ = 812.8*mm;

  G4double rmBoxX = 304.8*mm;
  G4double rmBoxY = rmBoxX;
  G4double rmBoxZ = 485.8*mm;

  G4double rmLittleBoxX = 406.4*mm;
  G4double rmLittleBoxY = 406.4*mm;
  G4double rmLittleBoxZ = 22.2*mm;

  G4double rmcyl = 196.978/2*mm+1*mm;
  G4double rmH = 152.4*mm;
  G4double angle0 = 0*mm;
  G4double angle360 = M_PI*2+1;

  G4Box* mainBox = new G4Box("mainBox", mainBoxX/2, mainBoxY/2, mainBoxZ/2);
  G4Box* rmBox1 = new G4Box("rmBox1", rmBoxX/2, rmBoxY/2, rmBoxZ/2);
  G4Box* rmBox2 = new G4Box("rmBox1", rmLittleBoxX/2, rmLittleBoxY/2, rmLittleBoxZ);
  G4Tubs* tubrm = new G4Tubs("rmTub", angle0, rmcyl, rmH/2, angle0, angle360);


  G4RotationMatrix* rot0 = new G4RotationMatrix;
  G4double rmZ2Pos = 406.4*mm;
  G4double rmZCylPos = rmZ2Pos - 22.2*mm -rmH/2;
  G4double rmZ1Pos = rmZCylPos - rmH/2 - rmBoxZ/2;

  G4ThreeVector posrm1 = G4ThreeVector(0,0,rmZ1Pos);
  G4ThreeVector posrm2 = G4ThreeVector(0,0,rmZ2Pos);
  G4ThreeVector posrmcyl = G4ThreeVector(0,0,rmZCylPos);


  G4Transform3D Tr1Pos = G4Transform3D(*rot0, posrm1);
  G4Transform3D Tr2Pos = G4Transform3D(*rot0, posrm2);
  G4Transform3D TrCyl = G4Transform3D(*rot0, posrmcyl);

  G4SubtractionSolid* Shielding1 = new G4SubtractionSolid("Shielding1", mainBox, rmBox1, Tr1Pos);
  G4SubtractionSolid* Shielding2 = new G4SubtractionSolid("Shielding2", Shielding1, rmBox2, Tr2Pos);
  G4SubtractionSolid* Shielding= new G4SubtractionSolid("Shielding", Shielding2, tubrm, TrCyl);


  G4Material* Lead = G4Material::GetMaterial("G4_Pb");

  G4LogicalVolume* ShieldingLead = new G4LogicalVolume(Shielding, Lead, "ShieldingLead");


  return ShieldingLead;
}

G4LogicalVolume* GetConstructionLeadCastleFrame(){

  G4double mainboxX = 644.5*mm;
  G4double mainboxY = mainboxX;
  G4double mainboxZ = 914.4*mm;

  G4double rmBoxX = mainboxX - 2*4.826*mm;
  G4double rmBoxY = mainboxY - 2*4.826*mm;
  G4double rmBoxZ = mainboxZ - 2*4.826*mm;

  G4double cylRmR = 196.978/2*mm+1*mm;
  G4double cylRmH = 20*mm;
  G4double angle0 = 0;
  G4double angle360 = M_PI*2+1;

  G4double rm12BoxX = mainboxX - 50.8*mm;
  G4double rm12BoxY = mainboxY - 50.8*mm;
  G4double rm12BoxZ = mainboxZ - 50.8*mm;

  G4Box* mainBox = new G4Box("mainBox", mainboxX/2, mainboxY/2, mainboxZ/2);
  G4Box* rmMainBox = new G4Box("rmmainBox", rmBoxX/2, rmBoxY/2, rmBoxZ/2 );
  G4Tubs* rmCyl = new G4Tubs("rmCyl", angle0, cylRmR, cylRmH/2, angle0, angle360);
  G4Box* rmBox1 = new G4Box("rmBox1", rm12BoxX, rm12BoxY/2, rm12BoxZ/2);
  G4Box* rmBox2 = new G4Box("rmBox1", rm12BoxX/2, rm12BoxY, rm12BoxZ/2);

  G4ThreeVector zeroVect = G4ThreeVector(0,0,0);
  G4RotationMatrix* rot0 = new G4RotationMatrix;

  G4double ZCyl = mainboxZ/2;
  G4ThreeVector cylVect = G4ThreeVector(0,0,ZCyl);

  G4Transform3D zeroTr = G4Transform3D(*rot0, zeroVect);
  G4Transform3D cylTr = G4Transform3D(*rot0, cylVect);

  G4SubtractionSolid* LeadCastle1 = new G4SubtractionSolid("LeadCastle1", mainBox, rmMainBox, zeroTr);
  G4SubtractionSolid* LeadCastle2 = new G4SubtractionSolid("LeadCastle2", LeadCastle1, rmBox1, zeroTr);
  G4SubtractionSolid* LeadCastle3 = new G4SubtractionSolid("LeadCastle3", LeadCastle2, rmBox2, zeroTr);
  G4SubtractionSolid* LeadCastleFinal = new G4SubtractionSolid("LeadCastleFinal", LeadCastle3, rmCyl, cylTr);

  G4Material* Alu = G4Material::GetMaterial("G4_Al");

  G4LogicalVolume* LeadCastleFrame = new G4LogicalVolume(LeadCastleFinal, Alu, "LeadCastleFrame");

  return LeadCastleFrame;
}

G4LogicalVolume* GetConstructionPartLeadCastle(){


    G4double SMainBoxX = 609.6*mm;
    G4double SMainBoxY = 0.8*mm;
    G4double SMainBoxZ = 863.6*mm;

    G4Box* SMainBox = new G4Box("mainBox", SMainBoxX/2, SMainBoxY/2, SMainBoxZ/2);

    G4Material* Alu = G4Material::GetMaterial("G4_Al");

    G4LogicalVolume* PartLeadCastle = new G4LogicalVolume(SMainBox, Alu, "PartLeadCastle");

    return PartLeadCastle;

}
