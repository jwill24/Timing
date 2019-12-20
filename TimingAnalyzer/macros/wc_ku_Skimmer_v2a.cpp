#include "Skimmer.hh"
#include "TROOT.h"

#include <iostream>


Skimmer::Skimmer(const TString & indir, const TString & outdir, const TString & filename, const TString & skimconfig)

  : fInDir(indir), fOutDir(outdir), fFileName(filename), fSkimConfig(skimconfig)
{

  // because root is dumb?
  gROOT->ProcessLine("#include <vector>");

  ////////////////////////
  // Get all the inputs //
  ////////////////////////
 //std::cout << "Setting up inputs for skim" << std::endl;

  // Set skim config options 
  Skimmer::SetupDefaults();
 //std::cout << "Running SkimConfig" << std::endl;
  Skimmer::SetupSkimConfig();

  // get detids if skim needs it
  //if (fSkim == SkimType::DiXtal) 
  Common::SetupDetIDs();

  // Get era info
  Common::SetupEras();

  // Get input file
  const TString infilename = Form("%s/%s", fInDir.Data(), fFileName.Data());
 //std::cout << "Getting input file " << infilename.Data() << std::endl;
  fInFile = TFile::Open(infilename.Data());
  Common::CheckValidFile(fInFile,infilename);
 //std::cout << "Finished getting input file " << infilename.Data() << std::endl;

  // Get input config tree
  const TString inconfigtreename = Form("%s/%s",Common::rootdir.Data(),Common::configtreename.Data());
 //std::cout << "Getting input config tree " << inconfigtreename.Data() << std::endl;
  fInConfigTree = (TTree*)fInFile->Get(inconfigtreename.Data());
  Common::CheckValidTree(fInConfigTree,inconfigtreename,infilename);
  Skimmer::GetInConfig();
 //std::cout << "Finished getting input config tree " << inconfigtreename.Data() << std::endl;

  // get sample weight from in config
  Skimmer::GetSampleWeight();

  // Get main input tree and initialize it
  const TString indisphotreename = Form("%s/%s",Common::rootdir.Data(),Common::disphotreename.Data());
 //std::cout << "Getting input tree " << indisphotreename.Data() << std::endl;
  fInTree = (TTree*)fInFile->Get(indisphotreename.Data());
  Common::CheckValidTree(fInTree,indisphotreename,infilename);
  Skimmer::InitInTree();
 //std::cout << "Finished getting input tree " << indisphotreename.Data() << std::endl;

  // Get the cut flow + event weight histogram --> set the wgtsum
  const TString inh_cutflowname = Form("%s/%s",Common::rootdir.Data(),Common::h_cutflowname.Data());
  fInCutFlow = (TH1F*)fInFile->Get(inh_cutflowname.Data());
  Common::CheckValidHist(fInCutFlow,inh_cutflowname,infilename);

  const TString inh_cutflow_wgtname = Form("%s/%s",Common::rootdir.Data(),Common::h_cutflow_wgtname.Data());
  fInCutFlowWgt = (TH1F*)fInFile->Get(inh_cutflow_wgtname.Data());
  Common::CheckValidHist(fInCutFlowWgt,inh_cutflow_wgtname,infilename);

  // Get PU weights input
  fPUWeights.clear();

//  if(fIsMC)
//  {
//   //std::cout << "Opening " << fPUWgtFileName << std::endl;
//    fInPUWgtFile = TFile::Open(fPUWgtFileName);
//    Common::CheckValidFile(fInPUWgtFile,fPUWgtFileName);
//
//    const TString puhistname = Form("%s_%s",Common::puTrueHistName.Data(),Common::puwgtHistName.Data());
//    fInPUWgtHist = (TH1F*)fInPUWgtFile->Get(puhistname.Data());
//    Common::CheckValidHist(fInPUWgtHist,puhistname,fPUWgtFileName);
//
//    Skimmer::GetPUWeights();
//  }

  /////////////////////////
  // Set all the outputs //
  /////////////////////////
 //std::cout << "Setting up output skim" << std::endl;

  // Make the output file, make trees, then init them
  fOutFile = TFile::Open(Form("%s/%s", fOutDir.Data(), fFileName.Data()),"recreate");
  fOutFile->cd();
  
  fOutConfigTree = new TTree(Common::configtreename.Data(),Common::configtreename.Data());
  fOutTree = new TTree(Common::disphotreename.Data(),Common::disphotreename.Data());

  // Init output info
  Skimmer::InitAndSetOutConfig();
  Skimmer::InitOutTree();
  Skimmer::InitOutCutFlowHists();
  //std::cout << "Finished setting up output skim" << std::endl;

  tofHist = new TH1F("tofHist","Time of Flight [ns]",10000,-5,5);
  tofHist->Sumw2(); 

  fOutAveXtalRecTimeHist = new TH1F("AveXtalRecTimeHist","AveXtalRecTime",400,-20,20);
  fOutAveXtalRecTimeHist->Sumw2();
  fOutAveXtalPhoRecTimeHist = new TH1F("AveXtalPhoRecTimeHist","AveXtalPhoRecTime",400,-20,20);
  fOutAveXtalPhoRecTimeHist->Sumw2();
  fOutDifXtalPhoRecTimeHist = new TH1F("DifXtalPhoRecTimeHist","DifXtalPhoRecTime",400,-20,20);
  fOutDifXtalPhoRecTimeHist->Sumw2();

  fOutAveXtalRtRecTimeHist = new TH1F("AveXtalRtRecTimeHist","AveXtalRtRecTime",400,-20,20);
  fOutAveXtalRtRecTimeHist->Sumw2();
  fOutAveXtalRtPhoRecTimeHist = new TH1F("AveXtalRtPhoRecTimeHist","AveXtalRtPhoRecTime",400,-20,20);
  fOutAveXtalRtPhoRecTimeHist->Sumw2();
  fOutDifXtalRtPhoRecTimeHist = new TH1F("DifXtalRtPhoRecTimeHist","DifXtalRtPhoRecTime",400,-20,20);
  fOutDifXtalRtPhoRecTimeHist->Sumw2();

  fOutAveXtalRtStcRecTimeHist = new TH1F("AveXtalRtStcRecTimeHist","AveXtalRtStcRecTime",400,-20,20);
  fOutAveXtalRtStcRecTimeHist->Sumw2();
  fOutAveXtalRtStcPhoRecTimeHist = new TH1F("AveXtalRtStcPhoRecTimeHist","AveXtalRtStcPhoRecTime",400,-20,20);
  fOutAveXtalRtStcPhoRecTimeHist->Sumw2();
  fOutDifXtalRtStcPhoRecTimeHist = new TH1F("DifXtalRtStcPhoRecTimeHist","DifXtalRtStcPhoRecTime",400,-20,20);
  fOutDifXtalRtStcPhoRecTimeHist->Sumw2();

 // fOutAveXtalRtOOTRecTimeHist = new TH1F("AveXtalRtOOTRecTimeHist","AveXtalRtOOTRecTime",400,-20,20);
 // fOutAveXtalRtOOTRecTimeHist->Sumw2();
 // fOutAveXtalRtOOTPhoRecTimeHist = new TH1F("AveXtalRtOOTPhoRecTimeHist","AveXtalRtOOTPhoRecTime",400,-20,20);
 // fOutAveXtalRtOOTPhoRecTimeHist->Sumw2();
 // fOutDifXtalRtOOTPhoRecTimeHist = new TH1F("DifXtalRtOOTPhoRecTimeHist","DifXtalRtOOTPhoRecTime",400,-20,20);
 // fOutDifXtalRtOOTPhoRecTimeHist->Sumw2();

  fOutAveXtalRtOOTStcPhoRecTimeHist = new TH1F("AveXtalRtOOTStcPhoRecTimeHist","AveXtalRtOOTStcPhoRecTime",400,-20,20);
  fOutAveXtalRtOOTStcPhoRecTimeHist->Sumw2();
  fOutDifXtalRtOOTStcPhoRecTimeHist = new TH1F("DifXtalRtOOTStcPhoRecTimeHist","DifXtalRtOOTStcPhoRecTime",400,-20,20);
  fOutDifXtalRtOOTStcPhoRecTimeHist->Sumw2();

  fOutAveXtalOccHist = new TH1F("AveXtalOccHist","AveXtalOcc",250,0,250);
  fOutAveXtalOccHist->Sumw2();
  fOutAveXtalPhoOccHist = new TH1F("AveXtalPhoOccHist","AveXtalPhoOcc",250,0,250);
  fOutAveXtalPhoOccHist->Sumw2();

  fOutAveXtalRecTimeHistEB = new TH1F("AveXtalRecTimeEBHist","AveXtalRecTime EB",400,-20,20);
  fOutAveXtalRecTimeHistEB->Sumw2();
  fOutAveXtalRecTimeHistEP = new TH1F("AveXtalRecTimeEPHist","AveXtalRecTime EP",400,-20,20);
  fOutAveXtalRecTimeHistEP->Sumw2();
  fOutAveXtalRecTimeHistEM = new TH1F("AveXtalRecTimeEMHist","AveXtalRecTime EM",400,-20,20);
  fOutAveXtalRecTimeHistEM->Sumw2();

  fOutAveXtalRtRecTimeHistEB = new TH1F("AveXtalRtRecTimeEBHist","AveXtalRtRecTime EB",400,-20,20);
  fOutAveXtalRtRecTimeHistEB->Sumw2();
  fOutAveXtalRtRecTimeHistEP = new TH1F("AveXtalRtRecTimeEPHist","AveXtalRtRecTime EP",400,-20,20);
  fOutAveXtalRtRecTimeHistEP->Sumw2();
  fOutAveXtalRtRecTimeHistEM = new TH1F("AveXtalRtRecTimeEMHist","AveXtalRtRecTime EM",400,-20,20);
  fOutAveXtalRtRecTimeHistEM->Sumw2();

  fOutAveXtalRtStcRecTimeHistEB = new TH1F("AveXtalRtStcRecTimeEBHist","AveXtalRtStcRecTime EB",400,-20,20);
  fOutAveXtalRtStcRecTimeHistEB->Sumw2();
  fOutAveXtalRtStcRecTimeHistEP = new TH1F("AveXtalRtStcRecTimeEPHist","AveXtalRtStcRecTime EP",400,-20,20);
  fOutAveXtalRtStcRecTimeHistEP->Sumw2();
  fOutAveXtalRtStcRecTimeHistEM = new TH1F("AveXtalRtStcRecTimeEMHist","AveXtalRtStcRecTime EM",400,-20,20);
  fOutAveXtalRtStcRecTimeHistEM->Sumw2();

  //fOutAveXtalRtOOTRecTimeHistEB = new TH1F("AveXtalRtOOTRecTimeEBHist","AveXtalRtOOTRecTime EB",400,-20,20);
  //fOutAveXtalRtOOTRecTimeHistEB->Sumw2();
  //fOutAveXtalRtOOTRecTimeHistEP = new TH1F("AveXtalRtOOTRecTimeEPHist","AveXtalRtOOTRecTime EP",400,-20,20);
  //fOutAveXtalRtOOTRecTimeHistEP->Sumw2();
  //fOutAveXtalRtOOTRecTimeHistEM = new TH1F("AveXtalRtOOTRecTimeEMHist","AveXtalRtOOTRecTime EM",400,-20,20);
  //fOutAveXtalRtOOTRecTimeHistEM->Sumw2();

  fOutAveXtalRtOOTStcRecTimeHistEB = new TH1F("AveXtalRtOOTStcRecTimeEBHist","AveXtalRtOOTStcRecTime EB",400,-20,20);
  fOutAveXtalRtOOTStcRecTimeHistEB->Sumw2();
  fOutAveXtalRtOOTStcRecTimeHistEP = new TH1F("AveXtalRtOOTStcRecTimeEPHist","AveXtalRtOOTStcRecTime EP",400,-20,20);
  fOutAveXtalRtOOTStcRecTimeHistEP->Sumw2();
  fOutAveXtalRtOOTStcRecTimeHistEM = new TH1F("AveXtalRtOOTStcRecTimeEMHist","AveXtalRtOOTStcRecTime EM",400,-20,20);
  fOutAveXtalRtOOTStcRecTimeHistEM->Sumw2();

  fOutAveXtalRtOOTStcRecTimeE0HistEB = new TH1F("AveXtalRtOOTStcRecTimeE0EBHist","AveXtalRtOOTStcRecTimeE0 EB",400,-20,20);
  fOutAveXtalRtOOTStcRecTimeE0HistEB->Sumw2();
  fOutAveXtalRtOOTStcRecTimeE0HistEP = new TH1F("AveXtalRtOOTStcRecTimeE0EPHist","AveXtalRtOOTStcRecTimeE0 EP",400,-20,20);
  fOutAveXtalRtOOTStcRecTimeE0HistEP->Sumw2();
  fOutAveXtalRtOOTStcRecTimeE0HistEM = new TH1F("AveXtalRtOOTStcRecTimeE0EMHist","AveXtalRtOOTStcRecTimeE0 EM",400,-20,20);
  fOutAveXtalRtOOTStcRecTimeE0HistEM->Sumw2();

  fOutAveXtalRtOOTStcRecTimeE1HistEB = new TH1F("AveXtalRtOOTStcRecTimeE1EBHist","AveXtalRtOOTStcRecTimeE1 EB",400,-20,20);
  fOutAveXtalRtOOTStcRecTimeE1HistEB->Sumw2();
  fOutAveXtalRtOOTStcRecTimeE1HistEP = new TH1F("AveXtalRtOOTStcRecTimeE1EPHist","AveXtalRtOOTStcRecTimeE1 EP",400,-20,20);
  fOutAveXtalRtOOTStcRecTimeE1HistEP->Sumw2();
  fOutAveXtalRtOOTStcRecTimeE1HistEM = new TH1F("AveXtalRtOOTStcRecTimeE1EMHist","AveXtalRtOOTStcRecTimeE1 EM",400,-20,20);
  fOutAveXtalRtOOTStcRecTimeE1HistEM->Sumw2();

  fOutAveXtalRtOOTStcRecTime2E1HistEB = new TH1F("AveXtalRtOOTStcRecTime2E1EBHist","AveXtalRtOOTStcRecTime2E1 EB",400,-20,20);
  fOutAveXtalRtOOTStcRecTime2E1HistEB->Sumw2();
  fOutAveXtalRtOOTStcRecTime2E1HistEP = new TH1F("AveXtalRtOOTStcRecTime2E1EPHist","AveXtalRtOOTStcRecTime2E1 EP",400,-20,20);
  fOutAveXtalRtOOTStcRecTime2E1HistEP->Sumw2();
  fOutAveXtalRtOOTStcRecTime2E1HistEM = new TH1F("AveXtalRtOOTStcRecTime2E1EMHist","AveXtalRtOOTStcRecTime2E1 EM",400,-20,20);
  fOutAveXtalRtOOTStcRecTime2E1HistEM->Sumw2();

  fOutAveXtalRtOOTStcRecTime4E1HistEB = new TH1F("AveXtalRtOOTStcRecTime4E1EBHist","AveXtalRtOOTStcRecTime4E1 EB",400,-20,20);
  fOutAveXtalRtOOTStcRecTime4E1HistEB->Sumw2();
  fOutAveXtalRtOOTStcRecTime4E1HistEP = new TH1F("AveXtalRtOOTStcRecTime4E1EPHist","AveXtalRtOOTStcRecTime4E1 EP",400,-20,20);
  fOutAveXtalRtOOTStcRecTime4E1HistEP->Sumw2();
  fOutAveXtalRtOOTStcRecTime4E1HistEM = new TH1F("AveXtalRtOOTStcRecTime4E1EMHist","AveXtalRtOOTStcRecTime4E1 EM",400,-20,20);
  fOutAveXtalRtOOTStcRecTime4E1HistEM->Sumw2();

  fOutAveXtalRtOOTStcRecTimeE2HistEB = new TH1F("AveXtalRtOOTStcRecTimeE2EBHist","AveXtalRtOOTStcRecTimeE2 EB",400,-20,20);
  fOutAveXtalRtOOTStcRecTimeE2HistEB->Sumw2();
  fOutAveXtalRtOOTStcRecTimeE2HistEP = new TH1F("AveXtalRtOOTStcRecTimeE2EPHist","AveXtalRtOOTStcRecTimeE2 EP",400,-20,20);
  fOutAveXtalRtOOTStcRecTimeE2HistEP->Sumw2();
  fOutAveXtalRtOOTStcRecTimeE2HistEM = new TH1F("AveXtalRtOOTStcRecTimeE2EMHist","AveXtalRtOOTStcRecTimeE2 EM",400,-20,20);
  fOutAveXtalRtOOTStcRecTimeE2HistEM->Sumw2();

  fOutAveXtalRtOOTStcRecTimeE5HistEB = new TH1F("AveXtalRtOOTStcRecTimeE5EBHist","AveXtalRtOOTStcRecTimeE5 EB",400,-20,20);
  fOutAveXtalRtOOTStcRecTimeE5HistEB->Sumw2();
  fOutAveXtalRtOOTStcRecTimeE5HistEP = new TH1F("AveXtalRtOOTStcRecTimeE5EPHist","AveXtalRtOOTStcRecTimeE5 EP",400,-20,20);
  fOutAveXtalRtOOTStcRecTimeE5HistEP->Sumw2();
  fOutAveXtalRtOOTStcRecTimeE5HistEM = new TH1F("AveXtalRtOOTStcRecTimeE5EMHist","AveXtalRtOOTStcRecTimeE5 EM",400,-20,20);
  fOutAveXtalRtOOTStcRecTimeE5HistEM->Sumw2();

  fOutAveXtalRtOOTStcRecTime2E5HistEB = new TH1F("AveXtalRtOOTStcRecTime2E5EBHist","AveXtalRtOOTStcRecTime2E5 EB",400,-20,20);
  fOutAveXtalRtOOTStcRecTime2E5HistEB->Sumw2();
  fOutAveXtalRtOOTStcRecTime2E5HistEP = new TH1F("AveXtalRtOOTStcRecTime2E5EPHist","AveXtalRtOOTStcRecTime2E5 EP",400,-20,20);
  fOutAveXtalRtOOTStcRecTime2E5HistEP->Sumw2();
  fOutAveXtalRtOOTStcRecTime2E5HistEM = new TH1F("AveXtalRtOOTStcRecTime2E5EMHist","AveXtalRtOOTStcRecTime2E5 EM",400,-20,20);
  fOutAveXtalRtOOTStcRecTime2E5HistEM->Sumw2();

  fOutAveXtalRtOOTStcRecTime4E5HistEB = new TH1F("AveXtalRtOOTStcRecTime4E5EBHist","AveXtalRtOOTStcRecTime4E5 EB",400,-20,20);
  fOutAveXtalRtOOTStcRecTime4E5HistEB->Sumw2();
  fOutAveXtalRtOOTStcRecTime4E5HistEP = new TH1F("AveXtalRtOOTStcRecTime4E5EPHist","AveXtalRtOOTStcRecTime4E5 EP",400,-20,20);
  fOutAveXtalRtOOTStcRecTime4E5HistEP->Sumw2();
  fOutAveXtalRtOOTStcRecTime4E5HistEM = new TH1F("AveXtalRtOOTStcRecTime4E5EMHist","AveXtalRtOOTStcRecTime4E5 EM",400,-20,20);
  fOutAveXtalRtOOTStcRecTime4E5HistEM->Sumw2();

  fOutAveXtalRtOOTStcRecTimeE10HistEB = new TH1F("AveXtalRtOOTStcRecTimeE10EBHist","AveXtalRtOOTStcRecTimeE10 EB",400,-20,20);
  fOutAveXtalRtOOTStcRecTimeE10HistEB->Sumw2();
  fOutAveXtalRtOOTStcRecTimeE10HistEP = new TH1F("AveXtalRtOOTStcRecTimeE10EPHist","AveXtalRtOOTStcRecTimeE10 EP",400,-20,20);
  fOutAveXtalRtOOTStcRecTimeE10HistEP->Sumw2();
  fOutAveXtalRtOOTStcRecTimeE10HistEM = new TH1F("AveXtalRtOOTStcRecTimeE10EMHist","AveXtalRtOOTStcRecTimeE10 EM",400,-20,20);
  fOutAveXtalRtOOTStcRecTimeE10HistEM->Sumw2();

  fOutAveXtalRtOOTStcPhoClRecTimeHistEB = new TH1F("AveXtalRtOOTStcPhoClRecTimeEBHist","AveXtalRtOOTStcPhoClRecTime EB",400,-20,20);
  fOutAveXtalRtOOTStcPhoClRecTimeHistEB->Sumw2();
  fOutAveXtalRtOOTStcPhoClRecTimeHistEP = new TH1F("AveXtalRtOOTStcPhoClRecTimeEPHist","AveXtalRtOOTStcPhoClRecTime EP",400,-20,20);
  fOutAveXtalRtOOTStcPhoClRecTimeHistEP->Sumw2();
  fOutAveXtalRtOOTStcPhoClRecTimeHistEM = new TH1F("AveXtalRtOOTStcPhoClRecTimeEMHist","AveXtalRtOOTStcPhoClRecTime EM",400,-20,20);
  fOutAveXtalRtOOTStcPhoClRecTimeHistEM->Sumw2();

  fOutAveXtalRtOOTStcPhoIcRecTimeHistEB = new TH1F("AveXtalRtOOTStcPhoIcRecTimeEBHist","AveXtalRtOOTStcPhoIcRecTime EB",400,-20,20);
  fOutAveXtalRtOOTStcPhoIcRecTimeHistEB->Sumw2();
  fOutAveXtalRtOOTStcPhoIcRecTimeHistEP = new TH1F("AveXtalRtOOTStcPhoIcRecTimeEPHist","AveXtalRtOOTStcPhoIcRecTime EP",400,-20,20);
  fOutAveXtalRtOOTStcPhoIcRecTimeHistEP->Sumw2();
  fOutAveXtalRtOOTStcPhoIcRecTimeHistEM = new TH1F("AveXtalRtOOTStcPhoIcRecTimeEMHist","AveXtalRtOOTStcPhoIcRecTime EM",400,-20,20);
  fOutAveXtalRtOOTStcPhoIcRecTimeHistEM->Sumw2();

  fOutAveXtalOccHistEB = new TH1F("AveXtalOccEBHist","AveXtalOcc EB",250,0,250);
  fOutAveXtalOccHistEB->Sumw2();
  fOutAveXtalOccHistEP = new TH1F("AveXtalOccEPHist","AveXtalOcc EP",250,0,250);
  fOutAveXtalOccHistEP->Sumw2();
  fOutAveXtalOccHistEM = new TH1F("AveXtalOccEMHist","AveXtalOcc EM",250,0,250);
  fOutAveXtalOccHistEM->Sumw2();

  fOutAveXtalPhoRecTimeHistEB = new TH1F("AveXtalPhoRecTimeEBHist","AveXtalPhoRecTime EB",400,-20,20);
  fOutAveXtalPhoRecTimeHistEB->Sumw2();
  fOutAveXtalPhoRecTimeHistEP = new TH1F("AveXtalPhoRecTimeEPHist","AveXtalPhoRecTime EP",400,-20,20);
  fOutAveXtalPhoRecTimeHistEP->Sumw2();
  fOutAveXtalPhoRecTimeHistEM = new TH1F("AveXtalPhoRecTimeEMHist","AveXtalPhoRecTime EM",400,-20,20);
  fOutAveXtalPhoRecTimeHistEM->Sumw2();

  fOutAveXtalRtPhoRecTimeHistEB = new TH1F("AveXtalRtPhoRecTimeEBHist","AveXtalRtPhoRecTime EB",400,-20,20);
  fOutAveXtalRtPhoRecTimeHistEB->Sumw2();
  fOutAveXtalRtPhoRecTimeHistEP = new TH1F("AveXtalRtPhoRecTimeEPHist","AveXtalRtPhoRecTime EP",400,-20,20);
  fOutAveXtalRtPhoRecTimeHistEP->Sumw2();
  fOutAveXtalRtPhoRecTimeHistEM = new TH1F("AveXtalRtPhoRecTimeEMHist","AveXtalRtPhoRecTime EM",400,-20,20);
  fOutAveXtalRtPhoRecTimeHistEM->Sumw2();

  fOutAveXtalRtStcPhoRecTimeHistEB = new TH1F("AveXtalRtStcPhoRecTimeEBHist","AveXtalRtStcPhoRecTime EB",400,-20,20);
  fOutAveXtalRtStcPhoRecTimeHistEB->Sumw2();
  fOutAveXtalRtStcPhoRecTimeHistEP = new TH1F("AveXtalRtStcPhoRecTimeEPHist","AveXtalRtStcPhoRecTime EP",400,-20,20);
  fOutAveXtalRtStcPhoRecTimeHistEP->Sumw2();
  fOutAveXtalRtStcPhoRecTimeHistEM = new TH1F("AveXtalRtStcPhoRecTimeEMHist","AveXtalRtStcPhoRecTime EM",400,-20,20);
  fOutAveXtalRtStcPhoRecTimeHistEM->Sumw2();
  
  //fOutAveXtalRtOOTPhoRecTimeHistEB = new TH1F("AveXtalRtOOTPhoRecTimeEBHist","AveXtalRtOOTPhoRecTime EB",400,-20,20);
  //fOutAveXtalRtOOTPhoRecTimeHistEB->Sumw2();
  //fOutAveXtalRtOOTPhoRecTimeHistEP = new TH1F("AveXtalRtOOTPhoRecTimeEPHist","AveXtalRtOOTPhoRecTime EP",400,-20,20);
  //fOutAveXtalRtOOTPhoRecTimeHistEP->Sumw2();
  //fOutAveXtalRtOOTPhoRecTimeHistEM = new TH1F("AveXtalRtOOTPhoRecTimeEMHist","AveXtalRtOOTPhoRecTime EM",400,-20,20);
  //fOutAveXtalRtOOTPhoRecTimeHistEM->Sumw2();

  fOutAveXtalRtOOTStcPhoRecTimeHistEB = new TH1F("AveXtalRtOOTStcPhoRecTimeEBHist","AveXtalRtOOTStcPhoRecTime EB",400,-20,20);
  fOutAveXtalRtOOTStcPhoRecTimeHistEB->Sumw2();
  fOutAveXtalRtOOTStcPhoRecTimeHistEP = new TH1F("AveXtalRtOOTStcPhoRecTimeEPHist","AveXtalRtOOTStcPhoRecTime EP",400,-20,20);
  fOutAveXtalRtOOTStcPhoRecTimeHistEP->Sumw2();
  fOutAveXtalRtOOTStcPhoRecTimeHistEM = new TH1F("AveXtalRtOOTStcPhoRecTimeEMHist","AveXtalRtOOTStcPhoRecTime EM",400,-20,20);
  fOutAveXtalRtOOTStcPhoRecTimeHistEM->Sumw2();

  fOutAveXtalPhoOccHistEB = new TH1F("AveXtalPhoOccEBHist","AveXtalPhoOcc EB",20,0,20);
  fOutAveXtalPhoOccHistEB->Sumw2();
  fOutAveXtalPhoOccHistEP = new TH1F("AveXtalPhoOccEPHist","AveXtalPhoOcc EP",20,0,20);
  fOutAveXtalPhoOccHistEP->Sumw2();
  fOutAveXtalPhoOccHistEM = new TH1F("AveXtalPhoOccEMHist","AveXtalPhoOcc EM",20,0,20);
  fOutAveXtalPhoOccHistEM->Sumw2();

  fOutDifXtalPhoRecTimeHistEB = new TH1F("DifXtalPhoRecTimeEBHist","DifXtalPhoRecTime EB",400,-20,20);
  fOutDifXtalPhoRecTimeHistEB->Sumw2();
  fOutDifXtalPhoRecTimeHistEP = new TH1F("DifXtalPhoRecTimeEPHist","DifXtalPhoRecTime EP",400,-20,20);
  fOutDifXtalPhoRecTimeHistEP->Sumw2();
  fOutDifXtalPhoRecTimeHistEM = new TH1F("DifXtalPhoRecTimeEMHist","DifXtalPhoRecTime EM",400,-20,20);
  fOutDifXtalPhoRecTimeHistEM->Sumw2();

  fOutDifXtalRtPhoRecTimeHistEB = new TH1F("DifXtalRtPhoRecTimeEBHist","DifXtalRtPhoRecTime EB",400,-20,20);
  fOutDifXtalRtPhoRecTimeHistEB->Sumw2();
  fOutDifXtalRtPhoRecTimeHistEP = new TH1F("DifXtalRtPhoRecTimeEPHist","DifXtalRtPhoRecTime EP",400,-20,20);
  fOutDifXtalRtPhoRecTimeHistEP->Sumw2();
  fOutDifXtalRtPhoRecTimeHistEM = new TH1F("DifXtalRtPhoRecTimeEMHist","DifXtalRtPhoRecTime EM",400,-20,20);
  fOutDifXtalRtPhoRecTimeHistEM->Sumw2();

  fOutDifXtalRtStcPhoRecTimeHistEB = new TH1F("DifXtalRtStcPhoRecTimeEBHist","DifXtalRtStcPhoRecTime EB",400,-20,20);
  fOutDifXtalRtStcPhoRecTimeHistEB->Sumw2();
  fOutDifXtalRtStcPhoRecTimeHistEP = new TH1F("DifXtalRtStcPhoRecTimeEPHist","DifXtalRtStcPhoRecTime EP",400,-20,20);
  fOutDifXtalRtStcPhoRecTimeHistEP->Sumw2();
  fOutDifXtalRtStcPhoRecTimeHistEM = new TH1F("DifXtalRtStcPhoRecTimeEMHist","DifXtalRtStcPhoRecTime EM",400,-20,20);
  fOutDifXtalRtStcPhoRecTimeHistEM->Sumw2();

  //fOutDifXtalRtOOTPhoRecTimeHistEB = new TH1F("DifXtalRtOOTPhoRecTimeEBHist","DifXtalRtOOTPhoRecTime EB",400,-20,20);
  //fOutDifXtalRtOOTPhoRecTimeHistEB->Sumw2();
  //fOutDifXtalRtOOTPhoRecTimeHistEP = new TH1F("DifXtalRtOOTPhoRecTimeEPHist","DifXtalRtOOTPhoRecTime EP",400,-20,20);
  //fOutDifXtalRtOOTPhoRecTimeHistEP->Sumw2();
  //fOutDifXtalRtOOTPhoRecTimeHistEM = new TH1F("DifXtalRtOOTPhoRecTimeEMHist","DifXtalRtOOTPhoRecTime EM",400,-20,20);
  //fOutDifXtalRtOOTPhoRecTimeHistEM->Sumw2();

  fOutDifXtalRtOOTStcPhoRecTimeHistEB = new TH1F("DifXtalRtOOTStcPhoRecTimeEBHist","DifXtalRtOOTStcPhoRecTime EB",400,-20,20);
  fOutDifXtalRtOOTStcPhoRecTimeHistEB->Sumw2();
  fOutDifXtalRtOOTStcPhoRecTimeHistEP = new TH1F("DifXtalRtOOTStcPhoRecTimeEPHist","DifXtalRtOOTStcPhoRecTime EP",400,-20,20);
  fOutDifXtalRtOOTStcPhoRecTimeHistEP->Sumw2();
  fOutDifXtalRtOOTStcPhoRecTimeHistEM = new TH1F("DifXtalRtOOTStcPhoRecTimeEMHist","DifXtalRtOOTStcPhoRecTime EM",400,-20,20);
  fOutDifXtalRtOOTStcPhoRecTimeHistEM->Sumw2();

  fOutAveXtalRecTimeMapEB = new TH2F("AveXtalRecTimeEBMap","AveXtalRecTime Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalRecTimeMapEB->Sumw2();
  fOutAveXtalRecTimeMapEP = new TH2F("AveXtalRecTimeEPMap","AveXtalRecTime Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRecTimeMapEP->Sumw2();
  fOutAveXtalRecTimeMapEM = new TH2F("AveXtalRecTimeEMMap","AveXtalRecTime Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRecTimeMapEM->Sumw2();

  fOutAveXtalRtRecTimeMapEB = new TH2F("AveXtalRtRecTimeEBMap","AveXtalRtRecTime Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalRtRecTimeMapEB->Sumw2();
  fOutAveXtalRtRecTimeMapEP = new TH2F("AveXtalRtRecTimeEPMap","AveXtalRtRecTime Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtRecTimeMapEP->Sumw2();
  fOutAveXtalRtRecTimeMapEM = new TH2F("AveXtalRtRecTimeEMMap","AveXtalRtRecTime Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtRecTimeMapEM->Sumw2();

  fOutAveXtalRtStcRecTimeMapEB = new TH2F("AveXtalRtStcRecTimeEBMap","AveXtalRtStcRecTime Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalRtStcRecTimeMapEB->Sumw2();
  fOutAveXtalRtStcRecTimeMapEP = new TH2F("AveXtalRtStcRecTimeEPMap","AveXtalRtStcRecTime Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtStcRecTimeMapEP->Sumw2();
  fOutAveXtalRtStcRecTimeMapEM = new TH2F("AveXtalRtStcRecTimeEMMap","AveXtalRtStcRecTime Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtStcRecTimeMapEM->Sumw2();

  //fOutAveXtalRtOOTRecTimeMapEB = new TH2F("AveXtalRtOOTRecTimeEBMap","AveXtalRtOOTRecTime Map EB",171,-85.5,85.5,360,0.5,360.5);
  //fOutAveXtalRtOOTRecTimeMapEB->Sumw2();
  //fOutAveXtalRtOOTRecTimeMapEP = new TH2F("AveXtalRtOOTRecTimeEPMap","AveXtalRtOOTRecTime Map EP",100,0.5,100.5,100,0.5,100.5);
  //fOutAveXtalRtOOTRecTimeMapEP->Sumw2();
  //fOutAveXtalRtOOTRecTimeMapEM = new TH2F("AveXtalRtOOTRecTimeEMMap","AveXtalRtOOTRecTime Map EM",100,0.5,100.5,100,0.5,100.5);
  //fOutAveXtalRtOOTRecTimeMapEM->Sumw2();

  fOutAveXtalRtOOTStcRecTimeMapEB = new TH2F("AveXtalRtOOTStcRecTimeEBMap","AveXtalRtOOTStcRecTime Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalRtOOTStcRecTimeMapEB->Sumw2();
  fOutAveXtalRtOOTStcRecTimeMapEP = new TH2F("AveXtalRtOOTStcRecTimeEPMap","AveXtalRtOOTStcRecTime Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcRecTimeMapEP->Sumw2();
  fOutAveXtalRtOOTStcRecTimeMapEM = new TH2F("AveXtalRtOOTStcRecTimeEMMap","AveXtalRtOOTStcRecTime Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcRecTimeMapEM->Sumw2();

  fOutAveXtalRtOOTStcRecTimeE0MapEB = new TH2F("AveXtalRtOOTStcRecTimeE0EBMap","AveXtalRtOOTStcRecTimeE0 Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalRtOOTStcRecTimeE0MapEB->Sumw2();
  fOutAveXtalRtOOTStcRecTimeE0MapEP = new TH2F("AveXtalRtOOTStcRecTimeE0EPMap","AveXtalRtOOTStcRecTimeE0 Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcRecTimeE0MapEP->Sumw2();
  fOutAveXtalRtOOTStcRecTimeE0MapEM = new TH2F("AveXtalRtOOTStcRecTimeE0EMMap","AveXtalRtOOTStcRecTimeE0 Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcRecTimeE0MapEM->Sumw2();

  fOutAveXtalRtOOTStcRecTimeE1MapEB = new TH2F("AveXtalRtOOTStcRecTimeE1EBMap","AveXtalRtOOTStcRecTimeE1 Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalRtOOTStcRecTimeE1MapEB->Sumw2();
  fOutAveXtalRtOOTStcRecTimeE1MapEP = new TH2F("AveXtalRtOOTStcRecTimeE1EPMap","AveXtalRtOOTStcRecTimeE1 Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcRecTimeE1MapEP->Sumw2();
  fOutAveXtalRtOOTStcRecTimeE1MapEM = new TH2F("AveXtalRtOOTStcRecTimeE1EMMap","AveXtalRtOOTStcRecTimeE1 Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcRecTimeE1MapEM->Sumw2();

  fOutAveXtalRtOOTStcRecTime2E1MapEB = new TH2F("AveXtalRtOOTStcRecTime2E1EBMap","AveXtalRtOOTStcRecTime2E1 Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalRtOOTStcRecTime2E1MapEB->Sumw2();
  fOutAveXtalRtOOTStcRecTime2E1MapEP = new TH2F("AveXtalRtOOTStcRecTime2E1EPMap","AveXtalRtOOTStcRecTime2E1 Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcRecTime2E1MapEP->Sumw2();
  fOutAveXtalRtOOTStcRecTime2E1MapEM = new TH2F("AveXtalRtOOTStcRecTime2E1EMMap","AveXtalRtOOTStcRecTime2E1 Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcRecTime2E1MapEM->Sumw2();
  fOutAveXtalRtOOTStcRecTime4E1MapEB = new TH2F("AveXtalRtOOTStcRecTime4E1EBMap","AveXtalRtOOTStcRecTime4E1 Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalRtOOTStcRecTime4E1MapEB->Sumw2();
  fOutAveXtalRtOOTStcRecTime4E1MapEP = new TH2F("AveXtalRtOOTStcRecTime4E1EPMap","AveXtalRtOOTStcRecTime4E1 Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcRecTime4E1MapEP->Sumw2();
  fOutAveXtalRtOOTStcRecTime4E1MapEM = new TH2F("AveXtalRtOOTStcRecTime4E1EMMap","AveXtalRtOOTStcRecTime4E1 Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcRecTime4E1MapEM->Sumw2();

  fOutAveXtalRtOOTStcRecTimeE2MapEB = new TH2F("AveXtalRtOOTStcRecTimeE2EBMap","AveXtalRtOOTStcRecTimeE2 Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalRtOOTStcRecTimeE2MapEB->Sumw2();
  fOutAveXtalRtOOTStcRecTimeE2MapEP = new TH2F("AveXtalRtOOTStcRecTimeE2EPMap","AveXtalRtOOTStcRecTimeE2 Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcRecTimeE2MapEP->Sumw2();
  fOutAveXtalRtOOTStcRecTimeE2MapEM = new TH2F("AveXtalRtOOTStcRecTimeE2EMMap","AveXtalRtOOTStcRecTimeE2 Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcRecTimeE2MapEM->Sumw2();

  fOutAveXtalRtOOTStcRecTimeE5MapEB = new TH2F("AveXtalRtOOTStcRecTimeE5EBMap","AveXtalRtOOTStcRecTimeE5 Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalRtOOTStcRecTimeE5MapEB->Sumw2();
  fOutAveXtalRtOOTStcRecTimeE5MapEP = new TH2F("AveXtalRtOOTStcRecTimeE5EPMap","AveXtalRtOOTStcRecTimeE5 Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcRecTimeE5MapEP->Sumw2();
  fOutAveXtalRtOOTStcRecTimeE5MapEM = new TH2F("AveXtalRtOOTStcRecTimeE5EMMap","AveXtalRtOOTStcRecTimeE5 Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcRecTimeE5MapEM->Sumw2();

  fOutAveXtalRtStcRecTimeE5MapEB = new TH2F("AveXtalRtStcRecTimeE5EBMap","AveXtalRtStcRecTimeE5 Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalRtStcRecTimeE5MapEB->Sumw2();
  fOutAveXtalRtStcRecTimeE5MapEP = new TH2F("AveXtalRtStcRecTimeE5EPMap","AveXtalRtStcRecTimeE5 Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtStcRecTimeE5MapEP->Sumw2();
  fOutAveXtalRtStcRecTimeE5MapEM = new TH2F("AveXtalRtStcRecTimeE5EMMap","AveXtalRtStcRecTimeE5 Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtStcRecTimeE5MapEM->Sumw2();

  fOutAveXtalWtOOTStcRecTimeE5MapEB = new TH2F("AveXtalWtOOTStcRecTimeE5EBMap","AveXtalWtOOTStcRecTimeE5 Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalWtOOTStcRecTimeE5MapEB->Sumw2();
  fOutAveXtalWtOOTStcRecTimeE5MapEP = new TH2F("AveXtalWtOOTStcRecTimeE5EPMap","AveXtalWtOOTStcRecTimeE5 Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalWtOOTStcRecTimeE5MapEP->Sumw2();
  fOutAveXtalWtOOTStcRecTimeE5MapEM = new TH2F("AveXtalWtOOTStcRecTimeE5EMMap","AveXtalWtOOTStcRecTimeE5 Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalWtOOTStcRecTimeE5MapEM->Sumw2();

  fOutAveXtalRtOOTStcRecTime2E5MapEB = new TH2F("AveXtalRtOOTStcRecTime2E5EBMap","AveXtalRtOOTStcRecTime2E5 Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalRtOOTStcRecTime2E5MapEB->Sumw2();
  fOutAveXtalRtOOTStcRecTime2E5MapEP = new TH2F("AveXtalRtOOTStcRecTime2E5EPMap","AveXtalRtOOTStcRecTime2E5 Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcRecTime2E5MapEP->Sumw2();
  fOutAveXtalRtOOTStcRecTime2E5MapEM = new TH2F("AveXtalRtOOTStcRecTime2E5EMMap","AveXtalRtOOTStcRecTime2E5 Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcRecTime2E5MapEM->Sumw2();
  fOutAveXtalRtOOTStcRecTime4E5MapEB = new TH2F("AveXtalRtOOTStcRecTime4E5EBMap","AveXtalRtOOTStcRecTime4E5 Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalRtOOTStcRecTime4E5MapEB->Sumw2();
  fOutAveXtalRtOOTStcRecTime4E5MapEP = new TH2F("AveXtalRtOOTStcRecTime4E5EPMap","AveXtalRtOOTStcRecTime4E5 Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcRecTime4E5MapEP->Sumw2();
  fOutAveXtalRtOOTStcRecTime4E5MapEM = new TH2F("AveXtalRtOOTStcRecTime4E5EMMap","AveXtalRtOOTStcRecTime4E5 Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcRecTime4E5MapEM->Sumw2();

  fOutAveXtalRtOOTStcRecTimeE10MapEB = new TH2F("AveXtalRtOOTStcRecTimeE10EBMap","AveXtalRtOOTStcRecTimeE10 Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalRtOOTStcRecTimeE10MapEB->Sumw2();
  fOutAveXtalRtOOTStcRecTimeE10MapEP = new TH2F("AveXtalRtOOTStcRecTimeE10EPMap","AveXtalRtOOTStcRecTimeE10 Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcRecTimeE10MapEP->Sumw2();
  fOutAveXtalRtOOTStcRecTimeE10MapEM = new TH2F("AveXtalRtOOTStcRecTimeE10EMMap","AveXtalRtOOTStcRecTimeE10 Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcRecTimeE10MapEM->Sumw2();

  fOutAveXtalOccMapEB = new TH2F("AveXtalOccEBMap","AveXtalOcc Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalOccMapEB->Sumw2();
  fOutAveXtalOccMapEP = new TH2F("AveXtalOccEPMap","AveXtalOcc Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalOccMapEP->Sumw2();
  fOutAveXtalOccMapEM = new TH2F("AveXtalOccEMMap","AveXtalOcc Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalOccMapEM->Sumw2();
 
  fOutAveXtalPhoRecTimeMapEB = new TH2F("AveXtalPhoRecTimeEBMap","AveXtalPhoRecTime Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalPhoRecTimeMapEB->Sumw2();
  fOutAveXtalPhoRecTimeMapEP = new TH2F("AveXtalPhoRecTimeEPMap","AveXtalPhoRecTime Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalPhoRecTimeMapEP->Sumw2();
  fOutAveXtalPhoRecTimeMapEM = new TH2F("AveXtalPhoRecTimeEMMap","AveXtalPhoRecTime Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalPhoRecTimeMapEM->Sumw2();

  fOutAveXtalRtPhoRecTimeMapEB = new TH2F("AveXtalRtPhoRecTimeEBMap","AveXtalRtPhoRecTime Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalRtPhoRecTimeMapEB->Sumw2();
  fOutAveXtalRtPhoRecTimeMapEP = new TH2F("AveXtalRtPhoRecTimeEPMap","AveXtalRtPhoRecTime Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtPhoRecTimeMapEP->Sumw2();
  fOutAveXtalRtPhoRecTimeMapEM = new TH2F("AveXtalRtPhoRecTimeEMMap","AveXtalRtPhoRecTime Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtPhoRecTimeMapEM->Sumw2();

  fOutAveXtalRtStcPhoRecTimeMapEB = new TH2F("AveXtalRtStcPhoRecTimeEBMap","AveXtalRtStcPhoRecTime Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalRtStcPhoRecTimeMapEB->Sumw2();
  fOutAveXtalRtStcPhoRecTimeMapEP = new TH2F("AveXtalRtStcPhoRecTimeEPMap","AveXtalRtStcPhoRecTime Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtStcPhoRecTimeMapEP->Sumw2();
  fOutAveXtalRtStcPhoRecTimeMapEM = new TH2F("AveXtalRtStcPhoRecTimeEMMap","AveXtalRtStcPhoRecTime Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtStcPhoRecTimeMapEM->Sumw2();

  fOutAveXtalRtDifStcPhoRecTimeMapEB = new TH2F("AveXtalRtDifStcPhoRecTimeEBMap","AveXtalRtDifStcPhoRecTime Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalRtDifStcPhoRecTimeMapEB->Sumw2();
  fOutAveXtalRtDifStcPhoRecTimeMapEP = new TH2F("AveXtalRtDifStcPhoRecTimeEPMap","AveXtalRtDifStcPhoRecTime Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtDifStcPhoRecTimeMapEP->Sumw2();
  fOutAveXtalRtDifStcPhoRecTimeMapEM = new TH2F("AveXtalRtDifStcPhoRecTimeEMMap","AveXtalRtDifStcPhoRecTime Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtDifStcPhoRecTimeMapEM->Sumw2();

  //fOutAveXtalRtOOTPhoRecTimeMapEB = new TH2F("AveXtalRtOOTPhoRecTimeEBMap","AveXtalRtOOTPhoRecTime Map EB",171,-85.5,85.5,360,0.5,360.5);
  //fOutAveXtalRtOOTPhoRecTimeMapEB->Sumw2();
  //fOutAveXtalRtOOTPhoRecTimeMapEP = new TH2F("AveXtalRtOOTPhoRecTimeEPMap","AveXtalRtOOTPhoRecTime Map EP",100,0.5,100.5,100,0.5,100.5);
  //fOutAveXtalRtOOTPhoRecTimeMapEP->Sumw2();
  //fOutAveXtalRtOOTPhoRecTimeMapEM = new TH2F("AveXtalRtOOTPhoRecTimeEMMap","AveXtalRtOOTPhoRecTime Map EM",100,0.5,100.5,100,0.5,100.5);
  //fOutAveXtalRtOOTPhoRecTimeMapEM->Sumw2();

  fOutAveXtalRtOOTStcPhoRecTimeMapEB = new TH2F("AveXtalRtOOTStcPhoRecTimeEBMap","AveXtalRtOOTStcPhoRecTime Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalRtOOTStcPhoRecTimeMapEB->Sumw2();
  fOutAveXtalRtOOTStcPhoRecTimeMapEP = new TH2F("AveXtalRtOOTStcPhoRecTimeEPMap","AveXtalRtOOTStcPhoRecTime Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcPhoRecTimeMapEP->Sumw2();
  fOutAveXtalRtOOTStcPhoRecTimeMapEM = new TH2F("AveXtalRtOOTStcPhoRecTimeEMMap","AveXtalRtOOTStcPhoRecTime Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcPhoRecTimeMapEM->Sumw2();



  fOutAveXtalPhoOccMapEB = new TH2F("AveXtalPhoOccEBMap","AveXtalPhoOcc Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalPhoOccMapEB->Sumw2();
  fOutAveXtalPhoOccMapEP = new TH2F("AveXtalPhoOccEPMap","AveXtalPhoOcc Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalPhoOccMapEP->Sumw2();
  fOutAveXtalPhoOccMapEM = new TH2F("AveXtalPhoOccEMMap","AveXtalPhoOcc Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalPhoOccMapEM->Sumw2();

  fOutDifXtalPhoRecTimeMapEB = new TH2F("DifXtalPhoRecTimeEBMap","DifXtalPhoRecTime Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutDifXtalPhoRecTimeMapEB->Sumw2();
  fOutDifXtalPhoRecTimeMapEP = new TH2F("DifXtalPhoRecTimeEPMap","DifXtalPhoRecTime Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutDifXtalPhoRecTimeMapEP->Sumw2();
  fOutDifXtalPhoRecTimeMapEM = new TH2F("DifXtalPhoRecTimeEMMap","DifXtalPhoRecTime Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutDifXtalPhoRecTimeMapEM->Sumw2();

  fOutDifXtalRtPhoRecTimeMapEB = new TH2F("DifXtalRtPhoRecTimeEBMap","DifXtalRtPhoRecTime Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutDifXtalRtPhoRecTimeMapEB->Sumw2();
  fOutDifXtalRtPhoRecTimeMapEP = new TH2F("DifXtalRtPhoRecTimeEPMap","DifXtalRtPhoRecTime Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutDifXtalRtPhoRecTimeMapEP->Sumw2();
  fOutDifXtalRtPhoRecTimeMapEM = new TH2F("DifXtalRtPhoRecTimeEMMap","DifXtalRtPhoRecTime Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutDifXtalRtPhoRecTimeMapEM->Sumw2();

  fOutDifXtalRtStcPhoRecTimeMapEB = new TH2F("DifXtalRtStcPhoRecTimeEBMap","DifXtalRtStcPhoRecTime Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutDifXtalRtStcPhoRecTimeMapEB->Sumw2();
  fOutDifXtalRtStcPhoRecTimeMapEP = new TH2F("DifXtalRtStcPhoRecTimeEPMap","DifXtalRtStcPhoRecTime Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutDifXtalRtStcPhoRecTimeMapEP->Sumw2();
  fOutDifXtalRtStcPhoRecTimeMapEM = new TH2F("DifXtalRtStcPhoRecTimeEMMap","DifXtalRtStcPhoRecTime Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutDifXtalRtStcPhoRecTimeMapEM->Sumw2();

  //fOutDifXtalRtOOTPhoRecTimeMapEB = new TH2F("DifXtalRtOOTPhoRecTimeEBMap","DifXtalRtOOTPhoRecTime Map EB",171,-85.5,85.5,360,0.5,360.5);
  //fOutDifXtalRtOOTPhoRecTimeMapEB->Sumw2();
  //fOutDifXtalRtOOTPhoRecTimeMapEP = new TH2F("DifXtalRtOOTPhoRecTimeEPMap","DifXtalRtOOTPhoRecTime Map EP",100,0.5,100.5,100,0.5,100.5);
  //fOutDifXtalRtOOTPhoRecTimeMapEP->Sumw2();
  //fOutDifXtalRtOOTPhoRecTimeMapEM = new TH2F("DifXtalRtOOTPhoRecTimeEMMap","DifXtalRtOOTPhoRecTime Map EM",100,0.5,100.5,100,0.5,100.5);
  //fOutDifXtalRtOOTPhoRecTimeMapEM->Sumw2();

  fOutDifXtalRtOOTStcPhoRecTimeMapEB = new TH2F("DifXtalRtOOTStcPhoRecTimeEBMap","DifXtalRtOOTStcPhoRecTime Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutDifXtalRtOOTStcPhoRecTimeMapEB->Sumw2();
  fOutDifXtalRtOOTStcPhoRecTimeMapEP = new TH2F("DifXtalRtOOTStcPhoRecTimeEPMap","DifXtalRtOOTStcPhoRecTime Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutDifXtalRtOOTStcPhoRecTimeMapEP->Sumw2();
  fOutDifXtalRtOOTStcPhoRecTimeMapEM = new TH2F("DifXtalRtOOTStcPhoRecTimeEMMap","DifXtalRtOOTStcPhoRecTime Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutDifXtalRtOOTStcPhoRecTimeMapEM->Sumw2();

 //std::cout << "Ssetting up for fOutAveXtalRtOOTStcPhoClRecTimeMap skim" << std::endl;

  fOutAveXtalRtOOTStcPhoClRecTimeMapEB = new TH2F("AveXtalRtOOTStcPhoClRecTimeEBMap","AveXtalRtOOTStcPhoClRecTime Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalRtOOTStcPhoClRecTimeMapEB->Sumw2();
  fOutAveXtalRtOOTStcPhoClRecTimeMapEP = new TH2F("AveXtalRtOOTStcPhoClRecTimeEPMap","AveXtalRtOOTStcPhoClRecTime Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcPhoClRecTimeMapEP->Sumw2();
  fOutAveXtalRtOOTStcPhoClRecTimeMapEM = new TH2F("AveXtalRtOOTStcPhoClRecTimeEMMap","AveXtalRtOOTStcPhoClRecTime Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcPhoClRecTimeMapEM->Sumw2();

 //std::cout << "Ssetting up for fOutAveXtalRtStcPhoClRecTimeMap skim" << std::endl;

  fOutAveXtalRtStcPhoClRecTimeMapEB = new TH2F("AveXtalRtStcPhoClRecTimeEBMap","AveXtalRtStcPhoClRecTime Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalRtStcPhoClRecTimeMapEB->Sumw2();
  fOutAveXtalRtStcPhoClRecTimeMapEP = new TH2F("AveXtalRtStcPhoClRecTimeEPMap","AveXtalRtStcPhoClRecTime Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtStcPhoClRecTimeMapEP->Sumw2();
  fOutAveXtalRtStcPhoClRecTimeMapEM = new TH2F("AveXtalRtStcPhoClRecTimeEMMap","AveXtalRtStcPhoClRecTime Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtStcPhoClRecTimeMapEM->Sumw2();

 //std::cout << "Ssetting up for fOutAveXtalWtOOTStcPhoClRecTimeMap skim" << std::endl;

  fOutAveXtalWtOOTStcPhoClRecTimeMapEB = new TH2F("AveXtalWtOOTStcPhoClRecTimeEBMap","AveXtalWtOOTStcPhoClRecTime Map EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalWtOOTStcPhoClRecTimeMapEB->Sumw2();
  fOutAveXtalWtOOTStcPhoClRecTimeMapEP = new TH2F("AveXtalWtOOTStcPhoClRecTimeEPMap","AveXtalWtOOTStcPhoClRecTime Map EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalWtOOTStcPhoClRecTimeMapEP->Sumw2();
  fOutAveXtalWtOOTStcPhoClRecTimeMapEM = new TH2F("AveXtalWtOOTStcPhoClRecTimeEMMap","AveXtalWtOOTStcPhoClRecTime Map EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalWtOOTStcPhoClRecTimeMapEM->Sumw2();

 //std::cout << "Ssetting up for fOutAveXtalRtOOTStcPhoIcRecTimeMap  skim" << std::endl;

  fOutAveXtalRtOOTStcPhoIcRecTimeMapEB = new TH2F("AveXtalRtOOTStcPhoIcRecTimeEBMap","AveXtalRtOOTStcPhoIcRecTimeMap EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalRtOOTStcPhoIcRecTimeMapEB->Sumw2();
  fOutAveXtalRtOOTStcPhoIcRecTimeMapEP = new TH2F("AveXtalRtOOTStcPhoIcRecTimeEPMap","AveXtalRtOOTStcPhoIcRecTimeMap EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcPhoIcRecTimeMapEP->Sumw2();
  fOutAveXtalRtOOTStcPhoIcRecTimeMapEM = new TH2F("AveXtalRtOOTStcPhoIcRecTimeEMMap","AveXtalRtOOTStcPhoIcRecTimeMap EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtOOTStcPhoIcRecTimeMapEM->Sumw2();

 //std::cout << "Ssetting up for fOutAveXtalRtStcPhoIcRecTimeMap skim" << std::endl;

  fOutAveXtalRtStcPhoIcRecTimeMapEB = new TH2F("AveXtalRtStcPhoIcRecTimeEBMap","AveXtalRtStcPhoIcRecTimeMap EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalRtStcPhoIcRecTimeMapEB->Sumw2();
  fOutAveXtalRtStcPhoIcRecTimeMapEP = new TH2F("AveXtalRtStcPhoIcRecTimeEPMap","AveXtalRtStcPhoIcRecTimeMap EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtStcPhoIcRecTimeMapEP->Sumw2();
  fOutAveXtalRtStcPhoIcRecTimeMapEM = new TH2F("AveXtalRtStcPhoIcRecTimeEMMap","AveXtalRtStcPhoIcRecTimeMap EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalRtStcPhoIcRecTimeMapEM->Sumw2();

 //std::cout << "Ssetting up for fOutAveXtalWtOOTStcPhoIcRecTimeMap skim" << std::endl;

  fOutAveXtalWtOOTStcPhoIcRecTimeMapEB = new TH2F("AveXtalWtOOTStcPhoIcRecTimeEBMap","AveXtalWtOOTStcPhoIcRecTimeMap EB",171,-85.5,85.5,360,0.5,360.5);
  fOutAveXtalWtOOTStcPhoIcRecTimeMapEB->Sumw2();
  fOutAveXtalWtOOTStcPhoIcRecTimeMapEP = new TH2F("AveXtalWtOOTStcPhoIcRecTimeEPMap","AveXtalWtOOTStcPhoIcRecTimeMap EP",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalWtOOTStcPhoIcRecTimeMapEP->Sumw2();
  fOutAveXtalWtOOTStcPhoIcRecTimeMapEM = new TH2F("AveXtalWtOOTStcPhoIcRecTimeEMMap","AveXtalWtOOTStcPhoIcRecTimeMap EM",100,0.5,100.5,100,0.5,100.5);
  fOutAveXtalWtOOTStcPhoIcRecTimeMapEM->Sumw2();

 //std::cout << "Finished setting up for skim" << std::endl;
}

Skimmer::~Skimmer()
{
  fPUWeights.clear();
  if (fIsMC)
  {
    delete fInPUWgtHist;
    delete fInPUWgtFile;
  }

  //  delete fInCutFlowWgt;
  delete fInCutFlow;
  delete fInTree;
  delete fInConfigTree;
  delete fInFile;

  delete fOutCutFlowScl;
  delete fOutCutFlowWgt;
  delete fOutCutFlow;

  delete tofHist;
  delete fOutAveXtalRecTimeHist;
  delete fOutAveXtalRtRecTimeHist;
  delete fOutAveXtalRtStcRecTimeHist;
  //delete fOutAveXtalRtOOTRecTimeHist;
  delete fOutAveXtalOccHist;
  delete fOutAveXtalRecTimeHistEB;
  delete fOutAveXtalRecTimeHistEP;
  delete fOutAveXtalRecTimeHistEM;
  delete fOutAveXtalRtRecTimeHistEB;
  delete fOutAveXtalRtRecTimeHistEP;
  delete fOutAveXtalRtRecTimeHistEM;
  delete fOutAveXtalRtStcRecTimeHistEB;
  delete fOutAveXtalRtStcRecTimeHistEP;
  delete fOutAveXtalRtStcRecTimeHistEM;
  //delete fOutAveXtalRtOOTRecTimeHistEB;
  //delete fOutAveXtalRtOOTRecTimeHistEP;
  //delete fOutAveXtalRtOOTRecTimeHistEM;
  delete fOutAveXtalRtOOTStcRecTimeHistEB;
  delete fOutAveXtalRtOOTStcRecTimeHistEP;
  delete fOutAveXtalRtOOTStcRecTimeHistEM;
  delete fOutAveXtalRtOOTStcRecTimeE0HistEB;
  delete fOutAveXtalRtOOTStcRecTimeE0HistEP;
  delete fOutAveXtalRtOOTStcRecTimeE0HistEM;
  delete fOutAveXtalRtOOTStcRecTimeE1HistEB;
  delete fOutAveXtalRtOOTStcRecTimeE1HistEP;
  delete fOutAveXtalRtOOTStcRecTimeE1HistEM;
  delete fOutAveXtalRtOOTStcRecTime2E1HistEB;
  delete fOutAveXtalRtOOTStcRecTime2E1HistEP;
  delete fOutAveXtalRtOOTStcRecTime2E1HistEM;
  delete fOutAveXtalRtOOTStcRecTime4E1HistEB;
  delete fOutAveXtalRtOOTStcRecTime4E1HistEP;
  delete fOutAveXtalRtOOTStcRecTime4E1HistEM;
  delete fOutAveXtalRtOOTStcRecTimeE2HistEB;
  delete fOutAveXtalRtOOTStcRecTimeE2HistEP;
  delete fOutAveXtalRtOOTStcRecTimeE2HistEM;
  delete fOutAveXtalRtOOTStcRecTimeE5HistEB;
  delete fOutAveXtalRtOOTStcRecTimeE5HistEP;
  delete fOutAveXtalRtOOTStcRecTimeE5HistEM;
  delete fOutAveXtalRtOOTStcRecTime2E5HistEB;
  delete fOutAveXtalRtOOTStcRecTime2E5HistEP;
  delete fOutAveXtalRtOOTStcRecTime2E5HistEM;  
  delete fOutAveXtalRtOOTStcRecTime4E5HistEB;
  delete fOutAveXtalRtOOTStcRecTime4E5HistEP;
  delete fOutAveXtalRtOOTStcRecTime4E5HistEM;
  delete fOutAveXtalRtOOTStcRecTimeE10HistEB;
  delete fOutAveXtalRtOOTStcRecTimeE10HistEP;
  delete fOutAveXtalRtOOTStcRecTimeE10HistEM;
  delete fOutAveXtalOccHistEB;
  delete fOutAveXtalOccHistEP;
  delete fOutAveXtalOccHistEM;
  delete fOutAveXtalRecTimeMapEB;
  delete fOutAveXtalRecTimeMapEP;
  delete fOutAveXtalRecTimeMapEM;
  delete fOutAveXtalRtRecTimeMapEB;
  delete fOutAveXtalRtRecTimeMapEP;
  delete fOutAveXtalRtRecTimeMapEM;
  delete fOutAveXtalRtStcRecTimeMapEB;
  delete fOutAveXtalRtStcRecTimeMapEP;
  delete fOutAveXtalRtStcRecTimeMapEM;
  //delete fOutAveXtalRtOOTRecTimeMapEB;
  //delete fOutAveXtalRtOOTRecTimeMapEP;
  //delete fOutAveXtalRtOOTRecTimeMapEM;
  delete fOutAveXtalRtOOTStcRecTimeMapEB;
  delete fOutAveXtalRtOOTStcRecTimeMapEP;
  delete fOutAveXtalRtOOTStcRecTimeMapEM;
  delete fOutAveXtalRtOOTStcRecTimeE0MapEB;
  delete fOutAveXtalRtOOTStcRecTimeE0MapEP;
  delete fOutAveXtalRtOOTStcRecTimeE0MapEM;
  delete fOutAveXtalRtOOTStcRecTimeE1MapEB;
  delete fOutAveXtalRtOOTStcRecTimeE1MapEP;
  delete fOutAveXtalRtOOTStcRecTimeE1MapEM;
  delete fOutAveXtalRtOOTStcRecTime2E1MapEB;
  delete fOutAveXtalRtOOTStcRecTime2E1MapEP;
  delete fOutAveXtalRtOOTStcRecTime2E1MapEM;
  delete fOutAveXtalRtOOTStcRecTime4E1MapEB;
  delete fOutAveXtalRtOOTStcRecTime4E1MapEP;
  delete fOutAveXtalRtOOTStcRecTime4E1MapEM;
  delete fOutAveXtalRtOOTStcRecTimeE2MapEB;
  delete fOutAveXtalRtOOTStcRecTimeE2MapEP;
  delete fOutAveXtalRtOOTStcRecTimeE2MapEM;
  delete fOutAveXtalRtOOTStcRecTimeE5MapEB;
  delete fOutAveXtalRtOOTStcRecTimeE5MapEP;
  delete fOutAveXtalRtOOTStcRecTimeE5MapEM;

  delete fOutAveXtalRtStcRecTimeE5MapEB;
  delete fOutAveXtalRtStcRecTimeE5MapEP;
  delete fOutAveXtalRtStcRecTimeE5MapEM;
  delete fOutAveXtalWtOOTStcRecTimeE5MapEB;
  delete fOutAveXtalWtOOTStcRecTimeE5MapEP;
  delete fOutAveXtalWtOOTStcRecTimeE5MapEM;

  delete fOutAveXtalRtOOTStcRecTime2E5MapEB;
  delete fOutAveXtalRtOOTStcRecTime2E5MapEP;
  delete fOutAveXtalRtOOTStcRecTime2E5MapEM;
  delete fOutAveXtalRtOOTStcRecTime4E5MapEB;
  delete fOutAveXtalRtOOTStcRecTime4E5MapEP;
  delete fOutAveXtalRtOOTStcRecTime4E5MapEM;
  delete fOutAveXtalRtOOTStcRecTimeE10MapEB;
  delete fOutAveXtalRtOOTStcRecTimeE10MapEP;
  delete fOutAveXtalRtOOTStcRecTimeE10MapEM;
  delete fOutAveXtalOccMapEB;
  delete fOutAveXtalOccMapEP;
  delete fOutAveXtalOccMapEM;
 
  delete fOutAveXtalPhoRecTimeHist;
  delete fOutAveXtalRtPhoRecTimeHist;
  delete fOutAveXtalRtStcPhoRecTimeHist;
  //delete fOutAveXtalRtOOTPhoRecTimeHist;
  delete fOutAveXtalRtOOTStcPhoRecTimeHist;
  delete fOutAveXtalPhoOccHist;
  delete fOutAveXtalPhoRecTimeHistEB;
  delete fOutAveXtalPhoRecTimeHistEP;
  delete fOutAveXtalPhoRecTimeHistEM;
  delete fOutAveXtalRtPhoRecTimeHistEB;
  delete fOutAveXtalRtPhoRecTimeHistEP;
  delete fOutAveXtalRtPhoRecTimeHistEM;
  delete fOutAveXtalRtStcPhoRecTimeHistEB;
  delete fOutAveXtalRtStcPhoRecTimeHistEP;
  delete fOutAveXtalRtStcPhoRecTimeHistEM;
  //delete fOutAveXtalRtOOTPhoRecTimeHistEB;
  //delete fOutAveXtalRtOOTPhoRecTimeHistEP;
  //delete fOutAveXtalRtOOTPhoRecTimeHistEM;
  delete fOutAveXtalRtOOTStcPhoRecTimeHistEB;
  delete fOutAveXtalRtOOTStcPhoRecTimeHistEP;
  delete fOutAveXtalRtOOTStcPhoRecTimeHistEM;
  delete fOutAveXtalPhoOccHistEB;
  delete fOutAveXtalPhoOccHistEP;
  delete fOutAveXtalPhoOccHistEM;
  delete fOutAveXtalPhoRecTimeMapEB;
  delete fOutAveXtalPhoRecTimeMapEP;
  delete fOutAveXtalPhoRecTimeMapEM;
  delete fOutAveXtalRtPhoRecTimeMapEB;
  delete fOutAveXtalRtPhoRecTimeMapEP;
  delete fOutAveXtalRtPhoRecTimeMapEM;
  delete fOutAveXtalRtStcPhoRecTimeMapEB;
  delete fOutAveXtalRtStcPhoRecTimeMapEP;
  delete fOutAveXtalRtStcPhoRecTimeMapEM;
  //delete fOutAveXtalRtOOTPhoRecTimeMapEB;
  //delete fOutAveXtalRtOOTPhoRecTimeMapEP;
  //delete fOutAveXtalRtOOTPhoRecTimeMapEM;
  delete fOutAveXtalRtOOTStcPhoRecTimeMapEB;
  delete fOutAveXtalRtOOTStcPhoRecTimeMapEP;
  delete fOutAveXtalRtOOTStcPhoRecTimeMapEM;
  delete fOutAveXtalPhoOccMapEB;
  delete fOutAveXtalPhoOccMapEP;
  delete fOutAveXtalPhoOccMapEM;

  delete fOutAveXtalRtOOTStcPhoClRecTimeHistEB;
  delete fOutAveXtalRtOOTStcPhoClRecTimeHistEP;
  delete fOutAveXtalRtOOTStcPhoClRecTimeHistEM;

  delete fOutAveXtalRtOOTStcPhoIcRecTimeHistEB;
  delete fOutAveXtalRtOOTStcPhoIcRecTimeHistEP;
  delete fOutAveXtalRtOOTStcPhoIcRecTimeHistEM;

  delete fOutAveXtalRtOOTStcPhoClRecTimeMapEB;
  delete fOutAveXtalRtOOTStcPhoClRecTimeMapEP;
  delete fOutAveXtalRtOOTStcPhoClRecTimeMapEM;

  delete fOutAveXtalRtOOTStcPhoIcRecTimeMapEB;
  delete fOutAveXtalRtOOTStcPhoIcRecTimeMapEP;
  delete fOutAveXtalRtOOTStcPhoIcRecTimeMapEM;

  delete fOutAveXtalRtStcPhoClRecTimeMapEB;
  delete fOutAveXtalRtStcPhoClRecTimeMapEP;
  delete fOutAveXtalRtStcPhoClRecTimeMapEM;

  delete fOutAveXtalRtStcPhoIcRecTimeMapEB;
  delete fOutAveXtalRtStcPhoIcRecTimeMapEP;
  delete fOutAveXtalRtStcPhoIcRecTimeMapEM;

  delete fOutAveXtalWtOOTStcPhoClRecTimeMapEB;
  delete fOutAveXtalWtOOTStcPhoClRecTimeMapEP;
  delete fOutAveXtalWtOOTStcPhoClRecTimeMapEM;

  delete fOutAveXtalWtOOTStcPhoIcRecTimeMapEB;
  delete fOutAveXtalWtOOTStcPhoIcRecTimeMapEP;
  delete fOutAveXtalWtOOTStcPhoIcRecTimeMapEM;

  delete fOutDifXtalRtPhoRecTimeHist;
  delete fOutDifXtalRtPhoRecTimeHistEB;
  delete fOutDifXtalRtPhoRecTimeHistEP;
  delete fOutDifXtalRtPhoRecTimeHistEM;
  delete fOutDifXtalRtPhoRecTimeMapEB;
  delete fOutDifXtalRtPhoRecTimeMapEP;
  delete fOutDifXtalRtPhoRecTimeMapEM;
  delete fOutDifXtalRtStcPhoRecTimeHist;
  delete fOutDifXtalRtStcPhoRecTimeHistEB;
  delete fOutDifXtalRtStcPhoRecTimeHistEP;
  delete fOutDifXtalRtStcPhoRecTimeHistEM;
  delete fOutDifXtalRtStcPhoRecTimeMapEB;
  delete fOutDifXtalRtStcPhoRecTimeMapEP;
  delete fOutDifXtalRtStcPhoRecTimeMapEM;
  //delete fOutDifXtalRtOOTPhoRecTimeHist;
  //delete fOutDifXtalRtOOTPhoRecTimeHistEB;
  //delete fOutDifXtalRtOOTPhoRecTimeHistEP;
  //delete fOutDifXtalRtOOTPhoRecTimeHistEM;
  //delete fOutDifXtalRtOOTPhoRecTimeMapEB;
  //delete fOutDifXtalRtOOTPhoRecTimeMapEP;
  //delete fOutDifXtalRtOOTPhoRecTimeMapEM;
  delete fOutDifXtalRtOOTStcPhoRecTimeHist;
  delete fOutDifXtalRtOOTStcPhoRecTimeHistEB;
  delete fOutDifXtalRtOOTStcPhoRecTimeHistEP;
  delete fOutDifXtalRtOOTStcPhoRecTimeHistEM;
  delete fOutDifXtalRtOOTStcPhoRecTimeMapEB;
  delete fOutDifXtalRtOOTStcPhoRecTimeMapEP;
  delete fOutDifXtalRtOOTStcPhoRecTimeMapEM;
  delete fOutDifXtalPhoRecTimeHist;
  delete fOutDifXtalPhoRecTimeHistEB;
  delete fOutDifXtalPhoRecTimeHistEP;
  delete fOutDifXtalPhoRecTimeHistEM;
  delete fOutDifXtalPhoRecTimeMapEB;
  delete fOutDifXtalPhoRecTimeMapEP;
  delete fOutDifXtalPhoRecTimeMapEM;

  delete fOutTree;
  delete fOutConfigTree;
  delete fOutFile;
}

void Skimmer::EventLoop()
{
  // do loop over events, reading in branches as needed, skimming, filling output trees and hists
  const auto nEntries = fInTree->GetEntries();
  float minRecE0 = 0.5;
  float minRecE1 = 1.f;
  float minRecE2 = 2.f;
  float minRecE5 = 5.f;
  float minRecE10 = 10.f;
  bool useTOF = true;
  //bool useTOF = false;
  //const auto nEntries = 100;
  for (auto entry = 0U; entry < nEntries; entry++)
  {
    // dump status check
    if (entry%Common::nEvCheck == 0 || entry == 0) //std::cout << "Processing Entry: " << entry << " out of " << nEntries << std::endl;
    //if( entry > 100 ) break;
    // get event weight: no scaling by BR, xsec, lumi, etc.
    if (fIsMC) fInEvent.b_genwgt->GetEntry(entry);
    const auto wgt    = (fIsMC ? fInEvent.genwgt : 1.f);
    const auto evtwgt = fSampleWeight * wgt; // sample weight for data == 1

    // always fill to ensure no data was lost
    fOutCutFlow   ->Fill((cutLabels["PreSkim"]*1.f)-0.5f);
    fOutCutFlowWgt->Fill((cutLabels["PreSkim"]*1.f)-0.5f,wgt);
    fOutCutFlowScl->Fill((cutLabels["PreSkim"]*1.f)-0.5f,evtwgt);

    //sumXtalRecTime.clear();
    //numXtalRecTime.clear();

    // get rechits
    fInRecHits.b_E->GetEntry(entry);
    fInRecHits.b_ID->GetEntry(entry);
    fInRecHits.b_time->GetEntry(entry);
    fInRecHits.b_TOF->GetEntry(entry);
    b_kurhID->GetEntry(entry);
    b_kurhtime->GetEntry(entry);
    if( hasMultiKURecHit ){
	b_kuStcrhtime->GetEntry(entry);
        //b_kuNotrhtime->GetEntry(entry);
        b_kuNotStcrhtime->GetEntry(entry);
        b_kuWootStcrhtime->GetEntry(entry);
    }
   //std::cout << "Pulling RecHits done "<< std::endl;

//    gZmass = 0.f;
//    gdR = 0.f;
    for( UInt_t idx = 0; idx < (*fInRecHits.ID).size(); idx++ ){
//       //std::cout << "Processing RecHit: " << idx << std::endl;
        const auto id_i = (*fInRecHits.ID)[idx];
        const auto t_i = (*fInRecHits.time)[idx];
        const auto e_i = (*fInRecHits.E)[idx];
        const auto tof_i = (*fInRecHits.TOF)[idx];
        auto RtStc_t_i = 0.f;
        auto RtOOTStc_t_i = 0.f;
        auto WtOOTStc_t_i = 0.f;
	auto t_tof = t_i;
	tofHist->Fill(tof_i);
	//if( e_i >= minRecE ){
//	//std::cout << "With: id_i: " << id_i << " time: " << t_i << " energy: " << e_i << " tof: " << tof_i << " and " << RtOOTStc_t_i << std::endl;
               sumXtalRecTime[id_i] += t_tof;
               numXtalRecTime[id_i] += 1;
	       if( hasMultiKURecHit ){
                  for(UInt_t kuseed = 0; kuseed < (*kurhID).size(); kuseed++ ){
                  	if( (*kurhID)[kuseed] == id_i ){ 
				RtStc_t_i = (*kuStcrhtime)[kuseed];
                                RtOOTStc_t_i = (*kuNotStcrhtime)[kuseed];
                                WtOOTStc_t_i = (*kuWootStcrhtime)[kuseed];
				break;
			}
                  }      
//		 //std::cout << "Filling sumXtalRtOOTStcRecTimes " << std::endl;  
		  if( useTOF ){ 
			RtStc_t_i += tof_i;
                        RtOOTStc_t_i += tof_i;
                        WtOOTStc_t_i += tof_i;
		  }
		  sumXtalRtOOTStcRecTime[id_i] += RtOOTStc_t_i;
		  numXtalRtOOTStcRecTime[id_i] += 1;
		  if( e_i >= minRecE0 ){
		  	sumXtalRtOOTStcRecTimeE0[id_i] += RtOOTStc_t_i;
                  	numXtalRtOOTStcRecTimeE0[id_i] += 1;
		  }
		  if( e_i >= minRecE1 ){
                        sumXtalRtOOTStcRecTimeE1[id_i] += RtOOTStc_t_i;
                        numXtalRtOOTStcRecTimeE1[id_i] += 1;
			if( entry%2 == 0 ){ sumXtalRtOOTStcRecTime2E1[id_i] += RtOOTStc_t_i; numXtalRtOOTStcRecTime2E1[id_i] += 1; }
                        if( entry%4 == 0 ){ sumXtalRtOOTStcRecTime4E1[id_i] += RtOOTStc_t_i; numXtalRtOOTStcRecTime4E1[id_i] += 1; } 
                  }
 		  if(e_i >= minRecE2 ){
                        sumXtalRtOOTStcRecTimeE2[id_i] += RtOOTStc_t_i;
                        numXtalRtOOTStcRecTimeE2[id_i] += 1;
                  }
		  if(e_i >= minRecE5 ){
                        sumXtalRtStcRecTimeE5[id_i] += RtStc_t_i;
                        sumXtalRtOOTStcRecTimeE5[id_i] += RtOOTStc_t_i;
                        sumXtalWtOOTStcRecTimeE5[id_i] += WtOOTStc_t_i;
                        numXtalRtOOTStcRecTimeE5[id_i] += 1;
                        if( entry%2 == 0 ){ sumXtalRtOOTStcRecTime2E5[id_i] += RtOOTStc_t_i; numXtalRtOOTStcRecTime2E5[id_i] += 1; }
                        if( entry%4 == 0 ){ sumXtalRtOOTStcRecTime4E5[id_i] += RtOOTStc_t_i; numXtalRtOOTStcRecTime4E5[id_i] += 1; }
                  }
		  if(e_i >= minRecE10 ){
                        sumXtalRtOOTStcRecTimeE10[id_i] += RtOOTStc_t_i;
                        numXtalRtOOTStcRecTimeE10[id_i] += 1;
                  }
	       }
 	//}
    }
   //std::cout << "Finished Filling RecHitTimes" << std::endl;
    // perform skim: standard
    if (fSkim == SkimType::Standard) // do not apply skim selection on toy config
    {
      // leading photon skim section
     //std::cout << "Starting Standard Skim" << std::endl;
      fInEvent.b_nphotons->GetEntry(entry);
      if (fInEvent.nphotons <= 0) continue;
      fOutCutFlow   ->Fill((cutLabels["nPhotons"]*1.f)-0.5f);
      fOutCutFlowWgt->Fill((cutLabels["nPhotons"]*1.f)-0.5f,wgt);
      fOutCutFlowScl->Fill((cutLabels["nPhotons"]*1.f)-0.5f,evtwgt);
      
      fInPhos.front().b_isEB->GetEntry(entry);
      if (!fInPhos.front().isEB) continue;
      fOutCutFlow   ->Fill((cutLabels["ph0isEB"]*1.f)-0.5f);
      fOutCutFlowWgt->Fill((cutLabels["ph0isEB"]*1.f)-0.5f,wgt);
      fOutCutFlowScl->Fill((cutLabels["ph0isEB"]*1.f)-0.5f,evtwgt);

      fInPhos.front().b_pt->GetEntry(entry);
      if (fInPhos.front().pt < 70.f) continue;
      fOutCutFlow   ->Fill((cutLabels["ph0pt70"]*1.f)-0.5f);
      fOutCutFlowWgt->Fill((cutLabels["ph0pt70"]*1.f)-0.5f,wgt);
      fOutCutFlowScl->Fill((cutLabels["ph0pt70"]*1.f)-0.5f,evtwgt);

      // filter on MET Flags
      fInEvent.b_metPV->GetEntry(entry);
      fInEvent.b_metBeamHalo->GetEntry(entry);
      fInEvent.b_metHBHENoise->GetEntry(entry);
      fInEvent.b_metHBHEisoNoise->GetEntry(entry);
      fInEvent.b_metECALTP->GetEntry(entry);
      fInEvent.b_metPFMuon->GetEntry(entry);
      fInEvent.b_metPFChgHad->GetEntry(entry);
      // fInEvent.b_metECALCalib->GetEntry(entry);
      fInEvent.b_metECALBadCalib->GetEntry(entry);
      if (!fInEvent.metPV || !fInEvent.metBeamHalo || !fInEvent.metHBHENoise || !fInEvent.metHBHEisoNoise || 
	  // !fInEvent.metECALTP || !fInEvent.metPFMuon || !fInEvent.metPFChgHad || !fInEvent.metECALCalib) continue;
       	  !fInEvent.metECALTP || !fInEvent.metPFMuon || !fInEvent.metPFChgHad || !fInEvent.metECALBadCalib) continue;

      fInEvent.b_metEESC->GetEntry(entry);
      if (!fIsMC && !fInEvent.metEESC) continue;
      
      // fill cutflow for MET filters
      fOutCutFlow   ->Fill((cutLabels["METFlag"]*1.f)-0.5f);
      fOutCutFlowWgt->Fill((cutLabels["METFlag"]*1.f)-0.5f,wgt);
      fOutCutFlowScl->Fill((cutLabels["METFlag"]*1.f)-0.5f,evtwgt);

      // fill photon list in standard fashion
      Skimmer::FillPhoListStandard();
    }
    else if (fSkim == SkimType::Zee)
    {
      
      // cut on HLT right away
      //      fInEvent.b_hltDiEle33MW->GetEntry(entry);
      
      //       if (!fInEvent.hltDiEle33MW) continue;
      //fOutCutFlow   ->Fill((cutLabels["diEleHLT"]*1.f)-0.5f);
      //fOutCutFlowWgt->Fill((cutLabels["diEleHLT"]*1.f)-0.5f,wgt);
      //fOutCutFlowScl->Fill((cutLabels["diEleHLT"]*1.f)-0.5f,evtwgt);

      // build list of "good electrons"
      std::vector<Int_t> good_phos;

     //std::cout << "Starting Zee Skim w/ nPhotons " << Common::nPhotons << endl;   
      for (auto ipho = 0; ipho < Common::nPhotons; ipho++)
      {
	auto & inpho = fInPhos[ipho];
	
	// 	inpho.b_pt->GetEntry(entry);
	// 	if (inpho.pt < 40.f) continue;

	inpho.b_hasPixSeed->GetEntry(entry);
	//cout << "has Pix Seed? " << inpho.hasPixSeed << endl;
	if (!inpho.hasPixSeed) continue;   //   <<<<<<<<<<<<<<<<<<<<<<<<<<<<< uncomment  temp fix to run 2018?

	inpho.b_gedID->GetEntry(entry);
//	cout << "gedID " << inpho.gedID << endl;
	if (inpho.gedID < 3) continue; //  <<<<<<<<<<<<<<<<<<<<<<<<<<  change back to inpho.gedID < 3    temp fix ro run 2018

	inpho.b_isOOT->GetEntry(entry);
//	cout << "isOOT " << inpho.isOOT << endl;
	if (inpho.isOOT) continue;

	good_phos.emplace_back(ipho);
      }
      
      // make sure have at least 1 good photon
      if (good_phos.size() < 1) continue;
      fOutCutFlow   ->Fill((cutLabels["goodPho1"]*1.f)-0.5f);
      fOutCutFlowWgt->Fill((cutLabels["goodPho1"]*1.f)-0.5f,wgt);
      fOutCutFlowScl->Fill((cutLabels["goodPho1"]*1.f)-0.5f,evtwgt);

      // make sure have at least 2 good photons
      if (good_phos.size() < 2) continue;
      fOutCutFlow   ->Fill((cutLabels["goodPho2"]*1.f)-0.5f);
      fOutCutFlowWgt->Fill((cutLabels["goodPho2"]*1.f)-0.5f,wgt);
      fOutCutFlowScl->Fill((cutLabels["goodPho2"]*1.f)-0.5f,evtwgt);

      // object for containing mass pairs
      std::vector<MassStruct> phopairs;

      // double loop over photons, make masse
      //cout << "good pho loop " << endl;
      for (auto i = 0U; i < good_phos.size(); i++)
      {
	auto & pho1 = fInPhos[good_phos[i]];
	pho1.b_pt ->GetEntry(entry);
	pho1.b_eta->GetEntry(entry);
	pho1.b_phi->GetEntry(entry);
	pho1.b_E  ->GetEntry(entry);
	TLorentzVector pho1vec; pho1vec.SetPtEtaPhiE(pho1.pt, pho1.eta, pho1.phi, pho1.E);

	for (auto j = i+1; j < good_phos.size(); j++)
	{
	  auto & pho2 = fInPhos[good_phos[j]];
	  pho2.b_pt ->GetEntry(entry);
	  pho2.b_eta->GetEntry(entry);
	  pho2.b_phi->GetEntry(entry);
	  pho2.b_E  ->GetEntry(entry);
	  TLorentzVector pho2vec; pho2vec.SetPtEtaPhiE(pho2.pt, pho2.eta, pho2.phi, pho2.E);
	  // get invariant mass
	  const auto dr12 = pho1vec.DeltaR(pho2vec);
	  pho1vec += pho2vec;  
	  phopairs.emplace_back(good_phos[i],good_phos[j],pho1vec.M(),dr12);
	}

        pho1.b_recHits->GetEntry(entry);
        const auto n = pho1.recHits->size();
       //std::cout << "Looping over zee recHits n = " << n << std::endl;
        for (auto i = 0U; i < n; i++)
        {
          float subsum = 0.f;
          float subsumnot = 0.f;
          float subsumwoot = 0.f;
          int subsumnum = 0;

          const auto rh_i = (*pho1.recHits)[i]; // position within event rec hits vector
          const auto E_i  = (*fInRecHits.E) [rh_i];
          const auto id_i = (*fInRecHits.ID)[rh_i];
          const auto t_i = (*fInRecHits.time)[rh_i];
          const auto tof_i = (*fInRecHits.TOF)[rh_i];
          auto RtStc_t_i = 0.f;
          auto RtOOTStc_t_i = 0.f;
          auto WtOOTStc_t_i = 0.f;

          if( hasMultiKURecHit ){

                for(UInt_t kuseed = 0; kuseed < (*kurhID).size(); kuseed++ ){
                        if( (*kurhID)[kuseed] == id_i ){
                                RtStc_t_i = (*kuStcrhtime)[kuseed];
                                RtOOTStc_t_i = (*kuNotStcrhtime)[kuseed];
                                WtOOTStc_t_i = (*kuWootStcrhtime)[kuseed];
                                break;
                        }
                }
                if( useTOF ){ 
			RtStc_t_i += tof_i;
                        RtOOTStc_t_i += tof_i;
                        WtOOTStc_t_i += tof_i;
		}
		if( E_i >= 5 ){
                sumXtalRtStcPhoClRecTime[id_i] += RtStc_t_i;
                sumXtalRtOOTStcPhoClRecTime[id_i] += RtOOTStc_t_i;
                sumXtalWtOOTStcPhoClRecTime[id_i] += WtOOTStc_t_i;
                numXtalRtOOTStcPhoClRecTime[id_i] += 1;
		}
          }
          for (auto j = i+1; j < n; j++)
          {
            const auto rh_j = (*pho1.recHits)[j]; // position within event rec hits vector
            const auto E_j  = (*fInRecHits.E) [rh_j];
            const auto id_j = (*fInRecHits.ID)[rh_j];
            auto RtStc_t_j = 0.f;
            auto RtOOTStc_t_j = 0.f;
            auto WtOOTStc_t_j = 0.f;
            const auto tof_j = (*fInRecHits.TOF)[rh_j];

                if( hasMultiKURecHit ){
                        for(UInt_t kuseed = 0; kuseed < (*kurhID).size(); kuseed++ ){
                                if( (*kurhID)[kuseed] == id_j ){
                                        RtStc_t_j = (*kuStcrhtime)[kuseed];
                                        RtOOTStc_t_j = (*kuNotStcrhtime)[kuseed];
                                        WtOOTStc_t_j = (*kuWootStcrhtime)[kuseed];
                                        break;
                                }
                        }
                	if( useTOF ){
                        	RtStc_t_j += tof_j;
                        	RtOOTStc_t_j += tof_j;
                        	WtOOTStc_t_j += tof_j;
                	}
                        //sumXtalRtOOTStcPhoIcRecTime :  numXtalRtOOTStcPhoIcRecTime                            
                        if( E_i >= 5 and E_j >= 3 ){
                        subsum += (RtStc_t_i - RtStc_t_j);
                        subsumnot += (RtOOTStc_t_i - RtOOTStc_t_j);
                        subsumwoot += (WtOOTStc_t_i - WtOOTStc_t_j);
                        subsumnum += 1;
                        }
                }

          } // end inner double loop over rechit
//              >>>>  do subsums
          if( hasMultiKURecHit ){
                if( subsumnum == 0. ) subsumnum = 1;
                sumXtalRtStcPhoIcRecTime[id_i] += (subsum/subsumnum);
                sumXtalRtOOTStcPhoIcRecTime[id_i] += (subsumnot/subsumnum);
                sumXtalWtOOTStcPhoIcRecTime[id_i] += (subsumwoot/subsumnum);
                numXtalRtOOTStcPhoIcRecTime[id_i] += 1;
          }
        } // end outer double loop over rechits
       //std::cout << "RecHits Loop done "<< std::endl;	

      }
      //cout << "sort by mass " << endl;
      // sort the mass structs
      std::sort(phopairs.begin(),phopairs.end(),
		[=](const auto & phopair1, const auto & phopair2)
		{
		  const auto diff1 = std::abs(phopair1.mass-Common::Zmass);
		  const auto diff2 = std::abs(phopair2.mass-Common::Zmass);
		  return diff1 < diff2;
		});
          
      // get best pair
      const auto & phopair = phopairs.front();
      
      // make sure within 30 GeV
      if ((phopair.mass < 60.f) || (phopair.mass > 150.f)) continue;
      gZmass = phopair.mass;
      gdR = phopair.dR12;
      fOutCutFlow   ->Fill((cutLabels["diPhoMZrange"]*1.f)-0.5f);
      fOutCutFlowWgt->Fill((cutLabels["diPhoMZrange"]*1.f)-0.5f,wgt);
      fOutCutFlowScl->Fill((cutLabels["diPhoMZrange"]*1.f)-0.5f,evtwgt);

      // re-order photons based on pairs
      auto & pho1 = fInPhos[phopair.ipho1];
      auto & pho2 = fInPhos[phopair.ipho2];

      pho1.b_seed->GetEntry(entry);
      pho2.b_seed->GetEntry(entry);
      fInRecHits.b_ID->GetEntry(entry);

      auto seed1 = pho1.seed;
      auto id1 = (*fInRecHits.ID)[seed1];
      auto t1 = (*fInRecHits.time)[seed1];
      auto seed2 = pho2.seed;
      auto id2 = (*fInRecHits.ID)[seed2];
      auto t2 = (*fInRecHits.time)[seed2];
      auto Rt_t1 = t1;
      auto RtStc_t1 = t1;
      auto RtOOT_t1 = t1;
      auto RtOOTStc_t1 = t1;
      auto WtOOTStc_t1 = t1;
      auto Rt_t2 = t1;
      auto RtStc_t2 = t1;
      auto RtOOT_t2 = t1;
      auto RtOOTStc_t2 = t1;
      auto WtOOTStc_t2 = t1;

     //std::cout << "Filling xtalRecHit " << id1 << " time with: " << t1 << std::endl;
      sumXtalPhoRecTime[id1] += t1;
      sumXtalPhoRecTime[id2] += t2;
      difXtalPhoRecTime[id1] += (t1-t2);
      difXtalPhoRecTime[id2] += (t2-t1);
      if( hasMultiKURecHit ){
          for(UInt_t kuseed = 0; kuseed < (*kurhID).size(); kuseed++ ){
                     if( (*kurhID)[kuseed] == id1 ){
                            Rt_t1 = (*kurhtime)[kuseed];
                            RtStc_t1 = (*kuStcrhtime)[kuseed];
                            //RtOOT_t1 = (*kuNotrhtime)[kuseed];
                            RtOOTStc_t1 = (*kuNotStcrhtime)[kuseed];
                            WtOOTStc_t1 = (*kuWootStcrhtime)[kuseed];
                            }
                     if( (*kurhID)[kuseed] == id2 ){
                            Rt_t2 = (*kurhtime)[kuseed];
                            RtStc_t2 = (*kuStcrhtime)[kuseed];
                           // RtOOT_t2 = (*kuNotrhtime)[kuseed];
                            RtOOTStc_t2 = (*kuNotStcrhtime)[kuseed];
                            WtOOTStc_t2 = (*kuWootStcrhtime)[kuseed];
                            }
          }
	 //std::cout << "Filling xtalRtPhoRecHit time with: " << Rt_t1 << std::endl;
          sumXtalRtPhoRecTime[id1] += Rt_t1;
          sumXtalRtPhoRecTime[id2] += Rt_t2;
          difXtalRtPhoRecTime[id1] += (Rt_t1-Rt_t2);
          difXtalRtPhoRecTime[id2] += (Rt_t2-Rt_t1);
          sumXtalRtStcPhoRecTime[id1] += RtStc_t1;
          sumXtalRtStcPhoRecTime[id2] += RtStc_t2;
          difXtalRtStcPhoRecTime[id1] += (RtStc_t1-RtStc_t2);
          difXtalRtStcPhoRecTime[id2] += (RtStc_t2-RtStc_t1);
          //sumXtalRtOOTPhoRecTime[id1] += RtOOT_t1;
          //sumXtalRtOOTPhoRecTime[id2] += RtOOT_t2;
          //difXtalRtOOTPhoRecTime[id1] += (RtOOT_t1-RtOOT_t2);
          //difXtalRtOOTPhoRecTime[id2] += (RtOOT_t2-RtOOT_t1);
          sumXtalRtOOTStcPhoRecTime[id1] += RtOOTStc_t1;
          sumXtalRtOOTStcPhoRecTime[id2] += RtOOTStc_t2;
          difXtalRtOOTStcPhoRecTime[id1] += (RtOOTStc_t1-RtOOTStc_t2);
          difXtalRtOOTStcPhoRecTime[id2] += (RtOOTStc_t2-RtOOTStc_t1);
      }
     //std::cout << "-------------Finished filling sumXtalRecHit times." << std::endl;
      numXtalPhoRecTime[id1] += 1;
      numXtalPhoRecTime[id2] += 1;
     //std::cout << "-------------Finished filling numXxtalRecHit times." << std::endl;

  // //   cout << "Seed1: " << seed1 << " ID: " << id1 << endl;
  // //   cout << "Seed2: " << seed2 << " ID: " << id2 << endl;

  //    nxtal_sep =  0;
      nxtal_sep =  Common::Xtal_Seperation(id1,id2);
  // //  //std::cout << " nxtal_sep : " << nxtal_sep << std::endl;
 
//            const auto rh_j = (*inpho.recHits)[j]; // position within event rec hits vector
//            const auto E_j  = (*fInRecHits.E) [rh_j];
//            const auto id_j = (*fInRecHits.ID)[rh_j];

      pho1.b_pt->GetEntry(entry);
      pho2.b_pt->GetEntry(entry);

      // now start to save them
      ////cout << "save photon " << endl;
      fPhoList.clear();
      fPhoList.emplace_back((pho1.pt > pho2.pt) ? phopair.ipho1 : phopair.ipho2);
      fPhoList.emplace_back((pho1.pt > pho2.pt) ? phopair.ipho2 : phopair.ipho1);
      for (auto ipho = 0; ipho < Common::nPhotons; ipho++)
      {
	if      (phopair.ipho1 == ipho) continue;
	else if (phopair.ipho2 == ipho) continue;
	
	fPhoList.emplace_back(ipho);
      }
    } // end of ZeeSkim
    else if (fSkim == SkimType::DiXtal) // this is a hack selection, which mixes up seeds and photons --> do NOT use this for analysis
    {
     //std::cout << "Start DiXtal "<< std::endl;
      // get rechits
//      fInRecHits.b_E->GetEntry(entry);
//      fInRecHits.b_ID->GetEntry(entry);
//      fInRecHits.b_time->GetEntry(entry);
        //std::cout << "Pulling RecHits done "<< std::endl;
//
      gZmass = 0.f;     
      gdR = 0.f; 
//      for( UInt_t idx = 0; idx < (*fInRecHits.ID).size(); idx++ ){
//                 //std::cout << "Filling first xtalRecHit " << id_i << " time with: " << t_i << std::endl;
//         	 const auto id_i = (*fInRecHits.ID)[idx];
//          	 const auto t_i = (*fInRecHits.time)[idx];		
//                 sumXtalRecTime[id_i] += t_i;
//                 numXtalRecTime[id_i] += 1;
//      }

      // loop over photons, getting pairs of rec hits that are most energetic and match!
     //std::cout << "Looping over Photons "<< std::endl;
      std::vector<DiXtalInfo> good_pairs;
      for (auto ipho = 0; ipho < Common::nPhotons; ipho++)
      {	
	auto & inpho = fInPhos[ipho];

	// skip OOT for now
	inpho.b_isOOT->GetEntry(entry);
	if (inpho.isOOT) continue;
	
	inpho.b_smin->GetEntry(entry);
	inpho.b_smaj->GetEntry(entry);

	if (inpho.smin > 0.3) continue;
	if (inpho.smaj > 0.5) continue;
		
	// get pair of rechits that are good candidates : double loop, yo
	inpho.b_recHits->GetEntry(entry);

	const auto n = inpho.recHits->size();
        //std::cout << "Looping over recHits n = " << n << std::endl;
	for (auto i = 0U; i < n; i++)
	{
	  Bool_t isGoodPair = false;
          float subsum = 0.f;
          int subsumnum = 0;
          float subsumnot = 0.f;
          float subsumwoot = 0.f;

	  const auto rh_i = (*inpho.recHits)[i]; // position within event rec hits vector
	  const auto E_i  = (*fInRecHits.E) [rh_i];
	  const auto id_i = (*fInRecHits.ID)[rh_i];
	  const auto t_i = (*fInRecHits.time)[rh_i];
	  const auto tof_i = (*fInRecHits.TOF)[rh_i];
	  auto RtStc_t_i = 0.f;
          auto RtOOTStc_t_i = 0.f;
          auto WtOOTStc_t_i = 0.f;

	  if( hasMultiKURecHit ){

                for(UInt_t kuseed = 0; kuseed < (*kurhID).size(); kuseed++ ){
                        if( (*kurhID)[kuseed] == id_i ){
                                RtStc_t_i = (*kuStcrhtime)[kuseed];
                                RtOOTStc_t_i = (*kuNotStcrhtime)[kuseed];
                                WtOOTStc_t_i = (*kuWootStcrhtime)[kuseed];
                                break;
                        }
                }
		if( useTOF ){ 
			RtStc_t_i += tof_i;
                        RtOOTStc_t_i += tof_i;
                        WtOOTStc_t_i += tof_i;		
		}
		if( E_i >= 3 ){
		sumXtalRtStcPhoClRecTime[id_i] += RtStc_t_i;
                sumXtalRtOOTStcPhoClRecTime[id_i] += RtOOTStc_t_i;
                sumXtalWtOOTStcPhoClRecTime[id_i] += WtOOTStc_t_i;
		numXtalRtOOTStcPhoClRecTime[id_i] += 1;
		}
	  }

	  for (auto j = i+1; j < n; j++)
	  {
	    const auto rh_j = (*inpho.recHits)[j]; // position within event rec hits vector
	    const auto E_j  = (*fInRecHits.E) [rh_j];
	    const auto id_j = (*fInRecHits.ID)[rh_j];
	    auto RtStc_t_j = 0.f;
            auto RtOOTStc_t_j = 0.f;
            auto WtOOTStc_t_j = 0.f;
	    const auto tof_j = (*fInRecHits.TOF)[rh_j];
//		asd
//		if( tof_i == tof_j ){
		if( hasMultiKURecHit ){
			for(UInt_t kuseed = 0; kuseed < (*kurhID).size(); kuseed++ ){
                        	if( (*kurhID)[kuseed] == id_j ){
                                	RtStc_t_j = (*kuStcrhtime)[kuseed];
                                        RtOOTStc_t_j = (*kuNotStcrhtime)[kuseed];
                                        WtOOTStc_t_j = (*kuWootStcrhtime)[kuseed];
                                	break;
                        	}	
                	}
                	if( useTOF ){
                        	RtStc_t_j += tof_j;
                        	RtOOTStc_t_j += tof_j;
                        	WtOOTStc_t_j += tof_j;
                	}
			//sumXtalRtOOTStcPhoIcRecTime :  numXtalRtOOTStcPhoIcRecTime				
			if( E_i >= 3 and E_j >= 1 ){
			subsum += (RtStc_t_i - RtStc_t_j);
                        subsumnot += (RtOOTStc_t_i - RtOOTStc_t_j);
                        subsumwoot += (WtOOTStc_t_i - WtOOTStc_t_j);
			subsumnum += 1;
			}
		}
		//}  // if tof == tof

		if ( not isGoodPair ){
	    	if (Common::IsCrossNeighbor(id_i,id_j)){ // neighboring crystals
	    	if (E_i <= (1.2f * E_j)){ // need to be within 20% of energy  old line:  if (E_i > (1.2f * E_j)) break;
			good_pairs.emplace_back(rh_i,rh_j,ipho);
	      		isGoodPair = true;
	      		nxtal_sep = 1;
	    		//  break;
	        }}}
	  } // end inner double loop over rechit
//		>>>>  do subsums
	  if( hasMultiKURecHit ){
		if( subsumnum == 0. ) subsumnum = 1;
		sumXtalRtStcPhoIcRecTime[id_i] += (subsum/subsumnum);
                sumXtalRtOOTStcPhoIcRecTime[id_i] += (subsumnot/subsumnum);
                sumXtalWtOOTStcPhoIcRecTime[id_i] += (subsumwoot/subsumnum);
		numXtalRtOOTStcPhoIcRecTime[id_i] += 1;
	  }	
	  //if (isGoodPair) break;
	} // end outer double loop over rechits
       //std::cout << "RecHits Loop done "<< std::endl;
      } // end loop over photons
     //std::cout << "Photon Loop done "<< std::endl;

      // skip if no pairs found
      if (good_pairs.size() == 0) continue;
      fOutCutFlow   ->Fill((cutLabels["goodDiXtal"]*1.f)-0.5f);
      fOutCutFlowWgt->Fill((cutLabels["goodDiXtal"]*1.f)-0.5f,wgt);
      fOutCutFlowScl->Fill((cutLabels["goodDiXtal"]*1.f)-0.5f,evtwgt);

      // sort pairs by highest energy for E1
      std::sort(good_pairs.begin(),good_pairs.end(),
		[&](const auto & pair1, const auto & pair2)
		{
		  return ((*fInRecHits.E)[pair1.rh1] > (*fInRecHits.E)[pair2.rh2]);
		});

      // now do the unholiest of exercises... set seed ids of first and second photon to pair ids
      const auto & pair = good_pairs.front();
      Skimmer::FillPhoListStandard();
      fOutPhos[0].seed = pair.rh1;
      fOutPhos[1].seed = pair.rh2;

            const auto id_i = (*fInRecHits.ID)[pair.rh1];
            const auto t_i = (*fInRecHits.time)[pair.rh1];
            const auto id_j = (*fInRecHits.ID)[pair.rh2];
            const auto t_j = (*fInRecHits.time)[pair.rh2];
            auto Rt_t_i = t_j;
            auto RtStc_t_i = t_j;
            //auto RtOOT_t_i = t_j;
            auto RtOOTStc_t_i = t_j;
            auto Rt_t_j = t_j;
            auto RtStc_t_j = t_j;
            //auto RtOOT_t_j = t_j;
            auto RtOOTStc_t_j = t_j;

	   //std::cout << "DiXtal rh time for pho " << pair.iph << " in " << id_i << " with " << t_i << std::endl;

              nxtal_sep = 1;
              sumXtalPhoRecTime[id_i] += t_i;
              sumXtalPhoRecTime[id_j] += t_j;
              difXtalPhoRecTime[id_i] += (t_i-t_j);
              difXtalPhoRecTime[id_j] += (t_j-t_i);
              numXtalPhoRecTime[id_i] += 1;
              numXtalPhoRecTime[id_j] += 1;
              if( hasMultiKURecHit ){
                 //std::cout << "filling ku rechits times" << std::endl;
                  for(UInt_t kuseed = 0; kuseed < (*kurhID).size(); kuseed++ ){
                             if( (*kurhID)[kuseed] == id_i ){
                                    Rt_t_i = (*kurhtime)[kuseed];
                                    RtStc_t_i = (*kuStcrhtime)[kuseed];
                                    //RtOOT_t_i = (*kuNotrhtime)[kuseed];
                                    RtOOTStc_t_i = (*kuNotStcrhtime)[kuseed];
                                    }
                             if( (*kurhID)[kuseed] == id_j ){
                                    Rt_t_j = (*kurhtime)[kuseed];
                                    RtStc_t_j = (*kuStcrhtime)[kuseed];
                                    //RtOOT_t_j = (*kuNotrhtime)[kuseed];
                                    RtOOTStc_t_j = (*kuNotStcrhtime)[kuseed];
                                    }
                  }
                  sumXtalRtPhoRecTime[id_i] += Rt_t_i;
                  sumXtalRtPhoRecTime[id_j] += Rt_t_j;
                  difXtalRtPhoRecTime[id_i] += (Rt_t_i-Rt_t_j);
                  difXtalRtPhoRecTime[id_j] += (Rt_t_j-Rt_t_i);
                  sumXtalRtStcPhoRecTime[id_i] += RtStc_t_i;
                  sumXtalRtStcPhoRecTime[id_j] += RtStc_t_j;
                  difXtalRtStcPhoRecTime[id_i] += (RtStc_t_i-RtStc_t_j);
                  difXtalRtStcPhoRecTime[id_j] += (RtStc_t_j-RtStc_t_i);
                  //sumXtalRtOOTPhoRecTime[id_i] += RtOOT_t_i;
                  //sumXtalRtOOTPhoRecTime[id_j] += RtOOT_t_j;
                  //difXtalRtOOTPhoRecTime[id_i] += (RtOOT_t_i-RtOOT_t_j);
                  //difXtalRtOOTPhoRecTime[id_j] += (RtOOT_t_j-RtOOT_t_i);
                  sumXtalRtOOTStcPhoRecTime[id_i] += RtOOTStc_t_i;
                  sumXtalRtOOTStcPhoRecTime[id_j] += RtOOTStc_t_j;
                  difXtalRtOOTStcPhoRecTime[id_i] += (RtOOTStc_t_i-RtOOTStc_t_j);
                  difXtalRtOOTStcPhoRecTime[id_j] += (RtOOTStc_t_j-RtOOTStc_t_i);
	      }

       //std::cout << "Filling fOutAveXtalRecTimeHist. " << std::endl;
  //    for( std::map<UInt_t,Float_t>::iterator it=sumXtalRecTime.begin(); it!=sumXtalRecTime.end(); ++it){
  //    	fOutAveXtalRecTimeHist->Fill( (it->second)/(numXtalRecTime[it->first]) );
  //    }
      //std::cout << "DiXtal: Set pho list in standard fashion." << std::endl;
      fPhoList.clear();
      fPhoList.emplace_back(pair.iph);
      fPhoList.emplace_back(pair.iph);
      for (auto ipho = 0; ipho < Common::nPhotons; ipho++) fPhoList.emplace_back(ipho);
    }
    else if (fSkim == SkimType::AlwaysTrue) // no skim, just set photon list
    {
      Skimmer::FillPhoListStandard();
    }
    else if (fSkim == SkimType::AlwaysFalse) // just skip all events! testing purposes only...
    {
      continue;
    }
    else
    {
      std::cerr << "How did this happen?? Somehow SkimType Enum is not one that is specified... Exiting..."  << std::endl;
      exit(1);
    }
   //std::cout << "Finished proccessing skim." << std::endl;

    // common skim params for MC
    if (fSkim != SkimType::AlwaysTrue)
    {
      // cut on crappy pu
//      if (fIsMC)
//      {
//	fInEvent.b_genputrue->GetEntry(entry);
//	if ((fInEvent.genputrue < 0) || (UInt_t(fInEvent.genputrue) >= fPUWeights.size())) continue;
//        if ((fInEvent.genputrue < 0)) continue;
//      }

      // fill cutflow
      fOutCutFlow   ->Fill((cutLabels["badPU"]*1.f)-0.5f);
      fOutCutFlowWgt->Fill((cutLabels["badPU"]*1.f)-0.5f,wgt);
      fOutCutFlowScl->Fill((cutLabels["badPU"]*1.f)-0.5f,evtwgt);
    }

    // end of skim, now copy... dropping rechits
//    if (fOutConfig.isGMSB) Skimmer::FillOutGMSBs(entry);
//    if (fOutConfig.isHVDS) Skimmer::FillOutHVDSs(entry);
//   if (fOutConfig.isToy)  Skimmer::FillOutToys(entry);
    Skimmer::FillOutEvent(entry,evtwgt);
    //std::cout << "Finished proccessing event info." << std::endl;
    //if (fSkim != SkimType::DiXtal) Skimmer::FillOutJets(entry);
    //std::cout << "Start proccessing phos info." << std::endl;
    Skimmer::FillOutPhos(entry);
    //std::cout << "Finished proccessing phos info." << std::endl;
//    if (fIsMC) Skimmer::CorrectMET();

    // fill the tree
    fOutTree->Fill();
  } // end loop over events

//  if (fSkim == SkimType::DiXtal){
//  if (true){

	  UInt_t offset = 100;
	  //std::cout << "Filling Hists and Maps. " << std::endl;
	  for( std::map<UInt_t,Float_t>::iterator it=sumXtalRecTime.begin(); it!=sumXtalRecTime.end(); ++it){
		const auto & idinfo = Common::DetIDMap[it->first];
                const auto & aveXtalTime = (it->second)/(numXtalRecTime[it->first]);
		//std::cout << "Filling " << it->first << " with " << it->second << " / " << numXtalRecTime[it->first] << std::endl;
	        fOutAveXtalRecTimeHist->Fill( aveXtalTime  );
                fOutAveXtalOccHist->Fill( numXtalRecTime[it->first] );
		if( idinfo.ecal == ECAL::EB ){ 
			fOutAveXtalRecTimeHistEB->Fill( aveXtalTime );
                        fOutAveXtalOccHistEB->Fill( numXtalRecTime[it->first] );
			fOutAveXtalRecTimeMapEB->Fill( idinfo.i2, idinfo.i1, aveXtalTime + offset ); 
                        fOutAveXtalOccMapEB->Fill( idinfo.i2, idinfo.i1, numXtalRecTime[it->first] );
		} else if( idinfo.ecal == ECAL::EP ){
                        fOutAveXtalRecTimeHistEP->Fill( aveXtalTime ); 
                        fOutAveXtalOccHistEP->Fill( numXtalRecTime[it->first] ); 
                        fOutAveXtalRecTimeMapEP->Fill( idinfo.i1, idinfo.i2, aveXtalTime + offset );
                        fOutAveXtalOccMapEP->Fill( idinfo.i1, idinfo.i2, numXtalRecTime[it->first] );
                } else if( idinfo.ecal == ECAL::EM ){ 
                        fOutAveXtalRecTimeHistEM->Fill( aveXtalTime );
                        fOutAveXtalOccHistEM->Fill( numXtalRecTime[it->first] );
                        fOutAveXtalRecTimeMapEM->Fill( idinfo.i1, idinfo.i2, aveXtalTime + offset );
                        fOutAveXtalOccMapEM->Fill( idinfo.i1, idinfo.i2, numXtalRecTime[it->first] );
		}
	  }

	  //std::cout << "Filling fOutAveXtalPhoRecTime Hists and Maps. " << std::endl;
	  for( std::map<UInt_t,Float_t>::iterator it=sumXtalPhoRecTime.begin(); it!=sumXtalPhoRecTime.end(); ++it){
               //std::cout << "Mapping " << it->first << " to idinfo." << std::endl;
                const auto & idinfo = Common::DetIDMap[it->first];
               //std::cout << "Filling " << idinfo.i2 << " x " << idinfo.i1 << " with " << it->second << " / " << numXtalPhoRecTime[it->first] << std::endl;
                const auto & aveXtalTime = (it->second)/(numXtalPhoRecTime[it->first]);
                fOutAveXtalPhoRecTimeHist->Fill( aveXtalTime );
                fOutAveXtalPhoOccHist->Fill( numXtalPhoRecTime[it->first] );
                if( idinfo.ecal == ECAL::EB ){
                        fOutAveXtalPhoRecTimeHistEB->Fill( aveXtalTime ); 
                        fOutAveXtalPhoOccHistEB->Fill( numXtalPhoRecTime[it->first] ); 
                        fOutAveXtalPhoRecTimeMapEB->Fill( idinfo.i2, idinfo.i1, aveXtalTime + offset );
                        fOutAveXtalPhoOccMapEB->Fill( idinfo.i2, idinfo.i1, numXtalPhoRecTime[it->first] );
                } else if( idinfo.ecal == ECAL::EP ){
                        fOutAveXtalPhoRecTimeHistEP->Fill( aveXtalTime );
                        fOutAveXtalPhoOccHistEP->Fill( numXtalPhoRecTime[it->first] );
                        fOutAveXtalPhoRecTimeMapEP->Fill( idinfo.i1, idinfo.i2, aveXtalTime + offset );
                        fOutAveXtalPhoOccMapEP->Fill( idinfo.i1, idinfo.i2, numXtalPhoRecTime[it->first] );
                } else if( idinfo.ecal == ECAL::EM ){  
                        fOutAveXtalPhoRecTimeHistEM->Fill( aveXtalTime );
                        fOutAveXtalPhoOccHistEM->Fill( numXtalPhoRecTime[it->first] );
                        fOutAveXtalPhoRecTimeMapEM->Fill( idinfo.i1, idinfo.i2, aveXtalTime + offset );
                        fOutAveXtalPhoOccMapEM->Fill( idinfo.i1, idinfo.i2, numXtalPhoRecTime[it->first] );
                }
		if( hasMultiKURecHit ){
                    const auto & aveXtalRtTime = (sumXtalRtPhoRecTime[it->first])/(numXtalPhoRecTime[it->first]);
                   //std::cout << "Filling Rt " << it->first << " with " << sumXtalRtPhoRecTime[it->first] << " / " << numXtalPhoRecTime[it->first] << std::endl;
                    fOutAveXtalRtPhoRecTimeHist->Fill( aveXtalRtTime );
                    if( idinfo.ecal == ECAL::EB ){
                            fOutAveXtalRtPhoRecTimeHistEB->Fill( aveXtalRtTime );
                            fOutAveXtalRtPhoRecTimeMapEB->Fill( idinfo.i2, idinfo.i1, aveXtalRtTime + offset );
                    } else if( idinfo.ecal == ECAL::EP ){
                            fOutAveXtalRtPhoRecTimeHistEP->Fill( aveXtalRtTime );
                            fOutAveXtalRtPhoRecTimeMapEP->Fill( idinfo.i1, idinfo.i2, aveXtalRtTime + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
                            fOutAveXtalRtPhoRecTimeHistEM->Fill( aveXtalRtTime );
                            fOutAveXtalRtPhoRecTimeMapEM->Fill( idinfo.i1, idinfo.i2, aveXtalRtTime + offset );
                    }
		}
                if( hasMultiKURecHit ){
                    const auto & aveXtalRtStcTime = (sumXtalRtStcPhoRecTime[it->first])/(numXtalPhoRecTime[it->first]);
                   //std::cout << "Filling RtStc " << it->first << " with " << sumXtalRtStcPhoRecTime[it->first] << " / " << numXtalPhoRecTime[it->first] << std::endl;
                    fOutAveXtalRtStcPhoRecTimeHist->Fill( aveXtalRtStcTime );
                    if( idinfo.ecal == ECAL::EB ){
                            fOutAveXtalRtStcPhoRecTimeHistEB->Fill( aveXtalRtStcTime );
                            fOutAveXtalRtStcPhoRecTimeMapEB->Fill( idinfo.i2, idinfo.i1, aveXtalRtStcTime + offset );
                    } else if( idinfo.ecal == ECAL::EP ){
                            fOutAveXtalRtStcPhoRecTimeHistEP->Fill( aveXtalRtStcTime );
                            fOutAveXtalRtStcPhoRecTimeMapEP->Fill( idinfo.i1, idinfo.i2, aveXtalRtStcTime + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
                            fOutAveXtalRtStcPhoRecTimeHistEM->Fill( aveXtalRtStcTime );
                            fOutAveXtalRtStcPhoRecTimeMapEM->Fill( idinfo.i1, idinfo.i2, aveXtalRtStcTime + offset );
                    }
                }
//                if( hasMultiKURecHit ){
//                    const auto & aveXtalRtOOTTime = (sumXtalRtOOTPhoRecTime[it->first])/(numXtalPhoRecTime[it->first]);
//                   //std::cout << "Filling RtOOT " << it->first << " with " << sumXtalRtOOTPhoRecTime[it->first] << " / " << numXtalPhoRecTime[it->first] << std::endl;
//                    fOutAveXtalRtOOTPhoRecTimeHist->Fill( aveXtalRtOOTTime );
//                    if( idinfo.ecal == ECAL::EB ){
//                            fOutAveXtalRtOOTPhoRecTimeHistEB->Fill( aveXtalRtOOTTime );
//                            fOutAveXtalRtOOTPhoRecTimeMapEB->Fill( idinfo.i2, idinfo.i1, aveXtalRtOOTTime + offset );
//                    } else if( idinfo.ecal == ECAL::EP ){
//                            fOutAveXtalRtOOTPhoRecTimeHistEP->Fill( aveXtalRtOOTTime );
//                            //auto test = idinfo.i1;
//                            //if( test > 50 ) test = test - 50;
//                            //fOutAveXtalRtOOTPhoRecTimeMapEP->Fill( test, idinfo.i2, aveXtalRtOOTTime + offset );
//                            fOutAveXtalRtOOTPhoRecTimeMapEP->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTTime + offset );
//                    } else if( idinfo.ecal == ECAL::EM ){
//                            fOutAveXtalRtOOTPhoRecTimeHistEM->Fill( aveXtalRtOOTTime );
//                            fOutAveXtalRtOOTPhoRecTimeMapEM->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTTime + offset );
//                    }
//                }
                if( hasMultiKURecHit ){
                    const auto & aveXtalRtOOTStcTime = (sumXtalRtOOTStcPhoRecTime[it->first])/(numXtalPhoRecTime[it->first]);
                   //std::cout << "Filling RtOOTStc " << it->first << " with " << sumXtalRtOOTStcPhoRecTime[it->first] << " / " << numXtalPhoRecTime[it->first] << std::endl;
                    fOutAveXtalRtOOTStcPhoRecTimeHist->Fill( aveXtalRtOOTStcTime );
		   //std::cout << "Filling RtOOTStc Maps and Hists with offset: " << offset << std::endl;
                    if( idinfo.ecal == ECAL::EB ){
			   //std::cout << "Filling EB hist" << std::endl;
                            fOutAveXtalRtOOTStcPhoRecTimeHistEB->Fill( aveXtalRtOOTStcTime );
			   //std::cout << "Filling EB Map" << std::endl;
                            fOutAveXtalRtOOTStcPhoRecTimeMapEB->Fill( idinfo.i2, idinfo.i1, aveXtalRtOOTStcTime + offset );
                           //std::cout << "Finished EB Filled" << std::endl;
                    } else if( idinfo.ecal == ECAL::EP ){
  			   //std::cout << "Filling EP Maps" << std::endl;
                            fOutAveXtalRtOOTStcPhoRecTimeHistEP->Fill( aveXtalRtOOTStcTime );
                            fOutAveXtalRtOOTStcPhoRecTimeMapEP->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
			   //std::cout << "Filling EM Maps" << std::endl;
                            fOutAveXtalRtOOTStcPhoRecTimeHistEM->Fill( aveXtalRtOOTStcTime );
                            fOutAveXtalRtOOTStcPhoRecTimeMapEM->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime + offset );
                    }
                }
          //std::cout << "Finished Filling fOutAveXtalPhoRecTime Hists and Maps. " << std::endl;		
	  }
          //std::cout << "Filling fOutDifXtalPhoRecTime Hists and Maps. " << std::endl;
          for( std::map<UInt_t,Float_t>::iterator it=difXtalPhoRecTime.begin(); it!=difXtalPhoRecTime.end(); ++it){
                const auto & idinfo = Common::DetIDMap[it->first];
                const auto & aveXtalTime = (it->second)/(numXtalPhoRecTime[it->first]);
//             //std::cout << "Filling " << it->first << " with " << it->second << " / " << numXtalPhoRecTime[it->first] << std::endl;
                fOutDifXtalPhoRecTimeHist->Fill( aveXtalTime );
                if( idinfo.ecal == ECAL::EB ){
                        fOutDifXtalPhoRecTimeHistEB->Fill( aveXtalTime );
                        fOutDifXtalPhoRecTimeMapEB->Fill( idinfo.i2, idinfo.i1, aveXtalTime + offset );
                } else if( idinfo.ecal == ECAL::EP ){
                        fOutDifXtalPhoRecTimeHistEP->Fill( aveXtalTime );
                        fOutDifXtalPhoRecTimeMapEP->Fill( idinfo.i1, idinfo.i2, aveXtalTime + offset );
                } else if( idinfo.ecal == ECAL::EM ){
                        fOutDifXtalPhoRecTimeHistEM->Fill( aveXtalTime );
                        fOutDifXtalPhoRecTimeMapEM->Fill( idinfo.i1, idinfo.i2, aveXtalTime + offset );
                }
                if( hasMultiKURecHit ){
                    const auto & aveXtalRtTime = (difXtalRtPhoRecTime[it->first])/(numXtalPhoRecTime[it->first]);
    //             //std::cout << "Filling " << it->first << " with " << it->second << " / " << numXtalPhoRecTime[it->first] << std::endl;
                    fOutDifXtalRtPhoRecTimeHist->Fill( aveXtalRtTime );
                    if( idinfo.ecal == ECAL::EB ){
                            fOutDifXtalRtPhoRecTimeHistEB->Fill( aveXtalRtTime );
                            fOutDifXtalRtPhoRecTimeMapEB->Fill( idinfo.i2, idinfo.i1, aveXtalRtTime + offset );
                    } else if( idinfo.ecal == ECAL::EP ){
                            fOutDifXtalRtPhoRecTimeHistEP->Fill( aveXtalRtTime );
                            fOutDifXtalRtPhoRecTimeMapEP->Fill( idinfo.i1, idinfo.i2, aveXtalRtTime + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
                            fOutDifXtalRtPhoRecTimeHistEM->Fill( aveXtalRtTime );
                            fOutDifXtalRtPhoRecTimeMapEM->Fill( idinfo.i1, idinfo.i2, aveXtalRtTime + offset );
                    }
                }
                if( hasMultiKURecHit ){
                    const auto & aveXtalRtStcTime = (difXtalRtStcPhoRecTime[it->first])/(numXtalPhoRecTime[it->first]);
    //             //std::cout << "Filling " << it->first << " with " << it->second << " / " << numXtalPhoRecTime[it->first] << std::endl;
                    fOutDifXtalRtStcPhoRecTimeHist->Fill( aveXtalRtStcTime );
                    if( idinfo.ecal == ECAL::EB ){
                            fOutDifXtalRtStcPhoRecTimeHistEB->Fill( aveXtalRtStcTime );
                            fOutDifXtalRtStcPhoRecTimeMapEB->Fill( idinfo.i2, idinfo.i1, aveXtalRtStcTime + offset );
                    } else if( idinfo.ecal == ECAL::EP ){
                            fOutDifXtalRtStcPhoRecTimeHistEP->Fill( aveXtalRtStcTime );
                            fOutDifXtalRtStcPhoRecTimeMapEP->Fill( idinfo.i1, idinfo.i2, aveXtalRtStcTime + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
                            fOutDifXtalRtStcPhoRecTimeHistEM->Fill( aveXtalRtStcTime );
                            fOutDifXtalRtStcPhoRecTimeMapEM->Fill( idinfo.i1, idinfo.i2, aveXtalRtStcTime + offset );
                    }
                }
//                if( hasMultiKURecHit ){
//                    const auto & aveXtalRtOOTTime = (difXtalRtOOTPhoRecTime[it->first])/(numXtalPhoRecTime[it->first]);
//    //             //std::cout << "Filling " << it->first << " with " << it->second << " / " << numXtalPhoRecTime[it->first] << std::endl;
//                    fOutDifXtalRtOOTPhoRecTimeHist->Fill( aveXtalRtOOTTime );
//                    if( idinfo.ecal == ECAL::EB ){
//                            fOutDifXtalRtOOTPhoRecTimeHistEB->Fill( aveXtalRtOOTTime );
//                            fOutDifXtalRtOOTPhoRecTimeMapEB->Fill( idinfo.i2, idinfo.i1, aveXtalRtOOTTime + offset );
//                    } else if( idinfo.ecal == ECAL::EP ){
//                            fOutDifXtalRtOOTPhoRecTimeHistEP->Fill( aveXtalRtOOTTime );
//                            fOutDifXtalRtOOTPhoRecTimeMapEP->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTTime + offset );
//                    } else if( idinfo.ecal == ECAL::EM ){
//                            fOutDifXtalRtOOTPhoRecTimeHistEM->Fill( aveXtalRtOOTTime );
//                            fOutDifXtalRtOOTPhoRecTimeMapEM->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTTime + offset );
//                    }
//                }
                if( hasMultiKURecHit ){
                    const auto & aveXtalRtOOTStcTime = (difXtalRtOOTStcPhoRecTime[it->first])/(numXtalPhoRecTime[it->first]);
    //             //std::cout << "Filling " << it->first << " with " << it->second << " / " << numXtalPhoRecTime[it->first] << std::endl;
                    fOutDifXtalRtOOTStcPhoRecTimeHist->Fill( aveXtalRtOOTStcTime );
                    if( idinfo.ecal == ECAL::EB ){
                            fOutDifXtalRtOOTStcPhoRecTimeHistEB->Fill( aveXtalRtOOTStcTime );
                            fOutDifXtalRtOOTStcPhoRecTimeMapEB->Fill( idinfo.i2, idinfo.i1, aveXtalRtOOTStcTime + offset );
                    } else if( idinfo.ecal == ECAL::EP ){
                            fOutDifXtalRtOOTStcPhoRecTimeHistEP->Fill( aveXtalRtOOTStcTime );
                            fOutDifXtalRtOOTStcPhoRecTimeMapEP->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
                            fOutDifXtalRtOOTStcPhoRecTimeHistEM->Fill( aveXtalRtOOTStcTime );
                            fOutDifXtalRtOOTStcPhoRecTimeMapEM->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime + offset );
                    }
                }
          //std::cout << "Finished Filling fOutDifXtalPhoRecTime Hists and Maps. " << std::endl;
          }
	if( hasMultiKURecHit ){
          for( std::map<UInt_t,Float_t>::iterator it=sumXtalRtOOTStcRecTime.begin(); it!=sumXtalRtOOTStcRecTime.end(); ++it){
                    const auto & idinfo = Common::DetIDMap[it->first];
                    const auto & aveXtalRtOOTStcTime = (sumXtalRtOOTStcRecTime[it->first])/(numXtalRtOOTStcRecTime[it->first]);
    //             //std::cout << "Filling " << it->first << " with " << it->second << " / " << numXtalRtOOTStcRecTime[it->first] << std::endl;
                    if( idinfo.ecal == ECAL::EB ){
                            fOutAveXtalRtOOTStcRecTimeHistEB->Fill( aveXtalRtOOTStcTime );
                            fOutAveXtalRtOOTStcRecTimeMapEB->Fill( idinfo.i2, idinfo.i1, aveXtalRtOOTStcTime + offset );
                    } else if( idinfo.ecal == ECAL::EP ){
                            fOutAveXtalRtOOTStcRecTimeHistEP->Fill( aveXtalRtOOTStcTime );
                            fOutAveXtalRtOOTStcRecTimeMapEP->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
                            fOutAveXtalRtOOTStcRecTimeHistEM->Fill( aveXtalRtOOTStcTime );
                            fOutAveXtalRtOOTStcRecTimeMapEM->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime + offset );
                    }
          }
          for( std::map<UInt_t,Float_t>::iterator it=sumXtalRtOOTStcRecTimeE0.begin(); it!=sumXtalRtOOTStcRecTimeE0.end(); ++it){
                    const auto & idinfo = Common::DetIDMap[it->first];
                    const auto & aveXtalRtOOTStcTime0 = (sumXtalRtOOTStcRecTimeE0[it->first])/(numXtalRtOOTStcRecTimeE0[it->first]);
    //             //std::cout << "Filling " << it->first << " with " << it->second << " / " << numXtalRtOOTStcRecTime[it->first] << std::endl;
                    if( idinfo.ecal == ECAL::EB ){
                            fOutAveXtalRtOOTStcRecTimeE0HistEB->Fill( aveXtalRtOOTStcTime0 );
                            fOutAveXtalRtOOTStcRecTimeE0MapEB->Fill( idinfo.i2, idinfo.i1, aveXtalRtOOTStcTime0 + offset );
                    } else if( idinfo.ecal == ECAL::EP ){
                            fOutAveXtalRtOOTStcRecTimeE0HistEP->Fill( aveXtalRtOOTStcTime0 );
                            fOutAveXtalRtOOTStcRecTimeE0MapEP->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime0 + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
                            fOutAveXtalRtOOTStcRecTimeE0HistEM->Fill( aveXtalRtOOTStcTime0 );
                            fOutAveXtalRtOOTStcRecTimeE0MapEM->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime0 + offset );
                    }
          }
          for( std::map<UInt_t,Float_t>::iterator it=sumXtalRtOOTStcRecTimeE1.begin(); it!=sumXtalRtOOTStcRecTimeE1.end(); ++it){
                    const auto & idinfo = Common::DetIDMap[it->first];
                    const auto & aveXtalRtOOTStcTime1 = (sumXtalRtOOTStcRecTimeE1[it->first])/(numXtalRtOOTStcRecTimeE1[it->first]);
          //         //std::cout << "Filling E1 " << it->first << " with " << it->second << " / " << numXtalRtOOTStcRecTimeE1[it->first] << std::endl;
                    if( idinfo.ecal == ECAL::EB ){
                            fOutAveXtalRtOOTStcRecTimeE1HistEB->Fill( aveXtalRtOOTStcTime1 );
                            fOutAveXtalRtOOTStcRecTimeE1MapEB->Fill( idinfo.i2, idinfo.i1, aveXtalRtOOTStcTime1 + offset );
                    } else if( idinfo.ecal == ECAL::EP ){
                            fOutAveXtalRtOOTStcRecTimeE1HistEP->Fill( aveXtalRtOOTStcTime1 );
                            fOutAveXtalRtOOTStcRecTimeE1MapEP->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime1 + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
                            fOutAveXtalRtOOTStcRecTimeE1HistEM->Fill( aveXtalRtOOTStcTime1 );
                            fOutAveXtalRtOOTStcRecTimeE1MapEM->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime1 + offset );
                    }
          }
          for( std::map<UInt_t,Float_t>::iterator it=sumXtalRtOOTStcRecTime2E1.begin(); it!=sumXtalRtOOTStcRecTime2E1.end(); ++it){
                    const auto & idinfo = Common::DetIDMap[it->first];
                    const auto & aveXtalRtOOTStcTime1 = (sumXtalRtOOTStcRecTime2E1[it->first])/(numXtalRtOOTStcRecTime2E1[it->first]);
        //           //std::cout << "Filling fOutAveXtalRtOOTStcRecTime2E1 " << it->first << " with " << it->second << " / " << numXtalRtOOTStcRecTime2E1[it->first] << std::endl;
                    if( idinfo.ecal == ECAL::EB ){
			   //std::cout << "EB" << std::endl;
                            fOutAveXtalRtOOTStcRecTime2E1HistEB->Fill( aveXtalRtOOTStcTime1 );
                            fOutAveXtalRtOOTStcRecTime2E1MapEB->Fill( idinfo.i2, idinfo.i1, aveXtalRtOOTStcTime1 + offset );
                    } else if( idinfo.ecal == ECAL::EP ){
			   //std::cout << "EP" << std::endl;
                            fOutAveXtalRtOOTStcRecTime2E1HistEP->Fill( aveXtalRtOOTStcTime1 );
                            fOutAveXtalRtOOTStcRecTime2E1MapEP->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime1 + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
		           //std::cout << "EM" << std::endl;
                            fOutAveXtalRtOOTStcRecTime2E1HistEM->Fill( aveXtalRtOOTStcTime1 );
                            fOutAveXtalRtOOTStcRecTime2E1MapEM->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime1 + offset );
                    }
          }
          for( std::map<UInt_t,Float_t>::iterator it=sumXtalRtOOTStcRecTime4E1.begin(); it!=sumXtalRtOOTStcRecTime4E1.end(); ++it){
                    const auto & idinfo = Common::DetIDMap[it->first];
                    const auto & aveXtalRtOOTStcTime1 = (sumXtalRtOOTStcRecTime4E1[it->first])/(numXtalRtOOTStcRecTime4E1[it->first]);
                    //std::cout << "Filling fOutAveXtalRtOOTStcRecTime4E1 " << it->first << " with " << it->second << " / " << numXtalRtOOTStcRecTime[it->first] << std::endl;
                    if( idinfo.ecal == ECAL::EB ){
                            fOutAveXtalRtOOTStcRecTime4E1HistEB->Fill( aveXtalRtOOTStcTime1 );
                            fOutAveXtalRtOOTStcRecTime4E1MapEB->Fill( idinfo.i2, idinfo.i1, aveXtalRtOOTStcTime1 + offset );
                    } else if( idinfo.ecal == ECAL::EP ){
                            fOutAveXtalRtOOTStcRecTime4E1HistEP->Fill( aveXtalRtOOTStcTime1 );
                            fOutAveXtalRtOOTStcRecTime4E1MapEP->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime1 + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
                            fOutAveXtalRtOOTStcRecTime4E1HistEM->Fill( aveXtalRtOOTStcTime1 );
                            fOutAveXtalRtOOTStcRecTime4E1MapEM->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime1 + offset );
                    }
          }
          for( std::map<UInt_t,Float_t>::iterator it=sumXtalRtOOTStcRecTimeE2.begin(); it!=sumXtalRtOOTStcRecTimeE2.end(); ++it){
                    const auto & idinfo = Common::DetIDMap[it->first];
                    const auto & aveXtalRtOOTStcTime2 = (sumXtalRtOOTStcRecTimeE2[it->first])/(numXtalRtOOTStcRecTimeE2[it->first]);
                    //std::cout << "Filling fOutAveXtalRtOOTStcRecTimeE2 " << it->first << " with " << it->second << " / " << numXtalRtOOTStcRecTime[it->first] << std::endl;
                    if( idinfo.ecal == ECAL::EB ){
                            fOutAveXtalRtOOTStcRecTimeE2HistEB->Fill( aveXtalRtOOTStcTime2 );
                            fOutAveXtalRtOOTStcRecTimeE2MapEB->Fill( idinfo.i2, idinfo.i1, aveXtalRtOOTStcTime2 + offset );
                    } else if( idinfo.ecal == ECAL::EP ){
                            fOutAveXtalRtOOTStcRecTimeE2HistEP->Fill( aveXtalRtOOTStcTime2 );
                            fOutAveXtalRtOOTStcRecTimeE2MapEP->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime2 + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
                            fOutAveXtalRtOOTStcRecTimeE2HistEM->Fill( aveXtalRtOOTStcTime2 );
                            fOutAveXtalRtOOTStcRecTimeE2MapEM->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime2 + offset );
                    }
          }
          for( std::map<UInt_t,Float_t>::iterator it=sumXtalRtOOTStcRecTimeE5.begin(); it!=sumXtalRtOOTStcRecTimeE5.end(); ++it){
                    const auto & idinfo = Common::DetIDMap[it->first];
                    const auto & aveXtalRtOOTStcTime5 = (sumXtalRtOOTStcRecTimeE5[it->first])/(numXtalRtOOTStcRecTimeE5[it->first]);
                    //std::cout << "Filling fOutAveXtalRtOOTStcRecTimeE5Hist " << it->first << " with " << it->second << " / " << numXtalRtOOTStcRecTime[it->first] << std::endl;
                    if( idinfo.ecal == ECAL::EB ){
                            fOutAveXtalRtOOTStcRecTimeE5HistEB->Fill( aveXtalRtOOTStcTime5 );
                            fOutAveXtalRtOOTStcRecTimeE5MapEB->Fill( idinfo.i2, idinfo.i1, aveXtalRtOOTStcTime5 + offset );
                    } else if( idinfo.ecal == ECAL::EP ){
                            fOutAveXtalRtOOTStcRecTimeE5HistEP->Fill( aveXtalRtOOTStcTime5 );
                            fOutAveXtalRtOOTStcRecTimeE5MapEP->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime5 + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
                            fOutAveXtalRtOOTStcRecTimeE5HistEM->Fill( aveXtalRtOOTStcTime5 );
                            fOutAveXtalRtOOTStcRecTimeE5MapEM->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime5 + offset );
                    }
          }
          for( std::map<UInt_t,Float_t>::iterator it=sumXtalRtStcRecTimeE5.begin(); it!=sumXtalRtStcRecTimeE5.end(); ++it){
                    const auto & idinfo = Common::DetIDMap[it->first];
                    const auto & aveXtalRtStcTime5 = (sumXtalRtStcRecTimeE5[it->first])/(numXtalRtOOTStcRecTimeE5[it->first]);
                    //std::cout << "Filling fOutAveXtalRtStcRecTimeE5Map " << it->first << " with " << it->second << " / " << numXtalRtOOTStcRecTimeE5[it->first] << std::endl;
                    if( idinfo.ecal == ECAL::EB ){
                            //fOutAveXtalRtStcRecTimeE5HistEB->Fill( aveXtalRtStcTime5 );
                            fOutAveXtalRtStcRecTimeE5MapEB->Fill( idinfo.i2, idinfo.i1, aveXtalRtStcTime5 + offset );
                    } else if( idinfo.ecal == ECAL::EP ){
                            //fOutAveXtalRtStcRecTimeE5HistEP->Fill( aveXtalRtStcTime5 );
                            fOutAveXtalRtStcRecTimeE5MapEP->Fill( idinfo.i1, idinfo.i2, aveXtalRtStcTime5 + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
                            //fOutAveXtalRtStcRecTimeE5HistEM->Fill( aveXtalRtStcTime5 );
                            fOutAveXtalRtStcRecTimeE5MapEM->Fill( idinfo.i1, idinfo.i2, aveXtalRtStcTime5 + offset );
                    }
          }
          for( std::map<UInt_t,Float_t>::iterator it=sumXtalWtOOTStcRecTimeE5.begin(); it!=sumXtalWtOOTStcRecTimeE5.end(); ++it){
                    const auto & idinfo = Common::DetIDMap[it->first];
                    const auto & aveXtalWtOOTStcTime5 = (sumXtalWtOOTStcRecTimeE5[it->first])/(numXtalRtOOTStcRecTimeE5[it->first]);
                    //std::cout << "Filling fOutAveXtalWtOOTStcRecTimeE5Map " << it->first << " with " << it->second << " / " << numXtalRtOOTStcRecTimeE5[it->first] << std::endl;
                    if( idinfo.ecal == ECAL::EB ){
                            //fOutAveXtalWtOOTStcRecTimeE5HistEB->Fill( aveXtalWtOOTStcTime5 );
                            fOutAveXtalWtOOTStcRecTimeE5MapEB->Fill( idinfo.i2, idinfo.i1, aveXtalWtOOTStcTime5 + offset );
                    } else if( idinfo.ecal == ECAL::EP ){
                            //fOutAveXtalWtOOTStcRecTimeE5HistEP->Fill( aveXtalWtOOTStcTime5 );
                            fOutAveXtalWtOOTStcRecTimeE5MapEP->Fill( idinfo.i1, idinfo.i2, aveXtalWtOOTStcTime5 + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
                            //fOutAveXtalWtOOTStcRecTimeE5HistEM->Fill( aveXtalWtOOTStcTime5 );
                            fOutAveXtalWtOOTStcRecTimeE5MapEM->Fill( idinfo.i1, idinfo.i2, aveXtalWtOOTStcTime5 + offset );
                    }
          }
          for( std::map<UInt_t,Float_t>::iterator it=sumXtalRtOOTStcRecTime2E5.begin(); it!=sumXtalRtOOTStcRecTime2E5.end(); ++it){
                    const auto & idinfo = Common::DetIDMap[it->first];
                    const auto & aveXtalRtOOTStcTime1 = (sumXtalRtOOTStcRecTime2E5[it->first])/(numXtalRtOOTStcRecTime2E5[it->first]);
           //        //std::cout << "Filling fOutAveXtalRtOOTStcRecTime2E5Map " << it->first << " with " << it->second << " / " << numXtalRtOOTStcRecTime[it->first] << std::endl;
                    if( idinfo.ecal == ECAL::EB ){
                            fOutAveXtalRtOOTStcRecTime2E5HistEB->Fill( aveXtalRtOOTStcTime1 );
                            fOutAveXtalRtOOTStcRecTime2E5MapEB->Fill( idinfo.i2, idinfo.i1, aveXtalRtOOTStcTime1 + offset );
                    } else if( idinfo.ecal == ECAL::EP ){
                            fOutAveXtalRtOOTStcRecTime2E5HistEP->Fill( aveXtalRtOOTStcTime1 );
                            fOutAveXtalRtOOTStcRecTime2E5MapEP->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime1 + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
                            fOutAveXtalRtOOTStcRecTime2E5HistEM->Fill( aveXtalRtOOTStcTime1 );
                            fOutAveXtalRtOOTStcRecTime2E5MapEM->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime1 + offset );
                    }
          }
          for( std::map<UInt_t,Float_t>::iterator it=sumXtalRtOOTStcRecTime4E5.begin(); it!=sumXtalRtOOTStcRecTime4E5.end(); ++it){
                    const auto & idinfo = Common::DetIDMap[it->first];
                    const auto & aveXtalRtOOTStcTime1 = (sumXtalRtOOTStcRecTime4E5[it->first])/(numXtalRtOOTStcRecTime4E5[it->first]);
           //        //std::cout << "Filling fOutAveXtalRtOOTStcRecTime4E5Hist " << it->first << " with " << it->second << " / " << numXtalRtOOTStcRecTime[it->first] << std::endl;
                    if( idinfo.ecal == ECAL::EB ){
                            fOutAveXtalRtOOTStcRecTime4E5HistEB->Fill( aveXtalRtOOTStcTime1 );
                            fOutAveXtalRtOOTStcRecTime4E5MapEB->Fill( idinfo.i2, idinfo.i1, aveXtalRtOOTStcTime1 + offset );
                    } else if( idinfo.ecal == ECAL::EP ){
                            fOutAveXtalRtOOTStcRecTime4E5HistEP->Fill( aveXtalRtOOTStcTime1 );
                            fOutAveXtalRtOOTStcRecTime4E5MapEP->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime1 + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
                            fOutAveXtalRtOOTStcRecTime4E5HistEM->Fill( aveXtalRtOOTStcTime1 );
                            fOutAveXtalRtOOTStcRecTime4E5MapEM->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime1 + offset );
                    }
          }
          for( std::map<UInt_t,Float_t>::iterator it=sumXtalRtOOTStcRecTimeE10.begin(); it!=sumXtalRtOOTStcRecTimeE10.end(); ++it){
                    const auto & idinfo = Common::DetIDMap[it->first];
                    const auto & aveXtalRtOOTStcTime10 = (sumXtalRtOOTStcRecTimeE10[it->first])/(numXtalRtOOTStcRecTimeE10[it->first]);
    //             //std::cout << "Filling " << it->first << " with " << it->second << " / " << numXtalRtOOTStcRecTime[it->first] << std::endl;
                    if( idinfo.ecal == ECAL::EB ){
                            fOutAveXtalRtOOTStcRecTimeE10HistEB->Fill( aveXtalRtOOTStcTime10 );
                            fOutAveXtalRtOOTStcRecTimeE10MapEB->Fill( idinfo.i2, idinfo.i1, aveXtalRtOOTStcTime10 + offset );
                    } else if( idinfo.ecal == ECAL::EP ){
                            fOutAveXtalRtOOTStcRecTimeE10HistEP->Fill( aveXtalRtOOTStcTime10 );
                            fOutAveXtalRtOOTStcRecTimeE10MapEP->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime10 + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
                            fOutAveXtalRtOOTStcRecTimeE10HistEM->Fill( aveXtalRtOOTStcTime10 );
                            fOutAveXtalRtOOTStcRecTimeE10MapEM->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime10 + offset );
                    }
          }
          for( std::map<UInt_t,Float_t>::iterator it=sumXtalRtOOTStcPhoClRecTime.begin(); it!=sumXtalRtOOTStcPhoClRecTime.end(); ++it){
                    const auto & idinfo = Common::DetIDMap[it->first];
                    const auto & aveXtalRtOOTStcTime = (sumXtalRtOOTStcPhoClRecTime[it->first])/(numXtalRtOOTStcPhoClRecTime[it->first]);
                 //std::cout << "Filling " << it->first << " with " << it->second << " / " << numXtalRtOOTStcPhoClRecTime[it->first] << std::endl;
                    if( idinfo.ecal == ECAL::EB ){
                            fOutAveXtalRtOOTStcPhoClRecTimeHistEB->Fill( aveXtalRtOOTStcTime );
                            fOutAveXtalRtOOTStcPhoClRecTimeMapEB->Fill( idinfo.i2, idinfo.i1, aveXtalRtOOTStcTime + offset );
                    } else if( idinfo.ecal == ECAL::EP ){
                            fOutAveXtalRtOOTStcPhoClRecTimeHistEP->Fill( aveXtalRtOOTStcTime );
                            fOutAveXtalRtOOTStcPhoClRecTimeMapEP->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
                            fOutAveXtalRtOOTStcPhoClRecTimeHistEM->Fill( aveXtalRtOOTStcTime );
                            fOutAveXtalRtOOTStcPhoClRecTimeMapEM->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime + offset );
                    }
	  }
          for( std::map<UInt_t,Float_t>::iterator it=sumXtalRtStcPhoClRecTime.begin(); it!=sumXtalRtStcPhoClRecTime.end(); ++it){
                    const auto & idinfo = Common::DetIDMap[it->first];
                    const auto & aveXtalRtStcTime = (sumXtalRtStcPhoClRecTime[it->first])/(numXtalRtOOTStcPhoClRecTime[it->first]);
                   //std::cout << "Filling fOutAveXtalRtStcPhoClRecTimeMap " << it->first << " with " << it->second << " / " << numXtalRtOOTStcPhoClRecTime[it->first] << std::endl;
                    if( idinfo.ecal == ECAL::EB ){
                            //fOutAveXtalRtStcPhoClRecTimeHistEB->Fill( aveXtalRtStcTime );
                            fOutAveXtalRtStcPhoClRecTimeMapEB->Fill( idinfo.i2, idinfo.i1, aveXtalRtStcTime + offset );
                    } else if( idinfo.ecal == ECAL::EP ){
                            //fOutAveXtalRtStcPhoClRecTimeHistEP->Fill( aveXtalRtStcTime );
                            fOutAveXtalRtStcPhoClRecTimeMapEP->Fill( idinfo.i1, idinfo.i2, aveXtalRtStcTime + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
                            //fOutAveXtalRtStcPhoClRecTimeHistEM->Fill( aveXtalRtStcTime );
                            fOutAveXtalRtStcPhoClRecTimeMapEM->Fill( idinfo.i1, idinfo.i2, aveXtalRtStcTime + offset );
                    }
          }
          for( std::map<UInt_t,Float_t>::iterator it=sumXtalWtOOTStcPhoClRecTime.begin(); it!=sumXtalWtOOTStcPhoClRecTime.end(); ++it){
                    const auto & idinfo = Common::DetIDMap[it->first];
                    const auto & aveXtalWtOOTStcTime = (sumXtalWtOOTStcPhoClRecTime[it->first])/(numXtalRtOOTStcPhoClRecTime[it->first]);
           // //std::cout << "Filling fOutAveXtalWtOOTStcPhoClRecTimeMapEB " << it->first << " with " << it->second << " / " << numXtalRtOOTStcPhoClRecTime[it->first] << std::endl;
                    if( idinfo.ecal == ECAL::EB ){
                            //fOutAveXtalWtOOTStcPhoClRecTimeHistEB->Fill( aveXtalWtOOTStcTime );
                            fOutAveXtalWtOOTStcPhoClRecTimeMapEB->Fill( idinfo.i2, idinfo.i1, aveXtalWtOOTStcTime + offset );
                    } else if( idinfo.ecal == ECAL::EP ){
                            //fOutAveXtalWtOOTStcPhoClRecTimeHistEP->Fill( aveXtalWtOOTStcTime );
                            fOutAveXtalWtOOTStcPhoClRecTimeMapEP->Fill( idinfo.i1, idinfo.i2, aveXtalWtOOTStcTime + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
                            //fOutAveXtalWtOOTStcPhoClRecTimeHistEM->Fill( aveXtalWtOOTStcTime );
                            fOutAveXtalWtOOTStcPhoClRecTimeMapEM->Fill( idinfo.i1, idinfo.i2, aveXtalWtOOTStcTime + offset );
                    }
          }
          for( std::map<UInt_t,Float_t>::iterator it=sumXtalRtOOTStcPhoIcRecTime.begin(); it!=sumXtalRtOOTStcPhoIcRecTime.end(); ++it){
                    const auto & idinfo = Common::DetIDMap[it->first];
                    const auto & aveXtalRtOOTStcTime = (sumXtalRtOOTStcPhoIcRecTime[it->first])/(numXtalRtOOTStcPhoIcRecTime[it->first]);
           // //std::cout << "Filling fOutAveXtalRtOOTStcPhoIcRecTimeMap " << it->first << " with " << it->second << " / " << numXtalRtOOTStcPhoIcRecTime[it->first] << std::endl;
                    if( idinfo.ecal == ECAL::EB ){
                            fOutAveXtalRtOOTStcPhoIcRecTimeHistEB->Fill( aveXtalRtOOTStcTime );
                            fOutAveXtalRtOOTStcPhoIcRecTimeMapEB->Fill( idinfo.i2, idinfo.i1, aveXtalRtOOTStcTime + offset );
                    } else if( idinfo.ecal == ECAL::EP ){
                            fOutAveXtalRtOOTStcPhoIcRecTimeHistEP->Fill( aveXtalRtOOTStcTime );
                            fOutAveXtalRtOOTStcPhoIcRecTimeMapEP->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
                            fOutAveXtalRtOOTStcPhoIcRecTimeHistEM->Fill( aveXtalRtOOTStcTime );
                            fOutAveXtalRtOOTStcPhoIcRecTimeMapEM->Fill( idinfo.i1, idinfo.i2, aveXtalRtOOTStcTime + offset );
                    }
	  }
          for( std::map<UInt_t,Float_t>::iterator it=sumXtalRtStcPhoIcRecTime.begin(); it!=sumXtalRtStcPhoIcRecTime.end(); ++it){
                    const auto & idinfo = Common::DetIDMap[it->first];
                    const auto & aveXtalRtStcTime = (sumXtalRtStcPhoIcRecTime[it->first])/(numXtalRtOOTStcPhoIcRecTime[it->first]);
           //   //std::cout << "Filling fOutAveXtalRtStcPhoIcRecTimeMap " << it->first << " with " << it->second << " / " << numXtalRtOOTStcPhoIcRecTime[it->first] << std::endl;
                    if( idinfo.ecal == ECAL::EB ){
                            //fOutAveXtalRtStcPhoIcRecTimeHistEB->Fill( aveXtalRtStcTime );
                            fOutAveXtalRtStcPhoIcRecTimeMapEB->Fill( idinfo.i2, idinfo.i1, aveXtalRtStcTime + offset );
                    } else if( idinfo.ecal == ECAL::EP ){
                            //fOutAveXtalRtStcPhoIcRecTimeHistEP->Fill( aveXtalRtStcTime );
                            fOutAveXtalRtStcPhoIcRecTimeMapEP->Fill( idinfo.i1, idinfo.i2, aveXtalRtStcTime + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
                            //fOutAveXtalRtStcPhoIcRecTimeHistEM->Fill( aveXtalRtStcTime );
                            fOutAveXtalRtStcPhoIcRecTimeMapEM->Fill( idinfo.i1, idinfo.i2, aveXtalRtStcTime + offset );
                    }
          }
          for( std::map<UInt_t,Float_t>::iterator it=sumXtalWtOOTStcPhoIcRecTime.begin(); it!=sumXtalWtOOTStcPhoIcRecTime.end(); ++it){
                    const auto & idinfo = Common::DetIDMap[it->first];
                    const auto & aveXtalWtOOTStcTime = (sumXtalWtOOTStcPhoIcRecTime[it->first])/(numXtalRtOOTStcPhoIcRecTime[it->first]);
             // //std::cout << "Filling fOutAveXtalWtOOTStcPhoIcRecTimeMap " << it->first << " with " << it->second << " / " << numXtalRtOOTStcPhoIcRecTime[it->first] << std::endl;
                    if( idinfo.ecal == ECAL::EB ){
                            //fOutAveXtalWtOOTStcPhoIcRecTimeHistEB->Fill( aveXtalWtOOTStcTime );
                            fOutAveXtalWtOOTStcPhoIcRecTimeMapEB->Fill( idinfo.i2, idinfo.i1, aveXtalWtOOTStcTime + offset );
                    } else if( idinfo.ecal == ECAL::EP ){
                            //fOutAveXtalWtOOTStcPhoIcRecTimeHistEP->Fill( aveXtalWtOOTStcTime );
                            fOutAveXtalWtOOTStcPhoIcRecTimeMapEP->Fill( idinfo.i1, idinfo.i2, aveXtalWtOOTStcTime + offset );
                    } else if( idinfo.ecal == ECAL::EM ){
                            //fOutAveXtalWtOOTStcPhoIcRecTimeHistEM->Fill( aveXtalWtOOTStcTime );
                            fOutAveXtalWtOOTStcPhoIcRecTimeMapEM->Fill( idinfo.i1, idinfo.i2, aveXtalWtOOTStcTime + offset );
                    }
          }
        }
 // }
  
  // write out the output
 //std::cout << "write out the output!"<< std::endl;
  fOutFile->cd();
  fOutCutFlow->Write();
  fOutCutFlowWgt->Write();
  fOutCutFlowScl->Write();

  tofHist->Write();
 //std::cout << "write out the output!"<< std::endl;
  fOutAveXtalRecTimeHist->Write();
  fOutAveXtalOccHist->Write();
  fOutAveXtalRecTimeHistEB->Write();
  fOutAveXtalRecTimeHistEP->Write();
  fOutAveXtalRecTimeHistEM->Write();
  fOutAveXtalOccHistEB->Write();
  fOutAveXtalOccHistEP->Write();
  fOutAveXtalOccHistEM->Write();
  fOutAveXtalRecTimeMapEB->Write();
  fOutAveXtalRecTimeMapEP->Write();
  fOutAveXtalRecTimeMapEM->Write();
  fOutAveXtalOccMapEB->Write();
  fOutAveXtalOccMapEP->Write();
  fOutAveXtalOccMapEM->Write();

 //std::cout << "write out the output!"<< std::endl;
  fOutAveXtalPhoRecTimeHist->Write();
  fOutAveXtalPhoOccHist->Write();
  fOutAveXtalPhoRecTimeHistEB->Write();
  fOutAveXtalPhoRecTimeHistEP->Write();
  fOutAveXtalPhoRecTimeHistEM->Write();
  fOutAveXtalPhoOccHistEB->Write();
  fOutAveXtalPhoOccHistEP->Write();
  fOutAveXtalPhoOccHistEM->Write();
  fOutAveXtalPhoRecTimeMapEB->Write();
  fOutAveXtalPhoRecTimeMapEP->Write();
  fOutAveXtalPhoRecTimeMapEM->Write();
  fOutAveXtalPhoOccMapEB->Write();
  fOutAveXtalPhoOccMapEP->Write();
  fOutAveXtalPhoOccMapEM->Write();

  fOutAveXtalRtPhoRecTimeHist->Write();
  fOutAveXtalRtPhoRecTimeHistEB->Write();
  fOutAveXtalRtPhoRecTimeHistEP->Write();
  fOutAveXtalRtPhoRecTimeHistEM->Write();
  fOutAveXtalRtPhoRecTimeMapEB->Write();
  fOutAveXtalRtPhoRecTimeMapEP->Write();
  fOutAveXtalRtPhoRecTimeMapEM->Write();

  fOutAveXtalRtStcPhoRecTimeHist->Write();
  fOutAveXtalRtStcPhoRecTimeHistEB->Write();
  fOutAveXtalRtStcPhoRecTimeHistEP->Write();
  fOutAveXtalRtStcPhoRecTimeHistEM->Write();
  fOutAveXtalRtStcPhoRecTimeMapEB->Write();
  fOutAveXtalRtStcPhoRecTimeMapEP->Write();
  fOutAveXtalRtStcPhoRecTimeMapEM->Write();

  //fOutAveXtalRtOOTPhoRecTimeHist->Write();
  //fOutAveXtalRtOOTPhoRecTimeHistEB->Write();
  //fOutAveXtalRtOOTPhoRecTimeHistEP->Write();
  //fOutAveXtalRtOOTPhoRecTimeHistEM->Write();
  //fOutAveXtalRtOOTPhoRecTimeMapEB->Write();
  //fOutAveXtalRtOOTPhoRecTimeMapEP->Write();
  //fOutAveXtalRtOOTPhoRecTimeMapEM->Write();

  fOutAveXtalRtOOTStcPhoRecTimeHist->Write();
  fOutAveXtalRtOOTStcPhoRecTimeHistEB->Write();
  fOutAveXtalRtOOTStcPhoRecTimeHistEP->Write();
  fOutAveXtalRtOOTStcPhoRecTimeHistEM->Write();
  fOutAveXtalRtOOTStcPhoRecTimeMapEB->Write();
  fOutAveXtalRtOOTStcPhoRecTimeMapEP->Write();
  fOutAveXtalRtOOTStcPhoRecTimeMapEM->Write();

 //std::cout << "write out the output!"<< std::endl;
  fOutDifXtalPhoRecTimeHist->Write();
  fOutDifXtalPhoRecTimeHistEB->Write();
  fOutDifXtalPhoRecTimeHistEP->Write();
  fOutDifXtalPhoRecTimeHistEM->Write();
  fOutDifXtalPhoRecTimeMapEB->Write();
  fOutDifXtalPhoRecTimeMapEP->Write();
  fOutDifXtalPhoRecTimeMapEM->Write();

  fOutDifXtalRtPhoRecTimeHist->Write();
  fOutDifXtalRtPhoRecTimeHistEB->Write();
  fOutDifXtalRtPhoRecTimeHistEP->Write();
  fOutDifXtalRtPhoRecTimeHistEM->Write();
  fOutDifXtalRtPhoRecTimeMapEB->Write();
  fOutDifXtalRtPhoRecTimeMapEP->Write();
  fOutDifXtalRtPhoRecTimeMapEM->Write();

  fOutDifXtalRtStcPhoRecTimeHist->Write();
  fOutDifXtalRtStcPhoRecTimeHistEB->Write();
  fOutDifXtalRtStcPhoRecTimeHistEP->Write();
  fOutDifXtalRtStcPhoRecTimeHistEM->Write();
  fOutDifXtalRtStcPhoRecTimeMapEB->Write();
  fOutDifXtalRtStcPhoRecTimeMapEP->Write();
  fOutDifXtalRtStcPhoRecTimeMapEM->Write();

  //fOutDifXtalRtOOTPhoRecTimeHist->Write();
  //fOutDifXtalRtOOTPhoRecTimeHistEB->Write();
  //fOutDifXtalRtOOTPhoRecTimeHistEP->Write();
  //fOutDifXtalRtOOTPhoRecTimeHistEM->Write();
  //fOutDifXtalRtOOTPhoRecTimeMapEB->Write();
  //fOutDifXtalRtOOTPhoRecTimeMapEP->Write();
  //fOutDifXtalRtOOTPhoRecTimeMapEM->Write();

  fOutDifXtalRtOOTStcPhoRecTimeHist->Write();
  fOutDifXtalRtOOTStcPhoRecTimeHistEB->Write();
  fOutDifXtalRtOOTStcPhoRecTimeHistEP->Write();
  fOutDifXtalRtOOTStcPhoRecTimeHistEM->Write();
  fOutDifXtalRtOOTStcPhoRecTimeMapEB->Write();
  fOutDifXtalRtOOTStcPhoRecTimeMapEP->Write();
  fOutDifXtalRtOOTStcPhoRecTimeMapEM->Write();

  fOutAveXtalRtOOTStcRecTimeHistEB->Write();
  fOutAveXtalRtOOTStcRecTimeMapEB->Write();
  fOutAveXtalRtOOTStcRecTimeHistEP->Write();
  fOutAveXtalRtOOTStcRecTimeMapEP->Write();
  fOutAveXtalRtOOTStcRecTimeHistEM->Write();
  fOutAveXtalRtOOTStcRecTimeMapEM->Write();

  fOutAveXtalRtOOTStcRecTimeE0HistEB->Write();
  fOutAveXtalRtOOTStcRecTimeE0MapEB->Write();
  fOutAveXtalRtOOTStcRecTimeE0HistEP->Write();
  fOutAveXtalRtOOTStcRecTimeE0MapEP->Write();
  fOutAveXtalRtOOTStcRecTimeE0HistEM->Write();
  fOutAveXtalRtOOTStcRecTimeE0MapEM->Write();

  fOutAveXtalRtOOTStcRecTimeE1HistEB->Write();
  fOutAveXtalRtOOTStcRecTimeE1MapEB->Write();
  fOutAveXtalRtOOTStcRecTimeE1HistEP->Write();
  fOutAveXtalRtOOTStcRecTimeE1MapEP->Write();
  fOutAveXtalRtOOTStcRecTimeE1HistEM->Write();
  fOutAveXtalRtOOTStcRecTimeE1MapEM->Write();

  fOutAveXtalRtOOTStcRecTime2E1HistEB->Write();
  fOutAveXtalRtOOTStcRecTime2E1MapEB->Write();
  fOutAveXtalRtOOTStcRecTime2E1HistEP->Write();
  fOutAveXtalRtOOTStcRecTime2E1MapEP->Write();
  fOutAveXtalRtOOTStcRecTime2E1HistEM->Write();
  fOutAveXtalRtOOTStcRecTime2E1MapEM->Write();

  fOutAveXtalRtOOTStcRecTime4E1HistEB->Write();
  fOutAveXtalRtOOTStcRecTime4E1MapEB->Write();
  fOutAveXtalRtOOTStcRecTime4E1HistEP->Write();
  fOutAveXtalRtOOTStcRecTime4E1MapEP->Write();
  fOutAveXtalRtOOTStcRecTime4E1HistEM->Write();
  fOutAveXtalRtOOTStcRecTime4E1MapEM->Write();

  fOutAveXtalRtOOTStcRecTimeE2HistEB->Write();
  fOutAveXtalRtOOTStcRecTimeE2MapEB->Write();
  fOutAveXtalRtOOTStcRecTimeE2HistEP->Write();
  fOutAveXtalRtOOTStcRecTimeE2MapEP->Write();
  fOutAveXtalRtOOTStcRecTimeE2HistEM->Write();
  fOutAveXtalRtOOTStcRecTimeE2MapEM->Write();

  fOutAveXtalRtOOTStcRecTimeE5HistEB->Write();
  fOutAveXtalRtOOTStcRecTimeE5MapEB->Write();
  fOutAveXtalRtOOTStcRecTimeE5HistEP->Write();
  fOutAveXtalRtOOTStcRecTimeE5MapEP->Write();
  fOutAveXtalRtOOTStcRecTimeE5HistEM->Write();
  fOutAveXtalRtOOTStcRecTimeE5MapEM->Write();

  fOutAveXtalRtStcRecTimeE5MapEB->Write();
  fOutAveXtalRtStcRecTimeE5MapEP->Write();
  fOutAveXtalRtStcRecTimeE5MapEM->Write();

  fOutAveXtalWtOOTStcRecTimeE5MapEB->Write();
  fOutAveXtalWtOOTStcRecTimeE5MapEP->Write();
  fOutAveXtalWtOOTStcRecTimeE5MapEM->Write();

  fOutAveXtalRtOOTStcRecTime2E5HistEB->Write();
  fOutAveXtalRtOOTStcRecTime2E5MapEB->Write();
  fOutAveXtalRtOOTStcRecTime2E5HistEP->Write();
  fOutAveXtalRtOOTStcRecTime2E5MapEP->Write();
  fOutAveXtalRtOOTStcRecTime2E5HistEM->Write();
  fOutAveXtalRtOOTStcRecTime2E5MapEM->Write();

  fOutAveXtalRtOOTStcRecTime4E5HistEB->Write();
  fOutAveXtalRtOOTStcRecTime4E5MapEB->Write();
  fOutAveXtalRtOOTStcRecTime4E5HistEP->Write();
  fOutAveXtalRtOOTStcRecTime4E5MapEP->Write();
  fOutAveXtalRtOOTStcRecTime4E5HistEM->Write();
  fOutAveXtalRtOOTStcRecTime4E5MapEM->Write();

  fOutAveXtalRtOOTStcRecTimeE10HistEB->Write();
  fOutAveXtalRtOOTStcRecTimeE10MapEB->Write();
  fOutAveXtalRtOOTStcRecTimeE10HistEP->Write();
  fOutAveXtalRtOOTStcRecTimeE10MapEP->Write();
  fOutAveXtalRtOOTStcRecTimeE10HistEM->Write();
  fOutAveXtalRtOOTStcRecTimeE10MapEM->Write();

  fOutAveXtalRtOOTStcPhoClRecTimeHistEB->Write();
  fOutAveXtalRtOOTStcPhoClRecTimeHistEP->Write();
  fOutAveXtalRtOOTStcPhoClRecTimeHistEM->Write();

  fOutAveXtalRtOOTStcPhoIcRecTimeHistEB->Write();
  fOutAveXtalRtOOTStcPhoIcRecTimeHistEP->Write();
  fOutAveXtalRtOOTStcPhoIcRecTimeHistEM->Write();

  fOutAveXtalRtOOTStcPhoClRecTimeMapEB->Write();
  fOutAveXtalRtOOTStcPhoClRecTimeMapEP->Write();
  fOutAveXtalRtOOTStcPhoClRecTimeMapEM->Write();

  fOutAveXtalRtOOTStcPhoIcRecTimeMapEB->Write();
  fOutAveXtalRtOOTStcPhoIcRecTimeMapEP->Write();
  fOutAveXtalRtOOTStcPhoIcRecTimeMapEM->Write();

  fOutAveXtalRtStcPhoClRecTimeMapEB->Write();
  fOutAveXtalRtStcPhoClRecTimeMapEP->Write();
  fOutAveXtalRtStcPhoClRecTimeMapEM->Write();

  fOutAveXtalRtStcPhoIcRecTimeMapEB->Write();
  fOutAveXtalRtStcPhoIcRecTimeMapEP->Write();
  fOutAveXtalRtStcPhoIcRecTimeMapEM->Write();

  fOutAveXtalWtOOTStcPhoClRecTimeMapEB->Write();
  fOutAveXtalWtOOTStcPhoClRecTimeMapEP->Write();
  fOutAveXtalWtOOTStcPhoClRecTimeMapEM->Write();

  fOutAveXtalWtOOTStcPhoIcRecTimeMapEB->Write();
  fOutAveXtalWtOOTStcPhoIcRecTimeMapEP->Write();
  fOutAveXtalWtOOTStcPhoIcRecTimeMapEM->Write();

 //std::cout << "write out the output!"<< std::endl;
  fOutConfigTree->Write();
  fOutTree->Write();
}

void Skimmer::FillOutGMSBs(const UInt_t entry)
{
  // get input branches

  // set output branches
}

void Skimmer::FillOutHVDSs(const UInt_t entry)
{
  // get input branches

  // set output branches
}

void Skimmer::FillOutToys(const UInt_t entry)
{
  // get input branches

  // set output branches
}

void Skimmer::FillOutEvent(const UInt_t entry, const Float_t evtwgt)
{
 //std::cout << "Starting FillOutEvent" << std::endl;
 // get input branches
  fInEvent.b_run->GetEntry(entry);
  fInEvent.b_lumi->GetEntry(entry);
  fInEvent.b_event->GetEntry(entry);
  fInEvent.b_hltSignal->GetEntry(entry);
  fInEvent.b_hltRefPhoID->GetEntry(entry);
  fInEvent.b_hltRefDispID->GetEntry(entry);
  fInEvent.b_hltRefHT->GetEntry(entry);
  fInEvent.b_hltPho50->GetEntry(entry);
  fInEvent.b_hltPho200->GetEntry(entry);
  fInEvent.b_hltDiPho70->GetEntry(entry);
  fInEvent.b_hltDiPho3022M90->GetEntry(entry);
  fInEvent.b_hltDiPho30PV18PV->GetEntry(entry);
  fInEvent.b_hltEle32WPT->GetEntry(entry);
  fInEvent.b_hltDiEle33MW->GetEntry(entry);
  fInEvent.b_hltJet500->GetEntry(entry);
  fInEvent.b_nvtx->GetEntry(entry);
  fInEvent.b_vtxX->GetEntry(entry);
  fInEvent.b_vtxY->GetEntry(entry);
  fInEvent.b_vtxZ->GetEntry(entry);
  fInEvent.b_rho->GetEntry(entry);
  // fInEvent.b_nmuHighT->GetEntry(entry);
  fInEvent.b_nrechits->GetEntry(entry);
  fInEvent.b_nkurechits->GetEntry(entry);
  //if( hasMultiKURecHit ){
  //b_nkuStcrechits->GetEntry(entry);
  //b_nkuNotrechits->GetEntry(entry);
  //b_nkuNotStcrechits->GetEntry(entry);
 // }
  fInEvent.b_nphotons->GetEntry(entry);

 //std::cout << "clearing UncalDigi " << std::endl;

  nurechits = 0;
  ndigis = 0;

   bunch_crossing = 0;
   num_bunch = 0;
   subtrain_position=0;
   train_position=0;
   subtrain_number=0;
   train_number=0;
   
   if( isLHCInfo ) {
   b_bunch_crossing->GetEntry(entry);   //!
   b_num_bunch->GetEntry(entry);   //!

   b_subtrain_position->GetEntry(entry);   //!
   b_train_position->GetEntry(entry);   //!
   b_subtrain_number->GetEntry(entry);   //!
   b_train_number->GetEntry(entry);   //!
   }

 ////std::cout << "lhcinfo done" << std::endl;
  // isMC only conditions
  fOutEvent.run = fInEvent.run;
  fOutEvent.lumi = fInEvent.lumi;
  fOutEvent.event = fInEvent.event;
  fOutEvent.hltSignal = fInEvent.hltSignal;
  fOutEvent.hltRefPhoID = fInEvent.hltRefPhoID;
  fOutEvent.hltRefDispID = fInEvent.hltRefDispID;
  fOutEvent.hltRefHT = fInEvent.hltRefHT;
  fOutEvent.hltPho50 = fInEvent.hltPho50;
  fOutEvent.hltPho200 = fInEvent.hltPho200;
  fOutEvent.hltDiPho70 = fInEvent.hltDiPho70;
  fOutEvent.hltDiPho3022M90 = fInEvent.hltDiPho3022M90;
  fOutEvent.hltDiPho30PV18PV = fInEvent.hltDiPho30PV18PV;
  fOutEvent.hltEle32WPT = fInEvent.hltEle32WPT;
  fOutEvent.hltDiEle33MW = fInEvent.hltDiEle33MW;
  fOutEvent.hltJet500 = fInEvent.hltJet500;
  fOutEvent.nvtx = fInEvent.nvtx;
  fOutEvent.vtxX = fInEvent.vtxX;
  fOutEvent.vtxY = fInEvent.vtxY;
  fOutEvent.vtxZ = fInEvent.vtxZ;
  fOutEvent.rho = fInEvent.rho;
  
  // fOutEvent.nmuHighT = fInEvent.nmuHighT;
  fOutEvent.nrechits = fInEvent.nrechits;
  fOutEvent.nkurechits = fInEvent.nkurechits;
  //if( hasMultiKURecHit ){
  //fOutEvent.nkuStcrechits = fInEvent.nkuStcrechits;
  //fOutEvent.nkuNotrechits = fInEvent.nkuNotrechits;
  //fOutEvent.nkuNotStcrechits = fInEvent.nkuNotStcrechits;
  //}
  fOutEvent.nphotons = fInEvent.nphotons;
  fOutEvent.evtwgt   = evtwgt;


 //std::cout << "event info done" << std::endl;

  // isMC only branches
}

void Skimmer::FillOutJets(const UInt_t entry)
{
  fInJets.b_E->GetEntry(entry);
  fInJets.b_pt->GetEntry(entry);
  fInJets.b_phi->GetEntry(entry);
  fInJets.b_eta->GetEntry(entry);
  fInJets.b_ID->GetEntry(entry);

  // fInJets.b_NHF->GetEntry(entry);
  // fInJets.b_NEMF->GetEntry(entry);
  // fInJets.b_CHF->GetEntry(entry);
  // fInJets.b_CEMF->GetEntry(entry);
  // fInJets.b_MUF->GetEntry(entry);
  // fInJets.b_NHM->GetEntry(entry);
  // fInJets.b_CHM->GetEntry(entry);

  const UInt_t nJets = fInJets.E->size();

  // resize outputs
  fOutJets.E_f.resize(nJets);
  fOutJets.pt_f.resize(nJets);
  fOutJets.phi_f.resize(nJets);
  fOutJets.eta_f.resize(nJets);
  fOutJets.ID_i.resize(nJets);

  // fOutJets.NHF_f.resize(nJets);
  // fOutJets.NEMF_f.resize(nJets);
  // fOutJets.CHF_f.resize(nJets);
  // fOutJets.CEMF_f.resize(nJets);
  // fOutJets.MUF_f.resize(nJets);
  // fOutJets.NHM_f.resize(nJets);
  // fOutJets.CHM_f.resize(nJets);

  // copy in: non-ideal (swap won't work, as we need the input values for MET corrections)
  for (auto ijet = 0U; ijet < nJets; ijet++)
  {
    fOutJets.E_f[ijet] = (*fInJets.E)[ijet];
    fOutJets.pt_f[ijet] = (*fInJets.pt)[ijet];
    fOutJets.phi_f[ijet] = (*fInJets.phi)[ijet];
    fOutJets.eta_f[ijet] = (*fInJets.eta)[ijet];
    fOutJets.ID_i[ijet] = (*fInJets.ID)[ijet];
    
    // fOutJets.NHF_f[ijet] = (*fInJets.NHF)[ijet];
    // fOutJets.NEMF_f[ijet] = (*fInJets.NEMF)[ijet];
    // fOutJets.CHF_f[ijet] = (*fInJets.CHF)[ijet];
    // fOutJets.CEMF_f[ijet] = (*fInJets.CEMF)[ijet];
    // fOutJets.MUF_f[ijet] = (*fInJets.MUF)[ijet];
    // fOutJets.NHM_f[ijet] = (*fInJets.NHM)[ijet];
    // fOutJets.CHM_f[ijet] = (*fInJets.CHM)[ijet];
  }

  // apply energy corrections, then sort!

    /////////////////
    // sort by pt! //
    /////////////////

    // make list of indices, sort them by pt
    std::vector<UInt_t> ijets(nJets);
    std::iota(ijets.begin(),ijets.end(),0);
    std::sort(ijets.begin(),ijets.end(),
	      [&](const UInt_t ijet1, const UInt_t ijet2)
	      {
		return fOutJets.pt_f[ijet1]>fOutJets.pt_f[ijet2];
	      });
    
    // use reorder function to sort all the output
    Common::ReorderVector(fOutJets.E_f,ijets);
    Common::ReorderVector(fOutJets.pt_f,ijets);
    Common::ReorderVector(fOutJets.phi_f,ijets);
    Common::ReorderVector(fOutJets.eta_f,ijets);
    Common::ReorderVector(fOutJets.ID_i,ijets);
    
    // Common::ReorderVector(fOutJets.NHF_f,ijets);
 
}

void Skimmer::FillOutPhos(const UInt_t entry)
{  
  // get input photon branches
 //std::cout << "Starting get entry" << std::endl;
  for (auto ipho : fPhoList)
  {
    auto & inpho = fInPhos[ipho];
    
    inpho.b_E->GetEntry(entry);
    inpho.b_pt->GetEntry(entry);
    inpho.b_eta->GetEntry(entry);
    inpho.b_phi->GetEntry(entry);
    inpho.b_scE->GetEntry(entry);
    inpho.b_sceta->GetEntry(entry);
    inpho.b_scphi->GetEntry(entry);
    inpho.b_HoE->GetEntry(entry);
    inpho.b_r9->GetEntry(entry);
    if( hasUrecDigi ) inpho.b_tdz->GetEntry(entry);
    inpho.b_ChgHadIso->GetEntry(entry);
    inpho.b_NeuHadIso->GetEntry(entry);
    inpho.b_PhoIso->GetEntry(entry);
    inpho.b_EcalPFClIso->GetEntry(entry);
    inpho.b_HcalPFClIso->GetEntry(entry);
    inpho.b_TrkIso->GetEntry(entry);
    // inpho.b_ChgHadIsoC->GetEntry(entry);
    // inpho.b_NeuHadIsoC->GetEntry(entry);
    // inpho.b_PhoIsoC->GetEntry(entry);
    // inpho.b_EcalPFClIsoC->GetEntry(entry);
    // inpho.b_HcalPFClIsoC->GetEntry(entry);
    // inpho.b_TrkIsoC->GetEntry(entry);
    inpho.b_sieie->GetEntry(entry);
    // inpho.b_sipip->GetEntry(entry);
    // inpho.b_sieip->GetEntry(entry);
    // inpho.b_e2x2->GetEntry(entry);
    // inpho.b_e3x3->GetEntry(entry);
    // inpho.b_e5x5->GetEntry(entry);
    inpho.b_smaj->GetEntry(entry);
    inpho.b_smin->GetEntry(entry);
    // inpho.b_alpha->GetEntry(entry);
    inpho.b_suisseX->GetEntry(entry);
    inpho.b_isOOT->GetEntry(entry);
    inpho.b_isEB->GetEntry(entry);
    inpho.b_isHLT->GetEntry(entry);
    inpho.b_isTrk->GetEntry(entry);
    inpho.b_passEleVeto->GetEntry(entry);
    inpho.b_hasPixSeed->GetEntry(entry);
    inpho.b_gedID->GetEntry(entry);
    inpho.b_ootID->GetEntry(entry);

   //std::cout << "Finished Base Pho list" << std::endl;
    if (fInConfig.storeRecHits)
    {
      inpho.b_seed->GetEntry(entry);
      inpho.b_recHits->GetEntry(entry);
    }
    else
    {
      // inpho.b_seedX->GetEntry(entry);
      // inpho.b_seedY->GetEntry(entry);
      // inpho.b_seedZ->GetEntry(entry);
      inpho.b_seedE->GetEntry(entry);
      inpho.b_seedtime->GetEntry(entry);
      // inpho.b_seedtimeErr->GetEntry(entry);
      inpho.b_seedTOF->GetEntry(entry);
      inpho.b_seedID->GetEntry(entry);
      // inpho.b_seedisOOT->GetEntry(entry);
      inpho.b_seedisGS6->GetEntry(entry);
      inpho.b_seedisGS1->GetEntry(entry);
      inpho.b_seedped12->GetEntry(entry);
      inpho.b_seedped6->GetEntry(entry);
      inpho.b_seedped1->GetEntry(entry);
      inpho.b_seedpedrms12->GetEntry(entry);
      inpho.b_seedpedrms6->GetEntry(entry);
      inpho.b_seedpedrms1->GetEntry(entry);
    }
  }  
 //std::cout << "Finished Pho list" << std::endl;
  // get input recHits if needed
  if (fInConfig.storeRecHits)
  {
    // fInRecHits.b_X->GetEntry(entry);
    // fInRecHits.b_Y->GetEntry(entry);
    // fInRecHits.b_Z->GetEntry(entry);
    fInRecHits.b_E->GetEntry(entry);
    fInRecHits.b_time->GetEntry(entry);
    // fInRecHits.b_timeErr->GetEntry(entry);
    fInRecHits.b_TOF->GetEntry(entry);
    fInRecHits.b_ID->GetEntry(entry);
    // fInRecHits.b_isOOT->GetEntry(entry);
    fInRecHits.b_isGS6->GetEntry(entry);
    fInRecHits.b_isGS1->GetEntry(entry);
    fInRecHits.b_adcToGeV->GetEntry(entry);
    fInRecHits.b_ped12->GetEntry(entry);
    fInRecHits.b_ped6->GetEntry(entry);
    fInRecHits.b_ped1->GetEntry(entry);
    fInRecHits.b_pedrms12->GetEntry(entry);
    fInRecHits.b_pedrms6->GetEntry(entry);
    fInRecHits.b_pedrms1->GetEntry(entry);

  }

  //b_kurhE->GetEntry(entry);
  b_kurhtime->GetEntry(entry);
  b_kurhtimeErr->GetEntry(entry);
  //b_kurhTOF->GetEntry(entry);
  b_kurhID->GetEntry(entry);

  if( hasMultiKURecHit ){
  //b_kuStcrhE->GetEntry(entry);
  b_kuStcrhtime->GetEntry(entry);
  b_kuStcrhtimeErr->GetEntry(entry);
  //b_kuStcrhTOF->GetEntry(entry);
  b_kuStcrhID->GetEntry(entry);

  //b_kuNotrhE->GetEntry(entry);
  //b_kuNotrhtime->GetEntry(entry);
  //b_kuNotrhtimeErr->GetEntry(entry);
  //b_kuNotrhTOF->GetEntry(entry);
  //b_kuNotrhID->GetEntry(entry);

  //b_kuNotStcrhE->GetEntry(entry);
  b_kuNotStcrhtime->GetEntry(entry);
  b_kuNotStcrhtimeErr->GetEntry(entry);
  //b_kuNotStcrhTOF->GetEntry(entry);
  b_kuNotStcrhID->GetEntry(entry);

//  b_kuWootStcrhE->GetEntry(entry);
  b_kuWootStcrhtime->GetEntry(entry);
  b_kuWootStcrhtimeErr->GetEntry(entry);
//  b_kuWootStcrhTOF->GetEntry(entry);
  b_kuWootStcrhID->GetEntry(entry);

  }
        if( hasUrecDigi ){
               //std::cout << "Getting UrecDigi Info" << std::endl;
                b_uRhId->GetEntry(entry);
                b_ootA0->GetEntry(entry);
                b_ootA1->GetEntry(entry);
                b_ootA2->GetEntry(entry);
                b_ootA3->GetEntry(entry);
                b_ootA4->GetEntry(entry);
                b_ootA5->GetEntry(entry);
                b_ootA6->GetEntry(entry);
                b_ootA7->GetEntry(entry);
                b_ootA8->GetEntry(entry);
                b_ootA9->GetEntry(entry);
                b_ndigis->GetEntry(entry);
                b_nurechits->GetEntry(entry);
 //              //std::cout << "Filling ootAs" << std::endl;
        }
 
    out_npho_recHits_0 = (fInPhos[0]).recHits;
    out_npho_recHits_1 = (fInPhos[1]).recHits;
    out_npho_recHits_2 = (fInPhos[2]).recHits;
    out_npho_recHits_3 = (fInPhos[3]).recHits;
    out_fInRecHits_E = fInRecHits.E;
    out_fInRecHits_ID = fInRecHits.ID;
    out_fInRecHits_time = fInRecHits.time;
    out_fInRecHits_TOF = fInRecHits.TOF;
    out_kurhtime = kurhtime;
    out_kurhID = kurhID;
    out_kuStcrhtime = kuStcrhtime;
    //out_kuNotrhtime = kuNotrhtime;
    out_kuNotStcrhtime = kuNotStcrhtime;
    out_kuWootStcrhtime = kuWootStcrhtime;

 //std::cout << "Finished get entry" << std::endl;
  // set output photon branches
  for (auto ipho = 0; ipho < fNOutPhos; ipho++) 
  {
    const auto & inpho = fInPhos[fPhoList[ipho]];
    auto & outpho = fOutPhos[ipho];

    outpho.E = inpho.E;
    outpho.pt = inpho.pt;
    outpho.eta = inpho.eta;
    outpho.phi = inpho.phi;
    outpho.scE = inpho.scE;
    outpho.sceta = inpho.sceta;
    outpho.scphi = inpho.scphi;
    outpho.HoE = inpho.HoE;
    outpho.r9 = inpho.r9;
    if( hasUrecDigi ) outpho.tdz = inpho.tdz; 
    else outpho.tdz = 0.0;
    outpho.ChgHadIso = inpho.ChgHadIso;
    outpho.NeuHadIso = inpho.NeuHadIso;
    outpho.PhoIso = inpho.PhoIso;
    outpho.EcalPFClIso = inpho.EcalPFClIso;
    outpho.HcalPFClIso = inpho.HcalPFClIso;
    outpho.TrkIso = inpho.TrkIso;
    // outpho.ChgHadIsoC = inpho.ChgHadIsoC;
    // outpho.NeuHadIsoC = inpho.NeuHadIsoC;
    // outpho.PhoIsoC = inpho.PhoIsoC;
    // outpho.EcalPFClIsoC = inpho.EcalPFClIsoC;
    // outpho.HcalPFClIsoC = inpho.HcalPFClIsoC;
    // outpho.TrkIsoC = inpho.TrkIsoC;
    outpho.sieie = inpho.sieie;
    // outpho.sipip = inpho.sipip;
    // outpho.sieip = inpho.sieip;
    // outpho.e2x2 = inpho.e2x2;
    // outpho.e3x3 = inpho.e3x3;
    // outpho.e5x5 = inpho.e5x5;
    outpho.smaj = inpho.smaj;
    outpho.smin = inpho.smin;
    // outpho.alpha = inpho.alpha;
    outpho.suisseX = inpho.suisseX;
    outpho.isOOT = inpho.isOOT;
    outpho.isEB = inpho.isEB;
    outpho.isHLT = inpho.isHLT;
    outpho.isTrk = inpho.isTrk;
    outpho.passEleVeto = inpho.passEleVeto;
    outpho.hasPixSeed = inpho.hasPixSeed;
    outpho.gedID = inpho.gedID;
    outpho.ootID = inpho.ootID;

    if (fInConfig.storeRecHits)
    {
      // something unholy and utterly disgusting

      auto seed = inpho.seed;
      if( fSkim == SkimType::DiXtal and ipho < 2 ) seed = outpho.seed;
      //const auto seed = (fSkim != SkimType::DiXtal) ? inpho.seed : outpho.seed;

      // store seed info + derived types if seed exists
      if (seed >= 0)
      {
	// outpho.seedX = (*fInRecHits.X)[seed];
	// outpho.seedY = (*fInRecHits.Y)[seed];
	// outpho.seedZ = (*fInRecHits.Z)[seed];
	outpho.seedE = (*fInRecHits.E)[seed];

	outpho.seedtime    = (*fInRecHits.time)   [seed];
	// outpho.seedtimeErr = (*fInRecHits.timeErr)[seed];
	outpho.seedTOF     = (*fInRecHits.TOF)    [seed];

	// get trigger tower
	outpho.seedTT = Common::GetTriggerTower((*fInRecHits.ID)[seed]);
	
	outpho.seedID    = (*fInRecHits.ID)[seed];
        const auto & sidinfo = Common::DetIDMap[(*fInRecHits.ID)[seed]];
        outpho.seedI1    = sidinfo.i1;
	outpho.seedI2    = sidinfo.i2;
	outpho.seedEcal  = sidinfo.ecal;
	// outpho.seedisOOT = (*fInRecHits.isOOT)[seed];

	outpho.seedootA0 = 0.0;
        outpho.seedootA1 = 0.0;
        outpho.seedootA2 = 0.0;
        outpho.seedootA3 = 0.0;
        outpho.seedootA4 = 0.0;
        outpho.seedootA5 = 0.0;
        outpho.seedootA6 = 0.0;
        outpho.seedootA7 = 0.0;
        outpho.seedootA8 = 0.0;
        outpho.seedootA9 = 0.0;
        outpho.seedootMax = 0.0;
        outpho.seedootMbefore = 0.0;
        outpho.seedootMafter = 0.0;
        outpho.seedootSign = 1;
        outpho.seedootVsum = 0.0;

	outpho.seedisGS6 = (*fInRecHits.isGS6)[seed];
	outpho.seedisGS1 = (*fInRecHits.isGS1)[seed];
	outpho.seedadcToGeV = (*fInRecHits.adcToGeV)[seed];

	outpho.seedped12 = (*fInRecHits.ped12)[seed];
	outpho.seedped6  = (*fInRecHits.ped6) [seed];
	outpho.seedped1  = (*fInRecHits.ped1) [seed];
	outpho.seedpedrms12 = (*fInRecHits.pedrms12)[seed];
	outpho.seedpedrms6  = (*fInRecHits.pedrms6) [seed];
	outpho.seedpedrms1  = (*fInRecHits.pedrms1) [seed];

        for(UInt_t kuseed = 0; kuseed < (*kurhID).size(); kuseed++ ){
                if( (*kurhID)[kuseed] == (*fInRecHits.ID)[seed] ){
//			outpho.seedkuE = (*kurhE)[kuseed];
        		outpho.seedkutime = (*kurhtime)[kuseed];
        		outpho.seedkutimeErr = (*kurhtimeErr)[kuseed];
//        		outpho.seedkuTOF = (*kurhTOF)[kuseed];
        		outpho.seedkuID = (*kurhID)[kuseed];			
                }
        }

  	if( hasMultiKURecHit ){
        for(UInt_t kuStcseed = 0; kuStcseed < (*kuStcrhID).size(); kuStcseed++ ){
                if( (*kuStcrhID)[kuStcseed] == (*fInRecHits.ID)[seed] ){
                        //outpho.seedkuStcE = (*kuStcrhE)[kuStcseed];
                        outpho.seedkuStctime = (*kuStcrhtime)[kuStcseed];
                        outpho.seedkuStctimeErr = (*kuStcrhtimeErr)[kuStcseed];
                        //outpho.seedkuStcTOF = (*kuStcrhTOF)[kuStcseed];
                        outpho.seedkuStcID = (*kuStcrhID)[kuStcseed];
                }
        }

//        for(UInt_t kuNotseed = 0; kuNotseed < (*kuNotrhID).size(); kuNotseed++ ){
//                if( (*kuNotrhID)[kuNotseed] == (*fInRecHits.ID)[seed] ){
//                        //outpho.seedkuNotE = (*kuNotrhE)[kuNotseed];
//                        outpho.seedkuNottime = (*kuNotrhtime)[kuNotseed];
//                        outpho.seedkuNottimeErr = (*kuNotrhtimeErr)[kuNotseed];
//                        //outpho.seedkuNotTOF = (*kuNotrhTOF)[kuNotseed];
//                        //outpho.seedkuNotID = (*kuNotrhID)[kuNotseed];
//                }
//        }

        for(UInt_t kuNotStcseed = 0; kuNotStcseed < (*kuNotStcrhID).size(); kuNotStcseed++ ){
                if( (*kuNotStcrhID)[kuNotStcseed] == (*fInRecHits.ID)[seed] ){
                        //outpho.seedkuNotStcE = (*kuNotStcrhE)[kuNotStcseed];
                        outpho.seedkuNotStctime = (*kuNotStcrhtime)[kuNotStcseed];
                        outpho.seedkuNotStctimeErr = (*kuNotStcrhtimeErr)[kuNotStcseed];
                        //outpho.seedkuNotStcTOF = (*kuNotStcrhTOF)[kuNotStcseed];
                        outpho.seedkuNotStcID = (*kuNotStcrhID)[kuNotStcseed];
                }
        }
        for(UInt_t kuWootStcseed = 0; kuWootStcseed < (*kuWootStcrhID).size(); kuWootStcseed++ ){
                if( (*kuWootStcrhID)[kuWootStcseed] == (*fInRecHits.ID)[seed] ){
//                        outpho.seedkuWootStcE = (*kuWootStcrhE)[kuWootStcseed];
                        outpho.seedkuWootStctime = (*kuWootStcrhtime)[kuWootStcseed];
                        outpho.seedkuWootStctimeErr = (*kuWootStcrhtimeErr)[kuWootStcseed];
//                        outpho.seedkuWootStcTOF = (*kuWootStcrhTOF)[kuWootStcseed];
                        outpho.seedkuWootStcID = (*kuWootStcrhID)[kuWootStcseed];
                }
        }

        }

        if( hasUrecDigi ){
		for(UInt_t urseed = 0; urseed < (*uRhId).size(); urseed++ ){
			if( (*uRhId)[urseed] == (*fInRecHits.ID)[seed] ){
	        		outpho.seedootA0 = (*ootA0)[urseed];
	        		outpho.seedootA1 = (*ootA1)[urseed];
	        		outpho.seedootA2 = (*ootA2)[urseed];
	        		outpho.seedootA3 = (*ootA3)[urseed];
	        		outpho.seedootA4 = (*ootA4)[urseed];
	        		outpho.seedootA5 = (*ootA5)[urseed];
	        		outpho.seedootA6 = (*ootA6)[urseed];
	        		outpho.seedootA7 = (*ootA7)[urseed];
	        		outpho.seedootA8 = (*ootA8)[urseed];
                                outpho.seedootA9 = (*ootA9)[urseed];
				outpho.seedootMbefore = std::max( outpho.seedootA0, 
								std::max(outpho.seedootA1, 
								std::max(outpho.seedootA2, 
								std::max(outpho.seedootA3, outpho.seedootA4 ))));
                		outpho.seedootMafter = std::max( outpho.seedootA5,
                                                                std::max(outpho.seedootA6,
                                                                std::max(outpho.seedootA7,
                                                                std::max(outpho.seedootA8, outpho.seedootA9 )))); 
                                outpho.seedootMax = std::max(outpho.seedootMbefore,outpho.seedootMafter);
				outpho.seedootSign = (outpho.seedootMbefore < outpho.seedootMafter )?1:-1;
				auto sum1 = outpho.seedootA0 * outpho.seedootA0 + outpho.seedootA1 * outpho.seedootA1;
				auto sum2 = outpho.seedootA2 * outpho.seedootA2 + outpho.seedootA3 * outpho.seedootA3;
				auto sum3 = outpho.seedootA4 * outpho.seedootA4 + outpho.seedootA5 * outpho.seedootA5;
				auto sum4 = outpho.seedootA6 * outpho.seedootA6 + outpho.seedootA7 * outpho.seedootA7;
				auto sum5 = outpho.seedootA8 * outpho.seedootA8 + outpho.seedootA9 * outpho.seedootA9;
				outpho.seedootVsum = sum1 + sum2 + sum3 + sum4 + sum5;
				break;
			}
		}
        }

	// compute mean time, weighted time, AND
	// weighted time "TOF": really compute weighted time with TOF, then subtract this from weighted time to get "TOF"
	outpho.nrechits = 0;
	outpho.nrechitsLT120 = 0;
	outpho.meantime = 0.f;
	outpho.meantimeLT120 = 0.f;
	outpho.weightedtime = 0.f;
	outpho.weightedtimeLT120 = 0.f;
	outpho.weightedtimeTOF = 0.f;
	outpho.weightedtimeLT120TOF = 0.f;
	Float_t sumweights      = 0.f;
	Float_t sumweightsLT120 = 0.f;
	for (const auto irh : (*inpho.recHits))
	{
	  const Float_t rh_E = (*fInRecHits.E)   [irh];
	  const Float_t rh_T = (*fInRecHits.time)[irh];
	  const Float_t rh_A = (rh_E/(*fInRecHits.adcToGeV)[irh])/(*fInRecHits.pedrms12)[irh]; // amplitude normalized by pedestal noise
	  const Float_t inv_weight_2 = 1.f/(std::pow(Common::timefitN/rh_A,2)+2.f*std::pow(Common::timefitC,2));
	  const Float_t rh_TOF = (*fInRecHits.TOF)[irh];

	  outpho.nrechits++;
	  outpho.meantime += rh_T;

	  outpho.weightedtime    += rh_T*inv_weight_2;
	  outpho.weightedtimeTOF += (rh_T+rh_TOF)*inv_weight_2;
	  sumweights             += inv_weight_2;
	  
	  if (rh_E > 120.f) continue;

	  outpho.nrechitsLT120++;
	  outpho.meantimeLT120 += rh_T;

	  outpho.weightedtimeLT120    += rh_T*inv_weight_2;
	  outpho.weightedtimeLT120TOF += (rh_T+rh_TOF)*inv_weight_2;
	  sumweightsLT120             += inv_weight_2;
	}

	// set the derived types
	if   (outpho.nrechits > 0)
	{
	  outpho.meantime        /= outpho.nrechits;
	  outpho.weightedtime    /= sumweights;
	  outpho.weightedtimeTOF /= sumweights;

	  // hack for weighted time "TOF"
	  outpho.weightedtimeTOF -= outpho.weightedtime;
	}
	else 
	{
	  outpho.meantime        = -9999.f;
	  outpho.weightedtime    = -9999.f;
	  outpho.weightedtimeTOF = -9999.f*2.f;
	}

	if   (outpho.nrechitsLT120 > 0)
	{
	  outpho.meantimeLT120        /= outpho.nrechitsLT120;
	  outpho.weightedtimeLT120    /= sumweightsLT120;
	  outpho.weightedtimeLT120TOF /= sumweightsLT120;

	  // hack for weighted time "TOF"
	  outpho.weightedtimeLT120TOF -= outpho.weightedtimeLT120;
	}
	else
	{
	  outpho.meantimeLT120        = -9999.f;
	  outpho.weightedtimeLT120    = -9999.f;
	  outpho.weightedtimeLT120TOF = -9999.f*2.f;
	}
      } // end check that seed exists
      else
      {
	// outpho.seedX = -9999.f;
	// outpho.seedY = -9999.f;
	// outpho.seedZ = -9999.f;
	outpho.seedE = -9999.f;

	outpho.seedtime    = -9999.f;
	// outpho.seedtimeErr = -9999.f;
	outpho.seedTOF     = -9999.f;	

	// outpho.seedID    = 0;
	// outpho.seedisOOT = -1;
	outpho.seedTT    = -9999;

	outpho.seedisGS6 = -1;
	outpho.seedisGS1 = -1;
	outpho.seedadcToGeV = -9999.f;
	outpho.seedped12 = -9999.f;
	outpho.seedped6  = -9999.f;
	outpho.seedped1  = -9999.f;
	outpho.seedpedrms12 = -9999.f;
	outpho.seedpedrms6 = -9999.f;
	outpho.seedpedrms1 = -9999.f;

        outpho.seedkuE = -9999.f;
        outpho.seedkutime    = -9999.f;
        outpho.seedkutimeErr = -9999.f;
        outpho.seedkuTOF     = -9999.f;
        outpho.seedkuID    = 0;

  	if( hasMultiKURecHit ){
        outpho.seedkuStcE = -9999.f;
        outpho.seedkuStctime    = -9999.f;
        outpho.seedkuStctimeErr = -9999.f;
        outpho.seedkuStcTOF     = -9999.f;
        outpho.seedkuStcID    = 0;

        outpho.seedkuNotE = -9999.f;
        outpho.seedkuNottime    = -9999.f;
        outpho.seedkuNottimeErr = -9999.f;
        outpho.seedkuNotTOF     = -9999.f;
        outpho.seedkuNotID    = 0;

        outpho.seedkuNotStcE = -9999.f;
        outpho.seedkuNotStctime    = -9999.f;
        outpho.seedkuNotStctimeErr = -9999.f;
        outpho.seedkuNotStcTOF     = -9999.f;
        outpho.seedkuNotStcID    = 0;

        outpho.seedkuWootStcE = -9999.f;
        outpho.seedkuWootStctime    = -9999.f;
        outpho.seedkuWootStctimeErr = -9999.f;
        outpho.seedkuWootStcTOF     = -9999.f;
        outpho.seedkuWootStcID    = 0;
        }

	outpho.nrechits             = -1;
	outpho.nrechitsLT120        = -1;
	outpho.meantime             = -9999.f;
	outpho.meantimeLT120        = -9999.f;
	outpho.weightedtime         = -9999.f;
	outpho.weightedtimeLT120    = -9999.f;
	outpho.weightedtimeTOF      = -9999.f*2.f;
	outpho.weightedtimeLT120TOF = -9999.f*2.f;
      }
    } // end check over store rechits
    else
    {
      // outpho.seedX = inpho.seedX;
      // outpho.seedY = inpho.seedY;
      // outpho.seedZ = inpho.seedZ;
      outpho.seedE = inpho.seedE;
      outpho.seedtime = inpho.seedtime;
      // outpho.seedtimeErr = inpho.seedtimeErr;
      outpho.seedTOF = inpho.seedTOF;
      // outpho.seedID = inpho.seedID;
      // outpho.seedisOOT = inpho.seedisOOT;
      outpho.seedTT = Common::GetTriggerTower(inpho.seedID);
      outpho.seedisGS6 = inpho.seedisGS1;
      outpho.seedisGS1 = inpho.seedisGS6;
      outpho.seedadcToGeV = inpho.seedadcToGeV;
      outpho.seedped12 = inpho.seedped12;
      outpho.seedped6 = inpho.seedped6;
      outpho.seedped1 = inpho.seedped1;
      outpho.seedpedrms12 = inpho.seedpedrms12;
      outpho.seedpedrms6 = inpho.seedpedrms6;
      outpho.seedpedrms1 = inpho.seedpedrms1;

    }
    
  }
}

void Skimmer::CorrectMET()
{
  // first, do jets
}

void Skimmer::GetInConfig()
{
  // Get Input Config
  Skimmer::InitInConfigStrings();
  Skimmer::InitInConfigBranches();

  // read in first entry (will be the same for all entries in a given file)
  fInConfigTree->GetEntry(0);

  // set isMC
  fIsMC = (fInConfig.isGMSB || fInConfig.isHVDS || fInConfig.isBkgd || fInConfig.isToy || fInConfig.isADD);
}

void Skimmer::InitInConfigStrings()
{
  fInConfig.phIDmin = 0;
  fInConfig.phgoodIDmin = 0;
  fInConfig.inputPaths = 0;
  fInConfig.inputFilters = 0;
  fInConfig.inputFlags = 0;
}

void Skimmer::InitInConfigBranches()
{
  fInConfigTree->SetBranchAddress(fInConfig.s_blindSF.c_str(), &fInConfig.blindSF);
  fInConfigTree->SetBranchAddress(fInConfig.s_applyBlindSF.c_str(), &fInConfig.applyBlindSF);
  fInConfigTree->SetBranchAddress(fInConfig.s_blindMET.c_str(), &fInConfig.blindMET);
  fInConfigTree->SetBranchAddress(fInConfig.s_applyBlindMET.c_str(), &fInConfig.applyBlindMET);
  fInConfigTree->SetBranchAddress(fInConfig.s_jetpTmin.c_str(), &fInConfig.jetpTmin);
  fInConfigTree->SetBranchAddress(fInConfig.s_jetEtamax.c_str(), &fInConfig.jetEtamax);
  fInConfigTree->SetBranchAddress(fInConfig.s_jetIDmin.c_str(), &fInConfig.jetIDmin);
  fInConfigTree->SetBranchAddress(fInConfig.s_rhEmin.c_str(), &fInConfig.rhEmin);
  fInConfigTree->SetBranchAddress(fInConfig.s_phpTmin.c_str(), &fInConfig.phpTmin);
  fInConfigTree->SetBranchAddress(fInConfig.s_phIDmin.c_str(), &fInConfig.phIDmin);
  fInConfigTree->SetBranchAddress(fInConfig.s_seedTimemin.c_str(), &fInConfig.seedTimemin);
  fInConfigTree->SetBranchAddress(fInConfig.s_splitPho.c_str(), &fInConfig.splitPho);
  fInConfigTree->SetBranchAddress(fInConfig.s_onlyGED.c_str(), &fInConfig.onlyGED);
  fInConfigTree->SetBranchAddress(fInConfig.s_onlyOOT.c_str(), &fInConfig.onlyOOT);
  // fInConfigTree->SetBranchAddress(fInConfig.s_ellowpTmin.c_str(), &fInConfig.ellowpTmin);
  // fInConfigTree->SetBranchAddress(fInConfig.s_elhighpTmin.c_str(), &fInConfig.elhighpTmin);
  // fInConfigTree->SetBranchAddress(fInConfig.s_mulowpTmin.c_str(), &fInConfig.mulowpTmin);
  // fInConfigTree->SetBranchAddress(fInConfig.s_muhighpTmin.c_str(), &fInConfig.muhighpTmin);
  fInConfigTree->SetBranchAddress(fInConfig.s_storeRecHits.c_str(), &fInConfig.storeRecHits);
  fInConfigTree->SetBranchAddress(fInConfig.s_applyTrigger.c_str(), &fInConfig.applyTrigger);
  fInConfigTree->SetBranchAddress(fInConfig.s_minHT.c_str(), &fInConfig.minHT);
  fInConfigTree->SetBranchAddress(fInConfig.s_applyHT.c_str(), &fInConfig.applyHT);
  fInConfigTree->SetBranchAddress(fInConfig.s_phgoodpTmin.c_str(), &fInConfig.phgoodpTmin);
  fInConfigTree->SetBranchAddress(fInConfig.s_phgoodIDmin.c_str(), &fInConfig.phgoodIDmin);
  fInConfigTree->SetBranchAddress(fInConfig.s_applyPhGood.c_str(), &fInConfig.applyPhGood);
  fInConfigTree->SetBranchAddress(fInConfig.s_dRmin.c_str(), &fInConfig.dRmin);
  fInConfigTree->SetBranchAddress(fInConfig.s_pTres.c_str(), &fInConfig.pTres);
  fInConfigTree->SetBranchAddress(fInConfig.s_genpTres.c_str(), &fInConfig.genpTres);
  fInConfigTree->SetBranchAddress(fInConfig.s_trackdRmin.c_str(), &fInConfig.trackdRmin);
  fInConfigTree->SetBranchAddress(fInConfig.s_trackpTmin.c_str(), &fInConfig.trackpTmin);
  fInConfigTree->SetBranchAddress(fInConfig.s_genjetdRmin.c_str(), &fInConfig.genjetdRmin);
  fInConfigTree->SetBranchAddress(fInConfig.s_genjetpTfactor.c_str(), &fInConfig.genjetpTfactor);
  // fInConfigTree->SetBranchAddress(fInConfig.s_leptondRmin.c_str(), &fInConfig.leptondRmin);
  fInConfigTree->SetBranchAddress(fInConfig.s_smearjetEmin.c_str(), &fInConfig.smearjetEmin);
  fInConfigTree->SetBranchAddress(fInConfig.s_inputPaths.c_str(), &fInConfig.inputPaths);
  fInConfigTree->SetBranchAddress(fInConfig.s_inputFilters.c_str(), &fInConfig.inputFilters);
  fInConfigTree->SetBranchAddress(fInConfig.s_inputFlags.c_str(), &fInConfig.inputFlags);
  fInConfigTree->SetBranchAddress(fInConfig.s_isGMSB.c_str(), &fInConfig.isGMSB);
  fInConfigTree->SetBranchAddress(fInConfig.s_isHVDS.c_str(), &fInConfig.isHVDS);
  fInConfigTree->SetBranchAddress(fInConfig.s_isBkgd.c_str(), &fInConfig.isBkgd);
  fInConfigTree->SetBranchAddress(fInConfig.s_isToy.c_str(), &fInConfig.isToy);
  fInConfigTree->SetBranchAddress(fInConfig.s_isADD.c_str(), &fInConfig.isADD);
  fInConfigTree->SetBranchAddress(fInConfig.s_xsec.c_str(), &fInConfig.xsec);
  fInConfigTree->SetBranchAddress(fInConfig.s_filterEff.c_str(), &fInConfig.filterEff);
  fInConfigTree->SetBranchAddress(fInConfig.s_BR.c_str(), &fInConfig.BR);
}

void Skimmer::InitInTree() 
{
  Skimmer::InitInStructs();
  Skimmer::InitInBranchVecs();
  Skimmer::InitInBranches();
}

void Skimmer::InitInStructs()
{
  if (fIsMC)
  {
    if (fInConfig.isGMSB)
    {
      fInGMSBs.clear(); 
      fInGMSBs.resize(Common::nGMSBs);
    }
    if (fInConfig.isHVDS)
    {
      fInHVDSs.clear(); 
      fInHVDSs.resize(Common::nHVDSs);
    }
    if (fInConfig.isToy)
    {
      fInToys.clear(); 
      fInToys.resize(Common::nToys);
    }
  }

  fInPhos.clear();
  fInPhos.resize(Common::nPhotons);
}

void Skimmer::InitInBranchVecs()
{
  fInJets.E = 0;
  fInJets.pt = 0;
  fInJets.phi = 0;
  fInJets.eta = 0;
  fInJets.ID = 0;

  // fInJets.NHF = 0;
  // fInJets.NEMF = 0;
  // fInJets.CHF = 0;
  // fInJets.CEMF = 0;
  // fInJets.MUF = 0;
  // fInJets.NHM = 0;
  // fInJets.CHM = 0;

  kurhE = 0;
  kurhtime = 0;
  kurhtimeErr = 0;
  kurhTOF = 0;
  kurhID = 0;

  if( hasMultiKURecHit ){
  kuStcrhE = 0;
  kuStcrhtime = 0;
  kuStcrhtimeErr = 0;
  kuStcrhTOF = 0;
  kuStcrhID = 0;

  kuNotrhE = 0;
  kuNotrhtime = 0;
  kuNotrhtimeErr = 0;
  kuNotrhTOF = 0;
  kuNotrhID = 0;

  kuNotStcrhE = 0;
  kuNotStcrhtime = 0;
  kuNotStcrhtimeErr = 0;
  kuNotStcrhTOF = 0;
  kuNotStcrhID = 0;

  kuWootStcrhE = 0;
  kuWootStcrhtime = 0;
  kuWootStcrhtimeErr = 0;
  kuWootStcrhTOF = 0;
  kuWootStcrhID = 0;
  }

  if( hasUrecDigi ){
   ootA0 = 0;
   ootA1 = 0;
   ootA2 = 0;
   ootA3 = 0;
   ootA4 = 0;
   ootA5 = 0;
   ootA6 = 0;
   ootA7 = 0;
   ootA8 = 0;
   ootA9 = 0;
   ootMax = 0;
   ootVsum = 0;
   uRhId = 0;
  }

  if (fInConfig.storeRecHits) 
  {
    // fInRecHits.X = 0;
    // fInRecHits.Y = 0;
    // fInRecHits.Z = 0;
    fInRecHits.E = 0;
    fInRecHits.time = 0;
    // fInRecHits.timeErr = 0;
    fInRecHits.TOF = 0;
    fInRecHits.ID = 0;
    // fInRecHits.isOOT = 0;
    fInRecHits.isGS6 = 0;
    fInRecHits.isGS1 = 0;
    fInRecHits.adcToGeV = 0;
    fInRecHits.ped12 = 0;
    fInRecHits.ped6 = 0;
    fInRecHits.ped1 = 0;
    fInRecHits.pedrms12 = 0;
    fInRecHits.pedrms6 = 0;
    fInRecHits.pedrms1 = 0;

    for (auto ipho = 0; ipho < Common::nPhotons; ipho++) 
    {
      fInPhos[ipho].recHits = 0;
    }  
  }
}

void Skimmer::InitInBranches()
{
  if (fIsMC)
  {
    fInTree->SetBranchAddress(fInEvent.s_genwgt.c_str(), &fInEvent.genwgt, &fInEvent.b_genwgt);
    fInTree->SetBranchAddress(fInEvent.s_genx0.c_str(), &fInEvent.genx0, &fInEvent.b_genx0);
    fInTree->SetBranchAddress(fInEvent.s_geny0.c_str(), &fInEvent.geny0, &fInEvent.b_geny0);
    fInTree->SetBranchAddress(fInEvent.s_genz0.c_str(), &fInEvent.genz0, &fInEvent.b_genz0);
    fInTree->SetBranchAddress(fInEvent.s_gent0.c_str(), &fInEvent.gent0, &fInEvent.b_gent0);
    fInTree->SetBranchAddress(fInEvent.s_genpuobs.c_str(), &fInEvent.genpuobs, &fInEvent.b_genpuobs);
    fInTree->SetBranchAddress(fInEvent.s_genputrue.c_str(), &fInEvent.genputrue, &fInEvent.b_genputrue);
    
    if (fInConfig.isGMSB)
    {
      fInTree->SetBranchAddress(fInEvent.s_nNeutoPhGr.c_str(), &fInEvent.nNeutoPhGr, &fInEvent.b_nNeutoPhGr);
      for (auto igmsb = 0; igmsb < Common::nGMSBs; igmsb++) 
      {
	auto & gmsb = fInGMSBs[igmsb];
	fInTree->SetBranchAddress(Form("%s_%i",gmsb.s_genNmass.c_str(),igmsb), &gmsb.genNmass, &gmsb.b_genNmass);
	fInTree->SetBranchAddress(Form("%s_%i",gmsb.s_genNE.c_str(),igmsb), &gmsb.genNE, &gmsb.b_genNE);
	fInTree->SetBranchAddress(Form("%s_%i",gmsb.s_genNpt.c_str(),igmsb), &gmsb.genNpt, &gmsb.b_genNpt);
	fInTree->SetBranchAddress(Form("%s_%i",gmsb.s_genNphi.c_str(),igmsb), &gmsb.genNphi, &gmsb.b_genNphi);
	fInTree->SetBranchAddress(Form("%s_%i",gmsb.s_genNeta.c_str(),igmsb), &gmsb.genNeta, &gmsb.b_genNeta);
	fInTree->SetBranchAddress(Form("%s_%i",gmsb.s_genNprodvx.c_str(),igmsb), &gmsb.genNprodvx, &gmsb.b_genNprodvx);
	fInTree->SetBranchAddress(Form("%s_%i",gmsb.s_genNprodvy.c_str(),igmsb), &gmsb.genNprodvy, &gmsb.b_genNprodvy);
	fInTree->SetBranchAddress(Form("%s_%i",gmsb.s_genNprodvz.c_str(),igmsb), &gmsb.genNprodvz, &gmsb.b_genNprodvz);
	fInTree->SetBranchAddress(Form("%s_%i",gmsb.s_genNdecayvx.c_str(),igmsb), &gmsb.genNdecayvx, &gmsb.b_genNdecayvx);
	fInTree->SetBranchAddress(Form("%s_%i",gmsb.s_genNdecayvy.c_str(),igmsb), &gmsb.genNdecayvy, &gmsb.b_genNdecayvy);
	fInTree->SetBranchAddress(Form("%s_%i",gmsb.s_genNdecayvz.c_str(),igmsb), &gmsb.genNdecayvz, &gmsb.b_genNdecayvz);
	fInTree->SetBranchAddress(Form("%s_%i",gmsb.s_genphE.c_str(),igmsb), &gmsb.genphE, &gmsb.b_genphE);
	fInTree->SetBranchAddress(Form("%s_%i",gmsb.s_genphpt.c_str(),igmsb), &gmsb.genphpt, &gmsb.b_genphpt);
	fInTree->SetBranchAddress(Form("%s_%i",gmsb.s_genphphi.c_str(),igmsb), &gmsb.genphphi, &gmsb.b_genphphi);
	fInTree->SetBranchAddress(Form("%s_%i",gmsb.s_genpheta.c_str(),igmsb), &gmsb.genpheta, &gmsb.b_genpheta);
	fInTree->SetBranchAddress(Form("%s_%i",gmsb.s_genphmatch.c_str(),igmsb), &gmsb.genphmatch, &gmsb.b_genphmatch);
	fInTree->SetBranchAddress(Form("%s_%i",gmsb.s_gengrmass.c_str(),igmsb), &gmsb.gengrmass, &gmsb.b_gengrmass);
	fInTree->SetBranchAddress(Form("%s_%i",gmsb.s_gengrE.c_str(),igmsb), &gmsb.gengrE, &gmsb.b_gengrE);
	fInTree->SetBranchAddress(Form("%s_%i",gmsb.s_gengrpt.c_str(),igmsb), &gmsb.gengrpt, &gmsb.b_gengrpt);
	fInTree->SetBranchAddress(Form("%s_%i",gmsb.s_gengrphi.c_str(),igmsb), &gmsb.gengrphi, &gmsb.b_gengrphi);
	fInTree->SetBranchAddress(Form("%s_%i",gmsb.s_gengreta.c_str(),igmsb), &gmsb.gengreta, &gmsb.b_gengreta);
      } // end loop over neutralinos
    } // end block over gmsb

    if (fInConfig.isHVDS)
    {
      fInTree->SetBranchAddress(fInEvent.s_nvPions.c_str(), &fInEvent.nvPions, &fInEvent.b_nvPions);
      for (auto ihvds = 0; ihvds < Common::nHVDSs; ihvds++) 
      {
	auto & hvds = fInHVDSs[ihvds]; 
	fInTree->SetBranchAddress(Form("%s_%i",hvds.s_genvPionmass.c_str(),ihvds), &hvds.genvPionmass, &hvds.b_genvPionmass);
	fInTree->SetBranchAddress(Form("%s_%i",hvds.s_genvPionE.c_str(),ihvds), &hvds.genvPionE, &hvds.b_genvPionE);
	fInTree->SetBranchAddress(Form("%s_%i",hvds.s_genvPionpt.c_str(),ihvds), &hvds.genvPionpt, &hvds.b_genvPionpt);
	fInTree->SetBranchAddress(Form("%s_%i",hvds.s_genvPionphi.c_str(),ihvds), &hvds.genvPionphi, &hvds.b_genvPionphi);
	fInTree->SetBranchAddress(Form("%s_%i",hvds.s_genvPioneta.c_str(),ihvds), &hvds.genvPioneta, &hvds.b_genvPioneta);
	fInTree->SetBranchAddress(Form("%s_%i",hvds.s_genvPionprodvx.c_str(),ihvds), &hvds.genvPionprodvx, &hvds.b_genvPionprodvx);
	fInTree->SetBranchAddress(Form("%s_%i",hvds.s_genvPionprodvy.c_str(),ihvds), &hvds.genvPionprodvy, &hvds.b_genvPionprodvy);
	fInTree->SetBranchAddress(Form("%s_%i",hvds.s_genvPionprodvz.c_str(),ihvds), &hvds.genvPionprodvz, &hvds.b_genvPionprodvz);
	fInTree->SetBranchAddress(Form("%s_%i",hvds.s_genvPiondecayvx.c_str(),ihvds), &hvds.genvPiondecayvx, &hvds.b_genvPiondecayvx);
	fInTree->SetBranchAddress(Form("%s_%i",hvds.s_genvPiondecayvy.c_str(),ihvds), &hvds.genvPiondecayvy, &hvds.b_genvPiondecayvy);
	fInTree->SetBranchAddress(Form("%s_%i",hvds.s_genvPiondecayvz.c_str(),ihvds), &hvds.genvPiondecayvz, &hvds.b_genvPiondecayvz);
	fInTree->SetBranchAddress(Form("%s_%i",hvds.s_genHVph0E.c_str(),ihvds), &hvds.genHVph0E, &hvds.b_genHVph0E);
	fInTree->SetBranchAddress(Form("%s_%i",hvds.s_genHVph0pt.c_str(),ihvds), &hvds.genHVph0pt, &hvds.b_genHVph0pt);
	fInTree->SetBranchAddress(Form("%s_%i",hvds.s_genHVph0phi.c_str(),ihvds), &hvds.genHVph0phi, &hvds.b_genHVph0phi);
	fInTree->SetBranchAddress(Form("%s_%i",hvds.s_genHVph0eta.c_str(),ihvds), &hvds.genHVph0eta, &hvds.b_genHVph0eta);
	fInTree->SetBranchAddress(Form("%s_%i",hvds.s_genHVph0match.c_str(),ihvds), &hvds.genHVph0match, &hvds.b_genHVph0match);
	fInTree->SetBranchAddress(Form("%s_%i",hvds.s_genHVph1E.c_str(),ihvds), &hvds.genHVph1E, &hvds.b_genHVph1E);
	fInTree->SetBranchAddress(Form("%s_%i",hvds.s_genHVph1pt.c_str(),ihvds), &hvds.genHVph1pt, &hvds.b_genHVph1pt);
	fInTree->SetBranchAddress(Form("%s_%i",hvds.s_genHVph1phi.c_str(),ihvds), &hvds.genHVph1phi, &hvds.b_genHVph1phi);
	fInTree->SetBranchAddress(Form("%s_%i",hvds.s_genHVph1eta.c_str(),ihvds), &hvds.genHVph1eta, &hvds.b_genHVph1eta);
	fInTree->SetBranchAddress(Form("%s_%i",hvds.s_genHVph1match.c_str(),ihvds), &hvds.genHVph1match, &hvds.b_genHVph1match);
      } // end loop over nvpions 
    } // end block over hvds

    if (fInConfig.isToy)
    {
      fInTree->SetBranchAddress(fInEvent.s_nToyPhs.c_str(), &fInEvent.nToyPhs, &fInEvent.b_nToyPhs);
      for (auto itoy = 0; itoy < Common::nToys; itoy++) 
      {
	auto & toy = fInToys[itoy]; 
	fInTree->SetBranchAddress(Form("%s_%i",toy.s_genphE.c_str(),itoy), &toy.genphE, &toy.b_genphE);
	fInTree->SetBranchAddress(Form("%s_%i",toy.s_genphpt.c_str(),itoy), &toy.genphpt, &toy.b_genphpt);
	fInTree->SetBranchAddress(Form("%s_%i",toy.s_genphphi.c_str(),itoy), &toy.genphphi, &toy.b_genphphi);
	fInTree->SetBranchAddress(Form("%s_%i",toy.s_genpheta.c_str(),itoy), &toy.genpheta, &toy.b_genpheta);
	fInTree->SetBranchAddress(Form("%s_%i",toy.s_genphmatch.c_str(),itoy), &toy.genphmatch, &toy.b_genphmatch);
	fInTree->SetBranchAddress(Form("%s_%i",toy.s_genphmatch_ptres.c_str(),itoy), &toy.genphmatch_ptres, &toy.b_genphmatch_ptres);
	fInTree->SetBranchAddress(Form("%s_%i",toy.s_genphmatch_status.c_str(),itoy), &toy.genphmatch_status, &toy.b_genphmatch_status);
      } // end loop over toy phos
    } // end block over toyMC

  } // end block over isMC

  fInTree->SetBranchAddress(fInEvent.s_run.c_str(), &fInEvent.run, &fInEvent.b_run);
  fInTree->SetBranchAddress(fInEvent.s_lumi.c_str(), &fInEvent.lumi, &fInEvent.b_lumi);
  fInTree->SetBranchAddress(fInEvent.s_event.c_str(), &fInEvent.event, &fInEvent.b_event);

   if( isLHCInfo ){
   fInTree->SetBranchAddress("bunch_crossing", &bunch_crossing, &b_bunch_crossing);
   fInTree->SetBranchAddress("num_bunch", &num_bunch, &b_num_bunch);
   fInTree->SetBranchAddress("subtrain_position", &subtrain_position, &b_subtrain_position);
   fInTree->SetBranchAddress("train_position", &train_position, &b_train_position);
   fInTree->SetBranchAddress("subtrain_number", &subtrain_number, &b_subtrain_number);
   fInTree->SetBranchAddress("train_number", &train_number, &b_train_number);
   fInTree->SetBranchAddress("beam1_VC", beam1_VC, &b_beam1_VC);
   fInTree->SetBranchAddress("beam2_VC", beam2_VC, &b_beam2_VC);
   fInTree->SetBranchAddress("beam1_RF", beam1_RF, &b_beam1_RF);
   fInTree->SetBranchAddress("beam2_RF", beam2_RF, &b_beam2_RF);
   }

   //fInTree->SetBranchAddress("kurhE", &kurhE, &b_kurhE);
   fInTree->SetBranchAddress("kurhtime", &kurhtime, &b_kurhtime);
   fInTree->SetBranchAddress("kurhtimeErr", &kurhtimeErr, &b_kurhtimeErr);
   //fInTree->SetBranchAddress("kurhTOF", &kurhTOF, &b_kurhTOF);
   fInTree->SetBranchAddress("kurhID", &kurhID, &b_kurhID);

   if( hasMultiKURecHit ){
   //fInTree->SetBranchAddress("kuStcrhE", &kuStcrhE, &b_kuStcrhE);
   fInTree->SetBranchAddress("kuStcrhtime", &kuStcrhtime, &b_kuStcrhtime);
   fInTree->SetBranchAddress("kuStcrhtimeErr", &kuStcrhtimeErr, &b_kuStcrhtimeErr);
   //fInTree->SetBranchAddress("kuStcrhTOF", &kuStcrhTOF, &b_kuStcrhTOF);
   fInTree->SetBranchAddress("kuStcrhID", &kuStcrhID, &b_kuStcrhID);

   //fInTree->SetBranchAddress("kuNotrhE", &kuNotrhE, &b_kuNotrhE);
   //fInTree->SetBranchAddress("kuNotrhtime", &kuNotrhtime, &b_kuNotrhtime);
   //fInTree->SetBranchAddress("kuNotrhtimeErr", &kuNotrhtimeErr, &b_kuNotrhtimeErr);
   //fInTree->SetBranchAddress("kuNotrhTOF", &kuNotrhTOF, &b_kuNotrhTOF);
   //fInTree->SetBranchAddress("kuNotrhID", &kuNotrhID, &b_kuNotrhID);

   //fInTree->SetBranchAddress("kuNotStcrhE", &kuNotStcrhE, &b_kuNotStcrhE);
   fInTree->SetBranchAddress("kuNotStcrhtime", &kuNotStcrhtime, &b_kuNotStcrhtime);
   fInTree->SetBranchAddress("kuNotStcrhtimeErr", &kuNotStcrhtimeErr, &b_kuNotStcrhtimeErr);
   //fInTree->SetBranchAddress("kuNotStcrhTOF", &kuNotStcrhTOF, &b_kuNotStcrhTOF);
   fInTree->SetBranchAddress("kuNotStcrhID", &kuNotStcrhID, &b_kuNotStcrhID);
//>>>>  alt def
//   fInTree->SetBranchAddress("kuWootStcrhE", &kuNotStcrhE, &b_kuNotStcrhE);
//   fInTree->SetBranchAddress("kuWootStcrhtime", &kuNotStcrhtime, &b_kuNotStcrhtime);
//   fInTree->SetBranchAddress("kuWootStcrhtimeErr", &kuNotStcrhtimeErr, &b_kuNotStcrhtimeErr);
//   fInTree->SetBranchAddress("kuWootStcrhTOF", &kuNotStcrhTOF, &b_kuNotStcrhTOF);
//   fInTree->SetBranchAddress("kuWootStcrhID", &kuNotStcrhID, &b_kuNotStcrhID);

 //  fInTree->SetBranchAddress("kuWootStcrhE", &kuWootStcrhE, &b_kuWootStcrhE);
   fInTree->SetBranchAddress("kuWootStcrhtime", &kuWootStcrhtime, &b_kuWootStcrhtime);
   fInTree->SetBranchAddress("kuWootStcrhtimeErr", &kuWootStcrhtimeErr, &b_kuWootStcrhtimeErr);
  // fInTree->SetBranchAddress("kuWootStcrhTOF", &kuWootStcrhTOF, &b_kuWootStcrhTOF);
   fInTree->SetBranchAddress("kuWootStcrhID", &kuWootStcrhID, &b_kuWootStcrhID);
//  >>>>>>>   alt def
//   fInTree->SetBranchAddress("kuNotStcrhE", &kuWootStcrhE, &b_kuWootStcrhE);
//   fInTree->SetBranchAddress("kuNotStcrhtime", &kuWootStcrhtime, &b_kuWootStcrhtime);
//   fInTree->SetBranchAddress("kuNotStcrhtimeErr", &kuWootStcrhtimeErr, &b_kuWootStcrhtimeErr);
//   fInTree->SetBranchAddress("kuNotStcrhTOF", &kuWootStcrhTOF, &b_kuWootStcrhTOF);
//   fInTree->SetBranchAddress("kuNotStcrhID", &kuWootStcrhID, &b_kuWootStcrhID);

   }

  if( hasUrecDigi ){
     fInTree->SetBranchAddress("nurechits", &nurechits, &b_nurechits);
     fInTree->SetBranchAddress("ndigis", &ndigis, &b_ndigis);
     fInTree->SetBranchAddress("uRhId", &uRhId, &b_uRhId);
     fInTree->SetBranchAddress("ootA0", &ootA0, &b_ootA0);
     fInTree->SetBranchAddress("ootA1", &ootA1, &b_ootA1);
     fInTree->SetBranchAddress("ootA2", &ootA2, &b_ootA2);
     fInTree->SetBranchAddress("ootA3", &ootA3, &b_ootA3);
     fInTree->SetBranchAddress("ootA4", &ootA4, &b_ootA4);
     fInTree->SetBranchAddress("ootA5", &ootA5, &b_ootA5);
     fInTree->SetBranchAddress("ootA6", &ootA6, &b_ootA6);
     fInTree->SetBranchAddress("ootA7", &ootA7, &b_ootA7);
     fInTree->SetBranchAddress("ootA8", &ootA8, &b_ootA8);
     fInTree->SetBranchAddress("ootA9", &ootA9, &b_ootA9);
  }

  fInTree->SetBranchAddress(fInEvent.s_hltSignal.c_str(), &fInEvent.hltSignal, &fInEvent.b_hltSignal);
  fInTree->SetBranchAddress(fInEvent.s_hltRefPhoID.c_str(), &fInEvent.hltRefPhoID, &fInEvent.b_hltRefPhoID);
  fInTree->SetBranchAddress(fInEvent.s_hltRefDispID.c_str(), &fInEvent.hltRefDispID, &fInEvent.b_hltRefDispID);
  fInTree->SetBranchAddress(fInEvent.s_hltRefHT.c_str(), &fInEvent.hltRefHT, &fInEvent.b_hltRefHT);
  fInTree->SetBranchAddress(fInEvent.s_hltPho50.c_str(), &fInEvent.hltPho50, &fInEvent.b_hltPho50);
  fInTree->SetBranchAddress(fInEvent.s_hltPho200.c_str(), &fInEvent.hltPho200, &fInEvent.b_hltPho200);
  fInTree->SetBranchAddress(fInEvent.s_hltDiPho70.c_str(), &fInEvent.hltDiPho70, &fInEvent.b_hltDiPho70);
  fInTree->SetBranchAddress(fInEvent.s_hltDiPho3022M90.c_str(), &fInEvent.hltDiPho3022M90, &fInEvent.b_hltDiPho3022M90);
  fInTree->SetBranchAddress(fInEvent.s_hltDiPho30PV18PV.c_str(), &fInEvent.hltDiPho30PV18PV, &fInEvent.b_hltDiPho30PV18PV);
  fInTree->SetBranchAddress(fInEvent.s_hltEle32WPT.c_str(), &fInEvent.hltEle32WPT, &fInEvent.b_hltEle32WPT);
  fInTree->SetBranchAddress(fInEvent.s_hltDiEle33MW.c_str(), &fInEvent.hltDiEle33MW, &fInEvent.b_hltDiEle33MW);
  fInTree->SetBranchAddress(fInEvent.s_hltJet500.c_str(), &fInEvent.hltJet500, &fInEvent.b_hltJet500);
  
  fInTree->SetBranchAddress(fInEvent.s_metPV.c_str(), &fInEvent.metPV, &fInEvent.b_metPV);
  fInTree->SetBranchAddress(fInEvent.s_metBeamHalo.c_str(), &fInEvent.metBeamHalo, &fInEvent.b_metBeamHalo);
  fInTree->SetBranchAddress(fInEvent.s_metHBHENoise.c_str(), &fInEvent.metHBHENoise, &fInEvent.b_metHBHENoise);
  fInTree->SetBranchAddress(fInEvent.s_metHBHEisoNoise.c_str(), &fInEvent.metHBHEisoNoise, &fInEvent.b_metHBHEisoNoise);
  fInTree->SetBranchAddress(fInEvent.s_metECALTP.c_str(), &fInEvent.metECALTP, &fInEvent.b_metECALTP);
  fInTree->SetBranchAddress(fInEvent.s_metPFMuon.c_str(), &fInEvent.metPFMuon, &fInEvent.b_metPFMuon);
  fInTree->SetBranchAddress(fInEvent.s_metPFChgHad.c_str(), &fInEvent.metPFChgHad, &fInEvent.b_metPFChgHad);
  fInTree->SetBranchAddress(fInEvent.s_metEESC.c_str(), &fInEvent.metEESC, &fInEvent.b_metEESC);
  // fInTree->SetBranchAddress(fInEvent.s_metECALCalib.c_str(), &fInEvent.metECALCalib, &fInEvent.b_metECALCalib);
  fInTree->SetBranchAddress(fInEvent.s_metECALBadCalib.c_str(), &fInEvent.metECALBadCalib, &fInEvent.b_metECALBadCalib);

  fInTree->SetBranchAddress(fInEvent.s_nvtx.c_str(), &fInEvent.nvtx, &fInEvent.b_nvtx);
  fInTree->SetBranchAddress(fInEvent.s_vtxX.c_str(), &fInEvent.vtxX, &fInEvent.b_vtxX);
  fInTree->SetBranchAddress(fInEvent.s_vtxY.c_str(), &fInEvent.vtxY, &fInEvent.b_vtxY);
  fInTree->SetBranchAddress(fInEvent.s_vtxZ.c_str(), &fInEvent.vtxZ, &fInEvent.b_vtxZ);
  fInTree->SetBranchAddress(fInEvent.s_rho.c_str(), &fInEvent.rho, &fInEvent.b_rho);


  fInTree->SetBranchAddress(fInEvent.s_nrechits.c_str(), &fInEvent.nrechits, &fInEvent.b_nrechits);
  fInTree->SetBranchAddress(fInEvent.s_nkurechits.c_str(), &fInEvent.nkurechits, &fInEvent.b_nkurechits);
  //if( hasMultiKURecHit ){
  //fInTree->SetBranchAddress("nkuStcrechits", &nkuStcrechits, &b_nkuStcrechits);
  //fInTree->SetBranchAddress("nkuNotrechits", &nkuNotrechits, &b_nkuNotrechits);
  //fInTree->SetBranchAddress("nkuNotStcrechits", &nkuNotStcrechits, &b_nkuNotStcrechits);
 // }

  if (fInConfig.storeRecHits)
  {
    // fInTree->SetBranchAddress(fInRecHits.s_X.c_str(), &fInRecHits.X, &fInRecHits.b_X);
    // fInTree->SetBranchAddress(fInRecHits.s_Y.c_str(), &fInRecHits.Y, &fInRecHits.b_Y);
    // fInTree->SetBranchAddress(fInRecHits.s_Z.c_str(), &fInRecHits.Z, &fInRecHits.b_Z);
    fInTree->SetBranchAddress(fInRecHits.s_E.c_str(), &fInRecHits.E, &fInRecHits.b_E);
    fInTree->SetBranchAddress(fInRecHits.s_time.c_str(), &fInRecHits.time, &fInRecHits.b_time);
    // fInTree->SetBranchAddress(fInRecHits.s_timeErr.c_str(), &fInRecHits.timeErr, &fInRecHits.b_timeErr);
    fInTree->SetBranchAddress(fInRecHits.s_TOF.c_str(), &fInRecHits.TOF, &fInRecHits.b_TOF);
    fInTree->SetBranchAddress(fInRecHits.s_ID.c_str(), &fInRecHits.ID, &fInRecHits.b_ID);
    // fInTree->SetBranchAddress(fInRecHits.s_isOOT.c_str(), &fInRecHits.isOOT, &fInRecHits.b_isOOT);
    fInTree->SetBranchAddress(fInRecHits.s_isGS6.c_str(), &fInRecHits.isGS6, &fInRecHits.b_isGS6);
    fInTree->SetBranchAddress(fInRecHits.s_isGS1.c_str(), &fInRecHits.isGS1, &fInRecHits.b_isGS1);
    fInTree->SetBranchAddress(fInRecHits.s_adcToGeV.c_str(), &fInRecHits.adcToGeV, &fInRecHits.b_adcToGeV);
    fInTree->SetBranchAddress(fInRecHits.s_ped12.c_str(), &fInRecHits.ped12, &fInRecHits.b_ped12);
    fInTree->SetBranchAddress(fInRecHits.s_ped6.c_str(), &fInRecHits.ped6, &fInRecHits.b_ped6);
    fInTree->SetBranchAddress(fInRecHits.s_ped1.c_str(), &fInRecHits.ped1, &fInRecHits.b_ped1);
    fInTree->SetBranchAddress(fInRecHits.s_pedrms12.c_str(), &fInRecHits.pedrms12, &fInRecHits.b_pedrms12);
    fInTree->SetBranchAddress(fInRecHits.s_pedrms6.c_str(), &fInRecHits.pedrms6, &fInRecHits.b_pedrms6);
    fInTree->SetBranchAddress(fInRecHits.s_pedrms1.c_str(), &fInRecHits.pedrms1, &fInRecHits.b_pedrms1);
  

  }

  fInTree->SetBranchAddress(fInEvent.s_nphotons.c_str(), &fInEvent.nphotons, &fInEvent.b_nphotons);
  for (auto ipho = 0; ipho < Common::nPhotons; ipho++) 
  {
    auto & pho = fInPhos[ipho];
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_E.c_str(),ipho), &pho.E, &pho.b_E);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_pt.c_str(),ipho), &pho.pt, &pho.b_pt);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_eta.c_str(),ipho), &pho.eta, &pho.b_eta);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_phi.c_str(),ipho), &pho.phi, &pho.b_phi);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_scE.c_str(),ipho), &pho.scE, &pho.b_scE);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_sceta.c_str(),ipho), &pho.sceta, &pho.b_sceta);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_scphi.c_str(),ipho), &pho.scphi, &pho.b_scphi);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_HoE.c_str(),ipho), &pho.HoE, &pho.b_HoE);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_r9.c_str(),ipho), &pho.r9, &pho.b_r9);
    if( hasUrecDigi ) fInTree->SetBranchAddress(Form("%s_%i",pho.s_tdz.c_str(),ipho), &pho.tdz, &pho.b_tdz);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_ChgHadIso.c_str(),ipho), &pho.ChgHadIso, &pho.b_ChgHadIso);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_NeuHadIso.c_str(),ipho), &pho.NeuHadIso, &pho.b_NeuHadIso);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_PhoIso.c_str(),ipho), &pho.PhoIso, &pho.b_PhoIso);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_EcalPFClIso.c_str(),ipho), &pho.EcalPFClIso, &pho.b_EcalPFClIso);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_HcalPFClIso.c_str(),ipho), &pho.HcalPFClIso, &pho.b_HcalPFClIso);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_TrkIso.c_str(),ipho), &pho.TrkIso, &pho.b_TrkIso);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_ChgHadIsoC.c_str(),ipho), &pho.ChgHadIsoC, &pho.b_ChgHadIsoC);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_NeuHadIsoC.c_str(),ipho), &pho.NeuHadIsoC, &pho.b_NeuHadIsoC);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_PhoIsoC.c_str(),ipho), &pho.PhoIsoC, &pho.b_PhoIsoC);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_EcalPFClIsoC.c_str(),ipho), &pho.EcalPFClIsoC, &pho.b_EcalPFClIsoC);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_HcalPFClIsoC.c_str(),ipho), &pho.HcalPFClIsoC, &pho.b_HcalPFClIsoC);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_TrkIsoC.c_str(),ipho), &pho.TrkIsoC, &pho.b_TrkIsoC);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_sieie.c_str(),ipho), &pho.sieie, &pho.b_sieie);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_sipip.c_str(),ipho), &pho.sipip, &pho.b_sipip);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_sieip.c_str(),ipho), &pho.sieip, &pho.b_sieip);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_e2x2.c_str(),ipho), &pho.e2x2, &pho.b_e2x2);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_e3x3.c_str(),ipho), &pho.e3x3, &pho.b_e3x3);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_e5x5.c_str(),ipho), &pho.e5x5, &pho.b_e5x5);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_smaj.c_str(),ipho), &pho.smaj, &pho.b_smaj);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_smin.c_str(),ipho), &pho.smin, &pho.b_smin);
    // fInTree->SetBranchAddress(Form("%s_%i",pho.s_alpha.c_str(),ipho), &pho.alpha, &pho.b_alpha);
    if (fInConfig.storeRecHits)
    {
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seed.c_str(),ipho), &pho.seed, &pho.b_seed);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_recHits.c_str(),ipho), &pho.recHits, &pho.b_recHits);
      //fInTree->SetBranchAddress(Form("%s_%i",pho.s_kurecHits.c_str(),ipho), &pho.kurecHits, &pho.b_kurecHits);
    }
    else
    {
      // fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedX.c_str(),ipho), &pho.seedX, &pho.b_seedX);
      // fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedY.c_str(),ipho), &pho.seedY, &pho.b_seedY);
      // fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedZ.c_str(),ipho), &pho.seedZ, &pho.b_seedZ);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedE.c_str(),ipho), &pho.seedE, &pho.b_seedE);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedtime.c_str(),ipho), &pho.seedtime, &pho.b_seedtime);
      // fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedtimeErr.c_str(),ipho), &pho.seedtimeErr, &pho.b_seedtimeErr);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedTOF.c_str(),ipho), &pho.seedTOF, &pho.b_seedTOF);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedID.c_str(),ipho), &pho.seedID, &pho.b_seedID);
      // fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedisOOT.c_str(),ipho), &pho.seedisOOT, &pho.b_seedisOOT);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedisGS6.c_str(),ipho), &pho.seedisGS6, &pho.b_seedisGS6);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedisGS1.c_str(),ipho), &pho.seedisGS1, &pho.b_seedisGS1);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedadcToGeV.c_str(),ipho), &pho.seedadcToGeV, &pho.b_seedadcToGeV);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedped12.c_str(),ipho), &pho.seedped12, &pho.b_seedped12);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedped6.c_str(),ipho), &pho.seedped6, &pho.b_seedped6);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedped1.c_str(),ipho), &pho.seedped1, &pho.b_seedped1);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedpedrms12.c_str(),ipho), &pho.seedpedrms12, &pho.b_seedpedrms12);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedpedrms6.c_str(),ipho), &pho.seedpedrms6, &pho.b_seedpedrms6);
      fInTree->SetBranchAddress(Form("%s_%i",pho.s_seedpedrms1.c_str(),ipho), &pho.seedpedrms1, &pho.b_seedpedrms1);

    }
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_suisseX.c_str(),ipho), &pho.suisseX, &pho.b_suisseX);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_isOOT.c_str(),ipho), &pho.isOOT, &pho.b_isOOT);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_isEB.c_str(),ipho), &pho.isEB, &pho.b_isEB);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_isHLT.c_str(),ipho), &pho.isHLT, &pho.b_isHLT);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_isTrk.c_str(),ipho), &pho.isTrk, &pho.b_isTrk);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_passEleVeto.c_str(),ipho), &pho.passEleVeto, &pho.b_passEleVeto);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_hasPixSeed.c_str(),ipho), &pho.hasPixSeed, &pho.b_hasPixSeed);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_gedID.c_str(),ipho), &pho.gedID, &pho.b_gedID);
    fInTree->SetBranchAddress(Form("%s_%i",pho.s_ootID.c_str(),ipho), &pho.ootID, &pho.b_ootID);
    
  }
}

void Skimmer::InitAndSetOutConfig()
{
  // Make the branches
  fOutConfigTree->Branch(fOutConfig.s_blindSF.c_str(), &fOutConfig.blindSF);
  fOutConfigTree->Branch(fOutConfig.s_applyBlindSF.c_str(), &fOutConfig.applyBlindSF);
  fOutConfigTree->Branch(fOutConfig.s_blindMET.c_str(), &fOutConfig.blindMET);
  fOutConfigTree->Branch(fOutConfig.s_applyBlindMET.c_str(), &fOutConfig.applyBlindMET);
  fOutConfigTree->Branch(fOutConfig.s_jetpTmin.c_str(), &fOutConfig.jetpTmin);
  fOutConfigTree->Branch(fOutConfig.s_jetEtamax.c_str(), &fOutConfig.jetEtamax);
  fOutConfigTree->Branch(fOutConfig.s_jetIDmin.c_str(), &fOutConfig.jetIDmin);
  fOutConfigTree->Branch(fOutConfig.s_rhEmin.c_str(), &fOutConfig.rhEmin);
  fOutConfigTree->Branch(fOutConfig.s_phpTmin.c_str(), &fOutConfig.phpTmin);
  fOutConfigTree->Branch(fOutConfig.s_phIDmin.c_str(), &fOutConfig.phIDmin_s);
  fOutConfigTree->Branch(fOutConfig.s_seedTimemin.c_str(), &fOutConfig.seedTimemin);
  fOutConfigTree->Branch(fOutConfig.s_splitPho.c_str(), &fOutConfig.splitPho);
  fOutConfigTree->Branch(fOutConfig.s_onlyGED.c_str(), &fOutConfig.onlyGED);
  fOutConfigTree->Branch(fOutConfig.s_onlyOOT.c_str(), &fOutConfig.onlyOOT);
  // fOutConfigTree->Branch(fOutConfig.s_ellowpTmin.c_str(), &fOutConfig.ellowpTmin);
  // fOutConfigTree->Branch(fOutConfig.s_elhighpTmin.c_str(), &fOutConfig.elhighpTmin);
  // fOutConfigTree->Branch(fOutConfig.s_mulowpTmin.c_str(), &fOutConfig.mulowpTmin);
  // fOutConfigTree->Branch(fOutConfig.s_muhighpTmin.c_str(), &fOutConfig.muhighpTmin);
  fOutConfigTree->Branch(fOutConfig.s_storeRecHits.c_str(), &fOutConfig.storeRecHits);
  fOutConfigTree->Branch(fOutConfig.s_applyTrigger.c_str(), &fOutConfig.applyTrigger);
  fOutConfigTree->Branch(fOutConfig.s_minHT.c_str(), &fOutConfig.minHT);
  fOutConfigTree->Branch(fOutConfig.s_applyHT.c_str(), &fOutConfig.applyHT);
  fOutConfigTree->Branch(fOutConfig.s_phgoodpTmin.c_str(), &fOutConfig.phgoodpTmin);
  fOutConfigTree->Branch(fOutConfig.s_phgoodIDmin.c_str(), &fOutConfig.phgoodIDmin_s);
  fOutConfigTree->Branch(fOutConfig.s_applyPhGood.c_str(), &fOutConfig.applyPhGood);
  fOutConfigTree->Branch(fOutConfig.s_dRmin.c_str(), &fOutConfig.dRmin);
  fOutConfigTree->Branch(fOutConfig.s_pTres.c_str(), &fOutConfig.pTres);
  fOutConfigTree->Branch(fOutConfig.s_genpTres.c_str(), &fOutConfig.genpTres);
  fOutConfigTree->Branch(fOutConfig.s_trackdRmin.c_str(), &fOutConfig.trackdRmin);
  fOutConfigTree->Branch(fOutConfig.s_trackpTmin.c_str(), &fOutConfig.trackpTmin);
  fOutConfigTree->Branch(fOutConfig.s_genjetdRmin.c_str(), &fOutConfig.genjetdRmin);
  fOutConfigTree->Branch(fOutConfig.s_genjetpTfactor.c_str(), &fOutConfig.genjetpTfactor);
  // fOutConfigTree->Branch(fOutConfig.s_leptondRmin.c_str(), &fOutConfig.leptondRmin);
  fOutConfigTree->Branch(fOutConfig.s_smearjetEmin.c_str(), &fOutConfig.smearjetEmin);
  fOutConfigTree->Branch(fOutConfig.s_inputPaths.c_str(), &fOutConfig.inputPaths_s);
  fOutConfigTree->Branch(fOutConfig.s_inputFilters.c_str(), &fOutConfig.inputFilters_s);
  fOutConfigTree->Branch(fOutConfig.s_inputFlags.c_str(), &fOutConfig.inputFlags_s);
  fOutConfigTree->Branch(fOutConfig.s_isGMSB.c_str(), &fOutConfig.isGMSB);
  fOutConfigTree->Branch(fOutConfig.s_isHVDS.c_str(), &fOutConfig.isHVDS);
  fOutConfigTree->Branch(fOutConfig.s_isBkgd.c_str(), &fOutConfig.isBkgd);
  fOutConfigTree->Branch(fOutConfig.s_isToy.c_str(), &fOutConfig.isToy);
  fOutConfigTree->Branch(fOutConfig.s_isADD.c_str(), &fOutConfig.isADD);
  fOutConfigTree->Branch(fOutConfig.s_xsec.c_str(), &fOutConfig.xsec);
  fOutConfigTree->Branch(fOutConfig.s_filterEff.c_str(), &fOutConfig.filterEff);
  fOutConfigTree->Branch(fOutConfig.s_BR.c_str(), &fOutConfig.BR);

  // extra branches
  fOutConfigTree->Branch(fOutConfig.s_sumWgts.c_str(), &fOutConfig.sumWgts);
  fOutConfigTree->Branch(fOutConfig.s_sampleWeight.c_str(), &fOutConfig.sampleWeight);
  fOutConfigTree->Branch(fOutConfig.s_puWeights.c_str(), &fOutConfig.puWeights);

  // Now set the values of the branches
  fOutConfig.blindSF = fInConfig.blindSF;
  fOutConfig.applyBlindSF = fInConfig.applyBlindSF;
  fOutConfig.blindMET = fInConfig.blindMET;
  fOutConfig.applyBlindMET = fInConfig.applyBlindMET;
  fOutConfig.jetpTmin = fInConfig.jetpTmin;
  fOutConfig.jetEtamax = fInConfig.jetEtamax;
  fOutConfig.jetIDmin = fInConfig.jetIDmin;
  fOutConfig.rhEmin = fInConfig.rhEmin;
  fOutConfig.phpTmin = fInConfig.phpTmin;
  fOutConfig.phIDmin_s = fInConfig.phIDmin->c_str();
  fOutConfig.seedTimemin = fInConfig.seedTimemin;
  fOutConfig.splitPho = fInConfig.splitPho;
  fOutConfig.onlyGED = fInConfig.onlyGED;
  fOutConfig.onlyOOT = fInConfig.onlyOOT;
  // fOutConfig.ellowpTmin = fInConfig.ellowpTmin;
  // fOutConfig.elhighpTmin = fInConfig.elhighpTmin;
  // fOutConfig.mulowpTmin = fInConfig.mulowpTmin;
  // fOutConfig.muhighpTmin = fInConfig.muhighpTmin;
  fOutConfig.storeRecHits = false; // drop these now!
  fOutConfig.applyTrigger = fInConfig.applyTrigger;
  fOutConfig.minHT = fInConfig.minHT;
  fOutConfig.applyHT = fInConfig.applyHT;
  fOutConfig.phgoodpTmin = fInConfig.phgoodpTmin;
  fOutConfig.phgoodIDmin_s = fInConfig.phgoodIDmin->c_str();
  fOutConfig.applyPhGood = fInConfig.applyPhGood;
  fOutConfig.dRmin = fInConfig.dRmin;
  fOutConfig.pTres = fInConfig.pTres;
  fOutConfig.genpTres = fInConfig.genpTres;
  fOutConfig.trackdRmin = fInConfig.trackdRmin;
  fOutConfig.trackpTmin = fInConfig.trackpTmin;
  fOutConfig.genjetdRmin = fInConfig.genjetdRmin;
  fOutConfig.genjetpTfactor = fInConfig.genjetpTfactor;
  // fOutConfig.leptondRmin = fInConfig.leptondRmin;
  fOutConfig.smearjetEmin = fInConfig.smearjetEmin;
  fOutConfig.inputPaths_s = fInConfig.inputPaths->c_str();
  fOutConfig.inputFilters_s = fInConfig.inputFilters->c_str();
  fOutConfig.inputFlags_s = fInConfig.inputFlags->c_str();
  fOutConfig.isGMSB = fInConfig.isGMSB;
  fOutConfig.isHVDS = fInConfig.isHVDS;
  fOutConfig.isBkgd = fInConfig.isBkgd;
  fOutConfig.isToy = fInConfig.isToy;
  fOutConfig.isADD = fInConfig.isADD;
  fOutConfig.xsec = fInConfig.xsec;
  fOutConfig.filterEff = fInConfig.filterEff;
  fOutConfig.BR = fInConfig.BR;

  // include computed variables for ease of use
  fOutConfig.sumWgts = fSumWgts;
  fOutConfig.sampleWeight = fSampleWeight;
  fOutConfig.puWeights = fPUWeights;

  // and fill it once
  fOutConfigTree->Fill();
}

void Skimmer::InitOutTree()
{
  Skimmer::InitOutStructs();
  Skimmer::InitOutBranches();
}

void Skimmer::InitOutStructs()
{

  fOutPhos.clear();
//  fOutPhos.resize(Common::nPhotons);
  fOutPhos.resize(Common::nPhotons+2);

}

void Skimmer::InitOutBranches()
{

  fOutTree->Branch(fOutEvent.s_run.c_str(), &fOutEvent.run);
  fOutTree->Branch(fOutEvent.s_lumi.c_str(), &fOutEvent.lumi);
  fOutTree->Branch(fOutEvent.s_event.c_str(), &fOutEvent.event);

  fOutTree->Branch("gZmass",&gZmass);
  fOutTree->Branch("gdR",&gdR);
  fOutTree->Branch("bunch_crossing",&bunch_crossing);
  fOutTree->Branch("num_bunch",&num_bunch);
  fOutTree->Branch("subtrain_position",&subtrain_position);
  fOutTree->Branch("train_position",&train_position);
  fOutTree->Branch("subtrain_number",&subtrain_number);
  fOutTree->Branch("train_number",&train_number);
  fOutTree->Branch("nxtal_sep",&nxtal_sep);

  fOutTree->Branch(fOutEvent.s_hltSignal.c_str(), &fOutEvent.hltSignal);
  fOutTree->Branch(fOutEvent.s_hltRefPhoID.c_str(), &fOutEvent.hltRefPhoID);
  fOutTree->Branch(fOutEvent.s_hltRefDispID.c_str(), &fOutEvent.hltRefDispID);
  fOutTree->Branch(fOutEvent.s_hltRefHT.c_str(), &fOutEvent.hltRefHT);
  fOutTree->Branch(fOutEvent.s_hltPho50.c_str(), &fOutEvent.hltPho50);
  fOutTree->Branch(fOutEvent.s_hltPho200.c_str(), &fOutEvent.hltPho200);
  fOutTree->Branch(fOutEvent.s_hltDiPho70.c_str(), &fOutEvent.hltDiPho70);
  fOutTree->Branch(fOutEvent.s_hltDiPho3022M90.c_str(), &fOutEvent.hltDiPho3022M90);
  fOutTree->Branch(fOutEvent.s_hltDiPho30PV18PV.c_str(), &fOutEvent.hltDiPho30PV18PV);
  fOutTree->Branch(fOutEvent.s_hltEle32WPT.c_str(), &fOutEvent.hltEle32WPT);
  fOutTree->Branch(fOutEvent.s_hltDiEle33MW.c_str(), &fOutEvent.hltDiEle33MW);
  fOutTree->Branch(fOutEvent.s_hltJet500.c_str(), &fOutEvent.hltJet500);

  fOutTree->Branch(fOutEvent.s_nvtx.c_str(), &fOutEvent.nvtx);
  fOutTree->Branch(fOutEvent.s_vtxX.c_str(), &fOutEvent.vtxX);
  fOutTree->Branch(fOutEvent.s_vtxY.c_str(), &fOutEvent.vtxY);
  fOutTree->Branch(fOutEvent.s_vtxZ.c_str(), &fOutEvent.vtxZ);
  fOutTree->Branch(fOutEvent.s_rho.c_str(), &fOutEvent.rho);

  fOutTree->Branch(fOutEvent.s_t1pfMETpt.c_str(), &fOutEvent.t1pfMETpt);
  fOutTree->Branch(fOutEvent.s_t1pfMETphi.c_str(), &fOutEvent.t1pfMETphi);
  fOutTree->Branch(fOutEvent.s_t1pfMETsumEt.c_str(), &fOutEvent.t1pfMETsumEt);

  fOutTree->Branch(fOutEvent.s_njets.c_str(), &fOutEvent.njets);
  if (fSkim != SkimType::DiXtal)
  {
    fOutTree->Branch(fOutJets.s_E.c_str(), &fOutJets.E_f);
    fOutTree->Branch(fOutJets.s_pt.c_str(), &fOutJets.pt_f);
    fOutTree->Branch(fOutJets.s_phi.c_str(), &fOutJets.phi_f);
    fOutTree->Branch(fOutJets.s_eta.c_str(), &fOutJets.eta_f);
    fOutTree->Branch(fOutJets.s_ID.c_str(), &fOutJets.ID_i);
  }

  
  fOutTree->Branch(fOutEvent.s_nrechits.c_str(), &fOutEvent.nrechits);
  fOutTree->Branch(fOutEvent.s_nkurechits.c_str(), &fOutEvent.nkurechits);
  if( hasMultiKURecHit ){
  //fOutTree->Branch("nkuStcrechits", &nkuStcrechits);
  //fOutTree->Branch("nkuNotrechits", &nkuNotrechits);
  //fOutTree->Branch("nkuNotStcrechits", &nkuNotStcrechits);
  fOutTree->Branch("out_npho_recHits_0", &out_npho_recHits_0);
  fOutTree->Branch("out_npho_recHits_1", &out_npho_recHits_1);
  fOutTree->Branch("out_npho_recHits_2", &out_npho_recHits_2);
  fOutTree->Branch("out_npho_recHits_3", &out_npho_recHits_3);
  fOutTree->Branch("out_fInRecHits_E", &out_fInRecHits_E);
  fOutTree->Branch("out_fInRecHits_ID", &out_fInRecHits_ID);
  fOutTree->Branch("out_fInRecHits_time", &out_fInRecHits_time);
  fOutTree->Branch("out_fInRecHits_TOF", &out_fInRecHits_TOF);
  fOutTree->Branch("out_kurhtime", &out_kurhtime);
  fOutTree->Branch("out_kurhID", &out_kurhID);
  fOutTree->Branch("out_kuStcrhtime", &out_kuStcrhtime);
  //fOutTree->Branch("out_kuNotrhtime", &out_kuNotrhtime);
  fOutTree->Branch("out_kuNotStcrhtime", &out_kuNotStcrhtime);
  fOutTree->Branch("out_kuWootStcrhtime", &out_kuWootStcrhtime);
  }
  fOutTree->Branch("nurechits", &nurechits);
  fOutTree->Branch("ndigis", &ndigis);

  fOutTree->Branch(fOutEvent.s_nphotons.c_str(), &fOutEvent.nphotons);
  for (auto ipho = 0; ipho < fNOutPhos; ipho++) 
  {
    auto & pho = fOutPhos[ipho];
    fOutTree->Branch(Form("%s_%i",pho.s_E.c_str(),ipho), &pho.E);
    fOutTree->Branch(Form("%s_%i",pho.s_pt.c_str(),ipho), &pho.pt);
    fOutTree->Branch(Form("%s_%i",pho.s_eta.c_str(),ipho), &pho.eta);
    fOutTree->Branch(Form("%s_%i",pho.s_phi.c_str(),ipho), &pho.phi);
    fOutTree->Branch(Form("%s_%i",pho.s_scE.c_str(),ipho), &pho.scE);
    fOutTree->Branch(Form("%s_%i",pho.s_sceta.c_str(),ipho), &pho.sceta);
    fOutTree->Branch(Form("%s_%i",pho.s_scphi.c_str(),ipho), &pho.scphi);
    fOutTree->Branch(Form("%s_%i",pho.s_HoE.c_str(),ipho), &pho.HoE);
    fOutTree->Branch(Form("%s_%i",pho.s_r9.c_str(),ipho), &pho.r9);
    fOutTree->Branch(Form("%s_%i",pho.s_tdz.c_str(),ipho), &pho.tdz);
    fOutTree->Branch(Form("%s_%i",pho.s_ChgHadIso.c_str(),ipho), &pho.ChgHadIso);
    fOutTree->Branch(Form("%s_%i",pho.s_NeuHadIso.c_str(),ipho), &pho.NeuHadIso);
    fOutTree->Branch(Form("%s_%i",pho.s_PhoIso.c_str(),ipho), &pho.PhoIso);
    fOutTree->Branch(Form("%s_%i",pho.s_EcalPFClIso.c_str(),ipho), &pho.EcalPFClIso);
    fOutTree->Branch(Form("%s_%i",pho.s_HcalPFClIso.c_str(),ipho), &pho.HcalPFClIso);
    fOutTree->Branch(Form("%s_%i",pho.s_TrkIso.c_str(),ipho), &pho.TrkIso);
    // fOutTree->Branch(Form("%s_%i",pho.s_ChgHadIsoC.c_str(),ipho), &pho.ChgHadIsoC);
    // fOutTree->Branch(Form("%s_%i",pho.s_NeuHadIsoC.c_str(),ipho), &pho.NeuHadIsoC);
    // fOutTree->Branch(Form("%s_%i",pho.s_PhoIsoC.c_str(),ipho), &pho.PhoIsoC);
    // fOutTree->Branch(Form("%s_%i",pho.s_EcalPFClIsoC.c_str(),ipho), &pho.EcalPFClIsoC);
    // fOutTree->Branch(Form("%s_%i",pho.s_HcalPFClIsoC.c_str(),ipho), &pho.HcalPFClIsoC);
    // fOutTree->Branch(Form("%s_%i",pho.s_TrkIsoC.c_str(),ipho), &pho.TrkIsoC);
    fOutTree->Branch(Form("%s_%i",pho.s_sieie.c_str(),ipho), &pho.sieie);
    // fOutTree->Branch(Form("%s_%i",pho.s_sipip.c_str(),ipho), &pho.sipip);
    // fOutTree->Branch(Form("%s_%i",pho.s_sieip.c_str(),ipho), &pho.sieip);
    // fOutTree->Branch(Form("%s_%i",pho.s_e2x2.c_str(),ipho), &pho.e2x2);
    // fOutTree->Branch(Form("%s_%i",pho.s_e3x3.c_str(),ipho), &pho.e3x3);
    // fOutTree->Branch(Form("%s_%i",pho.s_e5x5.c_str(),ipho), &pho.e5x5);
    fOutTree->Branch(Form("%s_%i",pho.s_smaj.c_str(),ipho), &pho.smaj);
    fOutTree->Branch(Form("%s_%i",pho.s_smin.c_str(),ipho), &pho.smin);
    // fOutTree->Branch(Form("%s_%i",pho.s_alpha.c_str(),ipho), &pho.alpha);
    fOutTree->Branch(Form("%s_%i",pho.s_suisseX.c_str(),ipho), &pho.suisseX);
    // fOutTree->Branch(Form("%s_%i",pho.s_seedX.c_str(),ipho), &pho.seedX);
    // fOutTree->Branch(Form("%s_%i",pho.s_seedY.c_str(),ipho), &pho.seedY);
    // fOutTree->Branch(Form("%s_%i",pho.s_seedZ.c_str(),ipho), &pho.seedZ);
    fOutTree->Branch(Form("%s_%i",pho.s_seedE.c_str(),ipho), &pho.seedE);
    fOutTree->Branch(Form("%s_%i",pho.s_seedtime.c_str(),ipho), &pho.seedtime);
    // fOutTree->Branch(Form("%s_%i",pho.s_seedtimeErr.c_str(),ipho), &pho.seedtimeErr);
    fOutTree->Branch(Form("%s_%i",pho.s_seedTOF.c_str(),ipho), &pho.seedTOF);
    fOutTree->Branch(Form("%s_%i",pho.s_seedID.c_str(),ipho), &pho.seedID);
    fOutTree->Branch(Form("%s_%i",pho.s_seedI1.c_str(),ipho), &pho.seedI1);
    fOutTree->Branch(Form("%s_%i",pho.s_seedI2.c_str(),ipho), &pho.seedI2);
    fOutTree->Branch(Form("%s_%i",pho.s_seedEcal.c_str(),ipho), &pho.seedEcal);
    // fOutTree->Branch(Form("%s_%i",pho.s_seedisOOT.c_str(),ipho), &pho.seedisOOT);
    fOutTree->Branch(Form("%s_%i",pho.s_seedisGS6.c_str(),ipho), &pho.seedisGS6);
    fOutTree->Branch(Form("%s_%i",pho.s_seedisGS1.c_str(),ipho), &pho.seedisGS1);
    fOutTree->Branch(Form("%s_%i",pho.s_seedadcToGeV.c_str(),ipho), &pho.seedadcToGeV);
    fOutTree->Branch(Form("%s_%i",pho.s_seedped12.c_str(),ipho), &pho.seedped12);
    fOutTree->Branch(Form("%s_%i",pho.s_seedped6.c_str(),ipho), &pho.seedped6);
    fOutTree->Branch(Form("%s_%i",pho.s_seedped1.c_str(),ipho), &pho.seedped1);
    fOutTree->Branch(Form("%s_%i",pho.s_seedpedrms12.c_str(),ipho), &pho.seedpedrms12);
    fOutTree->Branch(Form("%s_%i",pho.s_seedpedrms6.c_str(),ipho), &pho.seedpedrms6);
    fOutTree->Branch(Form("%s_%i",pho.s_seedpedrms1.c_str(),ipho), &pho.seedpedrms1);

    fOutTree->Branch(Form("%s_%i",pho.s_seedkuE.c_str(),ipho), &pho.seedkuE);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkutime.c_str(),ipho), &pho.seedkutime);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkutimeErr.c_str(),ipho), &pho.seedkutimeErr);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuTOF.c_str(),ipho), &pho.seedkuTOF);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuID.c_str(),ipho), &pho.seedkuID);

    if( hasMultiKURecHit ){
    //fOutTree->Branch(Form("%s_%i",pho.s_seedkuStcE.c_str(),ipho), &pho.seedkuStcE);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuStctime.c_str(),ipho), &pho.seedkuStctime);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuStctimeErr.c_str(),ipho), &pho.seedkuStctimeErr);
    //fOutTree->Branch(Form("%s_%i",pho.s_seedkuStcTOF.c_str(),ipho), &pho.seedkuStcTOF);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuStcID.c_str(),ipho), &pho.seedkuStcID);

    //fOutTree->Branch(Form("%s_%i",pho.s_seedkuNotE.c_str(),ipho), &pho.seedkuNotE);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuNottime.c_str(),ipho), &pho.seedkuNottime);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuNottimeErr.c_str(),ipho), &pho.seedkuNottimeErr);
    //fOutTree->Branch(Form("%s_%i",pho.s_seedkuNotTOF.c_str(),ipho), &pho.seedkuNotTOF);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuNotID.c_str(),ipho), &pho.seedkuNotID);

    //fOutTree->Branch(Form("%s_%i",pho.s_seedkuNotStcE.c_str(),ipho), &pho.seedkuNotStcE);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuNotStctime.c_str(),ipho), &pho.seedkuNotStctime);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuNotStctimeErr.c_str(),ipho), &pho.seedkuNotStctimeErr);
    //fOutTree->Branch(Form("%s_%i",pho.s_seedkuNotStcTOF.c_str(),ipho), &pho.seedkuNotStcTOF);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuNotStcID.c_str(),ipho), &pho.seedkuNotStcID);

    //fOutTree->Branch(Form("%s_%i",pho.s_seedkuWootStcE.c_str(),ipho), &pho.seedkuWootStcE);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuWootStctime.c_str(),ipho), &pho.seedkuWootStctime);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuWootStctimeErr.c_str(),ipho), &pho.seedkuWootStctimeErr);
    //fOutTree->Branch(Form("%s_%i",pho.s_seedkuWootStcTOF.c_str(),ipho), &pho.seedkuWootStcTOF);
    fOutTree->Branch(Form("%s_%i",pho.s_seedkuWootStcID.c_str(),ipho), &pho.seedkuWootStcID);

    }

    fOutTree->Branch(Form("%s_%i",pho.s_seedootA0.c_str(),ipho), &pho.seedootA0);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootA1.c_str(),ipho), &pho.seedootA1);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootA2.c_str(),ipho), &pho.seedootA2);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootA3.c_str(),ipho), &pho.seedootA3);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootA4.c_str(),ipho), &pho.seedootA4);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootA5.c_str(),ipho), &pho.seedootA5);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootA6.c_str(),ipho), &pho.seedootA6);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootA7.c_str(),ipho), &pho.seedootA7);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootA8.c_str(),ipho), &pho.seedootA8);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootA9.c_str(),ipho), &pho.seedootA9);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootMax.c_str(),ipho), &pho.seedootMax);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootMbefore.c_str(),ipho), &pho.seedootMbefore);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootMafter.c_str(),ipho), &pho.seedootMafter);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootSign.c_str(),ipho), &pho.seedootSign);
    fOutTree->Branch(Form("%s_%i",pho.s_seedootVsum.c_str(),ipho), &pho.seedootVsum);
    fOutTree->Branch(Form("%s_%i",pho.s_isOOT.c_str(),ipho), &pho.isOOT);
    fOutTree->Branch(Form("%s_%i",pho.s_isEB.c_str(),ipho), &pho.isEB);
    fOutTree->Branch(Form("%s_%i",pho.s_isHLT.c_str(),ipho), &pho.isHLT);
    fOutTree->Branch(Form("%s_%i",pho.s_isTrk.c_str(),ipho), &pho.isTrk);
    fOutTree->Branch(Form("%s_%i",pho.s_passEleVeto.c_str(),ipho), &pho.passEleVeto);
    fOutTree->Branch(Form("%s_%i",pho.s_hasPixSeed.c_str(),ipho), &pho.hasPixSeed);
    fOutTree->Branch(Form("%s_%i",pho.s_gedID.c_str(),ipho), &pho.gedID);
    fOutTree->Branch(Form("%s_%i",pho.s_ootID.c_str(),ipho), &pho.ootID);

    // Derived types
    fOutTree->Branch(Form("%s_%i",pho.s_seedTT.c_str(),ipho), &pho.seedTT);

    if (fInConfig.storeRecHits)
    {
      fOutTree->Branch(Form("%s_%i",pho.s_nrechits.c_str(),ipho), &pho.nrechits);
      fOutTree->Branch(Form("%s_%i",pho.s_nrechitsLT120.c_str(),ipho), &pho.nrechitsLT120);
      fOutTree->Branch(Form("%s_%i",pho.s_meantime.c_str(),ipho), &pho.meantime);
      fOutTree->Branch(Form("%s_%i",pho.s_meantimeLT120.c_str(),ipho), &pho.meantimeLT120);
      fOutTree->Branch(Form("%s_%i",pho.s_weightedtime.c_str(),ipho), &pho.weightedtime);
      fOutTree->Branch(Form("%s_%i",pho.s_weightedtimeLT120.c_str(),ipho), &pho.weightedtimeLT120);
      fOutTree->Branch(Form("%s_%i",pho.s_weightedtimeTOF.c_str(),ipho), &pho.weightedtimeTOF);
      fOutTree->Branch(Form("%s_%i",pho.s_weightedtimeLT120TOF.c_str(),ipho), &pho.weightedtimeLT120TOF);
    }
  } // end loop over nPhotons

  // add event weight
  fOutTree->Branch(fOutEvent.s_evtwgt.c_str(), &fOutEvent.evtwgt);
} 

void Skimmer::InitOutCutFlowHists()
{
  Skimmer::InitOutCutFlowHist(fInCutFlow,fOutCutFlow,Common::h_cutflowname);
  Skimmer::InitOutCutFlowHist(fInCutFlowWgt,fOutCutFlowWgt,Common::h_cutflow_wgtname);
  Skimmer::InitOutCutFlowHist(fInCutFlowWgt,fOutCutFlowScl,Common::h_cutflow_scaledname);

  // rescale input of scaled histogram by sample weight!
  fOutCutFlowScl->Scale(fSampleWeight);
  fOutCutFlowScl->SetTitle("Scaled");
  fOutCutFlowScl->GetYaxis()->SetTitle("nEvents");
}

void Skimmer::InitOutCutFlowHist(const TH1F * inh_cutflow, TH1F *& outh_cutflow, const TString & histname)
{
  // get cut flow labels
  const auto inNbinsX = inh_cutflow->GetNbinsX();
  for (auto ibin = 1; ibin <= inNbinsX; ibin++)
  {
    cutLabels[inh_cutflow->GetXaxis()->GetBinLabel(ibin)] = ibin;
  }
  auto inNbinsX_new = inNbinsX;

  // always add safety counter
  cutLabels["PreSkim"] = ++inNbinsX_new;

  // labels for each skim
  if (fSkim == SkimType::Standard)
  {
    cutLabels["nPhotons"] = ++inNbinsX_new;
    cutLabels["ph0isEB"] = ++inNbinsX_new;
    cutLabels["ph0pt70"] = ++inNbinsX_new;
    cutLabels["METFlag"] = ++inNbinsX_new;
  }
  else if (fSkim == SkimType::Zee)
  {
    cutLabels["diEleHLT"] = ++inNbinsX_new;
    cutLabels["goodPho1"] = ++inNbinsX_new;
    cutLabels["goodPho2"] = ++inNbinsX_new;
    cutLabels["diPhoMZrange"] = ++inNbinsX_new;
  }
  else if (fSkim == SkimType::DiXtal)
  {
    cutLabels["goodDiXtal"] = ++inNbinsX_new;
  }
  else
  {
    std::cerr << "How did this happen?? Somehow, fSkim was not setup! Exiting..." << std::endl;
    exit(1);
  }

  // common skim
  cutLabels["badPU"] = ++inNbinsX_new;

  // make new cut flow
  outh_cutflow = new TH1F(Form("%s",histname.Data()),inh_cutflow->GetTitle(),cutLabels.size(),0,cutLabels.size());
  outh_cutflow->Sumw2();

  for (const auto & cutlabel : cutLabels)
  {
    const auto ibin = cutlabel.second;

    outh_cutflow->GetXaxis()->SetBinLabel(ibin,cutlabel.first.c_str());

    if (ibin > inNbinsX) continue;

    outh_cutflow->SetBinContent(ibin,inh_cutflow->GetBinContent(ibin));
    outh_cutflow->SetBinError(ibin,inh_cutflow->GetBinError(ibin));
  }
  outh_cutflow->GetYaxis()->SetTitle(inh_cutflow->GetYaxis()->GetTitle());
}

void Skimmer::GetSampleWeight()
{
  // include normalization to lumi!!! ( do we need to multiply by * fInConfig.BR)
  fSampleWeight = (fIsMC ? fInConfig.xsec * fInConfig.filterEff * Common::EraMap["Full"].lumi * Common::invfbToinvpb / fSumWgts : 1.f); 
}

void Skimmer::GetPUWeights()
{
  for (auto ibin = 1; ibin <= fInPUWgtHist->GetNbinsX(); ibin++)
  {
    fPUWeights.emplace_back(fInPUWgtHist->GetBinContent(ibin));
  }
}

void Skimmer::FillPhoListStandard()
{      
  fPhoList.clear();
  for (auto ipho = 0; ipho < Common::nPhotons; ipho++)
  {
    fPhoList.emplace_back(ipho);
  }
}

///////////////////////////
// Configure the skimmer //
///////////////////////////

void Skimmer::SetupDefaults()
{
  fSkim = SkimType::Standard;
  fSumWgts = 1.f;
  isLHCInfo = false;
  hasUrecDigi = false;
  hasMultiKURecHit = false;
  fJEC = ECorr::Nominal;
  fJER = ECorr::Nominal;
  fPhoSc = ECorr::Nominal;
  fPhoSm = ECorr::Nominal;
}

void Skimmer::SetupSkimConfig()
{
 //std::cout << "Reading skim config..." << std::endl;

  std::ifstream infile(Form("%s",fSkimConfig.Data()),std::ios::in);
  std::string str;
  while (std::getline(infile,str))
  {
    if (str == "") continue;
    else if (str.find("skim_type=") != std::string::npos)
    {
      str = Common::RemoveDelim(str,"skim_type=");
      Skimmer::SetupSkimType(str);
    }
    else if (str.find("sum_wgts=") != std::string::npos)
    {
      str = Common::RemoveDelim(str,"sum_wgts=");
      fSumWgts = Common::Atof(str);
    }
    else if (str.find("puwgt_filename=") != std::string::npos)
    {
      str = Common::RemoveDelim(str,"puwgt_filename=");
      fPUWgtFileName = str;
    }
    else if (str.find("jet_scale=") != std::string::npos)
    {
      str = Common::RemoveDelim(str,"jet_scale=");
      Skimmer::SetupEnergyCorrection(str,fJEC,"jet_scale");
    }
    else if (str.find("jet_resol=") != std::string::npos)
    {
      str = Common::RemoveDelim(str,"jet_resol=");
      Skimmer::SetupEnergyCorrection(str,fJER,"jet_resol");
    }
    else if (str.find("pho_scale=") != std::string::npos)
    {
      str = Common::RemoveDelim(str,"pho_scale=");
      Skimmer::SetupEnergyCorrection(str,fPhoSc,"pho_scale");
    }
    else if (str.find("pho_smear=") != std::string::npos)
    {
      str = Common::RemoveDelim(str,"pho_smear=");
      Skimmer::SetupEnergyCorrection(str,fPhoSm,"pho_smear");
    }
    else if (str.find("isLHCInfo=") != std::string::npos)
    { 
      str = Common::RemoveDelim(str,"isLHCInfo=");
      if( str == "true" ) isLHCInfo = true;
      if( str == "false" ) isLHCInfo = false;
    }
    else if (str.find("hasUrecDigi=") != std::string::npos)
    {
      str = Common::RemoveDelim(str,"hasUrecDigi=");
      if( str == "true" ) hasUrecDigi = true;
      if( str == "false" ) hasUrecDigi = false;
    }
    else if (str.find("hasMultiKURecHit=") != std::string::npos)
    {
      str = Common::RemoveDelim(str,"hasMultiKURecHit=");
      if( str == "true" ) hasMultiKURecHit = true;
      if( str == "false" ) hasMultiKURecHit = false;
    }
    else
    {
      std::cerr << "Specified a non-known option: " << str.c_str() << " ...Exiting..." << std::endl;
      exit(1);
    }
  }
 //std::cout << "hasMultiKURecHit = " << hasMultiKURecHit << std::endl;
  // reduce output of DiXtal
  fNOutPhos = (fSkim == SkimType::DiXtal ? 6 : Common::nPhotons);
}

void Skimmer::SetupSkimType(const TString & skim_type)
{
  if      (skim_type.EqualTo("Standard"   ,TString::kExact)) fSkim = SkimType::Standard;
  else if (skim_type.EqualTo("Zee"        ,TString::kExact)) fSkim = SkimType::Zee;
  else if (skim_type.EqualTo("DiXtal"     ,TString::kExact)) fSkim = SkimType::DiXtal;
 // else if (skim_type.EqualTo("DiXtal"     ,TString::kExact)) fSkim = SkimType::DiXtal;
  else if (skim_type.EqualTo("AlwaysTrue" ,TString::kExact)) fSkim = SkimType::AlwaysTrue;
  else if (skim_type.EqualTo("AlwaysFalse",TString::kExact)) fSkim = SkimType::AlwaysFalse;
  else
  {
    std::cerr << skim_type.Data() << " is not a valid skim selection! Exiting..." << std::endl;
    exit(1);
  }
}

void Skimmer::SetupEnergyCorrection(const TString & str, ECorr & ecorr, const TString & text)
{
  if      (str.EqualTo("Nominal",TString::kExact)) ecorr = ECorr::Nominal;
  else if (str.EqualTo("Down"   ,TString::kExact)) ecorr = ECorr::Down;
  else if (str.EqualTo("Up"     ,TString::kExact)) ecorr = ECorr::Up;
  else
  {
    std::cerr << str.Data() << " is not a valid " << text.Data() << " selection! Exiting..." << std::endl;
    exit(1);
  }
}
