#include "run.hh"
#include "G4AnalysisManager.hh"
#include "G4UserRunAction.hh"
#include "G4Run.hh"

#include "G4RootAnalysisManager.hh"

MyRunAction::MyRunAction()
{
G4RootAnalysisManager *analysisManager = G4RootAnalysisManager::Instance();	
        
        
       
    analysisManager->CreateNtuple("Hits","Hits");
	analysisManager->CreateNtupleIColumn("Photons");
	analysisManager->CreateH1("0","Ph", 1, 0 ,500);
    analysisManager->FinishNtuple(0);
     /*  
        man->CreateNtuple("Time","Time");
        man->CreateNtupleDColumn("time");
          man->FinishNtuple(0);
*/
	analysisManager->CreateNtuple("Scoring", "Scoring");
	analysisManager->CreateNtupleDColumn("fEdep");
	analysisManager->FinishNtuple(1);


	 analysisManager->CreateH1("Eabs","Edep in detector", 50, 0.1, 5.);
     //analysisManager->CreateH1("Egap","Edep in gap", 100, 0., 30*MeV);
     //analysisManager->CreateH1("Labs","trackL in absorber", 100, 0., 50*cm);
     //analysisManager->CreateH1("Lgap","trackL in gap", 100, 0., 50*cm);

	 //analysisManager->CreateNtupleDColumn("Eabs");
	 //analysisManager->FinishNtuple(0);
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
	G4RootAnalysisManager *analysisManager = G4RootAnalysisManager::Instance();	
        
        analysisManager->OpenFile("kipida.root");
        
    //    man->CreateNtuple("Hits","Hits");
	//man->CreateNtupleDColumn("Photons");
     //   man->FinishNtuple(0);
	
	
	
	//man->OpenFile("output.root");
	
	
	
	
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
	G4RootAnalysisManager *analysisManager = G4RootAnalysisManager::Instance();
	
	 analysisManager->Write();
	 analysisManager->CloseFile();
}
