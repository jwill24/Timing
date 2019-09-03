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

  TH1F  * fOutAveXtalRecTimeHist;
  TH1F  * fOutAveXtalPhoRecTimeHist;
  TH1F  * fOutAveXtalOccHist;
  TH1F  * fOutAveXtalPhoOccHist;

  TH1F  * fOutAveXtalRecTimeHistEB;
  TH1F  * fOutAveXtalRecTimeHistEP;
  TH1F  * fOutAveXtalRecTimeHistEM;
  TH1F  * fOutAveXtalOccHistEB;
  TH1F  * fOutAveXtalOccHistEP;
  TH1F  * fOutAveXtalOccHistEM;

  TH1F  * fOutAveXtalPhoRecTimeHistEB;
  TH1F  * fOutAveXtalPhoRecTimeHistEP;
  TH1F  * fOutAveXtalPhoRecTimeHistEM;
  TH1F  * fOutAveXtalPhoOccHistEB;
  TH1F  * fOutAveXtalPhoOccHistEP;
  TH1F  * fOutAveXtalPhoOccHistEM;

  TH2F  * fOutAveXtalRecTimeMapEB;
  TH2F  * fOutAveXtalRecTimeMapEP;
  TH2F  * fOutAveXtalRecTimeMapEM;
  TH2F  * fOutAveXtalOccMapEB;
  TH2F  * fOutAveXtalOccMapEP;
  TH2F  * fOutAveXtalOccMapEM;
 
  TH2F  * fOutAveXtalPhoRecTimeMapEB;
  TH2F  * fOutAveXtalPhoRecTimeMapEP;
  TH2F  * fOutAveXtalPhoRecTimeMapEM;
  TH2F  * fOutAveXtalPhoOccMapEB;
  TH2F  * fOutAveXtalPhoOccMapEP;
  TH2F  * fOutAveXtalPhoOccMapEM;

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
   std::map<UInt_t,UInt_t> numXtalRecTime;

   std::map<UInt_t,Float_t> sumXtalRecTimeEB;
   std::map<UInt_t,UInt_t> numXtalRecTimeEB;
   std::map<UInt_t,Float_t> sumXtalRecTimeEP;
   std::map<UInt_t,UInt_t> numXtalRecTimeEP;
   std::map<UInt_t,Float_t> sumXtalRecTimeEM;
   std::map<UInt_t,UInt_t> numXtalRecTimeEM;

   std::map<UInt_t,Float_t> sumXtalPhoRecTime;
   std::map<UInt_t,UInt_t> numXtalPhoRecTime;

   std::map<UInt_t,Float_t> sumXtalPhoRecTimeEB;
   std::map<UInt_t,UInt_t> numXtalPhoRecTimeEB;
   std::map<UInt_t,Float_t> sumXtalPhoRecTimeEP;
   std::map<UInt_t,UInt_t> numXtalPhoRecTimeEP;
   std::map<UInt_t,Float_t> sumXtalPhoRecTimeEM;
   std::map<UInt_t,UInt_t> numXtalPhoRecTimeEM;


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

   TBranch        *b_nurechits;
   TBranch        *b_nkurechits;
   TBranch        *b_nkuStcrechits;
   TBranch        *b_nkuNotrechits;
   TBranch        *b_nkuNotStcrechits;
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

};

#endif
