#ifndef _skimmer_
#define _skimmer_ 

#include "SkimmerTypes.hh"
#include "Common.hh"

#include "TTree.h"
#include "TFile.h"
#include "TLorentzVector.h"

#include <vector>
#include <map>
#include <cmath>
#include <numeric>

class Skimmer 
{
public:
  // functions
  Skimmer(const TString & indir, const TString & outdir, const TString & filename, const TString & skimconfig);
  ~Skimmer();

  // skim config
  void SetupDefaults();
  void SetupSkimConfig();
  void SetupSkimType(const TString & skim_type);
  void SetupEnergyCorrection(const TString & str, ECorr & ecorr, const TString & text);

  // setup config inputs
  void GetInConfig();
  void InitInConfigStrings();
  void InitInConfigBranches();

  // setup tree inputs
  void InitInTree();
  void InitInStructs();
  void InitInBranchVecs();
  void InitInBranches();

  // setup gen inputs
  void GetSampleWeight();
  void GetPUWeights();

  // setup outputs
  void InitAndSetOutConfig();
  void InitOutTree();
  void InitOutStructs();
  void InitOutBranches();
  void InitOutCutFlowHists();
  void InitOutCutFlowHist(const TH1F * inh_cutflow, TH1F *& outh_cutflow, const TString & name);

  // skim and fill outputs
  void EventLoop();
  void FillOutGMSBs(const UInt_t entry);
  void FillOutHVDSs(const UInt_t entry);
  void FillOutToys(const UInt_t entry);
  void FillOutEvent(const UInt_t entry, const Float_t evtwgt);
  void FillOutJets(const UInt_t entry);
  void FillOutPhos(const UInt_t entry);

  // Correct MET
  void CorrectMET();

  // helper functions
  void FillPhoListStandard();

private:
  // I/O
  const TString fInDir;
  const TString fOutDir;
  const TString fFileName;
  const TString fSkimConfig;

  // Config
  SkimType fSkim;
  Float_t fSumWgts;
  TString fPUWgtFileName;
  ECorr fJEC;
  ECorr fJER;
  ECorr fPhoSc;
  ECorr fPhoSm;

  std::map<std::string,int> cutLabels;
  Bool_t fIsMC;
  Float_t fNOutPhos;

  // Input
  TFile * fInFile;
  TTree * fInTree; 
  TTree * fInConfigTree;
  TH1F  * fInCutFlow;
  TH1F  * fInCutFlowWgt;
  TFile * fInPUWgtFile;
  TH1F  * fInPUWgtHist;
  Float_t fSampleWeight;
  std::vector<Float_t> fPUWeights;
  
  GmsbVec fInGMSBs;
  HvdsVec fInHVDSs;
  ToyVec  fInToys;
  Event   fInEvent;
  RecHits fInRecHits;
  Jet     fInJets;
  PhoVec  fInPhos;

  Configuration fInConfig;

  // list of photon indices
  std::vector<Int_t> fPhoList;
  
  // Output
  TFile * fOutFile;
  TTree * fOutTree; 
  TTree * fOutConfigTree;
  TH1F  * fOutCutFlow;
  TH1F  * fOutCutFlowWgt;
  TH1F  * fOutCutFlowScl;
  TH1F  * tofHist;   

//  ave and diff hists
  TH1F  * fOutAveXtalRecTimeHist;
  TH1F  * fOutAveXtalPhoRecTimeHist;
  TH1F  * fOutDifXtalPhoRecTimeHist;

  TH1F  * fOutAveXtalRtRecTimeHist;
  TH1F  * fOutAveXtalRtPhoRecTimeHist;
  TH1F  * fOutDifXtalRtPhoRecTimeHist;

  TH1F  * fOutAveXtalRtStcRecTimeHist;
  TH1F  * fOutAveXtalRtStcPhoRecTimeHist;
  TH1F  * fOutDifXtalRtStcPhoRecTimeHist;

  TH1F  * fOutAveXtalRtOOTRecTimeHist;
  TH1F  * fOutAveXtalRtOOTPhoRecTimeHist;
  TH1F  * fOutDifXtalRtOOTPhoRecTimeHist;

  TH1F  * fOutAveXtalRtOOTStcRecTimeHist;
  TH1F  * fOutAveXtalRtOOTStcPhoRecTimeHist;
  TH1F  * fOutDifXtalRtOOTStcPhoRecTimeHist;

  TH1F  * fOutAveXtalOccHist;
  TH1F  * fOutAveXtalPhoOccHist;

//  ave hists
  TH1F  * fOutAveXtalRecTimeHistEB;
  TH1F  * fOutAveXtalRecTimeHistEP;
  TH1F  * fOutAveXtalRecTimeHistEM;

  TH1F  * fOutAveXtalRtRecTimeHistEB;
  TH1F  * fOutAveXtalRtRecTimeHistEP;
  TH1F  * fOutAveXtalRtRecTimeHistEM;

  TH1F  * fOutAveXtalRtStcRecTimeHistEB;
  TH1F  * fOutAveXtalRtStcRecTimeHistEP;
  TH1F  * fOutAveXtalRtStcRecTimeHistEM;

  TH1F  * fOutAveXtalRtOOTRecTimeHistEB;
  TH1F  * fOutAveXtalRtOOTRecTimeHistEP;
  TH1F  * fOutAveXtalRtOOTRecTimeHistEM;

  TH1F  * fOutAveXtalRtOOTStcRecTimeHistEB;
  TH1F  * fOutAveXtalRtOOTStcRecTimeHistEP;
  TH1F  * fOutAveXtalRtOOTStcRecTimeHistEM;

/// energy threshold cali hists
  TH1F  * fOutAveXtalRtOOTStcRecTimeE0HistEB;
  TH1F  * fOutAveXtalRtOOTStcRecTimeE0HistEP;
  TH1F  * fOutAveXtalRtOOTStcRecTimeE0HistEM;

  TH1F  * fOutAveXtalRtOOTStcRecTimeE1HistEB;
  TH1F  * fOutAveXtalRtOOTStcRecTimeE1HistEP;
  TH1F  * fOutAveXtalRtOOTStcRecTimeE1HistEM;

  TH1F  * fOutAveXtalRtOOTStcRecTime2E1HistEB;
  TH1F  * fOutAveXtalRtOOTStcRecTime2E1HistEP;
  TH1F  * fOutAveXtalRtOOTStcRecTime2E1HistEM;

  TH1F  * fOutAveXtalRtOOTStcRecTime4E1HistEB;
  TH1F  * fOutAveXtalRtOOTStcRecTime4E1HistEP;
  TH1F  * fOutAveXtalRtOOTStcRecTime4E1HistEM;

  TH1F  * fOutAveXtalRtOOTStcRecTimeE2HistEB;
  TH1F  * fOutAveXtalRtOOTStcRecTimeE2HistEP;
  TH1F  * fOutAveXtalRtOOTStcRecTimeE2HistEM;

  TH1F  * fOutAveXtalRtOOTStcRecTimeE5HistEB;
  TH1F  * fOutAveXtalRtOOTStcRecTimeE5HistEP;
  TH1F  * fOutAveXtalRtOOTStcRecTimeE5HistEM;

  TH1F  * fOutAveXtalRtOOTStcRecTime2E5HistEB;
  TH1F  * fOutAveXtalRtOOTStcRecTime2E5HistEP;
  TH1F  * fOutAveXtalRtOOTStcRecTime2E5HistEM;

  TH1F  * fOutAveXtalRtOOTStcRecTime4E5HistEB;
  TH1F  * fOutAveXtalRtOOTStcRecTime4E5HistEP;
  TH1F  * fOutAveXtalRtOOTStcRecTime4E5HistEM;

  TH1F  * fOutAveXtalRtOOTStcRecTimeE10HistEB;
  TH1F  * fOutAveXtalRtOOTStcRecTimeE10HistEP;
  TH1F  * fOutAveXtalRtOOTStcRecTimeE10HistEM;

/// ave and diff hists
  TH1F  * fOutAveXtalOccHistEB;
  TH1F  * fOutAveXtalOccHistEP;
  TH1F  * fOutAveXtalOccHistEM;

  TH1F  * fOutAveXtalPhoRecTimeHistEB;
  TH1F  * fOutAveXtalPhoRecTimeHistEP;
  TH1F  * fOutAveXtalPhoRecTimeHistEM;

  TH1F  * fOutAveXtalRtPhoRecTimeHistEB;
  TH1F  * fOutAveXtalRtPhoRecTimeHistEP;
  TH1F  * fOutAveXtalRtPhoRecTimeHistEM;

  TH1F  * fOutAveXtalRtStcPhoRecTimeHistEB;
  TH1F  * fOutAveXtalRtStcPhoRecTimeHistEP;
  TH1F  * fOutAveXtalRtStcPhoRecTimeHistEM;

  TH1F  * fOutAveXtalRtOOTPhoRecTimeHistEB;
  TH1F  * fOutAveXtalRtOOTPhoRecTimeHistEP;
  TH1F  * fOutAveXtalRtOOTPhoRecTimeHistEM;

  TH1F  * fOutAveXtalRtOOTStcPhoRecTimeHistEB;
  TH1F  * fOutAveXtalRtOOTStcPhoRecTimeHistEP;
  TH1F  * fOutAveXtalRtOOTStcPhoRecTimeHistEM;

  TH1F  * fOutAveXtalPhoOccHistEB;
  TH1F  * fOutAveXtalPhoOccHistEP;
  TH1F  * fOutAveXtalPhoOccHistEM;

  TH1F  * fOutDifXtalPhoRecTimeHistEB;
  TH1F  * fOutDifXtalPhoRecTimeHistEP;
  TH1F  * fOutDifXtalPhoRecTimeHistEM;

  TH1F  * fOutDifXtalRtPhoRecTimeHistEB;
  TH1F  * fOutDifXtalRtPhoRecTimeHistEP;
  TH1F  * fOutDifXtalRtPhoRecTimeHistEM;

  TH1F  * fOutDifXtalRtStcPhoRecTimeHistEB;
  TH1F  * fOutDifXtalRtStcPhoRecTimeHistEP;
  TH1F  * fOutDifXtalRtStcPhoRecTimeHistEM;

  TH1F  * fOutDifXtalRtOOTPhoRecTimeHistEB;
  TH1F  * fOutDifXtalRtOOTPhoRecTimeHistEP;
  TH1F  * fOutDifXtalRtOOTPhoRecTimeHistEM;

  TH1F  * fOutDifXtalRtOOTStcPhoRecTimeHistEB;
  TH1F  * fOutDifXtalRtOOTStcPhoRecTimeHistEP;
  TH1F  * fOutDifXtalRtOOTStcPhoRecTimeHistEM;

// maps   ave and diff
  TH2F  * fOutAveXtalRecTimeMapEB;
  TH2F  * fOutAveXtalRecTimeMapEP;
  TH2F  * fOutAveXtalRecTimeMapEM;

  TH2F  * fOutAveXtalRtRecTimeMapEB;
  TH2F  * fOutAveXtalRtRecTimeMapEP;
  TH2F  * fOutAveXtalRtRecTimeMapEM;

  TH2F  * fOutAveXtalRtStcRecTimeMapEB;
  TH2F  * fOutAveXtalRtStcRecTimeMapEP;
  TH2F  * fOutAveXtalRtStcRecTimeMapEM;

  TH2F  * fOutAveXtalRtDifStcPhoRecTimeMapEB;
  TH2F  * fOutAveXtalRtDifStcPhoRecTimeMapEP;
  TH2F  * fOutAveXtalRtDifStcPhoRecTimeMapEM;

  TH2F  * fOutAveXtalRtOOTRecTimeMapEB;
  TH2F  * fOutAveXtalRtOOTRecTimeMapEP;
  TH2F  * fOutAveXtalRtOOTRecTimeMapEM;

  TH2F  * fOutAveXtalRtOOTStcRecTimeMapEB;
  TH2F  * fOutAveXtalRtOOTStcRecTimeMapEP;
  TH2F  * fOutAveXtalRtOOTStcRecTimeMapEM;

  TH2F  * fOutAveXtalRtDifOOTPhoRecTimeMapEB;
  TH2F  * fOutAveXtalRtDifOOTPhoRecTimeMapEP;
  TH2F  * fOutAveXtalRtDifOOTPhoRecTimeMapEM;

// energy thresholds cali
  TH2F  * fOutAveXtalRtOOTStcRecTimeE0MapEB;
  TH2F  * fOutAveXtalRtOOTStcRecTimeE0MapEP;
  TH2F  * fOutAveXtalRtOOTStcRecTimeE0MapEM;

  TH2F  * fOutAveXtalRtOOTStcRecTimeE1MapEB;
  TH2F  * fOutAveXtalRtOOTStcRecTimeE1MapEP;
  TH2F  * fOutAveXtalRtOOTStcRecTimeE1MapEM;
  TH2F  * fOutAveXtalRtOOTStcRecTime2E1MapEB;
  TH2F  * fOutAveXtalRtOOTStcRecTime2E1MapEP;
  TH2F  * fOutAveXtalRtOOTStcRecTime2E1MapEM;
  TH2F  * fOutAveXtalRtOOTStcRecTime4E1MapEB;
  TH2F  * fOutAveXtalRtOOTStcRecTime4E1MapEP;
  TH2F  * fOutAveXtalRtOOTStcRecTime4E1MapEM;

  TH2F  * fOutAveXtalRtOOTStcRecTimeE2MapEB;
  TH2F  * fOutAveXtalRtOOTStcRecTimeE2MapEP;
  TH2F  * fOutAveXtalRtOOTStcRecTimeE2MapEM;

  TH2F  * fOutAveXtalRtOOTStcRecTimeE5MapEB;
  TH2F  * fOutAveXtalRtOOTStcRecTimeE5MapEP;
  TH2F  * fOutAveXtalRtOOTStcRecTimeE5MapEM;
  TH2F  * fOutAveXtalRtOOTStcRecTime2E5MapEB;
  TH2F  * fOutAveXtalRtOOTStcRecTime2E5MapEP;
  TH2F  * fOutAveXtalRtOOTStcRecTime2E5MapEM;
  TH2F  * fOutAveXtalRtOOTStcRecTime4E5MapEB;
  TH2F  * fOutAveXtalRtOOTStcRecTime4E5MapEP;
  TH2F  * fOutAveXtalRtOOTStcRecTime4E5MapEM;

  TH2F  * fOutAveXtalRtStcRecTimeE5MapEB;
  TH2F  * fOutAveXtalRtStcRecTimeE5MapEP;
  TH2F  * fOutAveXtalRtStcRecTimeE5MapEM;

  TH2F  * fOutAveXtalWtOOTStcRecTimeE5MapEB;
  TH2F  * fOutAveXtalWtOOTStcRecTimeE5MapEP;
  TH2F  * fOutAveXtalWtOOTStcRecTimeE5MapEM;

  TH2F  * fOutAveXtalRtOOTStcRecTimeE10MapEB;
  TH2F  * fOutAveXtalRtOOTStcRecTimeE10MapEP;
  TH2F  * fOutAveXtalRtOOTStcRecTimeE10MapEM;

/// ave diff maps
  TH2F  * fOutAveXtalOccMapEB;
  TH2F  * fOutAveXtalOccMapEP;
  TH2F  * fOutAveXtalOccMapEM;
 
  TH2F  * fOutAveXtalPhoRecTimeMapEB;
  TH2F  * fOutAveXtalPhoRecTimeMapEP;
  TH2F  * fOutAveXtalPhoRecTimeMapEM;

  TH2F  * fOutAveXtalRtPhoRecTimeMapEB;
  TH2F  * fOutAveXtalRtPhoRecTimeMapEP;
  TH2F  * fOutAveXtalRtPhoRecTimeMapEM;

  TH2F  * fOutAveXtalRtStcPhoRecTimeMapEB;
  TH2F  * fOutAveXtalRtStcPhoRecTimeMapEP;
  TH2F  * fOutAveXtalRtStcPhoRecTimeMapEM;

  TH2F  * fOutAveXtalRtOOTPhoRecTimeMapEB;
  TH2F  * fOutAveXtalRtOOTPhoRecTimeMapEP;
  TH2F  * fOutAveXtalRtOOTPhoRecTimeMapEM;

  TH2F  * fOutAveXtalRtOOTStcPhoRecTimeMapEB;
  TH2F  * fOutAveXtalRtOOTStcPhoRecTimeMapEP;
  TH2F  * fOutAveXtalRtOOTStcPhoRecTimeMapEM;

  TH2F  * fOutAveXtalPhoOccMapEB;
  TH2F  * fOutAveXtalPhoOccMapEP;
  TH2F  * fOutAveXtalPhoOccMapEM;

  TH2F  * fOutDifXtalPhoRecTimeMapEB;
  TH2F  * fOutDifXtalPhoRecTimeMapEP;
  TH2F  * fOutDifXtalPhoRecTimeMapEM;

  TH2F  * fOutDifXtalRtPhoRecTimeMapEB;
  TH2F  * fOutDifXtalRtPhoRecTimeMapEP;
  TH2F  * fOutDifXtalRtPhoRecTimeMapEM;

  TH2F  * fOutDifXtalRtStcPhoRecTimeMapEB;
  TH2F  * fOutDifXtalRtStcPhoRecTimeMapEP;
  TH2F  * fOutDifXtalRtStcPhoRecTimeMapEM;

  TH2F  * fOutDifXtalRtOOTPhoRecTimeMapEB;
  TH2F  * fOutDifXtalRtOOTPhoRecTimeMapEP;
  TH2F  * fOutDifXtalRtOOTPhoRecTimeMapEM;

  TH2F  * fOutDifXtalRtOOTStcPhoRecTimeMapEB;
  TH2F  * fOutDifXtalRtOOTStcPhoRecTimeMapEP;
  TH2F  * fOutDifXtalRtOOTStcPhoRecTimeMapEM;

/// hists for cl and ic cali
  TH1F  * fOutAveXtalRtOOTStcPhoClRecTimeHistEB;
  TH1F  * fOutAveXtalRtOOTStcPhoClRecTimeHistEP;
  TH1F  * fOutAveXtalRtOOTStcPhoClRecTimeHistEM;

  TH1F  * fOutAveXtalRtOOTStcPhoIcRecTimeHistEB;
  TH1F  * fOutAveXtalRtOOTStcPhoIcRecTimeHistEP;
  TH1F  * fOutAveXtalRtOOTStcPhoIcRecTimeHistEM;

///   maps for cl and ic cali
  TH2F  * fOutAveXtalRtStcPhoClRecTimeMapEB;
  TH2F  * fOutAveXtalRtStcPhoClRecTimeMapEP;
  TH2F  * fOutAveXtalRtStcPhoClRecTimeMapEM;

  TH2F  * fOutAveXtalRtStcPhoIcRecTimeMapEB;
  TH2F  * fOutAveXtalRtStcPhoIcRecTimeMapEP;
  TH2F  * fOutAveXtalRtStcPhoIcRecTimeMapEM;

  TH2F  * fOutAveXtalRtOOTStcPhoClRecTimeMapEB;
  TH2F  * fOutAveXtalRtOOTStcPhoClRecTimeMapEP;
  TH2F  * fOutAveXtalRtOOTStcPhoClRecTimeMapEM;

  TH2F  * fOutAveXtalRtOOTStcPhoIcRecTimeMapEB;
  TH2F  * fOutAveXtalRtOOTStcPhoIcRecTimeMapEP;
  TH2F  * fOutAveXtalRtOOTStcPhoIcRecTimeMapEM;

  TH2F  * fOutAveXtalWtOOTStcPhoClRecTimeMapEB;
  TH2F  * fOutAveXtalWtOOTStcPhoClRecTimeMapEP;
  TH2F  * fOutAveXtalWtOOTStcPhoClRecTimeMapEM;

  TH2F  * fOutAveXtalWtOOTStcPhoIcRecTimeMapEB;
  TH2F  * fOutAveXtalWtOOTStcPhoIcRecTimeMapEP;
  TH2F  * fOutAveXtalWtOOTStcPhoIcRecTimeMapEM;

//////////////////////////////////////////////////////

  GmsbVec fOutGMSBs;
  HvdsVec fOutHVDSs;
  ToyVec  fOutToys;
  Event   fOutEvent;
  Jet     fOutJets;
  PhoVec  fOutPhos;

  Configuration fOutConfig;

// LHCInfo

   bool		isLHCInfo;
   bool		hasUncalDigi;
   bool         hasKURecHit;
   bool         hasMultiKURecHit;
   bool		hasUrecDigi;


   //typedef std::map<UInt_t,Float_t> sumXtalRecTime_t;
   std::map<UInt_t,Float_t> sumXtalRecTime;
   //std::map<UInt_t,Float_t> sumXtalRtRecTime;
   std::map<UInt_t,Float_t> sumXtalRtStcRecTime;
   std::map<UInt_t,Float_t> sumXtalWtOOTStcRecTime;
   std::map<UInt_t,Float_t> sumXtalRtOOTStcRecTime;

   std::map<UInt_t,UInt_t> numXtalRecTime;
   std::map<UInt_t,UInt_t> numXtalRtOOTStcRecTime;

//   std::map<UInt_t,Float_t> sumXtalRecTimeEB;
//   std::map<UInt_t,Float_t> sumXtalRtRecTimeEB;
//   std::map<UInt_t,Float_t> sumXtalRtStcRecTimeEB;
//   std::map<UInt_t,Float_t> sumXtalRtOOTRecTimeEB;
//   std::map<UInt_t,Float_t> sumXtalRtOOTStcRecTimeEB;
//   std::map<UInt_t,UInt_t> numXtalRecTimeEB;
//   std::map<UInt_t,Float_t> sumXtalRecTimeEP;
//   std::map<UInt_t,Float_t> sumXtalRtRecTimeEP;
//   std::map<UInt_t,Float_t> sumXtalRtStcRecTimeEP;
//   std::map<UInt_t,Float_t> sumXtalRtOOTRecTimeEP;
//   std::map<UInt_t,Float_t> sumXtalRtOOTStcRecTimeEP;
//   std::map<UInt_t,UInt_t> numXtalRecTimeEP;
//   std::map<UInt_t,Float_t> sumXtalRecTimeEM;
//   std::map<UInt_t,Float_t> sumXtalRtRecTimeEM;
//   std::map<UInt_t,Float_t> sumXtalRtStcRecTimeEM;
//   std::map<UInt_t,Float_t> sumXtalRtOOTRecTimeEM;
//   std::map<UInt_t,Float_t> sumXtalRtOOTStcRecTimeEM;
//   std::map<UInt_t,UInt_t> numXtalRecTimeEM;

   std::map<UInt_t,Float_t> sumXtalPhoRecTime;
   std::map<UInt_t,Float_t> sumXtalRtPhoRecTime;
   std::map<UInt_t,Float_t> sumXtalRtStcPhoRecTime;
   std::map<UInt_t,Float_t> sumXtalRtOOTPhoRecTime;
   std::map<UInt_t,Float_t> sumXtalRtOOTStcPhoRecTime;
   std::map<UInt_t,Float_t> difXtalPhoRecTime;
   std::map<UInt_t,Float_t> difXtalRtPhoRecTime;
   std::map<UInt_t,Float_t> difXtalRtStcPhoRecTime;
   std::map<UInt_t,Float_t> difXtalRtOOTPhoRecTime;
   std::map<UInt_t,Float_t> difXtalRtOOTStcPhoRecTime;
   std::map<UInt_t,UInt_t> numXtalPhoRecTime;

//   std::map<UInt_t,Float_t> sumXtalPhoRecTimeEB;
//   std::map<UInt_t,Float_t> sumXtalRtPhoRecTimeEB;
//   std::map<UInt_t,Float_t> sumXtalRtStcPhoRecTimeEB;
//   std::map<UInt_t,Float_t> sumXtalRtOOTPhoRecTimeEB;
//   std::map<UInt_t,Float_t> sumXtalRtOOTStcPhoRecTimeEB;
//   std::map<UInt_t,Float_t> difXtalPhoRecTimeEB;
//   std::map<UInt_t,Float_t> difXtalRtPhoRecTimeEB;
//   std::map<UInt_t,Float_t> difXtalRtStcPhoRecTimeEB;
//   std::map<UInt_t,Float_t> difXtalRtOOTPhoRecTimeEB;
//   std::map<UInt_t,Float_t> difXtalRtOOTStcPhoRecTimeEB;
//   std::map<UInt_t,UInt_t> numXtalPhoRecTimeEB;
//   std::map<UInt_t,Float_t> sumXtalPhoRecTimeEP;
//   std::map<UInt_t,Float_t> sumXtalRtPhoRecTimeEP;
//   std::map<UInt_t,Float_t> sumXtalRtStcPhoRecTimeEP;
//   std::map<UInt_t,Float_t> sumXtalRtOOTPhoRecTimeEP;
//   std::map<UInt_t,Float_t> sumXtalRtOOTStcPhoRecTimeEP;
//   std::map<UInt_t,Float_t> difXtalPhoRecTimeEP;
//   std::map<UInt_t,Float_t> difXtalRtPhoRecTimeEP;
//   std::map<UInt_t,Float_t> difXtalRtStcPhoRecTimeEP;
//   std::map<UInt_t,Float_t> difXtalRtOOTPhoRecTimeEP;
//   std::map<UInt_t,Float_t> difXtalRtOOTStcPhoRecTimeEP;
//   std::map<UInt_t,UInt_t> numXtalPhoRecTimeEP;
//   std::map<UInt_t,Float_t> sumXtalPhoRecTimeEM;
//   std::map<UInt_t,Float_t> sumXtalRtPhoRecTimeEM;
//   std::map<UInt_t,Float_t> sumXtalRtStcPhoRecTimeEM;
//   std::map<UInt_t,Float_t> sumXtalRtOOTPhoRecTimeEM;
//   std::map<UInt_t,Float_t> sumXtalRtOOTStcPhoRecTimeEM;
//   std::map<UInt_t,Float_t> difXtalPhoRecTimeEM;
//   std::map<UInt_t,Float_t> difXtalRtPhoRecTimeEM;
//   std::map<UInt_t,Float_t> difXtalRtStcPhoRecTimeEM;
//   std::map<UInt_t,Float_t> difXtalRtOOTPhoRecTimeEM;
//   std::map<UInt_t,Float_t> difXtalRtOOTStcPhoRecTimeEM;
//   std::map<UInt_t,UInt_t> numXtalPhoRecTimeEM;

//   std::map<UInt_t,UInt_t> caliXtalPhoRecTimeEB;
//   std::map<UInt_t,UInt_t> caliXtalPhoRecTimeEP;
//   std::map<UInt_t,UInt_t> caliXtalPhoRecTimeEM;

   std::map<UInt_t,Float_t> sumXtalRtOOTStcRecTimeE0;
   std::map<UInt_t,UInt_t> numXtalRtOOTStcRecTimeE0;
   std::map<UInt_t,Float_t> sumXtalRtOOTStcRecTimeE1;
   std::map<UInt_t,UInt_t> numXtalRtOOTStcRecTimeE1;
   std::map<UInt_t,Float_t> sumXtalRtOOTStcRecTime2E1;
   std::map<UInt_t,UInt_t> numXtalRtOOTStcRecTime2E1;
   std::map<UInt_t,Float_t> sumXtalRtOOTStcRecTime4E1;
   std::map<UInt_t,UInt_t> numXtalRtOOTStcRecTime4E1;
   std::map<UInt_t,Float_t> sumXtalRtOOTStcRecTimeE2;
   std::map<UInt_t,UInt_t> numXtalRtOOTStcRecTimeE2;

   std::map<UInt_t,Float_t> sumXtalRtStcRecTimeE5;
   std::map<UInt_t,UInt_t> numXtalRtOOTStcRecTimeE5;
   std::map<UInt_t,Float_t> sumXtalRtOOTStcRecTimeE5;
   std::map<UInt_t,Float_t> sumXtalWtOOTStcRecTimeE5;

   std::map<UInt_t,Float_t> sumXtalRtOOTStcRecTime2E5;
   std::map<UInt_t,UInt_t> numXtalRtOOTStcRecTime2E5;
   std::map<UInt_t,Float_t> sumXtalRtOOTStcRecTime4E5;
   std::map<UInt_t,UInt_t> numXtalRtOOTStcRecTime4E5;
   std::map<UInt_t,Float_t> sumXtalRtOOTStcRecTimeE10;
   std::map<UInt_t,UInt_t> numXtalRtOOTStcRecTimeE10;

   std::map<UInt_t,Float_t> sumXtalRtOOTStcPhoClRecTime;
   std::map<UInt_t,UInt_t> numXtalRtOOTStcPhoClRecTime;
   std::map<UInt_t,Float_t> sumXtalRtStcPhoClRecTime;
   std::map<UInt_t,Float_t> sumXtalWtOOTStcPhoClRecTime;

   std::map<UInt_t,Float_t> sumXtalRtOOTStcPhoIcRecTime;
   std::map<UInt_t,UInt_t> numXtalRtOOTStcPhoIcRecTime;
   std::map<UInt_t,Float_t> sumXtalRtStcPhoIcRecTime;
   std::map<UInt_t,Float_t> sumXtalWtOOTStcPhoIcRecTime;

   //Float_t	   aveRecTime;
   //UInt_t	   numAveRecTime;

   UInt_t          bunch_crossing;
   UInt_t          num_bunch;
   UInt_t          subtrain_position;
   UInt_t          train_position;
   UInt_t          subtrain_number;
   UInt_t          train_number;
   Float_t         beam1_VC[3564];   //[num_bunch]
   Float_t         beam2_VC[3564];   //[num_bunch]
   Float_t         beam1_RF[3564];   //[num_bunch]
   Float_t         beam2_RF[3564];   //[num_bunch]
   Float_t         gZmass;
   Float_t         gdR;

   Int_t	  nxtal_sep;
   Int_t          nurechits;
   Int_t          nkurechits;
   Int_t          nkuStcrechits;
   Int_t          nkuNotrechits;
   Int_t          nkuNotStcrechits;
   Int_t          nkuWootStcrechits;
   Int_t          ndigis;

   std::vector<Float_t>  * ootA0;
   std::vector<Float_t>  * ootA1;
   std::vector<Float_t>  * ootA2;
   std::vector<Float_t>  * ootA3;
   std::vector<Float_t>  * ootA4;
   std::vector<Float_t>  * ootA5;
   std::vector<Float_t>  * ootA6;
   std::vector<Float_t>  * ootA7;
   std::vector<Float_t>  * ootA8;
   std::vector<Float_t>  * ootA9;
   std::vector<Float_t>  * ootMax;
   std::vector<Float_t>  * ootVsum;
   std::vector<Float_t>  * uRhId;

   std::vector<Float_t> * kurhE;
   std::vector<Float_t> * kurhtime;
   std::vector<Float_t> * kurhtimeErr;
   std::vector<Float_t> * kurhTOF;
   std::vector<UInt_t>  * kurhID;

   std::vector<Float_t> * kuStcrhE;
   std::vector<Float_t> * kuStcrhtime;
   std::vector<Float_t> * kuStcrhtimeErr;
   std::vector<Float_t> * kuStcrhTOF;
   std::vector<UInt_t>  * kuStcrhID;

   std::vector<Float_t> * kuNotrhE;
   std::vector<Float_t> * kuNotrhtime;
   std::vector<Float_t> * kuNotrhtimeErr;
   std::vector<Float_t> * kuNotrhTOF;
   std::vector<UInt_t>  * kuNotrhID;

   std::vector<Float_t> * kuNotStcrhE;
   std::vector<Float_t> * kuNotStcrhtime;
   std::vector<Float_t> * kuNotStcrhtimeErr;
   std::vector<Float_t> * kuNotStcrhTOF;
   std::vector<UInt_t>  * kuNotStcrhID;

   std::vector<Float_t> * kuWootStcrhE;
   std::vector<Float_t> * kuWootStcrhtime;
   std::vector<Float_t> * kuWootStcrhtimeErr;
   std::vector<Float_t> * kuWootStcrhTOF;
   std::vector<UInt_t>  * kuWootStcrhID;

   std::vector<Int_t> * out_npho_recHits_0;
   std::vector<Int_t> * out_npho_recHits_1;
   std::vector<Int_t> * out_npho_recHits_2;
   std::vector<Int_t> * out_npho_recHits_3;
   std::vector<Float_t> *   out_fInRecHits_E;
   std::vector<UInt_t> *   out_fInRecHits_ID;
   std::vector<Float_t> *   out_fInRecHits_time;
   std::vector<Float_t> *   out_fInRecHits_TOF;
   std::vector<Float_t> *   out_kurhtime;
   std::vector<UInt_t> *   out_kurhID;
   std::vector<Float_t> *   out_kuStcrhtime;
   std::vector<Float_t> *   out_kuNotrhtime;
   std::vector<Float_t> *   out_kuNotStcrhtime;
   std::vector<Float_t> *   out_kuWootStcrhtime;

   TBranch        *b_nurechits;
   TBranch        *b_nkurechits;
   TBranch        *b_nkuStcrechits;
   TBranch        *b_nkuNotrechits;
   TBranch        *b_nkuNotStcrechits;
   TBranch        *b_nkuWootStcrechits;
   TBranch        *b_ndigis;
   TBranch        *b_uRhId;

   TBranch        *b_ootA0;
   TBranch        *b_ootA1;
   TBranch        *b_ootA2;
   TBranch        *b_ootA3;
   TBranch        *b_ootA4;
   TBranch        *b_ootA5;
   TBranch        *b_ootA6;
   TBranch        *b_ootA7;
   TBranch        *b_ootA8;
   TBranch        *b_ootA9;
   TBranch        *b_ootMax;
   TBranch        *b_ootVsum;

   TBranch        *b_bunch_crossing;   //!
   TBranch        *b_num_bunch;   //!
   TBranch        *b_subtrain_position;   //!
   TBranch        *b_train_position;   //!
   TBranch        *b_subtrain_number;   //!
   TBranch        *b_train_number;   //! 
   TBranch        *b_beam1_VC;   //!
   TBranch        *b_beam2_VC;   //!
   TBranch        *b_beam1_RF;   //!
   TBranch        *b_beam2_RF;   //!
   TBranch        *b_nxtal_sep;   //!

   TBranch 	  *b_kurhE;
   TBranch 	  *b_kurhtime;
   TBranch 	  *b_kurhtimeErr;
   TBranch 	  *b_kurhTOF;
   TBranch 	  *b_kurhID;

   TBranch        *b_kuStcrhE;
   TBranch        *b_kuStcrhtime;
   TBranch        *b_kuStcrhtimeErr;
   TBranch        *b_kuStcrhTOF;
   TBranch        *b_kuStcrhID;

   TBranch        *b_kuNotrhE;
   TBranch        *b_kuNotrhtime;
   TBranch        *b_kuNotrhtimeErr;
   TBranch        *b_kuNotrhTOF;
   TBranch        *b_kuNotrhID;

   TBranch        *b_kuNotStcrhE;
   TBranch        *b_kuNotStcrhtime;
   TBranch        *b_kuNotStcrhtimeErr;
   TBranch        *b_kuNotStcrhTOF;
   TBranch        *b_kuNotStcrhID;

   TBranch        *b_kuWootStcrhE;
   TBranch        *b_kuWootStcrhtime;
   TBranch        *b_kuWootStcrhtimeErr;
   TBranch        *b_kuWootStcrhTOF;
   TBranch        *b_kuWootStcrhID;

};

#endif
