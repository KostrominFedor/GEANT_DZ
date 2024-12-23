#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh" 
#include "G4GenericMessenger.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4SubtractionSolid.hh"
#include "G4RotationMatrix.hh"

//#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	MyDetectorConstruction();
	~MyDetectorConstruction();
	
	G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }
	
	virtual G4VPhysicalVolume *Construct();
	
private:
	//G4LogicalVolume *logicDetector;	
	//virtual void ConstructSDandField();
	

	G4RotationMatrix *rotDet;
	
	G4Tubs *solidGeDetector, *solidBody1, *solidBody2;
	G4Box *solidWorld, *solidProtector1, *solidProtector2, *solidProtector3;
	G4Cons *Source;
	G4SubtractionSolid *Subtract1, *Subtract2, *Body;

	G4LogicalVolume *logicWorld, *logicProtector1, *logicProtector2, *logicSubtract1, *logicSubtract2, *logicGeDetector, *logicBody, *logicSource;

	G4VPhysicalVolume *physWorld, *physProtector1, *physProtector2, *physSubtract1, *physSubtract2, *physGeDetector, *physBody, *physSource;
	
	G4LogicalVolume *fScoringVolume;
	
	G4Material*worldMat, *Plu, *Cup, *Alu, *Ger, *K2CO3;
	G4Element*Ge , *Al, *Pb, *Cu;
	
	void DefineMaterials();

	void GeDetector();
	
	G4double xWorld, yWorld, zWorld;

};

#endif
