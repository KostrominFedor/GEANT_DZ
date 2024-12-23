#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{

	DefineMaterials();
	
	xWorld = 1.1*m;
	yWorld = 1.1*m;
	zWorld = 1.1*m;
}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::DefineMaterials()
{
	G4NistManager *nist = G4NistManager::Instance();
	
	G4double energy[2] = {1*eV, 8*eV};
	G4double rindexWorld[2] = {1.0, 1.0};

	G4double abslength2[2]= {100*m,100*m}; 
	G4double abslength3[2]= {1*nm,1*nm};
	
	worldMat = nist->FindOrBuildMaterial("G4_AIR");

	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
	mptWorld->AddProperty("ABSLENGTH", energy, abslength2, 2);        
	
	worldMat->SetMaterialPropertiesTable(mptWorld);
	
	// Новый материал

	Al = nist->FindOrBuildElement("Al");
	Alu = new G4Material("Al", 2.7*g/cm3, 1);
	Alu->AddElement(Al, 1);

	Ge = nist->FindOrBuildElement("Ge");
	Ger = new G4Material("Ge", 5.327*g/cm3, 1);
	Ger->AddElement(Ge, 1);

	Cu = nist->FindOrBuildElement("Cu");
	Cup = new G4Material("Cu", 8.89*g/cm3, 1);
	Cup->AddElement(Cu, 1);

	Pb = nist->FindOrBuildElement("Pb");
	Plu = new G4Material("Pb", 11.35*g/cm3, 1);
	Plu->AddElement(Pb, 1);

	// Материал источника

	K2CO3 = new G4Material("H2O", 2.43*g/cm3, 3);
	K2CO3->AddElement(nist->FindOrBuildElement("K"), 2);
	K2CO3->AddElement(nist->FindOrBuildElement("C"), 1);
	K2CO3->AddElement(nist->FindOrBuildElement("O"), 3);

}



// Новый детектор

void MyDetectorConstruction::GeDetector()
{
	// Passive Defence Cup Plu

	solidProtector1 = new G4Box("solidProtector1", (200.0)*mm, (285.0)*mm, (200.0)*mm);
	//logicProtector1 = new G4LogicalVolume(solidProtector1, water, "logicProtector1");
	//G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin", logicWorld, mirror);
	//fScoringVolume =logicScintillator;
	//physProtector1 = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicProtector1, "physProtector1", logicWorld, false, 0, true);

	solidProtector2 = new G4Box("solidProtector2", (100.0)*mm, (225.0)*mm, (100.0)*mm);
	//logicProtector2 = new G4LogicalVolume(solidProtector2, water, "logicProtector2");
	//G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin", logicWorld, mirror);
	//fScoringVolume =logicScintillator;
	//physProtector2 = new G4PVPlacement(0, G4ThreeVector(0.,60.,0.), logicProtector2, "physProtector2", logicWorld, false, 0, true);

	Subtract1 = new G4SubtractionSolid("Protector1-Protector2", solidProtector1, solidProtector2, 0, G4ThreeVector(0.,60.,0.));
	logicSubtract1 = new G4LogicalVolume(Subtract1, Plu, "logicSubtract1");
	//logicSubtract1->SetVisAttributes(G4Color::Blue());
	//G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin", logicWorld, mirror);
	//fScoringVolume =logicScintillator;
	physSubtract1 = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicSubtract1, "physSubtract1", logicWorld, false, 0, true);

	solidProtector3 = new G4Box("solidProtector3", (50.0)*mm, (200.0)*mm, (50.0)*mm);
	//logicProtector2 = new G4LogicalVolume(solidProtector2, water, "logicProtector2");
	//G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin", logicWorld, mirror);
	//fScoringVolume =logicScintillator;
	//physProtector2 = new G4PVPlacement(0, G4ThreeVector(0.,60.,0.), logicProtector2, "physProtector2", logicWorld, false, 0, true);

	Subtract2 = new G4SubtractionSolid("Protector2-Protector3", solidProtector2, solidProtector3, 0, G4ThreeVector(0.,60.,0.));
	logicSubtract2 = new G4LogicalVolume(Subtract2, Cup, "logicSubtract2");
	//G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin", logicWorld, mirror);
	//fScoringVolume =logicScintillator;
	physSubtract2 = new G4PVPlacement(0, G4ThreeVector(0.,60.,0.), logicSubtract2, "physSubtract2", logicWorld, false, 0, true);

	// Body Alu

	rotDet = new G4RotationMatrix();
	rotDet->rotateX(90.*deg);

	solidBody1 = new G4Tubs("solidBody1", 0.*mm, 41.5*mm, 30.65*mm, 0*deg, 360*deg);
	solidBody2 = new G4Tubs("solidBody2", 0.*mm, 40.5*mm, 29.65*mm, 0*deg, 360*deg);

	Body = new G4SubtractionSolid("solidBody1-solidBody2", solidBody1, solidBody2, 0, G4ThreeVector(0.,0.,1.));
	logicBody = new G4LogicalVolume(Body, Alu,"logicBody");
	physBody = new G4PVPlacement(rotDet,G4ThreeVector(0.,20.65, 0.),logicBody, "physBody", logicWorld, false, 0, true);

	// Detector Ger

	solidGeDetector = new G4Tubs("solidGeDetector", 0.*mm, 33.15*mm, 25.65*mm, 0*deg, 360*deg);
	logicGeDetector = new G4LogicalVolume(solidGeDetector, Ger,"logicGeDetector");
	physGeDetector = new G4PVPlacement(rotDet,G4ThreeVector(0.,20.65, 0.),logicGeDetector, "physGeDetector", logicWorld, false, 0, true);

	// Source K2CO3

	Source = new G4Cons("Source", 0.*mm, 42.5*mm, 0.*mm, 37.5*mm, 35.0*mm, 0*deg, 360*deg);
	logicSource = new G4LogicalVolume(Source, K2CO3,"logicSource");
	physSource = new G4PVPlacement(rotDet,G4ThreeVector(0.,-39.95, 0.),logicSource, "physSource", logicWorld, false, 0, true);

}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{			
	solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
	
	logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
	
	physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);
	
	GeDetector();
		
	return physWorld;
}	

