#ifndef __DisPhoMulti__
#define __DisPhoMulti__

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

class DisPhoMulti : public edm::one::EDAnalyzer<edm::one::SharedResources,edm::one::WatchRuns> 
{
public:

  ////////////////////////
  // Internal Functions //
  ////////////////////////

  explicit DisPhoMulti(const edm::ParameterSet & iConfig);
  void ConsumeTokens();
  ~DisPhoMulti();
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
  void InitializeLHCInfo();
  
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
  void SetKuStcRecHitBranches(const EcalRecHitCollection * recHits, const CaloSubdetectorGeometry * geometry, const float adcToGeV);
  void SetKuNotRecHitBranches(const EcalRecHitCollection * recHits, const CaloSubdetectorGeometry * geometry, const float adcToGeV);
  void SetKuNotStcRecHitBranches(const EcalRecHitCollection * recHits, const CaloSubdetectorGeometry * geometry, const float adcToGeV);
  void SetKuWtStcRecHitBranches(const EcalRecHitCollection * recHits, const CaloSubdetectorGeometry * geometry, const float adcToGeV);
  void SetKuWootStcRecHitBranches(const EcalRecHitCollection * recHits, const CaloSubdetectorGeometry * geometry, const float adcToGeV);
  void SetKuMfootStcRecHitBranches(const EcalRecHitCollection * recHits, const CaloSubdetectorGeometry * geometry, const float adcToGeV);
  void SetKuMfootCCStcRecHitBranches(const EcalRecHitCollection * recHits, const CaloSubdetectorGeometry * geometry, const float adcToGeV);
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

  // KU  RecHits EB
  const edm::InputTag kuRecHitsEBTag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuRecHitsEBToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuRecHitsEBH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuRecHitsEB;

  // KU  RecHits EE
  const edm::InputTag kuRecHitsEETag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuRecHitsEEToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuRecHitsEEH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuRecHitsEE;

  // KU Stc RecHits EB
  const edm::InputTag kuStcRecHitsEBTag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuStcRecHitsEBToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuStcRecHitsEBH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuStcRecHitsEB;

  // KU Stc RecHits EE
  const edm::InputTag kuStcRecHitsEETag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuStcRecHitsEEToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuStcRecHitsEEH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuStcRecHitsEE;

  // KU Not RecHits EB
  const edm::InputTag kuNotRecHitsEBTag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuNotRecHitsEBToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuNotRecHitsEBH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuNotRecHitsEB;

  // KU Not RuecHits EE
  const edm::InputTag kuNotRecHitsEETag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuNotRecHitsEEToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuNotRecHitsEEH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuNotRecHitsEE;

  // KU NotStc RecHits EB
  const edm::InputTag kuNotStcRecHitsEBTag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuNotStcRecHitsEBToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuNotStcRecHitsEBH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuNotStcRecHitsEB;

  // KU NotStc RuecHits EE
  const edm::InputTag kuNotStcRecHitsEETag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuNotStcRecHitsEEToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuNotStcRecHitsEEH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuNotStcRecHitsEE;

  // KU WtStc RecHits EB
  const edm::InputTag kuWtStcRecHitsEBTag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWtStcRecHitsEBToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWtStcRecHitsEBH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuWtStcRecHitsEB;

  // KU WtStc RuecHits EE
  const edm::InputTag kuWtStcRecHitsEETag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWtStcRecHitsEEToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWtStcRecHitsEEH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuWtStcRecHitsEE;

  // KU WootStc RecHits EB
  const edm::InputTag kuWootStcRecHitsEBTag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWootStcRecHitsEBToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWootStcRecHitsEBH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuWootStcRecHitsEB;

  // KU WootStc RuecHits EE
  const edm::InputTag kuWootStcRecHitsEETag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWootStcRecHitsEEToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuWootStcRecHitsEEH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuWootStcRecHitsEE;

  // KU MfootStc RecHits EB
  const edm::InputTag kuMfootStcRecHitsEBTag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuMfootStcRecHitsEBToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuMfootStcRecHitsEBH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuMfootStcRecHitsEB;

  // KU MfootStc RuecHits EE
  const edm::InputTag kuMfootStcRecHitsEETag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuMfootStcRecHitsEEToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuMfootStcRecHitsEEH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuMfootStcRecHitsEE;

  // KU MfootCCStc RecHits EB
  const edm::InputTag kuMfootCCStcRecHitsEBTag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuMfootCCStcRecHitsEBToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuMfootCCStcRecHitsEBH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuMfootCCStcRecHitsEB;

  // KU MfootCCStc RuecHits EE
  const edm::InputTag kuMfootCCStcRecHitsEETag;
  edm::EDGetTokenT<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuMfootCCStcRecHitsEEToken;
  edm::Handle<edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > > kuMfootCCStcRecHitsEEH;
  const edm::SortedCollection<EcalRecHit,edm::StrictWeakOrdering<EcalRecHit> > * kuMfootCCStcRecHitsEE;

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

  // EB Uncalibrated ku RecHits
  //const edm::InputTag ku_uncalibratedRecHitsEBTag;
  //edm::EDGetTokenT<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > ku_uncalibratedRecHitsEBToken;
  //edm::Handle<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > ku_uncalibratedRecHitsEBH;
  //const edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > * ku_uncalibratedRecHitsEB;

  // EE Uncalibrated ku RecHits
  //const edm::InputTag ku_uncalibratedRecHitsEETag;
  //edm::EDGetTokenT<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > ku_uncalibratedRecHitsEEToken;
  //edm::Handle<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > ku_uncalibratedRecHitsEEH;
  //const edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > * ku_uncalibratedRecHitsEE;


  // EB Uncalibrated kuNot RecHits
  //const edm::InputTag kuNot_uncalibratedRecHitsEBTag;
  //edm::EDGetTokenT<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > kuNot_uncalibratedRecHitsEBToken;
  //edm::Handle<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > kuNot_uncalibratedRecHitsEBH;
  //const edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > * kuNot_uncalibratedRecHitsEB;

  // EE Uncalibrated kuNot RecHits
  //const edm::InputTag kuNot_uncalibratedRecHitsEETag;
  //edm::EDGetTokenT<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > kuNot_uncalibratedRecHitsEEToken;
  //edm::Handle<edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > > kuNot_uncalibratedRecHitsEEH;
  //const edm::SortedCollection<EcalUncalibratedRecHit,edm::StrictWeakOrdering<EcalUncalibratedRecHit> > * kuNot_uncalibratedRecHitsEE;

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
  uiiumap kuStcRecHitMap;
  uiiumap kuNotRecHitMap;
  uiiumap kuNotStcRecHitMap;
  uiiumap kuWtStcRecHitMap;
  uiiumap kuWootStcRecHitMap;
  uiiumap kuMfootStcRecHitMap;
  uiiumap kuMfootCCStcRecHitMap;

  uiiumap uncalibratedRecHitMap;
  //uiiumap ku_uncalibratedRecHitMap;
  //uiiumap kuNot_uncalibratedRecHitMap;

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
  int nJets, nDigis, nPhotons;
  int nRecHits, nKuRecHits, nKuStcRecHits, nKuNotRecHits, nKuNotStcRecHits, nKuWtStcRecHits, nKuWootStcRecHits, nKuMfootStcRecHits, nKuMfootCCStcRecHits;
  int nURecHits, nKuURecHits, nKuNotURecHits;

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

  // kuRecHits
  int nkurechits;
  std::vector<float> kurhX, kurhY, kurhZ, kurhE, kurhtime, kurhtimeErr, kurhTOF;
  std::vector<unsigned int> kurhID;
  std::vector<bool> kurhisOOT, kurhisGS6, kurhisGS1;
  std::vector<float> kurhadcToGeV;
  std::vector<float> kurhped12, kurhped6, kurhped1;
  std::vector<float> kurhpedrms12, kurhpedrms6, kurhpedrms1;

  // kuStcRecHits
  int nkuStcrechits;
  std::vector<float> kuStcrhX, kuStcrhY, kuStcrhZ, kuStcrhE, kuStcrhtime, kuStcrhtimeErr, kuStcrhTOF;
  std::vector<unsigned int> kuStcrhID;
  std::vector<bool> kuStcrhisOOT, kuStcrhisGS6, kuStcrhisGS1;
  std::vector<float> kuStcrhadcToGeV;
  std::vector<float> kuStcrhped12, kuStcrhped6, kuStcrhped1;
  std::vector<float> kuStcrhpedrms12, kuStcrhpedrms6, kuStcrhpedrms1;

  // kuNotRecHits
  int nkuNotrechits;
  std::vector<float> kuNotrhX, kuNotrhY, kuNotrhZ, kuNotrhE, kuNotrhtime, kuNotrhtimeErr, kuNotrhTOF;
  std::vector<unsigned int> kuNotrhID;
  std::vector<bool> kuNotrhisOOT, kuNotrhisGS6, kuNotrhisGS1;
  std::vector<float> kuNotrhadcToGeV;
  std::vector<float> kuNotrhped12, kuNotrhped6, kuNotrhped1;
  std::vector<float> kuNotrhpedrms12, kuNotrhpedrms6, kuNotrhpedrms1;

  // kuNotStcRecHits
  int nkuNotStcrechits;
  std::vector<float> kuNotStcrhX, kuNotStcrhY, kuNotStcrhZ, kuNotStcrhE, kuNotStcrhtime, kuNotStcrhtimeErr, kuNotStcrhTOF;
  std::vector<unsigned int> kuNotStcrhID;
  std::vector<bool> kuNotStcrhisOOT, kuNotStcrhisGS6, kuNotStcrhisGS1;
  std::vector<float> kuNotStcrhadcToGeV;
  std::vector<float> kuNotStcrhped12, kuNotStcrhped6, kuNotStcrhped1;
  std::vector<float> kuNotStcrhpedrms12, kuNotStcrhpedrms6, kuNotStcrhpedrms1;

  // kuWtStcRecHits
  int nkuWtStcrechits;
  std::vector<float> kuWtStcrhX, kuWtStcrhY, kuWtStcrhZ, kuWtStcrhE, kuWtStcrhtime, kuWtStcrhtimeErr, kuWtStcrhTOF;
  std::vector<unsigned int> kuWtStcrhID;
  std::vector<bool> kuWtStcrhisOOT, kuWtStcrhisGS6, kuWtStcrhisGS1;
  std::vector<float> kuWtStcrhadcToGeV;
  std::vector<float> kuWtStcrhped12, kuWtStcrhped6, kuWtStcrhped1;
  std::vector<float> kuWtStcrhpedrms12, kuWtStcrhpedrms6, kuWtStcrhpedrms1;

  // kuWootStcRecHits
  int nkuWootStcrechits;
  std::vector<float> kuWootStcrhX, kuWootStcrhY, kuWootStcrhZ, kuWootStcrhE, kuWootStcrhtime, kuWootStcrhtimeErr, kuWootStcrhTOF;
  std::vector<unsigned int> kuWootStcrhID;
  std::vector<bool> kuWootStcrhisOOT, kuWootStcrhisGS6, kuWootStcrhisGS1;
  std::vector<float> kuWootStcrhadcToGeV;
  std::vector<float> kuWootStcrhped12, kuWootStcrhped6, kuWootStcrhped1;
  std::vector<float> kuWootStcrhpedrms12, kuWootStcrhpedrms6, kuWootStcrhpedrms1;

  // kuMfootStcRecHits
  int nkuMfootStcrechits;
  std::vector<float> kuMfootStcrhX, kuMfootStcrhY, kuMfootStcrhZ, kuMfootStcrhE, kuMfootStcrhtime, kuMfootStcrhtimeErr, kuMfootStcrhTOF;
  std::vector<unsigned int> kuMfootStcrhID;
  std::vector<bool> kuMfootStcrhisOOT, kuMfootStcrhisGS6, kuMfootStcrhisGS1;
  std::vector<float> kuMfootStcrhadcToGeV;
  std::vector<float> kuMfootStcrhped12, kuMfootStcrhped6, kuMfootStcrhped1;
  std::vector<float> kuMfootStcrhpedrms12, kuMfootStcrhpedrms6, kuMfootStcrhpedrms1;

  // kuMfootCCStcRecHits
  int nkuMfootCCStcrechits;
  std::vector<float> kuMfootCCStcrhX, kuMfootCCStcrhY, kuMfootCCStcrhZ, kuMfootCCStcrhE, kuMfootCCStcrhtime, kuMfootCCStcrhtimeErr, kuMfootCCStcrhTOF;
  std::vector<unsigned int> kuMfootCCStcrhID;
  std::vector<bool> kuMfootCCStcrhisOOT, kuMfootCCStcrhisGS6, kuMfootCCStcrhisGS1;
  std::vector<float> kuMfootCCStcrhadcToGeV;
  std::vector<float> kuMfootCCStcrhped12, kuMfootCCStcrhped6, kuMfootCCStcrhped1;
  std::vector<float> kuMfootCCStcrhpedrms12, kuMfootCCStcrhpedrms6, kuMfootCCStcrhpedrms1;

  // Uncalibrated RecHits
  int nurechits;
  std::vector<unsigned int> uRhId;
  std::vector<float> amplitude, amplitudeError, pedestal, jitter, chi2, jitterError;
  //std::vector<std::vector<float> > outOfTimeAmplitude;
  std::vector<float> ootA0, ootA1, ootA2, ootA3, ootA4, ootA5, ootA6, ootA7, ootA8, ootA9;

  // Uncalibrated ku RecHits
  //int nkuUrechits;
  //std::vector<unsigned int> ku_uRhId;
  //std::vector<float> ku_amplitude, ku_amplitudeError, ku_pedestal, ku_jitter, ku_chi2, ku_jitterError;
  ////std::vector<std::vector<float> > outOfTimeAmplitude;
  //std::vector<float> ku_ootA0, ku_ootA1, ku_ootA2, ku_ootA3, ku_ootA4, ku_ootA5, ku_ootA6, ku_ootA7, ku_ootA8, ku_ootA9;

  // Uncalibrated kuWieNot RecHits
  //int nkuNotUrechits;
  //std::vector<unsigned int> kuNot_uRhId;
  //std::vector<float> kuNot_amplitude, kuNot_amplitudeError, kuNot_pedestal, kuNot_jitter, kuNot_chi2, kuNot_jitterError;
  ////std::vector<std::vector<float> > outOfTimeAmplitude;
  //std::vector<float> kuNot_ootA0, kuNot_ootA1, kuNot_ootA2, kuNot_ootA3, kuNot_ootA4;
  //std::vector<float> kuNot_ootA5, kuNot_ootA6, kuNot_ootA7, kuNot_ootA8, kuNot_ootA9;

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
