#ifndef _skimmertypes_ 
#define _skimmertypes_ 

#include <string>
#include <vector>

#include "TBranch.h"

enum SkimType {Standard, Zee, DiXtal, AlwaysTrue, AlwaysFalse};
enum ECorr {Nominal, Down, Up};

// struct for containing electrons in Z
struct MassStruct
{
  MassStruct() {}
  MassStruct(const Int_t ipho1, const Int_t ipho2, const Float_t mass, Float_t dR12)
    : ipho1(ipho1), ipho2(ipho2), mass(mass), dR12(dR12) {}

  Int_t ipho1;
  Int_t ipho2;
  Float_t mass;
  Float_t dR12;
};

// simple struct for pairs of detids
struct DiXtalInfo
{
  DiXtalInfo(){}
  DiXtalInfo(const Int_t rh1, const Int_t rh2, const Int_t iph) 
    : rh1(rh1), rh2(rh2), iph(iph) {}
  
  Int_t rh1;
  Int_t rh2;
  Int_t iph;
};

struct Configuration
{
  // branches
  UInt_t  blindSF;
  Bool_t  applyBlindSF;
  Float_t blindMET;
  Bool_t  applyBlindMET;
  Float_t jetpTmin;
  Float_t jetEtamax;
  Int_t   jetIDmin;
  Float_t rhEmin;
  Float_t phpTmin;
  std::string * phIDmin;
  std::string phIDmin_s;
  Float_t seedTimemin;
  Bool_t  splitPho;
  Bool_t  onlyGED;
  Bool_t  onlyOOT;
  Float_t ellowpTmin;
  Float_t elhighpTmin;
  Float_t mulowpTmin;
  Float_t muhighpTmin;
  Bool_t  storeRecHits;
  Bool_t  applyTrigger;
  Float_t minHT;
  Bool_t  applyHT;
  Float_t phgoodpTmin;
  std::string * phgoodIDmin;
  std::string phgoodIDmin_s;
  Bool_t  applyPhGood;
  Float_t dRmin;
  Float_t pTres;
  Float_t genpTres;
  Float_t trackdRmin;
  Float_t trackpTmin;
  Float_t genjetdRmin;
  Float_t genjetpTfactor;
  Float_t leptondRmin;
  Float_t smearjetEmin;
  std::string * inputPaths;
  std::string inputPaths_s;
  std::string * inputFilters;
  std::string inputFilters_s;
  std::string * inputFlags;
  std::string inputFlags_s;
  Bool_t  isGMSB;
  Bool_t  isHVDS;
  Bool_t  isBkgd;
  Bool_t  isToy;
  Bool_t  isADD;
  Float_t xsec;
  Float_t filterEff;
  Float_t BR;
  Float_t sumWgts;
  Float_t sampleWeight;
  std::vector<Float_t> puWeights;

  // branch names
  std::string s_blindSF = "blindSF";
  std::string s_applyBlindSF = "applyBlindSF";
  std::string s_blindMET = "blindMET";
  std::string s_applyBlindMET = "applyBlindMET";
  std::string s_jetpTmin = "jetpTmin";
  std::string s_jetEtamax = "jetEtamax";
  std::string s_jetIDmin = "jetIDmin";
  std::string s_rhEmin = "rhEmin";
  std::string s_phpTmin = "phpTmin";
  std::string s_phIDmin = "phIDmin";
  std::string s_seedTimemin = "seedTimemin";
  std::string s_splitPho = "splitPho";
  std::string s_onlyGED = "onlyGED";
  std::string s_onlyOOT = "onlyOOT";
  std::string s_ellowpTmin = "ellowpTmin";
  std::string s_elhighpTmin = "elhighpTmin";
  std::string s_mulowpTmin = "mulowpTmin";
  std::string s_muhighpTmin = "muhighpTmin";
  std::string s_storeRecHits = "storeRecHits";
  std::string s_applyTrigger = "applyTrigger";
  std::string s_minHT = "minHT";
  std::string s_applyHT = "applyHT";
  std::string s_phgoodpTmin = "phgoodpTmin";
  std::string s_phgoodIDmin = "phgoodIDmin";
  std::string s_applyPhGood = "applyPhGood";
  std::string s_dRmin = "dRmin";
  std::string s_pTres = "pTres";
  std::string s_genpTres = "genpTres";
  std::string s_trackdRmin = "trackdRmin";
  std::string s_trackpTmin = "trackpTmin";
  std::string s_genjetdRmin = "genjetdRmin";
  std::string s_genjetpTfactor = "genjetpTfactor";
  std::string s_leptondRmin = "leptondRmin";
  std::string s_smearjetEmin = "smearjetEmin";
  std::string s_inputPaths = "inputPaths";
  std::string s_inputFilters = "inputFilters";
  std::string s_inputFlags = "inputFlags";
  std::string s_isGMSB = "isGMSB";
  std::string s_isHVDS = "isHVDS";
  std::string s_isBkgd = "isBkgd";
  std::string s_isToy  = "isToy";
  std::string s_isADD  = "isADD";
  std::string s_xsec = "xsec";
  std::string s_filterEff = "filterEff";
  std::string s_BR = "BR";
  std::string s_sumWgts = "sumWgts"; 
  std::string s_sampleWeight = "sampleWeight";
  std::string s_puWeights = "puWeights";
};

struct Event
{
  // branches
  UInt_t    run;
  UInt_t    lumi;
  ULong64_t event;
  Bool_t    hltSignal;
  Bool_t    hltRefPhoID;
  Bool_t    hltRefDispID;
  Bool_t    hltRefHT;
  Bool_t    hltPho50;
  Bool_t    hltPho200;
  Bool_t    hltDiPho70;
  Bool_t    hltDiPho3022M90;
  Bool_t    hltDiPho30PV18PV;
  Bool_t    hltEle32WPT;
  Bool_t    hltDiEle33MW;
  Bool_t    hltJet500;
  Bool_t    metPV;
  Bool_t    metBeamHalo;
  Bool_t    metHBHENoise;
  Bool_t    metHBHEisoNoise;
  Bool_t    metECALTP;
  Bool_t    metPFMuon;
  Bool_t    metPFChgHad;
  Bool_t    metEESC;
  Bool_t    metECALCalib;
  Bool_t    metECALBadCalib;

  Int_t     nvtx;
  Float_t   vtxX;
  Float_t   vtxY;
  Float_t   vtxZ;
  Float_t   rho;
  Float_t   t1pfMETpt;
  Float_t   t1pfMETphi;
  Float_t   t1pfMETsumEt;

  Int_t     njets;
  Int_t     nelLowL;
  Int_t     nelLowM;
  Int_t     nelLowT;
  Int_t     nelHighL;
  Int_t     nelHighM;
  Int_t     nelHighT;
  Int_t     nmuLowL;
  Int_t     nmuLowM;
  Int_t     nmuLowT;
  Int_t     nmuHighL;
  Int_t     nmuHighM;
  Int_t     nmuHighT;
  Int_t     nrechits;
  Int_t     nkurechits;
  Int_t     nphotons;

  Float_t   evtwgt;

  // MC Types
  Float_t   genwgt;
  Float_t   genx0;
  Float_t   geny0;
  Float_t   genz0;
  Float_t   gent0;
  Int_t     genpuobs;
  Int_t     genputrue;
  Float_t   puwgt;
  // GMSB
  Int_t     nNeutoPhGr;
  // HVDS
  Int_t     nvPions;
  // ToyMC 
  Int_t     nToyPhs;

  // branch names
  std::string s_run = "run";
  std::string s_lumi = "lumi";
  std::string s_event = "event";
  std::string s_hltSignal = "hltSignal";
  std::string s_hltRefPhoID = "hltRefPhoID";
  std::string s_hltRefDispID = "hltRefDispID";
  std::string s_hltRefHT = "hltRefHT";
  std::string s_hltPho50 = "hltPho50";
  std::string s_hltPho200 = "hltPho200";
  std::string s_hltDiPho70 = "hltDiPho70";
  std::string s_hltDiPho3022M90 = "hltDiPho3022M90";
  std::string s_hltDiPho30PV18PV = "hltDiPho30PV18PV";
  std::string s_hltEle32WPT = "hltEle32WPT";
  std::string s_hltDiEle33MW = "hltDiEle33MW";
  std::string s_hltJet500 = "hltJet500";
  std::string s_metPV = "metPV";
  std::string s_metBeamHalo = "metBeamHalo";
  std::string s_metHBHENoise = "metHBHENoise";
  std::string s_metHBHEisoNoise = "metHBHEisoNoise";
  std::string s_metECALTP = "metECALTP";
  std::string s_metPFMuon = "metPFMuon";
  std::string s_metPFChgHad = "metPFChgHad";
  std::string s_metEESC = "metEESC";
  std::string s_metECALCalib = "metECALCalib";
  std::string s_metECALBadCalib = "metECALBadCalib";
  std::string s_nvtx = "nvtx";
  std::string s_vtxX = "vtxX";
  std::string s_vtxY = "vtxY";
  std::string s_vtxZ = "vtxZ";
  std::string s_rho = "rho";
  std::string s_t1pfMETpt = "t1pfMETpt";
  std::string s_t1pfMETphi = "t1pfMETphi";
  std::string s_t1pfMETsumEt = "t1pfMETsumEt";
  std::string s_njets = "njets";
  std::string s_nelLowL = "nelLowL";
  std::string s_nelLowM = "nelLowM";
  std::string s_nelLowT = "nelLowT";
  std::string s_nelHighL = "nelHighL";
  std::string s_nelHighM = "nelHighM";
  std::string s_nelHighT = "nelHighT";
  std::string s_nmuLowL = "nmuLowL";
  std::string s_nmuLowM = "nmuLowM";
  std::string s_nmuLowT = "nmuLowT";
  std::string s_nmuHighL = "nmuHighL";
  std::string s_nmuHighM = "nmuHighM";
  std::string s_nmuHighT = "nmuHighT";
  std::string s_nrechits = "nrechits";
  std::string s_nkurechits = "nkurechits";
  std::string s_nphotons = "nphotons";
  std::string s_evtwgt = "evtwgt";
  std::string s_genwgt = "genwgt";  
  std::string s_genx0 = "genx0";
  std::string s_geny0 = "geny0";
  std::string s_genz0 = "genz0";
  std::string s_gent0 = "gent0";
  std::string s_genpuobs = "genpuobs";
  std::string s_genputrue = "genputrue";
  std::string s_puwgt = "puwgt";
  std::string s_nNeutoPhGr = "nNeutoPhGr";
  std::string s_nvPions = "nvPions";
  std::string s_nToyPhs = "nToyPhs";

  // tbranches
  TBranch * b_run;
  TBranch * b_lumi;
  TBranch * b_event;
  TBranch * b_hltSignal;
  TBranch * b_hltRefPhoID;
  TBranch * b_hltRefDispID;
  TBranch * b_hltRefHT;
  TBranch * b_hltPho50;
  TBranch * b_hltPho200;
  TBranch * b_hltDiPho70;
  TBranch * b_hltDiPho3022M90;
  TBranch * b_hltDiPho30PV18PV;
  TBranch * b_hltEle32WPT;
  TBranch * b_hltDiEle33MW;
  TBranch * b_hltJet500;
  TBranch * b_metPV;
  TBranch * b_metBeamHalo;
  TBranch * b_metHBHENoise;
  TBranch * b_metHBHEisoNoise;
  TBranch * b_metECALTP;
  TBranch * b_metPFMuon;
  TBranch * b_metPFChgHad;
  TBranch * b_metEESC;
  TBranch * b_metECALCalib;
  TBranch * b_metECALBadCalib;
  TBranch * b_nvtx;
  TBranch * b_vtxX;
  TBranch * b_vtxY;
  TBranch * b_vtxZ;
  TBranch * b_rho;
  TBranch * b_t1pfMETpt;
  TBranch * b_t1pfMETphi;
  TBranch * b_t1pfMETsumEt;
  TBranch * b_njets;
  TBranch * b_nelLowL;
  TBranch * b_nelLowM;
  TBranch * b_nelLowT;
  TBranch * b_nelHighL;
  TBranch * b_nelHighM;
  TBranch * b_nelHighT;
  TBranch * b_nmuLowL;
  TBranch * b_nmuLowM;
  TBranch * b_nmuLowT;
  TBranch * b_nmuHighL;
  TBranch * b_nmuHighM;
  TBranch * b_nmuHighT;
  TBranch * b_nrechits;
  TBranch * b_nkurechits;
  TBranch * b_nphotons;
  TBranch * b_evtwgt;
  TBranch * b_genwgt;
  TBranch * b_genx0;
  TBranch * b_geny0;
  TBranch * b_genz0;
  TBranch * b_gent0;
  TBranch * b_genpuobs;
  TBranch * b_genputrue;
  TBranch * b_puwgt;
  TBranch * b_nNeutoPhGr;
  TBranch * b_nvPions;
  TBranch * b_nToyPhs;
};

struct Jet
{
  std::vector<Float_t> * E;
  std::vector<Float_t> * pt;
  std::vector<Float_t> * phi;
  std::vector<Float_t> * eta;
  std::vector<Int_t>   * ID;

  std::vector<Float_t> * NHF;
  std::vector<Float_t> * NEMF;
  std::vector<Float_t> * CHF;
  std::vector<Float_t> * CEMF;
  std::vector<Float_t> * MUF;
  std::vector<Float_t> * NHM;
  std::vector<Float_t> * CHM;

  std::vector<Float_t> * scaleRel;
  std::vector<Float_t> * smearSF;
  std::vector<Float_t> * smearDownSF;
  std::vector<Float_t> * smearUpSF;
  std::vector<Int_t>   * isGen;

  std::vector<Float_t> E_f;
  std::vector<Float_t> pt_f;
  std::vector<Float_t> phi_f;
  std::vector<Float_t> eta_f;
  std::vector<Int_t>   ID_i;
  
  std::vector<Float_t> NHF_f;
  std::vector<Float_t> NEMF_f;
  std::vector<Float_t> CHF_f;
  std::vector<Float_t> CEMF_f;
  std::vector<Float_t> MUF_f;
  std::vector<Float_t> NHM_f;
  std::vector<Float_t> CHM_f;

  std::vector<Float_t> scaleRel_f;
  std::vector<Float_t> smearSF_f;
  std::vector<Float_t> smearDownSF_f;
  std::vector<Float_t> smearUpSF_f;
  std::vector<Int_t>   isGen_i;

  std::string s_E = "jetE";
  std::string s_pt = "jetpt";
  std::string s_phi = "jetphi";
  std::string s_eta = "jeteta";
  std::string s_ID = "jetID";

  std::string s_NHF = "jetNHF";
  std::string s_NEMF = "jetNEMF";
  std::string s_CHF = "jetCHF";
  std::string s_CEMF = "jetCEMF";
  std::string s_MUF = "jetMUF";
  std::string s_NHM = "jetNHM";
  std::string s_CHM = "jetCHM";

  std::string s_scaleRel = "jetscaleRel";
  std::string s_smearSF = "jetsmearSF";
  std::string s_smearDownSF = "jetsmearDownSF";
  std::string s_smearUpSF = "jetsmearUpSF";
  std::string s_isGen = "jetisGen";

  TBranch * b_E;
  TBranch * b_pt;
  TBranch * b_phi;
  TBranch * b_eta;
  TBranch * b_ID;

  TBranch * b_NHF;
  TBranch * b_NEMF;
  TBranch * b_CHF;
  TBranch * b_CEMF;
  TBranch * b_MUF;
  TBranch * b_NHM;
  TBranch * b_CHM;

  TBranch * b_scaleRel;
  TBranch * b_smearSF;
  TBranch * b_smearDownSF;
  TBranch * b_smearUpSF;
  TBranch * b_isGen;
};

struct RecHits
{
  std::vector<Float_t> * X;
  std::vector<Float_t> * Y;
  std::vector<Float_t> * Z;
  std::vector<Float_t> * E;
  std::vector<Float_t> * time;
  std::vector<Float_t> * timeErr;
  std::vector<Float_t> * TOF;
  std::vector<UInt_t>  * ID;
  std::vector<Int_t>   * isOOT;
  std::vector<Int_t>   * isGS6;
  std::vector<Int_t>   * isGS1;
  std::vector<Float_t> * adcToGeV;
  std::vector<Float_t> * ped12;
  std::vector<Float_t> * ped6;
  std::vector<Float_t> * ped1;
  std::vector<Float_t> * pedrms12;
  std::vector<Float_t> * pedrms6;
  std::vector<Float_t> * pedrms1;

  std::string s_X = "rhX";
  std::string s_Y = "rhY";
  std::string s_Z = "rhZ";
  std::string s_E = "rhE";
  std::string s_time = "rhtime";
  std::string s_timeErr = "rhtimeErr";
  std::string s_TOF = "rhTOF";
  std::string s_ID = "rhID";
  std::string s_isOOT = "rhisOOT";
  std::string s_isGS6 = "rhisGS6";
  std::string s_isGS1 = "rhisGS1";
  std::string s_adcToGeV = "rhadcToGeV";
  std::string s_ped12 = "rhped12";
  std::string s_ped6 = "rhped6";
  std::string s_ped1 = "rhped1";
  std::string s_pedrms12 = "rhpedrms12";
  std::string s_pedrms6 = "rhpedrms6";
  std::string s_pedrms1 = "rhpedrms1";

  TBranch * b_X;
  TBranch * b_Y;
  TBranch * b_Z;
  TBranch * b_E;
  TBranch * b_time;
  TBranch * b_timeErr;
  TBranch * b_TOF;
  TBranch * b_ID;
  TBranch * b_isOOT;
  TBranch * b_isGS6;
  TBranch * b_isGS1;
  TBranch * b_adcToGeV;
  TBranch * b_ped12;
  TBranch * b_ped6;
  TBranch * b_ped1;
  TBranch * b_pedrms12;
  TBranch * b_pedrms6;
  TBranch * b_pedrms1;
};

struct Pho
{
  Float_t E;
  Float_t pt;
  Float_t eta;
  Float_t phi;
  Float_t scE;
  Float_t sceta;
  Float_t scphi;
  Float_t HoE;
  Float_t r9;
  Float_t tdz;
  Float_t ChgHadIso;
  Float_t NeuHadIso;
  Float_t PhoIso;
  Float_t EcalPFClIso;
  Float_t HcalPFClIso;
  Float_t TrkIso;
  Float_t ChgHadIsoC;
  Float_t NeuHadIsoC;
  Float_t PhoIsoC;
  Float_t EcalPFClIsoC;
  Float_t HcalPFClIsoC;
  Float_t TrkIsoC;
  Float_t sieie;
  Float_t sipip;
  Float_t sieip;
  Float_t e2x2;
  Float_t e3x3;
  Float_t e5x5;
  Float_t smaj;
  Float_t smin;
  Float_t alpha;
  Int_t   seed;
  std::vector<Int_t> * recHits;
  std::vector<Int_t> * kurecHits;
  Float_t suisseX;
  Bool_t  isOOT;
  Bool_t  isEB;
  Bool_t  isHLT;
  Bool_t  isTrk;
  Bool_t  passEleVeto;
  Bool_t  hasPixSeed;
  Int_t   gedID;
  Int_t   ootID;
  // RecHit Info (whether stored directly or read through rec hit information)
  Float_t seedX;
  Float_t seedY;
  Float_t seedZ;
  Float_t seedE;
  Float_t seedtime;
  Float_t seedtimeErr;
  Float_t seedTOF;
  UInt_t  seedID;
  Int_t   seedisGS6;
  Int_t   seedisGS1;
  Float_t seedadcToGeV;
  Float_t seedped12;
  Float_t seedped6;
  Float_t seedped1;
  Float_t seedpedrms12;
  Float_t seedpedrms6;
  Float_t seedpedrms1;
  //  ucal RecHit Info
  Float_t seedootA0;
  Float_t seedootA1;
  Float_t seedootA2;
  Float_t seedootA3;
  Float_t seedootA4;
  Float_t seedootA5;
  Float_t seedootA6;
  Float_t seedootA7;
  Float_t seedootA8;
  Float_t seedootA9;
  Float_t seedootMax;
  Float_t seedootVsum;
  Float_t seedootMbefore;
  Float_t seedootMafter;
  Int_t   seedootSign;;

  // KU RecHit info

  //Float_t seedkuX;
  //Float_t seedkuY;
  //Float_t seedkuZ;
  Float_t seedkuE;
  Float_t seedkutime;
  Float_t seedkutimeErr;
  Float_t seedkuTOF;
  UInt_t  seedkuID;
  //Int_t   seedkuisGS6;
  //Int_t   seedkuisGS1;
  //Float_t seedkuadcToGeV;
  //Float_t seedkuped12;
  //Float_t seedkuped6;
  //Float_t seedkuped1;
  //Float_t seedkupedrms12;
  //Float_t seedkupedrms6;
  //Float_t seedkupedrms1;

  //Float_t seedkuStcX;
  //Float_t seedkuStcY;
  //Float_t seedkuStcZ;
  Float_t seedkuStcE;
  Float_t seedkuStctime;
  Float_t seedkuStctimeErr;
  Float_t seedkuStcTOF;
  UInt_t  seedkuStcID;
  //Int_t   seedkuStcisGS6;
  //Int_t   seedkuStcisGS1;
  //Float_t seedkuStcadcToGeV;
  //Float_t seedkuStcped12;
  //Float_t seedkuStcped6;
  //Float_t seedkuStcped1;
  //Float_t seedkuStcpedrms12;
  //Float_t seedkuStcpedrms6;
  //Float_t seedkuStcpedrms1;

  //Float_t seedkuNotX;
  //Float_t seedkuNotY;
  //Float_t seedkuNotZ;
  Float_t seedkuNotE;
  Float_t seedkuNottime;
  Float_t seedkuNottimeErr;
  Float_t seedkuNotTOF;
  UInt_t  seedkuNotID;
  //Int_t   seedkuNotisGS6;
  //Int_t   seedkuNotisGS1;
  //Float_t seedkuNotadcToGeV;
  //Float_t seedkuNotped12;
  //Float_t seedkuNotped6;
  //Float_t seedkuNotped1;
  //Float_t seedkuNotpedrms12;
  //Float_t seedkuNotpedrms6;
  //Float_t seedkuNotpedrms1;

  //Float_t seedkuNotStcX;
  //Float_t seedkuNotStcY;
  //Float_t seedkuNotStcZ;
  Float_t seedkuNotStcE;
  Float_t seedkuNotStctime;
  Float_t seedkuNotStctimeErr;
  Float_t seedkuNotStcTOF;
  UInt_t  seedkuNotStcID;
  //Int_t   seedkuNotStcisGS6;
  //Int_t   seedkuNotStcisGS1;
  //Float_t seedkuNotStcadcToGeV;
  //Float_t seedkuNotStcped12;
  //Float_t seedkuNotStcped6;
  //Float_t seedkuNotStcped1;
  //Float_t seedkuNotStcpedrms12;
  //Float_t seedkuNotStcpedrms6;
  //Float_t seedkuNotStcpedrms1;

  // MC types
  Bool_t  isGen;
  Int_t   isSignal;
  Float_t scaleAbs;
  Float_t smearAbs;
  // Derived types
  Int_t   seedTT;
  Int_t   nrechits;
  Int_t   nrechitsLT120;
  Float_t meantime;
  Float_t meantimeLT120;
  Float_t weightedtime;
  Float_t weightedtimeLT120;
  Float_t weightedtimeTOF;
  Float_t weightedtimeLT120TOF;

  // branch names
  std::string s_E = "phoE";
  std::string s_pt = "phopt";
  std::string s_eta = "phoeta";
  std::string s_phi = "phophi";
  std::string s_scE = "phoscE";
  std::string s_sceta = "phosceta";
  std::string s_scphi = "phoscphi";
  std::string s_HoE = "phoHoE";
  std::string s_r9 = "phor9";
  std::string s_tdz = "photdz";
  std::string s_ChgHadIso = "phoChgHadIso";
  std::string s_NeuHadIso = "phoNeuHadIso";
  std::string s_PhoIso = "phoPhoIso";
  std::string s_EcalPFClIso = "phoEcalPFClIso";
  std::string s_HcalPFClIso = "phoHcalPFClIso";
  std::string s_TrkIso = "phoTrkIso";
  std::string s_ChgHadIsoC = "phoChgHadIsoC";
  std::string s_NeuHadIsoC = "phoNeuHadIsoC";
  std::string s_PhoIsoC = "phoPhoIsoC";
  std::string s_EcalPFClIsoC = "phoEcalPFClIsoC";
  std::string s_HcalPFClIsoC = "phoHcalPFClIsoC";
  std::string s_TrkIsoC = "phoTrkIsoC";
  std::string s_sieie = "phosieie";
  std::string s_sipip = "phosipip";
  std::string s_sieip = "phosieip";
  std::string s_e2x2 = "phoe2x2";
  std::string s_e3x3 = "phoe3x3";  
  std::string s_e5x5 = "phoe5x5";
  std::string s_smaj = "phosmaj";
  std::string s_smin = "phosmin";
  std::string s_alpha = "phoalpha";
  
  std::string s_seed = "phoseed";
  std::string s_recHits = "phorecHits";
  std::string s_kurecHits = "phokurecHits";

  std::string s_suisseX = "phosuisseX";
  std::string s_isOOT = "phoisOOT";
  std::string s_isEB = "phoisEB";
  std::string s_isHLT = "phoisHLT";
  std::string s_isTrk = "phoisTrk";
  std::string s_passEleVeto = "phopassEleVeto";
  std::string s_hasPixSeed = "phohasPixSeed";
  std::string s_gedID = "phogedID";
  std::string s_ootID = "phoootID";
  std::string s_seedX = "phoseedX";
  std::string s_seedY = "phoseedY";
  std::string s_seedZ = "phoseedZ";
  std::string s_seedE = "phoseedE";
  std::string s_seedtime = "phoseedtime";
  std::string s_seedtimeErr = "phoseedtimeErr";
  std::string s_seedTOF = "phoseedTOF";
  std::string s_seedID = "phoseedID";
  std::string s_seedisGS6 = "phoseedisGS6";
  std::string s_seedisGS1 = "phoseedisGS1";
  std::string s_seedadcToGeV = "phoseedadcToGeV";
  std::string s_seedped12 = "phoseedped12";
  std::string s_seedped6 = "phoseedped6";
  std::string s_seedped1 = "phoseedped1";
  std::string s_seedpedrms12 = "phoseedpedrms12";
  std::string s_seedpedrms6 = "phoseedpedrms6";
  std::string s_seedpedrms1 = "phoseedpedrms1";

  std::string s_seedootA0 = "phoseedootA0";
  std::string s_seedootA1 = "phoseedootA1";
  std::string s_seedootA2 = "phoseedootA2";
  std::string s_seedootA3 = "phoseedootA3";
  std::string s_seedootA4 = "phoseedootA4";
  std::string s_seedootA5 = "phoseedootA5";
  std::string s_seedootA6 = "phoseedootA6";
  std::string s_seedootA7 = "phoseedootA7";
  std::string s_seedootA8 = "phoseedootA8"; 
  std::string s_seedootA9 = "phoseedootA9";
  std::string s_seedootMax = "phoseedootMax";
  std::string s_seedootMbefore = "phoseedootMbefore";
  std::string s_seedootMafter = "phoseedootMafter";
  std::string s_seedootSign = "phoseedootSign";
  std::string s_seedootVsum = "phoseedootVsum";

  std::string s_isGen = "phoisGen";
  std::string s_isSignal = "phoisSignal";
  std::string s_scaleAbs = "phoscaleAbs";
  std::string s_smearAbs = "phosmearAbs";
  std::string s_seedTT = "phoseedTT";
  std::string s_nrechits = "phonrechits";
  std::string s_nrechitsLT120 = "phonrechitsLT120";
  std::string s_meantime = "phomeantime";
  std::string s_meantimeLT120 = "phomeantimeLT120";
  std::string s_weightedtime = "phoweightedtime";
  std::string s_weightedtimeLT120 = "phoweightedtimeLT120";
  std::string s_weightedtimeTOF = "phoweightedtimeTOF";
  std::string s_weightedtimeLT120TOF = "phoweightedtimeLT120TOF";

  //std::string s_seedkuX = "phoseedkuX";
  //std::string s_seedkuY = "phoseedkuY";
  //std::string s_seedkuZ = "phoseedkuZ";
  std::string s_seedkuE = "phoseedkuE";
  std::string s_seedkutime = "phoseedkutime";
  std::string s_seedkutimeErr = "phoseedkutimeErr";
  std::string s_seedkuTOF = "phoseedkuTOF";
  std::string s_seedkuID = "phoseedkuID";
  //std::string s_seedkuisGS6 = "phoseedkuisGS6";
  //std::string s_seedkuisGS1 = "phoseedkuisGS1";
  //std::string s_seedkuadcToGeV = "phoseedkuadcToGeV";
  //std::string s_seedkuped12 = "phoseedkuped12";
  //std::string s_seedkuped6 = "phoseedkuped6";
  //std::string s_seedkuped1 = "phoseedkuped1";
  //std::string s_seedkupedrms12 = "phoseedkupedrms12";
  //std::string s_seedkupedrms6 = "phoseedkupedrms6";
  //std::string s_seedkupedrms1 = "phoseedkupedrms1";

  //std::string s_seedkuStcX = "phoseedkuStcX";
  //std::string s_seedkuStcY = "phoseedkuStcY";
  //std::string s_seedkuStcZ = "phoseedkuStcZ";
  std::string s_seedkuStcE = "phoseedkuStcE";
  std::string s_seedkuStctime = "phoseedkuStctime";
  std::string s_seedkuStctimeErr = "phoseedkuStctimeErr";
  std::string s_seedkuStcTOF = "phoseedkuStcTOF";
  std::string s_seedkuStcID = "phoseedkuStcID";
  //std::string s_seedkuStcisGS6 = "phoseedkuStcisGS6";
  //std::string s_seedkuStcisGS1 = "phoseedkuStcisGS1";
  //std::string s_seedkuStcadcToGeV = "phoseedkuStcadcToGeV";
  //std::string s_seedkuStcped12 = "phoseedkuStcped12";
  //std::string s_seedkuStcped6 = "phoseedkuStcped6";
  //std::string s_seedkuStcped1 = "phoseedkuStcped1";
  //std::string s_seedkuStcpedrms12 = "phoseedkuStcpedrms12";
  //std::string s_seedkuStcpedrms6 = "phoseedkuStcpedrms6";
  //std::string s_seedkuStcpedrms1 = "phoseedkuStcpedrms1";

  //std::string s_seedkuNotX = "phoseedkuNotX";
  //std::string s_seedkuNotY = "phoseedkuNotY";
  //std::string s_seedkuNotZ = "phoseedkuNotZ";
  std::string s_seedkuNotE = "phoseedkuNotE";
  std::string s_seedkuNottime = "phoseedkuNottime";
  std::string s_seedkuNottimeErr = "phoseedkuNottimeErr";
  std::string s_seedkuNotTOF = "phoseedkuNotTOF";
  std::string s_seedkuNotID = "phoseedkuNotID";
  //std::string s_seedkuNotisGS6 = "phoseedkuNotisGS6";
  //std::string s_seedkuNotisGS1 = "phoseedkuNotisGS1";
  //std::string s_seedkuNotadcToGeV = "phoseedkuNotadcToGeV";
  //std::string s_seedkuNotped12 = "phoseedkuNotped12";
  //std::string s_seedkuNotped6 = "phoseedkuNotped6";
  //std::string s_seedkuNotped1 = "phoseedkuNotped1";
  //std::string s_seedkuNotpedrms12 = "phoseedkuNotpedrms12";
  //std::string s_seedkuNotpedrms6 = "phoseedkuNotpedrms6";
  //std::string s_seedkuNotpedrms1 = "phoseedkuNotpedrms1";

  //std::string s_seedkuNotStcX = "phoseedkuNotStcX";
  //std::string s_seedkuNotStcY = "phoseedkuNotStcY";
  //std::string s_seedkuNotStcZ = "phoseedkuNotStcZ";
  std::string s_seedkuNotStcE = "phoseedkuNotStcE";
  std::string s_seedkuNotStctime = "phoseedkuNotStctime";
  std::string s_seedkuNotStctimeErr = "phoseedkuNotStctimeErr";
  std::string s_seedkuNotStcTOF = "phoseedkuNotStcTOF";
  std::string s_seedkuNotStcID = "phoseedkuNotStcID";
  //std::string s_seedkuNotStcisGS6 = "phoseedkuNotStcisGS6";
  //std::string s_seedkuNotStcisGS1 = "phoseedkuNotStcisGS1";
  //std::string s_seedkuNotStcadcToGeV = "phoseedkuNotStcadcToGeV";
  //std::string s_seedkuNotStcped12 = "phoseedkuNotStcped12";
  //std::string s_seedkuNotStcped6 = "phoseedkuNotStcped6";
  //std::string s_seedkuNotStcped1 = "phoseedkuNotStcped1";
  //std::string s_seedkuNotStcpedrms12 = "phoseedkuNotStcpedrms12";
  //std::string s_seedkuNotStcpedrms6 = "phoseedkuNotStcpedrms6";
  //std::string s_seedkuNotStcpedrms1 = "phoseedkuNotStcpedrms1";


  // tbranches
  TBranch * b_E;
  TBranch * b_pt;
  TBranch * b_eta;
  TBranch * b_phi;
  TBranch * b_scE;
  TBranch * b_sceta;
  TBranch * b_scphi;
  TBranch * b_HoE;
  TBranch * b_r9;
  TBranch * b_tdz;
  TBranch * b_ChgHadIso;
  TBranch * b_NeuHadIso;
  TBranch * b_PhoIso;
  TBranch * b_EcalPFClIso;
  TBranch * b_HcalPFClIso;
  TBranch * b_TrkIso;
  TBranch * b_ChgHadIsoC;
  TBranch * b_NeuHadIsoC;
  TBranch * b_PhoIsoC;
  TBranch * b_EcalPFClIsoC;
  TBranch * b_HcalPFClIsoC;
  TBranch * b_TrkIsoC;
  TBranch * b_sieie;
  TBranch * b_sipip;
  TBranch * b_sieip;
  TBranch * b_e2x2;
  TBranch * b_e3x3;
  TBranch * b_e5x5;
  TBranch * b_smaj;
  TBranch * b_smin;
  TBranch * b_alpha;
  TBranch * b_seed;
  TBranch * b_recHits;
  TBranch * b_kurecHits;
  TBranch * b_suisseX;
  TBranch * b_isOOT;
  TBranch * b_isEB;
  TBranch * b_isHLT;
  TBranch * b_isTrk;
  TBranch * b_passEleVeto;
  TBranch * b_hasPixSeed;
  TBranch * b_gedID;
  TBranch * b_ootID;

  TBranch * b_seedX;
  TBranch * b_seedY;
  TBranch * b_seedZ;
  TBranch * b_seedE;
  TBranch * b_seedtime;
  TBranch * b_seedtimeErr;
  TBranch * b_seedTOF;
  TBranch * b_seedID;
  TBranch * b_seedisGS6;
  TBranch * b_seedisGS1;
  TBranch * b_seedadcToGeV;
  TBranch * b_seedped12;
  TBranch * b_seedped6;
  TBranch * b_seedped1;
  TBranch * b_seedpedrms12;
  TBranch * b_seedpedrms6;
  TBranch * b_seedpedrms1;

  TBranch * b_seedootA0;
  TBranch * b_seedootA1;
  TBranch * b_seedootA2;
  TBranch * b_seedootA3;
  TBranch * b_seedootA4;
  TBranch * b_seedootA5;
  TBranch * b_seedootA6;
  TBranch * b_seedootA7;
  TBranch * b_seedootA8;
  TBranch * b_seedootA9;
  TBranch * b_seedootMax;
  TBranch * b_seedootMbefore;
  TBranch * b_seedootMafter;
  TBranch * b_seedootSign;
  TBranch * b_seedootVsum;

  TBranch * b_isGen;
  TBranch * b_isSignal;
  TBranch * b_scaleAbs;
  TBranch * b_smearAbs;
  TBranch * b_seedTT;
  TBranch * b_nrechits;
  TBranch * b_nkurechits;
  TBranch * b_nrechitsLT120;
  TBranch * b_meantime;
  TBranch * b_meantimeLT120;
  TBranch * b_weightedtime;
  TBranch * b_weightedtimeLT120;
  TBranch * b_weightedtimeTOF;
  TBranch * b_weightedtimeLT120TOF;

  //TBranch * b_seedkuX;
  //TBranch * b_seedkuY;
  //TBranch * b_seedkuZ;
  TBranch * b_seedkuE;
  TBranch * b_seedkutime;
  TBranch * b_seedkutimeErr;
  TBranch * b_seedkuTOF;
  TBranch * b_seedkuID;
  //TBranch * b_seedkuisGS6;
  //TBranch * b_seedkuisGS1;
  //TBranch * b_seedkuadcToGeV;
  //TBranch * b_seedkuped12;
  //TBranch * b_seedkuped6;
  //TBranch * b_seedkuped1;
  //TBranch * b_seedkupedrms12;
  //TBranch * b_seedkupedrms6;
  //TBranch * b_seedkupedrms1;

  //TBranch * b_seedkuStcX;
  //TBranch * b_seedkuStcY;
  //TBranch * b_seedkuStcZ;
  TBranch * b_seedkuStcE;
  TBranch * b_seedkuStctime;
  TBranch * b_seedkuStctimeErr;
  TBranch * b_seedkuStcTOF;
  TBranch * b_seedkuStcID;
  //TBranch * b_seedkuStcisGS6;
  //TBranch * b_seedkuStcisGS1;
  //TBranch * b_seedkuStcadcToGeV;
  //TBranch * b_seedkuStcped12;
  //TBranch * b_seedkuStcped6;
  //TBranch * b_seedkuStcped1;
  //TBranch * b_seedkuStcpedrms12;
  //TBranch * b_seedkuStcpedrms6;
  //TBranch * b_seedkuStcpedrms1;

  //TBranch * b_seedkuNotX;
  //TBranch * b_seedkuNotY;
  //TBranch * b_seedkuNotZ;
  TBranch * b_seedkuNotE;
  TBranch * b_seedkuNottime;
  TBranch * b_seedkuNottimeErr;
  TBranch * b_seedkuNotTOF;
  TBranch * b_seedkuNotID;
  //TBranch * b_seedkuNotisGS6;
  //TBranch * b_seedkuNotisGS1;
  //TBranch * b_seedkuNotadcToGeV;
  //TBranch * b_seedkuNotped12;
  //TBranch * b_seedkuNotped6;
  //TBranch * b_seedkuNotped1;
  //TBranch * b_seedkuNotpedrms12;
  //TBranch * b_seedkuNotpedrms6;
  //TBranch * b_seedkuNotpedrms1;

  //TBranch * b_seedkuNotStcX;
  //TBranch * b_seedkuNotStcY;
  //TBranch * b_seedkuNotStcZ;
  TBranch * b_seedkuNotStcE;
  TBranch * b_seedkuNotStctime;
  TBranch * b_seedkuNotStctimeErr;
  TBranch * b_seedkuNotStcTOF;
  TBranch * b_seedkuNotStcID;
  //TBranch * b_seedkuNotStcisGS6;
  //TBranch * b_seedkuNotStcisGS1;
  //TBranch * b_seedkuNotStcadcToGeV;
  //TBranch * b_seedkuNotStcped12;
  //TBranch * b_seedkuNotStcped6;
  //TBranch * b_seedkuNotStcped1;
  //TBranch * b_seedkuNotStcpedrms12;
  //TBranch * b_seedkuNotStcpedrms6;
  //TBranch * b_seedkuNotStcpedrms1;

};
typedef std::vector<Pho> PhoVec;

struct Gmsb
{
  Float_t genNmass;
  Float_t genNE;
  Float_t genNpt;
  Float_t genNphi;
  Float_t genNeta;
  Float_t genNprodvx;
  Float_t genNprodvy;
  Float_t genNprodvz;
  Float_t genNdecayvx;
  Float_t genNdecayvy;
  Float_t genNdecayvz;
  Float_t genphE;
  Float_t genphpt;
  Float_t genphphi;
  Float_t genpheta;
  Int_t   genphmatch;
  Float_t gengrmass;
  Float_t gengrE;
  Float_t gengrpt;
  Float_t gengrphi;
  Float_t gengreta;

  std::string s_genNmass = "genNmass";
  std::string s_genNE = "genNE";
  std::string s_genNpt = "genNpt";
  std::string s_genNphi = "genNphi";
  std::string s_genNeta = "genNeta";
  std::string s_genNprodvx = "genNprodvx";
  std::string s_genNprodvy = "genNprodvy";
  std::string s_genNprodvz = "genNprodvz";
  std::string s_genNdecayvx = "genNdecayvx";
  std::string s_genNdecayvy = "genNdecayvy";
  std::string s_genNdecayvz = "genNdecayvz";
  std::string s_genphE = "genphE";
  std::string s_genphpt = "genphpt";
  std::string s_genphphi = "genphphi";
  std::string s_genpheta = "genpheta";
  std::string s_genphmatch = "genphmatch";
  std::string s_gengrmass = "gengrmass";
  std::string s_gengrE = "gengrE";
  std::string s_gengrpt = "gengrpt";
  std::string s_gengrphi = "gengrphi";
  std::string s_gengreta = "gengreta";

  TBranch * b_genNmass;
  TBranch * b_genNE;
  TBranch * b_genNpt;
  TBranch * b_genNphi;
  TBranch * b_genNeta;
  TBranch * b_genNprodvx;
  TBranch * b_genNprodvy;
  TBranch * b_genNprodvz;
  TBranch * b_genNdecayvx;
  TBranch * b_genNdecayvy;
  TBranch * b_genNdecayvz;
  TBranch * b_genphE;
  TBranch * b_genphpt;
  TBranch * b_genphphi;
  TBranch * b_genpheta;
  TBranch * b_genphmatch;
  TBranch * b_gengrmass;
  TBranch * b_gengrE;
  TBranch * b_gengrpt;
  TBranch * b_gengrphi;
  TBranch * b_gengreta;
};
typedef std::vector<Gmsb> GmsbVec;

struct Hvds
{
  Float_t genvPionmass;
  Float_t genvPionE;
  Float_t genvPionpt;
  Float_t genvPionphi;
  Float_t genvPioneta;
  Float_t genvPionprodvx;
  Float_t genvPionprodvy;
  Float_t genvPionprodvz;
  Float_t genvPiondecayvx;
  Float_t genvPiondecayvy;
  Float_t genvPiondecayvz;
  Float_t genHVph0E;
  Float_t genHVph0pt;
  Float_t genHVph0phi;
  Float_t genHVph0eta;
  Int_t   genHVph0match;
  Float_t genHVph1E;
  Float_t genHVph1pt;
  Float_t genHVph1phi;
  Float_t genHVph1eta;
  Int_t   genHVph1match;

  std::string s_genvPionmass = "genvPionmass";
  std::string s_genvPionE = "genvPionE";
  std::string s_genvPionpt = "genvPionpt";
  std::string s_genvPionphi = "genvPionphi";
  std::string s_genvPioneta = "genvPioneta";
  std::string s_genvPionprodvx = "genvPionprodvx";
  std::string s_genvPionprodvy = "genvPionprodvy";
  std::string s_genvPionprodvz = "genvPionprodvz";
  std::string s_genvPiondecayvx = "genvPiondecayvx";
  std::string s_genvPiondecayvy = "genvPiondecayvy";
  std::string s_genvPiondecayvz = "genvPiondecayvz";
  std::string s_genHVph0E = "genHVph0E";
  std::string s_genHVph0pt = "genHVph0pt";
  std::string s_genHVph0phi = "genHVph0phi";
  std::string s_genHVph0eta = "genHVph0eta";
  std::string s_genHVph0match = "genHVph0match";
  std::string s_genHVph1E = "genHVph1E";
  std::string s_genHVph1pt = "genHVph1pt";
  std::string s_genHVph1phi = "genHVph1phi";
  std::string s_genHVph1eta = "genHVph1eta";
  std::string s_genHVph1match = "genHVph1match";

  TBranch * b_genvPionmass;
  TBranch * b_genvPionE;
  TBranch * b_genvPionpt;
  TBranch * b_genvPionphi;
  TBranch * b_genvPioneta;
  TBranch * b_genvPionprodvx;
  TBranch * b_genvPionprodvy;
  TBranch * b_genvPionprodvz;
  TBranch * b_genvPiondecayvx;
  TBranch * b_genvPiondecayvy;
  TBranch * b_genvPiondecayvz;
  TBranch * b_genHVph0E;
  TBranch * b_genHVph0pt;
  TBranch * b_genHVph0phi;
  TBranch * b_genHVph0eta;
  TBranch * b_genHVph0match;
  TBranch * b_genHVph1E;
  TBranch * b_genHVph1pt;
  TBranch * b_genHVph1phi;
  TBranch * b_genHVph1eta;
  TBranch * b_genHVph1match;

};
typedef std::vector<Hvds> HvdsVec;

struct Toy
{
  Float_t genphE;
  Float_t genphpt;
  Float_t genphphi;
  Float_t genpheta;
  Int_t   genphmatch;
  Int_t   genphmatch_ptres;
  Int_t   genphmatch_status;

  std::string s_genphE = "genphE";
  std::string s_genphpt = "genphpt";
  std::string s_genphphi = "genphphi";
  std::string s_genpheta = "genpheta";
  std::string s_genphmatch = "genphmatch";
  std::string s_genphmatch_ptres = "genphmatch_ptres";
  std::string s_genphmatch_status = "genphmatch_status";

  TBranch * b_genphE;
  TBranch * b_genphpt;
  TBranch * b_genphphi;
  TBranch * b_genpheta;
  TBranch * b_genphmatch;
  TBranch * b_genphmatch_ptres;
  TBranch * b_genphmatch_status;
};
typedef std::vector<Toy> ToyVec;

#endif
