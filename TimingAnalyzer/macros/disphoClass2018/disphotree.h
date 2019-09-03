//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Feb 11 13:58:11 2019 by ROOT version 6.10/09
// from TTree disphotree/disphotree
// found on file: /home/t3-ku/jaking/datasets/ecalTiming/EGamma_ntuple/190209_143105/0000/Outputfile_1.root
//////////////////////////////////////////////////////////

#ifndef disphotree_h
#define disphotree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"
#include "vector"

class disphotree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         rho;
   UInt_t          run;
   UInt_t          lumi;
   ULong64_t       event;
   UInt_t          bunch_crossing;
   UInt_t          num_bunch;
   Float_t         beam1_VC[3564];   //[num_bunch]
   Float_t         beam2_VC[3564];   //[num_bunch]
   Float_t         beam1_RF[3564];   //[num_bunch]
   Float_t         beam2_RF[3564];   //[num_bunch]
   UInt_t          subtrain_position;
   UInt_t          train_position;
   UInt_t          subtrain_number;
   UInt_t          train_number;
   Bool_t          hltSignal;
   Bool_t          hltRefPhoID;
   Bool_t          hltRefDispID;
   Bool_t          hltRefHT;
   Bool_t          hltPho50;
   Bool_t          hltPho200;
   Bool_t          hltDiPho70;
   Bool_t          hltDiPho3022M90;
   Bool_t          hltDiPho30PV18PV;
   Bool_t          hltEle32WPT;
   Bool_t          hltDiEle33MW;
   Bool_t          hltJet500;
   Bool_t          metPV;
   Bool_t          metBeamHalo;
   Bool_t          metHBHENoise;
   Bool_t          metHBHEisoNoise;
   Bool_t          metECALTP;
   Bool_t          metPFMuon;
   Bool_t          metPFChgHad;
   Bool_t          metEESC;
   Bool_t          metECALCalib;
   Bool_t          metECALBadCalib;
   Int_t           nvtx;
   Float_t         vtxX;
   Float_t         vtxY;
   Float_t         vtxZ;
   Float_t         t1pfMETpt;
   Float_t         t1pfMETphi;
   Float_t         t1pfMETsumEt;
   Int_t           njets;
   vector<float>   *jetE;
   vector<float>   *jetpt;
   vector<float>   *jeteta;
   vector<float>   *jetphi;
   vector<int>     *jetID;
   vector<float>   *jetNHF;
   vector<float>   *jetNEMF;
   vector<float>   *jetCHF;
   vector<float>   *jetCEMF;
   vector<float>   *jetMUF;
   vector<float>   *jetNHM;
   vector<float>   *jetCHM;
   Int_t           nelLowL;
   Int_t           nelLowM;
   Int_t           nelLowT;
   Int_t           nelHighL;
   Int_t           nelHighM;
   Int_t           nelHighT;
   Int_t           nmuLowL;
   Int_t           nmuLowM;
   Int_t           nmuLowT;
   Int_t           nmuHighL;
   Int_t           nmuHighM;
   Int_t           nmuHighT;
   Int_t           nrechits;
   vector<float>   *rhX;
   vector<float>   *rhY;
   vector<float>   *rhZ;
   vector<float>   *rhE;
   vector<float>   *rhtime;
   vector<float>   *rhtimeErr;
   vector<float>   *rhTOF;
   vector<unsigned int> *rhID;
   vector<bool>    *rhisOOT;
   vector<bool>    *rhisGS6;
   vector<bool>    *rhisGS1;
   vector<float>   *rhadcToGeV;
   vector<float>   *rhped12;
   vector<float>   *rhped6;
   vector<float>   *rhped1;
   vector<float>   *rhpedrms12;
   vector<float>   *rhpedrms6;
   vector<float>   *rhpedrms1;
   Int_t           nphotons;
   Float_t         phoE_0;
   Float_t         phopt_0;
   Float_t         phoeta_0;
   Float_t         phophi_0;
   Float_t         phoscE_0;
   Float_t         phosceta_0;
   Float_t         phoscphi_0;
   Float_t         phoHoE_0;
   Float_t         phor9_0;
   Float_t         phoChgHadIso_0;
   Float_t         phoNeuHadIso_0;
   Float_t         phoPhoIso_0;
   Float_t         phoEcalPFClIso_0;
   Float_t         phoHcalPFClIso_0;
   Float_t         phoTrkIso_0;
   Float_t         phoChgHadIsoC_0;
   Float_t         phoNeuHadIsoC_0;
   Float_t         phoPhoIsoC_0;
   Float_t         phoEcalPFClIsoC_0;
   Float_t         phoHcalPFClIsoC_0;
   Float_t         phoTrkIsoC_0;
   Float_t         phosieie_0;
   Float_t         phosipip_0;
   Float_t         phosieip_0;
   Float_t         phoe2x2_0;
   Float_t         phoe3x3_0;
   Float_t         phoe5x5_0;
   Float_t         phosmaj_0;
   Float_t         phosmin_0;
   Float_t         phoalpha_0;
   Int_t           phoseed_0;
   vector<int>     *phorecHits_0;
   Float_t         phosuisseX_0;
   Bool_t          phoisOOT_0;
   Bool_t          phoisEB_0;
   Bool_t          phoisHLT_0;
   Bool_t          phoisTrk_0;
   Bool_t          phopassEleVeto_0;
   Bool_t          phohasPixSeed_0;
   Int_t           phogedID_0;
   Int_t           phoootID_0;
   Float_t         phoE_1;
   Float_t         phopt_1;
   Float_t         phoeta_1;
   Float_t         phophi_1;
   Float_t         phoscE_1;
   Float_t         phosceta_1;
   Float_t         phoscphi_1;
   Float_t         phoHoE_1;
   Float_t         phor9_1;
   Float_t         phoChgHadIso_1;
   Float_t         phoNeuHadIso_1;
   Float_t         phoPhoIso_1;
   Float_t         phoEcalPFClIso_1;
   Float_t         phoHcalPFClIso_1;
   Float_t         phoTrkIso_1;
   Float_t         phoChgHadIsoC_1;
   Float_t         phoNeuHadIsoC_1;
   Float_t         phoPhoIsoC_1;
   Float_t         phoEcalPFClIsoC_1;
   Float_t         phoHcalPFClIsoC_1;
   Float_t         phoTrkIsoC_1;
   Float_t         phosieie_1;
   Float_t         phosipip_1;
   Float_t         phosieip_1;
   Float_t         phoe2x2_1;
   Float_t         phoe3x3_1;
   Float_t         phoe5x5_1;
   Float_t         phosmaj_1;
   Float_t         phosmin_1;
   Float_t         phoalpha_1;
   Int_t           phoseed_1;
   vector<int>     *phorecHits_1;
   Float_t         phosuisseX_1;
   Bool_t          phoisOOT_1;
   Bool_t          phoisEB_1;
   Bool_t          phoisHLT_1;
   Bool_t          phoisTrk_1;
   Bool_t          phopassEleVeto_1;
   Bool_t          phohasPixSeed_1;
   Int_t           phogedID_1;
   Int_t           phoootID_1;
   Float_t         phoE_2;
   Float_t         phopt_2;
   Float_t         phoeta_2;
   Float_t         phophi_2;
   Float_t         phoscE_2;
   Float_t         phosceta_2;
   Float_t         phoscphi_2;
   Float_t         phoHoE_2;
   Float_t         phor9_2;
   Float_t         phoChgHadIso_2;
   Float_t         phoNeuHadIso_2;
   Float_t         phoPhoIso_2;
   Float_t         phoEcalPFClIso_2;
   Float_t         phoHcalPFClIso_2;
   Float_t         phoTrkIso_2;
   Float_t         phoChgHadIsoC_2;
   Float_t         phoNeuHadIsoC_2;
   Float_t         phoPhoIsoC_2;
   Float_t         phoEcalPFClIsoC_2;
   Float_t         phoHcalPFClIsoC_2;
   Float_t         phoTrkIsoC_2;
   Float_t         phosieie_2;
   Float_t         phosipip_2;
   Float_t         phosieip_2;
   Float_t         phoe2x2_2;
   Float_t         phoe3x3_2;
   Float_t         phoe5x5_2;
   Float_t         phosmaj_2;
   Float_t         phosmin_2;
   Float_t         phoalpha_2;
   Int_t           phoseed_2;
   vector<int>     *phorecHits_2;
   Float_t         phosuisseX_2;
   Bool_t          phoisOOT_2;
   Bool_t          phoisEB_2;
   Bool_t          phoisHLT_2;
   Bool_t          phoisTrk_2;
   Bool_t          phopassEleVeto_2;
   Bool_t          phohasPixSeed_2;
   Int_t           phogedID_2;
   Int_t           phoootID_2;
   Float_t         phoE_3;
   Float_t         phopt_3;
   Float_t         phoeta_3;
   Float_t         phophi_3;
   Float_t         phoscE_3;
   Float_t         phosceta_3;
   Float_t         phoscphi_3;
   Float_t         phoHoE_3;
   Float_t         phor9_3;
   Float_t         phoChgHadIso_3;
   Float_t         phoNeuHadIso_3;
   Float_t         phoPhoIso_3;
   Float_t         phoEcalPFClIso_3;
   Float_t         phoHcalPFClIso_3;
   Float_t         phoTrkIso_3;
   Float_t         phoChgHadIsoC_3;
   Float_t         phoNeuHadIsoC_3;
   Float_t         phoPhoIsoC_3;
   Float_t         phoEcalPFClIsoC_3;
   Float_t         phoHcalPFClIsoC_3;
   Float_t         phoTrkIsoC_3;
   Float_t         phosieie_3;
   Float_t         phosipip_3;
   Float_t         phosieip_3;
   Float_t         phoe2x2_3;
   Float_t         phoe3x3_3;
   Float_t         phoe5x5_3;
   Float_t         phosmaj_3;
   Float_t         phosmin_3;
   Float_t         phoalpha_3;
   Int_t           phoseed_3;
   vector<int>     *phorecHits_3;
   Float_t         phosuisseX_3;
   Bool_t          phoisOOT_3;
   Bool_t          phoisEB_3;
   Bool_t          phoisHLT_3;
   Bool_t          phoisTrk_3;
   Bool_t          phopassEleVeto_3;
   Bool_t          phohasPixSeed_3;
   Int_t           phogedID_3;
   Int_t           phoootID_3;

   // List of branches
   TBranch        *b_rho;   //!
   TBranch        *b_run;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_event;   //!
   TBranch        *b_bunch_crossing;   //!
   TBranch        *b_num_bunch;   //!
   TBranch        *b_beam1_VC;   //!
   TBranch        *b_beam2_VC;   //!
   TBranch        *b_beam1_RF;   //!
   TBranch        *b_beam2_RF;   //!
   TBranch        *b_subtrain_position;   //!
   TBranch        *b_train_position;   //!
   TBranch        *b_subtrain_number;   //!
   TBranch        *b_train_number;   //!
   TBranch        *b_hltSignal;   //!
   TBranch        *b_hltRefPhoID;   //!
   TBranch        *b_hltRefDispID;   //!
   TBranch        *b_hltRefHT;   //!
   TBranch        *b_hltPho50;   //!
   TBranch        *b_hltPho200;   //!
   TBranch        *b_hltDiPho70;   //!
   TBranch        *b_hltDiPho3022M90;   //!
   TBranch        *b_hltDiPho30PV18PV;   //!
   TBranch        *b_hltEle32WPT;   //!
   TBranch        *b_hltDiEle33MW;   //!
   TBranch        *b_hltJet500;   //!
   TBranch        *b_metPV;   //!
   TBranch        *b_metBeamHalo;   //!
   TBranch        *b_metHBHENoise;   //!
   TBranch        *b_metHBHEisoNoise;   //!
   TBranch        *b_metECALTP;   //!
   TBranch        *b_metPFMuon;   //!
   TBranch        *b_metPFChgHad;   //!
   TBranch        *b_metEESC;   //!
   TBranch        *b_metECALCalib;   //!
   TBranch        *b_metECALBadCalib;   //!
   TBranch        *b_nvtx;   //!
   TBranch        *b_vtxX;   //!
   TBranch        *b_vtxY;   //!
   TBranch        *b_vtxZ;   //!
   TBranch        *b_t1pfMETpt;   //!
   TBranch        *b_t1pfMETphi;   //!
   TBranch        *b_t1pfMETsumEt;   //!
   TBranch        *b_njets;   //!
   TBranch        *b_jetE;   //!
   TBranch        *b_jetpt;   //!
   TBranch        *b_jeteta;   //!
   TBranch        *b_jetphi;   //!
   TBranch        *b_jetID;   //!
   TBranch        *b_jetNHF;   //!
   TBranch        *b_jetNEMF;   //!
   TBranch        *b_jetCHF;   //!
   TBranch        *b_jetCEMF;   //!
   TBranch        *b_jetMUF;   //!
   TBranch        *b_jetNHM;   //!
   TBranch        *b_jetCHM;   //!
   TBranch        *b_nelLowL;   //!
   TBranch        *b_nelLowM;   //!
   TBranch        *b_nelLowT;   //!
   TBranch        *b_nelHighL;   //!
   TBranch        *b_nelHighM;   //!
   TBranch        *b_nelHighT;   //!
   TBranch        *b_nmuLowL;   //!
   TBranch        *b_nmuLowM;   //!
   TBranch        *b_nmuLowT;   //!
   TBranch        *b_nmuHighL;   //!
   TBranch        *b_nmuHighM;   //!
   TBranch        *b_nmuHighT;   //!
   TBranch        *b_nrechits;   //!
   TBranch        *b_rhX;   //!
   TBranch        *b_rhY;   //!
   TBranch        *b_rhZ;   //!
   TBranch        *b_rhE;   //!
   TBranch        *b_rhtime;   //!
   TBranch        *b_rhtimeErr;   //!
   TBranch        *b_rhTOF;   //!
   TBranch        *b_rhID;   //!
   TBranch        *b_rhisOOT;   //!
   TBranch        *b_rhisGS6;   //!
   TBranch        *b_rhisGS1;   //!
   TBranch        *b_rhadcToGeV;   //!
   TBranch        *b_rhped12;   //!
   TBranch        *b_rhped6;   //!
   TBranch        *b_rhped1;   //!
   TBranch        *b_rhpedrms12;   //!
   TBranch        *b_rhpedrms6;   //!
   TBranch        *b_rhpedrms1;   //!
   TBranch        *b_nphotons;   //!
   TBranch        *b_phoE_0;   //!
   TBranch        *b_phopt_0;   //!
   TBranch        *b_phoeta_0;   //!
   TBranch        *b_phophi_0;   //!
   TBranch        *b_phoscE_0;   //!
   TBranch        *b_phosceta_0;   //!
   TBranch        *b_phoscphi_0;   //!
   TBranch        *b_phoHoE_0;   //!
   TBranch        *b_phor9_0;   //!
   TBranch        *b_phoChgHadIso_0;   //!
   TBranch        *b_phoNeuHadIso_0;   //!
   TBranch        *b_phoPhoIso_0;   //!
   TBranch        *b_phoEcalPFClIso_0;   //!
   TBranch        *b_phoHcalPFClIso_0;   //!
   TBranch        *b_phoTrkIso_0;   //!
   TBranch        *b_phoChgHadIsoC_0;   //!
   TBranch        *b_phoNeuHadIsoC_0;   //!
   TBranch        *b_phoPhoIsoC_0;   //!
   TBranch        *b_phoEcalPFClIsoC_0;   //!
   TBranch        *b_phoHcalPFClIsoC_0;   //!
   TBranch        *b_phoTrkIsoC_0;   //!
   TBranch        *b_phosieie_0;   //!
   TBranch        *b_phosipip_0;   //!
   TBranch        *b_phosieip_0;   //!
   TBranch        *b_phoe2x2_0;   //!
   TBranch        *b_phoe3x3_0;   //!
   TBranch        *b_phoe5x5_0;   //!
   TBranch        *b_phosmaj_0;   //!
   TBranch        *b_phosmin_0;   //!
   TBranch        *b_phoalpha_0;   //!
   TBranch        *b_phoseed_0;   //!
   TBranch        *b_phorecHits_0;   //!
   TBranch        *b_phosuisseX_0;   //!
   TBranch        *b_phoisOOT_0;   //!
   TBranch        *b_phoisEB_0;   //!
   TBranch        *b_phoisHLT_0;   //!
   TBranch        *b_phoisTrk_0;   //!
   TBranch        *b_phopassEleVeto_0;   //!
   TBranch        *b_phohasPixSeed_0;   //!
   TBranch        *b_phogedID_0;   //!
   TBranch        *b_phoootID_0;   //!
   TBranch        *b_phoE_1;   //!
   TBranch        *b_phopt_1;   //!
   TBranch        *b_phoeta_1;   //!
   TBranch        *b_phophi_1;   //!
   TBranch        *b_phoscE_1;   //!
   TBranch        *b_phosceta_1;   //!
   TBranch        *b_phoscphi_1;   //!
   TBranch        *b_phoHoE_1;   //!
   TBranch        *b_phor9_1;   //!
   TBranch        *b_phoChgHadIso_1;   //!
   TBranch        *b_phoNeuHadIso_1;   //!
   TBranch        *b_phoPhoIso_1;   //!
   TBranch        *b_phoEcalPFClIso_1;   //!
   TBranch        *b_phoHcalPFClIso_1;   //!
   TBranch        *b_phoTrkIso_1;   //!
   TBranch        *b_phoChgHadIsoC_1;   //!
   TBranch        *b_phoNeuHadIsoC_1;   //!
   TBranch        *b_phoPhoIsoC_1;   //!
   TBranch        *b_phoEcalPFClIsoC_1;   //!
   TBranch        *b_phoHcalPFClIsoC_1;   //!
   TBranch        *b_phoTrkIsoC_1;   //!
   TBranch        *b_phosieie_1;   //!
   TBranch        *b_phosipip_1;   //!
   TBranch        *b_phosieip_1;   //!
   TBranch        *b_phoe2x2_1;   //!
   TBranch        *b_phoe3x3_1;   //!
   TBranch        *b_phoe5x5_1;   //!
   TBranch        *b_phosmaj_1;   //!
   TBranch        *b_phosmin_1;   //!
   TBranch        *b_phoalpha_1;   //!
   TBranch        *b_phoseed_1;   //!
   TBranch        *b_phorecHits_1;   //!
   TBranch        *b_phosuisseX_1;   //!
   TBranch        *b_phoisOOT_1;   //!
   TBranch        *b_phoisEB_1;   //!
   TBranch        *b_phoisHLT_1;   //!
   TBranch        *b_phoisTrk_1;   //!
   TBranch        *b_phopassEleVeto_1;   //!
   TBranch        *b_phohasPixSeed_1;   //!
   TBranch        *b_phogedID_1;   //!
   TBranch        *b_phoootID_1;   //!
   TBranch        *b_phoE_2;   //!
   TBranch        *b_phopt_2;   //!
   TBranch        *b_phoeta_2;   //!
   TBranch        *b_phophi_2;   //!
   TBranch        *b_phoscE_2;   //!
   TBranch        *b_phosceta_2;   //!
   TBranch        *b_phoscphi_2;   //!
   TBranch        *b_phoHoE_2;   //!
   TBranch        *b_phor9_2;   //!
   TBranch        *b_phoChgHadIso_2;   //!
   TBranch        *b_phoNeuHadIso_2;   //!
   TBranch        *b_phoPhoIso_2;   //!
   TBranch        *b_phoEcalPFClIso_2;   //!
   TBranch        *b_phoHcalPFClIso_2;   //!
   TBranch        *b_phoTrkIso_2;   //!
   TBranch        *b_phoChgHadIsoC_2;   //!
   TBranch        *b_phoNeuHadIsoC_2;   //!
   TBranch        *b_phoPhoIsoC_2;   //!
   TBranch        *b_phoEcalPFClIsoC_2;   //!
   TBranch        *b_phoHcalPFClIsoC_2;   //!
   TBranch        *b_phoTrkIsoC_2;   //!
   TBranch        *b_phosieie_2;   //!
   TBranch        *b_phosipip_2;   //!
   TBranch        *b_phosieip_2;   //!
   TBranch        *b_phoe2x2_2;   //!
   TBranch        *b_phoe3x3_2;   //!
   TBranch        *b_phoe5x5_2;   //!
   TBranch        *b_phosmaj_2;   //!
   TBranch        *b_phosmin_2;   //!
   TBranch        *b_phoalpha_2;   //!
   TBranch        *b_phoseed_2;   //!
   TBranch        *b_phorecHits_2;   //!
   TBranch        *b_phosuisseX_2;   //!
   TBranch        *b_phoisOOT_2;   //!
   TBranch        *b_phoisEB_2;   //!
   TBranch        *b_phoisHLT_2;   //!
   TBranch        *b_phoisTrk_2;   //!
   TBranch        *b_phopassEleVeto_2;   //!
   TBranch        *b_phohasPixSeed_2;   //!
   TBranch        *b_phogedID_2;   //!
   TBranch        *b_phoootID_2;   //!
   TBranch        *b_phoE_3;   //!
   TBranch        *b_phopt_3;   //!
   TBranch        *b_phoeta_3;   //!
   TBranch        *b_phophi_3;   //!
   TBranch        *b_phoscE_3;   //!
   TBranch        *b_phosceta_3;   //!
   TBranch        *b_phoscphi_3;   //!
   TBranch        *b_phoHoE_3;   //!
   TBranch        *b_phor9_3;   //!
   TBranch        *b_phoChgHadIso_3;   //!
   TBranch        *b_phoNeuHadIso_3;   //!
   TBranch        *b_phoPhoIso_3;   //!
   TBranch        *b_phoEcalPFClIso_3;   //!
   TBranch        *b_phoHcalPFClIso_3;   //!
   TBranch        *b_phoTrkIso_3;   //!
   TBranch        *b_phoChgHadIsoC_3;   //!
   TBranch        *b_phoNeuHadIsoC_3;   //!
   TBranch        *b_phoPhoIsoC_3;   //!
   TBranch        *b_phoEcalPFClIsoC_3;   //!
   TBranch        *b_phoHcalPFClIsoC_3;   //!
   TBranch        *b_phoTrkIsoC_3;   //!
   TBranch        *b_phosieie_3;   //!
   TBranch        *b_phosipip_3;   //!
   TBranch        *b_phosieip_3;   //!
   TBranch        *b_phoe2x2_3;   //!
   TBranch        *b_phoe3x3_3;   //!
   TBranch        *b_phoe5x5_3;   //!
   TBranch        *b_phosmaj_3;   //!
   TBranch        *b_phosmin_3;   //!
   TBranch        *b_phoalpha_3;   //!
   TBranch        *b_phoseed_3;   //!
   TBranch        *b_phorecHits_3;   //!
   TBranch        *b_phosuisseX_3;   //!
   TBranch        *b_phoisOOT_3;   //!
   TBranch        *b_phoisEB_3;   //!
   TBranch        *b_phoisHLT_3;   //!
   TBranch        *b_phoisTrk_3;   //!
   TBranch        *b_phopassEleVeto_3;   //!
   TBranch        *b_phohasPixSeed_3;   //!
   TBranch        *b_phogedID_3;   //!
   TBranch        *b_phoootID_3;   //!

   disphotree(TTree *tree=0);
   virtual ~disphotree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef disphotree_cxx
disphotree::disphotree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/t3-ku/jaking/datasets/ecalTiming/EGamma_ntuple/190209_143105/0000/Outputfile_1.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/t3-ku/jaking/datasets/ecalTiming/EGamma_ntuple/190209_143105/0000/Outputfile_1.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/home/t3-ku/jaking/datasets/ecalTiming/EGamma_ntuple/190209_143105/0000/Outputfile_1.root:/tree");
      dir->GetObject("disphotree",tree);

   }
   Init(tree);
}

disphotree::~disphotree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t disphotree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t disphotree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void disphotree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   jetE = 0;
   jetpt = 0;
   jeteta = 0;
   jetphi = 0;
   jetID = 0;
   jetNHF = 0;
   jetNEMF = 0;
   jetCHF = 0;
   jetCEMF = 0;
   jetMUF = 0;
   jetNHM = 0;
   jetCHM = 0;
   rhX = 0;
   rhY = 0;
   rhZ = 0;
   rhE = 0;
   rhtime = 0;
   rhtimeErr = 0;
   rhTOF = 0;
   rhID = 0;
   rhisOOT = 0;
   rhisGS6 = 0;
   rhisGS1 = 0;
   rhadcToGeV = 0;
   rhped12 = 0;
   rhped6 = 0;
   rhped1 = 0;
   rhpedrms12 = 0;
   rhpedrms6 = 0;
   rhpedrms1 = 0;
   phorecHits_0 = 0;
   phorecHits_1 = 0;
   phorecHits_2 = 0;
   phorecHits_3 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("bunch_crossing", &bunch_crossing, &b_bunch_crossing);
   fChain->SetBranchAddress("num_bunch", &num_bunch, &b_num_bunch);
   fChain->SetBranchAddress("beam1_VC", beam1_VC, &b_beam1_VC);
   fChain->SetBranchAddress("beam2_VC", beam2_VC, &b_beam2_VC);
   fChain->SetBranchAddress("beam1_RF", beam1_RF, &b_beam1_RF);
   fChain->SetBranchAddress("beam2_RF", beam2_RF, &b_beam2_RF);
   fChain->SetBranchAddress("subtrain_position", &subtrain_position, &b_subtrain_position);
   fChain->SetBranchAddress("train_position", &train_position, &b_train_position);
   fChain->SetBranchAddress("subtrain_number", &subtrain_number, &b_subtrain_number);
   fChain->SetBranchAddress("train_number", &train_number, &b_train_number);
   fChain->SetBranchAddress("hltSignal", &hltSignal, &b_hltSignal);
   fChain->SetBranchAddress("hltRefPhoID", &hltRefPhoID, &b_hltRefPhoID);
   fChain->SetBranchAddress("hltRefDispID", &hltRefDispID, &b_hltRefDispID);
   fChain->SetBranchAddress("hltRefHT", &hltRefHT, &b_hltRefHT);
   fChain->SetBranchAddress("hltPho50", &hltPho50, &b_hltPho50);
   fChain->SetBranchAddress("hltPho200", &hltPho200, &b_hltPho200);
   fChain->SetBranchAddress("hltDiPho70", &hltDiPho70, &b_hltDiPho70);
   fChain->SetBranchAddress("hltDiPho3022M90", &hltDiPho3022M90, &b_hltDiPho3022M90);
   fChain->SetBranchAddress("hltDiPho30PV18PV", &hltDiPho30PV18PV, &b_hltDiPho30PV18PV);
   fChain->SetBranchAddress("hltEle32WPT", &hltEle32WPT, &b_hltEle32WPT);
   fChain->SetBranchAddress("hltDiEle33MW", &hltDiEle33MW, &b_hltDiEle33MW);
   fChain->SetBranchAddress("hltJet500", &hltJet500, &b_hltJet500);
   fChain->SetBranchAddress("metPV", &metPV, &b_metPV);
   fChain->SetBranchAddress("metBeamHalo", &metBeamHalo, &b_metBeamHalo);
   fChain->SetBranchAddress("metHBHENoise", &metHBHENoise, &b_metHBHENoise);
   fChain->SetBranchAddress("metHBHEisoNoise", &metHBHEisoNoise, &b_metHBHEisoNoise);
   fChain->SetBranchAddress("metECALTP", &metECALTP, &b_metECALTP);
   fChain->SetBranchAddress("metPFMuon", &metPFMuon, &b_metPFMuon);
   fChain->SetBranchAddress("metPFChgHad", &metPFChgHad, &b_metPFChgHad);
   fChain->SetBranchAddress("metEESC", &metEESC, &b_metEESC);
   fChain->SetBranchAddress("metECALCalib", &metECALCalib, &b_metECALCalib);
   fChain->SetBranchAddress("metECALBadCalib", &metECALBadCalib, &b_metECALBadCalib);
   fChain->SetBranchAddress("nvtx", &nvtx, &b_nvtx);
   fChain->SetBranchAddress("vtxX", &vtxX, &b_vtxX);
   fChain->SetBranchAddress("vtxY", &vtxY, &b_vtxY);
   fChain->SetBranchAddress("vtxZ", &vtxZ, &b_vtxZ);
   fChain->SetBranchAddress("t1pfMETpt", &t1pfMETpt, &b_t1pfMETpt);
   fChain->SetBranchAddress("t1pfMETphi", &t1pfMETphi, &b_t1pfMETphi);
   fChain->SetBranchAddress("t1pfMETsumEt", &t1pfMETsumEt, &b_t1pfMETsumEt);
   fChain->SetBranchAddress("njets", &njets, &b_njets);
   fChain->SetBranchAddress("jetE", &jetE, &b_jetE);
   fChain->SetBranchAddress("jetpt", &jetpt, &b_jetpt);
   fChain->SetBranchAddress("jeteta", &jeteta, &b_jeteta);
   fChain->SetBranchAddress("jetphi", &jetphi, &b_jetphi);
   fChain->SetBranchAddress("jetID", &jetID, &b_jetID);
   fChain->SetBranchAddress("jetNHF", &jetNHF, &b_jetNHF);
   fChain->SetBranchAddress("jetNEMF", &jetNEMF, &b_jetNEMF);
   fChain->SetBranchAddress("jetCHF", &jetCHF, &b_jetCHF);
   fChain->SetBranchAddress("jetCEMF", &jetCEMF, &b_jetCEMF);
   fChain->SetBranchAddress("jetMUF", &jetMUF, &b_jetMUF);
   fChain->SetBranchAddress("jetNHM", &jetNHM, &b_jetNHM);
   fChain->SetBranchAddress("jetCHM", &jetCHM, &b_jetCHM);
   fChain->SetBranchAddress("nelLowL", &nelLowL, &b_nelLowL);
   fChain->SetBranchAddress("nelLowM", &nelLowM, &b_nelLowM);
   fChain->SetBranchAddress("nelLowT", &nelLowT, &b_nelLowT);
   fChain->SetBranchAddress("nelHighL", &nelHighL, &b_nelHighL);
   fChain->SetBranchAddress("nelHighM", &nelHighM, &b_nelHighM);
   fChain->SetBranchAddress("nelHighT", &nelHighT, &b_nelHighT);
   fChain->SetBranchAddress("nmuLowL", &nmuLowL, &b_nmuLowL);
   fChain->SetBranchAddress("nmuLowM", &nmuLowM, &b_nmuLowM);
   fChain->SetBranchAddress("nmuLowT", &nmuLowT, &b_nmuLowT);
   fChain->SetBranchAddress("nmuHighL", &nmuHighL, &b_nmuHighL);
   fChain->SetBranchAddress("nmuHighM", &nmuHighM, &b_nmuHighM);
   fChain->SetBranchAddress("nmuHighT", &nmuHighT, &b_nmuHighT);
   fChain->SetBranchAddress("nrechits", &nrechits, &b_nrechits);
   fChain->SetBranchAddress("rhX", &rhX, &b_rhX);
   fChain->SetBranchAddress("rhY", &rhY, &b_rhY);
   fChain->SetBranchAddress("rhZ", &rhZ, &b_rhZ);
   fChain->SetBranchAddress("rhE", &rhE, &b_rhE);
   fChain->SetBranchAddress("rhtime", &rhtime, &b_rhtime);
   fChain->SetBranchAddress("rhtimeErr", &rhtimeErr, &b_rhtimeErr);
   fChain->SetBranchAddress("rhTOF", &rhTOF, &b_rhTOF);
   fChain->SetBranchAddress("rhID", &rhID, &b_rhID);
   fChain->SetBranchAddress("rhisOOT", &rhisOOT, &b_rhisOOT);
   fChain->SetBranchAddress("rhisGS6", &rhisGS6, &b_rhisGS6);
   fChain->SetBranchAddress("rhisGS1", &rhisGS1, &b_rhisGS1);
   fChain->SetBranchAddress("rhadcToGeV", &rhadcToGeV, &b_rhadcToGeV);
   fChain->SetBranchAddress("rhped12", &rhped12, &b_rhped12);
   fChain->SetBranchAddress("rhped6", &rhped6, &b_rhped6);
   fChain->SetBranchAddress("rhped1", &rhped1, &b_rhped1);
   fChain->SetBranchAddress("rhpedrms12", &rhpedrms12, &b_rhpedrms12);
   fChain->SetBranchAddress("rhpedrms6", &rhpedrms6, &b_rhpedrms6);
   fChain->SetBranchAddress("rhpedrms1", &rhpedrms1, &b_rhpedrms1);
   fChain->SetBranchAddress("nphotons", &nphotons, &b_nphotons);
   fChain->SetBranchAddress("phoE_0", &phoE_0, &b_phoE_0);
   fChain->SetBranchAddress("phopt_0", &phopt_0, &b_phopt_0);
   fChain->SetBranchAddress("phoeta_0", &phoeta_0, &b_phoeta_0);
   fChain->SetBranchAddress("phophi_0", &phophi_0, &b_phophi_0);
   fChain->SetBranchAddress("phoscE_0", &phoscE_0, &b_phoscE_0);
   fChain->SetBranchAddress("phosceta_0", &phosceta_0, &b_phosceta_0);
   fChain->SetBranchAddress("phoscphi_0", &phoscphi_0, &b_phoscphi_0);
   fChain->SetBranchAddress("phoHoE_0", &phoHoE_0, &b_phoHoE_0);
   fChain->SetBranchAddress("phor9_0", &phor9_0, &b_phor9_0);
   fChain->SetBranchAddress("phoChgHadIso_0", &phoChgHadIso_0, &b_phoChgHadIso_0);
   fChain->SetBranchAddress("phoNeuHadIso_0", &phoNeuHadIso_0, &b_phoNeuHadIso_0);
   fChain->SetBranchAddress("phoPhoIso_0", &phoPhoIso_0, &b_phoPhoIso_0);
   fChain->SetBranchAddress("phoEcalPFClIso_0", &phoEcalPFClIso_0, &b_phoEcalPFClIso_0);
   fChain->SetBranchAddress("phoHcalPFClIso_0", &phoHcalPFClIso_0, &b_phoHcalPFClIso_0);
   fChain->SetBranchAddress("phoTrkIso_0", &phoTrkIso_0, &b_phoTrkIso_0);
   fChain->SetBranchAddress("phoChgHadIsoC_0", &phoChgHadIsoC_0, &b_phoChgHadIsoC_0);
   fChain->SetBranchAddress("phoNeuHadIsoC_0", &phoNeuHadIsoC_0, &b_phoNeuHadIsoC_0);
   fChain->SetBranchAddress("phoPhoIsoC_0", &phoPhoIsoC_0, &b_phoPhoIsoC_0);
   fChain->SetBranchAddress("phoEcalPFClIsoC_0", &phoEcalPFClIsoC_0, &b_phoEcalPFClIsoC_0);
   fChain->SetBranchAddress("phoHcalPFClIsoC_0", &phoHcalPFClIsoC_0, &b_phoHcalPFClIsoC_0);
   fChain->SetBranchAddress("phoTrkIsoC_0", &phoTrkIsoC_0, &b_phoTrkIsoC_0);
   fChain->SetBranchAddress("phosieie_0", &phosieie_0, &b_phosieie_0);
   fChain->SetBranchAddress("phosipip_0", &phosipip_0, &b_phosipip_0);
   fChain->SetBranchAddress("phosieip_0", &phosieip_0, &b_phosieip_0);
   fChain->SetBranchAddress("phoe2x2_0", &phoe2x2_0, &b_phoe2x2_0);
   fChain->SetBranchAddress("phoe3x3_0", &phoe3x3_0, &b_phoe3x3_0);
   fChain->SetBranchAddress("phoe5x5_0", &phoe5x5_0, &b_phoe5x5_0);
   fChain->SetBranchAddress("phosmaj_0", &phosmaj_0, &b_phosmaj_0);
   fChain->SetBranchAddress("phosmin_0", &phosmin_0, &b_phosmin_0);
   fChain->SetBranchAddress("phoalpha_0", &phoalpha_0, &b_phoalpha_0);
   fChain->SetBranchAddress("phoseed_0", &phoseed_0, &b_phoseed_0);
   fChain->SetBranchAddress("phorecHits_0", &phorecHits_0, &b_phorecHits_0);
   fChain->SetBranchAddress("phosuisseX_0", &phosuisseX_0, &b_phosuisseX_0);
   fChain->SetBranchAddress("phoisOOT_0", &phoisOOT_0, &b_phoisOOT_0);
   fChain->SetBranchAddress("phoisEB_0", &phoisEB_0, &b_phoisEB_0);
   fChain->SetBranchAddress("phoisHLT_0", &phoisHLT_0, &b_phoisHLT_0);
   fChain->SetBranchAddress("phoisTrk_0", &phoisTrk_0, &b_phoisTrk_0);
   fChain->SetBranchAddress("phopassEleVeto_0", &phopassEleVeto_0, &b_phopassEleVeto_0);
   fChain->SetBranchAddress("phohasPixSeed_0", &phohasPixSeed_0, &b_phohasPixSeed_0);
   fChain->SetBranchAddress("phogedID_0", &phogedID_0, &b_phogedID_0);
   fChain->SetBranchAddress("phoootID_0", &phoootID_0, &b_phoootID_0);
   fChain->SetBranchAddress("phoE_1", &phoE_1, &b_phoE_1);
   fChain->SetBranchAddress("phopt_1", &phopt_1, &b_phopt_1);
   fChain->SetBranchAddress("phoeta_1", &phoeta_1, &b_phoeta_1);
   fChain->SetBranchAddress("phophi_1", &phophi_1, &b_phophi_1);
   fChain->SetBranchAddress("phoscE_1", &phoscE_1, &b_phoscE_1);
   fChain->SetBranchAddress("phosceta_1", &phosceta_1, &b_phosceta_1);
   fChain->SetBranchAddress("phoscphi_1", &phoscphi_1, &b_phoscphi_1);
   fChain->SetBranchAddress("phoHoE_1", &phoHoE_1, &b_phoHoE_1);
   fChain->SetBranchAddress("phor9_1", &phor9_1, &b_phor9_1);
   fChain->SetBranchAddress("phoChgHadIso_1", &phoChgHadIso_1, &b_phoChgHadIso_1);
   fChain->SetBranchAddress("phoNeuHadIso_1", &phoNeuHadIso_1, &b_phoNeuHadIso_1);
   fChain->SetBranchAddress("phoPhoIso_1", &phoPhoIso_1, &b_phoPhoIso_1);
   fChain->SetBranchAddress("phoEcalPFClIso_1", &phoEcalPFClIso_1, &b_phoEcalPFClIso_1);
   fChain->SetBranchAddress("phoHcalPFClIso_1", &phoHcalPFClIso_1, &b_phoHcalPFClIso_1);
   fChain->SetBranchAddress("phoTrkIso_1", &phoTrkIso_1, &b_phoTrkIso_1);
   fChain->SetBranchAddress("phoChgHadIsoC_1", &phoChgHadIsoC_1, &b_phoChgHadIsoC_1);
   fChain->SetBranchAddress("phoNeuHadIsoC_1", &phoNeuHadIsoC_1, &b_phoNeuHadIsoC_1);
   fChain->SetBranchAddress("phoPhoIsoC_1", &phoPhoIsoC_1, &b_phoPhoIsoC_1);
   fChain->SetBranchAddress("phoEcalPFClIsoC_1", &phoEcalPFClIsoC_1, &b_phoEcalPFClIsoC_1);
   fChain->SetBranchAddress("phoHcalPFClIsoC_1", &phoHcalPFClIsoC_1, &b_phoHcalPFClIsoC_1);
   fChain->SetBranchAddress("phoTrkIsoC_1", &phoTrkIsoC_1, &b_phoTrkIsoC_1);
   fChain->SetBranchAddress("phosieie_1", &phosieie_1, &b_phosieie_1);
   fChain->SetBranchAddress("phosipip_1", &phosipip_1, &b_phosipip_1);
   fChain->SetBranchAddress("phosieip_1", &phosieip_1, &b_phosieip_1);
   fChain->SetBranchAddress("phoe2x2_1", &phoe2x2_1, &b_phoe2x2_1);
   fChain->SetBranchAddress("phoe3x3_1", &phoe3x3_1, &b_phoe3x3_1);
   fChain->SetBranchAddress("phoe5x5_1", &phoe5x5_1, &b_phoe5x5_1);
   fChain->SetBranchAddress("phosmaj_1", &phosmaj_1, &b_phosmaj_1);
   fChain->SetBranchAddress("phosmin_1", &phosmin_1, &b_phosmin_1);
   fChain->SetBranchAddress("phoalpha_1", &phoalpha_1, &b_phoalpha_1);
   fChain->SetBranchAddress("phoseed_1", &phoseed_1, &b_phoseed_1);
   fChain->SetBranchAddress("phorecHits_1", &phorecHits_1, &b_phorecHits_1);
   fChain->SetBranchAddress("phosuisseX_1", &phosuisseX_1, &b_phosuisseX_1);
   fChain->SetBranchAddress("phoisOOT_1", &phoisOOT_1, &b_phoisOOT_1);
   fChain->SetBranchAddress("phoisEB_1", &phoisEB_1, &b_phoisEB_1);
   fChain->SetBranchAddress("phoisHLT_1", &phoisHLT_1, &b_phoisHLT_1);
   fChain->SetBranchAddress("phoisTrk_1", &phoisTrk_1, &b_phoisTrk_1);
   fChain->SetBranchAddress("phopassEleVeto_1", &phopassEleVeto_1, &b_phopassEleVeto_1);
   fChain->SetBranchAddress("phohasPixSeed_1", &phohasPixSeed_1, &b_phohasPixSeed_1);
   fChain->SetBranchAddress("phogedID_1", &phogedID_1, &b_phogedID_1);
   fChain->SetBranchAddress("phoootID_1", &phoootID_1, &b_phoootID_1);
   fChain->SetBranchAddress("phoE_2", &phoE_2, &b_phoE_2);
   fChain->SetBranchAddress("phopt_2", &phopt_2, &b_phopt_2);
   fChain->SetBranchAddress("phoeta_2", &phoeta_2, &b_phoeta_2);
   fChain->SetBranchAddress("phophi_2", &phophi_2, &b_phophi_2);
   fChain->SetBranchAddress("phoscE_2", &phoscE_2, &b_phoscE_2);
   fChain->SetBranchAddress("phosceta_2", &phosceta_2, &b_phosceta_2);
   fChain->SetBranchAddress("phoscphi_2", &phoscphi_2, &b_phoscphi_2);
   fChain->SetBranchAddress("phoHoE_2", &phoHoE_2, &b_phoHoE_2);
   fChain->SetBranchAddress("phor9_2", &phor9_2, &b_phor9_2);
   fChain->SetBranchAddress("phoChgHadIso_2", &phoChgHadIso_2, &b_phoChgHadIso_2);
   fChain->SetBranchAddress("phoNeuHadIso_2", &phoNeuHadIso_2, &b_phoNeuHadIso_2);
   fChain->SetBranchAddress("phoPhoIso_2", &phoPhoIso_2, &b_phoPhoIso_2);
   fChain->SetBranchAddress("phoEcalPFClIso_2", &phoEcalPFClIso_2, &b_phoEcalPFClIso_2);
   fChain->SetBranchAddress("phoHcalPFClIso_2", &phoHcalPFClIso_2, &b_phoHcalPFClIso_2);
   fChain->SetBranchAddress("phoTrkIso_2", &phoTrkIso_2, &b_phoTrkIso_2);
   fChain->SetBranchAddress("phoChgHadIsoC_2", &phoChgHadIsoC_2, &b_phoChgHadIsoC_2);
   fChain->SetBranchAddress("phoNeuHadIsoC_2", &phoNeuHadIsoC_2, &b_phoNeuHadIsoC_2);
   fChain->SetBranchAddress("phoPhoIsoC_2", &phoPhoIsoC_2, &b_phoPhoIsoC_2);
   fChain->SetBranchAddress("phoEcalPFClIsoC_2", &phoEcalPFClIsoC_2, &b_phoEcalPFClIsoC_2);
   fChain->SetBranchAddress("phoHcalPFClIsoC_2", &phoHcalPFClIsoC_2, &b_phoHcalPFClIsoC_2);
   fChain->SetBranchAddress("phoTrkIsoC_2", &phoTrkIsoC_2, &b_phoTrkIsoC_2);
   fChain->SetBranchAddress("phosieie_2", &phosieie_2, &b_phosieie_2);
   fChain->SetBranchAddress("phosipip_2", &phosipip_2, &b_phosipip_2);
   fChain->SetBranchAddress("phosieip_2", &phosieip_2, &b_phosieip_2);
   fChain->SetBranchAddress("phoe2x2_2", &phoe2x2_2, &b_phoe2x2_2);
   fChain->SetBranchAddress("phoe3x3_2", &phoe3x3_2, &b_phoe3x3_2);
   fChain->SetBranchAddress("phoe5x5_2", &phoe5x5_2, &b_phoe5x5_2);
   fChain->SetBranchAddress("phosmaj_2", &phosmaj_2, &b_phosmaj_2);
   fChain->SetBranchAddress("phosmin_2", &phosmin_2, &b_phosmin_2);
   fChain->SetBranchAddress("phoalpha_2", &phoalpha_2, &b_phoalpha_2);
   fChain->SetBranchAddress("phoseed_2", &phoseed_2, &b_phoseed_2);
   fChain->SetBranchAddress("phorecHits_2", &phorecHits_2, &b_phorecHits_2);
   fChain->SetBranchAddress("phosuisseX_2", &phosuisseX_2, &b_phosuisseX_2);
   fChain->SetBranchAddress("phoisOOT_2", &phoisOOT_2, &b_phoisOOT_2);
   fChain->SetBranchAddress("phoisEB_2", &phoisEB_2, &b_phoisEB_2);
   fChain->SetBranchAddress("phoisHLT_2", &phoisHLT_2, &b_phoisHLT_2);
   fChain->SetBranchAddress("phoisTrk_2", &phoisTrk_2, &b_phoisTrk_2);
   fChain->SetBranchAddress("phopassEleVeto_2", &phopassEleVeto_2, &b_phopassEleVeto_2);
   fChain->SetBranchAddress("phohasPixSeed_2", &phohasPixSeed_2, &b_phohasPixSeed_2);
   fChain->SetBranchAddress("phogedID_2", &phogedID_2, &b_phogedID_2);
   fChain->SetBranchAddress("phoootID_2", &phoootID_2, &b_phoootID_2);
   fChain->SetBranchAddress("phoE_3", &phoE_3, &b_phoE_3);
   fChain->SetBranchAddress("phopt_3", &phopt_3, &b_phopt_3);
   fChain->SetBranchAddress("phoeta_3", &phoeta_3, &b_phoeta_3);
   fChain->SetBranchAddress("phophi_3", &phophi_3, &b_phophi_3);
   fChain->SetBranchAddress("phoscE_3", &phoscE_3, &b_phoscE_3);
   fChain->SetBranchAddress("phosceta_3", &phosceta_3, &b_phosceta_3);
   fChain->SetBranchAddress("phoscphi_3", &phoscphi_3, &b_phoscphi_3);
   fChain->SetBranchAddress("phoHoE_3", &phoHoE_3, &b_phoHoE_3);
   fChain->SetBranchAddress("phor9_3", &phor9_3, &b_phor9_3);
   fChain->SetBranchAddress("phoChgHadIso_3", &phoChgHadIso_3, &b_phoChgHadIso_3);
   fChain->SetBranchAddress("phoNeuHadIso_3", &phoNeuHadIso_3, &b_phoNeuHadIso_3);
   fChain->SetBranchAddress("phoPhoIso_3", &phoPhoIso_3, &b_phoPhoIso_3);
   fChain->SetBranchAddress("phoEcalPFClIso_3", &phoEcalPFClIso_3, &b_phoEcalPFClIso_3);
   fChain->SetBranchAddress("phoHcalPFClIso_3", &phoHcalPFClIso_3, &b_phoHcalPFClIso_3);
   fChain->SetBranchAddress("phoTrkIso_3", &phoTrkIso_3, &b_phoTrkIso_3);
   fChain->SetBranchAddress("phoChgHadIsoC_3", &phoChgHadIsoC_3, &b_phoChgHadIsoC_3);
   fChain->SetBranchAddress("phoNeuHadIsoC_3", &phoNeuHadIsoC_3, &b_phoNeuHadIsoC_3);
   fChain->SetBranchAddress("phoPhoIsoC_3", &phoPhoIsoC_3, &b_phoPhoIsoC_3);
   fChain->SetBranchAddress("phoEcalPFClIsoC_3", &phoEcalPFClIsoC_3, &b_phoEcalPFClIsoC_3);
   fChain->SetBranchAddress("phoHcalPFClIsoC_3", &phoHcalPFClIsoC_3, &b_phoHcalPFClIsoC_3);
   fChain->SetBranchAddress("phoTrkIsoC_3", &phoTrkIsoC_3, &b_phoTrkIsoC_3);
   fChain->SetBranchAddress("phosieie_3", &phosieie_3, &b_phosieie_3);
   fChain->SetBranchAddress("phosipip_3", &phosipip_3, &b_phosipip_3);
   fChain->SetBranchAddress("phosieip_3", &phosieip_3, &b_phosieip_3);
   fChain->SetBranchAddress("phoe2x2_3", &phoe2x2_3, &b_phoe2x2_3);
   fChain->SetBranchAddress("phoe3x3_3", &phoe3x3_3, &b_phoe3x3_3);
   fChain->SetBranchAddress("phoe5x5_3", &phoe5x5_3, &b_phoe5x5_3);
   fChain->SetBranchAddress("phosmaj_3", &phosmaj_3, &b_phosmaj_3);
   fChain->SetBranchAddress("phosmin_3", &phosmin_3, &b_phosmin_3);
   fChain->SetBranchAddress("phoalpha_3", &phoalpha_3, &b_phoalpha_3);
   fChain->SetBranchAddress("phoseed_3", &phoseed_3, &b_phoseed_3);
   fChain->SetBranchAddress("phorecHits_3", &phorecHits_3, &b_phorecHits_3);
   fChain->SetBranchAddress("phosuisseX_3", &phosuisseX_3, &b_phosuisseX_3);
   fChain->SetBranchAddress("phoisOOT_3", &phoisOOT_3, &b_phoisOOT_3);
   fChain->SetBranchAddress("phoisEB_3", &phoisEB_3, &b_phoisEB_3);
   fChain->SetBranchAddress("phoisHLT_3", &phoisHLT_3, &b_phoisHLT_3);
   fChain->SetBranchAddress("phoisTrk_3", &phoisTrk_3, &b_phoisTrk_3);
   fChain->SetBranchAddress("phopassEleVeto_3", &phopassEleVeto_3, &b_phopassEleVeto_3);
   fChain->SetBranchAddress("phohasPixSeed_3", &phohasPixSeed_3, &b_phohasPixSeed_3);
   fChain->SetBranchAddress("phogedID_3", &phogedID_3, &b_phogedID_3);
   fChain->SetBranchAddress("phoootID_3", &phoootID_3, &b_phoootID_3);
   Notify();
}

Bool_t disphotree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void disphotree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t disphotree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef disphotree_cxx
