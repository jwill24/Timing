#ifndef __DisPho__
#define __DisPho__

// FWCore
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h" 

// HLT + Trigger info
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"

// Gen Info
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/JetReco/interface/GenJet.h"

// DataFormats
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"

// DetIds 
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"

// Ecal RecHits
#include "DataFormats/EcalRecHit/interface/EcalRecHit.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/EcalRecHit/interface/EcalUncalibratedRecHit.h"

// Ecal Digis
#include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"
#include "DataFormats/EcalDigi/interface/EcalTriggerPrimitiveDigi.h"
#include "DataFormats/EcalDigi/interface/EcalTimeDigi.h"
#include "DataFormats/EcalDigi/interface/EBSrFlag.h"
#include "DataFormats/EcalDigi/interface/EESrFlag.h"

// Supercluster info
#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "DataFormats/CaloRecHit/interface/CaloCluster.h"

// EGamma Tools
#include "RecoEcal/EgammaCoreTools/interface/EcalTools.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterTools.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"

// Geometry
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloSubdetectorGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"

// ECAL Record info (Laser Constants)
#include "CalibCalorimetry/EcalLaserCorrection/interface/EcalLaserDbService.h"
#include "CalibCalorimetry/EcalLaserCorrection/interface/EcalLaserDbRecord.h"

// ECAL Record info (Intercalibration Constants)
#include "CondFormats/EcalObjects/interface/EcalIntercalibConstants.h"
#include "CondFormats/DataRecord/interface/EcalIntercalibConstantsRcd.h"

// ECAL Record info (ADCToGeV)
#include "CondFormats/EcalObjects/interface/EcalADCToGeVConstant.h"
#include "CondFormats/DataRecord/interface/EcalADCToGeVConstantRcd.h"

// ECAL Record info (ADCToGeV)
#include "CondFormats/EcalObjects/interface/EcalADCToGeVConstant.h"
#include "CondFormats/DataRecord/interface/EcalADCToGeVConstantRcd.h"

// ECAL Record info (Pedestals)
#include "CondFormats/EcalObjects/interface/EcalPedestals.h"
#include "CondFormats/DataRecord/interface/EcalPedestalsRcd.h"

// JECS
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

// JERs
#include "CondFormats/JetMETObjects/interface/JetResolutionObject.h"
#include "JetMETCorrections/Modules/interface/JetResolution.h"

// LHC Info
#include "CondFormats/RunInfo/interface/LHCInfo.h"
#include "CondFormats/DataRecord/interface/LHCInfoRcd.h"
#include "CondTools/RunInfo/interface/LHCInfoPopConSourceHandler.h"

// ROOT
#include "TH1F.h"
#include "TTree.h"
#include "Math/PositionVector3D.h"

// Common Utilities
#include "Timing/TimingAnalyzer/plugins/CommonUtils.hh"

// Unique structs
#include "Timing/TimingAnalyzer/plugins/DisPhoTypes.hh"

#define BUNCHES 3564
#define SAMPLES 10

using namespace std;
using namespace edm;

////////////////////
// Unique typedef //
////////////////////

typedef ROOT::Math::PositionVector3D<ROOT::Math::Cartesian3D<float>,ROOT::Math::DefaultCoordinateSystemTag> Point3D;

//////////////////////
// Class Definition //
//////////////////////

class DisPho : public edm::one::EDAnalyzer<edm::one::SharedResources,edm::one::WatchRuns> 
{
public:

  ////////////////////////
  // Internal Functions //
  ////////////////////////

  explicit DisPho(const edm::ParameterSet & iConfig);
  void ConsumeTokens();
  ~DisPho();
  static void fillDescriptions(edm::ConfigurationDescriptions & descriptions);  

  /////////////////////////////
  // Analyzer Prep Functions //
  /////////////////////////////

  void MakeHists();
  void MakeAndFillConfigTree();
  void MakeEventTree();

  ///////////////////////////
  // Object Prep Functions //
  ///////////////////////////

  bool GetObjects(const edm::Event & iEvent, const edm::EventSetup & iSetup);
  bool GetLHCInfo(const edm::Event & iEvent, const edm::EventSetup & iSetup);
  bool GetStandardObjects(const edm::Event & iEvent);
  bool GetCalibrationConstants(const  edm::EventSetup & iSetup);
  bool GetMCObjects(const edm::Event & iEvent);
  void InitializeObjects(const edm::Event & iEvent);
  //void InitializeLHCInfo();
  
  void GetWeights();
  void InitializeGenPUBranches();
  void SetGenPUBranches();
  void AlwaysFillHists();

  void PrepObjects(const edm::Event & iEvent);

  ////////////////////////////////
  // Blinding and Pre-Selection //
  ////////////////////////////////

  inline bool ApplyBlindSF();
  void FillBlindSF();

  inline bool ApplyBlindMET();
  void FillBlindMET();

  bool ApplyPreSelectionTrigger();
  void FillPreSelectionTrigger();

  bool ApplyPreSelectionHT();
  void FillPreSelectionHT();

  bool ApplyPreSelectionGoodPhoton();
  void FillPreSelectionGoodPhoton();

  //////////////////////////////////////
  // Fill Tree from Objects Functions //
  //////////////////////////////////////

  void FillTreeFromObjects(const edm::Event & iEvent);

  void SetMCInfo();
  void InitializeGenPointBranches();
  void SetGenT0Branches();
  void SetGenXYZ0Branches();
  void InitializeGMSBBranches();
  void SetGMSBBranches();
  void InitializeHVDSBranches();
  void SetHVDSBranches();
  void InitializeToyBranches();
  void SetToyBranches();

  void SetRecordInfo(const edm::Event & iEvent);
  void SetTriggerBranches();
  void SetMETFilterBranches();

  void InitializePVBranches();
  void SetPVBranches();

  void InitializeMETBranches();
  void SetMETBranches();
  void InitializeMETBranchesMC();
  void SetMETBranchesMC();

  void InitializeJetBranches();
  void SetJetBranches();
  void InitializeJetBranchesMC();
  void SetJetBranchesMC();
  int GenJetMatcher(const pat::Jet & jet, const edm::Handle<std::vector<reco::GenJet> > & genJetsH, const float jer);
  void GetStochasticSmear(std::mt19937 & mt_rand, const float jer, const float jer_sf, float & jet_smear);
  void CheckJetSmear(const float energy, float & jet_smear);
  
  void InitializeElectronBranches();
  void SetElectronBranches();
  void InitializeMuonBranches();
  void SetMuonBranches();

  void InitializeRecHitBranches();
  void SetRecHitBranches();
  void SetRecHitBranches(const EcalRecHitCollection * recHits, const CaloSubdetectorGeometry * geometry, const float adcToGeV);
  void SetKuRecHitBranches(const EcalRecHitCollection * recHits, const CaloSubdetectorGeometry * geometry, const float adcToGeV);
  void SetURecHitBranches(const EcalUncalibratedRecHitCollection * recHits, const CaloSubdetectorGeometry * geometry);

  void InitializeDigiBranches();
  void SetDigiBranches();
  void SetDigiBranches(const EBDigiCollection * ebDigis, const EEDigiCollection * eeDigis, const CaloSubdetectorGeometry * geometry);

  void InitializePhoBranches();
  void SetPhoBranches();
  void InitializePhoBranchesMC();
  void SetPhoBranchesMC();
  int  CheckMatchHVDS(const int iphoton, const hvdsStruct & hvdsBranch);

private:

  ////////////////////////
  // Internal Functions //
  ////////////////////////

  virtual void beginJob() override;
  virtual void analyze(const edm::Event & iEvent, const edm::EventSetup & iSetup) override;
  virtual void endJob() override;
  
  virtual void beginRun(const edm::Run & iRun, const edm::EventSetup & iSetup) override;
  virtual void endRun(const edm::Run & iRun, const edm::EventSetup & iSetup) override;

  ///////////////////
  // Input Members //
  ///////////////////
 
  // Collection Flags
  const bool rawCollectionsValid;
  const bool kuRechitValid;

  // LHC info  
  std::vector<unsigned int> train_zero, train_notzero, long_train_notzero, subtrain_num, train_num;
  unsigned int subtrain_position, train_position, subtrain_number, train_number;
  unsigned int fBunchNum, fBX, fXangle;
  float fBeam1VC[BUNCHES], fBeam2VC[BUNCHES], fBeam1RF[BUNCHES], fBeam2RF[BUNCHES];
  float beam1_VC, beam2_VC, beam1_RF, beam2_RF;
  const bool lhcInfoValid;
  
  // blinding
  const unsigned int blindSF;
  const bool applyBlindSF;
  const float blindMET;
  const bool applyBlindMET;

  // object prep
  const float jetpTmin;
  const float jetEtamax;
  const int jetIDmin;
  const float rhEmin;
  const float phpTmin;
  const std::string phIDmin;

  // object extra pruning
  const float seedTimemin;
  const int nPhosmax;

  // photon storing options
  const bool splitPho;
  const bool onlyGED;
  const bool onlyOOT;

  // lepton prep cuts
  const float ellowpTmin;
  const float elhighpTmin;
  const float mulowpTmin;
  const float muhighpTmin;

  // rechit storing options
  const bool storeRecHits;

  // pre-selection vars
  const bool applyTrigger;
  const float minHT;
  const bool applyHT;
  const float phgoodpTmin;
  const std::string phgoodIDmin;
  const bool applyPhGood;

  // dR matching criteria
  const float dRmin;
  const float pTres;
  const float gendRmin;
  const float genpTres;
  const float trackdRmin;
  const float trackpTmin;
  const float genjetdRmin;
  const float genjetpTfactor;
  const float leptondRmin;

  // JER extra info
  const float smearjetEmin;

  // trigger inputs
  const std::string inputPaths;
  std::vector<std::string> pathNames;
  strBitMap triggerBitMap;
  const std::string inputFilters;
  std::vector<std::string> filterNames;

  // trigger results
  const edm::InputTag triggerResultsTag;
  edm::EDGetTokenT<edm::TriggerResults> triggerResultsToken;
  edm::Handle<edm::TriggerResults> triggerResultsH;

  // trigger objects
  const edm::InputTag triggerObjectsTag;
  edm::EDGetTokenT<std::vector<pat::TriggerObjectStandAlone> > triggerObjectsToken;
  edm::Handle<std::vector<pat::TriggerObjectStandAlone> > triggerObjectsH;

  // output triggers
  std::map<std::string,std::vector<pat::TriggerObjectStandAlone> > triggerObjectsByFilterMap; // first index is filter label, second is trigger objects

  // met filter inputs
  const std::string inputFlags;
  std::vector<std::string> flagNames;
  strBitMap triggerFlagMap;

  // met filters
  const edm::InputTag triggerFlagsTag;
  edm::EDGetTokenT<edm::TriggerResults> triggerFlagsToken;
  edm::Handle<edm::TriggerResults> triggerFlagsH;

  const edm::InputTag ecalBadCalibFlagTag;
  edm::EDGetTokenT<bool> ecalBadCalibFlagToken;
  edm::Handle<bool> ecalBadCalibFlagH;

  // Tracks
  const edm::InputTag tracksTag;
  edm::EDGetTokenT<std::vector<reco::Track> > tracksToken;
  edm::Handle<std::vector<reco::Track> > tracksH;

  // vertices
  const edm::InputTag verticesTag;
  edm::EDGetTokenT<std::vector<reco::Vertex> > verticesToken;
  edm::Handle<std::vector<reco::Vertex> > verticesH;

  // rho
  const edm::InputTag rhoTag;
  edm::EDGetTokenT<double> rhoToken;
  edm::Handle<double> rhoH;
  float rho;

  // mets
  const edm::InputTag metsTag;
  edm::EDGetTokenT<std::vector<pat::MET> > metsToken;
  edm::Handle<std::vector<pat::MET> > metsH;

  // output MET
  pat::MET t1pfMET;

  // jets
  const edm::InputTag jetsTag;
  edm::EDGetTokenT<std::vector<pat::Jet> > jetsToken;
  edm::Handle<std::vector<pat::Jet> > jetsH;
  std::vector<pat::Jet> jets;

  // electrons
  const edm::InputTag electronsTag;
  edm::EDGetTokenT<std::vector<pat::Electron> > electronsToken;
  edm::Handle<std::vector<pat::Electron> > electronsH;
  std::vector<pat::Electron> electrons;
  
  // muons
  const edm::InputTag muonsTag;
  edm::EDGetTokenT<std::vector<pat::Muon> > muonsToken;
  edm::Handle<std::vector<pat::Muon> > muonsH;
  std::vector<pat::Muon> muons;
  
  // RecHits EB
  const edm::InputTag recHitsEBTag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > recHitsEBToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > recHitsEBH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * recHitsEB;

  // RecHits EE
  const edm::InputTag recHitsEETag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > recHitsEEToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > recHitsEEH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * recHitsEE;

  // KU Ks RecHits EB
  const edm::InputTag kuKsRecHitsEBTag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuKsRecHitsEBToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuKsRecHitsEBH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuKsRecHitsEB;

  // KU Ks RuecHits EE
  const edm::InputTag kuKsRecHitsEETag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuKsRecHitsEEToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuKsRecHitsEEH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuKsRecHitsEE;

  // KU KsStc RecHits EB
  const edm::InputTag kuKsStcRecHitsEBTag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuKsStcRecHitsEBToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuKsStcRecHitsEBH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuKsStcRecHitsEB;

  // KU KsStc RuecHits EE
  const edm::InputTag kuKsStcRecHitsEETag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuKsStcRecHitsEEToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuKsStcRecHitsEEH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuKsStcRecHitsEE;

  // KU Wei RecHits EB
  const edm::InputTag kuWeiRecHitsEBTag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWeiRecHitsEBToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWeiRecHitsEBH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuWeiRecHitsEB;

  // KU Wei RuecHits EE
  const edm::InputTag kuWeiRecHitsEETag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWeiRecHitsEEToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWeiRecHitsEEH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuWeiRecHitsEE;

  // KU WeiStc RecHits EB
  const edm::InputTag kuWeiStcRecHitsEBTag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWeiStcRecHitsEBToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWeiStcRecHitsEBH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuWeiStcRecHitsEB;

  // KU WeiStc RuecHits EE
  const edm::InputTag kuWeiStcRecHitsEETag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWeiStcRecHitsEEToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWeiStcRecHitsEEH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuWeiStcRecHitsEE;

  // KU WeiNot RecHits EB
  const edm::InputTag kuWeiNotRecHitsEBTag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWeiNotRecHitsEBToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWeiNotRecHitsEBH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuWeiNotRecHitsEB;

  // KU WeiNot RuecHits EE
  const edm::InputTag kuWeiNotRecHitsEETag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWeiNotRecHitsEEToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWeiNotRecHitsEEH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuWeiNotRecHitsEE;

  // KU WeiNotStc RecHits EB
  const edm::InputTag kuWeiNotStcRecHitsEBTag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWeiNotStcRecHitsEBToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWeiNotStcRecHitsEBH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuWeiNotStcRecHitsEB;

  // KU WeiNotStc RuecHits EE
  const edm::InputTag kuWeiNotStcRecHitsEETag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWeiNotStcRecHitsEEToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWeiNotStcRecHitsEEH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuWeiNotStcRecHitsEE;

  // EB Uncalibrated RecHits
  const edm::InputTag uncalibratedRecHitsEBTag;
  edm::EDGetTokenT<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > uncalibratedRecHitsEBToken;
  edm::Handle<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > uncalibratedRecHitsEBH;
  const edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > * uncalibratedRecHitsEB;

  // EE Uncalibrated RecHits
  const edm::InputTag uncalibratedRecHitsEETag;
  edm::EDGetTokenT<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > uncalibratedRecHitsEEToken;
  edm::Handle<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > uncalibratedRecHitsEEH;
  const edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > * uncalibratedRecHitsEE;

  // EB Uncalibrated kuKs RecHits
  const edm::InputTag kuKs_uncalibratedRecHitsEBTag;
  edm::EDGetTokenT<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > kuKs_uncalibratedRecHitsEBToken;
  edm::Handle<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > kuKs_uncalibratedRecHitsEBH;
  const edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > * kuKs_uncalibratedRecHitsEB;

  // EE Uncalibrated kuKs RecHits
  const edm::InputTag kuKs_uncalibratedRecHitsEETag;
  edm::EDGetTokenT<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > kuKs_uncalibratedRecHitsEEToken;
  edm::Handle<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > kuKs_uncalibratedRecHitsEEH;
  const edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > * kuKs_uncalibratedRecHitsEE;

  // EB Uncalibrated kuWei RecHits
  const edm::InputTag kuWei_uncalibratedRecHitsEBTag;
  edm::EDGetTokenT<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > kuWei_uncalibratedRecHitsEBToken;
  edm::Handle<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > kuWei_uncalibratedRecHitsEBH;
  const edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > * kuWei_uncalibratedRecHitsEB;

  // EE Uncalibrated kuWei RecHits
  const edm::InputTag kuWei_uncalibratedRecHitsEETag;
  edm::EDGetTokenT<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > kuWei_uncalibratedRecHitsEEToken;
  edm::Handle<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > kuWei_uncalibratedRecHitsEEH;
  const edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > * kuWei_uncalibratedRecHitsEE;

  // EB Uncalibrated kuWeiNot RecHits
  const edm::InputTag kuWeiNot_uncalibratedRecHitsEBTag;
  edm::EDGetTokenT<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > kuWeiNot_uncalibratedRecHitsEBToken;
  edm::Handle<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > kuWeiNot_uncalibratedRecHitsEBH;
  const edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > * kuWeiNot_uncalibratedRecHitsEB;

  // EE Uncalibrated kuWeiNot RecHits
  const edm::InputTag kuWeiNot_uncalibratedRecHitsEETag;
  edm::EDGetTokenT<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > kuWeiNot_uncalibratedRecHitsEEToken;
  edm::Handle<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > kuWeiNot_uncalibratedRecHitsEEH;
  const edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > * kuWeiNot_uncalibratedRecHitsEE;

  // EB Digis test
  const edm::InputTag ecalDigisEBTag;
  edm::EDGetTokenT<EBDigiCollection> ebDigiCollectionToken_;
  edm::Handle<EBDigiCollection> pEBDigis;
  const EBDigiCollection * EBdigiCollection;

  // EE Digis test
  const edm::InputTag ecalDigisEETag;
  edm::EDGetTokenT<EEDigiCollection> eeDigiCollectionToken_;
  edm::Handle<EEDigiCollection> pEEDigis;
  const EEDigiCollection * EEdigiCollection;

  // Output rechit map
  uiiumap recHitMap;
  uiiumap kuRecHitMap;
  uiiumap uncalibratedRecHitMap;

  // Output digi map
  uiiumap digiMap;

  // gedPhotons
  const edm::InputTag gedPhotonsTag;
  edm::EDGetTokenT<std::vector<pat::Photon> > gedPhotonsToken;
  edm::Handle<std::vector<pat::Photon> > gedPhotonsH;

  // ootPhotons
  const edm::InputTag ootPhotonsTag;
  edm::EDGetTokenT<std::vector<pat::Photon> > ootPhotonsToken;
  edm::Handle<std::vector<pat::Photon> > ootPhotonsH;

  // output photons
  std::vector<pat::Photon> photons;

  // geometry
  edm::ESHandle<CaloGeometry> caloGeoH;
  const CaloSubdetectorGeometry * barrelGeometry;
  const CaloSubdetectorGeometry * endcapGeometry;

  // lasers
  edm::ESHandle<EcalLaserDbService> laserH;
  edm::Timestamp evTime;

  // inter calibration
  edm::ESHandle<EcalIntercalibConstants> interCalibH;
  const EcalIntercalibConstantMap *      interCalibMap;

  // ADCToGeV
  edm::ESHandle<EcalADCToGeVConstant> adcToGeVH;
  float adcToGeVEB;
  float adcToGeVEE;

  // pedestals
  edm::ESHandle<EcalPedestals> pedestalsH;

  // JECs
  edm::ESHandle<JetCorrectorParametersCollection> jetCorrH;
  
  // JERs
  JME::JetResolution jetRes;
  JME::JetResolutionScaleFactor jetRes_sf; 

  // Gen config and MC info
  const bool isGMSB;
  const bool isHVDS;
  const bool isBkgd;
  const bool isToy;
  const bool isADD;
  const float xsec;
  const float filterEff;
  const float BR;
  bool isMC;

  // genEvtInfo
  const edm::InputTag genEvtInfoTag;
  edm::EDGetTokenT<GenEventInfoProduct> genEvtInfoToken;
  edm::Handle<GenEventInfoProduct> genEvtInfoH;

  // gen time
  const edm::InputTag gent0Tag;
  edm::EDGetTokenT<float> gent0Token;
  edm::Handle<float> gent0H;
  
  // gen vertex
  const edm::InputTag genxyz0Tag;
  edm::EDGetTokenT<Point3D> genxyz0Token;
  edm::Handle<Point3D> genxyz0H;
  
  // pileups
  const edm::InputTag pileupInfosTag;
  edm::EDGetTokenT<std::vector<PileupSummaryInfo> > pileupInfosToken;
  edm::Handle<std::vector<PileupSummaryInfo> > pileupInfosH;
  
  // genParticles
  const edm::InputTag genParticlesTag;
  edm::EDGetTokenT<std::vector<reco::GenParticle> > genParticlesToken;
  edm::Handle<std::vector<reco::GenParticle> > genParticlesH;

  // genJets
  const edm::InputTag genJetsTag;
  edm::EDGetTokenT<std::vector<reco::GenJet> > genJetsToken;
  edm::Handle<std::vector<reco::GenJet> > genJetsH;

  // output gen particles
  std::vector<reco::GenParticle> neutralinos;
  std::vector<reco::GenParticle> vPions;
  std::vector<reco::GenParticle> toys;

  ///////////////////////////
  // Temp Internal Members //
  ///////////////////////////

  float wgt;
  int nJets, nRecHits, nKuRecHits, nURecHits, nDigis, nPhotons;

  ////////////////////
  // Output Members //
  ////////////////////

  // output histograms
  TH1F * h_cutflow;
  TH1F * h_cutflow_wgt;
  std::map<std::string,int> cutflowLabelMap;
  TH1F * h_genpuobs;
  TH1F * h_genpuobs_wgt;
  TH1F * h_genputrue;
  TH1F * h_genputrue_wgt;

  // output metadeta configs
  TTree * configtree;

  // output event level ntuple
  TTree * disphotree;
 
  // MC info
  float genwgt;
  float gent0,genx0,geny0,genz0;
  int genpuobs, genputrue;

  // gmsb
  int nNeutoPhGr;
  std::vector<gmsbStruct> gmsbBranches;

  // hvds
  int nvPions;
  std::vector<hvdsStruct> hvdsBranches;

  // toyMC
  int nToyPhs;
  std::vector<toyStruct> toyBranches;

  // event info
  unsigned long int event; // technically unsigned long long in Event.h...
  unsigned int run, lumi;  

  // trigger info
  bool hltSignal;
  bool hltRefPhoID;
  bool hltRefDispID;
  bool hltRefHT;
  bool hltPho50;
  bool hltPho200;
  bool hltDiPho70;
  bool hltDiPho3022M90;
  bool hltDiPho30PV18PV;
  bool hltEle32WPT;
  bool hltDiEle33MW;
  bool hltJet500;

  // met filter info
  bool metPV;
  bool metBeamHalo;
  bool metHBHENoise;
  bool metHBHEisoNoise;
  bool metECALTP;
  bool metPFMuon;
  bool metPFChgHad;
  bool metEESC;
  bool metECALCalib;
  bool metECALBadCalib;

  // vertices
  int nvtx;
  float vtxX, vtxY, vtxZ;

  // Type-1 PF MET
  float t1pfMETpt, t1pfMETphi, t1pfMETsumEt;

  // GEN MET
  float genMETpt, genMETphi;

  // jets
  int njets;
  std::vector<float> jetE, jetpt, jetphi, jeteta;
  std::vector<int>   jetID;
  std::vector<float> jetNHF, jetNEMF, jetCHF, jetCEMF, jetMUF, jetNHM, jetCHM;

  std::vector<float> jetscaleRel, jetsmearSF, jetsmearDownSF, jetsmearUpSF;
  std::vector<int>   jetisGen;

  // electrons
  int nelLowL, nelLowM, nelLowT, nelHighL, nelHighM, nelHighT;

  // muons
  int nmuLowL, nmuLowM, nmuLowT, nmuHighL, nmuHighM, nmuHighT;

  // RecHits
  int nrechits;
  std::vector<float> rhX, rhY, rhZ, rhE, rhtime, rhtimeErr, rhTOF;
  std::vector<unsigned int> rhID;
  std::vector<bool> rhisOOT, rhisGS6, rhisGS1;
  std::vector<float> rhadcToGeV;
  std::vector<float> rhped12, rhped6, rhped1;
  std::vector<float> rhpedrms12, rhpedrms6, rhpedrms1;

  // kuKsRecHits
  int nkurechits;
  std::vector<float> kurhX, kurhY, kurhZ, kurhE, kurhtime, kurhtimeErr, kurhTOF;
  std::vector<unsigned int> kurhID;
  std::vector<bool> kurhisOOT, kurhisGS6, kurhisGS1;
  std::vector<float> kurhadcToGeV;
  std::vector<float> kurhped12, kurhped6, kurhped1;
  std::vector<float> kurhpedrms12, kurhpedrms6, kurhpedrms1;

  // kuKsStcRecHits
  int nkuKsStcrechits;
  std::vector<float> kuKsStcrhX, kuKsStcrhY, kuKsStcrhZ, kuKsStcrhE, kuKsStcrhtime, kuKsStcrhtimeErr, kuKsStcrhTOF;
  std::vector<unsigned int> kuKsStcrhID;
  std::vector<bool> kuKsStcrhisOOT, kuKsStcrhisGS6, kuKsStcrhisGS1;
  std::vector<float> kuKsStcrhadcToGeV;
  std::vector<float> kuKsStcrhped12, kuKsStcrhped6, kuKsStcrhped1;
  std::vector<float> kuKsStcrhpedrms12, kuKsStcrhpedrms6, kuKsStcrhpedrms1;

  // kuWeiRecHits
  int nkuWeirechits;
  std::vector<float> kuWeirhX, kuWeirhY, kuWeirhZ, kuWeirhE, kuWeirhtime, kuWeirhtimeErr, kuWeirhTOF;
  std::vector<unsigned int> kuWeirhID;
  std::vector<bool> kuWeirhisOOT, kuWeirhisGS6, kuWeirhisGS1;
  std::vector<float> kuWeirhadcToGeV;
  std::vector<float> kuWeirhped12, kuWeirhped6, kuWeirhped1;
  std::vector<float> kuWeirhpedrms12, kuWeirhpedrms6, kuWeirhpedrms1;

  // kuWeiStcRecHits
  int nkuWeiStcrechits;
  std::vector<float> kuWeiStcrhX, kuWeiStcrhY, kuWeiStcrhZ, kuWeiStcrhE, kuWeiStcrhtime, kuWeiStcrhtimeErr, kuWeiStcrhTOF;
  std::vector<unsigned int> kuWeiStcrhID;
  std::vector<bool> kuWeiStcrhisOOT, kuWeiStcrhisGS6, kuWeiStcrhisGS1;
  std::vector<float> kuWeiStcrhadcToGeV;
  std::vector<float> kuWeiStcrhped12, kuWeiStcrhped6, kuWeiStcrhped1;
  std::vector<float> kuWeiStcrhpedrms12, kuWeiStcrhpedrms6, kuWeiStcrhpedrms1;

  // kuWeiNotRecHits
  int nkuWeiNotrechits;
  std::vector<float> kuWeiNotrhX, kuWeiNotrhY, kuWeiNotrhZ, kuWeiNotrhE, kuWeiNotrhtime, kuWeiNotrhtimeErr, kuWeiNotrhTOF;
  std::vector<unsigned int> kuWeiNotrhID;
  std::vector<bool> kuWeiNotrhisOOT, kuWeiNotrhisGS6, kuWeiNotrhisGS1;
  std::vector<float> kuWeiNotrhadcToGeV;
  std::vector<float> kuWeiNotrhped12, kuWeiNotrhped6, kuWeiNotrhped1;
  std::vector<float> kuWeiNotrhpedrms12, kuWeiNotrhpedrms6, kuWeiNotrhpedrms1;

  // kuWeiNotStcRecHits
  int nkuWeiNotStcrechits;
  std::vector<float> kuWeiNotStcrhX, kuWeiNotStcrhY, kuWeiNotStcrhZ, kuWeiNotStcrhE, kuWeiNotStcrhtime, kuWeiNotStcrhtimeErr, kuWeiNotStcrhTOF;
  std::vector<unsigned int> kuWeiNotStcrhID;
  std::vector<bool> kuWeiNotStcrhisOOT, kuWeiNotStcrhisGS6, kuWeiNotStcrhisGS1;
  std::vector<float> kuWeiNotStcrhadcToGeV;
  std::vector<float> kuWeiNotStcrhped12, kuWeiNotStcrhped6, kuWeiNotStcrhped1;
  std::vector<float> kuWeiNotStcrhpedrms12, kuWeiNotStcrhpedrms6, kuWeiNotStcrhpedrms1;

  // Uncalibrated RecHits
  int nurechits;
  std::vector<unsigned int> uRhId;
  std::vector<float> amplitude, amplitudeError, pedestal, jitter, chi2, jitterError;
  //std::vector<std::vector<float> > outOfTimeAmplitude;
  std::vector<float> ootA0, ootA1, ootA2, ootA3, ootA4, ootA5, ootA6, ootA7, ootA8, ootA9;

  // Uncalibrated kuKs RecHits
  int nkuKsUrechits;
  std::vector<unsigned int> kuKs_uRhId;
  std::vector<float> kuKs_amplitude, kuKs_amplitudeError, kuKs_pedestal, kuKs_jitter, kuKs_chi2, kuKs_jitterError;
  //std::vector<std::vector<float> > outOfTimeAmplitude;
  std::vector<float> kuKs_ootA0, kuKs_ootA1, kuKs_ootA2, kuKs_ootA3, kuKs_ootA4, kuKs_ootA5, kuKs_ootA6, kuKs_ootA7, kuKs_ootA8, kuKs_ootA9;

  // Uncalibrated KuWei RecHits
  int nKuWeiUrechits;
  std::vector<unsigned int> kuWei_uRhId;
  std::vector<float> kuWei_amplitude, kuWei_amplitudeError, kuWei_pedestal, kuWei_jitter, kuWei_chi2, kuWei_jitterError;
  //std::vector<std::vector<float> > outOfTimeAmplitude;
  std::vector<float> kuWei_ootA0, kuWei_ootA1, kuWei_ootA2, kuWei_ootA3, kuWei_ootA4, kuWei_ootA5, kuWei_ootA6, kuWei_ootA7, kuWei_ootA8, kuWei_ootA9;

  // Uncalibrated kuWieNot RecHits
  int nkuWeiNotUrechits;
  std::vector<unsigned int> kuWeiNot_uRhId;
  std::vector<float> kuWeiNot_amplitude, kuWeiNot_amplitudeError, kuWeiNot_pedestal, kuWeiNot_jitter, kuWeiNot_chi2, kuWeiNot_jitterError;
  //std::vector<std::vector<float> > outOfTimeAmplitude;
  std::vector<float> kuWeiNot_ootA0, kuWeiNot_ootA1, kuWeiNot_ootA2, kuWeiNot_ootA3, kuWeiNot_ootA4;
  std::vector<float> kuWeiNot_ootA5, kuWeiNot_ootA6, kuWeiNot_ootA7, kuWeiNot_ootA8, kuWeiNot_ootA9;

  std::vector<bool> isSaturated, isJitterValid, isJitterErrorValid;

  // Digis
  int ndigis;
  std::vector<unsigned int> digiID;
  std::vector<std::vector<float> > digiData;

  // photon info
  int nphotons;
  std::vector<phoStruct> phoBranches;
};

#endif
